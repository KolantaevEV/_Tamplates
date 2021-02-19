#ifndef FIFO
#define FIFO
#define FIFO_SIZE 128

#include <stdio.h>

typedef struct {
    uint8_t data[FIFO_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t cnt;
} fifo;

void fifo_clear(fifo *buff);
void fifo_write(fifo *buff, uint8_t data);
uint8_t fifo_read(fifo *buff);

#endif