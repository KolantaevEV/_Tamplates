#include "fifo.h"

void fifo_clear(fifo *buff)
{
    buff->head = 0;
    buff->tail = 0;
    buff->cnt = 0;
}

void fifo_write(fifo *buff, uint8_t data)
{
    if (buff->cnt < FIFO_SIZE) {
        buff->data[buff->tail] = data;
        buff->tail++;
        buff->cnt++;
        if (buff->tail == FIFO_SIZE) buff->tail = 0;
    }
}

uint8_t fifo_read(fifo *buff)
{
    uint8_t byte = 0;
    byte = buff->data[buff->head];
    buff->head++;
    buff->cnt--;
    if (buff->head == FIFO_SIZE) buff->head = 0;

    return byte;
}