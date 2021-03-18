#include "dma.h"

void DMA2_S5_init(volatile void *addr_perif, volatile void *addr_buff)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2->
    DMA2_Stream1-> = (uint32_t)addr_perif;
}
