/*
 * CAN.c
 *
 *  Created on: Mar 13, 2024
 *      Author: mm940
 */
#include "CAN.h"
#include "svCLI.h"
#include "svDebug.h"
#include "qbuffer.h"

typedef struct
{
  uint32_t prescaler;
  uint32_t sjw;
  uint32_t tseg1;
  uint32_t tseg2;
} CAN_BAUD_CFG_t;

const CAN_BAUD_CFG_t can_baud_cfg_80m_normal[] =
    {
        {50, 8, 13, 2}, // 100K, 87.5%
        {40, 8, 13, 2}, // 125K, 87.5%
        {20, 8, 13, 2}, // 250K, 87.5%
        {10, 8, 13, 2}, // 500K, 87.5%
        {5,  8, 13, 2}, // 1M,   87.5%
    };

const CAN_BAUD_CFG_t can_baud_cfg_80m_data[] =
    {
        {40, 8, 11, 8}, // 100K, 60%
        {32, 8, 11, 8}, // 125K, 60%
        {16, 8, 11, 8}, // 250K, 60%
        {8,  8, 11, 8}, // 500K, 60%
        {4,  8, 11, 8}, // 1M,   60%
        {2,  8, 11, 8}, // 2M    60%
        {1,  8, 11, 8}, // 4M    60%
        {1,  8,  9, 6}, // 5M    62.5%
    };

const CAN_BAUD_CFG_t *p_baud_normal = can_baud_cfg_80m_normal;
const CAN_BAUD_CFG_t *p_baud_data   = can_baud_cfg_80m_data;

const uint32_t dlc_len_tbl[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64};

const uint32_t dlc_tbl[] =
    {
        FDCAN_DLC_BYTES_0,
        FDCAN_DLC_BYTES_1,
        FDCAN_DLC_BYTES_2,
        FDCAN_DLC_BYTES_3,
        FDCAN_DLC_BYTES_4,
        FDCAN_DLC_BYTES_5,
        FDCAN_DLC_BYTES_6,
        FDCAN_DLC_BYTES_7,
        FDCAN_DLC_BYTES_8,
        FDCAN_DLC_BYTES_12,
        FDCAN_DLC_BYTES_16,
        FDCAN_DLC_BYTES_20,
        FDCAN_DLC_BYTES_24,
        FDCAN_DLC_BYTES_32,
        FDCAN_DLC_BYTES_48,
        FDCAN_DLC_BYTES_64
    };

static const uint32_t frame_tbl[] =
    {
        FDCAN_FRAME_CLASSIC,
        FDCAN_FRAME_FD_NO_BRS,
        FDCAN_FRAME_FD_BRS
    };

static const uint32_t mode_tbl[] =
    {
        FDCAN_MODE_NORMAL,
        FDCAN_MODE_BUS_MONITORING,
        FDCAN_MODE_INTERNAL_LOOPBACK
    };


typedef struct
{
  BOOL is_init;
  BOOL is_open;

  uint32_t err_code;
  uint8_t  state;
  uint32_t recovery_cnt;

  uint32_t q_rx_full_cnt;
  uint32_t q_tx_full_cnt;
  uint32_t fifo_full_cnt;
  uint32_t fifo_lost_cnt;

  /* Setting */
  uint32_t fifo_idx;
  uint32_t enable_int;
  CAN_MODE_t  mode;
  CAN_FRAME_t frame;
  CAN_BAUD_t  baud;
  CAN_BAUD_t  baud_data;

  FDCAN_HandleTypeDef  hfdcan;
  BOOL (*handler)(CAN_MSG_t *arg);

  qbuffer_t q_msg;
  CAN_MSG_t can_msg[CAN_MSG_RX_BUF_MAX];
} CAN_TBL_t;

static CAN_TBL_t can_tbl[CAN_MAX_CH];

static volatile uint32_t err_int_cnt = 0;

static void CAN_ErrUpdate(uint8_t ch);

BOOL     CAN_Init(void)
{
  BOOL ret = TRUE;

  for(int i=0; i<CAN_MAX_CH; i++)
  {
    can_tbl[i].is_init = TRUE;
    can_tbl[i].is_open = TRUE;
    can_tbl[i].err_code = CAN_ERR_NONE;
    can_tbl[i].state = 0;
    can_tbl[i].recovery_cnt = 0;

    can_tbl[i].q_rx_full_cnt = 0;
    can_tbl[i].q_tx_full_cnt = 0;
    can_tbl[i].fifo_full_cnt = 0;
    can_tbl[i].fifo_lost_cnt = 0;

    qbufferCreateBySize(&can_tbl[i].q_msg, (uint8_t *)&can_tbl[i].can_msg[0], sizeof(CAN_MSG_t), CAN_MSG_RX_BUF_MAX);

  }
  return ret;
}

BOOL     CAN_Open(uint8_t ch, CAN_MODE_t mode, CAN_FRAME_t frame, CAN_BAUD_t baud, CAN_BAUD_t baud_data)
{
  BOOL ret = TRUE;
  FDCAN_HandleTypeDef  *p_can;
  uint32_t tdc_offset;

  p_can = &can_tbl[ch].hfdcan;
  if(ch >= CAN_MAX_CH) return FALSE;

  switch(ch)
  {
    case _DEF_CAN1:
      p_can->Instance = FDCAN1;
      p_can->Init.ClockDivider = FDCAN_CLOCK_DIV1;
      p_can->Init.FrameFormat = frame_tbl[frame];
      p_can->Init.Mode = mode_tbl[mode];
      p_can->Init.AutoRetransmission = ENABLE;
      p_can->Init.TransmitPause = ENABLE;
      p_can->Init.ProtocolException = ENABLE;
      p_can->Init.NominalPrescaler = p_baud_normal[baud].prescaler;
      p_can->Init.NominalSyncJumpWidth = p_baud_normal[baud].sjw;
      p_can->Init.NominalTimeSeg1 = p_baud_normal[baud].tseg1;
      p_can->Init.NominalTimeSeg2 = p_baud_normal[baud].tseg2;
      p_can->Init.DataPrescaler = p_baud_data[baud_data].prescaler;
      p_can->Init.DataSyncJumpWidth = p_baud_data[baud_data].sjw;
      p_can->Init.DataTimeSeg1 = p_baud_data[baud_data].tseg1;
      p_can->Init.DataTimeSeg2 = p_baud_data[baud_data].tseg2;
      p_can->Init.StdFiltersNbr = 28;
      p_can->Init.ExtFiltersNbr = 8;
      p_can->Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION; //FIFO MODE
      can_tbl[ch].mode                  = mode;
      can_tbl[ch].frame                 = frame;
      can_tbl[ch].baud                  = baud;
      can_tbl[ch].baud_data             = baud_data;
      can_tbl[ch].fifo_idx              = FDCAN_RX_FIFO0;
      can_tbl[ch].enable_int            = FDCAN_IT_LIST_RX_FIFO0 |
                                          FDCAN_IT_BUS_OFF |
                                          FDCAN_IT_ERROR_WARNING |
                                          FDCAN_IT_ERROR_PASSIVE;

      ret = TRUE;

      break;
  }

  if(ret != TRUE)
  {
    return FALSE;
  }
  if (HAL_FDCAN_Init(p_can) != HAL_OK)
  {
    return FALSE;
  }

  CAN_ConfigFilter(ch, 0, CAN_STD, 0x0000, 0x0000);
  CAN_ConfigFilter(ch, 0, CAN_EXT, 0x0000, 0x0000);

  if (HAL_FDCAN_ConfigGlobalFilter(p_can, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
  {
    return FALSE;
  }
  if (HAL_FDCAN_ActivateNotification(p_can, can_tbl[ch].enable_int, 0) != HAL_OK)
  {
    return FALSE;
  }


  tdc_offset = p_can->Init.DataPrescaler * p_can->Init.DataTimeSeg1;

  if (HAL_FDCAN_ConfigTxDelayCompensation(p_can, tdc_offset, 0) != HAL_OK) return FALSE;
  if (HAL_FDCAN_EnableTxDelayCompensation(p_can) != HAL_OK)                return FALSE;

  if (HAL_FDCAN_Start(p_can) != HAL_OK)
  {
    return FALSE;
  }

  can_tbl[ch].is_open = TRUE;

  return ret;
}
void     CAN_Close(uint8_t ch)
{

}
BOOL     CAN_ConfigFilter(uint8_t ch, uint8_t index, CAN_ID_TYPE_t id_type, uint32_t id, uint32_t id_mask)
{
  BOOL ret = FALSE;

  FDCAN_FilterTypeDef sFilterConfig;

  if (ch >= CAN_MAX_CH) return FALSE;


  if (id_type == CAN_STD)
  {
    sFilterConfig.IdType = FDCAN_STANDARD_ID;
  }
  else
  {
    sFilterConfig.IdType = FDCAN_EXTENDED_ID;
  }

  if (can_tbl[ch].fifo_idx == FDCAN_RX_FIFO0)
  {
    sFilterConfig.FilterConfig  = FDCAN_FILTER_TO_RXFIFO0;
  }
  else
  {
    sFilterConfig.FilterConfig  = FDCAN_FILTER_TO_RXFIFO1;
  }

  sFilterConfig.FilterIndex   = index;
  sFilterConfig.FilterType    = FDCAN_FILTER_MASK; //Classic filter
  sFilterConfig.FilterID1     = id;
  sFilterConfig.FilterID2     = id_mask;


  if (HAL_FDCAN_ConfigFilter(&can_tbl[ch].hfdcan, &sFilterConfig) == HAL_OK)
  {
    ret = TRUE;
  }

  return ret;
}

uint32_t CAN_MsgAvailable(uint8_t ch)
{
  if(ch > CAN_MAX_CH) return 0;

  return qbufferAvailable(&can_tbl[ch].q_msg);
}

BOOL     CAN_MsgInit(CAN_MSG_t *p_msg, CAN_FRAME_t frame, CAN_ID_TYPE_t  id_type, CAN_DLC_t dlc)
{
  p_msg->frame   = frame;
  p_msg->id_type = id_type;
  p_msg->dlc     = dlc;
  p_msg->length  = dlc_len_tbl[dlc];
  return TRUE;
}

BOOL     CAN_MsgWrite(uint8_t ch, CAN_MSG_t *p_msg, uint32_t timeout)
{
  {
    FDCAN_HandleTypeDef  *p_can;
    FDCAN_TxHeaderTypeDef tx_header;
    uint32_t pre_time;
    BOOL ret = TRUE;


    if(ch > CAN_MAX_CH) return FALSE;

    if (can_tbl[ch].err_code & CAN_ERR_BUS_OFF) return FALSE;


    p_can = &can_tbl[ch].hfdcan;

    switch(p_msg->id_type)
    {
      case CAN_STD :
        tx_header.IdType = FDCAN_STANDARD_ID;
        break;

      case CAN_EXT :
        tx_header.IdType = FDCAN_EXTENDED_ID;
        break;
    }

    switch(p_msg->frame)
    {
      case CAN_CLASSIC:
        tx_header.FDFormat      = FDCAN_CLASSIC_CAN;
        tx_header.BitRateSwitch = FDCAN_BRS_OFF;
        break;

      case CAN_FD_NO_BRS:
        tx_header.FDFormat      = FDCAN_FD_CAN;
        tx_header.BitRateSwitch = FDCAN_BRS_OFF;
        break;

      case CAN_FD_BRS:
        tx_header.FDFormat      = FDCAN_FD_CAN;
        tx_header.BitRateSwitch = FDCAN_BRS_ON;
        break;
    }

    tx_header.Identifier          = p_msg->id;
    tx_header.MessageMarker       = 0;
    tx_header.TxEventFifoControl  = FDCAN_NO_TX_EVENTS;
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.TxFrameType         = FDCAN_DATA_FRAME;
    tx_header.DataLength          = dlc_tbl[p_msg->dlc];


    if (HAL_FDCAN_GetTxFifoFreeLevel(p_can) == 0)
    {
      return FALSE;
    }


    pre_time = HAL_GetTick();
    if(HAL_FDCAN_AddMessageToTxFifoQ(p_can, &tx_header, p_msg->data) == HAL_OK)
    {
      /* Wait transmission complete */
      while(HAL_FDCAN_GetTxFifoFreeLevel(p_can) == 0)
      {
        if (HAL_GetTick()-pre_time >= timeout)
        {
          ret = FALSE;
          break;
        }
      }
    }
    else
    {
      ret = FALSE;
    }

    return ret;
  }
}
BOOL     CAN_MsgRead(uint8_t ch, CAN_MSG_t *p_msg)
{
  BOOL ret = TRUE;

  if(ch > CAN_MAX_CH) return 0;

  ret = qbufferRead(&can_tbl[ch].q_msg, (uint8_t *)p_msg, 1);

  return ret;
}

uint16_t CAN_GetRxErrCount(uint8_t ch)
{
  uint16_t ret = 0;
  HAL_StatusTypeDef status;
  FDCAN_ErrorCountersTypeDef error_counters;

  if(ch > CAN_MAX_CH) return 0;

  status = HAL_FDCAN_GetErrorCounters(&can_tbl[ch].hfdcan, &error_counters);
  if (status == HAL_OK)
  {
    ret = error_counters.RxErrorCnt;
  }

  return ret;
}
uint16_t CAN_GetTxErrCount(uint8_t ch)
{
  uint16_t ret = 0;
  HAL_StatusTypeDef status;
  FDCAN_ErrorCountersTypeDef error_counters;

  if(ch > CAN_MAX_CH) return 0;

  status = HAL_FDCAN_GetErrorCounters(&can_tbl[ch].hfdcan, &error_counters);
  if (status == HAL_OK)
  {
    ret = error_counters.TxErrorCnt;
  }

  return ret;
}

uint32_t CAN_GetError(uint8_t ch)
{
  if(ch > CAN_MAX_CH) return 0;

  return HAL_FDCAN_GetError(&can_tbl[ch].hfdcan);
}

uint32_t CAN_GetState(uint8_t ch)
{
  if(ch > CAN_MAX_CH) return 0;

  return HAL_FDCAN_GetState(&can_tbl[ch].hfdcan);
}


void CAN_RxFifoCallback(uint8_t ch, FDCAN_HandleTypeDef *hfdcan)
{
  CAN_MSG_t *rx_buf;
  FDCAN_RxHeaderTypeDef rx_header;


  rx_buf  = (CAN_MSG_t *)qbufferPeekWrite(&can_tbl[ch].q_msg);

  if (HAL_FDCAN_GetRxMessage(hfdcan, can_tbl[ch].fifo_idx, &rx_header, rx_buf->data) == HAL_OK)
  {
    if(rx_header.IdType == FDCAN_STANDARD_ID)
    {
      rx_buf->id      = rx_header.Identifier;
      rx_buf->id_type = CAN_STD;
    }
    else
    {
      rx_buf->id      = rx_header.Identifier;
      rx_buf->id_type = CAN_EXT;
    }
    rx_buf->length = dlc_len_tbl[(rx_header.DataLength >> 16) & 0x0F];


    if (rx_header.FDFormat == FDCAN_FD_CAN)
    {
      if (rx_header.BitRateSwitch == FDCAN_BRS_ON)
      {
        rx_buf->frame = CAN_FD_BRS;
      }
      else
      {
        rx_buf->frame = CAN_FD_NO_BRS;
      }
    }
    else
    {
      rx_buf->frame = CAN_CLASSIC;
    }

    if (qbufferWrite(&can_tbl[ch].q_msg, NULL, 1) != TRUE)
    {
      can_tbl[ch].q_rx_full_cnt++;
    }

    if( can_tbl[ch].handler != NULL )
    {
      if ((*can_tbl[ch].handler)((void *)rx_buf) == TRUE)
      {
        qbufferRead(&can_tbl[ch].q_msg, NULL, 1);
      }
    }
  }
}

void CAN_AttachRxInterrupt(uint8_t ch, BOOL (*handler)(CAN_MSG_t *arg))
{
  if(ch > CAN_MAX_CH) return;

  can_tbl[ch].handler = handler;
}

void CAN_DetachRxInterrupt(uint8_t ch)
{
  if(ch > CAN_MAX_CH) return;

  can_tbl[ch].handler = NULL;
}

void CAN_Recovery(uint8_t ch)
{
  if(ch > CAN_MAX_CH) return;

  HAL_FDCAN_Stop(&can_tbl[ch].hfdcan);
  HAL_FDCAN_Start(&can_tbl[ch].hfdcan);

  can_tbl[ch].recovery_cnt++;
}

BOOL     CAN_Update(void)
{
  BOOL ret = FALSE;
  CAN_TBL_t *p_can;

  for (int i=0; i<CAN_MAX_CH; i++)
  {
    p_can = &can_tbl[i];


    switch(p_can->state)
    {
      case 0:
        if (p_can->err_code & CAN_ERR_BUS_OFF)
        {
          canRecovery(i);
          p_can->state = 1;
          ret = TRUE;
        }
        break;

      case 1:
        if ((p_can->err_code & CAN_ERR_BUS_OFF) == 0)
        {
          p_can->state = 0;
        }
        break;
    }
  }

  return ret;
}

void     CAN_ErrClear(uint8_t ch)
{
  if(ch > CAN_MAX_CH) return;

  can_tbl[ch].err_code = CAN_ERR_NONE;
}

void     CAN_ErrPrint(uint8_t ch)
{
  uint32_t err_code;


  if(ch > CAN_MAX_CH) return;

  err_code = can_tbl[ch].err_code;

  if (err_code & CAN_ERR_PASSIVE) UART_Printf("  ERR : CAN_ERR_PASSIVE\n");
  if (err_code & CAN_ERR_WARNING) UART_Printf("  ERR : CAN_ERR_WARNING\n");
  if (err_code & CAN_ERR_BUS_OFF) UART_Printf("  ERR : CAN_ERR_BUS_OFF\n");
}

void CAN_ErrUpdate(uint8_t ch)
{
  FDCAN_ProtocolStatusTypeDef protocol_status;

  HAL_FDCAN_GetProtocolStatus(&can_tbl[ch].hfdcan, &protocol_status);

  if (protocol_status.ErrorPassive)
  {
    can_tbl[ch].err_code |= CAN_ERR_PASSIVE;
  }
  else
  {
    can_tbl[ch].err_code &= ~CAN_ERR_PASSIVE;
  }

  if (protocol_status.Warning)
  {
    can_tbl[ch].err_code |= CAN_ERR_WARNING;
  }
  else
  {
    can_tbl[ch].err_code &= ~CAN_ERR_WARNING;
  }

  if (protocol_status.BusOff)
  {
    can_tbl[ch].err_code |= CAN_ERR_BUS_OFF;
  }
  else
  {
    can_tbl[ch].err_code &= ~CAN_ERR_BUS_OFF;
  }
}

void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs)
{
  uint8_t ch = _DEF_CAN1;

  CAN_ErrUpdate(ch);
}
void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan)
{
  uint8_t ch = _DEF_CAN1;

  err_int_cnt++;

  if (hfdcan->ErrorCode > 0)
  {
    can_tbl[ch].err_code |= CAN_ERR_ETC;
  }
}

void FDCAN1_IT0_IRQHandler(void)
{
  HAL_FDCAN_IRQHandler(&can_tbl[_DEF_CAN1].hfdcan);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
    CAN_RxFifoCallback(_DEF_CAN1, hfdcan);
  }

  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_FULL) != RESET)
  {
    can_tbl[_DEF_CAN1].fifo_full_cnt++;
  }

  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_MESSAGE_LOST) != RESET)
  {
    can_tbl[_DEF_CAN1].fifo_lost_cnt++;
  }
}

void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef* hfdcan)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hfdcan->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspInit 0 */

  /* USER CODE END FDCAN1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
    PeriphClkInitStruct.FdcanClockSelection = RCC_FDCANCLKSOURCE_HSE;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_FDCAN_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_FDCAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* FDCAN1 interrupt Init */
    HAL_NVIC_SetPriority(FDCAN1_IT0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspInit 1 */

  /* USER CODE END FDCAN1_MspInit 1 */
  }

}

void HAL_FDCAN_MspDeInit(FDCAN_HandleTypeDef* hfdcan)
{
  if(hfdcan->Instance==FDCAN1)
  {
  /* USER CODE BEGIN FDCAN1_MspDeInit 0 */

  /* USER CODE END FDCAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_FDCAN_CLK_DISABLE();

    /**FDCAN1 GPIO Configuration
    PA11     ------> FDCAN1_RX
    PA12     ------> FDCAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* FDCAN1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(FDCAN1_IT0_IRQn);
  /* USER CODE BEGIN FDCAN1_MspDeInit 1 */

  /* USER CODE END FDCAN1_MspDeInit 1 */
  }

}

#ifdef USE_CLI_FUNCTIONS
SVCLI_TABLE_ENTRY (CAN_TEST, "CAN", "CAN [1(INFO),2(READ),3(SEND)] [0x0800 F000 ~ address]", CLI_FDCANTest)
static void CLI_FDCANTest(char *pArgLine, unsigned int nCount, unsigned int nFirst, unsigned int nAddress)
{
  BOOL ret = FALSE;

  if (nCount == 2)
  {
    switch(nFirst)
    {
      case 1:
        for (int i=0; i<CAN_MAX_CH; i++)
        {
          DebugMsg(DEBUGMSG_CLI,"is_open       : %d\n", can_tbl[i].is_open);
          DebugMsg(DEBUGMSG_CLI,"q_rx_full_cnt : %d\n", can_tbl[i].q_rx_full_cnt);
          DebugMsg(DEBUGMSG_CLI,"q_tx_full_cnt : %d\n", can_tbl[i].q_tx_full_cnt);
          DebugMsg(DEBUGMSG_CLI,"fifo_full_cnt : %d\n", can_tbl[i].fifo_full_cnt);
          DebugMsg(DEBUGMSG_CLI,"fifo_lost_cnt : %d\n", can_tbl[i].fifo_lost_cnt);
          //DebugMsg(DEBUGMSG_CLI,i);
        }
        ret = TRUE;
        break;
      case 2:
        uint32_t index = 0;
        while(1)
        {
          if (CAN_MsgAvailable(_DEF_CAN1))
          {
            CAN_MSG_t msg;

            CAN_MsgRead(_DEF_CAN1, &msg);

            index %= 1000;
            DebugMsg(DEBUGMSG_CLI,"%03d(R) <- id ", index++);
            if (msg.id_type == CAN_STD)
            {
              DebugMsg(DEBUGMSG_CLI,"std ");
            }
            else
            {
              DebugMsg(DEBUGMSG_CLI,"ext ");
            }
            DebugMsg(DEBUGMSG_CLI,": 0x%08X, L:%02d, ", msg.id, msg.length);
            for (int i=0; i<msg.length; i++)
            {
              DebugMsg(DEBUGMSG_CLI,"0x%02X ", msg.data[i]);
            }
            DebugMsg(DEBUGMSG_CLI,"\n");
          }
        }
    }
  }
}
#endif
