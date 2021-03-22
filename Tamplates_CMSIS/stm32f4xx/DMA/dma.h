#ifndef LIB_DMA
#define LIB_DMA

#include "stm32f4xx.h"
#include "string.h"

void DMA2_S2_init(volatile void *addr_perif, volatile void *addr_buff);
void DMA2_S7_init(volatile void *addr_perif, volatile void *addr_buff);

#endif  /*LIB_DMA*/