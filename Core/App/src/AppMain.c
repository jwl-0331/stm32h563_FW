/*
 * AppMain.c
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */
#include "main.h"
#include "BSPConfig.h"
#include "lwip.h"
#include "app_ethernet.h"
#include "tcp_echoserver.h"
#include "tcp_client.h"

#include "LED.h"
#include "UART.h"
#include "RESET.h"
#include "RTC.h"
#include "FLASH.h"
#include "CAN.h"

#include "BuildTime.h"
#include "svUtils.h"
#include "svTaskTimer.h"
#include "svPlatform.h"
#include "svCLI.h"
#include "svDebug.h"
#include "svRingBuffer.h"

struct netif gnetif;
extern BOOL timeFlag;

void ethernetif_notify_conn_changed(struct netif *netif)
{
  /* NOTE : This is function could be implemented in user file
   when the callback is needed,
   */
  if (netif_is_link_up(netif))
  {
    HAL_GPIO_WritePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED3_RED_GPIO_Port, LED3_RED_Pin, GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_RED_GPIO_Port, LED3_RED_Pin, GPIO_PIN_SET);
  }
}

void AppMain()
{
  __enable_irq();

  RESET_Init();
  LED_Init();
  LED_SimpleAnimation();

  svDebugInit();
  UART_Init(_DEF_UART1, 115200);

  CAN_Init();
  CAN_Open(_DEF_CAN1, CAN_NORMAL, CAN_CLASSIC, CAN_1M, CAN_2M);


  //lwip_init();
  MX_LWIP_Init();
  //tcp_echoserver_init(7);

  /* USER CODE BEGIN 2 */
  ethernetif_notify_conn_changed(&gnetif);


  // Chk Reset Count
  //uint32_t pre_time = HAL_GetTick();
  DebugMsg(DEBUGMSG_APP, "\r\n<< svCLI TEST : >>\r\n");

  /* RTOS */
  /* Init scheduler */
  //osKernelInitialize();

  /* Call init function for freertos objects (in freertos.c) */
  //MX_FREERTOS_Init();

  /* Start scheduler */
  //osKernelStart();
  while(1)
  {
    /*TCP ECHO SERVER */
    /* Read a received packet from the Ethernet buffers and send it
       to the lwIP for handling */
    //ethernetif_input(&gnetif);

    /* Handle timeouts */
    //sys_check_timeouts();

#if LWIP_NETIF_LINK_CALLBACK
    //Ethernet_Link_Periodic_Handle(&gnetif);
#endif

#if LWIP_DHCP
    DHCP_Periodic_Handle(&gnetif);
#endif
    /* End OF ECHO SERVER  */


    svDebugProcess();
    MX_LWIP_Process();

    if(timeFlag)
    {
      timeFlag = FALSE;
      app_start_get_time(); //get time information from the server
    }
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

