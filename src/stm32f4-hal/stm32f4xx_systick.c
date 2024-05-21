/******************************************************************************/
/**
 * @file stm32f4xx_systick.c
 * @brief SYSTICK peripheral driver implementation for stm32f401cc.
 *
 * This file implements functions to configure, start, and interact with
 * the SYSTICK peripheral for providing system timing and delay functionalities
 * on stm32f401cc.
 *
 * @par Project Name
 * STM32F4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the implementation of a driver for the SYSTICK peripheral.
 * It provides functions to:
 *   - Configure the SYSTICK clock source and reload value.
 *   - Start the SYSTICK counter for generating system timing interrupts.
 *   - Optionally set a callback function for handling SYSTICK interrupts.
 *
 * @par Usage
 *
 * This driver provides functions to configure, start, and interact with the 
 * SYSTICK peripheral.
 * 
 * Here's a summary of the functions and their usage:
 *
 *  1. **SysTick_Config(SysTick_CFG_t *SysTickCFG):**
 *     - This function configures the SYSTICK peripheral based on the provided 
 *       settings in the `SysTickCFG` structure. It sets the clock source,
 *       and enables interrupt generation (if applicable).
 *     - Call this function before using any other SYSTICK functionalities.
 *
 *  2. **SysTick_Start(void):**
 *     - This function starts the SYSTICK counter and initiates its countdown. 
 *       After the configured reload value is reached, a system tick interrupt 
 *       will be generated.
 *     - Ensure successful configuration using `SysTick_Config(...)`
 *       before calling this function.
 *
 *  3. **SysTick_SetTimeMS(uint32_t Time):**
 *     - This function sets the reload value and counter value of the SYSTICK 
 *       peripheral to the provided time in milliseconds. It calculates the 
 *       reload value based on the time and configured clock frequency 
 *       (`CLK` from `SysTickCFG`).
 *     - The SYSTICK peripheral must be properly configured using 
 *      `SysTick_Config(...)` before calling this function.
 *
 *  4. **SysTick_SetCallback(SysTickCB_t pCallBackFunction):** 
 *     - This function allows registering a callback function 
 *       (`pCallBackFunction`) to be invoked when a SYSTICK interrupt occurs.
 *       The callback function is responsible for handling the interrupt and
 *       performing any necessary actions.
 *     - Refer to the function documentation for details on the expected 
 *       callback function format.
 *
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 *
 */
/******************************************************************************/


/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "stm32f4xx_systick.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/**
 * @brief  Defines 'read / write' structure member permissions.
 */
#define     __IOM    volatile      
   
/**
 * @brief Defines 'read only' structure member permissions.
 */
#define     __IM     volatile const     

/**
 * @brief  SysTick CTRL CLKSOURCE Position
 */
#define SysTick_CTRL_CLKSOURCE_Pos          2U                                            

/**
 * SysTick CTRL CLKSOURCE Mask
 */
#define SysTick_CTRL_CLKSOURCE_Msk         (1UL << SysTick_CTRL_CLKSOURCE_Pos)            

/**
 * @brief SysTick CTRL TICKINT Position
 */
#define SysTick_CTRL_TICKINT_Pos            1U           

/**
 *@brief  SysTick CTRL TICKINT Mask
 */
#define SysTick_CTRL_TICKINT_Msk           (1UL << SysTick_CTRL_TICKINT_Pos)            

/**
 * @brief SysTick CTRL ENABLE Position
 */
#define SysTick_CTRL_ENABLE_Pos             0U         

/**
 * @brief SysTick CTRL ENABLE Mask 
 */
#define SysTick_CTRL_ENABLE_Msk            (1UL)          

/**
 * @brief SysTick LOAD RELOAD Position 
 */
#define SysTick_LOAD_RELOAD_Pos             0U   

/**
 * @brief SysTick LOAD RELOAD Mask
 */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFFUL)   

/**
 * @brief SysTick Base address.
 */
#define     SYSTICK     ((SysTick_t * const)0xE000E010)
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

/**
 * @brief Macro used to Check if the provided parameter is equal to NULL.
 */
#define  IS_NULL_PARAM(_PTR)                   (_PTR == NULL)

/**
 * @brief Macro used to Check if the provided time is not valid.
 */
#define  IS_NOT_VALID_TIME(_TIME)              (_TIME == 0)


/**
 * @brief Macro used to check if the provided system clock is not valid.
 */
#define IS_NOT_INVALID_SYS_CLK(_CLK)           (_CLK == 0)

/**
 * @brief Macro Used to convert clk from Hertz (HZ) to kilo Hertz(KHZ). 
 */
#define CONVERT_FROM_HZ_TO_KHZ(_CLK)            (_CLK / 1000U)


/**
 * @brief Macro to calculate the clock frequency after applying a prescaler.
 */
#define GET_CLK_AFTER_PRESCALER(_CLK)            (_CLK / 8U)
/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/**
 * @typedef SysTick_t
 * @brief Structure representing the SYSTICK peripheral registers.
 *
 * @par This structure defines members corresponding to the registers of the SYSTICK 
 * peripheral. These registers are used to configure, control, and access the 
 * SYSTICK counter for system timing functionalities.
 **/
typedef struct
{
  __IOM uint32_t CTRL;                   /** SysTick Control and Status Register */
  __IOM uint32_t LOAD;                   /** SysTick Reload Value Register */
  __IOM uint32_t VAL;                    /** SysTick Current Value Register */
  __IM  uint32_t CALIB;                  /** SysTick Calibration Register */
} SysTick_t;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

/**
 * @brief Contains the system clock frequency in Hertz (Hz)
 */
static uint32_t CLK = 0; 

/**
 * @brief Contains the time in MilliSeconds (MS).
 */
static uint32_t TimeMS = 0;

/**
 * @brief Contains the callback function called in each SysTick interrupt.
 */
static SysTickCB_t CallBack = NULL;
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

SysTick_ErrorStatus_t SysTick_Config(SysTick_CFG_t * SysTickCFG)
{
    SysTick_ErrorStatus_t RET_ErrorStatus = SYSTICK_OK;
    if(IS_NULL_PARAM(SysTickCFG))
    {
        RET_ErrorStatus = SYSTICK_NULL_PTR_PASSED;
    }
    else if(IS_NOT_INVALID_SYS_CLK(SysTickCFG->CLK))
    {
        RET_ErrorStatus = SYSTICK_NOT_OK;
    }
    else
    {
        CLK = SysTickCFG->CLK;
        
        switch (SysTickCFG->CLKSOURCE)
        {
        case SYSTICK_CLKSRC_PROC_CLK:
            /**  Processor clock (AHB) is the clock source */
            SYSTICK->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; 
            break;
        case SYSTICK_CLKSRC_AHB_DIV_8:
            /**  (AHB / 8) is the clock source */
            SYSTICK->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
            CLK = GET_CLK_AFTER_PRESCALER(CLK);
            break;
        default:
            /** An Error occur */
            RET_ErrorStatus = SYSTICK_NOT_OK;
            break;
        }
    }
    return RET_ErrorStatus;
}

SysTick_ErrorStatus_t SysTick_SetTimeMS(uint32_t Time)
{
    SysTick_ErrorStatus_t RET_ErrorStatus = SYSTICK_OK;
    if(IS_NOT_VALID_TIME(Time))
    {
        RET_ErrorStatus = SYSTICK_NOT_OK;
    }
    else
    {
        /** valid Time must be at maximum 0xFFFFFF */
        Time &= SysTick_LOAD_RELOAD_Msk;
        /**Load the number of ticks on load register */
        SYSTICK->LOAD = CONVERT_FROM_HZ_TO_KHZ(CLK) * Time;
        /**Used to check the user assign time to start or not */
        TimeMS = CONVERT_FROM_HZ_TO_KHZ(CLK) * Time;
    }
    return RET_ErrorStatus;
}

SysTick_ErrorStatus_t SysTick_Start(void)
{
    SysTick_ErrorStatus_t RET_ErrorStatus = SYSTICK_OK;
    if(IS_NOT_INVALID_SYS_CLK(CLK))
    {
        RET_ErrorStatus = SYSTICK_NOT_OK;
    }
    if(IS_NOT_VALID_TIME(TimeMS))
    {
        RET_ErrorStatus = SYSTICK_NOT_OK;
    }
    else
    {
        /**Clear timer Counter register */
        SYSTICK->VAL   = 0UL;   
        /** Enable the exception request and enable the timer */
        SYSTICK->CTRL |= (SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);                    
    }
    return RET_ErrorStatus;
}

SysTick_ErrorStatus_t SysTick_SetCallback(SysTickCB_t pCallBackFunction)
{
    SysTick_ErrorStatus_t RET_ErrorStatus = SYSTICK_OK;
    if(IS_NULL_PARAM(pCallBackFunction))
    {
        RET_ErrorStatus = SYSTICK_NOT_OK;
    }
    else
    {
        /** Set the callback */
        CallBack = pCallBackFunction; 
    }
    return RET_ErrorStatus;
}

SysTick_ErrorStatus_t SysTick_DelayMicroSeconds(uint32_t Time)
{
    SYSTICK->VAL   = 0UL;   
    SYSTICK->CTRL |=  (SysTick_CTRL_ENABLE_Msk);
    uint32_t cnt = 0;  
    uint32_t last = 0;
    uint32_t current = 0;
    while(cnt < Time)
    {
        current = SYSTICK->VAL;
        if(current - last >= 8)
        {
            cnt++;
            last = current;
        }
    }
    return SYSTICK_OK;
}

void SysTick_Handler(void)
{
    if(!IS_NULL_PARAM(CallBack))
    {
        CallBack();
    }
}
/******************************************************************************/