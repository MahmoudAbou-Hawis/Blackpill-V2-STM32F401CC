/******************************************************************************/
/**
 * @file LCD.c
 * @brief Implementation of functions for LCD control.

 * This file implements functions for initializing, sending commands, setting cursor 
 * position, and writing strings to the LCD display in an asynchronous manner. The 
 * LCD configuration is assumed to be:

 * - **Dimensions:** `LCD_WIDTH` characters x `LCD_HEIGHT` lines (refer to `LCD_CFG.h` for definitions)
 * - **Data Bus Width:** `LCD_DATA_WIDTH` (either 4-bit or 8-bit, refer to `LCD_CFG.h` for definitions)
 * - **Number of Lines:** `LCD_LINES` (either 1-line or 2-line, refer to `LCD_CFG.h` for definitions)

 * Functions utilize asynchronous operations whenever possible, returning immediately 
 * after initiating the operation and communicating the completion status through 
 * a provided callback function (`CallBack` type). Additional functions are 
 * provided for low-level communication with the LCD controller.

 * Refer to the `LCD.h` header file for function prototypes and detailed descriptions.

 * @par Project Name
 * LCD Project

 * @par Code Language
 * C

 * @par Author
 * @MahmoudAbou-Hawis
 *
 *****************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "CHAR_LCD.h"
#include "CHAR_LCD_CFG.h"
#include "CHAR_LCD_priv.h"
#include "stm32f4xx_gpio.h"
#include <stdbool.h>
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/


/**
 * @brief Command for display control.
 */
#define CMD_DISPLAY_CONTROL ((uint8_t)0x0C)

/**
 * @brief Command for setting entry mode.
 */
#define CMD_ENTRY_MODE_SET ((uint8_t)0x06)

/**
 * @brief Address for the second line on an LCD.
 */
#define LCD_SECOND_LINE_ADDRESS ((uint8_t)0x40)

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

#define IS_NULL_PARAM(_PTR) (_PTR == NULL)

#define IS_ALL_LCD_PINS_INITIALIZED(_CFG_FLAG) (_CFG_FLAG == false)

#define IS_PIN_INITIALIZATION_FAILED(_RET) (_RET != SUCCESS)

#define IS_LAST_REQUEST_IN_PROCESS(_STATE) (_STATE == BUSY)

#define IS_NOT_VALID_CMD(_CMD) ((_CMD != CMD_CLEAR_DISPLAY) &&             \
                                (_CMD != CMD_RETURN_HOME) &&               \
                                (_CMD != CMD_SHIFT_LEFT) &&                \
                                (_CMD != CMD_SHIFT_RIGHT) &&               \
                                (_CMD != CMD_SHIFT_ENTIRE_DISPLAY_LEFT) && \
                                (_CMD != CMD_SHIFT_ENTIRE_DISPLAY_RIGHT))

#define IS_LCD_OFF(_STATE) (_STATE == OFF_STATE)


#define IS_NOT_VALID_CURSOR_POSITION(_X, _Y) ((_X >= NUM_OF_ROWS) || \
                                              (_Y >= NUM_OF_COLS))


#define IS_LCD_IN_OPERATIONAL_STATE(_STATE) (_STATE == OPERATIONAL_STATE)

#define IS_LCD_IN_INITIALIZATION_STATE(_STATE) (_STATE == INITIALIZATION_STATE)

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/**
 * @typedef UserRequestsTypes_t
 * @brief Enumerates the different types of user requests.
 */
typedef enum
{
  /** @enum WRITE - Denotes a request to write data to the display. */
  WRITE,
  /** @enum COMMAND - Denotes a request to send a control command to the display. */
  COMMAND,
  /** @enum CURSOR - Denotes a request to control the cursor on the display. */
  CURSOR,
} UserRequestsTypes_t;

/**
 * @typedef RequestState_t
 * @brief Enumerate the different request states.
 */
typedef enum
{
  /** @enum BUSY - Denotes the LCD is busy processing a request and 
   *        cannot receive new ones. */
  BUSY,
  /** @enum IDLE - Denotes the LCD is ready to receive a new request. */
  IDLE
} RequestState_t;

/**
 * @typedef InitStates_t
 * @brief Enumerate the different Initialization stages.
 */
typedef enum
{
  /** @enum FUNCTION_SET - Represents the stage where LCD functionalities 
   *        are configured. */
  FUNCTION_SET,
  /** @enum DISPLAY_ON_OFF_CONTROL - Represents the stage where display 
   *        power and visibility are set. */
  DISPLAY_ON_OFF_CONTROL,
  /** @enum DISPLAY_CLEAR - Represents the stage where the LCD display is cleared. */
  DISPLAY_CLEAR,
  /** @enum ENTRY_MODE_SET - Represents the stage where the cursor movement 
            and display shift behavior are defined. */
  ENTRY_MODE_SET
} InitStates_t;

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/**
 * @typedef UserRequest_t
 * @brief Structure representing a user request for the LCD.
 */
typedef struct 
{
  /** @field ReqState - The current state of the request (BUSY or IDLE). */
  RequestState_t ReqState; 
  /** @field ReqType - The type of request (WRITE, COMMAND, or CURSOR). */
  UserRequestsTypes_t ReqType;
  /** @field Callback - A function pointer to be called when the request 
             is complete (optional). */
  CallBack Callback;
} UserRequest_t;


/**
 * @typedef WriteRequest_t
 * @brief Structure representing a write request for the LCD.
 */
typedef struct 
{
  /** @field String - The string to be written to the LCD display. */
  char * String;
  /** @field StringLen - The length of the string to be written. */
  uint8_t StringLen;
  /** @field CurPos - The current cursor position within 
   *                  the string (zero-based index). */
  uint8_t CurPos;
  /** @field posX - The target X position (row) on the LCD 
   *                to start writing the string. */
  uint8_t posX;
  /** @field PosY - The target Y position (column) on the LCD 
    *               to start writing the string. */
  uint8_t PosY;
} WriteRequest_t;

/**
 * @typedef CommandRequest_t
 * @brief Structure representing a command request for the LCD.
 */
typedef struct 
{
    /** @field Command - The command to be sent to the LCD display */
    uint8_t Command;
    /** @field IsRequestFromCursor - A flag indicating if the command originated
         from the cursor control (not directly from the user). */
    bool IsRequestFromCursor;
} CommandRequest_t;

/**
 * @typedef CursorRequest_t
 * @brief Structure represent a Change Cursor request for the LCD.
 */
typedef struct 
{
    /**@field X - indicate the row number in LCD (zero-based index).*/
    uint8_t X;
    /**@field X - indicate the column number in LCD (zero-based index).*/
    uint8_t Y;
    /** @field IsRequestFromWrite - A flag indicating if the cursor move request 
               originated from a write operation (not directly from the user).  */
    bool IsRequestFromWrite;
} CursorRequest_t;

/**
 * @typedef WriteByte_t
 * @brief Structure represent the byte to be sent to the LCD 
 *        (which can be command or data).
 */
typedef struct 
{
    /** @field byte - indicate the byte to be sent to the LCD */
    uint8_t byte;
    /** @field counter - used to tracking byte because in 4-bit mode byte 
     *                  will be divided into two halves, with the high nibble sent 
     *                  initially, then the next low nibble  */
    uint8_t counter;
    /** @field IsByteSent - Flag indicating if the byte has been successfully 
     *                      sent to the LCD. */
    uint8_t IsByteSent;
    /** @field IsCommand - Flag indicating if the byte
     *                     represent a command or data*/
    bool IsCommend;
} WriteByte_t;

/**
 *@brief used to indicate time for send command function.
 */
uint8_t CommandCounter = 0;

/**
 *@brief used to indicate time for cursor function.
 */
uint8_t CursorCounter  = 0;
/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/

const uint8_t TimeNeedToSentData = ((LCD_DATA_MODE % EIGHT_BIT_MODE == 0)?2:3);

/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

/**
 * @brief Stores the current power state of the LCD (OFF, OPERATIONAL, etc.).
 */
static LCD_States_t  LCD_STATE = OFF_STATE;

/**
 * @brief indicate the default cursor place when LCD get ON.
 */
static CursorRequest_t CursorReq = {
    .X = 0,
    .Y = 0
};

/**
 * @brief When the LCD turns on, no default command request is received.
 */
static CommandRequest_t CommandReq = {0};

/**
 * @brief When the LCD turns on, no default write request is received.
 */
static WriteRequest_t WriteReq = {
    .CurPos = 0 , 
    .String = NULL ,
    .StringLen = 0,
    .PosY = 0
};

/**
 *@brief Represents a user's request for the LCD.
 */
static UserRequest_t userReq = 
{
    .Callback = NULL
};

/**
 * @brief Structure holding a byte to be sent to the LCD (can be command or data)
 */
static WriteByte_t Byte ;

/**
 * @brief indicate the current initialization stage when the LCD in 
 *        initialization mode(FUNCTION_SET ,DISPLAY_ON_OFF_CONTROL , etc..)
 */
static InitStates_t CurrentInitState = FUNCTION_SET;

/**
 * @brief represent track waiting time in initialization stage.
 */
static uint32_t waitingCounter = 0;

/**
 * @brief represent track time for function set function.
 */
static uint8_t FunctionSetCounter = 0;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/**
 * @brief The LCD pins which configured previously in CHAR_LCD_CFG.h.
 */
extern const LCD_CFG_t LCD_PINS[LCD_PIN_NUMS];
/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES */
/******************************************************************************/

/**
 * @brief Initializes the LCD display by sending a sequence of commands
 *        to configure basic functionalities and prepare it for use.
 */
static void LCD_InitHandler(void);

/**
 * @brief Processes user or internal requests for the LCD display.
 *        This function handles different types of requests like writing text,
 *        moving the cursor, or sending commands.
 */
static void LCD_RequestsHandler(void);

/**
 * @brief Sets the data or control bits on the communication bus used to
 *        interact with the LCD, depending on the provided data and data type.
 * @param data The data byte to be sent on the bus.
 * @param dataType Flag indicating whether the data is a command (true) or data (false).
 */
static void LCD_SetBitsInTheBus(char data, bool dataType);

/**
 * @brief It enables the LCD to receive new requests from the communication bus.
 */
static void LCD_ReceiveData(void);

/**
 * @brief Sends the "Function Set" command to the LCD, which is part of
 *        the initialization process to configure basic functionalities.
 */
static void FunctionSet(void);

/**
 * @brief Sends a single byte (data or command) to the LCD. This function 
 *        handles the low-level communication logic, using
 *        `LCD_SetBitsInTheBus` to set the data bits on the bus.
 */
static void SendByte(void);

/**
 * @brief used to configure the byte before sending.
 * 
 * @param data The data byte to be sent.
 * @param isCommand Flag indicating whether the data is a command (true) or data (false).
 */
static void SetByte(uint8_t data, bool isCommand);

/**
 * @brief Sends a string of characters to the LCD display. 
 */
static void SendString(void);

/**
 * @brief Sends commands to the LCD to set the new cursor position.
 */
static void SetCurser(void);

/**
 * @brief Sends a command byte directly to the LCD.
 */
static void SendCommand(void);

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/

/** Called by the schedular each 1 millisecond (MS)*/
void LCD_Runnable(void)
{
    /** Check if the LCD is in initialization stage. */
    if(IS_LCD_IN_INITIALIZATION_STATE(LCD_STATE))
    {
        LCD_InitHandler();
    } 
    /** Check if the LCD is in operational stage. */
    else if(IS_LCD_IN_OPERATIONAL_STATE(LCD_STATE))
    {
        LCD_RequestsHandler();
    }
    else
    {
        /**The LCD is off */
    }
}

/*
 * LCD Initialization Steps:
 * -------------------------
 * 1. Power on the LCD module.
 * 2. Wait for the LCD to stabilize (typically a few milliseconds).
 * 3. Send the initialization sequence:
 *    a. Set the interface mode (e.g., 4-bit mode or 8-bit mode).
 *    b. Configure display settings (e.g., number of lines, font size).
 *    c. Set cursor settings (e.g., cursor visibility, cursor blink).
 *    d. Clear the display.
 *    e. Return home (set cursor to the initial position).
 * 4. Wait for the initialization sequence to complete (typically a few milliseconds).
 * 5. LCD is ready for use.
 *
 */
static void LCD_InitHandler(void)
{
    waitingCounter++;
    switch (CurrentInitState)
    {
    case FUNCTION_SET:
        if(waitingCounter >= 31)   
        {
            FunctionSet();
        }
        break;
    case DISPLAY_ON_OFF_CONTROL:
            if(waitingCounter == 2)
            {
                SetByte(CMD_DISPLAY_CONTROL,true);
                SendByte();
            }
            else if(waitingCounter > 2)
            {
                if(Byte.IsByteSent == 1)
                {
                    CurrentInitState = DISPLAY_CLEAR;
                    waitingCounter = 0;
                }
                else
                {
                    SendByte();
                }
            }
            break;
    case DISPLAY_CLEAR:
        if(waitingCounter == 1)
        {
            SetByte(CMD_CLEAR_DISPLAY,true);
            SendByte();
        }
        else if(waitingCounter > 1)
        {
            if(Byte.IsByteSent == 1)
            {
                CurrentInitState = ENTRY_MODE_SET;
                waitingCounter = 0;
            }
            else
            {
                SendByte();
            }
        }
        break;
    case ENTRY_MODE_SET:
        if(waitingCounter ==3)
        {
            SetByte(CMD_ENTRY_MODE_SET,true);
            SendByte();
        }
        else if(waitingCounter > 3)
        {
            if(Byte.IsByteSent == 1)
            {
                LCD_STATE = OPERATIONAL_STATE;
                CurrentInitState = FUNCTION_SET;
                waitingCounter = 0;
                userReq.ReqState = IDLE;
                if(userReq.Callback != NULL)
                {
                    userReq.Callback();
                }
                else
                {

                }
            }
            else
            {
                SendByte();
            }
        }
        break;
    default:
        break;
    }
}

static void LCD_RequestsHandler(void)
{
    /** if no request from user return.*/
    if(userReq.ReqState == IDLE) return;
    switch (userReq.ReqType)
    {
    case WRITE:
        SendString();
        break;
    case COMMAND:
        SendCommand();
        break;
    case CURSOR:
        SetCurser();
        break;
    default:
        break;
    }
}

/** set the data in the communication bus  */
static void LCD_SetBitsInTheBus(char data,bool dataType)
{
    for(int Pin = 0 ; Pin < LCD_PIN_NUMS -3 ; Pin++)
    {
        GPIO_SetPinValue(LCD_PINS[Pin].GPIO_Port,LCD_PINS[Pin].GPIO_Pin,
                        (uint32_t)(((data >> Pin) &1) ^1));
    }
    GPIO_SetPinValue(LCD_PINS[RW].GPIO_Port, LCD_PINS[RW].GPIO_Pin, GPIO_STATE_RESET);
    GPIO_SetPinValue(LCD_PINS[RS].GPIO_Port,LCD_PINS[RS].GPIO_Pin,dataType);
    GPIO_SetPinValue(LCD_PINS[E].GPIO_Port,LCD_PINS[E].GPIO_Pin,GPIO_STATE_SET); 
}

static void LCD_ReceiveData(void)
{
    GPIO_SetPinValue(LCD_PINS[E].GPIO_Port,LCD_PINS[E].GPIO_Pin,GPIO_STATE_RESET); 
}

static void SendByte(void)
{  
    if(TimeNeedToSentData == Byte.counter)
    {
        Byte.IsByteSent = true;
    }
    else
    {
        if(Byte.counter > 0)
        {
            LCD_ReceiveData();
            Byte.byte <<= LCD_DATA_MODE;
        }
        else
        {
        }
        if(Byte.counter + 1 < TimeNeedToSentData)
        {
            LCD_SetBitsInTheBus((Byte.byte >> (LCD_DATA_MODE % EIGHT_BIT_MODE))
                                ,Byte.IsCommend);
        }
        else
        {
        }
    }
    Byte.counter++;
}

static void SetByte(uint8_t data, bool isCommand)
{
    Byte.byte = data;
    Byte.counter = 0;
    Byte.IsByteSent = 0;
    Byte.IsCommend = isCommand;
}

static void FunctionSet(void)
{
    #if LCD_DATA_MODE == EIGHT_BIT_MODE
    if(FunctionSetCounter == 0)
    {
        SetByte(0x30|NUM_OF_DIS_LINES,true);
        SendByte();
    }
    else
    {
        if(Byte.IsByteSent == true)
        {
            CurrentInitState = DISPLAY_ON_OFF_CONTROL;
            FunctionSetCounter = 0;
            waitingCounter = 0;
            Byte.IsByteSent = 0;
        }
        else
        {
            SendByte();
        }
    }
    #else
        if(FunctionSetCounter == 0)
        {
            SetByte(0x22,true);
            SendByte();
        }
        else
        {
            if(Byte.IsByteSent == true)
            {
                if(FunctionSetCounter == 1)
                {
                    LCD_ReceiveData();
                    waitingCounter = 0;
                    CurrentInitState = DISPLAY_ON_OFF_CONTROL;
                    return;
                }
                FunctionSetCounter = 0;
                LCD_SetBitsInTheBus(NUM_OF_DIS_LINES,true);
            }
            else
            {
                SendByte();
            }
        }
    #endif
    FunctionSetCounter++;
}

void SendString()
{
     /** the line 1 full and need to change the cursor postion to the next line. */
    if(WriteReq.PosY >= 16)
    {
        CursorReq.IsRequestFromWrite = true;
        CursorReq.X = 1;
        CursorReq.Y = 0;
        userReq.ReqType = CURSOR;
    }
    else
    {
    if(WriteReq.CurPos == 0)
    {
        SetByte(WriteReq.String[WriteReq.CurPos++],false);
        SendByte();
    }
        else
        {
            if(Byte.IsByteSent == 1)
            {
                /** increase the cursor column postion */
                WriteReq.PosY++;

                /** Check if the cursor ate the end of string write 
                 *  the remaining chars in line 2 */
                if(WriteReq.posX != 1 && WriteReq.PosY == 16) return;

                /** Thse string still not sent */
                if(WriteReq.CurPos < WriteReq.StringLen)
                {
                    SetByte(WriteReq.String[WriteReq.CurPos++],false);
                    SendByte();
                }
                else
                {
                    /**String is sent */
                    userReq.ReqState = IDLE;
                    if(userReq.Callback != NULL)
                    {
                        userReq.Callback();
                    }
                    else
                    {

                    }
                }
            }
            else
            {
                SendByte();
            }
        }
    }
}


static void SendCommand(void)
{
    if(CommandCounter == 0)
    {
        SetByte(CommandReq.Command,true);
        SendByte();
    }
    else if(Byte.IsByteSent == true)
    {
        CommandCounter = 0;
        if(CommandReq.IsRequestFromCursor == true)
        {
            userReq.ReqType = CURSOR;
        }
        else
        {
            userReq.ReqState = IDLE;
            if(userReq.Callback != NULL)
            {
                userReq.Callback();
            }
            else
            {

            }
        }
    }
    else
    {
        SendByte();
    }
    if(Byte.IsByteSent == 0)
        CommandCounter++;
}

static void SetCurser(void)
{
    if(CursorCounter == 0)
    {
        CommandReq.Command = 
            (((CursorReq.X * LCD_SECOND_LINE_ADDRESS) + CursorReq.Y) | (1 << 7));
        CommandReq.IsRequestFromCursor = true;
        userReq.ReqType = COMMAND;
        CursorCounter++;
    } 
    else
    {
        CursorCounter = 0;
        WriteReq.posX = CursorReq.X;
        WriteReq.PosY = CursorReq.Y;
        if(CursorReq.IsRequestFromWrite == true)
        {
            userReq.ReqType = WRITE;
        }
        else
        {
            userReq.ReqState = IDLE;
            if(userReq.Callback != NULL)
            {
                userReq.Callback();
            }
            else
            {

            }
        }
    }
}
/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

LCD_ErrorStatus_t LCD_InitAsync(CallBack CB)
{
    /* Temporary GPIO pin configuration structure */
    gpioPin_t pinCfg;

    /** Function return */
    LCD_ErrorStatus_t RET_enuErrorStatus = LCD_ERROR_NONE;

    /** This flag indicates that the user has selected an incorrect GPIO port or pin. */
    uint8_t Wrong_Configuration = false;

    /* Iterate through each pin in the LCD array pins */
    for (uint32_t PinIdx = 0; PinIdx < LCD_PIN_NUMS && !Wrong_Configuration; PinIdx++)
    {
        /** Set up the specified GPIO pins as output using push-pull configuration. */
        pinCfg.GPIO_Speed = GPIO_SPEED_LOW;
        pinCfg.GPIO_Mode = GPIO_MODE_OUT_PP;
        pinCfg.GPIO_Port = LCD_PINS[PinIdx].GPIO_Port;
        pinCfg.GPIO_Pin = LCD_PINS[PinIdx].GPIO_Pin;
        pinCfg.GPIO_AT_Type = GPIO_AT_None;

        /** If the user enters an incorrect port or pin, the function will return an error. */
        if (IS_PIN_INITIALIZATION_FAILED(GPIO_Init(&pinCfg)))
        {
            RET_enuErrorStatus = LCD_ERROR;
            Wrong_Configuration = true;
        }
        else
        {
            /* No Thing */
        }
    }

    /** If the user enters all ports and pins correctly, and these pins are configured, 
     * the LCD initialization will begin. */
    if (IS_ALL_LCD_PINS_INITIALIZED(Wrong_Configuration))
    {
        LCD_STATE = INITIALIZATION_STATE;
        userReq.Callback = CB;
        userReq.ReqState = BUSY;
    }
    else
    {
        /**No Thing */
    }

    return RET_enuErrorStatus;
}

LCD_ErrorStatus_t LCD_SendCommandAsync(uint8_t CMD, CallBack CB)
{
    /** Function return*/
    LCD_ErrorStatus_t RET_enuErrorStatus = LCD_ERROR_NONE;

    /** Check if the LCD is disabled. */
    if(IS_LCD_OFF(LCD_STATE))
    {
        RET_enuErrorStatus = LCD_IS_OFF;
    }
    /** Check if the LCD cannot handle a new request. */
    else if (IS_LAST_REQUEST_IN_PROCESS(userReq.ReqState))
    {
        RET_enuErrorStatus = LCD_LAST_REQUEST_PROCESSING_STILL_IN_EXECUTION;
    }
    /** Verify if the CMD parameter does not represent a valid command for the LCD. */
    else if (IS_NOT_VALID_CMD(CMD))
    {
        RET_enuErrorStatus = LCD_ERROR_INVALID_PARAM;
    }
    else
    {
        if(CMD == CMD_CLEAR_DISPLAY || CMD == CMD_RETURN_HOME)
        {
            WriteReq.posX = 0;
            WriteReq.PosY = 0;
        }
        else
        {

        }
       /** The request will begin processing. */
        userReq.Callback = CB;
        CommandReq.Command = CMD;
        userReq.ReqType  = COMMAND;
        CommandReq.IsRequestFromCursor = false;
        userReq.ReqState = BUSY;
    }

    return RET_enuErrorStatus;
}

LCD_ErrorStatus_t LCD_SetCursorAsync(uint8_t Pos_X, uint8_t Pos_Y, CallBack CB)
{
    /** Function return*/
    LCD_ErrorStatus_t RET_enuErrorStatus = LCD_ERROR_NONE;
    
    /** Check if the LCD is disabled. */
    if(IS_LCD_OFF(LCD_STATE))
    {
        RET_enuErrorStatus = LCD_IS_OFF;
    }
    /** Check if the LCD cannot handle a new request. */
    else if (IS_LAST_REQUEST_IN_PROCESS(userReq.ReqState))
    {
        RET_enuErrorStatus = LCD_LAST_REQUEST_PROCESSING_STILL_IN_EXECUTION;
    }
    /** Check if the cursor will be in an invalid position */
    else if (IS_NOT_VALID_CURSOR_POSITION(Pos_X,Pos_Y))
    {
        RET_enuErrorStatus = LCD_ERROR_INVALID_PARAM;
    }
    else
    {
        /** The request will begin processing. */
        userReq.Callback = CB;
        CursorReq.X = Pos_X;
        CursorReq.Y = Pos_Y;
        CursorReq.IsRequestFromWrite = false;
        userReq.ReqType = CURSOR;
        userReq.ReqState = BUSY;
    }
    return RET_enuErrorStatus;
}

LCD_ErrorStatus_t LCD_WriteStringAsyncZeroCopy(char *string, uint8_t size,
                                               CallBack CB)
{
    /** Function return*/
    LCD_ErrorStatus_t RET_enuErrorStatus = LCD_ERROR_NONE;
    
    /** Check if the LCD is disabled. */
    if(IS_LCD_OFF(LCD_STATE))
    {
        RET_enuErrorStatus = LCD_IS_OFF;
    }
    /** Check if the LCD cannot handle a new request. */
    else if (IS_LAST_REQUEST_IN_PROCESS(userReq.ReqState))
    {
        RET_enuErrorStatus = LCD_LAST_REQUEST_PROCESSING_STILL_IN_EXECUTION;
    }
    else if(IS_NULL_PARAM(string))
    {
        RET_enuErrorStatus = NULL_PTR_PASSED;
    }
    else
    {
        uint8_t RemainingCharInLCD = (NUM_OF_COLS * NUM_OF_ROWS) - 
                                    (((WriteReq.posX) * NUM_OF_COLS) + WriteReq.PosY); 
        if(RemainingCharInLCD < size)
        {
            RET_enuErrorStatus = LCD_ERROR_INVALID_PARAM;
        }
        else
        {
            /** The request will begin processing. */
            userReq.Callback = CB;
            WriteReq.CurPos = 0;
            WriteReq.String = string;
            WriteReq.StringLen = size;
            userReq.ReqType = WRITE;
            userReq.ReqState = BUSY;
        }
    }
    return RET_enuErrorStatus;
}

LCD_ErrorStatus_t LCD_GetState(LCD_States_t * LCDState)
{
    /** Function return */
    LCD_ErrorStatus_t RET_enuErrorStatus = LCD_ERROR_NONE;

    if(IS_NULL_PARAM(LCDState))
    {
        RET_enuErrorStatus = NULL_PTR_PASSED;
    }
    else
    {
        /**Copy LCD state*/
        *LCDState = LCD_STATE;
    }
    return RET_enuErrorStatus;
}
/******************************************************************************/