/******************************************************************************/
/**
 * @file stm32f4xx_rcc.c
 * @brief Source file for STM32F401 microcontroller.
 *
 * @par Project Name
 * STM32F4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the source code for controlling and interacting with
 * the STM32F401 microcontroller. It includes initialization functions,
 * peripheral configurations.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/


/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "stm32f4xx_rcc.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/**
 * @brief this is RCC base address , in Memory Map section p.38 in reference
 * manual.
 */
#define              RCC_BASE_ADD                       ((uint32_t)0x40023800)


/**
 * @brief  pointer to the RCC (Reset and Clock Control) register, it allows
 * access the RCC registers.
 */
#define              RCC                                ((volatile stRCC_t* const)RCC_BASE_ADD)

/**
 * @brief Maximum allowable value for PLLM.
 */
#define              PLLM_MAX                           ((uint32_t)63)


/**
 * @brief Maximum allowable value for PLLM.
 */
#define              PLLM_MIN                           ((uint32_t)2)


/**
 * @brief Maximum allowable value for PLLM.
 */
#define              PLLN_MAX                           ((uint32_t)432)


/**
 * @brief Minimum allowable value for PLLM.
 */
#define              PLLN_MIN                           ((uint32_t)192)


/**
 * @brief represent the HSI frequency.
 */
#define               HSI_FREQ                          ((uint32_t)16)

/**
 * represent the pll max frequency as system clock.
 */
#define               PLL_MAX_FRQ                       ((uint32_t)84)


/**
 *@brief Maximum frequency (in MHz) supported by the external high-speed
 *       oscillator (HSE).
 */
#define               HSE_MAX_FRQ                       ((uint32_t)26)

/**
 *@brief Minimum frequency (in MHz) supported by the external high-speed
 *       oscillator (HSE).
 */
#define               HSE_MIN_FRQ                       ((uint32_t)4)


/**
 * @brief Bit position indicating the readiness of the High-Speed External
 *       (HSE) oscillator.
 */
#define               HSE_RDY                           ((uint32_t)131072)


/**
 * @brief Bit position indicating the readiness of the High-Speed Internal
 *       (HSI) oscillator.
 */
#define               HSI_RDY                           ((uint32_t)2)

/**
 * @brief Bit position indicating the readiness of the Phase-Locked Loop
 *       (PLL) oscillator.
 */
#define               PLL_RDY                           ((uint32_t)33554432)

/**
 * @brief to clear the system clock .
 */
#define               SYSCLK_CLR                        ((uint32_t)4294967292)


/**
 * @brief Bits representing the current system clock.
 */
#define              CURRENT_SYSCLK                     ((uint32_t)12)

/**
 * @brief represent the AHB1 bus.
 */
#define              AHB1_BUS                           ((uint32_t)2)

/**
 * @brief represent the APB1 bus.
 */
#define              APB1_BUS                           ((uint32_t)0)

/**
 * @brief represent the APB2 bus.
 */
#define              APB2_BUS                           ((uint32_t)1)
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/



/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/**
 * @brief RCC (Reset and Clock Control) Register Map
 *
 * @par This struct represents the register map for the RCC (Reset and Clock Control)
 * module of the STM32F401 microcontroller. The RCC module is responsible for
 * controlling and configuring the system and peripheral clocks.
 *
 * @par The struct contains members corresponding to various registers within the RCC
 * module, each controlling different aspects of clock configuration and peripheral
 * control. These registers include clock control, PLL configuration, clock configuration,
 * interrupt control, peripheral reset, peripheral clock enable, low-power peripheral
 * clock enable, backup domain control, clock control and status, spread spectrum
 * clock generation, PLLI2S configuration, PLLSAI configuration, and dedicated clock
 * configuration.
 */
typedef struct
{
    volatile uint32_t CR;        /**< RCC Clock Control Register */
    volatile uint32_t PLLCFGR;   /**< RCC PLL Configuration Register */
    volatile uint32_t CFGR;      /**< RCC Clock Configuration Register */
    volatile uint32_t CIR;       /**< RCC Clock Interrupt Register */
    volatile uint32_t AHB1RSTR;  /**< RCC AHB1 Peripheral Reset Register */
    volatile uint32_t AHB2RSTR;  /**< RCC AHB2 Peripheral Reset Register */
    volatile uint32_t RESERVED_0;/**< Reserved */
    volatile uint32_t RESERVED_1;/**< Reserved */
    volatile uint32_t APB1RSTR;  /**< RCC APB1 Peripheral Reset Register */
    volatile uint32_t APB2RSTR;  /**< RCC APB2 Peripheral Reset Register */
    volatile uint32_t RESERVED_2;/**< Reserved */
    volatile uint32_t RESERVED_3;/**< Reserved */
    volatile uint32_t AHB1ENR;   /**< RCC AHB1 Peripheral Clock Enable Register */
    volatile uint32_t AHB2ENR;   /**< RCC AHB2 Peripheral Clock Enable Register */
    volatile uint32_t RESERVED_4;/**< Reserved */
    volatile uint32_t RESERVED_5;/**< Reserved */
    volatile uint32_t APB1ENR;   /**< RCC APB1 Peripheral Clock Enable Register */
    volatile uint32_t APB2ENR;   /**< RCC APB2 Peripheral Clock Enable Register */
    volatile uint32_t AHB1LPENR; /**< RCC AHB1 Peripheral Clock Enable in Low Power Mode Register */
    volatile uint32_t AHB2LPENR; /**< RCC AHB2 Peripheral Clock Enable in Low Power Mode Register */
    volatile uint32_t APB1LPENR; /**< RCC APB1 Peripheral Clock Enable in Low Power Mode Register */
    volatile uint32_t APB2LPENR; /**< RCC APB2 Peripheral Clock Enable in Low Power Mode Register */
    volatile uint32_t BDCR;      /**< RCC Backup Domain Control Register */
    volatile uint32_t CSR;       /**< RCC Clock Control & Status Register */
    volatile uint32_t SSCGR;     /**< RCC Spread Spectrum Clock Generation Register */
    volatile uint32_t PLLI2SCFGR;/**< RCC PLLI2S Configuration Register */
    volatile uint32_t PLLSAICFGR;/**< RCC PLLSAI Configuration Register */
    volatile uint32_t DCKCFGR;   /**< RCC Dedicated Clock Configuration Register */
} stRCC_t;



/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

static uint32_t HSEFreq = 4294967295;
static uint8_t isPLLConfigured = 0;
static uint8_t u8PllSrc = -1;
/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DEFINITIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES */
/******************************************************************************/
static RCC_enuErrorStatus isPLLWorking(void);
static RCC_enuErrorStatus isHSEWorking(void);
static RCC_enuErrorStatus isHSIWorking(void);
static RCC_enuErrorStatus isPllConfigIsCorrect(
                          RCC_stPLLconfig_t * const RCC_stConfig
                          );
static uint32_t u32GetSysClk(void);
/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/
static RCC_enuErrorStatus isPLLWorking(void)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_PLL_IS_DISABLED;
    uint32_t isPLLactive = (RCC->CR & CLK_PLL);
    if(isPLLactive)
    {
        RET_enuErrorStatus = RCC_PLL_IS_WORKING;
    }
    else
    {
        // No thing
    }
    return RET_enuErrorStatus;
}

static RCC_enuErrorStatus isHSEWorking(void)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_HSE_IS_DISABLED;
    uint32_t isHSEactive = (RCC->CR & CLK_HSE);
    if(isHSEactive)
    {
        RET_enuErrorStatus = RCC_HSE_IS_WORKING;
    }
    else
    {
        // No thing
    }
    return RET_enuErrorStatus;
}


static RCC_enuErrorStatus isHSIWorking(void)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_HSI_IS_DISABLED;
    uint32_t isHSIactive = (RCC->CR & CLK_HSI);
    if(isHSIactive)
    {
        RET_enuErrorStatus = RCC_HSI_IS_WORKING;
    }
    else
    {
        // No thing
    }
    return RET_enuErrorStatus;
}


static RCC_enuErrorStatus isPllConfigIsCorrect(
                          RCC_stPLLconfig_t * const RCC_stConfig
                          )
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if((RCC_stConfig->PLLSource != CLK_HSE &&
       RCC_stConfig->PLLSource != CLK_HSI) ||
       ((RCC_stConfig->PLLSource == CLK_HSE) && (HSEFreq == 4294967295)))
    {
        RET_enuErrorStatus = RCC_PLL_WRONG_CFG;
    }
    else if(RCC_stConfig->PLLM > PLLM_MAX ||
            RCC_stConfig->PLLM < PLLM_MIN)
    {
        RET_enuErrorStatus = RCC_PLL_WRONG_CFG;
    }
    else if(RCC_stConfig->PLLN > PLLN_MAX ||
            RCC_stConfig->PLLN < PLLN_MIN)
    {
        RET_enuErrorStatus = RCC_PLL_WRONG_CFG;
    }
    else if(RCC_stConfig->PLLP != 2 &&
            RCC_stConfig->PLLP != 4 &&
            RCC_stConfig->PLLP != 6 &&
            RCC_stConfig->PLLP != 8)
    {
        RET_enuErrorStatus = RCC_PLL_WRONG_CFG;
    }
    else
    {
        uint8_t VCO_in = 0;
        switch (RCC_stConfig->PLLSource)
        {
        case CLK_HSE:
            VCO_in =  HSEFreq / RCC_stConfig->PLLM;
            break;

        case CLK_HSI:
            VCO_in =  HSI_FREQ /  RCC_stConfig->PLLM;
            break;
        default:
            break;
        }
        if(VCO_in != 1 && VCO_in != 2)
        {
            RET_enuErrorStatus = RCC_PLL_WRONG_CFG;
        }
        else
        {
            uint8_t PllFreq = ((VCO_in  * RCC_stConfig->PLLN) / RCC_stConfig->PLLP);
            if(PllFreq > PLL_MAX_FRQ)
            {
                RET_enuErrorStatus = RCC_PLL_WRONG_CFG;
            }
            else
            {
                //No thing
            }
        }
    }
   return RET_enuErrorStatus;
}

static uint32_t u32GetSysClk(void)
{
    return ((RCC->CFGR & CURRENT_SYSCLK) >> 2);
}

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

RCC_enuErrorStatus  RCC_enuConfigPLL(RCC_stPLLconfig_t * const RCC_stConfig)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;

    RCC_enuErrorStatus PLLStatus = isPLLWorking();

    if(PLLStatus == RCC_PLL_IS_WORKING)
    {
        RET_enuErrorStatus = RCC_PLL_IS_WORKING;
    }
    else
    {
        if(RCC_stConfig == NULL)
        {
            RET_enuErrorStatus = RCC_NULL_PTR_PASSED;
        }
        else
        {
            RET_enuErrorStatus = isPllConfigIsCorrect(RCC_stConfig);
            if(RET_enuErrorStatus == RCC_FUNC_DONE)
            {
                uint32_t u32Temp = 0;
                u32Temp = RCC_stConfig->PLLM | (RCC_stConfig->PLLN << 6) |
                         (((RCC_stConfig->PLLP/2)-1) << 16);
                switch(RCC_stConfig->PLLSource)
                {
                    case CLK_HSE:
                        u32Temp |= (1 << 22);
                        u8PllSrc = 1;
                    break;
                    case CLK_HSI:
                        u8PllSrc = 1;
                    break;
                    default:
                    break;
                }
                RCC->PLLCFGR = u32Temp;
                isPLLConfigured = 1;
            }
            else
            {
                // No thing
            }
        }
    }
    return RET_enuErrorStatus;
}


RCC_enuErrorStatus  RCC_enuConfigHSE(uint32_t HSE , uint32_t Freq)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if(HSE != HSE_BY_PASS && HSE != HSE_NOT_BY_PASS)
    {
        RET_enuErrorStatus = RCC_HSE_WRONG_CFG;
    }
    else if(Freq > HSE_MAX_FRQ || Freq < HSE_MIN_FRQ)
    {
        RET_enuErrorStatus = RCC_HSE_WRONG_CFG;
    }
    else
    {
        HSEFreq = Freq;
        uint32_t u32Temp = RCC->CR;
        switch (HSE)
        {
        case HSE_BY_PASS:
            u32Temp |= HSE_BY_PASS;
            break;

        case HSE_NOT_BY_PASS:
            u32Temp &= HSE_NOT_BY_PASS;
            break;

        default:
            /*No thing*/
            break;
        }
        RCC->CR = u32Temp;
    }
    return RET_enuErrorStatus;
}

RCC_enuErrorStatus  RCC_enuEnableClk(uint32_t CLK)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    uint32_t u32Timeout = 30000;
    if(CLK != CLK_HSE && CLK != CLK_HSI && CLK != CLK_PLL)
    {
        RET_enuErrorStatus = RCC_WRONG_CLK;
    }
    else
    {
        switch (CLK)
        {
        case CLK_HSI:
            RCC->CR |= CLK_HSI;
            while (!(RCC->CR & HSI_RDY) && u32Timeout--);
            if(u32Timeout == 0)
            {
                RET_enuErrorStatus = RCC_TIMEOUT_ERROR;
                RCC->CR &= ~CLK_HSI;
            }
            else
            {
                /* No thing*/
            }
            break;
        case CLK_HSE:
            if(HSEFreq != 4294967295)
            {
                RCC->CR |= CLK_HSE;
                while (!(RCC->CR & HSE_RDY) && u32Timeout--);
                if(u32Timeout == 0)
                {
                    RET_enuErrorStatus = RCC_TIMEOUT_ERROR;
                    RCC->CR &= ~CLK_HSE;
                }
                else
                {
                    /* No thing*/
                }
            }
            else
            {
                RET_enuErrorStatus = RCC_HSE_NOT_CONFIGURED;
            }
            break;
        case CLK_PLL:
            if(isPLLConfigured)
            {
                RCC->CR |= CLK_PLL;
                while (!(RCC->CR & PLL_RDY) && u32Timeout--);
                if(u32Timeout == 0)
                {
                    RET_enuErrorStatus = RCC_TIMEOUT_ERROR;
                    RCC->CR &= ~CLK_PLL;
                }
                else
                {
                    /* No thing*/
                }
            }
            else
            {
                RET_enuErrorStatus = RCC_PLL_NOT_CONFIGURED;
            }
            break;
        default:
            break;
        }
    }
    return RET_enuErrorStatus;
}


RCC_enuErrorStatus 	RCC_enuIsClkWorking(uint32_t CLK)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if(CLK != CLK_HSE && CLK != CLK_HSI && CLK != CLK_PLL)
    {
        RET_enuErrorStatus = RCC_WRONG_CLK;
    }
    else
    {
        switch (CLK)
        {
        case CLK_HSI:
            RET_enuErrorStatus = isHSIWorking();
            break;
        case CLK_HSE:
            RET_enuErrorStatus = isHSEWorking();
            break;
        case CLK_PLL:
            RET_enuErrorStatus = isPLLWorking();
            break;
        default:
            break;
        }
    }
    return RET_enuErrorStatus;
}

RCC_enuErrorStatus  RCC_enuSetSysClk(uint32_t SYSCLK)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if(SYSCLK != SYSCLK_HSE && SYSCLK != SYSCLK_HSI && SYSCLK_PLL != SYSCLK_PLL)
    {
        RET_enuErrorStatus = RCC_WRONG_SYSCLK;
    }
    else
    {
        volatile uint32_t u32Temp = (RCC->CFGR);
        u32Temp &= SYSCLK_CLR;
        switch (SYSCLK)
        {
        case SYSCLK_HSI:
            if(isHSIWorking() == RCC_HSI_IS_WORKING)
            {
                u32Temp |= SYSCLK_HSI;
                RCC->CFGR = u32Temp;
            }
            else
            {
                RET_enuErrorStatus = RCC_HSI_IS_DISABLED;
            }
            break;
        case SYSCLK_HSE:
            if(isHSEWorking() == RCC_HSE_IS_WORKING)
            {
                u32Temp |= SYSCLK_HSE;
                RCC->CFGR = u32Temp;
            }
            else
            {
                RET_enuErrorStatus = RCC_HSI_IS_DISABLED;
            }

            break;

        case SYSCLK_PLL:
            if(isPLLWorking() == RCC_PLL_IS_WORKING)
            {
                u32Temp |= SYSCLK_PLL;
                RCC->CFGR = u32Temp;
            }
            else
            {
                RET_enuErrorStatus = RCC_HSI_IS_DISABLED;
            }

            break;

        default:
            break;
        }
    }
    return RET_enuErrorStatus;
}


RCC_enuErrorStatus  RCC_enuDisableClk(uint32_t CLK)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if(CLK != CLK_HSE && CLK != CLK_HSI && CLK != CLK_PLL)
    {
        RET_enuErrorStatus = RCC_WRONG_CLK;
    }
    else
    {
        uint32_t u32SystemClock = u32GetSysClk();
        uint32_t u32Timeout = 1000;
        switch (CLK)
        {
        case CLK_HSE:
            if(u32SystemClock == SYSCLK_HSE || (u8PllSrc == 1 && u32SystemClock == SYSCLK_PLL))
            {
                RET_enuErrorStatus = RCC_CLK_CANNOT_DISABLE_IT_IS_SYSCLK;
            }
            else
            {
                RCC->CR &= ~CLK_HSE;
                while ((RCC->CR & HSE_RDY) && u32Timeout--);
                if(u32Timeout == 0)
                {
                    RET_enuErrorStatus = RCC_TIMEOUT_ERROR;
                }
                else
                {

                }
            }
            break;

        case CLK_HSI:
            if(u32SystemClock == SYSCLK_HSI|| (u8PllSrc == 1 && u32SystemClock == SYSCLK_PLL))
            {
                RET_enuErrorStatus = RCC_CLK_CANNOT_DISABLE_IT_IS_SYSCLK;
            }
            else
            {
                RCC->CR &= ~CLK_HSI;
                while ((RCC->CR & HSI_RDY) && u32Timeout--);
                if(u32Timeout == 0)
                {
                    RET_enuErrorStatus = RCC_TIMEOUT_ERROR;
                }
                else
                {

                }
            }
            break;
        case CLK_PLL:
            if(u32SystemClock == SYSCLK_PLL)
            {
                RET_enuErrorStatus = RCC_CLK_CANNOT_DISABLE_IT_IS_SYSCLK;
            }
            else
            {
                RCC->CR &= ~CLK_PLL;
                while ((RCC->CR & PLL_RDY) && u32Timeout--);
                if(u32Timeout == 0)
                {
                    RET_enuErrorStatus = RCC_TIMEOUT_ERROR;
                }
                else
                {

                }
            }
            break;

        default:
            break;
        }
    }
    return RET_enuErrorStatus;
}

uint32_t 			RCC_enuGetSysClk(void)
{
	uint32_t SysClk = u32GetSysClk();
    return SysClk;
}

RCC_enuErrorStatus  RCC_enuSetPrescaler(uint32_t BUS)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;

    if (BUS != BUS_AHB_PRE_DIV1 &&
        BUS != BUS_AHB_PRE_DIV2 &&
        BUS != BUS_AHB_PRE_DIV4 &&
        BUS != BUS_AHB_PRE_DIV8 &&
        BUS != BUS_AHB_PRE_DIV16 &&
        BUS != BUS_AHB_PRE_DIV64 &&
        BUS != BUS_AHB_PRE_DIV128 &&
        BUS != BUS_AHB_PRE_DIV256 &&
        BUS != BUS_AHB_PRE_DIV512 &&
        BUS != BUS_ABP2_PRE_DIV1 &&
        BUS != BUS_ABP2_PRE_DIV2 &&
        BUS != BUS_ABP2_PRE_DIV4 &&
        BUS != BUS_ABP2_PRE_DIV8 &&
        BUS != BUS_ABP2_PRE_DIV16 &&
        BUS != BUS_ABP1_PRE_DIV1 &&
        BUS != BUS_ABP1_PRE_DIV2 &&
        BUS != BUS_ABP1_PRE_DIV4 &&
        BUS != BUS_ABP1_PRE_DIV8 &&
        BUS != BUS_ABP1_PRE_DIV16)
    {
        RET_enuErrorStatus = RCC_WRONG_BUS_PRESCLER;
    }
    else
    {
        uint32_t u32Temp = RCC->CFGR;
        if(( BUS <= BUS_AHB_PRE_DIV512 && BUS >= BUS_AHB_PRE_DIV1))
        {
            u32Temp &= ~BUS_AHB_PRE_DIV512;
        }
        else if(( BUS <= BUS_ABP2_PRE_DIV16 && BUS >= BUS_ABP2_PRE_DIV1))
        {
            u32Temp &= ~BUS_ABP2_PRE_DIV16;
        }
        else
        {
            u32Temp &= ~BUS_ABP1_PRE_DIV16;
        }
        u32Temp |= BUS;
        RCC->CFGR = u32Temp;
    }
    return RET_enuErrorStatus;
}

RCC_enuErrorStatus  RCC_enuGetPrescaler(uint32_t BUS, uint32_t * BusPrescaler)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;

    if (BUS != BUS_AHB_PRE_DIV1 &&
        BUS != BUS_AHB_PRE_DIV2 &&
        BUS != BUS_AHB_PRE_DIV4 &&
        BUS != BUS_AHB_PRE_DIV8 &&
        BUS != BUS_AHB_PRE_DIV16 &&
        BUS != BUS_AHB_PRE_DIV64 &&
        BUS != BUS_AHB_PRE_DIV128 &&
        BUS != BUS_AHB_PRE_DIV256 &&
        BUS != BUS_AHB_PRE_DIV512 &&
        BUS != BUS_ABP2_PRE_DIV1 &&
        BUS != BUS_ABP2_PRE_DIV2 &&
        BUS != BUS_ABP2_PRE_DIV4 &&
        BUS != BUS_ABP2_PRE_DIV8 &&
        BUS != BUS_ABP2_PRE_DIV16 &&
        BUS != BUS_ABP1_PRE_DIV1 &&
        BUS != BUS_ABP1_PRE_DIV2 &&
        BUS != BUS_ABP1_PRE_DIV4 &&
        BUS != BUS_ABP1_PRE_DIV8 &&
        BUS != BUS_ABP1_PRE_DIV16)
    {
        RET_enuErrorStatus = RCC_WRONG_BUS_PRESCLER;
    }
    else
    {
        *BusPrescaler = (RCC->CFGR&BUS);
    }
    return RET_enuErrorStatus;
}

RCC_enuErrorStatus	RCC_enuEnablePeripheral(uint32_t PERIPHERAL)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if (PERIPHERAL != PERIPHERAL_GPIOA &&
        PERIPHERAL != PERIPHERAL_GPIOB &&
        PERIPHERAL != PERIPHERAL_GPIOC &&
        PERIPHERAL != PERIPHERAL_GPIOD &&
        PERIPHERAL != PERIPHERAL_GPIOE &&
        PERIPHERAL != PERIPHERAL_GPIOH &&
        PERIPHERAL != PERIPHERAL_DMA1 &&
        PERIPHERAL != PERIPHERAL_DMA2 &&
        PERIPHERAL != PERIPHERAL_TIM2 &&
        PERIPHERAL != PERIPHERAL_TIM3 &&
        PERIPHERAL != PERIPHERAL_TIM4 &&
        PERIPHERAL != PERIPHERAL_TM55 &&
        PERIPHERAL != PERIPHERAL_WWDG &&
        PERIPHERAL != PERIPHERAL_SPI2 &&
        PERIPHERAL != PERIPHERAL_SPI3 &&
        PERIPHERAL != PERIPHERAL_USART2 &&
        PERIPHERAL != PERIPHERAL_I2C1 &&
        PERIPHERAL != PERIPHERAL_I2C2 &&
        PERIPHERAL != PERIPHERAL_PWR &&
        PERIPHERAL != PERIPHERAL_TIM1 &&
        PERIPHERAL != PERIPHERAL_USART1 &&
        PERIPHERAL != PERIPHERAL_USART6 &&
        PERIPHERAL != PERIPHERAL_ADC1 &&
        PERIPHERAL != PERIPHERAL_SDIO &&
        PERIPHERAL != PERIPHERAL_SPI1 &&
        PERIPHERAL != PERIPHERAL_SPI4 &&
        PERIPHERAL != PERIPHERAL_SYSCF &&
        PERIPHERAL != PERIPHERAL_TIM9 &&
        PERIPHERAL != PERIPHERAL_TIM10 &&
        PERIPHERAL != PERIPHERAL_TIM11)
    {
        RET_enuErrorStatus = RCC_PERIPHERAL_NOT_FOUND;
    }
    else
    {
        uint32_t PeripheralBus = (PERIPHERAL >> 28);
        PERIPHERAL &= 0x0FFFFFFF;
        switch (PeripheralBus)
        {
        case AHB1_BUS:
            RCC->AHB1ENR |= PERIPHERAL;
            break;

        case APB2_BUS:
            RCC->APB2ENR |= PERIPHERAL;
            break;

        case APB1_BUS:
            RCC->APB1ENR |= PERIPHERAL;
            break;

        default:
            break;
        }
    }
    return RET_enuErrorStatus;
}

RCC_enuErrorStatus	RCC_enuDisablePeripheral(uint32_t PERIPHERAL)
{
    RCC_enuErrorStatus RET_enuErrorStatus = RCC_FUNC_DONE;
    if (PERIPHERAL != PERIPHERAL_GPIOA &&
        PERIPHERAL != PERIPHERAL_GPIOB &&
        PERIPHERAL != PERIPHERAL_GPIOC &&
        PERIPHERAL != PERIPHERAL_GPIOD &&
        PERIPHERAL != PERIPHERAL_GPIOE &&
        PERIPHERAL != PERIPHERAL_GPIOH &&
        PERIPHERAL != PERIPHERAL_DMA1 &&
        PERIPHERAL != PERIPHERAL_DMA2 &&
        PERIPHERAL != PERIPHERAL_TIM2 &&
        PERIPHERAL != PERIPHERAL_TIM3 &&
        PERIPHERAL != PERIPHERAL_TIM4 &&
        PERIPHERAL != PERIPHERAL_TM55 &&
        PERIPHERAL != PERIPHERAL_WWDG &&
        PERIPHERAL != PERIPHERAL_SPI2 &&
        PERIPHERAL != PERIPHERAL_SPI3 &&
        PERIPHERAL != PERIPHERAL_USART2 &&
        PERIPHERAL != PERIPHERAL_I2C1 &&
        PERIPHERAL != PERIPHERAL_I2C2 &&
        PERIPHERAL != PERIPHERAL_PWR &&
        PERIPHERAL != PERIPHERAL_TIM1 &&
        PERIPHERAL != PERIPHERAL_USART1 &&
        PERIPHERAL != PERIPHERAL_USART6 &&
        PERIPHERAL != PERIPHERAL_ADC1 &&
        PERIPHERAL != PERIPHERAL_SDIO &&
        PERIPHERAL != PERIPHERAL_SPI1 &&
        PERIPHERAL != PERIPHERAL_SPI4 &&
        PERIPHERAL != PERIPHERAL_SYSCF &&
        PERIPHERAL != PERIPHERAL_TIM9 &&
        PERIPHERAL != PERIPHERAL_TIM10 &&
        PERIPHERAL != PERIPHERAL_TIM11)
    {
        RET_enuErrorStatus = RCC_PERIPHERAL_NOT_FOUND;
    }
    else
    {
        uint32_t PeripheralBus = (PERIPHERAL >> 28);
        PERIPHERAL &= 0x0FFFFFFF;
        switch (PeripheralBus)
        {
        case AHB1_BUS:
            RCC->AHB1ENR &= ~PERIPHERAL;
            break;

        case APB2_BUS:
            RCC->APB2ENR &= ~PERIPHERAL;
            break;

        case APB1_BUS:
            RCC->APB1ENR &= ~PERIPHERAL;
            break;

        default:
            break;
        }
    }
    return RET_enuErrorStatus;
}

/******************************************************************************/
