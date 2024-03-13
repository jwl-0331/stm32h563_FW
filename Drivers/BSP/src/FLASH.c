/*
 * FLASH.c
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */
#include "Flash.h"
#include "svCLI.h"
#include "svDebug.h"

#define FLASH_MAX_BANK    2
#define FLASH_MAX_SECTOR  128
#define FLASH_WRITE_SIZE 16   // Allign

/*
typedef struct
{
  int16_t  index;
  uint32_t bank;
  uint32_t addr;
  uint32_t length;
} FLASH_t;
*/




static BOOL Flash_InSector(uint16_t sector_num, uint32_t addr, uint32_t length);

BOOL Flash_Init(void)
{
  BOOL ret = TRUE;


  return ret;
}
BOOL Flash_Erase(uint32_t addr, uint32_t length)
{
  BOOL ret = FALSE;

  int32_t start_sector = -1;
  int32_t end_sector = -1;

  HAL_FLASH_Unlock();
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTCHANGEERR);

  start_sector = -1;
  end_sector = -1;

  for(int i=0; i < FLASH_MAX_SECTOR; i++)
  {
    if(Flash_InSector(i, addr, length) == TRUE)
    {
      if(start_sector < 0)
      {
        start_sector = i;
      }
      end_sector = i;
    }
  }

  if(start_sector >= 0)
  {
    //HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError)
    HAL_StatusTypeDef status;
    // TypeErase : Mass or Page Erase ,Banks :   Page/PageAddress:  Nbpages:
    FLASH_EraseInitTypeDef EraseInit;
    uint32_t SectorError;
    //@ref FLASH_Type_Erase
    EraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
    //@ref FLASH_Banks  - FLASH_BANK_BOTH  , 1
    EraseInit.Banks = FLASH_BANK_BOTH;
    EraseInit.Sector = start_sector;    // sector 번호 OR sector address , 확인해야댐 (페이지 번호를 주거나, 지우는 주소를 주거나)
    EraseInit.NbSectors = (end_sector - start_sector) + 1;     // 페이지 개수 (시작 페이지 부터 몇개의 페이지를 지울 것인가)

    status = HAL_FLASHEx_Erase(&EraseInit, &SectorError);

    if(status == HAL_OK)
    {
      ret = TRUE;
    }
  }

  HAL_FLASH_Lock();
  return ret;
}
BOOL Flash_InSector(uint16_t sector_num, uint32_t addr, uint32_t length)
{
  BOOL ret = FALSE;

  uint32_t sector_start;
  uint32_t sector_end;
  uint32_t flash_start;
  uint32_t flash_end;


  sector_start = FLASH_BASE + (sector_num * FLASH_SECTOR_SIZE);
  sector_end   = sector_start + FLASH_SECTOR_SIZE - 1;
  flash_start  = addr;
  flash_end    = addr + length - 1;


  if (sector_start >= flash_start && sector_start <= flash_end)
  {
    ret = TRUE;
  }

  if (sector_end >= flash_start && sector_end <= flash_end)
  {
    ret = TRUE;
  }

  if (flash_start >= sector_start && flash_start <= sector_end)
  {
    ret = TRUE;
  }

  if (flash_end >= sector_start && flash_end <= sector_end)
  {
    ret = TRUE;
  }

  return ret;
}

BOOL Flash_Write(uint32_t addr, uint8_t *p_data, uint32_t length)
{
  BOOL ret = TRUE;
  uint32_t index;
  uint32_t write_length;
  uint32_t write_addr;
  uint8_t buf[32];
  uint32_t offset;
  HAL_StatusTypeDef status;

  // FLASH 메모리를 access 하기 위해 필요
  HAL_FLASH_Unlock();

  index = 0;
  offset = addr % FLASH_WRITE_SIZE;


  if(offset != 0 || length < FLASH_WRITE_SIZE)
  {
    write_addr = addr - offset;
    memcpy(&buf[0], (void *)write_addr, FLASH_WRITE_SIZE);
    memcpy(&buf[offset], &p_data[0], constrain(FLASH_WRITE_SIZE-offset, 0, length));

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, write_addr, (uint32_t)&buf);
    if (status != HAL_OK)
    {
      return FALSE;
    }

    if (offset == 0 && length < FLASH_WRITE_SIZE)
    {
      index += length;
    }
    else
    {
      index += (FLASH_WRITE_SIZE - offset);
    }
  }
  while(index < length)
  {
    write_length = constrain(length - index, 0, FLASH_WRITE_SIZE);

    if (write_length == FLASH_WRITE_SIZE)
    {
      status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, addr + index, (uint32_t)&p_data[index]);
      if (status != HAL_OK)
      {
        ret = FALSE;
        break;
      }
      index += write_length;
    }

    if ((length - index) > 0 && (length - index) < FLASH_WRITE_SIZE)
    {
      offset = length - index;
      write_addr = addr + index;
      memcpy(&buf[0], (void *)write_addr, FLASH_WRITE_SIZE);
      memcpy(&buf[0], &p_data[index], offset);

      status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, write_addr, (uint32_t)&buf);
      if (status != HAL_OK)
      {
        return FALSE;
      }
      break;
    }
  }
  // FLASH 메모리를 access 하기 위해 필요
  HAL_FLASH_Lock();
  return ret;
}
BOOL Flash_Read(uint32_t addr, uint32_t *p_data, uint32_t length)
{
  BOOL ret = TRUE;

  // 1byte 데이터 포인터
  uint8_t *p_byte = (uint8_t *)addr;

  for(int i=0; i < length; i++)
  {
    p_data[i] = p_byte[i];
  }



  return ret;
}

// Read, Erase, Write
#ifdef USE_CLI_FUNCTIONS
SVCLI_TABLE_ENTRY (FLASH_TEST, "Flash", "Flash [1(Read),2(Erase),3(Write)] [0x0800 F000 ~ address]", CLI_FlashTest)
static void CLI_FlashTest(char *pArgLine, unsigned int nCount, unsigned int nFirst, unsigned int nAddress)
{
  if(nCount == 2)
  {
    switch(nFirst)
    {
      case 1:
        uint32_t rbuf[16];
        DebugMsg(DEBUGMSG_CLI,"=============================================\r\n");
        Flash_Read(nAddress, &rbuf[0],16);
        for(int i=0; i<16; i++)
        {
          DebugMsg(DEBUGMSG_CLI, "0x%X : 0x%X\n", nAddress + i, rbuf[i]);
        }
        break;
      case 2:
        if(Flash_Erase(nAddress, 16) == TRUE)
        {
          DebugMsg(DEBUGMSG_CLI, "Erase OK\n");
        }
        else
        {
          DebugMsg(DEBUGMSG_CLI, "Erase Fail\n");
        }
        break;
      case 3:
        uint8_t wbuf[16];
        for(int i=0; i<16; i++)
        {
          wbuf[i] = i;
        }
        if(Flash_Write(nAddress, wbuf, 16) == TRUE)
        {
          DebugMsg(DEBUGMSG_CLI, "Write OK\n");
        }
        else
        {
          DebugMsg(DEBUGMSG_CLI,"Write Fail\n");
        }
        break;
      default:
        DebugMsg(DEBUGMSG_CLI,"\r\nFlash [1(Read),2(Erase),3(Write)] [0x0800 F000 ~ address]\r\n");
        break;
    }
  }
}
#endif
