/******************************************************************************/
/**
 * @file switch.c
 * @brief Source file for switch control in the system.
 *
 * @par Project Name
 * Embedded Switch Control System
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This source file contains the implementations of functions for controlling switches
 * in the embedded system.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/


/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "switch.h"
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
 * @brief Macro to Check if a Value is Not a Valid Switch Identifier
 *
 * This macro checks if the given value is not a valid switch identifier by verifying
 * if it is less than zero or greater than or equal to the total number of switches
 * defined in the system.
 *
 * @param __SWITCH__ The value to be checked as a switch identifier.
 * @return 1 if the value is not a valid switch identifier, 0 otherwise.
 */
#define IS_NOT_SWITCH(__SWITCH__)             ((__SWITCH__ < 0) || (__SWITCH__ >= _SWITCHES_NUM))



/**
 * @brief Macro to Check if a Pointer is Null
 *
 * This macro checks if the given pointer is null.
 *
 * @param __PTR__ The pointer to be checked.
 * @return 1 if the pointer is null, 0 otherwise.
 */
#define IS_NULL(__PTR__)                  ((__PTR__) == NULL)



#define     STABLE_READ                     5

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/
typedef struct 
{
    uint32_t previous;
    uint32_t Counts;
    uint32_t CurrentState;
} SwitchStatusBlock;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

static SwitchStatusBlock SwitchesStatus[_SWITCHES_NUM];

/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/**
 * @brief External Declaration of Switch Configuration Array
 *
 * This declaration makes the switch configuration array accessible from other
 * source files. The array contains configurations for all switches defined
 * in the system, including GPIO port, pin number, and connection type (pull-up or pull-down).
 */
extern const SWITCH_CFG_t switches[_SWITCHES_NUM];

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

SWITCH_errorStatus SWITCH_enuInit(void) {
   /* Temporary GPIO pin configuration structure */
   gpioPin_t pinCfg;

   SWITCH_errorStatus RET_enuErrorStatus = SWITCH_SUCCESS;
   uint8_t Wrong_Configuration = false;

   /* Iterate through each switch in the switches array */
   for (uint8_t switchIdx = 0; switchIdx < _SWITCHES_NUM && !Wrong_Configuration; switchIdx++) {
       /* Retrieve GPIO configuration from the switches array */
       pinCfg.GPIO_Pin = switches[switchIdx].GPIO_Pin;
       pinCfg.GPIO_Port = switches[switchIdx].GPIO_Port;
       pinCfg.GPIO_Mode = ((switches[switchIdx].SWITCH_Connection == SWITCH_CONNECTION_PULLUP) ?GPIO_MODE_IN_PU :GPIO_MODE_IN_PD);
       
       /* Set desired GPIO configuration settings */
       pinCfg.GPIO_Speed = GPIO_SPEED_VERY_HIGH;

       /** Pin is not alternate function*/
       pinCfg.GPIO_AT_Type = GPIO_AT_None;

        /**When starting the system all switches not pressed  it is the initial value*/
        SwitchesStatus[switchIdx].CurrentState = SWITCH_STATUS_NOT_PRESSED;
        SwitchesStatus[switchIdx].Counts = 0;
        SwitchesStatus[switchIdx].previous = 0;

       /* Initialize the GPIO pin */
       if (GPIO_Init(&pinCfg) != GPIO_SUCCESS) {
           RET_enuErrorStatus = SWITCH_CONFIGURATION_FAILED;
           Wrong_Configuration = true;
       }
       else {
        /* No thing*/
       }
   }

   return RET_enuErrorStatus;
}

SWITCH_errorStatus SWITCH_enuGetStatus(uint8_t switchName, 
                                       uint32_t *switchStatus) 
{
    SWITCH_errorStatus RET_enuErrorStatus = SWITCH_SUCCESS;    
    /* Validate input arguments */
    if (IS_NOT_SWITCH(switchName) || IS_NULL(switchStatus)) {
        RET_enuErrorStatus = SWITCH_FAILED;
    }
    else{
        /** get the current state of the switch. */
        *switchStatus = SwitchesStatus[switchName].CurrentState;
    }
    return RET_enuErrorStatus;
}

/**
 * @brief  This function(Runnable) is intended to be executed periodically
 *          by a scheduler, typically every 5 milliseconds.
 */
void CheckSwitchesStates(void)
{
    uint32_t  switchStatus;
    for(uint32_t switchIdx = 0 ; switchIdx < _SWITCHES_NUM ; switchIdx++)
    {
        /* Get switch configuration from the switches array */
        SWITCH_CFG_t switchConfig = switches[switchIdx];
        
        /* Set the GPIO pin based on the desired state and connection type */
        GPIO_GetPinValue(switchConfig.GPIO_Port, switchConfig.GPIO_Pin,
                         &switchStatus);

        switchStatus = (switchStatus ^ switchConfig.SWITCH_Connection); 

        if(switchStatus == SwitchesStatus[switchIdx].previous)
        {
            SwitchesStatus[switchIdx].Counts++;
        }
        else
        {
            SwitchesStatus[switchIdx].Counts = 0;
        }
        if(SwitchesStatus[switchIdx].Counts == STABLE_READ )
        {
            SwitchesStatus[switchIdx].CurrentState = switchStatus;
            SwitchesStatus[switchIdx].Counts = 0;
        }

        SwitchesStatus[switchIdx].previous = switchStatus;
    }
}

/******************************************************************************/