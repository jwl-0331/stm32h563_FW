/*
 * LED.c
 *
 *  Created on: Jan 29, 2024
 *      Author: jwLee
 */

#include "BSPConfig.h"
#include "main.h"
#include "LED.h"
#include "svCLI.h"
#include "svDebug.h"

// Static Variables
static BOOL s_bLEDInit = FALSE;
static BOOL s_bLEDEnable = FALSE;

// Function Declarations
void LED_Init(void)
{
  s_bLEDInit = TRUE;
  s_bLEDEnable = TRUE;
}

void LED_Deinit(void)
{
  s_bLEDInit = FALSE;
}

void LED_Enable(BOOL bEnable)
{
  s_bLEDEnable = bEnable;
}

void LED_OnOff(LED_e eLED, BOOL bOn)
{
  if(FALSE == s_bLEDEnable)
  {
    return;
  }

  GPIO_TypeDef* LED_GPIO_Port;
  uint16_t LED_GPIO_Pin;
  if(s_bLEDInit)
  {
    switch(eLED){
      case LED1_GREEN:
        LED_GPIO_Port = LED1_GREEN_GPIO_Port;
        LED_GPIO_Pin = LED1_GREEN_Pin;
        break;
      case LED2_YELLOW:
        LED_GPIO_Port = LED2_YELLOW_GPIO_Port;
        LED_GPIO_Pin = LED2_YELLOW_Pin;
        break;
      case LED3_RED:
        LED_GPIO_Port = LED3_RED_GPIO_Port;
        LED_GPIO_Pin = LED3_RED_Pin;
        break;
      default:
        return;
        break;
    }
    if(bOn)
    {
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_GPIO_Pin, GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(LED_GPIO_Port, LED_GPIO_Pin, GPIO_PIN_RESET);
    }
  }
}

void LED_AllOnOff(BOOL bOn)
{
  if(FALSE == s_bLEDEnable)
  {
    return;
  }
  LED_OnOff(LED1_GREEN, bOn);
  LED_OnOff(LED2_YELLOW, bOn);
  LED_OnOff(LED3_RED, bOn);
}

void LED_SimpleAnimation(void)
{
  for(int i =0; i<3; i++)
  {
    LED_OnOff(LED1_GREEN, TRUE);
    HAL_Delay(50);
    LED_OnOff(LED1_GREEN, FALSE);
    HAL_Delay(50);
    LED_OnOff(LED2_YELLOW, TRUE);
    HAL_Delay(50);
    LED_OnOff(LED2_YELLOW, FALSE);
    HAL_Delay(50);
    LED_OnOff(LED3_RED, TRUE);
    HAL_Delay(50);
    LED_OnOff(LED3_RED, FALSE);
    HAL_Delay(50);
  }
}
#ifdef USE_CLI_FUNCTIONS
SVCLI_TABLE_ENTRY (LED_TEST,"LED","LED [1~11] [0,1,2] ",CLI_LEDTest);

static void CLI_LEDTest(char* pArgLine, unsigned int nCount, unsigned int nFirst, unsigned int nSecond)
{
  if (nCount == 2) {
    LED_OnOff((LED_e)nFirst, (BOOL)(nSecond != 0));
  }
}
#endif // USE_CLI_FUNCTIONS
