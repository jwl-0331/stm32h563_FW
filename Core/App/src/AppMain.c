/*
 * AppMain.c
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */
#include "AppConfig.h"

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

#include "MQTTPaho.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern struct netif gnetif;  //reside in lwip.c
extern BOOL timeFlag;
extern UART_HandleTypeDef huart2;

/*RTOS - ECHO SERVER*/
osThreadId_t g_hTaskMain;
const osThreadAttr_t TaskMain_attributes = {
  .name = "TaskMain",
  .priority = (osPriority_t) TASK_PRIORITY_MAIN,
  .stack_size = STACK_SIZE_MAIN*4
};
osThreadId_t echoTaskHandle; // echo server task handle
const osThreadAttr_t echoTask_attributes = {
  .name = "echoTask",
  .priority = (osPriority_t) TASK_PRIORITY_TCP,
  .stack_size = STACK_SIZE_TCP
};

/* RTOS - Tcp Client */
extern struct netif gnetif; //extern gnetif
osThreadId_t tcpClientTaskHandle;  //tcp client task handle
const osThreadAttr_t tcpClientTask_attributes = {
  .name = "tcpClientTask",
  .priority = (osPriority_t) TASK_PRIORITY_TCP,
  .stack_size = STACK_SIZE_TCP
};

ip_addr_t server_addr; //server address
struct time_packet packet; //256 bytes time_packet structure


/* FOR LWIP DEBUG MSG */
/*
#ifdef __GNUC__

  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}
*/
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

  //MX_LWIP_Init();
  /* NO RTOS */
  //app_echoserver_init();

  //ethernetif_notify_conn_changed(&gnetif);

  // Chk Reset Count
  //uint32_t pre_time = HAL_GetTick();
  DebugMsg(DEBUGMSG_APP, "\r\n<< svCLI TEST : >>\r\n");
  /* Init scheduler */
  osKernelInitialize();


  g_hTaskMain = osThreadNew(TaskMain, NULL, &TaskMain_attributes);
  echoTaskHandle = osThreadNew(StartEchoTask, NULL, &echoTask_attributes);
  tcpClientTaskHandle = osThreadNew(StartTcpClientTask, NULL, &tcpClientTask_attributes);
  MQTT_Init();

  osKernelStart();
  /*With out RTOS */
  while(1)
  {
    /* End OF ECHO SERVER  */


    svDebugProcess();
    //MX_LWIP_Process();



    /* NO RTOS */
    /*tcp_client module */
    /*
    if(timeFlag)
    {
      timeFlag = FALSE;
      app_start_get_time(); //get time information from the server
    }
    */
    /*tcp_echoserver */
    /*
#if LWIP_NETIF_LINK_CALLBACK
    Ethernet_Link_Periodic_Handle(&gnetif);
#endif

#if LWIP_DHCP
    DHCP_Periodic_Handle(&gnetif);
#endif
*/

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

void TaskMain(void* argument)
{
  MX_LWIP_Init();

  //echoTaskHandle = osThreadNew(StartEchoTask, NULL, &echoTask_attributes);
  //tcpClientTaskHandle = osThreadNew(StartTcpClientTask, NULL, &tcpClientTask_attributes);
  for(;;)
  {
    svDebugProcess();
    HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin); //toggle running led
    osDelay(500);
  }

}

void StartEchoTask(void const *argument)
{
  /* Netconn API */
  struct netconn *conn, *newconn;
  err_t err, accept_err;
  struct netbuf *buf;
  void *data;
  u16_t len;

  LWIP_UNUSED_ARG(argument);

  conn = netconn_new(NETCONN_TCP); //new tcp netconn , create new connection

  if (conn != NULL)
  {
    err = netconn_bind(conn, NULL, 7); //bind to port 7

    if (err == ERR_OK)
    {
      netconn_listen(conn); //listen at port 7

      while (1)
      {
        accept_err = netconn_accept(conn, &newconn); //accept new connection

        if (accept_err == ERR_OK) //accept ok
        {
          DebugMsg(DEBUGMSG_APP, "\r\nTCP Connected\r\n");
          while (netconn_recv(newconn, &buf) == ERR_OK) //receive data
          {
            do
            {
              netbuf_data(buf, &data, &len); //receive data pointer & length  buf -> data
              DebugMsg(DEBUGMSG_APP, "\r\nMSG FROM Client: %s\r\n",data);
              netconn_write(newconn, data, len, NETCONN_COPY); //echo back to the client

              HAL_GPIO_TogglePin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin); //toggle data led
            }
            while (netbuf_next(buf) >= 0); //check buffer empty

            netbuf_delete(buf); //clear buffer
          }

          netconn_close(newconn); //close session
          netconn_delete(newconn); //free memory
        }
      }
    }
    else
    {
      netconn_delete(newconn); //free memory
    }
  }
}

void StartTcpClientTask(void const *argument)
{
  err_t err;
  struct netconn *conn;
  struct netbuf *buf;
  void *data;

  u16_t len; //buffer length
  u16_t nRead; //read buffer index
  u16_t nWritten; //write buffer index

  LWIP_UNUSED_ARG(argument);

  while (1)
  {
    if (gnetif.ip_addr.addr == 0 || gnetif.netmask.addr == 0 || gnetif.gw.addr == 0) //system has no valid ip address
    {
      osDelay(1000);
      continue;
    }
    else //valid ip address
    {
      osDelay(100); //request interval
    }

    nRead = 0; //clear indexes
    nWritten = 0;

    conn = netconn_new(NETCONN_TCP); //new tcp netconn

    if (conn != NULL)
    {
      IP4_ADDR(&server_addr, SERVER_IP1, SERVER_IP2, SERVER_IP3, SERVER_IP4); //server ip
      err = netconn_connect(conn, &server_addr, SERVER_PORT); //connect to the server

      if (err != ERR_OK)
      {
        netconn_delete(conn); //free memory
        continue;
      }

      memset(&packet, 0, sizeof(struct time_packet));
      /*
      packet.head = 0xAE; //head
      packet.type = REQ; //request typ
      packet.year = 2024;
      packet.month = 03;
      packet.day = 06;
      packet.hour = 17;
      packet.minute = 30;
      packet.second = 0;
      packet.dummy[0] = 11;
      packet.tail = 0xEA; //tail
      */
      packet.dummy[0] = 'H';
      packet.dummy[1] = 'E';
      packet.dummy[2] = 'L';
      packet.dummy[3] = 'L';
      packet.dummy[4] = 'O';

      do
      {
        if (netconn_write_partly(
            conn, //connection
            (const void*) (&packet + nWritten), //buffer pointer
            (sizeof(struct time_packet) - nWritten), //buffer length
            NETCONN_NOFLAG, //no copy
            (size_t*) &len) != ERR_OK) //written len
        {
          netconn_close(conn); //close session
          netconn_delete(conn); //free memory
          continue;
        }
        else
        {
          nWritten += len;  // write buffer index++
        }
      }
      while (nWritten < sizeof(struct time_packet)); //send request

      while (netconn_recv(conn, &buf) == ERR_OK) //receive the response
      {
        do
        {
          netbuf_data(buf, &data, &len); //receive data pointer & length

          memcpy(&packet + nRead, data, len);
          nRead += len;
        }
        while (netbuf_next(buf) >= 0); //check buffer empty
        netbuf_delete(buf); //clear buffer
      }

      if (nRead == sizeof(struct time_packet) )//&& packet.type == RESP) //if received length is valid
      {
        //printf("%04d-%02d-%02d %02d:%02d:%02d\n", packet.year + 2000, packet.month, packet.day, packet.hour, packet.minute, packet.second); //print time information
        HAL_GPIO_TogglePin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin); //toggle data led
      }

      netconn_close(conn); //close session
      netconn_delete(conn); //free memory
    }
  }
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == USER_BUTTON_Pin)
  {
    HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin);
  }
}

/* FOR Printf  */
void _putchar(char character)
{
  HAL_UART_Transmit(&huart2, (const unsigned char*)&character, 1, 1000);
}
