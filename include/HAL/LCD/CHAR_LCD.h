/*******************************************************************************/
/**
 * @file LCD.h
 * @brief Header file for Liquid Crystal Display (LCD) control functions.
 *
 * This header file provides function prototypes and definitions for
 * interacting with a Liquid Crystal Display (LCD) module. 
 * 
 * @par Project Name
 * LCD Project.
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines functions for initializing the LCD, sending commands
 * and data, clearing the display, setting cursor position.
 *
 * @par Author
 * @MahmoudAbou-Hawis
 *
 * @date [19-3-2024]
 *
 *******************************************************************************/


/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef LCD_H_
#define LCD_H_
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
 * @brief  LCD command for clear display.
 */
#define  CMD_CLEAR_DISPLAY                        ((uint8_t)0x1)

/**
 * @brief  LCD command for return home.
 */
#define  CMD_RETURN_HOME                          ((uint8_t)0x2)


/**
 * @brief LCD command for shift display left.
 */
#define  CMD_SHIFT_LEFT                           ((uint8_t)0x10)

/**
 * @brief LCD command for shift display right.
 */
#define  CMD_SHIFT_RIGHT                          ((uint8_t)0x14)

/**
 * @brief LCD command for shift entire display left.
 */
#define  CMD_SHIFT_ENTIRE_DISPLAY_LEFT            ((uint8_t)0x18)

/**
 * @brief LCD command for shift entire display right.
 */
#define  CMD_SHIFT_ENTIRE_DISPLAY_RIGHT           ((uint8_t)0x1C)

/**
 * @brief LCD command for Enable cursor and blinking.
 */
#define  CMD_CURSOR_BLINKING                       ((uint8_t)0x0B)

/**
 * @brief LCD command for Disable cursor and blinking.
 */
#define  CMD_CURSOR_NOT_BLINKING                    ((uint8_t)0x08)

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/**
 * @typedef LCD_ErrorStatus_t
 * @brief An enumeration defining error status codes returned by LCD functions.

 * This enumeration (`LCD_ErrorStatus_t`) defines the possible return values from LCD functions 
 * to indicate the outcome of the operation.

 * Values:
 *   - `LCD_ERROR_NONE`: Indicates successful execution of the function.
 *   - `LCD_ERROR`: A generic error occurred during function execution. Refer to the specific 
 *     function documentation for more details about potential error scenarios.
 *   - `LCD_ERROR_INVALID_PARAM`: An invalid parameter was passed to the function.
 *   - `LCD_NULL_PTR_PASSED`: A null pointer was passed to the function where a valid pointer 
 *     was expected.
 *   - `LCD_NOT_INITIALIZED`: The LCD interface was not properly initialized before attempting 
 *     to use an LCD function. Make sure to call `LCD_InitAsync` before using other functions.
 *   - `LCD_LAST_REQUEST_PROCESSING_STILL_IN_EXECUTION`: An asynchronous operation is still 
 *     in progress from a previous function call.
 *    - `LCD_IS_OFF` :Indicates that the liquid crystal display (LCD) is  
 *      off and Can't displaying any New content.
 */
typedef enum
{
    LCD_ERROR_NONE,
    LCD_ERROR,
    LCD_ERROR_INVALID_PARAM,
    LCD_NULL_PTR_PASSED,
    LCD_NOT_INITIALIZED,
    LCD_LAST_REQUEST_PROCESSING_STILL_IN_EXECUTION,
    LCD_IS_OFF
} LCD_ErrorStatus_t;

/**
 * @typedef LCD_States_t
 * @brief Enumeration defining possible states of the LCD controller.

 * This enumeration (`LCD_States_t`) defines the different states the LCD controller 
 * can be in.

 * Values:
 *   - `INITIALIZATION_STATE`: The LCD is undergoing initialization. Communication 
 *     with the LCD may be limited or restricted during this state.
 *   - `OPERATIONAL_STATE`: The LCD is fully initialized and ready for normal 
 *     operations like sending commands, setting cursor position, and writing strings.
 *   - `OFF_STATE`: The LCD display is turned off. 
 */
typedef enum
{
    INITIALIZATION_STATE,
    OPERATIONAL_STATE,
    OFF_STATE
} LCD_States_t;

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @typedef CallBack
 * @brief Callback function pointer type definition for LCD functions.
*/
typedef void (*CallBack)(void);

/**
 * @brief LCD Configuration Structure
 * 
 * This structure defines the configuration for an LCD, including the GPIO port,
 * pin number.
 */
typedef struct
{
    void *  GPIO_Port;      /**< Pointer to the GPIO port used by the LED */
    uint8_t GPIO_Pin;       /**< Pin number of the LED */
} LCD_CFG_t;

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
 * @brief Initializes the LCD asynchronously.

 * This function initializes the LCD display in an asynchronous manner. 
 * Asynchronous means the function will return immediately after starting the
 * initialization process and will not wait for it to complete. The completion
 * status will be communicated through the provided callback function (`CB`).
 *
 * @param CB: The callback function to be called when the initialization is complete.
 *
 * @return : An `LCD_ErrorStatus_t` value indicating whether the function was able to
 *          start the asynchronous initialization process successfully or not. 
 * 
 * @note  It is mandatory to call this function before using any LCD APIs.
 */
LCD_ErrorStatus_t LCD_InitAsync(CallBack CB);

/**
 * @brief Sends a command to the LCD asynchronously.

 * This function sends  command (`cmd`) to the LCD display in an asynchronous manner.
 * Asynchronous means the function will return immediately after initiating the
 * command transfer and will not wait for it to complete. The completion status 
 * will be communicated through the provided callback function (`CB`).

 * @param cmd: command to be sent to the LCD. 

 * @param CB: The callback function to be called when the command transfer is complete.



 * @return : An `LCD_ErrorStatus_t` value indicating whether the function was able to
 *              start the asynchronous command transfer process successfully. 
 *                - `LCD_ERROR_NONE`: The command transfer process was started successfully.
 *                - `LCD_ERROR` : The command transfer process failed to start.
 */ 
LCD_ErrorStatus_t LCD_SendCommandAsync(uint8_t CMD, CallBack CB);


/**
 * @brief Sets the cursor position on the LCD asynchronously.

 * This function sets the cursor position on the LCD display in an asynchronous manner.
 * The cursor position is defined by two parameters: `Pos_X` (horizontal position) 
 * and `Pos_Y` (vertical position). The function will return immediately after initiating 
 * the cursor position update and will not wait for it to complete. The completion status 
 * will be communicated through the provided callback function (`CB`).

 * @param Pos_X: The X-coordinate (horizontal position) of the new cursor location. 
 *               The valid range for this value depends on your configuration.
 * 
 * @param Pos_Y: The Y-coordinate (vertical position) of the new cursor location. 
 *               The valid range for this value depends on your configuration.
 * 
 * @param CB: The callback function to be called when the cursor position update is complete. 

 * @return: An `LCD_ErrorStatus_t` value indicating whether the function was able to
 *          start the asynchronous cursor position update process successfully. 
 *          - `LCD_ERROR_NONE`: The cursor position update process was started successfully.
 *          - `LCD_ERROR_INVALID_PARAM`: If the provided coordinates are outside the valid range.
 */
LCD_ErrorStatus_t LCD_SetCursorAsync(uint8_t Pos_X, uint8_t Pos_Y, CallBack CB);


/**
 * @brief Writes a string to the LCD asynchronously using a zero-copy method.

 * This function writes a string of characters (`string`) to the LCD display in an 
 * asynchronous manner. The function utilizes a zero-copy approach, which means it avoids 
 * unnecessary copying of the string data. The size of the string is provided in the 
 * `size` parameter. Similar to other functions, the function will return immediately 
 * after initiating the string writing process and will not wait for it to complete. 
 * The completion status will be communicated through the provided callback function (`CB`).

 * @param string: A pointer to the character array containing the string to be written.
 *             `Important:` The function assumes the caller is responsible for ensuring 
 *             the memory pointed to by `string` remains valid until the writing 
 *             operation is complete. Modifying the memory pointed to by `string` during 
 *             the writing process can lead to undefined behavior.
 * @param size : The size of the string (`string`) in number of characters .
 * 
 * @param CB : The callback function to be called when the string writing is complete.
 *
 * @return : An `LCD_ErrorStatus_t` value indicating whether the function was able to
 *          start the asynchronous string writing process successfully. 
 *          - `LCD_ERROR_NONE`: The string writing process was started successfully.
 *          - `LCD_NULL_PTR_PASSED` : The pointer passed to the string is NULL.
 */
LCD_ErrorStatus_t LCD_WriteStringAsyncZeroCopy(char *string, uint8_t size,
                                               CallBack CB);


/**
 * @brief Retrieves the current state of the LCD controller.
 *
 * This function (`LCD_GetState`) retrieves the current state of the LCD controller 
 * and stores it in the provided `LCDState` pointer. The function returns an 
 * `LCD_ErrorStatus_t` value indicating the outcome of the operation.
 *
 * @param LCDState: Pointer to a variable of type `LCD_States_t` where the current 
 *                   LCD state will be stored. The caller is responsible for ensuring 
 *                   that the provided pointer is valid memory.
 *
 * @return An `LCD_ErrorStatus_t` value indicating the outcome of the operation:
 *         - `LCD_ERROR_NONE`: The LCD state retrieval was successful.
 *         - `LCD_ERROR`: An error occurred while trying to retrieve the state 
 *            from the LCD controller.
 *         - `LCD_NULL_PTR_PASSED`: A null pointer was passed for the `LCDState` 
 *            argument.
 */
LCD_ErrorStatus_t LCD_GetState(LCD_States_t * LCDState);
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
#endif /* LCD_H_ */
/******************************************************************************/
