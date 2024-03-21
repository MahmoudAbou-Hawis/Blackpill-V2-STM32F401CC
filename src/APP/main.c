#include "AppCFG.h"

#if CFG_IS_CURRENT_APP(CFG_APP_MAIN)
#include "stm32f4xx_rcc.h"
#include "led.h"
#include "switch.h"
#include "schedular.h"
#include "CHAR_LCD.h"


char arr[7] = "Mahmoud";

char arr1[7] = "sofar#1";

void callBack(void)
{
	LCD_WriteStringAsyncZeroCopy(arr,7,NULL);
}
static uint32_t cnt = 0;
void runnable(void)
{
	if(cnt == 12000)
	{
		LCD_WriteStringAsyncZeroCopy(arr1,7,NULL);
	}
	else if(cnt == 8000){
		LCD_SetCursorAsync(1,9,NULL);
	}
	cnt+= 4000;
}

int main(void)
{

 	RCC_enuEnablePeripheral(PERIPHERAL_GPIOA);

	LCD_InitAsync(callBack);

	schedular_init();
	schedular_start();

    return 0;
}
#endif