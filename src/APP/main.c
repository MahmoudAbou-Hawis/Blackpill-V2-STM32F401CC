#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "stm32f4xx_rcc.h"
#include "led.h"
#include "switch.h"
#include "schedular.h"

uint32_t switchState = SWITCH_STATUS_NOT_PRESSED;

void App(void)
{
	SWITCH_enuGetStatus(ALARM_SWITCH,&switchState);
	if(switchState == SWITCH_STATUS_PRESSED)
	{
		LED_enuSetStatus(ALARM_LED,LED_STATE_ON);
	}
	else
	{
		LED_enuSetStatus(ALARM_LED,LED_STATE_OFF);
	}
}

int main(void)
{
	
	RCC_enuSetPrescaler(BUS_AHB_PRE_DIV2);
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

	LED_enuInit();	
	SWITCH_enuInit();

	schedular_init();
	schedular_start();

    return 0;
}
#endif