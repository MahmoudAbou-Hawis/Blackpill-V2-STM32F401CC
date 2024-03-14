/*******************************************************************************/
/**
 * @file scheduler.h
 * @brief Header file for a task scheduling library for STM32F401CC microcontrollers.
 *
 * This header file provides declarations for functions used to
 * manage the execution of runnables in programs running on STM32F401CC microcontrollers.
 * It likely includes mechanisms for defining runnables, scheduling their execution
 * at specific times or intervals, and potentially managing resources shared between tasks.
 *
 * @par Project Name
 * stm32fxx services
 *
 * @par Code Language
 * C
 *
 * @par Description
 * A more detailed description of the scheduler's functionality can be provided here.
 * This include:
 *   - Supported scheduling types (e.g., periodic)
 *   - runnable management mechanisms (e.g., creation, priority)
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 * @par Target Microcontroller
 * STM32F401CC
 *
 *******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef SCHEDULAR_H_
#define SCHEDULAR_H_
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

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief Function pointer for runnable callbacks
 */
typedef void (*runnableCallBack)(void);

/**
 * @brief Structure to represent a runnable for the scheduler.
 */
typedef struct {
    /**
     * @brief Name of the runnable .
     */
    char *name;

    /**
     * @brief Periodicity in milliseconds (how often to run the runnable).
     */
    uint32_t periodicityMS;

    /**
     * @brief Priority of the runnable (smaller number indicates higher priority).
     * Used by the scheduler to determine the order of execution.
     */
    uint32_t priority;

    /**
     * @brief Callback function pointer to be executed when the runnable is triggered.
     * The specific signature of `runnableCallBack` depends on your application.
     */
    runnableCallBack CallBack;

    /**
     * @brief Delay in milliseconds before the first execution (optional).
     * Useful for delaying the start of certain tasks or coordinating execution.
     */
    uint32_t DelayMS;
} Schedular_runnable_t;



/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DECLARATIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DECLARATIONS */
/******************************************************************************/

/**
 * @brief Initializes the scheduler.
 *
 * @note This function must be called before using the scheduler to configure its
 * internal state and potentially set up any hardware resources required
 * for task scheduling (e.g., systick).
 *
 * It is typically called once during program initialization.
 */
void schedular_init(void);


/**
 * @brief Starts the scheduler.
 *
 * This function initiates the execution of tasks managed by the scheduler.
 * Once called, the scheduler typically enters a loop where it monitors periodic
 * timing, determines which task to run next based on priority and its period,
 * and invokes the corresponding task callback function.
 * 
 * @note It is typically called after successful scheduler initialization 
 *       (`scheduler_init`).
 */
void schedular_start(void);
/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES */
/******************************************************************************/


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
#endif /* SCHEDULAR_H_ */
/******************************************************************************/
