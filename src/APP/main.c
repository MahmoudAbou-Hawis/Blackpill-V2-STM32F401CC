#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_uart.h"
#include "stm32f4xx_nvic.h"
#include "led.h"
#include "switch.h"
#include "schedular.h"
#include "CHAR_LCD.h"

char arr[8] = "Mahmoud";

char arr2[7] = "";

UART_Handle_t uart_handle;


void CALLBACK(void)
{
	UART_TransmitTimeOut(&uart_handle,arr2,7,-1);
}
int main(void)
{

 	RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);
	RCC_enuEnablePeripheral(PERIPHERAL_USART1);
	NVIC_EnableIRQ(USART1_IRQn);
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
	
	UART_TransmitAsyncZeroCopy(&uart_handle,arr,7,NULL);
	UART_TransmitAsyncZeroCopy(&uart_handle,arr,7,NULL);
	UART_ReceiveAsyncZeroCopy(&uart_handle,arr2,7,CALLBACK);
	UART_ReceiveAsyncZeroCopy(&uart_handle,arr2,7,CALLBACK);
	///UART_TransmitAsyncZeroCopy(&uart_handle,arr,7,NULL);
	while(1)
	{
	}
	//LCD_InitAsync(callBack);

	//schedular_init();
	//schedular_start();

    return 0;
}
#endif