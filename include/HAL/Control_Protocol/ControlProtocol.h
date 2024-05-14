/*******************************************************************************/
/**
 * @file ControlProtocol.h
 * @brief Header file for the control protocol.
 * 
 * @par Project Name
 * Control Protocol 
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines the functions and data structures used for communication
 * between the micro-controllers. It provides a hardware-
 * independent interface for sending and receiving control messages.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 *******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef CONTROL_PROTOCOL_H_
#define CONTROL_PROTOCOL_H_
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
#include <stdbool.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

#define NUMBER_OF_DATA                  (8U)

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

typedef enum
{
    PROTOCOL_OK,
    PROTOCOL_ERROR
} PROTOCOL_ErrorStatus_t;


/* Enum defining the type of message */
typedef enum
{
    COMMAND,    /**< Command message */
    DATA        /**< Data message */
} MsgType_t;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/* Callback function type */
typedef void (*Protocol_CallBack)(void);

/* Struct defining a  message */
typedef struct 
{
    MsgType_t MessageType;          /**< Type of the message (Command or Data) */
    char  pMessage[NUMBER_OF_DATA]; /**< Pointer to the message data */
    uint16_t len;                   /**< Length of the message data */
    Protocol_CallBack CallBack;     /**< Callback function for message handling */
} Message_t;

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

/** @brief Initializes the control protocol
 *  @return Error Status
 */
PROTOCOL_ErrorStatus_t Protocol_Init(void);

/** @brief Sends a message asynchronously 
 *  @param[in] msg Pointer to the message to be sent
 *  @return Error Status
 */
PROTOCOL_ErrorStatus_t Protocol_SendAsync(Message_t * msg);

/** @brief Receives a message asynchronously 
 *  @param[in out] Frame Pointer to store the received message
 *  @return Error Status
 */
PROTOCOL_ErrorStatus_t Protocol_ReceiveAsync(Message_t* msg);
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
#endif /* CONTROL_PROTOCOL_H_ */
/******************************************************************************/
