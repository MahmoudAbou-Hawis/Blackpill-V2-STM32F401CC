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
    /** put your initialization here */
}

void TFT_COM::TFT_SelectPin(uint32_t pinNumber, uint8_t value)
{
    /** implement control pin value 1 mean is high value 0 mean low */
}

void TFT_COM::TFT_WaitMicroSeconds(uint32_t Time)
{
    
}


void TFT_COM::TFT_SendSPI(uint8_t data)
{
 
}