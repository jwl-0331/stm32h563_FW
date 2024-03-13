/*
 * RESET.h
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */

#ifndef BSP_INC_RESET_H_
#define BSP_INC_RESET_H_

#include "BSPConfig.h"

#define RESET_REG_PARAM   0
#define RESET_REG_COUNT   1
#define RESET_REG_MAGICNUMBER   0x20240215

BOOL RESET_Init(void);

uint32_t RESET_GetCount(void);
void RESET_ToBoot(uint32_t timeout);
void RESET_ToSystemBoot(void);

#endif /* BSP_INC_RESET_H_ */
