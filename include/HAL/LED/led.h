/*******************************************************************************/
/**
 * @file LED.h
 * @brief Header file for LED Module
 *
 * @par Project Name
 *  Led Module.
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines the interface for the LED module. It contains declarations
 * for functions and data types related to controlling LEDs, such as initialization
 * and setting LED states.
 *
 * @par Usage
 * To use the LED module in your project:
 * 1. Include the "LED.h" header file in your source files where LED functionality is needed.
 * 2. Call LED_enuInit() to initialize the LED module before using any other LED-related functions.
 * 3. Use the LED_enuSetStatus() function to set the status (ON/OFF) of individual LEDs.
 * 
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/ 

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef LED_H_
#define LED_H_
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
#include "led_cfg.h"
#include <stdint.h>
#include <stddef.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

#define LED_CONNECTION_FORWARD   ((uint8_t)1)
#define LED_CONNECTION_REVERSE   ((uint8_t)0)
#define LED_STATE_ON             ((uint8_t)1)
#define LED_STATE_OFF            ((uint8_t)0)
/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/**
 * @brief LED Error Status Enumeration
 *
 * This enumeration defines the possible error status values that can be returned
 * by LED-related functions. It includes the following values:
 * - LED_SUCCESS: The operation was successful.
 * - INITIALIZATION_FAILED: LED initialization failed.
 * - LED_FAILED: General failure status.
 */
typedef enum {
    LED_SUCCESS = 0U,               /**< Operation successful */
    LED_INITIALIZATION_FAILED,      /**< LED initialization failed */
    LED_FAILED                      /**< General failure status */
} LED_errorStatus;

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief LED Configuration Structure
 * 
 * This structure defines the configuration for an LED, including the GPIO port,
 * pin number, connection type, and default state.
 */
typedef struct
{
    void *  GPIO_Port;      /**< Pointer to the GPIO port used by the LED */
    uint8_t GPIO_Pin;       /**< Pin number of the LED */
    uint8_t LED_Connection; /**< Type of LED connection (forward or reverse) */
    uint8_t LED_State;      /**< Default state of the LED (ON or OFF) */
} LED_CFG_t;

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
 * @brief Initialize the LED Module
 *
 * This function initializes the LED module. It configures the GPIO pins and
 * sets the default state for all LEDs. If initialization is successful, it
 * returns SUCCESS; otherwise, it returns INITIALIZATION_FAILED.
 *
 * @return LED_errorStatus
 * - LED_SUCCESS: The LED module was successfully initialized.
 * - INITIALIZATION_FAILED: LED module initialization failed.
 */
extern LED_errorStatus LED_enuInit(void);


/**
 * @brief Set the Status of an LED
 *
 * This function sets the status of the specified LED to the given state.
 *
 * @param Led_Name The name or identifier of the LED.
 * @param LED_State The state to set for the LED (ON or OFF).
 * 
 * @return LED_errorStatus
 * - LED_SUCCESS: The LED status was successfully set.
 * - LED_FAILED: Failed to set the LED status.
 * 
 * @note you should Call LED_enuInit() first.
 */
extern LED_errorStatus LED_enuSetStatus(uint8_t Led_Name, uint8_t LED_State);

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
#endif /* FILE_H_ */
/******************************************************************************/
