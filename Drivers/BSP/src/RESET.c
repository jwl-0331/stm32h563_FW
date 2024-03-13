/*
 * RESET.c
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */
#include "RESET.h"
#include "RTC.h"

static uint32_t s_ResetCount = 0;
static uint32_t s_RunTimeoutCount = 0;

void Reset_ISR(void)
{
  if(s_RunTimeoutCount > 0)
  {
    s_RunTimeoutCount--;
    if(s_RunTimeoutCount == 0)
    {
      Reset_ToRunBoot();
    }
  }
}


BOOL RESET_Init(void)
{
  BOOL ret = TRUE;
  BOOL is_debug = FALSE;


  // 만약 디버거가 연결된 경우

  if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
  {
    is_debug = TRUE;
  }
  RTC_WriteBackupReg(RESET_REG_COUNT+1, RESET_REG_MAGICNUMBER);
  // 만약 Reset 핀이 눌렸다면
  // 리셋 상태 레지스터 자기자신 + 1 을 준다.
  // 500ms 안에 여러번 누른경우 reset_count 값에 저장된다.
  if((RCC->RSR & (1<<26) && is_debug != TRUE) && RTC_ReadBackupReg(RESET_REG_COUNT+1) == RESET_REG_MAGICNUMBER)
  {
    RTC_WriteBackupReg(RESET_REG_COUNT, RTC_ReadBackupReg(RESET_REG_COUNT) + 1);
    HAL_Delay(500); // 500 m delay
    s_ResetCount = RTC_ReadBackupReg(RESET_REG_COUNT);
  }
  //clear 다시 0으로
  RTC_WriteBackupReg(RESET_REG_COUNT, 0);

  return ret;
}

uint32_t Reset_GetCount(void)
{
  return s_ResetCount;
}
void Reset_ToRunBoot(uint32_t timeout)
{
  void(*SysMemBootJump)(void);
  volatile uint32_t addr = 0x1FFF0000;

  HAL_RCC_DeInit();

  //SYSCFG->MEMRMP = 0x01;
  //SYSCFG->CFGR1 = 0x01;
  SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL  = 0;

  for (int i=0;i<8;i++)
  {
    NVIC->ICER[i]=0xFFFFFFFF;
    NVIC->ICPR[i]=0xFFFFFFFF;
    __DSB();
    __ISB();
  }

  SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));

  __set_MSP(*(uint32_t *)addr);
  SysMemBootJump();
}
void RESET_ToSystemBoot(void)
{
  uint32_t reg;

  reg = RTC_ReadBackupReg(RESET_REG_PARAM);

  reg |= (1<<0);
  RTC_WriteBackupReg(RESET_REG_PARAM, reg);
  NVIC_SystemReset();
}

