/*******************************************************************************/
/**
 * @file gpio.h
 * @brief Header file for STM32F4xx GPIO functionalities
 *
 * @par Project Name
 * stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines macros and functions for configuring and interacting with
 * GPIO pins on an STM32F4xx microcontroller. It aims to provide a clean and
 * efficient interface for your application.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef __STM32F4xx_GPIO_H
#define __STM32F4xx_GPIO_H
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


/******************************************************************************/
/*GPIO PORTS*/
/******************************************************************************/

/**
 * @brief Base address definition for GPIO Port A
 */
#define GPIO_PORTA            ((void *)0x40020000)

/**
 * @brief Base address definition for GPIO Port B
 */
#define GPIO_PORTB            ((void *)0x40020400)

/**
 * @brief Base address definition for GPIO Port C
 */
#define GPIO_PORTC            ((void *)0x40020800)

/**
 * @brief Base address definition for GPIO Port D
 */
#define GPIO_PORTD            ((void *)0x40020C00)

/**
 * @brief Base address definition for GPIO Port E
 */
#define GPIO_PORTE            ((void *)0x40021000)

/**
 * @brief Base address definition for GPIO Port H
 */
#define GPIO_PORTH            ((void *)0x40021C00)



/******************************************************************************/
/*GPIO PINS*/
/******************************************************************************/

/**
 * @brief GPIO Pin 0
 */
#define GPIO_PIN0             ((uint8_t)0)

/**
 * @brief GPIO Pin 1
 */
#define GPIO_PIN1            ((uint8_t)1)

/**
 * @brief GPIO Pin 2
 */
#define GPIO_PIN2             ((uint8_t)2)

/**
 * @brief GPIO Pin 3
 */
#define GPIO_PIN3             ((uint8_t)3)

/**
 * @brief GPIO Pin 4
 */
#define GPIO_PIN4             ((uint8_t)4)

/**
 * @brief GPIO Pin 5
 */
#define GPIO_PIN5             ((uint8_t)5)

/**
 * @brief GPIO Pin 6
 */
#define GPIO_PIN6             ((uint8_t)6)

/**
 * @brief GPIO Pin 7
 */
#define GPIO_PIN7             ((uint8_t)7)

/**
 * @brief GPIO Pin 8
 */
#define GPIO_PIN8             ((uint8_t)8)

/**
 * @brief GPIO Pin 9
 */
#define GPIO_PIN9             ((uint8_t)9)

/**
 * @brief GPIO Pin 10
 */
#define GPIO_PIN10            ((uint8_t)10)

/**
 * @brief GPIO Pin 11
 */
#define GPIO_PIN11            ((uint8_t)11)

/**
 * @brief GPIO Pin 12
 */
#define GPIO_PIN12            ((uint8_t)12)

/**
 * @brief GPIO Pin 13
 */
#define GPIO_PIN13            ((uint8_t)13)

/**
 * @brief GPIO Pin 14
 */
#define GPIO_PIN14            ((uint8_t)14)

/**
 * @brief GPIO Pin 15
 */
#define GPIO_PIN15            ((uint8_t)15)



/******************************************************************************/
/*GPIO MODES                                                                  */
/******************************************************************************/

/**
 * @defgroup GPIO_Modes GPIO Modes
 * @brief Definitions for GPIO pin modes
 * @{
 */

/**
 * @brief GPIO Mode for Output Push-Pull
 * Pins configured in this mode can output a signal that actively 
 * drives the pin high or low.
 */
#define GPIO_MODE_OUT_PP ((uint32_t)0x00040001)

/**
 * @brief GPIO Mode for Output Open-Drain
 * Pins configured in this mode can output a signal that actively 
 * drives the pin low.
 */
#define GPIO_MODE_OUT_OD ((uint32_t)0x00041001)

/**
 * @brief GPIO Mode for Input with Pull-Up
 * Pins configured in this mode are used as inputs with a pull-up
 * resistor enabled, ensuring a high state when no external signal is driving the pin.
 */
#define GPIO_MODE_IN_PU ((uint32_t)0x000C1000)

/**
 * @brief GPIO Mode for Input with Pull-Down
 * Pins configured in this mode are used as inputs with a pull-down resistor enabled, 
 * ensuring a low state when no external signal is driving the pin.
 */
#define GPIO_MODE_IN_PD ((uint32_t)0x000C2000)

/**
 * @brief GPIO Mode for Input Floating
 * Pins configured in this mode are used as inputs without pull-up or pull-down resistors,
 *  allowing the pin to float and be influenced by external factors.
 */
#define GPIO_MODE_IN_FLG ((uint32_t)0x000C0000)

/**
 * @brief GPIO Mode for Analog
 * Pins configured in this mode are used for analog input or output operations.
 */
#define GPIO_MODE_AM ((uint32_t)0x00000003)


/**
 * @brief GPIO Mode for Alternate Function 0 (System)
 */
#define GPIO_MODE_AF0 ((uint32_t)0x00200002)

/**
 * @brief GPIO Mode for Alternate Function 1 (TIM1/TIM2)
 */
#define GPIO_MODE_AF1 ((uint32_t)0x00201002)

/**
 * @brief GPIO Mode for Alternate Function 2 (TIM3/TIM4/TIM5)
 */
#define GPIO_MODE_AF2 ((uint32_t)0x00202002)

/**
 * @brief GPIO Mode for Alternate Function 3 (TIM9/TIM10/TIM11)
 */
#define GPIO_MODE_AF3 ((uint32_t)0x00203002)

/**
 * @brief GPIO Mode for Alternate Function 4 (I2C1/I2C2/I2C3)
 */
#define GPIO_MODE_AF4 ((uint32_t)0x00204002)

/**
 * @brief GPIO Mode for Alternate Function 5 (SPI1/SPI2/I2S2/SPI3/I2S3/SPI4)
 */
#define GPIO_MODE_AF5 ((uint32_t)0x00205002)

/**
 * @brief GPIO Mode for Alternate Function 6 (SPI2/I2S2/SPI3/I2S3)
 */
#define GPIO_MODE_AF6 ((uint32_t)0x00206002)

/**
 * @brief GPIO Mode for Alternate Function 7 (USART1/USART2/USART6)
 */
#define GPIO_MODE_AF7 ((uint32_t)0x00207002)

/**
 * @brief GPIO Mode for Alternate Function 8 (I2C2/I2C3)
 */
#define GPIO_MODE_AF8 ((uint32_t)0x00208002)

/**
 * @brief GPIO Mode for Alternate Function 9 (OTG1_FS)
 */
#define GPIO_MODE_AF9 ((uint32_t)0x00209002)

/**
 * @brief GPIO Mode for Alternate Function 10 (SDIO)
 */
#define GPIO_MODE_AF10 ((uint32_t)0x0020A002)

/**
 * @brief GPIO Mode for Alternate Function 11 (Not specified)
 */
#define GPIO_MODE_AF11 ((uint32_t)0x0020B002)

/**
 * @brief GPIO Mode for Alternate Function 12 (Not specified)
 */
#define GPIO_MODE_AF12 ((uint32_t)0x0020C002)

/**
 * @brief GPIO Mode for Alternate Function 13 (Not specified)
 */
#define GPIO_MODE_AF13 ((uint32_t)0x0020D002)

/**
 * @brief GPIO Mode for Alternate Function 14 (Not specified)
 */
#define GPIO_MODE_AF14 ((uint32_t)0x0020E002)

/**
 * @brief GPIO Mode for Alternate Function 15 (Not specified)
 */
#define GPIO_MODE_AF15 ((uint32_t)0x0020F002)
/** @} */


/**
 * @defgroup GPIO_Alternate_Function GPIO Alternate Function type
 * @brief GPIO pin alternate function types
 * @{
 */
#define GPIO_AT_None        ((uint8_t)0)   /**< No alternate function */
#define GPIO_AT_PushPull    ((uint8_t)1)   /**< Push-pull output type */
#define GPIO_AT_OpenDrain   ((uint8_t)2)   /**< Open-drain output type */
#define GPIO_AT_PullUp      ((uint8_t)3)   /**< Pull-up input type */
#define GPIO_AT_PullDown    ((uint8_t)4)   /**< Pull-down input type */
/** @} */



/******************************************************************************/
/*GPIO PINS SPEED                                                             */
/******************************************************************************/

/**
 * @brief Low speed for GPIO pins
 * Pins configured with this speed setting have a low slew rate, 
 * suitable for low-speed applications or to reduce electromagnetic interference.
 */
#define GPIO_SPEED_LOW ((uint8_t)0)

/**
 * @brief Medium speed for GPIO pins
 * Pins configured with this speed setting have a moderate slew rate, 
 * suitable for general-purpose applications.
 */
#define GPIO_SPEED_MEDIUM ((uint8_t)1)

/**
 * @brief High speed for GPIO pins
 * Pins configured with this speed setting have a high slew rate, 
 * suitable for high-speed applications or when fast signal transitions are required.
 */
#define GPIO_SPEED_HIGH ((uint8_t)2)

/**
 * @brief Very high speed for GPIO pins
 * Pins configured with this speed setting have a very high slew rate, 
 * suitable for high-frequency applications or when very fast signal transitions are required.
 */
#define GPIO_SPEED_VERY_HIGH ((uint8_t)3)


#define GPIO_STATE_RESET    ((uint32_t)0x00000001)
#define GPIO_STATE_SET      ((uint32_t)0x00000000)
/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/


/**
 * @brief Enumeration for error status codes
 * This enumeration defines error status codes that can be returned by functions to indicate different types of errors.
 * - `NULL_PTR_PASSED`: Indicates that a null pointer was passed as an argument.
 * - `NOT_VALID_PIN`: Indicates that the provided GPIO pin number is not valid.
 * - `NOT_VALID_MODE`: Indicates that the provided GPIO mode is not valid.
 * - `NOT_VALID_PORT`: Indicates that the provided GPIO port is not valid.
 * - `NOT_VALID_SPEED`: Indicates that the provided GPIO speed setting is not valid.
 * - `SUCCESS`: Indicates successful completion of an operation.
 */
typedef enum
{
    GPIO_SUCCESS = 0,
    NULL_PTR_PASSED,
    NOT_VALID_PIN,
    NOT_VALID_MODE,
    NOT_VALID_PORT,
    NOT_VALID_SPEED,
    NOT_VALID_STATUS,
    NOT_VALID_AT_TYPE,
} GPIO_enuErrorStatus;



/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/


/**
 * @brief Structure for GPIO pin configuration
 * This structure defines the configuration parameters for a GPIO pin, including 
 * the port , pin number, speed setting, and mode setting.
 */
typedef struct 
{
    void *   GPIO_Port;    /**< Pointer to the GPIO port base address */
    uint8_t  GPIO_Pin;     /**< GPIO pin number */
    uint8_t  GPIO_Speed;   /**< Speed setting for the GPIO pin */
    uint32_t GPIO_Mode;    /**< Mode setting for the GPIO pin */
    uint8_t  GPIO_AT_Type; /**< GPIO pin alternate function type.
                             Refer to @ref GPIO_Alternate_Function */
} gpioPin_t;


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
 * @brief Initialize a GPIO pin
 * This function initializes a GPIO pin based on the configuration specified 
 * in the gpioPin_t structure.
 * 
 * @param gpio Pointer to a gpioPin_t structure containing the GPIO pin configuration.
 * 
  @return: Indicates the success or failure of the initialization process.
 *   - `SUCCESS`: The pin was initialized successfully.
 *   - `NOT_VALID_PORT`: The provided GPIO port instance is invalid.
 *   - `NOT_VALID_MODE`: The provided GPIO mode is invalid.
 *   - `NOT_VALID_SPEED`: The provided GPIO speed is invalid.
 *   - `NOT_VALID_PIN`: The provided GPIO pin number is invalid.
 *
 */
GPIO_enuErrorStatus GPIO_Init(gpioPin_t * gpioPin);

/**
 * @brief Set the value of a GPIO pin
 * This function sets the value (state) of a GPIO pin to the specified state (GPIO_STATE).
 * 
 * @param GPIO_Port Pointer to the base address of the GPIO port.
 * @param GPIO_Pin The number of the GPIO pin.
 * @param GPIO_State The state (high or low) to set the GPIO pin to.
 * 
 *@return: Indicates the success or failure of the operation.
 *   - `SUCCESS`: The pin value was set successfully.
 *   - `NOT_VALID_PORT`: The provided GPIO_Port pointer is invalid.
 *   - `NOT_VALID_PIN`: The provided GPIO_Pin number is invalid.
 *   - `NOT_VALID_STATUS`: The provided GPIO_State value is invalid.
 * 
 * @note you should init the pin first.
 */
GPIO_enuErrorStatus GPIO_SetPinValue(void * GPIO_Port, uint8_t GPIO_Pin, uint32_t GPIO_State);

/**
 * @brief Get the value of a GPIO pin
 * This function retrieves the current value (state) of a GPIO pin and stores it in the variable pointed to by 'value'.
 * 
 * @param GPIO_Port Pointer to the base address of the GPIO port.
 * @param GPIO_Pin The number of the GPIO pin.
 * @param value[in out] Pointer to a variable where the current state of the GPIO pin will be stored.
 * 
 * @return: Indicates the success or failure of the operation.
 *   - `SUCCESS`: The pin value was retrieved successfully.
 *   - `NOT_VALID_PORT`: The provided GPIO_Port pointer is invalid.
 *   - `NOT_VALID_PIN`: The provided GPIO_Pin number is invalid.
 *   - `NULL_PTR_PASSED`: The provided `value` pointer is NULL.
 * 
 * @note you should init the pin first.
 */
GPIO_enuErrorStatus GPIO_GetPinValue(void * GPIO_Port, uint8_t GPIO_Pin, uint32_t * value);


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
#endif /* __STM32F4xx_GPIO_H */
/******************************************************************************/
