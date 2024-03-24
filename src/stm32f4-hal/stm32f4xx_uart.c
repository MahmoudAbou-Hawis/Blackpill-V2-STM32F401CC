/******************************************************************************/
/**
 * @file UART.c
 * @brief Implementation of the UART driver for STM32F401CC microcontrollers
 *
 * @par Project Name
 * stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file provides the implementation of functions defined in the `UART.h`
 * header file.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 *
 *******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "stm32f4xx_uart.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/
/**
 * @brief  Defines 'read / write' structure member permissions.
 */
#define __IOM volatile

/**
 * @brief Defines 'read only' structure member permissions.
 */
#define __IM volatile const

#define __STATIC_INLINE static inline

#define PARITY_ENABLE 0x00000200U

#ifndef CLK
#define CLK 16000000
#endif

#define UART_SR_TXE_Pos (7U)
#define UART_SR_TXE_Msk (0x1UL << UART_SR_TXE_Pos)
#define UART_SR_TXE UART_SR_TXE_Msk

#define UART_SR_RXNE_Pos (5U)
#define UART_SR_RXNE_Msk (0x1UL << UART_SR_RXNE_Pos)
#define UART_SR_RXNE UART_SR_RXNE_Msk

#define UART_CR1_TXEIE_Pos (7U)
#define UART_CR1_TXEIE_Msk (0x1UL << UART_CR1_TXEIE_Pos)
#define UART_CR1_TXEIE UART_CR1_TXEIE_Msk

#define UART_CR1_RXNEIE_Pos (5U)
#define UART_CR1_RXNEIE_Msk (0x1UL << UART_CR1_RXNEIE_Pos)
#define UART_CR1_RXNEIE UART_CR1_RXNEIE_Msk

#define UART_CR1_UE_Pos (13U)
#define UART_CR1_UE_Msk (0x1UL << UART_CR1_UE_Pos)
#define UART_CR1_UE UART_CR1_UE_Msk

#define NUMBER_OF_UART 3
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

#define IS_NULL_PTR(_PARAM) (_PARAM == NULL)

#define IS_VALID_OVER_SAMPLING(_PARAM) (_PARAM == UART_OVERSAMPLING_16 || \
                                        _PARAM == UART_OVERSAMPLING_8)

#define IS_VALID_WORD_LENGTH(_PARAM) (_PARAM == UART_WORDLENGTH_8B || \
                                      _PARAM == UART_WORDLENGTH_9B)

#define IS_VALID_STOP_BITS(_PARAM) (_PARAM == UART_STOP_BITS_ONE || \
                                    _PARAM == UART_STOP_BITS_TWO)

#define IS_VALID_PARITY(_PARAM) (_PARAM == UART_PARITY_NONE || \
                                 _PARAM == UART_PARITY_ODD ||  \
                                 _PARAM == UART_PARITY_EVEN)

#define IS_VALID_MODE(_PARAM) (_PARAM == UART_MODE_RX || \
                               _PARAM == UART_MODE_TX || \
                               _PARAM == UART_MODE_TX_RX)

#define IS_VALID_USART_INSTANCE(_PARAM) (_PARAM == USART1 || \
                                         _PARAM == USART2 || \
                                         _PARAM == USART6)

#define IS_NOT_UART_IN_PROCESS(_PARAM) (_PARAM == false)

#define IS_UART_INSTANCE_BUSY(_PARAM)   (_PARAM == true)

#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(2U*((uint64_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U) + 50U) / 100U)

#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))
/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/**
 * @brief Universal Synchronous Asynchronous Receiver Transmitter
 */
typedef struct
{
  __IOM uint32_t SR;   /*!< USART Status registe */
  __IOM uint32_t DR;   /*!< USART Data register */
  __IOM uint32_t BRR;  /*!< USART Baud rate register */
  __IOM uint32_t CR1;  /*!< USART Control register 1 */
  __IOM uint32_t CR2;  /*!< USART Control register 2 */
  __IOM uint32_t CR3;  /*!< USART Control register 3 */
  __IOM uint32_t GTPR; /*!< USART Guard time and prescaler */
} USART_t;

typedef struct
{
  bool isTXProcessRequest;
  bool isRXProcessRequest;
  char * pUartTransmitBuffer;
  uint16_t TransmitBufferSize;
  uint16_t TransmitPos;
  Uart_CallBack TXCallBack;
  Uart_CallBack RXCallBack;
  char * pUartReceiverBuffer;
  uint16_t ReceiverBufferSize;
  uint16_t ReceivePos;
} UartInstanceProperties;
/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
static UartInstanceProperties UartInstancePro[NUMBER_OF_UART] = {0};
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES */
/******************************************************************************/
__STATIC_INLINE UART_ErrorStatus_t UART_WaitingFlagUntilTimeout(USART_t * Instance,
                                               uint32_t Flag, uint32_t Timeout);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/
__STATIC_INLINE UART_ErrorStatus_t UART_WaitingFlagUntilTimeout(USART_t * Instance,
                                                  uint32_t Flag, uint32_t Timeout)
{
  UART_ErrorStatus_t RET_enuErrorStatus = UART_ERROR_NONE;
  while (!(Instance->SR & Flag) && Timeout--);
  if(Timeout == 0)
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  return RET_enuErrorStatus;
}
/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

UART_ErrorStatus_t UART_Init(const UART_Handle_t *const uartHandle)
{
  UART_ErrorStatus_t RET_enuErrorStatus = UART_ERROR_NONE;
  USART_t *UartInstance = ((USART_t *)((uint32_t)uartHandle->pUartInstance &0xFFFFFFF0));
  if (IS_NULL_PTR(uartHandle))
  {
    RET_enuErrorStatus = UART_NULL_PTR_PASSED;
  }
  else if (IS_VALID_USART_INSTANCE(uartHandle->pUartInstance) &&
           IS_VALID_OVER_SAMPLING(uartHandle->UartConfiguration.OverSampling) &&
           IS_VALID_MODE(uartHandle->UartConfiguration.Mode) &&
           IS_VALID_STOP_BITS(uartHandle->UartConfiguration.StopBits) &&
           IS_VALID_WORD_LENGTH(uartHandle->UartConfiguration.WordLength) &&
           IS_VALID_PARITY(uartHandle->UartConfiguration.Parity) && 
           IS_NOT_UART_IN_PROCESS(
                    UartInstancePro[(uint32_t)uartHandle->pUartInstance &0x0000000F].isTXProcessRequest) &&
           IS_NOT_UART_IN_PROCESS(
                    UartInstancePro[(uint32_t)uartHandle->pUartInstance &0x0000000F].isRXProcessRequest))
  {
    UartInstance->CR1 = 0;
    UartInstance->CR2 = 0;
    UartInstance->CR1 |= uartHandle->UartConfiguration.OverSampling;
    UartInstance->CR1 |= uartHandle->UartConfiguration.WordLength;
    UartInstance->CR1 |= uartHandle->UartConfiguration.Parity;
    UartInstance->CR1 |= uartHandle->UartConfiguration.Mode;
    UartInstance->CR2 |= uartHandle->UartConfiguration.StopBits;
    UartInstance->BRR = UART_BRR_SAMPLING8(CLK,uartHandle->UartConfiguration.BaudRate);
    if(uartHandle->UartConfiguration.Parity != UART_PARITY_NONE)
    {
      UartInstance->CR1 |= PARITY_ENABLE;
    }
  }
  else
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  return RET_enuErrorStatus;
}

UART_ErrorStatus_t UART_TransmitTimeOut(UART_Handle_t *uartHandle, char *pData,
                                                   uint16_t Size, uint32_t Timeout)
{
  UART_ErrorStatus_t RET_enuErrorStatus = UART_ERROR_NONE;
  USART_t *UartInstance = ((USART_t *)((uint32_t)uartHandle->pUartInstance &0xFFFFFFF0));
  bool isErrorOccur = false;
  if (IS_NULL_PTR(uartHandle) || IS_NULL_PTR(pData))
  {
    RET_enuErrorStatus = UART_NULL_PTR_PASSED;
  }
  else if(IS_VALID_USART_INSTANCE(uartHandle->pUartInstance))
  {
    UartInstance->CR1 |= UART_CR1_UE;
    for(int Byte = 0 ; Byte < Size && !isErrorOccur ; Byte++)
    {
      UartInstance->DR = pData[Byte];
      RET_enuErrorStatus = UART_WaitingFlagUntilTimeout(UartInstance,UART_SR_TXE,Timeout);
      if(RET_enuErrorStatus == UART_ERROR)
      {
        isErrorOccur = true;
      }
      else
      {
        /**No Thing */
      }
      
    }
    UartInstance->CR1 &= ~UART_CR1_UE;
  }
  else
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  return RET_enuErrorStatus;
}

UART_ErrorStatus_t UART_ReceiveTimeOut(UART_Handle_t *uartHandle, char *pData,
                                              uint16_t Size, uint32_t Timeout)
{
  UART_ErrorStatus_t RET_enuErrorStatus = UART_ERROR_NONE;
  USART_t *UartInstance = ((USART_t *)((uint32_t)uartHandle->pUartInstance &0xFFFFFFF0));
  bool isErrorOccur = false;
  if (IS_NULL_PTR(uartHandle) || IS_NULL_PTR(pData))
  {
    RET_enuErrorStatus = UART_NULL_PTR_PASSED;
  }
  else if(IS_VALID_USART_INSTANCE(uartHandle->pUartInstance))
  {
    UartInstance->CR1 |= UART_CR1_UE;
    for(int Byte = 0 ; Byte < Size && !isErrorOccur ; Byte++)
    {
      RET_enuErrorStatus = UART_WaitingFlagUntilTimeout(UartInstance,UART_SR_RXNE,Timeout);
      pData[Byte] =  UartInstance->DR;
      if(RET_enuErrorStatus == UART_ERROR)
      {
        isErrorOccur = true;
      }
      else
      {
        /**No Thing */
      }
      
    }
    UartInstance->CR1 &= ~UART_CR1_UE;
  }
  else
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  return RET_enuErrorStatus;
}

UART_ErrorStatus_t UART_TransmitAsyncZeroCopy(UART_Handle_t *uartHandle,
                                                     char *pData, uint16_t Size,
                                                     Uart_CallBack CB)
{
  UART_ErrorStatus_t RET_enuErrorStatus = UART_ERROR_NONE;
  USART_t *UartInstance = ((USART_t *)((uint32_t)uartHandle->pUartInstance &0xFFFFFFF0));
  uint8_t UART_PropertiesIdx = (uint32_t)uartHandle->pUartInstance &0x0000000F;
  if (IS_NULL_PTR(uartHandle) || IS_NULL_PTR(pData))
  {
    RET_enuErrorStatus = UART_NULL_PTR_PASSED;
  }
  else if(IS_UART_INSTANCE_BUSY(UartInstancePro[UART_PropertiesIdx].isTXProcessRequest))
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  else if(IS_VALID_USART_INSTANCE(uartHandle->pUartInstance))
  {
    UartInstancePro[UART_PropertiesIdx].isTXProcessRequest  = true;
    UartInstancePro[UART_PropertiesIdx].pUartTransmitBuffer = pData;
    UartInstancePro[UART_PropertiesIdx].TransmitBufferSize = Size;
    UartInstancePro[UART_PropertiesIdx].TransmitPos         = 1;
    UartInstancePro[UART_PropertiesIdx].TXCallBack = CB;
    UartInstance->CR1 |= UART_CR1_TXEIE;
    UartInstance->CR1 |= UART_CR1_UE;
    UartInstance->DR = pData[0];
  }
  else
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  return RET_enuErrorStatus;
}


 UART_ErrorStatus_t UART_ReceiveAsyncZeroCopy(UART_Handle_t *uartHandle,
                                                    char *pData, uint16_t Size, 
                                                    Uart_CallBack CB)
{
  UART_ErrorStatus_t RET_enuErrorStatus = UART_ERROR_NONE;
  USART_t *UartInstance = ((USART_t *)((uint32_t)uartHandle->pUartInstance &0xFFFFFFF0));
  uint8_t UART_PropertiesIdx = (uint32_t)uartHandle->pUartInstance &0x0000000F;
  if (IS_NULL_PTR(uartHandle) || IS_NULL_PTR(pData))
  {
    RET_enuErrorStatus = UART_NULL_PTR_PASSED;
  }
  else if(IS_UART_INSTANCE_BUSY(UartInstancePro[UART_PropertiesIdx].isRXProcessRequest))
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  else if(IS_VALID_USART_INSTANCE(uartHandle->pUartInstance))
  {
    UartInstancePro[UART_PropertiesIdx].isRXProcessRequest   = true;
    UartInstancePro[UART_PropertiesIdx].pUartReceiverBuffer = pData;
    UartInstancePro[UART_PropertiesIdx].ReceiverBufferSize = Size;
    UartInstancePro[UART_PropertiesIdx].ReceivePos         = 0;
    UartInstancePro[UART_PropertiesIdx].RXCallBack = CB;
    UartInstance->CR1 |= UART_CR1_RXNEIE;
    UartInstance->CR1 |= UART_CR1_UE;
  }
  else
  {
    RET_enuErrorStatus = UART_ERROR;
  }
  return RET_enuErrorStatus;
}

void USART1_IRQHandler(void)
{
  if(((USART_t*)USART1)->SR & UART_SR_RXNE)
  {
    UartInstancePro[0].pUartReceiverBuffer[UartInstancePro[0].ReceivePos++] = ((USART_t*)USART1)->DR;
    if(UartInstancePro[0].ReceivePos == UartInstancePro[0].ReceiverBufferSize)
    {
      UartInstancePro[0].isRXProcessRequest = false;
      ((USART_t*)USART1)->CR1 &= ~UART_CR1_RXNEIE;
      if(UartInstancePro[0].isTXProcessRequest != true)
      {
        ((USART_t*)USART1)->CR1 &= ~UART_CR1_UE;
      }
      if(IS_NULL_PTR(UartInstancePro[0].RXCallBack))
      {

      }
      else
      {
        UartInstancePro[0].RXCallBack();
      }
    }
  }

  if(((USART_t*)USART1)->SR & UART_SR_TXE_Msk)
  {
    if(UartInstancePro[0].TransmitPos < UartInstancePro[0].TransmitBufferSize)
    {
      ((USART_t*)USART1)->DR = UartInstancePro[0].pUartTransmitBuffer[UartInstancePro[0].TransmitPos++];
    }
    else
    {
      if(UartInstancePro[0].isTXProcessRequest == true)
      {
        UartInstancePro[0].isTXProcessRequest = false;
        ((USART_t*)USART1)->CR1 &= ~UART_CR1_TXEIE;
        if(UartInstancePro[0].isRXProcessRequest != true)
        {
         ((USART_t*)USART1)->CR1 &= ~UART_CR1_UE;
        }
        if(IS_NULL_PTR(UartInstancePro[0].TXCallBack))
        {

        }
        else
        {
          UartInstancePro[0].TXCallBack();
        }
      }
    }
  }
}


/******************************************************************************/