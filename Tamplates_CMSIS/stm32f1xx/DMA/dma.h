#ifndef LIB_DMA
#define LIB_DMA

#include "stm32f1xx.h"
#include "string.h"

void DMA1_Ch2_init(volatile void *addr_perif, volatile void *addr_buff);

#endif  /*LIB_DMA*/