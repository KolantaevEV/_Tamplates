#include "dma.h"

void DMA2_S2_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2_Stream2->PAR = (uint32_t)addr_perif;   //addr perif
    DMA2_Stream2->M0AR = (uint32_t)addr_buff;   //addr memory #0
    DMA2_Stream2->M1AR = 0;   //addr memory #1 (not used in single buffer mode)
    DMA2_Stream2->NDTR = 128;   //count of data words
    DMA2_Stream2->FCR &= ~DMA_SxFCR_DMDIS;  //Direct mode or FIFO
    DMA2_Stream2->FCR &= ~DMA_SxFCR_FTH;    //FIFO threshold
    DMA2_Stream2->CR |= DMA_SxCR_CHSEL_2;   //select DMA channel
    DMA2_Stream2->CR &= ~DMA_SxCR_MBURST;   //set burst transfer from memory (reset = singl transfer)
    DMA2_Stream2->CR &= ~DMA_SxCR_PBURST;   //set burst transfer from perif (reset = singl transfer)
    DMA2_Stream2->CR &= ~DMA_SxCR_CT;   // start target buffer in double buffering
    DMA2_Stream2->CR &= ~DMA_SxCR_DBM;  //set Double buffer mode
    DMA2_Stream2->CR &= ~DMA_SxCR_PL;    //set priority
    DMA2_Stream2->CR &= ~DMA_SxCR_PINCOS;   //perif offset size
    DMA2_Stream2->CR &= ~DMA_SxCR_MSIZE;    //Mem word size
    DMA2_Stream2->CR &= ~DMA_SxCR_PSIZE;    //Perif word size
    DMA2_Stream2->CR |= DMA_SxCR_MINC;  //Memory increment mode
    DMA2_Stream2->CR &= ~DMA_SxCR_PINC;  //Perif increment mode
    DMA2_Stream2->CR &= ~DMA_SxCR_CIRC; //Circular mode
    DMA2_Stream2->CR &= ~DMA_SxCR_DIR;  //Ttransfer direction
    DMA2_Stream2->CR &= ~DMA_SxCR_PFCTRL;   //Flow controller
    DMA2_Stream2->CR |= DMA_SxCR_TCIE; //Transfer Complete interrupt
    DMA2_Stream2->CR &= ~DMA_SxCR_HTIE; //Half transfer interrupt
    DMA2_Stream2->CR |= DMA_SxCR_TEIE; //Transfer error interrupt
    DMA2_Stream2->CR &= ~DMA_SxCR_DMEIE; //Direct mode error interrupt
    DMA2_Stream2->FCR &= ~DMA_SxFCR_FEIE; //FIFO error interrupt
    DMA2_Stream2->CR |= DMA_SxCR_EN;    //Enable DMA
}

void DMA2_S7_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2_Stream7->PAR = (uint32_t)addr_perif;   //addr perif
    DMA2_Stream7->M0AR = (uint32_t)addr_buff;   //addr memory #0
    DMA2_Stream7->M1AR = 0;   //addr memory #1 (not used in single buffer mode)
    DMA2_Stream7->NDTR = 0;   //count of data words
    DMA2_Stream7->FCR &= ~DMA_SxFCR_DMDIS;  //Direct mode or FIFO
    DMA2_Stream7->FCR &= ~DMA_SxFCR_FTH;    //FIFO threshold
    DMA2_Stream7->CR |= DMA_SxCR_CHSEL_2;   //select DMA channel
    DMA2_Stream7->CR &= ~DMA_SxCR_MBURST;   //set burst transfer from memory (reset = singl transfer)
    DMA2_Stream7->CR &= ~DMA_SxCR_PBURST;   //set burst transfer from perif (reset = singl transfer)
    DMA2_Stream7->CR &= ~DMA_SxCR_CT;   // start target buffer in double buffering
    DMA2_Stream7->CR &= ~DMA_SxCR_DBM;  //set Double buffer mode
    DMA2_Stream7->CR &= ~DMA_SxCR_PL;    //set priority
    DMA2_Stream7->CR &= ~DMA_SxCR_PINCOS;   //perif offset size
    DMA2_Stream7->CR &= ~DMA_SxCR_MSIZE;    //Mem word size
    DMA2_Stream7->CR &= ~DMA_SxCR_PSIZE;    //Perif word size
    DMA2_Stream7->CR |= DMA_SxCR_MINC;  //Memory increment mode
    DMA2_Stream7->CR &= ~DMA_SxCR_PINC;  //Perif increment mode
    DMA2_Stream7->CR &= ~DMA_SxCR_CIRC; //Circular mode
    DMA2_Stream7->CR |= DMA_SxCR_DIR_0;  //Ttransfer direction
    DMA2_Stream7->CR &= ~DMA_SxCR_PFCTRL;   //flow controller
    DMA2_Stream7->CR |= DMA_SxCR_TCIE; //Transfer Complete interrupt
    DMA2_Stream7->CR &= ~DMA_SxCR_HTIE; //Half transfer interrupt
    DMA2_Stream7->CR |= DMA_SxCR_TEIE; //Transfer error interrupt
    DMA2_Stream7->CR &= ~DMA_SxCR_DMEIE; //Direct mode error interrupt
    DMA2_Stream7->FCR &= ~DMA_SxFCR_FEIE; //FIFO error interrupt
    DMA2_Stream7->CR &= ~DMA_SxCR_EN;    //Enable DMA
}