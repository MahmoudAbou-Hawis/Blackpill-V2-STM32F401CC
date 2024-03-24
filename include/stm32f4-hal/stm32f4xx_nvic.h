/*******************************************************************************/
/**
 * @file stm32f4xx_nvic.h
 * @brief Definitions and prototypes for NVIC (Nested Vectored Interrupt Controller)
 *
 * @par Project Name
 * STM32F4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This file contains the definitions and prototypes for the NVIC 
 * (Nested Vectored Interrupt Controller) peripheral for STM32F4xx microcontrollers.
 * The NVIC is responsible for managing interrupt priorities and handling interrupts 
 * in Cortex-M4 based STM32F4xx microcontrollers.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 ******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef __STM32F4xx_NVIC_H
#define __STM32F4xx_NVIC_H
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
 * @defgroup PRIORITY_GROUP
 * @{
 */

/**
 * @brief 4 bits for preemption priority, no sub-priority.
 */
#define PRIORITYGROUP_0  ((uint32_t)0x00000300)

/**
 * @brief 3 bits for preemption priority, 1 bit for sub-priority.
 */
#define PRIORITYGROUP_1  ((uint32_t)0x00000400)

/**
 * @brief 2 bits for preemption priority, 2 bits for sub-priority.
 */
#define PRIORITYGROUP_2  ((uint32_t)0x00000500)

/**
 * @brief 1 bit for preemption priority, 3 bits for sub-priority.
 */
#define PRIORITYGROUP_3  ((uint32_t)0x00000600)

/**
 * @brief 0 bits for preemption priority, 4 bits for sub-priority.
 */
#define PRIORITYGROUP_4  ((uint32_t)0x00000700)

/**
 * @}
 */

/******************************************************************************/

/******************************************************************************/
/* PUBLIC MACROS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PUBLIC ENUMS */
/******************************************************************************/


/** @defgroup STM32_Interrupt_Numbers STM32 Interrupt Numbers
 * @{
 */

/**
 * @brief Interrupt request number (IRQn) enumeration.
 *
 * This enumeration defines the interrupt request numbers for various peripherals
 * and functionalities on the STM32 microcontroller.
 *
 * The priority grouping scheme (configurable using `NVIC_SetPriorityGrouping`)
 * determines how the priority bits within the NVIC Interrupt Priority Register
 * (NVIC_IP) are divided between preemption priority and sub-priority levels.
 */
typedef enum
{
    WWDG_IRQn,                   /*!< Window WatchDog Interrupt                                         */
    PVD_IRQn,                    /*!< PVD through EXTI Line detection Interrupt                         */
    TAMP_STAMP_IRQn,             /*!< Tamper and TimeStamp interrupts through the EXTI line             */
    RTC_WKUP_IRQn,               /*!< RTC Wakeup interrupt through the EXTI line                        */
    FLASH_IRQn,                  /*!< FLASH global Interrupt                                            */
    RCC_IRQn,                    /*!< RCC global Interrupt                                              */
    EXTI0_IRQn,                  /*!< EXTI Line0 Interrupt                                              */
    EXTI1_IRQn,                  /*!< EXTI Line1 Interrupt                                              */
    EXTI2_IRQn,                  /*!< EXTI Line2 Interrupt                                              */
    EXTI3_IRQn,                  /*!< EXTI Line3 Interrupt                                              */
    EXTI4_IRQn,                  /*!< EXTI Line4 Interrupt                                              */
    DMA1_Stream0_IRQn,           /*!< DMA1 Stream 0 global Interrupt                                    */
    DMA1_Stream1_IRQn,           /*!< DMA1 Stream 1 global Interrupt                                    */
    DMA1_Stream2_IRQn,           /*!< DMA1 Stream 2 global Interrupt                                    */
    DMA1_Stream3_IRQn,           /*!< DMA1 Stream 3 global Interrupt                                    */
    DMA1_Stream4_IRQn,           /*!< DMA1 Stream 4 global Interrupt                                    */
    DMA1_Stream5_IRQn,           /*!< DMA1 Stream 5 global Interrupt                                    */
    DMA1_Stream6_IRQn,           /*!< DMA1 Stream 6 global Interrupt                                    */
    ADC_IRQn,                    /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
    EXTI9_5_IRQn = 23,           /*!< External Line[9:5] Interrupts                                     */
    TIM1_BRK_TIM9_IRQn,          /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
    TIM1_UP_TIM10_IRQn,          /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
    TIM1_TRG_COM_TIM11_IRQn,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
    TIM1_CC_IRQn,                /*!< TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQn,                   /*!< TIM2 global Interrupt                                             */
    TIM3_IRQn,                   /*!< TIM3 global Interrupt                                             */
    TIM4_IRQn,                   /*!< TIM4 global Interrupt                                             */
    I2C1_EV_IRQn,                /*!< I2C1 Event Interrupt                                              */
    I2C1_ER_IRQn,                /*!< I2C1 Error Interrupt                                              */
    I2C2_EV_IRQn,                /*!< I2C2 Event Interrupt                                              */
    I2C2_ER_IRQn,                /*!< I2C2 Error Interrupt                                              */
    SPI1_IRQn,                   /*!< SPI1 global Interrupt                                             */
    SPI2_IRQn,                   /*!< SPI2 global Interrupt                                             */
    USART1_IRQn,                 /*!< USART1 global Interrupt                                           */
    USART2_IRQn,                 /*!< USART2 global Interrupt                                           */
    EXTI15_10_IRQn = 40,         /*!< External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQn,              /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
    OTG_FS_WKUP_IRQn,            /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
    DMA1_Stream7_IRQn = 47,      /*!< DMA1 Stream7 Interrupt                                            */
    SDIO_IRQn = 49,              /*!< SDIO global Interrupt                                             */
    TIM5_IRQn,                   /*!< TIM5 global Interrupt                                             */
    SPI3_IRQn,                   /*!< SPI3 global Interrupt                                             */
    DMA2_Stream0_IRQn = 56,      /*!< DMA2 Stream 0 global Interrupt                                    */
    DMA2_Stream1_IRQn,           /*!< DMA2 Stream 1 global Interrupt                                    */
    DMA2_Stream2_IRQn,           /*!< DMA2 Stream 2 global Interrupt                                    */
    DMA2_Stream3_IRQn,           /*!< DMA2 Stream 3 global Interrupt                                    */
    DMA2_Stream4_IRQn,           /*!< DMA2 Stream 4 global Interrupt                                    */
    OTG_FS_IRQn = 67,                 /*!< USB OTG FS global Interrupt                                       */
    DMA2_Stream5_IRQn,           /*!< DMA2 Stream 5 global interrupt                                    */
    DMA2_Stream6_IRQn,           /*!< DMA2 Stream 6 global interrupt                                    */
    DMA2_Stream7_IRQn,           /*!< DMA2 Stream 7 global interrupt                                    */
    USART6_IRQn,                 /*!< USART6 global interrupt                                           */
    I2C3_EV_IRQn,                /*!< I2C3 event interrupt                                              */
    I2C3_ER_IRQn,                /*!< I2C3 error interrupt                                              */
    FPU_IRQn = 81,               /*!< FPU global interrupt                                              */
    SPI4_IRQn = 84                  /*!< SPI4 global Interrupt                                             */
} IRQn_Type;

/**
  * @}
*/

/**
 * @defgroup NVIC_ERROR_STATUS
 * @{
 */

/**
 * @typedef NVIC_ErrorStatus
 * @brief Enumeration for NVIC error status codes.
 *
 * This enumeration defines the possible return values from NVIC related functions
 * to indicate success or error conditions.
 */
typedef enum
{
    /** @enum{0} No error occurred (function call successful). */
    NVIC_OK,
    /** @enum{1} An error occurred during the function call. */
    NVIC_NOT_OK,
    /** @enum{2} Null pointer passed as an argument to a function. */
    NVIC_NULL_PTR_PASSED
} NVIC_ErrorStatus_t;

/**
 * @}
 */
/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/


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
 * @brief Configures the interrupt priority grouping scheme.
 *
 * This function sets how interrupt priority bits in the NVIC Interrupt
 * Priority Register (NVIC_IP) are divided between preemption priority and
 * sub-priority levels. Preemption priority determines which interrupt can preempt
 * another, while sub-priority further prioritizes interrupts within the same
 * preemption level.
 *
 * @param[in] PriorityGroup: Defines the priority grouping scheme. Valid values
 *                           typically range from 0-4 (system-specific variations may exist).
 *                           - Use the provided #defines for clarity and portability:
 *                             - 'PRIORITYGROUP_0': 4 bits for preemption priority, no sub-priority.
 *                             - 'PRIORITYGROUP_1': 3 bits for preemption priority, 1 bit for sub-priority.
 *                             - 'PRIORITYGROUP_2': 2 bits for preemption priority, 2 bits for sub-priority.
 *                             - 'PRIORITYGROUP_3': 1 bit for preemption priority, 3 bits for sub-priority.
 *                             - 'PRIORITYGROUP_4': 0 bits for preemption priority, 4 bits for sub-priority.
 *                             
 *
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_SetPriorityGrouping(uint32_t PriorityGroup);



/**
 * @brief Assigns priority levels to a specific interrupt source.
 *
 * This function sets the preemption priority and sub-priority values for an
 * interrupt. Higher numerical values indicate higher priority. The specific
 * interpretation of these values depends on the configured priority grouping
 * (refer to NVIC_SetPriorityGrouping).
 *
 * @param[in] IRQn: Interrupt number for which priority is being configured.
 *                  This parameter should be an element of the IRQn_Type
 *                  enumeration defined in the @ref STM32_Interrupt_Numbers group.
 * @param[in] PreemptPriority: Preemption priority value within the configured group.
 * @param[in] SubPriority: Sub-priority value within the configured group.
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);


/**
 * @brief Enables a specific interrupt source.
 *
 * This function allows the specified interrupt to generate an interrupt request
 * when its trigger condition occurs. The interrupt will be considered for
 * servicing by the processor based on its configured priority and the current
 * state of other interrupts.
 *
 * @param[in] IRQn: Interrupt number for the source to be enabled. This value is
 *              typically defined in an interrupt enumeration belonging to the
 *              @ref STM32_Interrupt_Numbers group. 
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_EnableIRQ(IRQn_Type IRQn);


/**
 * @brief Disables a specific interrupt source.
 *
 * This function prevents the specified interrupt from generating an interrupt request.
 * Disabling an interrupt prevents it from interrupting the processor even if its
 * trigger condition occurs. However, the interrupt source might still need to be
 * cleared manually depending on the peripheral or functionality it is associated with.
 * 
 * @param[in] IRQn: Interrupt number for the source to be disabled. This value is
 *              typically defined in an interrupt enumeration belonging to the
 *              @ref STM32_Interrupt_Numbers group.
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_DisableIRQ(IRQn_Type IRQn);

/**
 * @brief Triggers a system reset, typically restarting the microcontroller.
 *
 * This function initiates a system reset, which usually leads to restarting
 * the microcontroller. Use with caution as it can disrupt program execution.
 */                   

__attribute__((__noreturn__)) void NVIC_SystemReset(void);

/**
 * @brief Retrieves the current interrupt priority grouping configuration.
 *
 * This function reads the currently active priority grouping setting from the NVIC.
 *
 * @return Current priority grouping value @ref PRIORITY_GROUP.
 */
extern uint32_t NVIC_GetPriorityGrouping(void);

/**
 * @brief Gets the preemption and sub-priority levels for a specific interrupt.
 *
 * This function retrieves the preemption priority and sub-priority values assigned
 * to a particular interrupt source.
 *
 * @param[in] IRQn: Interrupt number for which priority information is requested.
 * @param[in] PriorityGroup: Currently active priority group (passed as input).
 * @param[in out] pPreemptPriority: Pointer to store the retrieved preemption priority value.
 * @param[in out] pSubPriority: Pointer to store the retrieved sub-priority value.
 * 
* @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, 
                                  uint32_t* pPreemptPriority, uint32_t* pSubPriority);

/**
 * @brief Checks if a specific interrupt has a pending request.
 *
 * This function determines whether the specified interrupt has requested service
 * and is waiting to be handled by the processor.
 *
 * @param[in] IRQn: Interrupt number to check for pending status.
 *
 * @param[in out] pPendingState: pointer to save the pending state value.
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_GetPendingIRQ(IRQn_Type IRQn ,uint32_t * pPendingState);

/**
 * @brief Sets the pending bit for a specific interrupt, forcing service.
 *
 * This function artificially sets the pending bit for an interrupt, forcing the
 * processor to service it as soon as possible. Use with caution as unexpected
 * behavior might occur if used improperly.
 * 
 * @param[in] IQRn: interrupt number to set it's pending state.
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_SetPendingIRQ(IRQn_Type IRQn);

/**
 * @brief Clears the pending bit for a specific interrupt.
 *
 * This function removes the pending bit from an interrupt, indicating that it has
 * been serviced and is no longer waiting for attention.
 *
 * @param[in] IRQn: Interrupt number whose pending status will be cleared.
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
 */
extern NVIC_ErrorStatus_t NVIC_ClearPendingIRQ(IRQn_Type IRQn);

/**
 * @brief Checks if a specific interrupt is currently active.
 *
 * This function determines whether the specified interrupt is currently being
 * serviced by the processor.
 *
 * @param[in] IRQn: Interrupt number to check for active status.
 *
 * @param[in out] pActiveState: pointer to save the active state.
 * 
 * @return NVIC_ErrorStatus: Indicates the outcome of the operation.
 *                          - @ref NVIC_OK: No error occurred (function call successful).
 *                          - Other values represent error conditions.
*/
extern NVIC_ErrorStatus_t NVIC_GetActive(IRQn_Type IRQn,uint32_t * pActiveState);
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
#endif /* __STM32F4xx_NVIC_H */
/******************************************************************************/
