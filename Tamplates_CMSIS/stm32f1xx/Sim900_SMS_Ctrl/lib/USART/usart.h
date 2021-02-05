#ifndef USART
#define USART
#define RBUFF_SIZE 128
#define UWORD_SIZE 128


#include "stm32f1xx.h"
#include "string.h"

typedef struct {
    uint8_t data[RBUFF_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t cnt;
} Rbuff;

typedef struct {
    uint8_t data[UWORD_SIZE];
    uint16_t size;
} Uword;

void USART1_init(void);
void USART1_IRQHandler(void);
void USART2_init(void);
void USART2_IRQHandler(void);
void USART1_Send_byte(uint8_t byte);
void USART1_Send_Word(uint8_t *word, uint16_t size);
void USART2_Send_byte(uint8_t byte);
void USART2_Send_Word(uint8_t *word, uint16_t size);
void Rbuff_clear(Rbuff *buff);
void Rbuff_write(Rbuff *buff, uint8_t data);
uint8_t Rbuff_read(Rbuff *buff);
void Uword_clear(Uword *word);

#endif