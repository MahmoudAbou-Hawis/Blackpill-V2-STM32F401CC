/******************************************************************************/
/**
 * @file stm32f4xx_nvic.c
 * @brief NVIC Driver for Cortex-M4 Processor
 *
 * This file provides a basic driver for managing interrupts using the NVIC
 * (Nested Vectored Interrupt Controller) in Cortex-M4 processors. It includes
 * functions for enabling interrupts, setting priorities (optional).
 *
 * NVIC Implementation Description:
 * 
 * 1. Configure Interrupt Priorities:
 *    - Use NVIC_SetPriorityGrouping() to set priority grouping.
 *    - Set priorities for individual interrupts using NVIC_SetPriority().
 * 
 * 2. Enable/Disable Interrupts:
 *    - Enable specific interrupts with NVIC_EnableIRQ().
 *    - Disable interrupts when not needed with NVIC_DisableIRQ().
 * 
 * 3. Handling Interrupt Requests:
 *    - Identify interrupt sources and prioritize them based on configured priorities.
 *    - Execute Interrupt Service Routines (ISRs) to handle interrupt tasks.
 *    - Clear interrupt pending flags with NVIC_ClearPendingIRQ() after ISR execution.
 * 
 * 4. System Reset:
 *    - Use NVIC_SystemReset() to perform a system reset if necessary.
 *
 * @par Project Name
 * STM32F4xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This driver provides a C-based implementation for managing interrupts using
 * the Nested Vectored Interrupt Controller (NVIC) on Cortex-M4 based STM32F4xx
 * microcontrollers. 
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/


/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "stm32f4xx_nvic.h"
/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/

/**
 * @brief  Defines 'read / write' structure member permissions.
 */
#define     __IOM    volatile      

/**
 * @brief Defines 'write only' structure  member permissions.
 */
#define     __OM     volatile      

/**
 * @brief Defines 'read only' structure member permissions.
 */
#define     __IM     volatile const     


/**
 * @brief System Control Block Application Interrupt and Reset Control Register.
 */
#define     SCB_AIRCR  *((__IOM uint32_t*)0xE000ED0C)

/**
 * @brief Instructs the compiler to optimize based on  that this function does 
 *        not return control to the caller.
 */
#define __NO_RETURN  __attribute__((__noreturn__)) void 

/**
 * @brief SCB AIRCR VECTKEY Position.
 */
#define SCB_AIRCR_VECTKEY_Pos                  16U

/**
 * @brief SCB AIRCR VECTKEY fixed value.
 */
#define SCB_AIRCR_VECTKEY_VALUE               (0x5FAUL << SCB_AIRCR_VECTKEY_Pos) 

/**
 * @brief SCB AIRCR PRIGROUP Position.
 */
#define SCB_AIRCR_PRIGROUP_Pos              8U   

/**
 * @brief SCB AIRCR PRIGROUP Position.
 */
#define SCB_AIRCR_PRIGROUP_Msk             (7UL << SCB_AIRCR_PRIGROUP_Pos) 


/**
* @brief Specifies the number of bits implemented for priority levels in the NVIC 
*        (Nested Vectored Interrupt Controller).
*/
#define __NVIC_PRIO_BITS                    4U

/**
 * @brief NVIC priority mask.
 */
#define __NVIC_PRIO_Msk                     ((uint8_t)0x0F)


/**
*@brief Position of the System Reset Request bit in the Application Interrupt 
        and Reset Control Register (AIRCR).
*/
#define SCB_AIRCR_SYSRESETREQ_Pos           2U            

/**
*
*@brief Mask for the System Reset Request bit in the Application Interrupt 
*       and Reset Control Register (AIRCR).
*/
#define SCB_AIRCR_SYSRESETREQ_Msk          (1UL << SCB_AIRCR_SYSRESETREQ_Pos) 


/**
*@brief When using PRIORITYGROUP_4, there is no preemption priority,
*        only subpriority levels are available.
*/
#define NO_PREEMPT_PRIORITY                   5UL

/**
 * @brief  NVIC base address.
 */
#define NVIC                                  ((NVIC_t* const)0xE000E100)

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/

/**
 * @brief Macro to verify if the provided priority group value is valid.
 */
#define  IS_NVIC_PRIORITY_GROUP(__PRIORITY_GROUP) \
                                    ((__PRIORITY_GROUP == PRIORITYGROUP_0)  || \
                                     (__PRIORITY_GROUP == PRIORITYGROUP_1)  || \
                                     (__PRIORITY_GROUP == PRIORITYGROUP_2)  || \
                                     (__PRIORITY_GROUP == PRIORITYGROUP_3)  || \
                                     (__PRIORITY_GROUP == PRIORITYGROUP_4))



/**
* @brief Macro to check if the supplied interrupt is invalid.
*/
#define IS_NOT_NVIC_IRQn(__IRQn)    (__IRQn < WWDG_IRQn || __IRQn > SPI4_IRQn)

/**
 * @brief Macro to check is the supplied preemption priority is invalid.  
 */
#define IS_NOT_NVIC_PREEMPTION_PRIORITY(PRIORITY)  ((PRIORITY) > 0x10U)

/**
 * @brief Macro to check is the supplied sub priority is invalid. 
 */
#define IS_NOT_NVIC_SUB_PRIORITY(PRIORITY)         ((PRIORITY) > 0x10U)

/**
 * @brief Macro used to get the preempt PRIORITY POSition in the implemnted 
 *        bits in nvic priority bits according the priority group.
 */

/**
* @brief Macro used to retrieve the position of the preemptive priority bits 
*        within the implemented bits in the NVIC priority bits, based on the
*        configured priority group.
*/
#define GET_PREEMPT_PRIORITY_POS(GROUP)        ((PRIORITYGROUP_4 - GROUP) >> 8U)

/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/**
 *  @brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
*/
typedef struct 
{
    __IOM uint32_t ISERx[8U];         /* Interrupt Set Enable Register */
          uint32_t RESERVED0[24U];    
    __IOM uint32_t ICER[8U];          /* Interrupt Clear Enable Register */
          uint32_t RESERVED1[24U];
    __IOM uint32_t ISPR[8U];          /* Interrupt Set Pending Register */
          uint32_t RESERVED2[24U];     
    __IOM uint32_t ICPR[8U];          /* Interrupt Clear Pending Register */ 
          uint32_t RESERVED3[24U];
    __IM const uint32_t IABR[8U];     /* Interrupt Active bit Register */
          uint32_t RESERVED4[56U];
    __IOM uint8_t IPR[240U];          /* Interrupt Priority Register (8Bit wide) */
          uint32_t RESERVED5[644U];      
    __OM  uint32_t STIR;              /* Software Trigger Interrupt Register */
} NVIC_t;


/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/

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

/******************************************************************************/

/******************************************************************************/
/* PRIVATE FUNCTION DEFINITIONS */
/******************************************************************************/
/******************************************************************************/

static uint32_t GetPriorityGrouping(void)
{
    return (SCB_AIRCR & SCB_AIRCR_PRIGROUP_Msk);
}

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/

NVIC_ErrorStatus_t NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
    /** error status which will return from the function */
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK; 
    if(IS_NVIC_PRIORITY_GROUP(PriorityGroup))
    { 
        /** assign write key and priority group */ 
        SCB_AIRCR = (SCB_AIRCR_VECTKEY_VALUE | PriorityGroup);
    }
    else
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, 
                                  uint32_t SubPriority)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else if(IS_NOT_NVIC_PREEMPTION_PRIORITY(PreemptPriority))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else if(IS_NOT_NVIC_SUB_PRIORITY(SubPriority))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else
    {
        /** Get the priority group */
        uint32_t PriorityGroupTmp = GetPriorityGrouping();
        uint32_t PreemptPriorityPos;

        /** Get the preempt priority position depend on the priority group*/
        PreemptPriorityPos =(__NVIC_PRIO_BITS ) - (((PriorityGroupTmp == PRIORITYGROUP_4) ?
                            NO_PREEMPT_PRIORITY : 
                            GET_PREEMPT_PRIORITY_POS(PriorityGroupTmp)));

        /** If the the priority group is 4 with no preempt priority */
        PreemptPriorityPos = (PreemptPriorityPos == -1) ? __NVIC_PRIO_BITS : PreemptPriorityPos;

        /** Selects only the relevant bits based on the configured priority group.*/
        SubPriority &= ~(__NVIC_PRIO_Msk << PreemptPriorityPos);

        /** assign the priority to the IRQn */
        NVIC->IPR[IRQn] = (uint8_t)((( PreemptPriority << PreemptPriorityPos) | SubPriority) << 4U);
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_EnableIRQ(IRQn_Type IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else
    {
        /**Enable the provided IRQn*/
        NVIC->ISERx[IRQn >> 5UL] = (1 << (IRQn % 32));
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_DisableIRQ(IRQn_Type IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else
    {
        /**Disable the provided IRQn*/
        NVIC->ICER[IRQn >> 5UL] = (1 << (IRQn % 32));
    }
    return RET_ErrorStatus;
}

__NO_RETURN NVIC_SystemReset(void)
{
    /** Reset request */
    SCB_AIRCR |= (1 << SCB_AIRCR_SYSRESETREQ_Msk);

    /**waiting until the request is handled */
    while (1);
}

uint32_t NVIC_GetPriorityGrouping(void)
{
    return GetPriorityGrouping();
}

NVIC_ErrorStatus_t NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, 
                                  uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
    NVIC_ErrorStatus_t RET_errorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_errorStatus = NVIC_NOT_OK;
    }
    else if(!IS_NVIC_PRIORITY_GROUP(PriorityGroup))
    {
        RET_errorStatus = NVIC_NOT_OK;
    }
    else if(pPreemptPriority == NULL || pSubPriority == NULL)
    {
        RET_errorStatus = NVIC_NULL_PTR_PASSED;
    }
    else
    {
        /** Get the current priority which will decoded */
        uint8_t Priority = NVIC->IPR[IRQn];

        /** Moves the priority to the lower 4 bits  */
        Priority >>= __NVIC_PRIO_BITS ;

        /** Retrieves the number of bits allocated for the preemptive priority based on
            the configured priority group. */
        uint32_t PreemptPriorityBits = 
                                GET_PREEMPT_PRIORITY_POS(PriorityGroup);

        /** The preempt priority  */
        *pPreemptPriority = (Priority >> (__NVIC_PRIO_BITS - PreemptPriorityBits));

        /** The sub priority  */
        *pSubPriority     = (Priority & 
                            ~(__NVIC_PRIO_Msk << (__NVIC_PRIO_BITS - PreemptPriorityBits)));
        
    }
    return RET_errorStatus;
}

NVIC_ErrorStatus_t NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else
    {
        /** Sets pending status for the specified IRQn. */
        NVIC->ISPR[IRQn >> 5UL] = (1 << (IRQn % 32));
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetPendingIRQ(IRQn_Type IRQn, uint32_t * pPendingState)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else if(pPendingState == NULL)
    {
        RET_ErrorStatus = NVIC_NULL_PTR_PASSED;
    }
    else
    {
        /** Get the pending status for the specified IRQn. */
        *pPendingState = NVIC->ISPR[IRQn >> 5UL] & (1 << (IRQn%32));
    } 
    return RET_ErrorStatus;
}



NVIC_ErrorStatus_t NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else
    {
        /** Clear pending status for the specified IRQn. */
        NVIC->ICPR[IRQn >> 5UL] = (uint32_t)(1UL << (IRQn % 32));
    }
    return RET_ErrorStatus;
}

NVIC_ErrorStatus_t NVIC_GetActive(IRQn_Type IRQn,uint32_t * pActiveState)
{
    NVIC_ErrorStatus_t RET_ErrorStatus = NVIC_OK;
    if(IS_NOT_NVIC_IRQn(IRQn))
    {
        RET_ErrorStatus = NVIC_NOT_OK;
    }
    else if(pActiveState == NULL)
    {
        RET_ErrorStatus = NVIC_NULL_PTR_PASSED;
    }
    else
    {
        /** Get the active status for the specified IRQn. */
        *pActiveState = NVIC->IABR[IRQn >> 5UL] & (1 << (IRQn%32));
    } 
    return RET_ErrorStatus;
}
/******************************************************************************/