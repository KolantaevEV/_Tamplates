#ifndef lib_USART
#define lib_USART
#define UDATA_SIZE 128

#include "stm32f4xx.h"
#include "string.h"

typedef struct {
    uint8_t data[UDATA_SIZE];
    uint16_t size;
} Udata;

void USART1_init(void);
void USART_Send_byte(USART_TypeDef *USARTx, uint8_t byte);
void USART_Send_Word(USART_TypeDef *USARTx, uint8_t *word, uint16_t size);
void Udata_clear(Udata *word);

#endif  /*lib_USART*/