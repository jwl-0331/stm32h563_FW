/*
 * LED.h
 *
 *  Created on: Jan 29, 2024
 *      Author: mm940
 */

#ifndef BSP_INC_LED_H_
#define BSP_INC_LED_H_

#include "BSPConfig.h"

#define LED_ON      TRUE
#define LED_OFF     FALSE

typedef enum
{
  LED_NOTHING = 0,
  LED1_GREEN = 1,
  LED2_YELLOW = 2,
  LED3_RED = 3
}LED_e;

// Function Declarations
void LED_Init(void);
void LED_Deinit(void);
void LED_Enable(BOOL bEnable);
void LED_OnOff(LED_e eLED, BOOL bOn);
void LED_AllOnOff(BOOL bOn);
void LED_SimpleAnimation(void);

#endif /* BSP_INC_LED_H_ */
