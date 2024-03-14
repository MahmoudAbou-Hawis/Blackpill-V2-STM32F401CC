/******************************************************************************/
/**
 * @file Traffic.c
 * @brief Implementation file for traffic management using a scheduler based on SysTick.
 *
 * @par Project Name
 * Traffic Management System
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the implementation of a traffic management system
 * using a scheduler that relies on the SysTick timer. Users of this file
 * must configure the scheduler according to their specific requirements.
 * 
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "schedular_CFG.h"
#include "led.h"
#include "led_cfg.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/**
 * @brief Duration until the green LED deactivation (in Milli seconds).
 */
#define    DEACTIVATE_TIME_GREEN_LED        6000


/**
 * @brief Duration until the red LED deactivation (in Milli seconds).
 */
#define    DEACTIVATE_TIME_RED_LED          4000


/**
 * @brief Duration until the yellow LED deactivation (in Milli seconds).
 */
#define    DEACTIVATE_TIME_YELLOW_LED       2000
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/


/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/**
 * @brief Enumerates the possible states of a traffic light.
 *
 * This enum defines the different states (RED, YELLOW, GREEN) that a traffic
 * light can be in.
 */
typedef enum {
  RED,
  YELLOW,
  GREEN
} TrafficLightState_t; 


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
 * @brief Initial state of the traffic light.
 */
static TrafficLightState_t TrafficCurrentState = GREEN;

/**
 * @brief Determines the next traffic state based on the previous state.
 *        The yellow LED is utilized to determine whether the traffic will transition
 *        to the red state or the green state. Initially, the traffic state is 
 *        set to green since there are no states preceding it.
 */
static TrafficLightState_t PreviousTrafficState = GREEN;


/**
 *@brief Counter used to determine the time remaining before deactivating 
 * the states.
 */
static uint32_t Counter = 0 ; 
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
void traffic_start(void)
{
    /* Calculate the time needed to make a decision regarding which state to 
       run and what to stop.*/
    Counter += 2000;
    switch (TrafficCurrentState)
    {
    case GREEN:
        /** green led is on*/
        LED_enuSetStatus(TRAFFIC_GREEN_LED,LED_STATE_ON);
        /** red led is off*/
        LED_enuSetStatus(TRAFFIC_RED_LED,LED_STATE_OFF);
        /** yellow led is off */
        LED_enuSetStatus(TRAFFIC_YELLOW_LED,LED_STATE_OFF);
        if(Counter == DEACTIVATE_TIME_GREEN_LED)
        {
            PreviousTrafficState = GREEN;
            TrafficCurrentState  = YELLOW;
            
            /**Reset the counter to initiate calculations for the next state. */
            Counter = 0;
        }
        else
        {

        }
        break;

    case YELLOW:
        /** green led is off*/
        LED_enuSetStatus(TRAFFIC_GREEN_LED,LED_STATE_OFF);
        /** red led is off*/
        LED_enuSetStatus(TRAFFIC_RED_LED,LED_STATE_OFF);
        /** yellow led is on */
        LED_enuSetStatus(TRAFFIC_YELLOW_LED,LED_STATE_ON);
        if(Counter == DEACTIVATE_TIME_YELLOW_LED)
        {
            if(PreviousTrafficState == RED)
            {
                TrafficCurrentState = GREEN;
            }
            else
            {
                TrafficCurrentState = RED;
            }

            /**Reset the counter to initiate calculations for the next state. */
            Counter = 0;
        }
        else
        {

        }
        break;
    
    case RED:
        /** green led is off*/
        LED_enuSetStatus(TRAFFIC_GREEN_LED,LED_STATE_OFF);
        /** red led is on*/
        LED_enuSetStatus(TRAFFIC_RED_LED,LED_STATE_ON);
        /** yellow led is off */
        LED_enuSetStatus(TRAFFIC_YELLOW_LED,LED_STATE_OFF);
        if(Counter == DEACTIVATE_TIME_RED_LED)
        {
            PreviousTrafficState = RED;
            /** The Current state */
            TrafficCurrentState  = YELLOW;

            /**Reset the counter to initiate calculations for the next state. */
            Counter = 0;
        }
        else
        {

        }
        break;    

    default:
        break;
    }
}
/******************************************************************************/