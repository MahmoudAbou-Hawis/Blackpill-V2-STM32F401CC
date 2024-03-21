/*******************************************************************************/
/**
 * @file LCD_CFG.h
 * @brief  Header file for LCD configuration.
 * 
 * This header file defines configurations for interacting with the LCD display.
 *
 * @par Project Name
 *  LCD Project.
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines configuration options for the LCD display, including
 * its dimensions, data bus width, and number of lines.
 * 
 * @par Author
 * @MahmoudAbou-Hawis
 *
 ******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef LCD_CFG_H_
#define LCD_CFG_H_
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
/*			                    LCD dimension		        	              */
/******************************************************************************/

/**
 * @def NUM_OF_ROWS
 * @brief Macro defining the number of rows (lines) on the LCD display.
 * 
 * This macro, `NUM_OF_ROWS`, defines the number of rows (lines) that your LCD display 
 * can display. The specific value depends on the physical capabilities of your LCD. 
 * 
 * Value: 2 (default, adjust based on your LCD)
 */
#define			NUM_OF_ROWS				2

/**
 * @def NUM_OF_COLS
 * @brief Macro defining the number of columns on the LCD display.

 * This macro, `NUM_OF_COLS`, defines the number of columns (characters) that each row 
 * of your LCD display can accommodate. The specific value depends on the physical 
 * capabilities of your LCD.
 * 
 * Value: 16 (default, adjust based on your LCD)
 */
#define			NUM_OF_COLS				16




/******************************************************************************/
/*			             LCD MODE CONFIGURATION	                              */
/******************************************************************************/


/**
 * @def FOUR_BIT_MODE
 * @brief Macro defining a 4-bit data bus mode for the LCD.
 * 
 * This macro, `FOUR_BIT_MODE`, is used to configure the LCD display to use a 4-bit data 
 * bus. In this mode, data is sent to the LCD in two 4-bit nibbles (half-bytes). 
 */
#define FOUR_BIT_MODE                   4

/**
 * @def EIGHT_BIT_MODE
 * @brief Macro defining an 8-bit data bus mode for the LCD.

 * This macro, `EIGHT_BIT_MODE`, is used to configure the LCD display to use an 8-bit data 
 * bus. In this mode, data is sent to the LCD directly as full bytes. This typically provides 
 * faster data transfer compared to 4-bit mode. 
 */
#define EIGHT_BIT_MODE                  8

/**
 * @def LCD_DATA_MODE
 * @brief Macro defining the current LCD data bus mode.
 * 
 * This macro, `LCD_DATA_MODE`, is currently set to use the `FOUR_BIT_MODE` by default. 
 * You can modify this macro to switch between 4-bit and 8-bit modes based on your 
 * project requirements and the capabilities of your LCD controller.
 * 
 * Value: Determined by the chosen configuration (either `FOUR_BIT_MODE` or `EIGHT_BIT_MODE`).
 */
#define LCD_DATA_MODE                   EIGHT_BIT_MODE

/******************************************************************************/
/*			            NUMBER OF LINES USED                                  */
/******************************************************************************/


/**
 * @def ONE_LINE
 * @brief Macro defining a 1-line LCD configuration.

 * This macro, `ONE_LINE`, is used to configure the LCD display to operate in a 
 * 1-line mode. 
 */
#define			ONE_LINE				0



/**
 * @def TWO_LINE
 * @brief Macro defining a 2-line LCD configuration.

 * This macro, `TWO_LINE`, is used to configure the LCD display to operate in a 
 * 2-line mode. 
 * */
#define			TWO_LINE				0x08

/**
 * @def NUM_OF_DIS_LINES
 * @brief Macro defining the current number of display lines.

 * This macro, `NUM_OF_DIS_LINES`, is set to use the `TWO_LINE` configuration by default. 
 * You can modify this macro to switch between 1-line and 2-line modes based on 
 * your project requirements.

 * Value: Determined by the chosen configuration (either `ONE_LINE` or `TWO_LINE`).
 */
#define			NUM_OF_DIS_LINES	    TWO_LINE


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
#endif /* LCD_CFG_H_ */
/******************************************************************************/
