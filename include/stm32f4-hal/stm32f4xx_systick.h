/*******************************************************************************/
/**
 * @file stm32f4xx_systick.h
 *
 * @brief SysTick Timer Driver
 *
 * @par Project Name
 * stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file provides functions a to configure and utilize
 * the SysTick timer as a system time base or for generating time delays.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/ 

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef __STM32F4xx_SYSTICK_H_
#define __STM32F4xx_SYSTICK_H_
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
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/**
 * @typedef SysTickCB_t
 * @brief Callback function type definition for SYSTICK interrupts.
 *
 * This typedef defines the function signature expected for callback functions
 * used with SYSTICK interrupts. The callback function must take no arguments
 * and return void.
 *
 * **Important:** Functions used as SYSTICK callbacks must strictly adhere to this
 * format (void (*SysTickCB_t)(void)) to ensure proper interaction with the SYSTICK
 * interrupt handling mechanism.
 */
typedef void (*SysTickCB_t)(void);



/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/**
 * @defgroup SYSTICK_ERROR_STATUS
 * @{
 */

/**
  * @typedef SysTick_ErrorStatus_t
  * @brief Enumeration for SYSTICK error status codes.
  *
  * This enumeration defines the possible return values from SYSTICK-related 
  * functions to indicate success or error conditions.
  */
typedef enum
{
  /** @enum{0} No error occurred (function call successful). */
  SYSTICK_OK,

  /** @enum{1} An error occurred during the SYSTICK operation. */
  SYSTICK_NOT_OK,

  /** @enum{2} A null pointer was passed as an argument to a SYSTICK function. */
  SYSTICK_NULL_PTR_PASSED
} SysTick_ErrorStatus_t;

/**
 * @}
 */

/**
 * @defgroup SYSTICK_Configuration
 * @{
 */

/**
 * @typedef CLKSRC_t
 * @brief Enumeration for SYSTICK clock source options.
 *
 * This enumeration defines the valid clock source selections for the SYSTICK timer.
 */
typedef enum
{
  /** @enum{0} AHB_DIV_8: Selects the AHB clock divided by 8 as the SYSTICK clock source. */
  SYSTICK_CLKSRC_AHB_DIV_8 = 0,

  /** @enum{1} PROC_CLK: Selects the processor clock (AHB) as the SYSTICK clock source. */
  SYSTICK_CLKSRC_PROC_CLK = 1,

} SysTick_CLKSRC_t;

/**
 * @}
 */

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @typedef SysTick_CFG_t
 * @brief Configuration structure for SYSTICK peripheral.
 *
 * This structure defines the configuration parameters for the SYSTICK peripheral.
 *
 */
typedef struct
{
  uint32_t CLK;  /** Clock frequency for SYSTICK timer (in Hz)  */
  SysTick_CLKSRC_t CLKSOURCE; /** Selects the clock source for SYSTICK counter*/
} SysTick_CFG_t;


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
 * @brief Configures the SYSTICK peripheral with specified settings.
 *
 * This function sets up the SYSTICK timer according to the configuration
 * provided in the `SysTickCFG` structure. 
 *
 * @param[in] SysTickCFG  Pointer to a `SysTick_CFG_t` structure containing the
 *                        desired configuration settings:
 * 
 *     - @member CLK:        Clock frequency for the SYSTICK timer (in Hz).
 *     - @member CLKSOURCE:  Clock source selection for the SYSTICK counter.
 *
 * @return SYSTICK_OK on successful configuration, SYSTICK_NOT_OK on error.
 *
 * @note This function must be called before using other SYSTICK functionalities.
 */
extern SysTick_ErrorStatus_t SysTick_Config(SysTick_CFG_t * SysTickCFG);

/**
 * @brief Sets the reload value and counter value of the SYSTICK peripheral to the
 * provided time in milliseconds.
 *
 * This function configures the SYSTICK peripheral to generate an interrupt after
 * the specified time in milliseconds has elapsed.
 *
 * @param[in] Time  The desired time delay in milliseconds (must be non-zero).
 *
 * @return SYSTICK_OK on success, SYSTICK_NOT_OK on error.
 * 
 * @note should use SysTick_Start() to start counting.
 */
extern SysTick_ErrorStatus_t SysTick_SetTimeMS(uint32_t Time);



/**
 * @brief Starts the SYSTICK counter.
 *
 * This function enables the SYSTICK counter and initiates its countdown. After
 * the configured reload value is reached, a system tick interrupt will be generated.
 * 
 * @note Before calling this function, ensure the SYSTICK timer 
 *             has been properly configured and initialized with a reload value. 
 *             This typically involves setting the clock source and reload value 
 *             using functions like SysTick_Config(...)
 */
extern SysTick_ErrorStatus_t SysTick_Start(void);



/**
 * @brief Registers a callback function for SYSTICK interrupts.
 *
 * This function assigns the provided callback function (`pCallBackFunction`) to be
 * invoked when a SYSTICK interrupt occurs. The callback function is responsible
 * for handling the interrupt and performing any necessary actions.
 *
 * @param[in] pCallBackFunction  Pointer to the callback function to be registered.
 *                           The function must adhere to the format `void (*SysTickCB_t)(void)`.
 *
 * @return SYSTICK_OK on success, SYSTICK_NOT_OK on error (e.g., invalid callback format).
 */
extern SysTick_ErrorStatus_t SysTick_SetCallback(SysTickCB_t pCallBackFunction);
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
#endif /* __STM32F4xx_SYSTICK_H_ */
/******************************************************************************/
