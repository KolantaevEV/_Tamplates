#ifndef INTERRUPTS
#define INTERRUPTS

#include "main.h"

void IRQ_init(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);

#endif
