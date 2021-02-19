#include "dma.h"

void DMA1_Channel1_init(void)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel1->CPAR = ; //Start addr of perif(or memory)
    DMA1_Channel1->CMAR = ; //Start addr of memory(or perif)
    DMA1_Channel1->CNDTR = ; //Count of words to transfer
    DMA1_Channel1->CCR |= DMA_CCR_MEM2MEM; //Mem to Mem mode
    DMA1_Channel1->CCR |= DMA_CCR_PL_0; //Set priority
    DMA1_Channel1->CCR |= DMA_CCR_MSIZE_0; //Set mem word size
    DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0; //Set perif word size
    DMA1_Channel1->CCR |= DMA_CCR_MINC; //MemAddr++
    DMA1_Channel1->CCR |= DMA_CCR_PINC; //PerifAddr++
    DMA1_Channel1->CCR |= DMA_CCR_CIRC; //Auto reload CNDTR
    DMA1_Channel1->CCR |= DMA_CCR_DIR; //Direction
//    DMA1_Channel1->CCR |= DMA_CCR_TEIE; //Interrupt transfer error
//    DMA1_Channel1->CCR |= DMA_CCR_HTIE; //Interrupt half transfer
//    DMA1_Channel1->CCR |= DMA_CCR_TCIE; //Interrupt transfer complete
    DMA1_Channel1->CCR |= DMA_CCR_EN; //Enable DMA
}

void DMA_buff_clear(void *struct *buff)
{
    memset(buff->data, 0, DMA_buff_size);
    buff->size = 0;
}