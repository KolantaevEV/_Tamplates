#include "dma.h"

void DMA1_Ch4_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel4->CPAR = (uint32_t)addr_perif; //Start addr of perif(or memory)
    DMA1_Channel4->CMAR = (uint32_t)addr_buff; //Start addr of memory(or perif)
    DMA1_Channel4->CNDTR = 0; //Count of words to transfer
    DMA1_Channel4->CCR &= ~DMA_CCR_MEM2MEM; //Mem to Mem mode
    DMA1_Channel4->CCR |= DMA_CCR_PL_0; //Set priority
    DMA1_Channel4->CCR &= ~DMA_CCR_MSIZE; //Set mem word size
    DMA1_Channel4->CCR &= ~DMA_CCR_PSIZE; //Set perif word size
    DMA1_Channel4->CCR |= DMA_CCR_MINC; //MemAddr++
    DMA1_Channel4->CCR &= ~DMA_CCR_PINC; //PerifAddr++
    DMA1_Channel4->CCR &= ~DMA_CCR_CIRC; //Auto reload CNDTR
    DMA1_Channel4->CCR |= DMA_CCR_DIR; //Direction
    DMA1_Channel4->CCR |= DMA_CCR_TEIE; //Interrupt transfer error
//    DMA1_Channel4->CCR |= DMA_CCR_HTIE; //Interrupt half transfer
    DMA1_Channel4->CCR |= DMA_CCR_TCIE; //Interrupt transfer complete
    DMA1_Channel4->CCR &= ~DMA_CCR_EN; //Enable DMA CH
}

void DMA1_Ch5_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel5->CPAR = (uint32_t)addr_perif; //Start addr of perif(or memory)
    DMA1_Channel5->CMAR = (uint32_t)addr_buff; //Start addr of memory(or perif)
    DMA1_Channel5->CNDTR = 128; //Count of words to transfer
    DMA1_Channel5->CCR &= ~DMA_CCR_MEM2MEM; //Mem to Mem mode
    DMA1_Channel5->CCR |= DMA_CCR_PL_1; //Set priority
    DMA1_Channel5->CCR &= ~DMA_CCR_MSIZE; //Set mem word size
    DMA1_Channel5->CCR &= ~DMA_CCR_PSIZE; //Set perif word size
    DMA1_Channel5->CCR |= DMA_CCR_MINC; //MemAddr++
    DMA1_Channel5->CCR &= ~DMA_CCR_PINC; //PerifAddr++
    DMA1_Channel5->CCR &= ~DMA_CCR_CIRC; //Auto reload CNDTR
    DMA1_Channel5->CCR &= ~DMA_CCR_DIR; //Direction
    DMA1_Channel5->CCR |= DMA_CCR_TEIE; //Interrupt transfer error
//    DMA1_Channel5->CCR |= DMA_CCR_HTIE; //Interrupt half transfer
    DMA1_Channel5->CCR |= DMA_CCR_TCIE; //Interrupt transfer complete
    DMA1_Channel5->CCR |= DMA_CCR_EN; //Enable DMA CH
}

void DMA1_Ch2_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel2->CPAR = (uint32_t)addr_perif; //Start addr of perif(or memory)
    DMA1_Channel2->CMAR = (uint32_t)addr_buff; //Start addr of memory(or perif)
    DMA1_Channel2->CNDTR = 0; //Count of words to transfer
    DMA1_Channel2->CCR &= ~DMA_CCR_MEM2MEM; //Mem to Mem mode
    DMA1_Channel2->CCR |= DMA_CCR_PL_0; //Set priority
    DMA1_Channel2->CCR &= ~DMA_CCR_MSIZE; //Set mem word size
    DMA1_Channel2->CCR &= ~DMA_CCR_PSIZE; //Set perif word size
    DMA1_Channel2->CCR |= DMA_CCR_MINC; //MemAddr++
    DMA1_Channel2->CCR &= ~DMA_CCR_PINC; //PerifAddr++
    DMA1_Channel2->CCR &= ~DMA_CCR_CIRC; //Auto reload CNDTR
    DMA1_Channel2->CCR |= DMA_CCR_DIR; //Direction
    DMA1_Channel2->CCR |= DMA_CCR_TEIE; //Interrupt transfer error
//    DMA1_Channel2->CCR |= DMA_CCR_HTIE; //Interrupt half transfer
    DMA1_Channel2->CCR |= DMA_CCR_TCIE; //Interrupt transfer complete
    DMA1_Channel2->CCR &= ~DMA_CCR_EN; //Enable DMA CH
}

void DMA1_Ch3_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel3->CPAR = (uint32_t)addr_perif; //Start addr of perif(or memory)
    DMA1_Channel3->CMAR = (uint32_t)addr_buff; //Start addr of memory(or perif)
    DMA1_Channel3->CNDTR = 128; //Count of words to transfer
    DMA1_Channel3->CCR &= ~DMA_CCR_MEM2MEM; //Mem to Mem mode
    DMA1_Channel3->CCR |= DMA_CCR_PL_1; //Set priority
    DMA1_Channel3->CCR &= ~DMA_CCR_MSIZE; //Set mem word size
    DMA1_Channel3->CCR &= ~DMA_CCR_PSIZE; //Set perif word size
    DMA1_Channel3->CCR |= DMA_CCR_MINC; //MemAddr++
    DMA1_Channel3->CCR &= ~DMA_CCR_PINC; //PerifAddr++
    DMA1_Channel3->CCR &= ~DMA_CCR_CIRC; //Auto reload CNDTR
    DMA1_Channel3->CCR &= ~DMA_CCR_DIR; //Direction
    DMA1_Channel3->CCR |= DMA_CCR_TEIE; //Interrupt transfer error
//    DMA1_Channel3->CCR |= DMA_CCR_HTIE; //Interrupt half transfer
    DMA1_Channel3->CCR |= DMA_CCR_TCIE; //Interrupt transfer complete
    DMA1_Channel3->CCR |= DMA_CCR_EN; //Enable DMA CH
}