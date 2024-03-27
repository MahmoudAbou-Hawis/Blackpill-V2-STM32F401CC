/*******************************************************************************/
/**
 * @file UART.h
 * @brief UART (Universal Asynchronous Receiver/Transmitter) interface definitions
 *        for STM32F401CC microcontrollers
 *
 * @par Project Name
 * stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file provides a generic interface for interacting with multiple UART
 * peripherals on the STM32F401CC microcontroller (UART1,UART2 and UART6).
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 *
 *******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef UART_H_
#define UART_H_
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
#include <stddef.h>
#include <stdbool.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/** @defgroup UART_Word_Length UART Word Length
  * @{
*/
#define UART_WORDLENGTH_8B                  0x00000000U
#define UART_WORDLENGTH_9B                  0x00001000U
/**
  * @}
*/

/** @defgroup UART_Over_Sampling UART over sampling options
  * @{
*/
#define UART_OVERSAMPLING_16                0x00000000U
#define UART_OVERSAMPLING_8                 0x00008000U
 /**
  * @}
*/

/** @defgroup UART_PARITY UART parity options
 * @{
 */
#define UART_PARITY_NONE                    0x00000000U
#define UART_PARITY_ODD                     0x00000200U
#define UART_PARITY_EVEN                    0x00000000U
/**
 * @}
*/

/** @defgroup UART_STOP_BITS UART stop bits options
 * @{
*/
#define UART_STOP_BITS_ONE                  0x00000000U
#define UART_STOP_BITS_TWO                  0x00002000U

/**
 * @}
*/

/** @defgroup UART_Mode UART Transfer Mode
  * @{
*/
#define UART_MODE_RX                        0x00000004U
#define UART_MODE_TX                        0x00000008U
#define UART_MODE_TX_RX                     ((uint32_t)(UART_MODE_TX | UART_MODE_RX))
/**
  * @}
*/

/** @defgroup UART_Instances UART Instances options :
  * @{
*/
#define USART1                              ((void*)0x40011000)
#define USART2                              ((void*)0x40004401)
#define USART6                              ((void*)0x40011402)
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
 * @typedef UART_ErrorStatus_t
 * @brief Enumerates the different UART error status codes.
 */
typedef enum
{
  /** @enum{UART_NULL_PTR_PASSED} - Error code indicating a null pointer 
   *        was passed to a UART function. */
  UART_NULL_PTR_PASSED,

  /** @enum{UART_ERROR_NONE} - Error code indicating no error occurred 
   *        in UART communication . */
  UART_ERROR_NONE,

  /** @enum{UART_ERROR} - General error code for any UART error . */
  UART_ERROR,

   /** @enum{UART_PARAM_ERROR} - Error code indicating invalid 
    *       parameters were passed to a UART function. 
   *                          
   */
  UART_PARAM_ERROR
} UART_ErrorStatus_t;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @typedef Uart_CallBack
 * @brief Defines a function pointer type for UART callback functions.
 *
 * @return void
 */
typedef void (*Uart_CallBack)(void);

/**
 * @typedef UART_Init_t
 * @brief Defines a structure containing configuration parameters for UART initialization.
 */
typedef struct
{
    /** @field OverSampling - Oversampling factor for UART communication. */
    /** @ref UART_Word_Length */
    uint32_t OverSampling;

    /** @field WordLength - Word length (number of bits per data frame 8Bit or 9Bit). */
    /** @ref UART_Over_Sampling*/
    uint32_t WordLength;

    /** @field Parity - Parity configuration (e.g., none, even, odd). */
    /** @ref  UART_PARITY*/
    uint32_t Parity;

    /** @field Mode - Indicates whether the UART will transmit, receive, or both. */
    /** @ref  UART_Mode*/
    uint32_t Mode;

    /** @field tStopBits - Number of stop bits used in UART communication. */
    /** @ref  UART_STOP_BITS*/
    uint32_t StopBits;

    /** @field BaudRate - Baud rate (communication speed) for UART transmission. */
    uint32_t BaudRate;
} UART_Init_t;

/**
 * @typedef UART_Handle_t
 * @brief Defines a structure representing a UART handle, used to manage a UART instance.
 */
typedef struct 
{
    /** @field pUartInstance - Pointer to the UART peripheral instance. */
    /** @ref UART_Instances*/
    void * pUartInstance;

    /** @field UartConfiguration - UART configuration parameters used for initialization. */
    UART_Init_t UartConfiguration;

} UART_Handle_t;


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
 * @brief Initializes a UART instance with the specified configuration.
 *
 * @param[in] uartHandle Pointer to a UART_Handle_t structure containing the UART 
 *                   instance and configuration.
 *
 * @return UART_ErrorStatus_t An error status code indicating the 
 *         success or failure of initialization.
 * 
 * @note it is mandatory to call init function before utilizing other APIs.
 */
extern UART_ErrorStatus_t UART_Init(const UART_Handle_t * const uartHandle);

/**
 * @brief Transmits data over UART with a timeout mechanism.
 *
 * @param[in] uartHandle Pointer to a UART_Handle_t structure identifying the UART instance.
 * @param[in] pData Pointer to the data to be transmitted.
 * @param[in] Size Size of the data to be transmitted in bytes.
 * @param[in] Timeout Timeout value.
 *
 * @return UART_ErrorStatus_t An error status code indicating the 
 *         success or failure of transmission.
 */
extern UART_ErrorStatus_t UART_TransmitTimeOut(UART_Handle_t *uartHandle, char *pData,
                                                   uint16_t Size, uint32_t Timeout);

/**
 * @brief Receives data over UART with a timeout mechanism.
 *
 * @param[in] uartHandle Pointer to a UART_Handle_t structure identifying the UART instance.
 * @param[in] pData Pointer to the buffer where the received data will be stored.
 * @param[in] Size Maximum size of data to be received in bytes.
 * @param[in] Timeout Timeout value.
 *
 * @return UART_ErrorStatus_t An error status code indicating the 
 *         success or failure of reception.
 */
extern UART_ErrorStatus_t UART_ReceiveTimeOut(UART_Handle_t *uartHandle, char *pData,
                                              uint16_t Size, uint32_t Timeout);

/**
 * @brief Asynchronously transmits data over UART without data copying (zero-copy) 
 *        and using a callback mechanism.
 *
 * @param[in] uartHandle Pointer to a UART_Handle_t structure identifying the UART instance.
 * @param[in] pData Pointer to the data to be transmitted .
 * @param[in] Size Size of the data to be transmitted in bytes.
 * @param[in] CB Callback function that will be invoked upon transmission completion or errors.
 *
 * @return UART_ErrorStatus_t An error status code indicating the 
 *         success or failure of starting asynchronous transmission.
 */
extern UART_ErrorStatus_t UART_TransmitAsyncZeroCopy(UART_Handle_t *uartHandle,
                                                     char *pData, uint16_t Size,
                                                     Uart_CallBack CB);

/**
 * @brief Asynchronously receives data over UART without data copying (zero-copy)
 *       and using a callback mechanism.
 *
 * @param[in] uartHandle Pointer to a UART_Handle_t structure identifying the UART instance.
 * @param[in] pData Pointer to the buffer where the received data will be stored.
 * @param[in] Size Maximum size of data to be received in bytes.
 * @param[in] CB Callback function that will be invoked upon reception completion or errors.
 *
 * @return UART_ErrorStatus_t An error status code indicating the 
 *         success or failure of starting asynchronous reception.
 */
extern UART_ErrorStatus_t UART_ReceiveAsyncZeroCopy(UART_Handle_t *uartHandle,
                                                    char *pData, uint16_t Size, 
                                                    Uart_CallBack CB);



/** @brief Transmits data using UART with DMA (Direct Memory Access).
*
*This function transmits data through the UART peripheral using Direct Memory Access (DMA). 
*It returns the status of the transmission, indicating success or an error.
*
* @param[in] uartHandle Pointer to a UART_Handle_t structure identifying the UART instance.
*
* @param[in] CB Callback function that will be invoked upon transmission completion.
*
*/
extern void UART_TransmitWithDMA(UART_Handle_t *uartHandle,Uart_CallBack CB);


/** @brief Receives data using UART with DMA (Direct Memory Access).
*
*This function receives data through the UART peripheral using Direct Memory Access (DMA). 
*It returns the status of the reception, indicating success or an error.
*
* @param[in] uartHandle Pointer to a UART_Handle_t structure identifying the UART instance.
*
*/
extern void UART_ReceiveWithDMA(UART_Handle_t *uartHandle);


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
#endif /* UART_H_ */
/******************************************************************************/
