#ifndef TIM
#define TIM

#include "stm32f1xx.h"

void TIM2_Init(void);
void TIM2_switch(uint16_t time, uint8_t state);
void TIM3_Init(void);
void TIM3_switch(uint16_t time, uint8_t state);

#endif