#include <stdint.h>

namespace display
{
    class TFT_COM
    {
        protected:
            TFT_COM();
            void TFT_SendSPI(uint8_t data) ;
            void TFT_WaitMicroSeconds(uint32_t Time) ;
            void TFT_SelectPin(uint32_t pinNumber, uint8_t value) ;
    };
};