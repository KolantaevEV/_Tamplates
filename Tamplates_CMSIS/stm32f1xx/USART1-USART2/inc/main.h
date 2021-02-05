#define buff_size 512

#include "stm32f1xx.h"

typedef struct {
    uint16_t data[buff_size];
    uint16_t head;
    uint16_t tail;
    uint16_t cnt;
} ring_buffer;

void USART1_Send_byte(uint8_t byte);
void USART1_Send_Word(uint8_t *word, uint16_t size);
void USART2_Send_byte(uint8_t byte);
void USART2_Send_Word(uint8_t *word, uint16_t size);
void RCC_init(void);
void GPIO_init(void);
void USART1_init(void);
void USART1_IRQHandler(void);
void USART2_init(void);
void USART2_IRQHandler(void);
void Rbuff_clear(ring_buffer *buff);
void Rbuff_write(ring_buffer *buff, uint8_t data);
uint8_t Rbuff_read(ring_buffer *buff);