#include "CHAR_LCD_CFG.h"

#if  LCD_DATA_MODE == EIGHT_BIT_MODE
/**
*@brief refer to data pin 0.
*/
#define			D0					0

/**
*@brief refer to data pin 1.
*/
#define			D1					1

/**
*@brief refer to data pin 2.
*/
#define			D2					2

/**
*@brief refer to data pin 3.
*/
#define			D3					3

/**
*@brief refer to data pin 4.
*/
#define			D4					4

/**
*@brief refer to data pin 5.
*/
#define			D5					5

/**
*@brief refer to data pin 6.
*/
#define			D6					6

/**
*@brief refer to data pin 7.
*/
#define			D7					7

/**
*@brief refer to Enable pin.
*/
#define			E					8

/**
*@brief refer to read/write pin.
*/
#define			RW					9

/**
*@brief refer to register select pin.
*/
#define			RS					10


/**
 * @brief represent the number of LCD pins.
 */
#define         LCD_PIN_NUMS        11

#elif  LCD_DATA_MODE == FOUR_BIT_MODE

/**
*@brief refer to data pin 4.
*/
#define			D4					0

/**
*@brief refer to data pin 5.
*/
#define			D5					1

/**
*@brief refer to data pin 6.
*/
#define			D6					2

/**
*@brief refer to data pin 7.
*/
#define			D7					3

/**
*@brief refer to Enable pin.
*/
#define			E					4

/**
*@brief refer to read/write pin.
*/
#define			RW					5

/**
*@brief refer to register select pin.
*/
#define			RS					6

/**
 * @brief represent the number of LCD pins.
 */
#define         LCD_PIN_NUMS        7

#else 
    #error "LCD_DATA_MODE configuration is incorrect"
#endif

