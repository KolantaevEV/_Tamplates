#ifndef DMA
#define DMA
#define DMA8_size 128
#define DMA16_size 128
#define DMA32_size 128

#include "stm32f1xx.h"
#include "string.h"

typedef struct {
    uint8_t data[DMA8_size];
    uint16_t size;
} DMA8_buff;

typedef struct {
    uint16_t data[DMA16_size];
    uint16_t size;
} DMA16_buff;

typedef struct {
    uint32_t data[DMA32_size];
    uint16_t size;
} DMA32_buff;

void DMA_init(void);
void DMA_buff_clear(void *buff);

#endif