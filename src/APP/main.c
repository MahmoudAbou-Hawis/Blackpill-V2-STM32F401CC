#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "stm32f4xx_rcc.h"
#include "led.h"
#include "switch.h"
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


	uint32_t  Switch_READ; 
    while (1)
    {	
		SWITCH_enuGetStatus(ALARM_SWITCH,&Switch_READ);
		if(Switch_READ == SWITCH_STATUS_PRESSED)
		{
			LED_enuSetStatus(ALARM_LED,LED_STATE_ON);
		}
		else
		{
			LED_enuSetStatus(ALARM_LED,LED_STATE_OFF);
		}
    }
    
    return 0;
}
#endif