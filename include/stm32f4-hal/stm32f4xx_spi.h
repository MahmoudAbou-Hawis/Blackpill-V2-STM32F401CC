/*******************************************************************************/
/**
* @file    stm32f401xx_spi.h
* @brief   SPI Driver Header File for STM32F401CC Microcontroller
*
* @par Project Name
*  stm32f4xx drivers
*
* @par Code Language
* C
*
* @par Description
* This header file provides function prototypes and definitions for
* interacting with the Serial Peripheral Interface (SPI) module on the
* STM32F401CC microcontroller. It offers functionalities for setting up the
* SPI peripheral, configuring communication parameters, and transmitting/receiving
* data.
*
* @par Author
* Mahmoud Abou-Hawis
*
*******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef __STM32F4xx_SPI_H_
#define __STM32F4xx_SPI_H_
/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/


/** @defgroup SPI_Instances SPI Instances
  * @{
  */
#define SPI1                            ((void*)0x40013000) /*!< SPI1 base address */
#define SPI2                            ((void*)0x40003800) /*!< SPI2 base address */
#define SPI3                            ((void*)0x40003C00) /*!< SPI3 base address */
#define SPI4                            ((void*)0x40013400) /*!< SPI4 base address */
/**
  * @}
  */

/** @defgroup SPI_Mode SPI Mode
  * @{
  */
#define SPI_MODE_MASTER                 (0x00000004U)
#define SPI_MODE_SLAVE                  (0x00000000U)
/**
  * @}
  */


/** @defgroup SPI_BaudRate_Prescaler SPI BaudRate Prescaler
  * @{
  */
#define SPI_BAUDRATEPRESCALER_2           (0x00000000U) /*!< SPI baud rate prescaler: 2 */
#define SPI_BAUDRATEPRESCALER_4           (0x00000008U) /*!< SPI baud rate prescaler: 4 */
#define SPI_BAUDRATEPRESCALER_8           (0x00000010U) /*!< SPI baud rate prescaler: 8 */
#define SPI_BAUDRATEPRESCALER_16          (0x00000018U) /*!< SPI baud rate prescaler: 16 */
#define SPI_BAUDRATEPRESCALER_32          (0x00000020U) /*!< SPI baud rate prescaler: 32 */
#define SPI_BAUDRATEPRESCALER_64          (0x00000028U) /*!< SPI baud rate prescaler: 64 */
#define SPI_BAUDRATEPRESCALER_128         (0x00000030U) /*!< SPI baud rate prescaler: 128 */
#define SPI_BAUDRATEPRESCALER_256         (0x00000038U) /*!< SPI baud rate prescaler: 256 */
/**
  * @}
  */


/** @defgroup SPI_MSB_LSB_transmission SPI MSP_LSB transmission options
  * @{
  */
#define SPI_BYTEORDER_MSB               (0x00000000U)
#define SPI_BYTEORDER_LSB               (0x00000080U)
/**
  * @}
  */
 

/** @defgroup SPI_Slave_Select_management SPI Slave Select Management
  * @{
  */  
#define SPI_NSS_SOFT                    (0x00000200U)
#define SPI_NSS_HW_INPUT                (0x00000000U)
#define SPI_NSS_HW_OUTPUT               (0x00000004U)
/**
  * @}
  */

/** @defgroup SPI_Data_Size SPI Data Size
  * @{
  */
#define SPI_DATASIZE_8BIT               (0x00000000U)
#define SPI_DATASIZE_16BIT              (0x00000800U)
/**
  * @}
  */



/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
  * @{
  */
#define SPI_POLARITY_LOW                (0x00000000U)
#define SPI_POLARITY_HIGH               (0x00000002U)
/**
  * @}
  */


/** @defgroup SPI_Clock_Phase SPI Clock Phase
  * @{
  */
#define SPI_PHASE_FIRST_EDGE            (0x00000000U)
#define SPI_PHASE_SECOND_EDGE           (0x00000001U)
/**
  * @}
  */



/** @defgroup SPI_CRC_Calculation SPI CRC Calculation
  * @{
  */
#define SPI_CRCCALCULATION_DISABLE      (0x00000000U)
#define SPI_CRCCALCULATION_ENABLE       (0x00002000U)
/**
  * @}
  */




/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/** 
  * @brief  SPI Status structures definition  
  */  
typedef enum
{
  SPI_OK       = 0x00U,
  SPI_ERROR    = 0x01U,
  SPI_BUSY     = 0x02U,
  SPI_TIMEOUT  = 0x03U
} SPI_ErrorStatus;

/**
  * @brief  Enumeration of SPI states.
  *         Defines the possible states of the SPI peripheral.
  */
typedef enum
{
  SPI_STATE_BUSY            = 0x00U, /*!< SPI is busy */
  SPI_STATE_IDLE            = 0x01U, /*!< SPI is idle */
  SPI_STATE_NOT_INITIALIZED = 0x02U, /*!< SPI is not initialized */
  SPI_STATE_INITIALIZED     = 0x03U  /*!< SPI is initialized */
} SPI_States;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief Call Back function 
 * 
 */
typedef void (*CallBack_t)(void);

/**
 * @brief SPI Initialization Configuration
 *
 * This structure defines the configuration parameters for initializing the SPI
 * peripheral. Members of this structure specify various operational aspects
 * of the SPI communication.
 *
 * @note Refer to the microcontroller's specific SPI documentation for detailed
 * information on supported features and configuration options.
 */
typedef struct 
{
    /**
     * @brief SPI Operation Mode
     *
     * This parameter specifies the SPI operation mode, which can be either
     * master or slave. It should be set using the following values from the
     * @ref SPI_Mode.
     */
    uint32_t Mode;    

    /**
     * @brief SPI Baud Rate Prescaler
     *
     * This parameter specifies the SPI communication clock prescaler value. It is
     * used to configure the transmit and receive Serial Clock (SCK) frequency.
     * The valid values for this parameter can be found in the @ref SPI_BaudRate_Prescaler.
     *
     * @note The SPI communication clock is derived from the master clock. The
     * slave device does not need its clock configured because it synchronizes with
     * the master's SCK signal.
     */
    uint32_t BaudRatePrescaler;

    /**
     * @brief SPI Byte Order (MSB/LSB)
     *
     * This parameter specifies the order in which data bytes are transmitted
     * and received on the SPI bus. It should be set using the following values
     * from the @ref SPI_MSB_LSB_transmission.
     */
    uint32_t ByteOrder;

    /**
     * @brief SPI Slave Select (NSS) Management
     *
     * This parameter specifies the method used to manage the Slave Select (NSS)
     * signal for SPI communication. It should be set using the following values
     * from the @ref SPI_Slave_Select_Management.
     */
    uint32_t NSS;

    /**
     * @brief SPI Data Size
     *
     * This parameter specifies the number of bits per data element that will be
     * transmitted and received on the SPI bus. It should be set using the following
     * values from the @ref SPI_Data_Size .
     */
    uint32_t DataSize;

    /**
     * @brief SPI Clock Polarity (CPOL)
     *
     * This parameter specifies the polarity of the SPI clock (SCK) signal. It
     * should be set using the following values from the @ref CLKPolarity.
     */
    uint32_t CLKPolarity; 

    /**
     * @brief SPI Clock Phase (CPHA)
     *
     * This parameter specifies the phase relationship between the SPI clock (SCK) signal
     * and the data on the bus. It should be set using the following values from the
     * @ref SPI_Clock_Phase.
     */
    uint32_t CLKPhase;

    /**
     * @brief SPI CRC Calculation Enable
     *
     * This parameter specifies whether to enable or disable Cyclic Redundancy Check
     * (CRC) calculation for SPI communication. It should be set using the following
     * values from the @ref SPI_CRC_Calculation.
     */
    uint32_t CRCCalculation;

    /**
     * @brief SPI CRC Polynomial
     *
     * This parameter specifies the polynomial used for the Cyclic Redundancy Check
     * (CRC) calculation. The CRC polynomial is a bit pattern that influences the
     * error detection capability of the CRC algorithm.
     *
     * **Valid Values:**
     * - The CRCPolynomial value must be an odd number between the minimum data size
     *   (Min_Data = 1) and the maximum data size (Max_Data = 65535). 
     */
    uint32_t CRCPolynomial;

} SPI_Init_t;


/* 
 * Structure defining an SPI handle, which holds a pointer to the SPI instance 
  and its initialization parameters.
 */
typedef struct 
{
  void * Instance;    /*!< Pointer to the SPI instance @ref SPI_Instances */
  SPI_Init_t Init;    /*!< Initialization parameters of the SPI */
  SPI_States State;   /*!  Carry the current State of SPI*/ 
  uint32_t idx;       /*!< Carry the current idx when used Async functions*/
  uint32_t size;      /*!< Carry the current size of data when used Async functions*/
  CallBack_t callBack;/*!< Carry the CallBack which will executed after finish the Async functions*/
  uint8_t * Data;     /*!< Carry the data (transmit/received) in Async functions */
} SPI_Handle_t;



/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DECLARATIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DECLARATIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES */
/******************************************************************************/

/**
 * @brief Initializes the SPI peripheral.
 *
 * This function initializes the SPI peripheral based on the provided handle.
 *
 * @param hspi Pointer to the SPI handle structure.
 * @return SPI error status, indicating success or failure of the initialization.
 */
extern SPI_ErrorStatus SPI_Init(SPI_Handle_t *hspi);


/**
 * @brief Transmits data over SPI.
 *
 * This function transmits data over SPI using the provided handle.
 *
 * @param hspi Pointer to the SPI handle structure.
 * @param pData Pointer to the data buffer to be transmitted.
 * @param Size Number of data bytes to transmit.
 * @param Timeout Timeout duration in milliseconds.
 * @return SPI error status, indicating success or failure of the transmission.
 */
extern SPI_ErrorStatus SPI_Transmit(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);


/**
 * @brief Receives data over SPI.
 *
 * This function receives data over SPI using the provided handle.
 *
 * @param hspi Pointer to the SPI handle structure.
 * @param pData Pointer to the buffer to store the received data.
 * @param Size Number of data bytes to receive.
 * @param Timeout Timeout duration in milliseconds.
 * @return SPI error status, indicating success or failure of the reception.
 */
extern SPI_ErrorStatus SPI_Receive(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);


/**
 * @brief Transmits data over SPI asynchronously without using a buffer.
 *
 * This function transmits data over SPI asynchronously without using a buffer.
 *
 * @param hspi Pointer to the SPI handle structure.
 * @param pData Pointer to the data buffer to be transmitted.
 * @param Size Number of data bytes to transmit.
 * @return SPI error status, indicating success or failure of the transmission.
 */
extern SPI_ErrorStatus SPI_TransmitAsyncZeroCopy(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size,CallBack_t CB);


/**
 * @brief Receives data over SPI asynchronously without using a buffer.
 *
 * This function receives data over SPI asynchronously without using a buffer.
 *
 * @param hspi Pointer to the SPI handle structure.
 * @param pData Pointer to the buffer to store the received data.
 * @param Size Number of data bytes to receive.
 * @return SPI error status, indicating success or failure of the reception.
 */
extern SPI_ErrorStatus SPI_ReceiveAsyncZeroCopy(SPI_Handle_t *hspi, uint8_t *pData, uint16_t Size,CallBack_t CB);


/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
}
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#endif /* __STM32F4xx_SPI_H_ */
/******************************************************************************/
