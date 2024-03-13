/*
 * CAN.h
 *
 *  Created on: Mar 13, 2024
 *      Author: mm940
 */

#ifndef BSP_INC_CAN_H_
#define BSP_INC_CAN_H_

#include "BSPConfig.h"

#define CAN_MAX_CH          1
#define CAN_MSG_RX_BUF_MAX  16
#define _DEF_CAN1           0
typedef enum
{
  CAN_100K,
  CAN_125K,
  CAN_250K,
  CAN_500K,
  CAN_1M,
  CAN_2M,
  CAN_4M,
  CAN_5M
} CAN_BAUD_t;

typedef enum
{
  CAN_NORMAL,
  CAN_MONITOR,
  CAN_LOOPBACK
}CAN_MODE_t;

typedef enum
{
  CAN_CLASSIC,
  CAN_FD_NO_BRS,
  CAN_FD_BRS
} CAN_FRAME_t;

typedef enum
{
  CAN_STD,
  CAN_EXT
} CAN_ID_TYPE_t;

typedef enum
{
  CAN_DLC_0,
  CAN_DLC_1,
  CAN_DLC_2,
  CAN_DLC_3,
  CAN_DLC_4,
  CAN_DLC_5,
  CAN_DLC_6,
  CAN_DLC_7,
  CAN_DLC_8,
  CAN_DLC_12,
  CAN_DLC_16,
  CAN_DLC_20,
  CAN_DLC_24,
  CAN_DLC_32,
  CAN_DLC_48,
  CAN_DLC_64
} CAN_DLC_t;

typedef enum
{
  CAN_ERR_NONE      = 0x00000000,
  CAN_ERR_PASSIVE   = 0x00000001,
  CAN_ERR_WARNING   = 0x00000002,
  CAN_ERR_BUS_OFF   = 0x00000004,
  CAN_ERR_BUS_FAULT = 0x00000008,
  CAN_ERR_ETC       = 0x00000010,
} CAN_ERR_t;


typedef struct
{
  uint32_t id;
  uint16_t length;
  uint8_t  data[64];

  CAN_DLC_t      dlc;
  CAN_ID_TYPE_t  id_type;
  CAN_FRAME_t    frame;
} CAN_MSG_t;





BOOL     CAN_Init(void);
BOOL     CAN_Open(uint8_t ch, CAN_MODE_t mode, CAN_FRAME_t frame, CAN_BAUD_t baud, CAN_BAUD_t baud_data);
void     CAN_Close(uint8_t ch);
BOOL     CAN_ConfigFilter(uint8_t ch, uint8_t index, CAN_ID_TYPE_t id_type, uint32_t id, uint32_t id_mask);

BOOL     CAN_MsgInit(CAN_MSG_t *p_msg, CAN_FRAME_t frame, CAN_ID_TYPE_t  id_type, CAN_DLC_t dlc);
uint32_t CAN_MsgAvailable(uint8_t ch);
BOOL     CAN_MsgWrite(uint8_t ch, CAN_MSG_t *p_msg, uint32_t timeout);
BOOL     CAN_MsgRead(uint8_t ch, CAN_MSG_t *p_msg);

uint16_t CAN_GetRxErrCount(uint8_t ch);
uint16_t CAN_GetTxErrCount(uint8_t ch);
uint32_t CAN_GetError(uint8_t ch);
uint32_t CAN_GetState(uint8_t ch);

void     CAN_ErrClear(uint8_t ch);
void     CAN_ErrPrint(uint8_t ch);
BOOL     CAN_Update(void);

void     CAN_AttachRxInterrupt(uint8_t ch, BOOL (*handler)(CAN_MSG_t *arg));
void     CAN_DetachRxInterrupt(uint8_t ch);


#endif /* BSP_INC_CAN_H_ */
