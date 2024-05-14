/******************************************************************************/
/**
 * @file schedular_CFG.c
 * @brief Configuration file for the scheduler.
 *
 * @par Project Name
 *  stm32fxx services
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file likely contains configuration settings for the scheduler,
 * allowing you to customize its behavior without modifying the core code.
 * These settings include all runnable configurations:
 *   - Periodic tick interval 
 *   - runnable priorities
 *   - runnable callback
 *   - runnable delay
 *   - runnable name 
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
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/


extern void CheckSwitchesStates(void);

extern void app(void);

extern void traffic_start(void);

extern void LCD_Runnable(void);

extern void runnable(void);

extern void CheckDoublePressed(void);

/**
 * @brief Array to store all runnable tasks in the system.
 *
 * @par This constant array `AllRunnableInSystemList` of type `Schedular_runnable_t`
 * holds up to `MAX_RUNNABLES` (defined in schedular_CFG.h) runnables  
 * These runnables are managed by the scheduler and will be scheduled for execution 
 * based on their priority and periodicity.
 */
const Schedular_runnable_t AllRunnablesSystemList[MAX_RUNNABLES] =
{
    [PRIORITY_0] =
    {
        .CallBack = CheckSwitchesStates,
        .DelayMS = 0,
        .periodicityMS = 5,
        .name = "LCD task"
    },
    [PRIORITY_1] =
    {
        .CallBack = app,
        .DelayMS = 100,
        .periodicityMS = 100,
        .name = "Check Double"
    }
};

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/


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

/******************************************************************************/