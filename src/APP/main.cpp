#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MASTER)


#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_systick.h"
#include "Amr.h"
#include "TFT.hpp"

SPI_Handle_t SPI;
gpioPin_t MOSI, MISO, SS , CLK , A0;

void sendCommand(uint8_t command)
{
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_STATE_RESET);

	SPI_Transmit(&SPI,&command,1,-1);
}


void sendData(uint8_t command)
{
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN2,GPIO_STATE_SET);

	SPI_Transmit(&SPI,&command,1,-1);
}

void init()
{
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_SET);
	SysTick_DelayMicroSeconds(100);
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_RESET);
	SysTick_DelayMicroSeconds(3);
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_SET);
	SysTick_DelayMicroSeconds(100);
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_RESET);
	SysTick_DelayMicroSeconds(100);
	GPIO_SetPinValue(GPIO_PORTA,GPIO_PIN0,GPIO_STATE_SET);
	SysTick_DelayMicroSeconds(120000);
	sendCommand(0x11);
	SysTick_DelayMicroSeconds(150000);
	sendCommand(0x3A);
	sendData(0x05);
	sendCommand(0x29);
}

void HTFT_voidDisplay(const uint16_t* Copy_pu16Image)
{
	uint16_t counter;
	sendCommand(0x2A);
	sendData(0);
	sendData(0);
	sendData(0);
	sendData(127);
	sendCommand(0x2B);
	sendData(0);
	sendData(0);
	sendData(0);
	sendData(159);
	sendCommand(0x2C);
	for(counter =0; counter < 20480; counter++)
	{
		sendData(Copy_pu16Image[counter]>>8);
		sendData(Copy_pu16Image[counter]&0x00ff);
	}
}


void setPin(uint32_t id,uint8_t state)
{
	if(id == 0)
	{
		if(state == 0)
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
		if(state == 0)
		{
			GPIO_SetPinValue(A0.GPIO_Port,A0.GPIO_Pin,GPIO_STATE_RESET);
		}
		else
		{
			GPIO_SetPinValue(A0.GPIO_Port,A0.GPIO_Pin,GPIO_STATE_SET);
		}
	}
}
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


	display::point start{128,160};
	display::point end{1,1};

	display::TFT screen{128,160,[](uint32_t Time){SysTick_DelayMicroSeconds(Time);},
	setPin,[](uint8_t data){SPI_Transmit(&SPI,&data,1,-1);},0,1};

	//screen.WriteText("Mahmoud muhammef mahmoud said-Ahmed Abou-Hawis",display::Fonts::Font_11X18,display::Colors::RED,display::Colors::YELLOW,&start);
  	screen.DrawLine(&start, &end, display::Colors::BLACK);	

	start = {128,30};
	end = {1,0};
	  	screen.DrawLine(&start, &end, display::Colors::BLACK);	

	while(1)
	{

	}
    return 0;
}
#endif