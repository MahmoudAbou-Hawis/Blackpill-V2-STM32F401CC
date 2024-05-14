#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MASTER)


#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"


SPI_Handle_t SPI;



int main(void)
 {
	/*
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
 */
	RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);
	RCC_enuEnablePeripheral(PERIPHERAL_SPI1);

	gpioPin_t MOSI, MISO, SS , CLK;

	MISO.GPIO_Pin = GPIO_PIN6;
	MISO.GPIO_Mode = GPIO_MODE_AF5;
	MISO.GPIO_Speed = GPIO_SPEED_HIGH;
	MISO.GPIO_Port  = GPIO_PORTA;
	MISO.GPIO_AT_Type = GPIO_AT_PullDown;


	MOSI.GPIO_Pin = GPIO_PIN7;
	MOSI.GPIO_Mode = GPIO_MODE_AF5;
	MOSI.GPIO_Speed = GPIO_SPEED_HIGH;
	MOSI.GPIO_Port  = GPIO_PORTA;
	MOSI.GPIO_AT_Type = GPIO_AT_PullUp;

	
	CLK.GPIO_Pin = GPIO_PIN5;
	CLK.GPIO_Mode = GPIO_MODE_AF5;
	CLK.GPIO_Speed = GPIO_SPEED_HIGH;
	CLK.GPIO_Port  = GPIO_PORTA;
	CLK.GPIO_AT_Type = GPIO_AT_PullUp;

	SS.GPIO_AT_Type = GPIO_AT_None;
	SS.GPIO_Mode    = GPIO_MODE_OUT_PP;
	SS.GPIO_Pin 	= GPIO_PIN0;
	SS.GPIO_Port    = GPIO_PORTA;
	SS.GPIO_Speed   = GPIO_SPEED_HIGH;

	GPIO_Init(&MISO);
	GPIO_Init(&MOSI);
	GPIO_Init(&SS);
	GPIO_Init(&CLK);


	SPI.Instance = SPI1;
	SPI.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_4;
	SPI.Init.CLKPhase			= SPI_PHASE_FIRST_EDGE;
	SPI.Init.CLKPolarity		= SPI_POLARITY_LOW;
	SPI.Init.DataSize			= SPI_DATASIZE_8BIT;
	SPI.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
	SPI.Init.Mode				= SPI_MODE_MASTER;
	SPI.Init.ByteOrder			= SPI_BYTEORDER_MSB;
	SPI.Init.NSS				= SPI_NSS_SOFT;
	SPI.Init.CRCPolynomial		= 10;

	SPI_Init(&SPI);
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_RESET);
	uint8_t  data[6] = "Mahmo";
	while(1)
	{
		SPI_Transmit(&SPI,data,5,-1);
	}
    return 0;
}
#endif