#include "interrupts.h"

extern Rbuff buff_uart_1;
extern Rbuff buff_uart_2;
extern uint8_t timer_TIM2;
extern uint8_t timer_TIM3;

void USART1_IRQHandler(void)    //ECHO MODE 
{
    if (USART1->SR & USART_SR_RXNE) //ADD ORE CHECK!!!!
    {
//        USART1->SR &= ~USART_SR_RXNE; //not need, it resets when read usart1->dr
        Rbuff_write(&buff_uart_1, USART1->DR);
    }
}

void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE) //ADD ORE CHECK!!!!
    {
//      USART1->SR &= ~USART_SR_RXNE; //not need, it resets when read usart1->dr
        Rbuff_write(&buff_uart_2, USART2->DR);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR = ~TIM_SR_UIF;
        if (timer_TIM2 < 3000) timer_TIM2++;
        else timer_TIM2 = 0;
    }
}

void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF) {
        TIM3->SR = ~TIM_SR_UIF;
        if (timer_TIM3 < 3000) timer_TIM3++;
        else timer_TIM3 = 0;
    }
}