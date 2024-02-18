/*******************************************************************************/
/**
 * @file FILE.h
 * @brief 
 *
 * @par Project Name
 * 
 *
 * @par Code Language
 * C
 *
 * @par Description
 * 
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef SWITCH_H_
#define SWITCH_H_
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
#include "switch_cfg.h"
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/**
 * @brief Switch Connection Type: Pull-Up
 *
 * This macro defines the switch connection type as pull-up. When a switch is
 * configured with this connection type, it is connected to the GPIO pin with
 * a pull-up resistor.
 */
#define SWITCH_CONNECTION_PULLUP   ((uint8_t)1)

/**
 * @brief Switch Connection Type: Pull-Down
 *
 * This macro defines the switch connection type as pull-down. When a switch is
 * configured with this connection type, it is connected to the GPIO pin with
 * a pull-down resistor.
 */
#define SWITCH_CONNECTION_PULLDOWN ((uint8_t)0)

/**
 * @brief Switch Pressed Status
 *
 * This macro defines the status value indicating that a switch is pressed.
 */
#define SWITCH_STATUS_PRESSED       ((uint8_t)1)

/**
 * @brief Switch Not Pressed Status
 *
 * This macro defines the status value indicating that a switch is not pressed.
 */
#define SWITCH_STATUS_NOT_PRESSED   ((uint8_t)0)


/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/**
 * @brief Switch Error Status Enumeration
 *
 * This enumeration defines the possible error status values that can be returned
 * by switch-related functions. It includes the following values:
 * - SWITCH_SUCCESS: The operation was successful.
 * - SWITCH_CONFIGURATION_FAILED: Switch configuration failed.
 * - SWITCH_FAILED: General failure status.
 */
typedef enum
{
    SWITCH_SUCCESS,                 /**< Operation successful */
    SWITCH_CONFIGURATION_FAILED,    /**< Switch configuration failed */
    SWITCH_FAILED                   /**< General failure status */
} SWITCH_errorStatus;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief Switch Configuration Structure
 * 
 * This structure defines the configuration for a switch, including the GPIO port,
 * pin number, and connection type (pull-up or pull-down).
 */
typedef struct
{
    void *  GPIO_Port;          /**< Pointer to the GPIO port used by the switch */
    uint8_t GPIO_Pin;           /**< Pin number of the switch */
    uint8_t SWITCH_Connection;  /**< Type of switch connection (pull-up or pull-down) */
} SWITCH_CFG_t;


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
 * @brief Initialize the Switch Module
 *
 * This function initializes the switch module. It configures the GPIO pins and
 * sets up any necessary hardware for switch functionality. If initialization
 * is successful, it returns SWITCH_SUCCESS; otherwise, it returns an error status.
 *
 * @return SWITCH_errorStatus
 * - SWITCH_SUCCESS: The switch module was successfully initialized.
 * - SWITCH_CONFIGURATION_FAILED: Switch configuration failed.
 */
extern SWITCH_errorStatus SWITCH_enuInit(void);


/**
 * @brief Get the Status of a Switch
 *
 * This function retrieves the current status of the specified switch and stores
 * it in the provided pointer variable. The status indicates whether the switch
 * is pressed or not pressed. If the switch status is successfully retrieved,
 * it returns SWITCH_SUCCESS; otherwise, it returns an error status.
 *
 * @param switchName[in] The name or identifier of the switch.
 * @param switchStatus[in/out] Pointer to a variable where the switch status will be stored.
 * @return SWITCH_errorStatus
 * - SWITCH_SUCCESS: The switch status was successfully retrieved.
 * - SWITCH_FAILED: Failed to retrieve the switch status.
 */
extern SWITCH_errorStatus SWITCH_enuGetStatus(uint8_t switchName, 
                                              uint32_t *switchStatus);

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
#endif /* SWITCH_H_ */
/******************************************************************************/
