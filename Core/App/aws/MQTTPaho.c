/*
 * MQTTPaho.c
 *
 *  Created on: Mar 21, 2024
 *      Author: mm940
 */

/* MQTT library includes */
#include "MQTTPaho.h"
#include "AppConfig.h"
#include "string.h"
#include "svDebug.h"

extern struct netif gnetif; //extern gnetif
Network s_Net; //mqtt network
MQTTClient s_MQTTClient; //mqtt client

uint8_t s_SendBuffer[MQTT_BUFSIZE]; //mqtt send buffer
uint8_t s_RecvBuffer[MQTT_BUFSIZE]; //mqtt receive buffer
uint8_t s_MsgBuffer[MQTT_BUFSIZE]; //mqtt message buffer


int MqttConnectBroker();
void MqttMessageArrived(MessageData* msg);
/* MQTT - Subscribe Handler */
osThreadId_t g_hTaskSubMQTT;  //mqtt client task handle
const osThreadAttr_t TaskSubMQTT_attributes = {
    .name = "mqttClientSubTask",
    .priority = (osPriority_t) TASK_PRIORITY_MQTT,
    .stack_size = STACK_SIZE_MQTT
};


void TaskSubMQTT(void* pvParameters);

void MQTT_Init()
{
  g_hTaskSubMQTT = osThreadNew(TaskSubMQTT, NULL, &TaskSubMQTT_attributes);
}

void TaskSubMQTT(void* pvParameters)
{
  while(1)
  {
    //waiting for valid ip address
    if (gnetif.ip_addr.addr == 0 || gnetif.netmask.addr == 0 || gnetif.gw.addr == 0) //system has no valid ip address
    {
      osDelay(1000);
      continue;
    }
    else
    {
      DebugMsg(DEBUGMSG_APP,"DHCP/Static IP O.K.\n");
      break;
    }
  }

  while(1)
  {
    if(!s_MQTTClient.isconnected)
    {
      //try to connect to the broker
      MQTTDisconnect(&s_MQTTClient);
      MqttConnectBroker();
      osDelay(1000);
    }
    else
    {
      MQTTYield(&s_MQTTClient, 1000); //handle timer
      osDelay(100);
    }
  }
}

int MqttConnectBroker()
{
  int ret;

  NewNetwork(&s_Net);
  ret = ConnectNetwork(&s_Net, BROKER_IP, MQTT_PORT);
  if(ret != MQTT_SUCCESS)
  {
    DebugMsg(DEBUGMSG_APP,"ConnectNetwork failed.\n");
    net_disconnect(&s_Net);
    return -1;
  }

  MQTTClientInit(&s_MQTTClient, &s_Net, 1000, s_SendBuffer, sizeof(s_SendBuffer), s_RecvBuffer, sizeof(s_RecvBuffer));

  MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
  data.willFlag = 0;
  data.MQTTVersion = 3;
  data.clientID.cstring = "STM32H5";
  data.username.cstring = "STM32H5";
  data.password.cstring = "";
  data.keepAliveInterval = 60;
  data.cleansession = 1;

  ret = MQTTConnect(&s_MQTTClient, &data);
  if(ret != MQTT_SUCCESS)
  {
    DebugMsg(DEBUGMSG_APP,"MQTTConnect failed.\n");
    MQTTCloseSession(&s_MQTTClient);
    net_disconnect(&s_Net);
    return ret;
  }

  ret = MQTTSubscribe(&s_MQTTClient, "test", QOS0, MqttMessageArrived);
  if(ret != MQTT_SUCCESS)
  {
    DebugMsg(DEBUGMSG_APP,"MQTTSubscribe failed.\n");
    MQTTCloseSession(&s_MQTTClient);
    net_disconnect(&s_Net);
    return ret;
  }

  DebugMsg(DEBUGMSG_APP,"MQTT_ConnectBroker O.K.\n");
  return MQTT_SUCCESS;
}

void MqttMessageArrived(MessageData* msg)
{
  HAL_GPIO_TogglePin(LED2_YELLOW_GPIO_Port, LED2_YELLOW_Pin); //toggle pin when new message arrived

  MQTTMessage* message = msg->message;
  memset(s_MsgBuffer, 0, sizeof(s_MsgBuffer));
  memcpy(s_MsgBuffer, message->payload,message->payloadlen);

  DebugMsg(DEBUGMSG_APP,"MQTT MSG[%d]:%s\n", (int)message->payloadlen, s_MsgBuffer);
}
