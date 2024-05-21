/******************************************************************************/
/**
 * @file stm32f401cc_spi.c
 * @brief STM32F401CC SPI Driver Implementation
 *
 * @par Project Name
 *  stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file implements the SPI driver functions for STM32F401CC microcontrollers.
 * It provides functions to configure and interact with the SPI peripheral.
 *
 * @par Dependencies
 * - stm32f401cc_spi.h (header file for this driver)
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "stm32f4xx_spi.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

#define SPI_CR1_RESET       (0U)         /*!< SPI CR1 register reset value */
#define SPI_CRCPR_RESET     (0x0007U)    /*!< SPI CRC polynomial register reset value */        


#define TX_BUFFER_EMPTY     (SPI_SR_TXE)
#define RX_BUFFER_NOT_EMPTY (SPI_SR_RXNE_Msk)
#define SPI_IS_BUSY         (SPI_SR_BSY)



#define SPI_CR1_SPE_Pos     (6U)
#define SPI_CR1_SPE_Msk     (0x1UL << SPI_CR1_SPE_Pos)
#define SPI_CR1_SPE         SPI_CR1_SPE_Msk


#define SPI_SR_TXE_Pos      (1U)
#define SPI_SR_TXE_Msk      (0x1UL << SPI_SR_TXE_Pos)
#define SPI_SR_TXE          SPI_SR_TXE_Msk



#define SPI_CR1_CRCNEXT_Pos (12U)
#define SPI_CR1_CRCNEXT_Msk (0x1UL << SPI_CR1_CRCNEXT_Pos)
#define SPI_CR_CRCNEXT      SPI_CR1_CRCNEXT_Msk


#define SPI_SR_BSY_Pos      (7U)
#define SPI_SR_BSY_Msk      (0x1UL << SPI_SR_BSY_Pos)
#define SPI_SR_BSY          SPI_SR_BSY_Msk


#define SPI_SR_RXNE_Pos     (0U)
#define SPI_SR_RXNE_Msk     (0x1UL << SPI_SR_RXNE_Pos)
#define SPI_SR_RXNE         SPI_SR_RXNE_Msk

#define SPI_CR2_TXEIE_Pos    (7U)
#define SPI_CR2_TXEIE_Msk    (0x1UL << SPI_CR2_TXEIE_Pos)
#define SPI_CR2_TXEIE        SPI_CR2_TXEIE_Msk

#define SPI_CR2_RXNEIE_Pos    (6U)
#define SPI_CR2_RXNEIE_Msk    (0x1UL << SPI_CR2_RXNEIE_Pos)
#define SPI_CR2_RXNEIE        SPI_CR2_RXNEIE_Msk


#define SPI_CR1_SSM_Pos       (9U)                                       
#define SPI_CR1_SSM_Msk       (0x1UL << SPI_CR1_SSM_Pos)                  /*!< 0x00000200 */
#define SPI_CR1_SSM           SPI_CR1_SSM_Msk                            /*!<Software slave management  */

#define SPI_CR1_SSI_Pos       (8U)                                       
#define SPI_CR1_SSI_Msk       (0x1UL << SPI_CR1_SSI_Pos)                  /*!< 0x00000100 */
#define SPI_CR1_SSI           SPI_CR1_SSI_Msk                            /*!<Internal slave select    */

#define NUMBER_OF_SPI      (3U)
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

/** 
  * @brief  Check if a given instance is a valid SPI instance.
  * @param  INSTANCE: pointer to the instance to check.
  * @retval 1 if the instance is a valid SPI instance, otherwise 0.
  */
#define IS_SPI_INSTANCE(INSTANCE) ((INSTANCE == SPI1) || \
                                   (INSTANCE == SPI2) || \
                                   (INSTANCE == SPI3) || \
                                   (INSTANCE == SPI4))


/**
  * @brief  Check if a given mode is a valid SPI mode.
  * @param  MODE: the mode to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_MODE_MASTER: SPI Master mode
  *            @arg SPI_MODE_SLAVE: SPI Slave mode
  * @retval 1 if the mode is a valid SPI mode, otherwise 0.
  */
#define IS_SPI_MODE(MODE) (((MODE) == SPI_MODE_MASTER) || ((MODE) == SPI_MODE_SLAVE))


/**
  * @brief  Check if a given SPI baud rate prescaler is valid.
  * @param  PRESCALER: the baud rate prescaler to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_BAUDRATEPRESCALER_2: SPI baud rate prescaler: 2
  *            @arg SPI_BAUDRATEPRESCALER_4: SPI baud rate prescaler: 4
  *            @arg SPI_BAUDRATEPRESCALER_8: SPI baud rate prescaler: 8
  *            @arg SPI_BAUDRATEPRESCALER_16: SPI baud rate prescaler: 16
  *            @arg SPI_BAUDRATEPRESCALER_32: SPI baud rate prescaler: 32
  *            @arg SPI_BAUDRATEPRESCALER_64: SPI baud rate prescaler: 64
  *            @arg SPI_BAUDRATEPRESCALER_128: SPI baud rate prescaler: 128
  *            @arg SPI_BAUDRATEPRESCALER_256: SPI baud rate prescaler: 256
  * @retval 1 if the baud rate prescaler is valid, otherwise 0.
  */
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BAUDRATEPRESCALER_2) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_4) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_8) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_16) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_32) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_64) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_128) || \
                                               ((PRESCALER) == SPI_BAUDRATEPRESCALER_256))


/**
  * @brief  Check if a given SPI byte order is valid.
  * @param  BYTE_ORDER: the byte order to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_BYTEORDER_MSB: Most Significant Bit first
  *            @arg SPI_BYTEORDER_LSB: Least Significant Bit first
  * @retval 1 if the byte order is valid, otherwise 0.
  */
#define IS_SPI_BYTE_ORDER(BYTE_ORDER) (((BYTE_ORDER) == SPI_BYTEORDER_MSB) || \
                                        ((BYTE_ORDER) == SPI_BYTEORDER_LSB))


/**
  * @brief  Check if a given SPI NSS configuration is valid.
  * @param  NSS_CONFIG: the NSS configuration to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_NSS_SOFT: Software-driven NSS
  *            @arg SPI_NSS_HW_INPUT: Hardware NSS input mode
  *            @arg SPI_NSS_HW_OUTPUT: Hardware NSS output mode
  * @retval 1 if the NSS configuration is valid, otherwise 0.
  */
#define IS_SPI_NSS_CONFIG(NSS_CONFIG) (((NSS_CONFIG) == SPI_NSS_SOFT) || \
                                        ((NSS_CONFIG) == SPI_NSS_HW_INPUT) || \
                                        ((NSS_CONFIG) == SPI_NSS_HW_OUTPUT))


/**
  * @brief  Check if a given SPI data size is valid.
  * @param  DATA_SIZE: the data size to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_DATASIZE_8BIT: 8-bit data size
  *            @arg SPI_DATASIZE_16BIT: 16-bit data size
  * @retval 1 if the data size is valid, otherwise 0.
  */
#define IS_SPI_DATASIZE(DATA_SIZE) (((DATA_SIZE) == SPI_DATASIZE_8BIT) || \
                                     ((DATA_SIZE) == SPI_DATASIZE_16BIT))


/**
  * @brief  Check if a given SPI polarity is valid.
  * @param  POLARITY: the polarity to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_POLARITY_LOW:  Polarity low
  *            @arg SPI_POLARITY_HIGH: Polarity high
  * @retval 1 if the polarity is valid, otherwise 0.
  */
#define IS_SPI_POLARITY(POLARITY) (((POLARITY) == SPI_POLARITY_LOW) || \
                                    ((POLARITY) == SPI_POLARITY_HIGH))



/**
  * @brief  Check if a given SPI phase is valid.
  * @param  PHASE: the phase to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_PHASE_FIRST_EDGE: First edge
  *            @arg SPI_PHASE_SECOND_EDGE: Second edge
  * @retval 1 if the phase is valid, otherwise 0.
  */
#define IS_SPI_PHASE(PHASE) (((PHASE) == SPI_PHASE_FIRST_EDGE) || \
                              ((PHASE) == SPI_PHASE_SECOND_EDGE))



/**
  * @brief  Check if a given SPI CRC calculation setting is valid.
  * @param  CRC_SETTING: the CRC calculation setting to check.
  *         This parameter can be one of the following values:
  *            @arg SPI_CRCCALCULATION_DISABLE: CRC calculation disabled
  *            @arg SPI_CRCCALCULATION_ENABLE: CRC calculation enabled
  * @retval 1 if the CRC calculation setting is valid, otherwise 0.
  */
#define IS_SPI_CRC_SETTING(CRC_SETTING) (((CRC_SETTING) == SPI_CRCCALCULATION_DISABLE) || \
                                          ((CRC_SETTING) == SPI_CRCCALCULATION_ENABLE))



/**
  * @brief  Check if a parameter is null or not.
  * @param  PTR: the parameter to check.
  * @retval 1 if the parameter is not null, otherwise 0.
  */
#define IS_NOT_NULL(PTR) ((PTR) != NULL)


/** @brief  Checks if SPI polynomial value to be used for the CRC calculation, is in allowed range.
  * @param  __POLYNOMIAL__ specifies the SPI polynomial value to be used for the CRC calculation.
  *         This parameter must be a number between Min_Data = 0 and Max_Data = 65535
  * @retval None
  */
#define IS_SPI_CRC_POLYNOMIAL(__POLYNOMIAL__) (((__POLYNOMIAL__) >= 0x1U) && ((__POLYNOMIAL__) <= 0xFFFFU) && (((__POLYNOMIAL__)&0x1U) != 0U))




/**
  * @brief  Check the state of a flag in a register.
  * @param  __REG__: The register to check.
  * @param  __FLAG__: The flag to check in the register.
  * @retval 1 if the flag is set, otherwise 0.
  */
#define GET_FLAG_STATE(__REG__,__FLAG__)    (((__REG__) & (__FLAG__)))

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/** 
  * @brief Serial Peripheral Interface
  */
typedef struct 
{
    __IO uint32_t CR1;   /*!< Control register 1 */
    __IO uint32_t CR2;   /*!< Control register 2 */
    __IO uint32_t SR;    /*!< Status register */
    __IO uint32_t DR;    /*!< Data register */
    __IO uint32_t CRCPR; /*!< CRC polynomial register */
    __IO uint32_t RXCRCR;/*!< RX CRC register */
    __IO uint32_t TXCRCR;/*!< TX CRC register */
    __IO uint32_t I2SCFGR; /*!< I2S configuration register */
    __IO uint32_t I2SPR; /*!< I2S prescaler register */
} SPI_t;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

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

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
SPI_ErrorStatus SPI_Init(SPI_Handle_t *hspi)
{
    SPI_ErrorStatus RET_enuErrorStatus = SPI_OK;
    if(IS_NOT_NULL(hspi) &&
       IS_SPI_BAUDRATE_PRESCALER(hspi->Init.BaudRatePrescaler) &&
       IS_SPI_BYTE_ORDER(hspi->Init.ByteOrder) &&
       IS_SPI_CRC_SETTING(hspi->Init.CRCCalculation) &&
       IS_SPI_DATASIZE(hspi->Init.DataSize) &&
       IS_SPI_INSTANCE(hspi->Instance) &&
       IS_SPI_MODE(hspi->Init.Mode) &&
       IS_SPI_NSS_CONFIG(hspi->Init.NSS) &&
       IS_SPI_POLARITY(hspi->Init.CLKPolarity) &&
       IS_SPI_PHASE(hspi->Init.CLKPhase)/* && 
       IS_SPI_CRC_POLYNOMIAL(hspi->Init.CRCPolynomial)*/)
       {
            SPI_t * Instance = ((SPI_t*)hspi->Instance);
            Instance->CR1 = (hspi->Init.Mode | hspi->Init.CRCCalculation | hspi->Init.DataSize |
                            (hspi->Init.NSS & SPI_CR1_SSM ) | hspi->Init.CLKPolarity       | hspi->Init.CLKPhase |
                             hspi->Init.ByteOrder | hspi->Init.BaudRatePrescaler);
            Instance->CR2   = ((hspi->Init.NSS == SPI_NSS_HW_OUTPUT)?SPI_NSS_HW_OUTPUT : SPI_CR1_RESET);
            Instance->CRCPR = ((hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)?hspi->Init.CRCPolynomial:SPI_CRCPR_RESET);
          if(hspi->Init.NSS == SPI_NSS_SOFT)
          {
            Instance->CR1 |= SPI_CR1_SSI;
          }
          hspi->State = SPI_STATE_INITIALIZED;
       }
    else
    {
      RET_enuErrorStatus = SPI_ERROR;
    }
    return RET_enuErrorStatus;
}

SPI_ErrorStatus SPI_Transmit(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    SPI_ErrorStatus RET_enuErrorStatus = SPI_OK; 
    if(IS_NOT_NULL(hspi) && IS_NOT_NULL(pData))
    {
        SPI_t * Instance = ((SPI_t*)hspi->Instance);
        uint32_t idx = 0;
        if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
        {
          Instance->CR1 = SPI_CR1_RESET;
        }
        Instance->CR1 |= SPI_CR1_SPE;
        while ( idx < Size)
        {
            if(GET_FLAG_STATE(Instance->SR,SPI_SR_TXE)  == TX_BUFFER_EMPTY)
            {
                Instance->DR = pData[idx];
                idx += 1;
            }
        }
        if(hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
        {
          Instance->CR1 |= SPI_CR_CRCNEXT;
        }
        while (GET_FLAG_STATE(Instance->SR,SPI_SR_BSY) == SPI_IS_BUSY);
    } 
    else
    {
        RET_enuErrorStatus = SPI_ERROR;
    }
    return RET_enuErrorStatus;
}

SPI_ErrorStatus SPI_Receive(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    SPI_ErrorStatus RET_enuErrorStatus = SPI_OK; 
    if(IS_NOT_NULL(hspi) && IS_NOT_NULL(pData))
    {
      SPI_t * Instance = ((SPI_t*)hspi->Instance);
      Instance->CR1 |= SPI_CR1_SPE;
      for(uint32_t data = 0 ; data < Size && Timeout ;data++)
      {
        if(hspi->Init.Mode == SPI_MODE_MASTER)
        {
          while( GET_FLAG_STATE(Instance->SR,SPI_SR_TXE)  != TX_BUFFER_EMPTY);
          /**Send Dummy Data */
          Instance->DR = pData[data];
        }
        while(GET_FLAG_STATE(Instance->SR,SPI_SR_RXNE) != RX_BUFFER_NOT_EMPTY);

        pData[data] = Instance->DR;
      }   
    }
    else
    {
        RET_enuErrorStatus = SPI_ERROR;
    }  
    return RET_enuErrorStatus;
}

SPI_ErrorStatus SPI_TransmitAsyncZeroCopy(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size,CallBack_t CB)
{
  SPI_ErrorStatus RET_ErrorStatus = SPI_OK;
  if(IS_NOT_NULL(hspi) && IS_NOT_NULL(pData) && hspi->State != SPI_STATE_BUSY)
  {
    hspi->State = SPI_STATE_BUSY;
    hspi->callBack = CB;
    hspi->Data     = pData;
    hspi->size     = Size;
    hspi->idx      = 0;
    ((SPI_t*)hspi->Instance)->CR1 |= SPI_CR1_SPE;
    ((SPI_t*)hspi->Instance)->CR2 |= SPI_CR2_TXEIE;
  }
  else
  {
    RET_ErrorStatus = SPI_ERROR;
  }
  return RET_ErrorStatus;
}


SPI_ErrorStatus SPI_ReceiveAsyncZeroCopy(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size,CallBack_t CB)
{
  SPI_ErrorStatus RET_ErrorStatus = SPI_OK;
  if(IS_NOT_NULL(hspi) && IS_NOT_NULL(pData) && hspi->State != SPI_STATE_BUSY)
  {
    hspi->State = SPI_STATE_BUSY;
    hspi->callBack = CB;
    hspi->Data     = pData;
    hspi->size     = Size;
    hspi->idx      = 0;
    ((SPI_t*)hspi->Instance)->CR1 |= SPI_CR1_SPE;
    ((SPI_t*)hspi->Instance)->CR2 |= SPI_CR2_RXNEIE;
    if(hspi->Init.Mode == SPI_MODE_MASTER)
    {
      ((SPI_t*)hspi->Instance)->DR = 0xFF;
    }
  }
  else
  {
    RET_ErrorStatus = SPI_ERROR;
  }
  return RET_ErrorStatus;
}


/******************************************************************************/