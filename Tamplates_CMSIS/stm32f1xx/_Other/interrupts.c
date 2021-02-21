#include "interrupts.h"

extern fifo buff_uart_1;
extern fifo buff_uart_2;
extern uint8_t timer_TIM2;
extern uint8_t timer_TIM3;

void IRQ_init(void)
{
    NVIC_SetPriority(TIM2_IRQn, 6);
    NVIC_EnableIRQ(TIM2_IRQn);

    NVIC_SetPriority(TIM3_IRQn, 6);
    NVIC_EnableIRQ(TIM3_IRQn);

    NVIC_SetPriority(USART1_IRQn, 5);
    NVIC_EnableIRQ(USART1_IRQn);
    
    NVIC_SetPriority(USART2_IRQn, 5);
    NVIC_EnableIRQ(USART2_IRQn);
}

void USART1_IRQHandler(void)    //ECHO MODE 
{
    if (USART1->SR & USART_SR_RXNE) //ADD ORE CHECK!!!!
    {
        Rbuff_write(&buff_uart_1, USART1->DR);
    }
}

void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE) //ADD ORE CHECK!!!!
    {
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