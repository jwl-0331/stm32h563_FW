/*
 * AppMain.c
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */
#include "main.h"
#include "BSPConfig.h"

#include "LED.h"
#include "UART.h"
#include "RESET.h"
#include "RTC.h"
#include "FLASH.h"

#include "BuildTime.h"
#include "svUtils.h"
#include "svTaskTimer.h"
#include "svPlatform.h"
#include "svCLI.h"
#include "svDebug.h"
#include "svRingBuffer.h"
void AppMain()
{
  __enable_irq();

  RESET_Init();
  LED_Init();
  LED_SimpleAnimation();

  svDebugInit();
  UART_Init(_DEF_UART1, 115200);
  // Chk Reset Count
  uint32_t pre_time = HAL_GetTick();

  DebugMsg(DEBUGMSG_APP, "\r\n<< svCLI TEST : >>\r\n");
  /* Init scheduler */
  //osKernelInitialize();

  /* Call init function for freertos objects (in freertos.c) */
  //MX_FREERTOS_Init();

  /* Start scheduler */
  //osKernelStart();
  while(1)
  {

    svDebugProcess();

    /* RESET TEST */
    /*
    if(HAL_GetTick() - pre_time >= 500)
    {
      pre_time = HAL_GetTick();

      UART_Printf(_DEF_UART1, "ResetCount : %d \r\n", Reset_GetCount());
    }
    */
    /*
     * Flash Test
     * firmware 영역을 벗어난곳을 사용하여 test used 47K , 60K 주소 사용
     * 시작주소 0x8000000
     * UART DATA를 받아서
     */
    /*
    if(Uart_Available(_DEF_UART1) > 0)
    {
      uint8_t rx_data;

      rx_data = Uart_Read(_DEF_UART1);

      //read - test
      if(rx_data == '1')
      {
        // 32byte test, 64byte test
        uint32_t buf[16];
        UART_Printf(_DEF_UART1, "Read...\n");

        // 시작 주소 + 60 K 이후 , buf에 32 byte read
        Flash_Read(0x8000000 + (1024 * 60) , buf, 16);

        //화면에 출력 (주소 : data)
        for(int i = 0; i<16; i++)
        {
          UART_Printf(_DEF_UART1,"0x%X : 0x%X\n", 0x8000000 + (1024 * 60) + i, buf[i]);
        }
      }

      //erase - flash 특성상 지우면 0xfff
      if(rx_data == '2')
      {
        UART_Printf(_DEF_UART1,"Erase...\n");
        //지우고자하는 시작 주소 , length
        if(Flash_Erase(0x8000000 + (1024 * 60), 12) == TRUE)
        {
          UART_Printf(_DEF_UART1,"Erase OK\n");
        }
        else
        {
          UART_Printf(_DEF_UART1,"Erase Fail\n");
        }
      }

      //write
      if(rx_data == '3')
      {
        uint8_t buf[16] = {
            120,
            86,
            52,
            18,
            1,
            2,
            3,
            4,
            5,
            6,
            1,
            12,
            13,
            15,
            11,
            11
        };

        UART_Printf(_DEF_UART1,"Write...\n");

        if(Flash_Write(0x8000000 + (60*1024), buf, 20) == TRUE)
        {
          UART_Printf(_DEF_UART1,"Write OK\n");
        }
        else
        {
          UART_Printf(_DEF_UART1,"Write Fail\n");
        }
      }
    }
    */
  }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == USER_BUTTON_Pin)
  {
    HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin);
  }
}

