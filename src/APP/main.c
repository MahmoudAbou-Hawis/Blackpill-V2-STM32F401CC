#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

int main(void)
{
	volatile int var = 0;

	RCC_enuSetPrescaler(BUS_AHB_PRE__DIV2);
	RCC_stPLLconfig_t pllcfg;
	pllcfg.PLLSource = CLK_HSI;
	pllcfg.PLLM = 8;
	pllcfg.PLLN = 252;
	pllcfg.PLLP = 6;
	RCC_enuConfigPLL(&pllcfg);
	RCC_enuEnableClk(CLK_PLL);
	RCC_enuSetSysClk(SYSCLK_PLL);

	RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);
	RCC_enuEnablePeripheral(PERIPHERAL_GPIOC);

	gpioPin_t led = 
	{
		.GPIO_Mode  = GPIO_MODE_OUT_PP ,
		.GPIO_Port  = GPIO_PORTA ,
		.GPIO_Speed = GPIO_SPEED_VERY_HIGH ,
		.GPIO_Pin   = GPIO_PIN0
	}; 
	

	gpioPin_t Switch = 
	{
		.GPIO_Mode  = GPIO_MODE_IN_PU,
		.GPIO_Port  = GPIO_PORTC ,
		.GPIO_Speed = GPIO_SPEED_VERY_HIGH ,
		.GPIO_Pin   = GPIO_PIN15
	}; 

	GPIO_Init(&led);
	GPIO_Init(&Switch);

	uint32_t  Switch_READ; 
    while (1)
    {
		GPIO_GetPinValue(Switch.GPIO_Port,Switch.GPIO_Pin,&Switch_READ);
		if(Switch_READ == GPIO_STATE_RESET)
		{
			GPIO_SetPinValue(led.GPIO_Port,led.GPIO_Pin,GPIO_STATE_SET);
		}
		else
		{
			GPIO_SetPinValue(led.GPIO_Port,led.GPIO_Pin,GPIO_STATE_RESET);
		}
    }
    
    return 0;
}
#endif