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
#include "ControlProtocol.h"
#include "protocol_physical__layer.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

#define FRAME_SIZE                         (26U)

#define FRAME_SIZE_IN_SEGMENTS             (13U)

#define MAXIMUM_FRAMES_FOR_MSG             (4U)

#define START_FRAME_SEG                    (0U)

#define DATA_TYPE_SEG                      (1U)  
#define DATA_LEN_SEG                       (2U)

#define CHECKSUM_SEG                       (11U)
#define END_FRAME_SEG                      (12U)


/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

#define GET_NUMBER_OF_FRAMES(MSG_LEN)  ((MSG_LEN + 7) / 8)

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

typedef struct 
{
    uint8_t order;
    uint8_t data;
} Segment_t;

typedef struct
{
    Segment_t Segment[FRAME_SIZE_IN_SEGMENTS];
} Frame_t;

typedef struct 
{
    bool isStartSent;

} ReceivedMsg;


/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
static Frame_t messageToSend = {0};
static Frame_t messageToReceive = {0};

static ReceivedMsg receivedMsg   = {0};
static Segment_t SegmentReceived = {0};


static Message_t * received = NULL;
static Message_t * sent     = NULL; 

Frame_t ACK = 
{
    .Segment[START_FRAME_SEG].order = 0,
    .Segment[START_FRAME_SEG].data = 0xff,
    .Segment[DATA_LEN_SEG].order = DATA_LEN_SEG,
    .Segment[DATA_LEN_SEG].data = 255,
    .Segment[END_FRAME_SEG].data = 0xff,
    .Segment[END_FRAME_SEG].order = END_FRAME_SEG
};


Frame_t sendDataAgain = 
{
    .Segment[START_FRAME_SEG].order = 0,
    .Segment[START_FRAME_SEG].data = 0xff,
    .Segment[DATA_TYPE_SEG].order = DATA_TYPE_SEG,
    .Segment[DATA_TYPE_SEG].data = DATA,
    .Segment[END_FRAME_SEG].data = 0xff,
    .Segment[END_FRAME_SEG].order = END_FRAME_SEG
};



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
static void ConvertMsgToFrames(Message_t * msg);
static void ConvertFramesToMsg(Frame_t * msg);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/
static void ConvertMsgToFrames(Message_t * msg)
{
    /**This variable carry the checksum of the data*/
    uint8_t CheckSum = 0;

    /** Set the start of the frame */
    messageToSend.Segment[START_FRAME_SEG].data = 0xff;
    messageToSend.Segment[DATA_LEN_SEG].data = msg->len;
    messageToSend.Segment[DATA_TYPE_SEG].data = msg->MessageType;

    /**Set the date and calculate the check in the frame only */
    for(uint8_t DataSegmentIdx = 3 ; DataSegmentIdx < FRAME_SIZE_IN_SEGMENTS-2 ; DataSegmentIdx++)
    {
        if(DataSegmentIdx -3 < msg->len)
        {
            messageToSend.Segment[DataSegmentIdx].data 
            = msg->pMessage[DataSegmentIdx - 3];
            CheckSum += msg->pMessage[DataSegmentIdx - 3];
        }
        else
        {
            messageToSend.Segment[DataSegmentIdx].data = 0;
        }
    }

    /**set the checksum and the end of the frame */
    messageToSend.Segment[CHECKSUM_SEG].data = CheckSum;
    messageToSend.Segment[END_FRAME_SEG].data = 0xff;
}

static void ConvertFramesToMsg(Frame_t * frame)
{
    received->len = frame->Segment[DATA_LEN_SEG].data;
    received->MessageType = frame->Segment[DATA_TYPE_SEG].data;
    for(uint8_t Data = 3; Data < FRAME_SIZE_IN_SEGMENTS -2 ; Data++)
    {
        received->pMessage[Data-3] = frame->Segment[Data].data;
    }
}

void ProtocolReceiveCallBack(void)
{
    if(SegmentReceived.order == 0  && SegmentReceived.data == 255 )
    {
        receivedMsg.isStartSent = true;
    }
    if(SegmentReceived.order == 12 && SegmentReceived.data == 255 && receivedMsg.isStartSent == true)
    {
        receivedMsg.isStartSent = false;
        if(messageToReceive.Segment[DATA_LEN_SEG].data == 255)
        {
            if(sent->CallBack != NULL) sent->CallBack();
        }
        else if(messageToReceive.Segment[DATA_TYPE_SEG].data == DATA)
        {
            HardWare_Send((char *)(&messageToSend),FRAME_SIZE);
        }
        else
        {
            uint8_t Checksum = 0;
            for(uint8_t DataIdx = 3 ;DataIdx <  FRAME_SIZE_IN_SEGMENTS-2 ; DataIdx++ )
            {
                Checksum += messageToReceive.Segment[DataIdx].data;
            }
            if(Checksum == messageToReceive.Segment[CHECKSUM_SEG].data)
            {
                ConvertFramesToMsg(&messageToReceive);
                if(received->CallBack != NULL)
                {
                    received->CallBack();
                }
                HardWare_Send((char*)(&ACK),FRAME_SIZE);
            }
            else
            {
                HardWare_Send((char*)(&sendDataAgain),FRAME_SIZE);
            }
        }
    }
    messageToReceive.Segment[SegmentReceived.order].order = SegmentReceived.order;
    messageToReceive.Segment[SegmentReceived.order].data = SegmentReceived.data;
    HardWare_Receive((char*)(&SegmentReceived),2);
}

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/


PROTOCOL_ErrorStatus_t Protocol_Init(void)
{
    HardWare_Init(ProtocolReceiveCallBack);
    receivedMsg.isStartSent = false;
    HardWare_Receive((char*)(&SegmentReceived),2);
    for(uint8_t Frame = 0 ; Frame < MAXIMUM_FRAMES_FOR_MSG ; Frame++)
    {
        for(uint8_t SegmentIdx = 0 ; SegmentIdx < FRAME_SIZE_IN_SEGMENTS ; SegmentIdx++)
        {
            messageToSend.Segment[SegmentIdx].order = SegmentIdx;
        }
    }
    return PROTOCOL_OK;
}

PROTOCOL_ErrorStatus_t Protocol_SendAsync(Message_t * msg)
{
    PROTOCOL_ErrorStatus_t RET_ErrorStatus = PROTOCOL_OK;
    if(msg != NULL)
    {
        sent = msg;
        ConvertMsgToFrames(sent);
        HardWare_Send((char*)(&messageToSend),FRAME_SIZE);
    }
    else
    {
        RET_ErrorStatus = PROTOCOL_ERROR;
    }
    return RET_ErrorStatus;
}

PROTOCOL_ErrorStatus_t Protocol_ReceiveAsync(Message_t* msg)
{
    PROTOCOL_ErrorStatus_t RET_ErrorStatus = PROTOCOL_OK;
    if(msg != NULL)
    {
        received = msg;
        received->len = 0;
    }
    else
    {
        RET_ErrorStatus = PROTOCOL_ERROR;
    }
    return RET_ErrorStatus;
}


/******************************************************************************/