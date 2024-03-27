/*******************************************************************************/
/**
 * @file DMA.h
 * @brief Provides functions and definitions for Direct Memory Access (DMA) 
 * control on STM32F401CC.
 *
 * @par Project Name
 * stm32f401xx drivers
 *
 * @par Code Language
 * C
 *
 * @par Description
 * This header file defines functions and macros for initializing, configuring,
 * and using the DMA controller on the STM32F401CC microcontroller. It provides
 * a layer of abstraction over the low-level register access specific to this
 * microcontroller, making it easier to perform DMA transfers in your code.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 * @date [25/3/2024]  
 *
 *******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef __STM32F4xx_DMA_H
#define __STM32F4xx_DMA_H
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
#include <stddef.h>
#include <stdint.h>
/******************************************************************************/

/******************************************************************************/
/* PUBLIC DEFINES */
/******************************************************************************/


#define DMA_SxCR_PFCTRL_Pos                 (5U)                           
#define DMA_SxCR_FLOWCTRL_0                 ((uint32_t)(0x1UL << DMA_SxCR_PFCTRL_Pos))


#define DMA_SxCR_DIR_Pos                    (6U)         
#define DMA_SxCR_DIR_0                      ((uint32_t)(0x1UL << DMA_SxCR_DIR_Pos))                    
#define DMA_SxCR_DIR_1                      ((uint32_t)(0x2UL << DMA_SxCR_DIR_Pos))


#define DMA_SxCR_CIRC_Pos                   (8U)
#define DMA_SxCR_CIRC_0                     ((uint32_t)(0x1UL << DMA_SxCR_CIRC_Pos))

#define DMA_SxCR_PINC_Pos                   (9U)
#define DMA_SxCR_PINC_0                     ((uint32_t)(0x1UL << DMA_SxCR_PINC_Pos))


#define DMA_SxCR_MINC_Pos                   (10U)
#define DMA_SxCR_MINC_0                     ((uint32_t)(0x1UL << DMA_SxCR_MINC_Pos))

#define DMA_SxCR_PSIZE_Pos                  (11U) 
#define DMA_SxCR_PSIZE_0                    ((uint32_t)(0x1UL << DMA_SxCR_PSIZE_Pos))
#define DMA_SxCR_PSIZE_1                    ((uint32_t)(0x2UL << DMA_SxCR_PSIZE_Pos))


#define DMA_SxCR_MSIZE_Pos                  (13U) 
#define DMA_SxCR_MSIZE_0                    ((uint32_t)(0x1UL << DMA_SxCR_MSIZE_Pos))
#define DMA_SxCR_MSIZE_1                    ((uint32_t)(0x2UL << DMA_SxCR_MSIZE_Pos))

#define DMA_SxCR_PL_Pos                     (16U)
#define DMA_SxCR_PL_0                       ((uint32_t)(0x1UL << DMA_SxCR_PL_Pos))
#define DMA_SxCR_PL_1                       ((uint32_t)(0x2UL << DMA_SxCR_PL_Pos))
#define DMA_SxCR_PL_2                       ((uint32_t)(0x3UL << DMA_SxCR_PL_Pos))

#define DMA_SxCR_PBURST_Pos                 (21U)
#define DMA_SxCR_PBURST_0                   ((uint32_t)(0x1UL << DMA_SxCR_PBURST_Pos))
#define DMA_SxCR_PBURST_1                   ((uint32_t)(0x2UL << DMA_SxCR_PBURST_Pos))
#define DMA_SxCR_PBURST_2                   ((uint32_t)(0x3UL << DMA_SxCR_PBURST_Pos))


#define DMA_SxCR_MBURST_Pos                 (23U)
#define DMA_SxCR_MBURST_0                   ((uint32_t)(0x1UL << DMA_SxCR_MBURST_Pos))
#define DMA_SxCR_MBURST_1                   ((uint32_t)(0x2UL << DMA_SxCR_MBURST_Pos))
#define DMA_SxCR_MBURST_2                   ((uint32_t)(0x3UL << DMA_SxCR_MBURST_Pos))

#define DMA_SxFCE_DMDIS_Pos                 (2U)
#define DMA_SxFCR_DMDIS_0                   ((uint32_t)(0x1UL << DMA_SxFCE_DMDIS_Pos))

#define DMA_SxFCR_FTH_Pos                   (0U)
#define DMA_SxFCR_FTH_0                     ((uint32_t)(0x1UL << DMA_SxFCR_FTH_Pos))
#define DMA_SxFCR_FTH_1                     ((uint32_t)(0x2UL << DMA_SxFCR_FTH_Pos))
#define DMA_SxFCR_FTH_2                     ((uint32_t)(0x3UL << DMA_SxFCR_FTH_Pos))

#define DMA_SxCR_TCIE_Pos                   (4U)                                          
#define DMA_SxCR_TCIE_Msk                   (0x1UL << DMA_SxCR_TCIE_Pos)                   
#define DMA_SxCR_TCIE                       DMA_SxCR_TCIE_Msk  

#define DMA_SxCR_HTIE_Pos                   (3U)                                          
#define DMA_SxCR_HTIE_Msk                   (0x1UL << DMA_SxCR_HTIE_Pos)                  
#define DMA_SxCR_HTIE                       DMA_SxCR_HTIE_Msk 

#define DMA_SxCR_TEIE_Pos                   (2U)                                          
#define DMA_SxCR_TEIE_Msk                   (0x1UL << DMA_SxCR_TEIE_Pos)                 
#define DMA_SxCR_TEIE                       DMA_SxCR_TEIE_Msk 

#define DMA_SxCR_DMEIE_Pos                  (1U)                                          
#define DMA_SxCR_DMEIE_Msk                  (0x1UL << DMA_SxCR_DMEIE_Pos)                  
#define DMA_SxCR_DMEIE                      DMA_SxCR_DMEIE_Msk     


#define DMA_SxFCR_DMDIS_Pos                 (2U)                                          
#define DMA_SxFCR_DMDIS_Msk                 (0x1UL << DMA_SxFCR_DMDIS_Pos)                 
#define DMA_SxFCR_DMDIS                     DMA_SxFCR_DMDIS_Msk  

/** @defgroup DMA_INSTANCES DMA Instances 
  * @brief    DMA Instances in the stm32f401xx
  * @{
  */
#define DMA1                                    ((void*)0x40026000)    
#define DMA2                                    ((void*)0x40026400)   
/**
  * @}
  */ 

/** @defgroup DMA_STREAMS DMA Available streams  
  * @brief    DMA Available streams in the stm32f401xx
  * @{
  */
#define DMA_STREAM_0                            0x100U                 
#define DMA_STREAM_1                            0x281U                  
#define DMA_STREAM_2                            0x402U                       
#define DMA_STREAM_3                            0x583U                 
#define DMA_STREAM_4                            0x704U               
#define DMA_STREAM_5                            0x885U              
#define DMA_STREAM_6                            0xA06U                 
#define DMA_STREAM_7                            0xB87U          
/**
  * @}
  */ 


/** @defgroup DMA_CHANNELS DMA Available channels  
  * @brief    DMA Available channels in the stm32f401xx
  * @{
  */
#define DMA_CHANNEL_0                           0x00000000U           
#define DMA_CHANNEL_1                           0x02000000U           
#define DMA_CHANNEL_2                           0x04000000U           
#define DMA_CHANNEL_3                           0x06000000U           
#define DMA_CHANNEL_4                           0x08000000U          
#define DMA_CHANNEL_5                           0x0A000000U           
#define DMA_CHANNEL_6                           0x0C000000U          
#define DMA_CHANNEL_7                           0x0E000000U           
/**
  * @}
  */ 


/** @defgroup DMA_DATA_DIRECTION DMA Available DMA Data transfer direction  
  * @brief    DMA Data transfer direction
  * @{
  */
#define DMA_PERIPH_TO_MEMORY                    0x00000000U                                      
#define DMA_MEMORY_TO_PERIPH                    DMA_SxCR_DIR_0  
#define DMA_MEMORY_TO_MEMORY                    DMA_SxCR_DIR_1 
/**
  * @}
  */ 

/** @defgroup DMA_MODE DMA Modes 
  * @brief    DMA Modes
  * @{
  */
#define DMA_NORMAL                              0x00000000U          
#define DMA_CIRCULAR                            DMA_SxCR_CIRC_0 
#define DMA_PFCTRL                              DMA_SxCR_FLOWCTRL_0 
 /**
  * @}
  */ 


/** @defgroup DMA_Peripheral_increment_Mode Peripheral increment mode
  * @brief    Peripheral increment mode
  * @{
  */
#define DMA_PERIPHERAL_INCREMENT_DISABLED       0x00000000U     
#define DMA_PERIPHERAL_INCREMENT_ENABLED        DMA_SxCR_CIRC_0 
 /**
  * @}
  */ 

/** @defgroup DMA_Memory_increment_Mode Memory increment mode
  * @brief    Memory increment mode
  * @{
  */
#define DMA_MEMORY_INCREMENT_DISABLED            0x00000000U
#define DMA_MEMORY_INCREMENT_ENABLED             DMA_SxCR_MINC_0
 /**
  * @}
  */ 

/** @defgroup DMA_Peripheral_data_size DMA Peripheral data size
  * @brief    DMA peripheral data size 
  * @{
  */ 
#define DMA_PDATAALIGN_BYTE                      0x00000000U                  
#define DMA_PDATAALIGN_HALFWORD                  DMA_SxCR_PSIZE_0             
#define DMA_PDATAALIGN_WORD                      DMA_SxCR_PSIZE_1  
/**
  * @}
  */ 

/** @defgroup DMA_Memory_data_size DMA Memory data size
  * @brief    DMA Memory data size 
  * @{
  */ 
#define DMA_MDATAALIGN_BYTE                      0x00000000U                  
#define DMA_MDATAALIGN_HALFWORD                  DMA_SxCR_MSIZE_0             
#define DMA_MDATAALIGN_WORD                      DMA_SxCR_MSIZE_1  
/**
  * @}
  */ 

/** @defgroup DMA_Priority_level DMA Priority level
  * @brief    DMA priority levels 
  * @{
  */
#define DMA_PRIORITY_LOW                         0x00000000U                 
#define DMA_PRIORITY_MEDIUM                      DMA_SxCR_PL_0   
#define DMA_PRIORITY_HIGH                        DMA_SxCR_PL_1   
#define DMA_PRIORITY_VERY_HIGH                   DMA_SxCR_PL_2    
/**
  * @}
  */ 

/** @defgroup DMA_Memory_burst DMA Memory burst
  * @brief    DMA memory burst 
  * @{
  */ 
#define DMA_MBURST_SINGLE                        0x00000000U
#define DMA_MBURST_INC4                          DMA_SxCR_MBURST_0
#define DMA_MBURST_INC8                          DMA_SxCR_MBURST_1 
#define DMA_MBURST_INC16                         DMA_SxCR_MBURST_2
/**
  * @}
  */ 

/** @defgroup DMA_Peripheral_burst DMA Peripheral burst
  * @brief    DMA peripheral burst 
  * @{
  */ 
#define DMA_PBURST_SINGLE                        0x00000000U
#define DMA_PBURST_INC4                          DMA_SxCR_PBURST_0
#define DMA_PBURST_INC8                          DMA_SxCR_PBURST_1
#define DMA_PBURST_INC16                         DMA_SxCR_PBURST_2
/**
  * @}
  */

/** @defgroup DMA_FIFO_mode DMA FIFO  mode
  * @brief    DMA FIFO  mode
  * @{
  */
#define DMA_FIFOMODE_DISABLE                     0x00000000U                
#define DMA_FIFOMODE_ENABLE                      DMA_SxFCR_DMDIS_0
/**
  * @}
  */ 

/** @defgroup DMA_FIFO_threshold_level DMA FIFO threshold level
  * @brief    DMA FIFO level 
  * @{
  */
#define DMA_FIFO_THRESHOLD_1QUARTERFULL          0x00000000U                  
#define DMA_FIFO_THRESHOLD_HALFFULL              DMA_SxFCR_FTH_0
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL         DMA_SxFCR_FTH_1  
#define DMA_FIFO_THRESHOLD_FULL                  DMA_SxFCR_FTH_2   
/**
  * @}
  */ 

 /** @defgroup DMA_interrupt_enable_definitions DMA interrupt enable definitions
  * @brief    DMA interrupts definition 
  * @{
  */
#define DMA_IT_TC                     ((uint32_t)DMA_SxCR_TCIE)
#define DMA_IT_TE                     ((uint32_t)DMA_SxCR_TEIE)
#define DMA_IT_DME                    ((uint32_t)DMA_SxCR_DMEIE)
#define DMA_IT_HT                     ((uint32_t)DMA_SxCR_HTIE)
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

/** @brief DMA transfer status enumeration. */
typedef enum 
{
  DMA_OK,          /**< Transfer completed successfully. */
  DMA_BUSY,        /**< The DMA controller is currently busy with another transfer. */
  DMA_ERROR,       /**< An error occurred during the transfer. */
  DMA_TIMEOUT
} DMA_ErrorStatus_t;

/** @brief DMA interrupt identifier enumeration. */
typedef enum
{
  HALF_TRANSFER_CALLBACK,  /**< Interrupt triggered when the DMA transfer 
                                reaches half completion. */
  COMPLETE_TRANSFER_CALLBACK, /**< Interrupt triggered when the DMA transfer
                                   is complete. */
  ERROR_TRANSFER_CALLBACK   /**< Interrupt triggered when an error occurs
                                 during the DMA transfer. */
} DMA_InterruptId;

/** @brief DMA channel state enumeration. */
typedef enum
{
  /** @brief DMA channel is in reset state (not initialized or undergoing reset). */
  DMA_STATE_RESET,

  /** @brief DMA channel is ready for a new transfer 
   *        (initialization complete, no ongoing transfer). */
  DMA_STATE_READY,

  /** @brief DMA channel is currently busy with a transfer operation. */
  DMA_STATE_BUSY,
} DMA_States_t;


/******************************************************************************/

/******************************************************************************/
/* PUBLIC TYPES */
/******************************************************************************/

/** @brief DMA initialization structure. */
typedef struct
{
  /** @brief DMA channel to be used.
   *  @ref DMA_CHANNELS*/
  uint32_t Channel;

  /** @brief Transfer direction (memory to peripheral or vice versa).
   *  @ref DMA_DATA_DIRECTION */
  uint32_t Direction;

  /** @brief Peripheral address increment mode. 
   *  @ref DMA_Peripheral_increment_Mode*/
  uint32_t PeriphInc;

  /** @brief Memory address increment mode. 
   *  @ref DMA_Memory_increment_Mode*/
  uint32_t MemInc;

  /** @brief Memory alignment for data transfers. 
   *  @ref DMA_Memory_data_size*/
  uint32_t MemAlignment;

  /** @brief Peripheral alignment for data transfers. 
   *  @ref DMA_Peripheral_data_size*/
  uint32_t PerAlignment;

  /** @brief Transfer priority level.
   *  @ref DMA_Priority_level*/
  uint32_t Priority;

  /** @brief DMA FIFO operation mode.
   *  @ref DMA_FIFO_mode*/
  uint32_t FIFOMode;

  /** @brief DMA FIFO threshold level.
   *  @ref DMA_FIFO_threshold_level*/
  uint32_t FIFOThreshold;

  /** @brief Peripheral burst size for data transfers.
   *  @ref DMA_Peripheral_burst*/
  uint32_t PeriphBurst;

  /** @brief Memory burst size for data transfers.
   *  @ref DMA_Memory_burst*/
  uint32_t MemBurst;

  /** @brief DMA Mode.
   *  @ref DMA_MODE*/
  uint32_t Mode;

} DMA_Init_t;


/** @brief DMA channel handle structure. */
typedef struct 
{
  /** @brief Pointer to the DMA controller instance. @ref DMA_INSTANCES*/
  void * Instance;

  /** @brief DMA stream number within the controller. @ref DMA_STREAMS*/
  uint32_t Stream;

  /** @brief DMA initialization configuration. */
  DMA_Init_t Initialization;

  /** @brief DMA Stream state. */
  DMA_States_t State;
  
  /** @brief Callback function for half transfer completion. */
  void (*HalfTransferCallBack)(void);

  /** @brief Callback function for complete transfer. */
  void (*CompleteTransferCallBack)(void);

  /** @brief Callback function for transfer error. */
  void (*ErrorTransferCallBack)(void);
  
} DMA_Handle_t;


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
 * @brief Initializes a DMA channel handle.
 *
 * This function configures a DMA channel based on the settings provided in the 
 * `pHandleDMA` structure's `Initialization` member.
 *
 * @param[in] pHandleDMA Pointer to a DMA handle structure (`DMA_Handle_t`). 
 *                       This structure must be filled with the desired DMA channel 
 *                       configuration before calling this function.
 *
 * @return DMA_ErrorStatus_t indicating the status of the initialization:
 *   - DMA_OK: Initialization successful.
 *   - DMA_ERROR: An error occurred during initialization.
 *   - DMA_BUSY: The DMA channel is currently busy.
 *
 * @note This function must be called before using any other DMA functions on the specified channel.
 */
extern DMA_ErrorStatus_t DMA_Init(DMA_Handle_t * pHandleDMA , uint32_t TimeOut);


/**
 * @brief Starts a DMA transfer.
 *
 * This function initiates a DMA transfer between the specified source and destination addresses
 *  with the provided data length.
 *
 * @param[in] pHandleDMA Pointer to a DMA handle structure (`DMA_Handle_t`). 
 *                       The channel and configuration for the transfer should be set in this structure 
 *                       before calling this function.
 * @param[in] srcAddress Source address for the data transfer.
 * @param[in] destAddress Destination address for the data transfer.
 * @param[in] DataLength Number of bytes to be transferred.
 *
 * @return DMA_ErrorStatus_t indicating the status of the transfer start:
 *   - DMA_OK: Transfer started successfully.
 *   - DMA_ERROR: An error occurred during transfer start.
 *   - DMA_BUSY: The DMA channel is currently busy.
 *
 */
extern DMA_ErrorStatus_t DMA_StartInterrupt(DMA_Handle_t * pHandleDMA,void * srcAddress,
                                              void * destAddress , uint32_t DataLength);


/**
 * @brief Registers a callback function for a specific DMA interrupt.
 *
 * This function associates a callback function with a particular DMA interrupt 
 *  (half-transfer, complete transfer, or error) for the specified channel.
 *
 * @param[in] pHandleDMA Pointer to a DMA handle structure (`DMA_Handle_t`).
 * @param[in] IntId Interrupt identifier (`DMA_InterruptId`).
 * @param[in] CallBack Pointer to the callback function to be invoked upon the specified interrupt.
 *
 * @return DMA_ErrorStatus_t indicating the status of the callback registration:
 *   - DMA_OK: Callback registered successfully.
 *   - DMA_ERROR: An error occurred during callback registration.
 *
 */
extern DMA_ErrorStatus_t DMA_RegisterCallBack(DMA_Handle_t *pHandleDMA, 
                                            DMA_InterruptId IntId,void (*CallBack)(void));


/**
 * @brief Unregisters a callback function for a specific DMA interrupt.
 *
 * This function removes a previously registered callback 
 * function associated with a particular DMA interrupt
 * (half-transfer, complete transfer, or error) for the specified channel.
 *
 * @param[in] pHandleDMA Pointer to a DMA handle structure (`DMA_Handle_t`).
 * @param[in] IntId Interrupt identifier (`DMA_InterruptId`).
 *
 * @return DMA_ErrorStatus_t indicating the status of the callback unregistration:
 *   - DMA_OK: Callback unregistered successfully.
 *   - DMA_ERROR: An error occurred during callback unregistration.
 *
 */
extern DMA_ErrorStatus_t DMA_UnRegisterCallBack(DMA_Handle_t *pHandleDMA,
                                                 DMA_InterruptId IntId);


/**
 * @brief Gets the current state of a DMA channel.
 *
 * This function retrieves the current state of the DMA channel 
 * represented by the provided handle. The specific details of the 
 * returned state information may vary depending on the DMA controller implementation.
 *
 * @param[in] pHandleDMA Pointer to a DMA handle structure (`DMA_Handle_t`).
 *
 * @param[in out] state pointer to DMA state.
 * 
 * @return DMA_ErrorStatus_t indicating the status of the callback unregistration:
 *   - DMA_OK: Callback unregistered successfully.
 *   - DMA_ERROR: An error occurred during callback unregistration.
 *
 */
extern DMA_ErrorStatus_t DMA_GetState(DMA_Handle_t *pHandleDMA, DMA_States_t * state);


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
#endif /* __STM32F4xx_DMA_H */
/******************************************************************************/
