/******************************************************************************/
/**
 * @file DMA.c
 * @brief **STM32 DMA Peripheral Driver**
 *
 * This file implements a driver for the Direct Memory Access (DMA) controller 
 * on STM32 microcontrollers. It provides functions for initializing DMA streams, 
 * configuring transfers, and starting/stopping DMA operations.
 *
 * @par Project Name
 * **(Replace with your project name)**
 * 
 * @par Code Language
 * C
 *
 * @par Description
 * This driver provides basic functionalities for DMA configuration and transfer 
 * management. It can be adapted to work with different STM32 peripherals that 
 * support DMA transfers.
 *
 * @par Author
 * Mahmoud Abou-Hawis
 *
 */
/******************************************************************************/


/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include "stm32f4xx_dma.h"

/******************************************************************************/

/******************************************************************************/
/* PRIVATE DEFINES */
/******************************************************************************/
/**
 * @brief  Defines 'read / write' structure member permissions.
 */
#define __IOM volatile


#define DMA_SxCR_EN_Pos          (0U)                                          
#define DMA_SxCR_EN_Msk          (0x1UL << DMA_SxCR_EN_Pos)                     
#define DMA_SxCR_EN              DMA_SxCR_EN_Msk  

#define DMA_SxCR_CHSEL_Pos       (25U)                                         
#define DMA_SxCR_CHSEL_Msk       (0x7UL << DMA_SxCR_CHSEL_Pos)                  
#define DMA_SxCR_CHSEL           DMA_SxCR_CHSEL_Msk     

#define DMA_SxCR_MBURST_Pos      (23U)                                         
#define DMA_SxCR_MBURST_Msk      (0x3UL << DMA_SxCR_MBURST_Pos)                 
#define DMA_SxCR_MBURST          DMA_SxCR_MBURST_Msk 

#define DMA_SxCR_PBURST_Pos      (21U)                                         
#define DMA_SxCR_PBURST_Msk      (0x3UL << DMA_SxCR_PBURST_Pos)                
#define DMA_SxCR_PBURST          DMA_SxCR_PBURST_Msk

#define DMA_SxCR_CT_Pos          (19U)                                         
#define DMA_SxCR_CT_Msk          (0x1UL << DMA_SxCR_CT_Pos)                  
#define DMA_SxCR_CT              DMA_SxCR_CT_Msk  

#define DMA_SxCR_DBM_Pos         (18U)                                         
#define DMA_SxCR_DBM_Msk         (0x1UL << DMA_SxCR_DBM_Pos)                   
#define DMA_SxCR_DBM             DMA_SxCR_DBM_Msk    


#define DMA_SxCR_PL_Pos          (16U)                                         
#define DMA_SxCR_PL_Msk          (0x3UL << DMA_SxCR_PL_Pos)                   
#define DMA_SxCR_PL              DMA_SxCR_PL_Msk        

#define DMA_SxCR_PINCOS_Pos      (15U)                                         
#define DMA_SxCR_PINCOS_Msk      (0x1UL << DMA_SxCR_PINCOS_Pos)                 
#define DMA_SxCR_PINCOS          DMA_SxCR_PINCOS_Msk    

#define DMA_SxCR_MSIZE_Pos       (13U)                                         
#define DMA_SxCR_MSIZE_Msk       (0x3UL << DMA_SxCR_MSIZE_Pos)              
#define DMA_SxCR_MSIZE           DMA_SxCR_MSIZE_Msk  

#define DMA_SxCR_PSIZE_Pos       (11U)                                         
#define DMA_SxCR_PSIZE_Msk       (0x3UL << DMA_SxCR_PSIZE_Pos)                
#define DMA_SxCR_PSIZE           DMA_SxCR_PSIZE_Msk 

#define DMA_SxCR_MINC_Pos        (10U)                                         
#define DMA_SxCR_MINC_Msk        (0x1UL << DMA_SxCR_MINC_Pos)                  
#define DMA_SxCR_MINC            DMA_SxCR_MINC_Msk 

#define DMA_SxCR_PINC_Pos        (9U)                                          
#define DMA_SxCR_PINC_Msk        (0x1UL << DMA_SxCR_PINC_Pos)                  
#define DMA_SxCR_PINC            DMA_SxCR_PINC_Msk  


#define DMA_SxCR_CIRC_Pos        (8U)                                          
#define DMA_SxCR_CIRC_Msk        (0x1UL << DMA_SxCR_CIRC_Pos)                 
#define DMA_SxCR_CIRC            DMA_SxCR_CIRC_Msk   

#define DMA_SxCR_DIR_Pos         (6U)                                          
#define DMA_SxCR_DIR_Msk         (0x3UL << DMA_SxCR_DIR_Pos)                    
#define DMA_SxCR_DIR             DMA_SxCR_DIR_Msk       


#define DMA_SxCR_PFCTRL_Pos      (5U)                                          
#define DMA_SxCR_PFCTRL_Msk      (0x1UL << DMA_SxCR_PFCTRL_Pos)                 
#define DMA_SxCR_PFCTRL          DMA_SxCR_PFCTRL_Msk  
                         


#define DMA_SxFCR_FTH_Pos        (0U)                                          
#define DMA_SxFCR_FTH_Msk        (0x3UL << DMA_SxFCR_FTH_Pos)                 
#define DMA_SxFCR_FTH            DMA_SxFCR_FTH_Msk 


#define DMA_HIFCR_CDMEIF7_Pos   (24)
#define DMA_HIFCR_CDMEIF7_Msk   (0x1UL << DMA_HIFCR_CDMEIF7_Pos)                 
#define DMA_HIFCR_CDMEIF7       DMA_HIFCR_CDMEIF7_Msk

#define DMA_HISR_DMEIF7_Pos   (24)
#define DMA_HISR_DMEIF7_Msk   (0x1UL << DMA_HISR_DMEIF7_Pos)                 
#define DMA_HISR_DMEIF7       DMA_HISR_DMEIF7_Msk


#define DMA_HIFCR_CTEIF7_Pos   (25)
#define DMA_HIFCR_CTEIF7_Msk   (0x1UL << DMA_HIFCR_CTEIF7_Pos)                 
#define DMA_HIFCR_CTEIF7       DMA_HIFCR_CTEIF7_Msk

#define DMA_HISR_TEIF7_Pos   (25)
#define DMA_HISR_TEIF7_Msk   (0x1UL << DMA_HISR_TEIF7_Pos)                 
#define DMA_HISR_TEIF7       DMA_HISR_TEIF7_Msk


#define DMA_HIFCR_CHTIF7_Pos   (26)
#define DMA_HIFCR_CHTIF7_Msk   (0x1UL << DMA_HIFCR_CHTIF7_Pos)                 
#define DMA_HIFCR_CHTIF7       DMA_HIFCR_CHTIF7_Msk

#define DMA_HISR_HTIF7_Pos   (26)
#define DMA_HISR_HTIF7_Msk  (0x1UL << DMA_HISR_HTIF7_Pos)                 
#define DMA_HISR_HTIF7       DMA_HISR_HTIF7_Msk


#define DMA_HIFCR_CTCIF7_Pos   (27)
#define DMA_HIFCR_CTCIF7_Msk   (0x1UL << DMA_HIFCR_CTCIF7_Pos)                 
#define DMA_HIFCR_CTCIF7       DMA_HIFCR_CTCIF7_Msk

#define DMA_HISR_TCIF7_Pos   (27)
#define DMA_HISR_TCIF7_Msk   (0x1UL << DMA_HISR_TCIF7_Pos)                 
#define DMA_HISR_TCIF7       DMA_HISR_TCIF7_Msk


#define DMA_HIFCR_CDMEIF5_Pos   (8U)
#define DMA_HIFCR_CDMEIF5_Msk   (0x1UL << DMA_HIFCR_CDMEIF5_Pos)                 
#define DMA_HIFCR_CDMEIF5       DMA_HIFCR_CDMEIF5_Msk

#define DMA_HISR_DMEIF5_Pos   (8U)
#define DMA_HISR_DMEIF5_Msk   (0x1UL << DMA_HISR_DMEIF5_Pos)                 
#define DMA_HISR_DMEIF5       DMA_HISR_DMEIF5_Msk


#define DMA_HIFCR_CTEIF5_Pos   (9U)
#define DMA_HIFCR_CTEIF5_Msk   (0x1UL << DMA_HIFCR_CTEIF5_Pos)                 
#define DMA_HIFCR_CTEIF5       DMA_HIFCR_CTEIF5_Msk

#define DMA_HISR_TEIF5_Pos   (9U)
#define DMA_HISR_TEIF5_Msk   (0x1UL << DMA_HISR_TEIF5_Pos)                 
#define DMA_HISR_TEIF5       DMA_HISR_TEIF5_Msk


#define DMA_HIFCR_CHTIF5_Pos   (10U)
#define DMA_HIFCR_CHTIF5_Msk   (0x1UL << DMA_HIFCR_CHTIF5_Pos)                 
#define DMA_HIFCR_CHTIF5       DMA_HIFCR_CHTIF5_Msk

#define DMA_HISR_HTIF5_Pos   (10U)
#define DMA_HISR_HTIF5_Msk  (0x1UL << DMA_HISR_HTIF5_Pos)                 
#define DMA_HISR_HTIF5       DMA_HISR_HTIF5_Msk


#define DMA_HIFCR_CTCIF5_Pos   (11U)
#define DMA_HIFCR_CTCIF5_Msk   (0x1UL << DMA_HIFCR_CTCIF5_Pos)                 
#define DMA_HIFCR_CTCIF5       DMA_HIFCR_CTCIF5_Msk

#define DMA_HISR_TCIF5_Pos   (11U)
#define DMA_HISR_TCIF5_Msk   (0x1UL << DMA_HISR_TCIF5_Pos)                 
#define DMA_HISR_TCIF5       DMA_HISR_TCIF5_Msk


#define NUMBER_OF_STREAMS   (8U)
#define STREAM_7            (7U)
#define STREAM_5            (5U)
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE MACROS */
/******************************************************************************/


#define IS_DMA_CHANNEL(CHANNEL) (((CHANNEL) == DMA_CHANNEL_0) || \
                                 ((CHANNEL) == DMA_CHANNEL_1) || \
                                 ((CHANNEL) == DMA_CHANNEL_2) || \
                                 ((CHANNEL) == DMA_CHANNEL_3) || \
                                 ((CHANNEL) == DMA_CHANNEL_4) || \
                                 ((CHANNEL) == DMA_CHANNEL_5) || \
                                 ((CHANNEL) == DMA_CHANNEL_6) || \
                                 ((CHANNEL) == DMA_CHANNEL_7))

#define IS_DMA_BASE_ADDRESS(BASE) (((BASE) == DMA1) || ((BASE) == DMA2))

#define IS_DMA_STREAM(STREAM) (((STREAM) == DMA_STREAM_0) || \
                                ((STREAM) == DMA_STREAM_1) || \
                                ((STREAM) == DMA_STREAM_2) || \
                                ((STREAM) == DMA_STREAM_3) || \
                                ((STREAM) == DMA_STREAM_4) || \
                                ((STREAM) == DMA_STREAM_5) || \
                                ((STREAM) == DMA_STREAM_6) || \
                                ((STREAM) == DMA_STREAM_7))

#define IS_DMA_DIRECTION(DIRECTION) (((DIRECTION) == DMA_PERIPH_TO_MEMORY) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_PERIPH) || \
                                     ((DIRECTION) == DMA_MEMORY_TO_MEMORY))

#define IS_DMA_TRANSFER_MODE(MODE) (((MODE) == DMA_NORMAL) || \
                                    ((MODE) == DMA_CIRCULAR) || \
                                    ((MODE) == DMA_PFCTRL))

#define IS_DMA_PERIPHERAL_INCREMENT_MODE(MODE) (((MODE) == DMA_PERIPHERAL_INCREMENT_DISABLED) || \
                                                ((MODE) == DMA_PERIPHERAL_INCREMENT_ENABLED))

#define IS_DMA_MEMORY_INCREMENT_MODE(MODE) (((MODE) == DMA_MEMORY_INCREMENT_DISABLED) || \
                                            ((MODE) == DMA_MEMORY_INCREMENT_ENABLED))

#define IS_DMA_PERIPHERAL_DATA_ALIGNMENT(MODE) (((MODE) == DMA_PDATAALIGN_BYTE) || \
                                                ((MODE) == DMA_PDATAALIGN_HALFWORD) || \
                                                ((MODE) == DMA_PDATAALIGN_WORD))

#define IS_DMA_MEMORY_DATA_ALIGNMENT(MODE) (((MODE) == DMA_MDATAALIGN_BYTE) || \
                                            ((MODE) == DMA_MDATAALIGN_HALFWORD) || \
                                            ((MODE) == DMA_MDATAALIGN_WORD))

#define IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_PRIORITY_LOW) || \
                                    ((PRIORITY) == DMA_PRIORITY_MEDIUM) || \
                                    ((PRIORITY) == DMA_PRIORITY_HIGH) || \
                                    ((PRIORITY) == DMA_PRIORITY_VERY_HIGH))


#define IS_DMA_MEMORY_BURST_SIZE(SIZE) (((SIZE) == DMA_MBURST_SINGLE) || \
                                        ((SIZE) == DMA_MBURST_INC4) || \
                                        ((SIZE) == DMA_MBURST_INC8) || \
                                        ((SIZE) == DMA_MBURST_INC16))


#define IS_DMA_PERIPHERAL_BURST_SIZE(SIZE) (((SIZE) == DMA_PBURST_SINGLE) || \
                                            ((SIZE) == DMA_PBURST_INC4) || \
                                            ((SIZE) == DMA_PBURST_INC8) || \
                                            ((SIZE) == DMA_PBURST_INC16))

#define IS_DMA_FIFO_THRESHOLD(THRESHOLD) (((THRESHOLD) == DMA_FIFO_THRESHOLD_1QUARTERFULL) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_HALFFULL) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_3QUARTERSFULL) || \
                                          ((THRESHOLD) == DMA_FIFO_THRESHOLD_FULL))

#define IS_DMA_FIFO_MODE(MODE) (((MODE) == DMA_FIFOMODE_DISABLE) || \
                                ((MODE) == DMA_FIFOMODE_ENABLE))


#define IS_NULL_PARAM(PARAM) ((PARAM) == NULL)


#define IS_DMA_BUSY(STATUS) (STATUS == DMA_STATE_BUSY)


/******************************************************************************/
/* PRIVATE ENUMS */
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/
/* PRIVATE TYPES */
/******************************************************************************/

/** 
  * @brief DMA Controller
  */
typedef struct
{
  __IOM uint32_t CR;     /*!< DMA stream x configuration register      */
  __IOM uint32_t NDTR;   /*!< DMA stream x number of data register     */
  __IOM uint32_t PAR;    /*!< DMA stream x peripheral address register */
  __IOM uint32_t M0AR;   /*!< DMA stream x memory 0 address register   */
  __IOM uint32_t M1AR;   /*!< DMA stream x memory 1 address register   */
  __IOM uint32_t FCR;    /*!< DMA stream x FIFO control register       */
} DMA_Stream_t;

typedef struct
{
  __IOM uint32_t LISR;   /*!< DMA low interrupt status register        */
  __IOM uint32_t HISR;   /*!< DMA high interrupt status register       */
  __IOM uint32_t LIFCR;  /*!< DMA low interrupt flag clear register    */
  __IOM uint32_t HIFCR;  /*!< DMA high interrupt flag clear register   */
} DMA_t;



/******************************************************************************/

/******************************************************************************/
/* PRIVATE CONSTANT DEFINITIONS */
/******************************************************************************/


/******************************************************************************/

/******************************************************************************/
/* PRIVATE VARIABLE DEFINITIONS */
/******************************************************************************/
static DMA_Handle_t * HandlesDMA2[NUMBER_OF_STREAMS] = {0};
static DMA_Handle_t * HandlesDMA1[NUMBER_OF_STREAMS] = {0};
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

/******************************************************************************/
/* PUBLIC FUNCTION DEFINITIONS */
/******************************************************************************/
DMA_ErrorStatus_t DMA_Init(DMA_Handle_t * pHandleDMA, uint32_t TimeOut)
{
    DMA_ErrorStatus_t RET_ErrorStatus = DMA_OK;

    /** Check if the parameters are valid */
    if (!IS_NULL_PARAM(pHandleDMA) &&
        IS_DMA_BASE_ADDRESS(pHandleDMA->Instance) &&
        IS_DMA_STREAM(pHandleDMA->Stream) &&
        IS_DMA_DIRECTION(pHandleDMA->Initialization.Direction) &&
        IS_DMA_CHANNEL(pHandleDMA->Initialization.Channel) &&
        IS_DMA_TRANSFER_MODE(pHandleDMA->Initialization.Mode) &&
        IS_DMA_MEMORY_BURST_SIZE(pHandleDMA->Initialization.MemBurst) &&
        IS_DMA_MEMORY_INCREMENT_MODE(pHandleDMA->Initialization.MemInc) &&
        IS_DMA_MEMORY_DATA_ALIGNMENT(pHandleDMA->Initialization.MemAlignment) &&
        IS_DMA_PRIORITY(pHandleDMA->Initialization.Priority) &&
        IS_DMA_PERIPHERAL_DATA_ALIGNMENT(pHandleDMA->Initialization.PerAlignment) &&
        IS_DMA_PERIPHERAL_BURST_SIZE(pHandleDMA->Initialization.PeriphBurst) &&
        IS_DMA_PERIPHERAL_INCREMENT_MODE(pHandleDMA->Initialization.PeriphInc) &&
        IS_DMA_FIFO_MODE(pHandleDMA->Initialization.FIFOMode) )
    {
        pHandleDMA->State = DMA_STATE_BUSY;

        /** get the stream which will configured */
        DMA_Stream_t * stream = (DMA_Stream_t *)((uint32_t)pHandleDMA->Instance + 
                                                 ((uint32_t)(pHandleDMA->Stream) >> 4));
        /** Check if the stram not busy */
        while ((stream->CR & DMA_SxCR_EN) == DMA_BUSY && TimeOut--);
        if(TimeOut == 0)
        {
            RET_ErrorStatus = DMA_TIMEOUT;
        }
        else
        {
            uint32_t Temp = stream->CR;
            /** Clear last configuration */
            Temp &= ~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST | 
                      DMA_SxCR_PL    | DMA_SxCR_MSIZE  | DMA_SxCR_PSIZE  | 
                      DMA_SxCR_MINC  | DMA_SxCR_PINC   | DMA_SxCR_CIRC   | 
                      DMA_SxCR_DIR   | DMA_SxCR_CT     | DMA_SxCR_DBM);
            /** set the new configuration */
            Temp |= (pHandleDMA->Initialization.Channel     | pHandleDMA->Initialization.Priority     |
                     pHandleDMA->Initialization.Direction   | pHandleDMA->Initialization.Mode         |
                     pHandleDMA->Initialization.MemInc      | pHandleDMA->Initialization.PerAlignment |
                     pHandleDMA->Initialization.PeriphBurst | pHandleDMA->Initialization.MemAlignment );
                     
            if(pHandleDMA->Initialization.FIFOMode == DMA_FIFOMODE_ENABLE)
            {
                Temp |= (pHandleDMA->Initialization.MemBurst | pHandleDMA->Initialization.PeriphBurst);
            }
            stream->CR = Temp;
            Temp = stream->FCR;
            Temp &=  ~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);
            if(pHandleDMA->Initialization.FIFOMode == DMA_FIFOMODE_ENABLE)
            {
                Temp |= (pHandleDMA->Initialization.FIFOThreshold | pHandleDMA->Initialization.FIFOMode);
            }
            stream->FCR = Temp;
            pHandleDMA->State = DMA_STATE_READY;
            if(pHandleDMA->Instance == DMA2)
            {
                HandlesDMA2[(pHandleDMA->Stream &0x00F)] = pHandleDMA;
            }
            else
            {
                HandlesDMA1[(pHandleDMA->Stream &0x00F)] = pHandleDMA;
            }
        }
    }
    else
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    return RET_ErrorStatus;
}

DMA_ErrorStatus_t DMA_RegisterCallBack(DMA_Handle_t *pHandleDMA, 
                                            DMA_InterruptId IntId,void (*CallBack)(void))
{
    DMA_ErrorStatus_t RET_ErrorStatus = DMA_OK;
    if(IS_NULL_PARAM(pHandleDMA))
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    else if(IS_DMA_BUSY(pHandleDMA->State))
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    else
    {
        switch (IntId)
        {
        case HALF_TRANSFER_CALLBACK:
            pHandleDMA->HalfTransferCallBack = CallBack;
            break;
        case COMPLETE_TRANSFER_CALLBACK:
            pHandleDMA->CompleteTransferCallBack = CallBack;
            break;
        case ERROR_TRANSFER_CALLBACK:
            pHandleDMA->ErrorTransferCallBack = CallBack;
            break;
        default:
            RET_ErrorStatus = DMA_ERROR;
            break;
        }
    }
    return RET_ErrorStatus;
}

DMA_ErrorStatus_t DMA_UnRegisterCallBack(DMA_Handle_t *pHandleDMA,
                                        DMA_InterruptId IntId)
{
    DMA_ErrorStatus_t RET_ErrorStatus = DMA_OK;
    if(IS_NULL_PARAM(pHandleDMA))
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    else if(IS_DMA_BUSY(pHandleDMA->State))
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    else
    {
        switch (IntId)
        {
        case HALF_TRANSFER_CALLBACK:
            pHandleDMA->HalfTransferCallBack = NULL;
            break;
        case COMPLETE_TRANSFER_CALLBACK:
            pHandleDMA->CompleteTransferCallBack = NULL;
            break;
        case ERROR_TRANSFER_CALLBACK:
            pHandleDMA->ErrorTransferCallBack = NULL;
            break;
        default:
            RET_ErrorStatus = DMA_ERROR;
            break;
        }
    }
    return RET_ErrorStatus;
}

DMA_ErrorStatus_t DMA_GetState(DMA_Handle_t *pHandleDMA, DMA_States_t * state)
{
    DMA_ErrorStatus_t RET_ErrorStatus = DMA_OK;
    if(IS_NULL_PARAM(pHandleDMA) || IS_NULL_PARAM(state))
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    else
    {   
        *state = pHandleDMA->State;
    }
    return RET_ErrorStatus;
}

DMA_ErrorStatus_t DMA_StartInterrupt(DMA_Handle_t * pHandleDMA,void * srcAddress,
                                   void * destAddress , uint32_t DataLength)
{
    DMA_ErrorStatus_t RET_ErrorStatus = DMA_OK;
    if(IS_NULL_PARAM(pHandleDMA) || IS_NULL_PARAM(srcAddress) || IS_NULL_PARAM(destAddress))
    {
        RET_ErrorStatus = DMA_ERROR;
    }
    else if(pHandleDMA->State == DMA_STATE_BUSY)
    {
        RET_ErrorStatus = DMA_BUSY;
    }
    else
    {
        pHandleDMA->State = DMA_BUSY;
        DMA_Stream_t * stream = (DMA_Stream_t *)((uint32_t)pHandleDMA->Instance + 
                                                 (uint32_t)(pHandleDMA->Stream >> 4));
        uint32_t Temp = stream->CR;
        Temp |= (DMA_IT_TC | DMA_IT_TE | DMA_IT_HT);
        stream->CR = Temp;
        if(pHandleDMA->Initialization.Direction == DMA_PERIPH_TO_MEMORY)
        {
            stream->PAR  = (uint32_t)srcAddress;
            stream->M0AR = (uint32_t)destAddress; 
        }
        else
        {
            stream->PAR  = (uint32_t)destAddress;
            stream->M0AR = (uint32_t)srcAddress; 
        }
        stream->NDTR = DataLength;
        stream->CR |= DMA_SxCR_EN;
    }
    return RET_ErrorStatus;
}

void DMA2_Stream7_IRQHandler(void)
{
    DMA_t * instance = ((DMA_t*)DMA2);
    if((instance->HISR & DMA_HISR_TCIF7 )== DMA_HISR_TCIF7)
    {
        if(HandlesDMA2[STREAM_7]->CompleteTransferCallBack != NULL)
        {
            HandlesDMA2[STREAM_7]->CompleteTransferCallBack();
        }
        instance->HIFCR |= DMA_HIFCR_CTCIF7;
    }
    if((instance->HISR & DMA_HISR_HTIF7) == DMA_HISR_HTIF7)
    {
        if(HandlesDMA2[STREAM_7]->HalfTransferCallBack != NULL)
        {
            HandlesDMA2[STREAM_7]->HalfTransferCallBack();
        }
        instance->HIFCR |= DMA_HIFCR_CHTIF7;
    }
    if((instance->HISR & DMA_HISR_TEIF7) == DMA_HISR_TEIF7)
    {
        if(HandlesDMA2[STREAM_7]->ErrorTransferCallBack != NULL)
        {
            HandlesDMA2[STREAM_7]->ErrorTransferCallBack();
        }
        instance->HIFCR |= DMA_HIFCR_CTEIF7;
    }
    instance->HIFCR |= 0x0F400000;
}

void DMA2_Stream5_IRQHandler(void)
{
DMA_t * instance = ((DMA_t*)DMA2);
    if((instance->HISR & DMA_HISR_TCIF5 )== DMA_HISR_TCIF5)
    {
        if(HandlesDMA2[STREAM_5]->CompleteTransferCallBack != NULL)
        {
            HandlesDMA2[STREAM_5]->CompleteTransferCallBack();
        }
        instance->HIFCR |= DMA_HIFCR_CTCIF5;
    }
    if((instance->HISR & DMA_HISR_HTIF5) == DMA_HISR_HTIF5)
    {
        if(HandlesDMA2[STREAM_5]->HalfTransferCallBack != NULL)
        {
            HandlesDMA2[STREAM_5]->HalfTransferCallBack();
        }
        instance->HIFCR |= DMA_HIFCR_CHTIF5; 
    }
    if((instance->HISR & DMA_HISR_TEIF5) == DMA_HISR_TEIF5)
    {
        if(HandlesDMA2[STREAM_5]->ErrorTransferCallBack != NULL)
        {
            HandlesDMA2[STREAM_5]->ErrorTransferCallBack();
        }
        instance->HIFCR |= DMA_HIFCR_CTEIF5;
    }
    instance->HIFCR |= 0x0F400000;
}
/******************************************************************************/