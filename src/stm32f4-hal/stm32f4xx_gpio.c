/******************************************************************************/
/**
 * @file gpio.c
 * @brief GPIO driver implementation for STM32F4xx microcontrollers.
 *
 * @par Project Name
 * stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the implementation of a GPIO driver for STM32F4xx
 * microcontrollers. It provides functions to initialize GPIO pins, set pin
 * modes (input/output/alternate function/analog), read and write pin values,
 * and configure pin pull-up/pull-down resistors.
 *
 * @par Usage
 * To use this GPIO driver:
 * 1. Include "stm32f4xx_gpio.h" in your project.
 * 2. Ensure that the RCC (Reset and Clock Control) peripheral is enabled for
 *    the GPIO port you want to use. You can do this by calling the
 *    appropriate RCC peripheral enable function. For example, to enable GPIOA,
 *    use RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);.
 * 3. Initialize the GPIO pin(s) you want to use by calling GPIO_Init().
 * 4. Use GPIO_SetPinValue() to set the output value of the pin(s) (if configured as output).
 * 5. Use GPIO_GetPinValue() to read the input value of the pin(s) (if configured as input).
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/

#include "stm32f4xx_gpio.h"

/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

#define ANALOG_MODE                    3U

#define ALTERNATE_FUNCTION_MODE        2U

#define OUTPUT_MODE                    1U

#define INPUT_MODE                     0U

#define PULLUP_MODE                    1U

#define PULLDOWN_MODE                  2U

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

#define IS_GPIO_PIN(__VALUE__)      ((((uint8_t)0) <= (__VALUE__)) && ((__VALUE__) <= (GPIO_PIN15)))


#define IS_GPIO_SPEED(__SPEED__)    (((__SPEED__) == GPIO_SPEED_LOW)    ||\
                                     ((__SPEED__) == GPIO_SPEED_MEDIUM) ||\
                                     ((__SPEED__) == GPIO_SPEED_HIGH)   ||\
                                     ((__SPEED__) == GPIO_SPEED_VERY_HIGH))

#define IS_GPIO_MODE(__MODE__)     (((__MODE__) == GPIO_MODE_OUT_PP)     || \
                                    ((__MODE__) == GPIO_MODE_OUT_OD)     || \
                                    ((__MODE__) == GPIO_MODE_IN_PU)      || \
                                    ((__MODE__) == GPIO_MODE_IN_PD)      || \
                                    ((__MODE__) == GPIO_MODE_IN_FLG)     || \
                                    ((__MODE__) == GPIO_MODE_AM)         || \
                                    ((__MODE__) == GPIO_MODE_AF0)        || \
                                    ((__MODE__) == GPIO_MODE_AF1)        || \
                                    ((__MODE__) == GPIO_MODE_AF2)        || \
                                    ((__MODE__) == GPIO_MODE_AF3)        || \
                                    ((__MODE__) == GPIO_MODE_AF4)        || \
                                    ((__MODE__) == GPIO_MODE_AF5)        || \
                                    ((__MODE__) == GPIO_MODE_AF6)        || \
                                    ((__MODE__) == GPIO_MODE_AF7)        || \
                                    ((__MODE__) == GPIO_MODE_AF8)        || \
                                    ((__MODE__) == GPIO_MODE_AF9)        || \
                                    ((__MODE__) == GPIO_MODE_AF10)       || \
                                    ((__MODE__) == GPIO_MODE_AF11)       || \
                                    ((__MODE__) == GPIO_MODE_AF12)       || \
                                    ((__MODE__) == GPIO_MODE_AF13)       || \
                                    ((__MODE__) == GPIO_MODE_AF14)       || \
                                    ((__MODE__) == GPIO_MODE_AF15))

#define IS_GPIO_INSTANCE(__GPIOx__) (((__GPIOx__) == GPIO_PORTA)        || \
                                     ((__GPIOx__) == GPIO_PORTB)        || \
                                     ((__GPIOx__) == GPIO_PORTC)        || \
                                     ((__GPIOx__) == GPIO_PORTD)        || \
                                     ((__GPIOx__) == GPIO_PORTE)        || \
                                     ((__GPIOx__) == GPIO_PORTH))



#define IS_ALTERNATE_TYPE(__AT__)    (((__AT__) == GPIO_AT_None)        || \
                                      ((__AT__) == GPIO_AT_PullUp)      || \
                                      ((__AT__) == GPIO_AT_PullDown)    || \
                                      ((__AT__) == GPIO_AT_OpenDrain)   || \
                                      ((__AT__) == GPIO_AT_PushPull))


#define IS_GPIO_STATE(__STATE__)    (((__STATE__) == GPIO_STATE_RESET) || ((__STATE__) == GPIO_STATE_SET))


#define GET_MODE(__MODE__)           ((__MODE__ & 0x00000003U))

#define IS_ALTERNATE_FUNC(__MODE__)  (GET_MODE(__MODE__) == 0x00000002U)

#define GET_MODE_CFG_VAL(__VALUE__)  ((__VALUE__ & 0x0000F000U) >> 12)

#define IS_ANALOG_MODE(__MODE__)     (GET_MODE(__MODE__) == 0x00000003U)

#define IS_INPUT_MODE(__MODE__)      (GET_MODE(__MODE__) == 0x00000000U)

#define IS_OUTPUT_MODE(__MODE__)     (GET_MODE(__MODE__) == 0x00000001U)

#define CLR_PIN_MODE_CFG(__MODE__, __PIN__) ((__MODE__) &= ~(3U << ((__PIN__) * 2U)))

#define CLR_PIN_AF_CFG(__VALUE__, __PIN__)  ((__VALUE__) &= ~(0xFU << ((__PIN__) * 4U)))

#define CLR_PIN_OUT_CFG(__VALUE__, __PIN__)  ((__VALUE__) &= ~(1U << (__PIN__)))

#define CLR_PIN_IN_CFG(__VALUE__, __PIN__)   ((__VALUE__) &= ~(3U << ((__PIN__) * 2U)))

#define CLR_PIN_SPEED(__VALUE__, __PIN__)    ((__VALUE__) &= ~(3U << ((__PIN__) * 2U)))

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

typedef struct {
    volatile uint32_t MODER;    /**< GPIO port mode register */
    volatile uint32_t OTYPER;   /**< GPIO port output type register */
    volatile uint32_t OSPEEDR;  /**< GPIO port output speed register */
    volatile uint32_t PUPDR;    /**< GPIO port pull-up/pull-down register */
    volatile uint32_t IDR;      /**< GPIO port input data register */
    volatile uint32_t ODR;      /**< GPIO port output data register */
    volatile uint32_t BSRR;     /**< GPIO port bit set/reset register */
    volatile uint32_t LCKR;     /**< GPIO port configuration lock register */
    volatile uint32_t AFR[2];   /**< GPIO alternate function low/high register */
    volatile uint32_t BRR;      /**< GPIO port bit reset register */
} GPIO;

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

GPIO_enuErrorStatus GPIO_Init(gpioPin_t * gpioPin)
{
    GPIO_enuErrorStatus RET_enuErrorStatus = GPIO_SUCCESS;
    
    /* Check the given pin configuration */
    if(!IS_GPIO_INSTANCE(gpioPin->GPIO_Port))
    {
        RET_enuErrorStatus = NOT_VALID_PORT;
    }
    else if(!IS_GPIO_MODE(gpioPin->GPIO_Mode))
    {
        RET_enuErrorStatus = NOT_VALID_MODE;
    }
    else if(!IS_GPIO_SPEED(gpioPin->GPIO_Speed))
    {
        RET_enuErrorStatus = NOT_VALID_SPEED;
    }
    else if(!IS_GPIO_PIN(gpioPin->GPIO_Pin))
    {
        RET_enuErrorStatus = NOT_VALID_PIN;
    }
    else if(!IS_ALTERNATE_TYPE(gpioPin->GPIO_AT_Type))
    {
        RET_enuErrorStatus = NOT_VALID_AT_TYPE;
    }
    else
    {
        /** */
        GPIO * const gpio = (GPIO*)(gpioPin->GPIO_Port);
        /** Set the pin mode */
        uint32_t mode = gpio->MODER;

        CLR_PIN_MODE_CFG(mode,gpioPin->GPIO_Pin);

        if(IS_ANALOG_MODE(gpioPin->GPIO_Mode))
        {
            mode |= (ANALOG_MODE << (gpioPin->GPIO_Pin * 2));
        }
        else if(IS_ALTERNATE_FUNC(gpioPin->GPIO_Mode))
        {
            mode |= (ALTERNATE_FUNCTION_MODE << (gpioPin->GPIO_Pin * 2));

            uint32_t alternate_function = gpio->AFR[(gpioPin->GPIO_Pin/8)];

            CLR_PIN_AF_CFG(alternate_function,(gpioPin->GPIO_Pin % 8));

            alternate_function |= 
                                (GET_MODE_CFG_VAL(gpioPin->GPIO_Mode) << ((gpioPin->GPIO_Pin %8) *4 ));
            
            gpio->AFR[(gpioPin->GPIO_Pin/8)] = alternate_function;
            
            
            /** Used if the alternate function is pullup or pull down */
            uint32_t input_mode = gpio->PUPDR;
            CLR_PIN_IN_CFG(input_mode,gpioPin->GPIO_Pin);
            
            switch (gpioPin->GPIO_AT_Type)
            {
            case GPIO_AT_OpenDrain:
                gpio->OTYPER |= (1 << gpioPin->GPIO_Pin);
                break;

            case GPIO_AT_PullUp:
                input_mode |= ( PULLUP_MODE << (gpioPin->GPIO_Pin *2));
                gpio->PUPDR = input_mode;
                break;

            case GPIO_AT_PullDown:
                input_mode |= ( PULLDOWN_MODE << (gpioPin->GPIO_Pin *2));
                gpio->PUPDR = input_mode;
                break;

            case GPIO_AT_PushPull:
                gpio->OTYPER &= ~(1 << gpioPin->GPIO_Pin);
                break;
            default:
                break;
            }
        }
        else if(IS_OUTPUT_MODE(gpioPin->GPIO_Mode))
        {
            mode |= (OUTPUT_MODE << (gpioPin->GPIO_Pin * 2));

            uint32_t output_mode = gpio->OTYPER;

            CLR_PIN_OUT_CFG(output_mode,gpioPin->GPIO_Pin);

            output_mode |= (GET_MODE_CFG_VAL(gpioPin->GPIO_Mode) << gpioPin->GPIO_Pin);

            gpio->OTYPER = output_mode;
        }
        else
        {
            mode |= (INPUT_MODE << (gpioPin->GPIO_Pin * 2));

            uint32_t input_mode = gpio->PUPDR;

            CLR_PIN_IN_CFG(input_mode,gpioPin->GPIO_Pin);

            input_mode |= (GET_MODE_CFG_VAL(gpioPin->GPIO_Mode) << (gpioPin->GPIO_Pin *2));

            gpio->PUPDR = input_mode;
        }
        gpio->MODER = mode;

        uint32_t pin_speed = gpio->OSPEEDR;

        CLR_PIN_SPEED(pin_speed,gpioPin->GPIO_Pin);

        pin_speed |= (gpioPin->GPIO_Speed << (gpioPin->GPIO_Pin *2));

        gpio->OSPEEDR = pin_speed;
    }

    return RET_enuErrorStatus;
}

GPIO_enuErrorStatus GPIO_SetPinValue(void *GPIO_Port, uint8_t GPIO_Pin, uint32_t GPIO_State)
{
    /* Initialize return status to success */
    GPIO_enuErrorStatus RET_enuErrorStatus = GPIO_SUCCESS;

    /* Validate input arguments */
    if (!IS_GPIO_INSTANCE(GPIO_Port))
    {
        RET_enuErrorStatus = NOT_VALID_PORT;
    }
    else if (!IS_GPIO_PIN(GPIO_Pin))
    {
        RET_enuErrorStatus = NOT_VALID_PIN;
    }
    else if (!IS_GPIO_STATE(GPIO_State))
    {
        RET_enuErrorStatus = NOT_VALID_STATUS;
    }
    else
    {
        /* Set pin value using BSRR register */
        ((GPIO *const)(GPIO_Port))->BSRR |= (1 << (GPIO_Pin + (GPIO_State * 16)));
    }

    return RET_enuErrorStatus;
}

GPIO_enuErrorStatus GPIO_GetPinValue(void *GPIO_Port, uint8_t GPIO_Pin, uint32_t *value)
{
    GPIO_enuErrorStatus RET_enuErrorStatus = GPIO_SUCCESS;

    /* Validate input arguments */
    if (!IS_GPIO_INSTANCE(GPIO_Port))
    {
        RET_enuErrorStatus = NOT_VALID_PORT;
    }
    else if (!IS_GPIO_PIN(GPIO_Pin))
    {
        RET_enuErrorStatus = NOT_VALID_PIN;
    }
    else if (value == NULL)
    {
        RET_enuErrorStatus = NULL_PTR_PASSED;
    }
    else
    {
        /* Retrieve pin value from the input data register */
        *value = (((((GPIO *)GPIO_Port)->IDR) >> GPIO_Pin) & 1U);
    }

    return RET_enuErrorStatus;
}
/******************************************************************************/