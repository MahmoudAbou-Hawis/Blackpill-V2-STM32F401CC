/******************************************************************************/
/**
 * @file led_cfg.h
 * @brief LED Configuration Header
 *
 * @par Project Name
 * Embedded LED Configuration for STM32F401CC
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines structures and constants for LED configurations,
 * including GPIO port, pin number, connection type, and default state.
 * 
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef LED_CFG_H_
#define LED_CFG_H_
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

/*
 * Enumeration defining different LEDs.
 * 
 * This enumeration is used to represent different LEDs in the system.
 * 
 * - _LEDs_NUM: Represents the total number of LEDs in the system.
 * 
 * Note: The symbol '_' prefix conventionally indicates a private or internal
 * symbol. In this case, _LEDs_NUM is used internally to represent the total
 * number of LEDs and should not be accessed directly outside this module.
 */
typedef enum
{
  TRAFFIC_RED_LED,
  TRAFFIC_YELLOW_LED,
  TRAFFIC_GREEN_LED ,
  _LEDs_NUM
} LEDs_t;

/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/


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
#endif /* LED_CFG_H_ */
/******************************************************************************/
