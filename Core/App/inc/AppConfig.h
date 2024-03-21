/*
 * AppConfig.h
 *
 *  Created on: Mar 19, 2024
 *      Author: mm940
 */

#ifndef APP_INC_APPCONFIG_H_
#define APP_INC_APPCONFIG_H_

#include "BSPConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


/* lwip */
#include "lwip.h"
#include "lwip/api.h"
#include "app_ethernet.h"

/* RAW API */
//#include "tcp_echoserver.h"
//#include "tcp_client.h"

/* MQTT */
#include "MQTTClient.h"
#include "MQTTInterface.h"

// Task Priority
#define TASK_PRIORITY_MAIN                  osPriorityNormal
#define TASK_PRIORITY_MQTT                  osPriorityNormal
#define TASK_PRIORITY_DEBUG                 osPriorityLow
#define TASK_PRIORITY_TCP                  osPriorityNormal

// Task Stack Size - 4Byte Unit !!!
// Make sure the total size is smaller than "configTOTAL_HEAP_SIZE" !!! (200KB)

#define STACK_SIZE_MAIN                     1536
#define STACK_SIZE_TCP                      2048
#define STACK_SIZE_MQTT                     3072      // Note.  MQTT Task stack should be greater than 1024 (Stack Overflow has occurred !!!)
#define STACK_SIZE_IDLE_TASK                configMINIMAL_STACK_SIZE      // 256
#define STACK_SIZE_RTOS_DAEMON_TASK         configTIMER_TASK_STACK_DEPTH  // 1024


#define SERVER_IP1  192 //server ip address
#define SERVER_IP2  168
#define SERVER_IP3  219
#define SERVER_IP4  42
#define SERVER_PORT 1234 //server listen port


void TaskMain(void* argument);
void StartEchoTask(void const *argument);  //echo server task function
void StartTcpClientTask(void const *argument); //tcp client task function


typedef enum
{
  REQ = 0,
  RESP = 1
} packet_type;

struct time_packet
{
  /*
  uint8_t head; //0xAE
  uint8_t type; //0:REQ, 1:RESP
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t dummy[247]; //you may add more information
  uint8_t tail; //0xEA
  */
  uint8_t dummy[5];
};


#endif /* APP_INC_APPCONFIG_H_ */
