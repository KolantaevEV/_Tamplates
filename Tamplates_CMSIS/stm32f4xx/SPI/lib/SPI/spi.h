#ifndef LIB_SPI
#define LIB_SPI

#include "stm32f4xx.h"



void SPI_1_init(void);
void SPI_2_init(void);
void SPI_send_byte(SPI_TypeDef *SPI_x, uint8_t byte);
void SPI_send_word(SPI_TypeDef *SPI_x, uint8_t *word, uint16_t word_size);

#endif  /*LIB_SPI*/