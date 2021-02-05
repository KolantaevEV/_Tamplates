#define buff_size 256

#include "stm32f1xx.h"

typedef struct {
    uint8_t data[buff_size];
    uint8_t head;
    uint8_t tail;
    uint8_t cnt;
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
uint8_t Rbuff_write(ring_buffer *buff, uint8_t data);
uint8_t Rbuff_read(ring_buffer *buff);