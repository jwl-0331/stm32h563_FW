/*
 * RTC.h
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */

#ifndef BSP_INC_RTC_H_
#define BSP_INC_RTC_H_

#include "BSPConfig.h"

uint32_t RTC_ReadBackupReg(uint32_t index);
void     RTC_WriteBackupReg(uint32_t index, uint32_t data);

#endif /* BSP_INC_RTC_H_ */
