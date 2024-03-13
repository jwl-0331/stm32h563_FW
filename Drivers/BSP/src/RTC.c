/*
 * RTC.c
 *
 *  Created on: Mar 12, 2024
 *      Author: mm940
 */
#include "RTC.h"

RTC_HandleTypeDef hrtc;

uint32_t RTC_ReadBackupReg(uint32_t index)
{
  return HAL_RTCEx_BKUPRead(&hrtc, index);
}

void RTC_WriteBackupReg(uint32_t index, uint32_t data)
{
  HAL_RTCEx_BKUPWrite(&hrtc, index, data);
}
