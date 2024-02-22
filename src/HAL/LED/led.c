/*******************************************************************************/
/**
 * @file LED.c
 * @brief Implementation file for LED Module
 *
 * @par Project Name
 * LED Control System
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This implementation file contains the definitions of functions declared in
 * LED.h. It provides the actual implementation for controlling LEDs, such as
 * initialization and setting LED states.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/ 

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "led.h"
#include <stdbool.h>
#include "stm32f4xx_gpio.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

/**
 * @brief Macro to Check if a Value is Not a Valid LED Identifier
 *
 * This macro checks if the given value is not a valid LED identifier by verifying
 * if it is less than zero or greater than or equal to the total number of LEDs
 * defined in the system.
 *
 * @param __LED__ The value to be checked as a LED identifier.
 * @return 1 if the value is not a valid LED identifier, 0 otherwise.
 */
#define IS_NOT_LED(__LED__)             ((__LED__ < 0) || (__LED__ >= _LEDs_NUM))

/**
 * @brief Macro to Check if a Value is Not a Valid LED State
 *
 * This macro checks if the given value is not a valid LED state by verifying
 * if it is not equal to LED_STATE_ON or LED_STATE_OFF.
 *
 * @param __STATE__ The value to be checked as a LED state.
 * @return 1 if the value is not a valid LED state, 0 otherwise.
 */
#define IS_NOT_LED_STATE(__STATE__)     ((__STATE__ != LED_STATE_ON) &&     \
                                            (__STATE__ != LED_STATE_OFF))


/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

/**
 * @brief External Declaration of LED Configuration Array
 *
 * This declaration makes the LED configuration array accessible from other
 * source files. The array contains configurations for all LEDs defined
 * in the system, including GPIO port, pin number, connection type, and default state.
 */
extern const LED_CFG_t LEDs[_LEDs_NUM];


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

LED_errorStatus LED_enuInit(void) {
   /* Temporary GPIO pin configuration structure */
   gpioPin_t pinCfg;

   LED_errorStatus RET_enuErrorStatus = LED_SUCCESS;
   uint8_t Wrong_Configuration = false;

   /* Iterate through each LED in the LEDs array */
   for (uint8_t ledIdx = 0; ledIdx < _LEDs_NUM && !Wrong_Configuration; ledIdx++) {
       /* Retrieve GPIO configuration from the LEDs array */
       pinCfg.GPIO_Pin = LEDs[ledIdx].GPIO_Pin;
       pinCfg.GPIO_Port = LEDs[ledIdx].GPIO_Port;

       /* Set desired GPIO configuration settings */
       pinCfg.GPIO_Speed   = GPIO_SPEED_VERY_HIGH;
       pinCfg.GPIO_Mode    = GPIO_MODE_OUT_PP;
       pinCfg.GPIO_AT_Type = GPIO_AT_None;

       /* Initialize the GPIO pin */
       if (GPIO_Init(&pinCfg) != SUCCESS) {
           RET_enuErrorStatus = LED_INITIALIZATION_FAILED;
           Wrong_Configuration = true;
       }
       else {
        /* No thing*/
       }
   }

   return RET_enuErrorStatus;
}


LED_errorStatus LED_enuSetStatus(uint8_t Led_Name, uint8_t LED_State) {
    LED_errorStatus RET_enuErrorStatus = LED_SUCCESS;

    /* Validate input arguments */
    if (IS_NOT_LED(Led_Name) || IS_NOT_LED_STATE(LED_State)) {
        RET_enuErrorStatus = LED_FAILED;
    } else {
        /* Get LED configuration from the LEDs array */
        LED_CFG_t led_config = LEDs[Led_Name];

        /* Set the GPIO pin based on the desired state and connection type */
        GPIO_SetPinValue(led_config.GPIO_Port, led_config.GPIO_Pin,
                         (uint32_t)(LED_State ^ led_config.LED_Connection));
    }

    return RET_enuErrorStatus;
}
/******************************************************************************/