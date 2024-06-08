#include <TFT_Port.hpp>

using namespace display;

extern "C"
{

    #include "TFT_Conf.hpp"

    /** Your drivers which do these functionalities */
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_spi.h"
    #include "stm32f4xx_systick.h"
    #include "stm32f4xx_rcc.h"
}

SPI_Handle_t SPI;
gpioPin_t MOSI, MISO, SS , CLK , A0;

TFT_COM::TFT_COM()
{
    
    RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);
	RCC_enuEnablePeripheral(PERIPHERAL_SPI1);
	
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
	SS.GPIO_Speed   = GPIO_SPEED_VERY_HIGH;


	A0.GPIO_AT_Type = GPIO_AT_None;
	A0.GPIO_Mode    = GPIO_MODE_OUT_PP;
	A0.GPIO_Pin 	= GPIO_PIN2;
	A0.GPIO_Port    = GPIO_PORTA;
	A0.GPIO_Speed   = GPIO_SPEED_VERY_HIGH;

	GPIO_Init(&MISO);
	GPIO_Init(&MOSI);
	GPIO_Init(&SS);
	GPIO_Init(&CLK);
	GPIO_Init(&A0);

	SPI.Instance = SPI1;
	SPI.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_4;
	SPI.Init.CLKPhase			= SPI_PHASE_SECOND_EDGE;
	SPI.Init.CLKPolarity		= SPI_POLARITY_HIGH;
	SPI.Init.DataSize			= SPI_DATASIZE_8BIT;
	SPI.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
	SPI.Init.Mode				= SPI_MODE_MASTER;
	SPI.Init.ByteOrder			= SPI_BYTEORDER_MSB;
	SPI.Init.NSS				= SPI_NSS_SOFT;
	SPI.Init.CRCPolynomial		= 10;

	SPI_Init(&SPI);
	SysTick_CFG_t SysTickConf = 
    {
        .CLK = 16000000,
        .CLKSOURCE = SYSTICK_CLKSRC_AHB_DIV_8
    };

    /**configure the sys timer */
    SysTick_Config(&SysTickConf);
    SysTick_SetTimeMS(1);
}

void TFT_COM::TFT_SelectPin(uint32_t pinNumber, uint8_t value)
{
    if(pinNumber == A0_PIN_IDX)
    {
        if(value == 0)
		{
			GPIO_SetPinValue(A0.GPIO_Port,A0.GPIO_Pin,GPIO_STATE_RESET);
		}
		else
		{
			GPIO_SetPinValue(A0.GPIO_Port,A0.GPIO_Pin,GPIO_STATE_SET);
		}
    }
    else if(pinNumber == RST_PIN_IDX)
    {
        if(value == 0)
		{
			GPIO_SetPinValue(SS.GPIO_Port,SS.GPIO_Pin,GPIO_STATE_RESET);
		}
		else
		{
			GPIO_SetPinValue(SS.GPIO_Port,SS.GPIO_Pin,GPIO_STATE_SET);
		}
    }
    else
    {
        /** No thing */
    }
}

void TFT_COM::TFT_WaitMicroSeconds(uint32_t Time)
{
    SysTick_DelayMicroSeconds(Time);
}


void TFT_COM::TFT_SendSPI(uint8_t data)
{
    SPI_Transmit(&SPI,&data,1,-1);
}