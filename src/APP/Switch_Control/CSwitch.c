/******************************************************************************/
/**
 * @file FILE.c
 * @brief 
 *
 * @par Project Name
 * 
 *
 * @par Code Language
 * C
 *
 * @par Description
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
#include "switch.h"
#include "ControlProtocol.h"
#include "CSwitch.h"
#include "switch_cfg.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/** the sent */
static CSWITCH_States_t state = NORMAL;


static CSWITCH_States_t MyState = NORMAL;
static CSWITCH_PressedButton_t MyPbutton = NO_PRESSED;


static Message_t Mymsg;
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
static volatile uint8_t UPNumberOfPressed = 0;
static volatile uint32_t UPCounts = 0;
static volatile uint8_t DownNumberOfPressed = 0;
static volatile uint32_t DOWNCounts = 0;
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
static void CheckButtonsInNormalState(void);
static void CheckButtonsInStopWatchState(void);
static void CheckButtonsInEditState(void);
static void ReceiveCallBack(void);

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/
static void CheckButtonsInNormalState(void)
{
    uint32_t ButtonRead;
    Message_t msg;
    msg.MessageType = COMMAND;
    msg.CallBack =  NULL;
    msg.len = 1;
    SWITCH_enuGetStatus(UP_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {
        state = STOPWATCH;
        msg.pMessage[0] = 'S';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(DOWN_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {
        state = EDIT;
        msg.pMessage[0] = 'E';
        Protocol_SendAsync(&msg);
    }
}

static void CheckButtonsInStopWatchState(void)
{
    uint32_t ButtonRead;
    Message_t msg;
    msg.MessageType = COMMAND;
    msg.pMessage[0] = 'S';
    msg.CallBack =  NULL;
    msg.len = 2;
    SWITCH_enuGetStatus(UP_SWITCH,&ButtonRead);
    /** Go to start the stopwatch */
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {
        msg.pMessage[1] = 'G';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(RIGHT_SWITCH,&ButtonRead);
    /**Pause */
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {
        msg.pMessage[1] = 'P';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(DOWN_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {
        msg.pMessage[1] = 'Z';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(LEFT_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {
        msg.len = 1; 
        msg.pMessage[0] = 'N';
        msg.pMessage[1] = 0;
        Protocol_SendAsync(&msg);
        state = NORMAL;
        return;
    }
}


static void CheckButtonsInEditState(void)
{
    uint32_t ButtonRead;
    Message_t msg;
    msg.MessageType = COMMAND;
    msg.CallBack =  NULL;
    msg.len = 2;
    msg.pMessage[0] = 'E';
    UPCounts += 100;
    DOWNCounts += 100;
    SWITCH_enuGetStatus(UP_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED) UPNumberOfPressed++;
    if(UPCounts >= 1600)
    {
        UPCounts = 0;
        if(UPNumberOfPressed >= 1 && UPNumberOfPressed < 3)
        {
            msg.pMessage[1] = 'U';
            Protocol_SendAsync(&msg);
            UPNumberOfPressed = 0;
            return;
        }
    	else if(UPNumberOfPressed >= 3)
		{
            msg.pMessage[0] = 'N';
            msg.pMessage[1] = 'K';
            Protocol_SendAsync(&msg);
            state = NORMAL;
            UPNumberOfPressed = 0;
            return;
		}
    }
    SWITCH_enuGetStatus(DOWN_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED) DownNumberOfPressed++;
    if(DOWNCounts >= 1600)
    {
        if(DownNumberOfPressed >= 1 && DownNumberOfPressed < 3)
        {
            msg.pMessage[1] = 'D';
            Protocol_SendAsync(&msg);
            DownNumberOfPressed = 0;
            return;
        }
    	else if(DownNumberOfPressed >= 3)
		{
            /**Quit */
            msg.pMessage[1] = 'Q';
            msg.pMessage[0] = 'N';
            state = NORMAL;
            DownNumberOfPressed = 0;
            Protocol_SendAsync(&msg);
            return;
		}
        DownNumberOfPressed  = 0;
        DOWNCounts = 0;
    }
    SWITCH_enuGetStatus(RIGHT_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {

        msg.pMessage[1] = 'R';
        Protocol_SendAsync(&msg);
        return;
    }
    SWITCH_enuGetStatus(LEFT_SWITCH,&ButtonRead);
    if(ButtonRead == SWITCH_STATUS_PRESSED)
    {

        msg.pMessage[1] = 'L';
        Protocol_SendAsync(&msg);
        return;
    }
}

void ReceiveCallBack(void)
{
    if(Mymsg.pMessage[0] == 'N')
    {
        MyState = NORMAL;
    }
    else if(Mymsg.pMessage[0] == 'E')
    {
        MyState = EDIT;
    }
    else if(Mymsg.pMessage[0] == 'S')
    {
        MyState = STOPWATCH;
    }
    if(Mymsg.len == 2)
    {
        if(Mymsg.pMessage[1] == 'G')
        {
            MyPbutton = GO;
        }
        else if(Mymsg.pMessage[1] == 'L')
        {
            MyPbutton =  LEFT;
        }
        else if(Mymsg.pMessage[1] == 'R')
        {
            MyPbutton = RIGHT;
        }
        else if(Mymsg.pMessage[1] == 'Q')
        {
            MyPbutton = CANCEL;
        }
        else if(Mymsg.pMessage[1] == 'K')
        {
            MyPbutton = OK;
        }
        else if(Mymsg.pMessage[1] == 'U')
        {
            MyPbutton = UP;
        }
        else if(Mymsg.pMessage[1] == 'D')
        {
            MyPbutton = DOWN;
        }
        else if(Mymsg.pMessage[1] == 'P')
        {
            MyPbutton = PAUSE;
        }
        else if(Mymsg.pMessage[1] == 'Z')
        {
            MyPbutton = RESET;
        }
    }
}

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
void CSWITCH_Init(void)
{
    Protocol_Init();
	SWITCH_enuInit();
    Mymsg.CallBack = ReceiveCallBack;
    Protocol_ReceiveAsync(&Mymsg);
}

void CSWIRCH_SendUpdate(void)
{
    switch (state)
    {
    case NORMAL:
        CheckButtonsInNormalState();
        break;
    case STOPWATCH:
        CheckButtonsInStopWatchState();
        break;
    case EDIT:
        CheckButtonsInEditState();
        break;
    default:
        break;
    }
}

CSWITCH_ErrorStatus_t CSWIRCH_ReceivedUpdate(CSWITCH_ScreenState_t * Updates)
{
    CSWITCH_ErrorStatus_t RET_ErrorStatus = CSWITCH_OK;
    if(Updates != NULL)
    {
        Updates->button = MyPbutton;
        Updates->state  = MyState;
    }
    else
    {
        RET_ErrorStatus = CSWITCH_NULL_PTR_PASSES;
    }
    return  RET_ErrorStatus;
}

/******************************************************************************/