/*******************************************************************************/
/**
 * @file stm32f4xx_rcc.h
 * @brief Header file for RCC (Reset and Clock Control) configuration on STM32F401
 *
 * @par Project Name
 * stm32f4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file contains definitions and functions for configuring the RCC
 * (Reset and Clock Control) module on the STM32F401 microcontroller.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef __STM32F4xx_RCC_H
#define __STM32F4xx_RCC_H
/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include <stdint.h>
#include <stddef.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/

/**
 * @brief main Clocks used in the the system .
 */
#define 	CLK_PLL						((uint32_t)0x01000000)
#define		CLK_HSE						((uint32_t)0x00010000)
#define		CLK_HSI						((uint32_t)0x00000001)


/**
 * @brief main clocks for main system clock.
 */
#define 	SYSCLK_HSI					((uint32_t)0x00000000)
#define		SYSCLK_HSE					((uint32_t)0x00000001)
#define		SYSCLK_PLL					((uint32_t)0x00000002)

/**
 * @brief All prescalers for AHB Bus.
 */
#define 	BUS_AHB_PRE_DIV1 	  		((uint32_t)0x00000070)
#define 	BUS_AHB_PRE_DIV2   			((uint32_t)0x00000080)
#define 	BUS_AHB_PRE_DIV4   			((uint32_t)0x00000090)
#define 	BUS_AHB_PRE_DIV8   			((uint32_t)0x000000A0)
#define 	BUS_AHB_PRE_DIV16  			((uint32_t)0x000000B0)
#define 	BUS_AHB_PRE_DIV64  			((uint32_t)0x000000C0)
#define 	BUS_AHB_PRE_DIV128 			((uint32_t)0x000000D0)
#define 	BUS_AHB_PRE_DIV256 			((uint32_t)0x000000E0)
#define 	BUS_AHB_PRE_DIV512 			((uint32_t)0x000000F0)

/**
 * @brief All prescalers for ABP2 Bus.
 */
#define		BUS_ABP2_PRE_DIV1			((uint32_t)0x00006000)
#define		BUS_ABP2_PRE_DIV2			((uint32_t)0x00008000)
#define		BUS_ABP2_PRE_DIV4			((uint32_t)0x0000A000)
#define		BUS_ABP2_PRE_DIV8			((uint32_t)0x0000C000)
#define		BUS_ABP2_PRE_DIV16			((uint32_t)0x0000E000)

/**
 * @brief All prescalers for ABP1 Bus.
 */
#define		BUS_ABP1_PRE_DIV1			((uint32_t)0x00000F00)
#define		BUS_ABP1_PRE_DIV2			((uint32_t)0x00001000)
#define		BUS_ABP1_PRE_DIV4			((uint32_t)0x00001400)
#define		BUS_ABP1_PRE_DIV8			((uint32_t)0x00001800)
#define		BUS_ABP1_PRE_DIV16			((uint32_t)0x00001C00)



/**
 * @brief Available GPIOs , which is connected on AHB1
*/
#define 	PERIPHERAL_GPIOA			((uint32_t)0x20000001)
#define		PERIPHERAL_GPIOB			((uint32_t)0x20000002)
#define		PERIPHERAL_GPIOC			((uint32_t)0x20000004)
#define		PERIPHERAL_GPIOD			((uint32_t)0x20000008)
#define		PERIPHERAL_GPIOE			((uint32_t)0x20000010)
#define 	PERIPHERAL_GPIOH     		((uint32_t)0x20000080)


#define 	PERIPHERAL_DMA1		     	((uint32_t)0x20200000)
#define 	PERIPHERAL_DMA2  			((uint32_t)0x20400000)




/**
 * @brief Peripherals which connected in ABP1
 */
#define 	PERIPHERAL_TIM2		    	((uint32_t)0x00000001)
#define		PERIPHERAL_TIM3		    	((uint32_t)0x00000002)
#define 	PERIPHERAL_TIM4 			((uint32_t)0x00000004)
#define		PERIPHERAL_TM55	 	 	    ((uint32_t)0x00000008)
#define 	PERIPHERAL_WWDG	     		((uint32_t)0x00000080)
#define		PERIPHERAL_SPI2 			((uint32_t)0x00004000)
#define		PERIPHERAL_SPI3 			((uint32_t)0x00004000)
#define		PERIPHERAL_USART2   		((uint32_t)0x00020000)
#define		PERIPHERAL_I2C1 			((uint32_t)0x00200000)
#define		PERIPHERAL_I2C2	 	    	((uint32_t)0x00400000)
#define		PERIPHERAL_I2C3		     	((uint32_t)0x00800000)
#define		PERIPHERAL_PWR   			((uint32_t)0x10000000)


/**
 * @brief Peripherals which is connected in ABP2
 */
#define 	PERIPHERAL_TIM1				((uint32_t)0x10000001)
#define		PERIPHERAL_USART1			((uint32_t)0x10000010)
#define		PERIPHERAL_USART6			((uint32_t)0x10000020)
#define		PERIPHERAL_ADC1				((uint32_t)0x10000100)
#define     PERIPHERAL_SDIO				((uint32_t)0x10000800)
#define		PERIPHERAL_SPI1				((uint32_t)0x10001000)
#define		PERIPHERAL_SPI4				((uint32_t)0x10002000)
#define		PERIPHERAL_SYSCF			((uint32_t)0x10004000)
#define		PERIPHERAL_TIM9				((uint32_t)0x10010000)
#define		PERIPHERAL_TIM10			((uint32_t)0x10020000)
#define		PERIPHERAL_TIM11			((uint32_t)0x10040000)

/**
 * @brief HSE Configuration
 */
#define 	HSE_BY_PASS 				((uint32_t)0x00040000)
#define 	HSE_NOT_BY_PASS				((uint32_t)0xFFFBFFFF)

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/

/**
 * @brief Enumeration for error status
 *
 * This enumeration defines various error statuses that can be returned by functions.
 * Each status represents a different error condition, allowing for easy identification
 * and handling of errors within the application.
 *
 * Example usage:
 * @code
 *      // Function returning an error status
 *      RCC_enuErrorStatus result = SomeFunction();
 *
 *      // Check if an error occurred
 *      if (result == RCC_FUNC_DONE) {
 *          // Function done correctly.
 *      } else if (result == RCC_PLL_WRONG_CFG) {
 *          // Handle invalid configuration error
 *      } else {
 *          // Handle other errors
 *      }
 * @endcode
 */
typedef enum
{
	RCC_FUNC_DONE,

	RCC_PLL_IS_WORKING,

	RCC_PLL_WRONG_CFG ,

	RCC_PLL_IS_DISABLED ,

	RCC_HSE_ALREADY_ON ,

	RCC_HSE_IS_WORKING ,

	RCC_HSE_IS_DISABLED,

	RCC_HSE_SHOULD_BE_ON,

	RCC_HSE_WRONG_CFG,

	RCC_HSI_IS_DISABLED ,

	RCC_HSI_IS_WORKING,

	RCC_HSI_SHOULD_BE_ON ,

	RCC_HSE_MUST_BE_ENABLE ,

	RCC_TIMEOUT_ERROR ,

	RCC_WRONG_CLK,

	RCC_NULL_PTR_PASSED ,

	RCC_HSE_NOT_CONFIGURED ,

	RCC_PLL_NOT_CONFIGURED ,

	RCC_WRONG_SYSCLK ,

	RCC_CLK_CANNOT_DISABLE_IT_IS_SYSCLK ,

	RCC_WRONG_BUS_PRESCLER ,

	RCC_PERIPHERAL_NOT_FOUND

} RCC_enuErrorStatus;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/**
 * @brief PLL Configuration Structure
 *
 * This structure defines the parameters needed to configure a PLL (Phase-Locked Loop)
 * in a microcontroller system. The PLL is an essential component for generating
 * high-frequency clock signals with precise control over frequency and phase.
 *
 * - PLLSource: Specifies the PLL input clock source, such as HSI, HSE, or PLLCLK.
 * - PLLM: Division factor for the PLL input clock.
 * - PLLN: Multiplication factor for the PLL VCO (Voltage-Controlled Oscillator) output.
 * - PLLP: Division factor for the main system clock (SYSCLK).
 * - PLLQ: Division factor for USB OTG FS, SDIO, and RNG clocks (if available).
 *
 * Example usage:
 * @code
 *      // Define and initialize a PLL configuration structure
 *      RCC_stPLLconfig_t pllConfig = {
 *          .PLLSource = CLK_HSE,		    // PLL input clock source: HSE
 *          .PLLM = 8,                      // PLLM division factor
 *          .PLLN = 336,                    // PLLN multiplication factor
 *          .PLLP = 2,			            // PLLP division factor for SYSCLK
 *          .PLLQ = 7                       // PLLQ division factor for USB OTG FS, SDIO, RNG clocks
 *      };
 *
 *      // Configure the PLL with the specified parameters
 *      RCC_enuConfigPLL(&pllConfig);
 * @endcode
 */
typedef struct
{
	  uint32_t PLLSource; /**< PLL source must be CLK_HSE or CLK_HSI */

	  uint32_t PLLM; 	  /**< PLLM must ensure that the VCO input
	  						   frequency ranges from 1 to 2 MHz.
							    2<= PLLM <= 63 .
								VCO input frequency =
								PLL input clock frequency / PLLM*/

	  uint32_t PLLN;	  /**< 192 <= PLLN <= 432
	  							VCO output frequency = VCO input frequency × PLLN*/

	  uint32_t PLLP;      /**< PLLP = 2, 4, 6, or 8
	 							PLL output clock frequency = VCO frequency / PLLP*/

} RCC_stPLLconfig_t;

/******************************************************************************/

/******************************************************************************/
/* PUBLIC CONSTANT DECLARATIONS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC VARIABLE DECLARATIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PUBLIC FUNCTION PROTOTYPES */
/******************************************************************************/

/**
 * @brief Configure PLL
 *
 * This function configures the PLL (Phase-Locked Loop) with the provided parameters
 * in the RCC_stPLLconfig_t structure. The PLL is a crucial component in microcontroller
 * systems for generating high-frequency clock signals with precise control over frequency
 * and phase. By using this function, the programmer can set the PLL input clock source,
 * division factors, and multiplication factors according to the system requirements.
 *
 * @param[in] RCC_stConfig Pointer to the PLL configuration structure containing the desired parameters.
 * @return Error status
 *
 * Example usage:
 * @code
 *      // Define and initialize a PLL configuration structure
 *      RCC_stPLLconfig_t pllConfig = {
 *          .PLLSource = RCC_PLLSOURCE_HSE, // PLL input clock source: HSE
 *          .PLLM = 8,                      // PLLM division factor
 *          .PLLN = 336,                    // PLLN multiplication factor
 *          .PLLP = 2,         				// PLLP division factor for SYSCLK
 *          .PLLQ = 7                       // PLLQ division factor for USB OTG FS, SDIO, RNG clocks
 *      };
 *
 *      // Configure the PLL with the specified parameters
 *      RCC_enuConfigPLL(&pllConfig);
 * @endcode
 *
 * @note  PLL configuration cannot be altered while it is enabled.
 *        If using HSE as a PLL source, ensure it is configured
 * 		  before attempting PLL configuration, and it is running."
 *
 */
RCC_enuErrorStatus  RCC_enuConfigPLL(RCC_stPLLconfig_t * const RCC_stConfig);


/**
 * @brief Configure HSE (High-Speed External) clock
 *
 * This function configures the High-Speed External (HSE) clock, which is an external
 * clock source typically used in microcontroller systems. The HSE clock is often used
 * as a primary clock source or as an input to the PLL (Phase-Locked Loop) for generating
 * higher frequency clock signals. By using this function, the programmer can set the
 * HSE oscillator type.
 *
 * @param[in] HSE Oscillator type for the HSE clock (e.g., HSE_BY_PASS or HSE_NOT_BY_PASS)
 * @param[in] Freq represent the HSE frequency, must be with MHZ.
 * 				   allowed range is ( 4 <= Freq <=26 ) MHZ.
 * @return Error status
 *
 * Example usage:
 * @code
 *      // Configure HSE clock with crystal oscillator
 *      RCC_enuConfigHSE(HSE_BY_PASS);
 * @endcode
 *
 *
 * @note HSE must be enable to configure the HSE.
 */
RCC_enuErrorStatus  RCC_enuConfigHSE(uint32_t HSE , uint32_t Freq);

/**
 * @brief Enable PLL, HSE, or HSI clock
 *
 * This function enables the PLL (Phase-Locked Loop), HSE (High-Speed External),
 * or HSI (High-Speed Internal) clock in the microcontroller system, allowing
 * the associated peripheral or functionality to operate. Enabling these clocks
 * is a crucial step in initializing and configuring various peripherals or system
 * components that rely on these clock sources.
 *
 * @param[in] CLK The type of clock to be enabled (CLK_HSE, CLK_HSI, or CLK_PLL)
 * @return error status
 *
 * Example usage:
 * @code
 *      // Enable the PLL clock
 *      RCC_enuEnableClk(CLK_PLL);
 *
 *      // Enable the HSE clock
 *      RCC_enuEnableClk(CLK_HSI);
 *
 *      // Enable the HSI clock
 *      RCC_enuEnableClk(CLK_HSE);
 * @endcode
 *
 */
RCC_enuErrorStatus  RCC_enuEnableClk(uint32_t CLK);

/**
 * @brief Disable PLL, HSE, or HSI clock
 *
 * This function disables the PLL (Phase-Locked Loop), HSE (High-Speed External),
 * or HSI (High-Speed Internal) clock in the microcontroller system. Disabling
 * these clocks halts the associated peripheral or functionality, conserving power
 * or preparing the system for low-power modes.
 *
 * @param[in] CLK The type of clock to be disabled (CLK_HSE, CLK_HSI, or CLK_PLL)
 * @return error status
 *
 * Example usage:
 * @code
 *      // Disable the PLL clock
 *      RCC_enuDisableClk(CLK_HSE);
 *
 *      // Disable the HSE clock
 *      RCC_enuDisableClk(CLK_HSI);
 *
 *      // Disable the HSI clock
 *      RCC_enuDisableClk(CLK_PLL);
 * @endcode
 *
 * @note You cannot disable a clock while it is being used as the system clock.
 *       Before disabling a clock, you must first select another clock source as
 *       the system clock to ensure continuous operation of the microcontroller. */
RCC_enuErrorStatus  RCC_enuDisableClk(uint32_t CLK);

/**
 * @brief Check if the specified clock is operational
 *
 * This function checks whether the specified clock in the microcontroller system
 * is operational or not. It verifies whether the clock source is stable and within
 * the expected frequency range, indicating its functionality and reliability.
 *
 * @param[in] CLK The type of clock to be checked (e.g., CLK_PLL, CLK_HSE)
 * @return Error status
 *
 * Example usage:
 * @code
 *      // Check if the HSE clock is operational
 *      if (RCC_enuIsClkWorking(CLK_HSE)) {
 *          // HSE clock is operational, perform operations
 *      } else {
 *          // HSE clock is not operational, handle accordingly
 *      }
 * @endcode
 *
 */
RCC_enuErrorStatus 	RCC_enuIsClkWorking(uint32_t CLK);

/**
 * @brief Set a clock as the system clock
 *
 * This function sets the specified clock source as the system clock in the microcontroller
 * system. The system clock is the main clock signal used by the CPU and other peripherals
 * for timing and synchronization. By using this function, the programmer can choose the
 * desired clock source to be used as the system clock, ensuring proper operation of the
 * microcontroller and its peripherals.
 *
 * @param[in] SYSCLK The type of clock to be set as the system clock (e.g., SYSCLK_HSE, SYSCLK_PLL)
 * @return RCC_enuErrorStatus
 *
 * Example usage:
 * @code
 *      // Set the PLL clock as the system clock
 *      RCC_enuSetSysClk(SYSCLK_HSE);
 *
 *      // Set the HSE clock as the system clock
 *      RCC_enuSetSysClk(SYSCLK_PLL);
 * @endcode
 *
 * @note you should enable the clock source first. you should use RCC_enuEnableClk() first.
 */
RCC_enuErrorStatus  RCC_enuSetSysClk(uint32_t SYSCLK);


/**
 * @brief Get the current system clock source
 *
 * This function retrieves the clock source that is currently configured as the system clock
 * in the microcontroller system. The system clock is the main clock signal used by the CPU
 * and other peripherals for timing and synchronization. By using this function, the programmer
 * can determine which clock source is currently serving as the system clock, providing valuable
 * information for system configuration and debugging purposes.
 *
 * @return The clock source currently configured as the system clock (e.g., SYSCLK_HSE, SYSCLK_PLL)
 *
 * Example usage:
 * @code
 *      // Get the current system clock source
 *      uint32_t systemClockSource = RCC_enuGetSysClk();
 *      if (systemClockSource == SYSCLK_HSE) {
 *
 *      } else if (systemClockSource == SYSCLK_PLL) {
 *
 *      } else {
 *
 *      }
 * @endcode
 */
uint32_t 			RCC_enuGetSysClk(void);

/**
 * @brief Set the prescaler for a bus (AHB, APB1, or APB2)
 *
 * This function sets the prescaler for a specific bus in the microcontroller system,
 * such as the AHB (Advanced High-Performance Bus), APB1 (Advanced Peripheral Bus 1),
 * or APB2 (Advanced Peripheral Bus 2). The prescaler divides the clock frequency of
 * the selected bus, allowing for adjustments in the peripheral clock frequency or
 * synchronization with external devices.
 *
 * @param[in] BUS The type of bus to set the prescaler for (e.g., BUS_ABP2_PRE_DIV1, BUS_ABP1_PRE_DIV1)
 * @return Error status
 *
 * Example usage:
 * @code
 *      // Set the prescaler for AHB bus
 *      RCC_enuSetPrescaler(BUS_ABP2_PRE_DIV1);
 *
 *      // Set the prescaler for APB1 bus
 *      RCC_enuSetPrescaler(BUS_ABP1_PRE_DIV1);
 *
 *      // Set the prescaler for APB2 bus
 *      RCC_enuSetPrescaler(BUS_AHB_PRE_DIV1);
 * @endcode
 *
 * @note APB2 not to exceed 84 MHz
 * 		 APB1 not to exceed 42 MHz
 */
RCC_enuErrorStatus  RCC_enuSetPrescaler(uint32_t BUS);

/**
 * @brief Get the prescaler value for a bus (AHB, APB1, or APB2)
 *
 * This function retrieves the prescaler value currently set for a specific bus
 * in the microcontroller system, such as the AHB (Advanced High-Performance Bus),
 * APB1 (Advanced Peripheral Bus 1), or APB2 (Advanced Peripheral Bus 2). The prescaler
 * divides the clock frequency of the selected bus, allowing for adjustments in the
 * peripheral clock frequency or synchronization with external devices.
 *
 * @param[in] BUS The type of bus to set the prescaler for (e.g., BUS_ABP2_PRE_DIV1, BUS_ABP1_PRE_DIV1)
 * @param[in  out] BusPrescaler pointer to the bus prescaler result.
 * @return Error status
 *
 * Example usage:
 * @code
 *      // Get the prescaler value for AHB bus
 *      uint32_t ahbPrescaler = RCC_enuGetPrescaler(BUS_AHB_PRE_DIV1);
 *
 *      // Get the prescaler value for APB1 bus
 *      uint32_t apb1Prescaler = GetBusPrescaler(BUS_ABP1_PRE_DIV1);
 *
 *      // Get the prescaler value for APB2 bus
 *      uint32_t apb2Prescaler = GetBusPrescaler(BUS_ABP2_PRE_DIV1);
 * @endcode
 */
RCC_enuErrorStatus  RCC_enuGetPrescaler(uint32_t BUS, uint32_t * BusPrescaler);

/**
 * @brief Enable a peripheral
 *
 * This function enables a specific peripheral in the microcontroller system,
 * allowing it to operate and interact with other components. Enabling a peripheral
 * is a necessary step before it can be used for various tasks or functionalities.
 * By using this function, the programmer can activate the desired peripheral,
 * enabling its functionality and access to the associated registers.
 *
 * @param[in] PERIPHERAL The identifier of the peripheral to be enabled (e.g., PERIPHERAL_USART1, PERIPHERAL_TIM1)
 * @return Error status
 *
 * Example usage:
 * @code
 *      // Enable USART1 peripheral
 *      RCC_enuEnablePeripheral(PERIPHERAL_USART1);
 *
 *      // Enable TIM1 peripheral
 *      RCC_enuEnablePeripheral(PERIPHERAL_TIM1);
 * @endcode
 */
RCC_enuErrorStatus	RCC_enuEnablePeripheral(uint32_t PERIPHERAL);

/**
 * @brief Disable a peripheral
 *
 * This function disables a specific peripheral in the microcontroller system,
 * halting its operation and preventing it from interacting with other components.
 * Disabling a peripheral can conserve power or prepare the system for low-power
 * modes when the peripheral is not needed. By using this function, the programmer
 * can deactivate the desired peripheral, disabling its functionality and access
 * to the associated registers.
 *
 * @param[in] peripheral The identifier of the peripheral to be disabled (e.g., PERIPHERAL_USART1, PERIPHERAL_TIM1)
 * @return Error Status.
 *
 * Example usage:
 * @code
 *      // Disable USART1 peripheral
 *      RCC_enuDisablePeripheral(PERIPHERAL_USART1);
 *
 *      // Disable TIM1 peripheral
 *      RCC_enuDisablePeripheral(PERIPHERAL_TIM1);
 * @endcode
 */
RCC_enuErrorStatus	RCC_enuDisablePeripheral(uint32_t PERIPHERAL);


/******************************************************************************/

/******************************************************************************/
/* C++ Style GUARD */
/******************************************************************************/
#ifdef __cplusplus
}
#endif /* __cplusplus */
/******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#endif /* __STM32F4xx_RCC_H*/
/******************************************************************************/
