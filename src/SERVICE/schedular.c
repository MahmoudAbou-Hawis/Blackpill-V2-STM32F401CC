/******************************************************************************/
/**
 * @file schedular.c
 * @brief Implementation of a simple scheduler for managing and executing tasks.
 *
 * @par Project Name
 * stm32fxx services
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file implements a basic scheduler that can be used to schedule tasks for repetitive
 * or delayed execution. Tasks are represented by the `Schedular_runnable_t` structure,
 * which defines properties like name, periodicity, priority, a callback function, and
 * an optional delay before the first execution. The scheduler provides functionality
 * to add, remove, and execute tasks based on their priorities and periodicities.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/


/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "schedular.h"
#include "schedular_CFG.h"
#include "stm32f4xx_systick.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

#define IS_RUNNABLE_WILL_EXECUTE_NOW(RunnableIdx)  \
                            (RemainingTimeForAllRunnables[RunnableIdx]  == 0)

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


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

/**
 * @brief An array to store the remaining execution time for all runnable tasks.
 * 
 * This array likely keeps track of the time remaining for all runnables.
 */
static uint32_t RemainingTimeForAllRunnables[MAX_RUNNABLES];

/**
 * @brief Track if the tasks is pending.
 */
static volatile uint8_t PendingRunnables = 0;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/**
 *@brief Array of runnable tasks defined in schedular_CFG.c (read-only)
 */
extern const Schedular_runnable_t AllRunnablesSystemList[MAX_RUNNABLES];

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

/**
 * @brief Callback function executed by the system tick handler.
 *
 * This function is invoked periodically at a rate determined by the configuration.
 * 
 */
static void TickCB(void)
{
    /** The scheduler must now execute the runnables.  */
    PendingRunnables++;
}

/**
 * @brief Schedules and executes a runnable based on its priority and periodicity.
 */
static void Schedular(void)
{
    uint32_t CurrentRunnable ;
    /**
     * Looping through all runnables to update the remaining time for each runnable
     * and calling the runnable if the remaining time has ended.
     */
    for(CurrentRunnable = 0 ; CurrentRunnable < MAX_RUNNABLES ; CurrentRunnable++)
    {
        if(IS_RUNNABLE_WILL_EXECUTE_NOW(CurrentRunnable))
        {
            /** Executes the runnable if the designated time has arrived. */
            AllRunnablesSystemList[CurrentRunnable].CallBack();
            RemainingTimeForAllRunnables[CurrentRunnable] =
                            AllRunnablesSystemList[CurrentRunnable].periodicityMS;
        }
        /**update the remaining time for the runnable */
        RemainingTimeForAllRunnables[CurrentRunnable] -= TICK_TIME;
    }
}

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
void schedular_init(void)
{
    /** make the remaining time equal to the delay function */
    for(uint32_t runnable = 0 ; runnable < MAX_RUNNABLES ; runnable++)
    {
        RemainingTimeForAllRunnables[runnable] = 
                                AllRunnablesSystemList[runnable].DelayMS;
    }
    SysTick_CFG_t SysTickConf = 
    {
        .CLK = SYS_CLK,
        .CLKSOURCE = SYSTICK_CLKSRC_AHB_DIV_8
    };

    /**configure the sys timer */
    SysTick_Config(&SysTickConf);
    SysTick_SetTimeMS(TICK_TIME);
    SysTick_SetCallback(TickCB);
}

void schedular_start(void)
{
    SysTick_Start();
    while(1)
    {
        if(PendingRunnables)
        {
            Schedular();
            PendingRunnables--;
        }
        else
        {
            
        }
    }
}

/******************************************************************************/