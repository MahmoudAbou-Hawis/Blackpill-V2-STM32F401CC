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
#include "protocol_physical__layer.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_nvic.h"
#include "stm32f4xx_uart.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/


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

static void *  uart = USART1 + 0x4;
static DMA_Handle_t handle;
static DMA_Handle_t handle2;
static UART_Handle_t uart_handle;
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
void HardWare_Init(void (*CallBack)(void))
{
	
	RCC_enuEnablePeripheral(PERIPHERAL_DMA2);   
	RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);
	RCC_enuEnablePeripheral(PERIPHERAL_USART1);

	NVIC_EnableIRQ(DMA2_Stream5_IRQn);
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);

	NVIC_EnableIRQ(USART1_IRQn);


	handle.Instance					 	= DMA2;
	handle.Stream   					= DMA_STREAM_7;
	handle.Initialization.Channel   	= DMA_CHANNEL_4;
	handle.Initialization.Direction 	= DMA_MEMORY_TO_PERIPH;
	handle.Initialization.FIFOMode  	= DMA_FIFOMODE_DISABLE;
	handle.Initialization.MemAlignment  = DMA_MDATAALIGN_BYTE;
	handle.Initialization.MemBurst		= DMA_MBURST_SINGLE;
	handle.Initialization.MemInc		= DMA_MEMORY_INCREMENT_ENABLED;
	handle.Initialization.Mode			= DMA_NORMAL;
	handle.Initialization.Priority      = DMA_PRIORITY_VERY_HIGH;
	handle.Initialization.PerAlignment	= DMA_PDATAALIGN_BYTE;
	handle.Initialization.PeriphInc		= DMA_PERIPHERAL_INCREMENT_DISABLED;
	handle.Initialization.PeriphBurst	= DMA_PBURST_SINGLE;
	handle.CompleteTransferCallBack = NULL;
	handle.HalfTransferCallBack = NULL;
	handle.ErrorTransferCallBack = NULL;

	handle2.Instance					 = DMA2;
	handle2.Stream   					=  DMA_STREAM_5;
	handle2.Initialization.Channel   	= DMA_CHANNEL_4;
	handle2.Initialization.Direction 	= DMA_PERIPH_TO_MEMORY;
	handle2.Initialization.FIFOMode  	= DMA_FIFOMODE_DISABLE;
	handle2.Initialization.MemAlignment  = DMA_MDATAALIGN_BYTE;
	handle2.Initialization.MemBurst		= DMA_MBURST_SINGLE;
	handle2.Initialization.MemInc		= DMA_MEMORY_INCREMENT_ENABLED;
	handle2.Initialization.Mode			= DMA_NORMAL;
	handle2.Initialization.Priority      = DMA_PRIORITY_VERY_HIGH;
	handle2.Initialization.PerAlignment	= DMA_PDATAALIGN_BYTE;
	handle2.Initialization.PeriphInc		= DMA_PERIPHERAL_INCREMENT_DISABLED;
	handle2.Initialization.PeriphBurst	= DMA_PBURST_SINGLE;
	handle2.CompleteTransferCallBack = CallBack;
	handle2.HalfTransferCallBack = NULL;
	handle2.ErrorTransferCallBack = NULL;
	DMA_Init(&handle,-1);
	DMA_Init(&handle2,-1);


	gpioPin_t TX;
	gpioPin_t RX;

	TX.GPIO_AT_Type = GPIO_AT_PushPull;
	TX.GPIO_Mode    = GPIO_MODE_AF7;
	TX.GPIO_Pin	    = GPIO_PIN9;
	TX.GPIO_Port	= GPIO_PORTA;
	TX.GPIO_Speed	= GPIO_SPEED_MEDIUM;

	RX.GPIO_AT_Type = GPIO_AT_PullDown;
	RX.GPIO_Mode    = GPIO_MODE_AF7;
	RX.GPIO_Pin	    = GPIO_PIN10;
	RX.GPIO_Port	= GPIO_PORTA;
	RX.GPIO_Speed	= GPIO_SPEED_MEDIUM;

	GPIO_Init(&TX);
	GPIO_Init(&RX);


	uart_handle.pUartInstance 				= USART1;
	uart_handle.UartConfiguration.BaudRate 	= 9600;
	uart_handle.UartConfiguration.Mode 		= UART_MODE_TX_RX;
	uart_handle.UartConfiguration.Parity 		= UART_PARITY_NONE;
	uart_handle.UartConfiguration.StopBits 	= UART_STOP_BITS_ONE;
	uart_handle.UartConfiguration.WordLength 	= UART_WORDLENGTH_8B;
	uart_handle.UartConfiguration.OverSampling = UART_OVERSAMPLING_8; 

	UART_Init(&uart_handle);
	UART_TransmitWithDMA(&uart_handle,NULL);
	UART_ReceiveWithDMA(&uart_handle);
}

void HardWare_Send(char * data, uint8_t len)
{
    DMA_StartInterrupt(&handle,data,uart,len);
}

void HardWare_Receive(char * data, uint8_t len)
{
    DMA_StartInterrupt(&handle2,uart,data,len);
}
/******************************************************************************/