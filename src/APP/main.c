#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "stm32f4xx_rcc.h"
#include "led.h"
#include "switch.h"
#include "schedular.h"
uint8_t LedState = 0;


int main(void)
{

	RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);
	RCC_enuEnablePeripheral(PERIPHERAL_GPIOC);

	LED_enuInit();	

	schedular_init();
	schedular_start();

    return 0;
}
#endif