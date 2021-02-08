#include "tim.h"

void TIM2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 7200 - 1;
    TIM2->ARR = 1000 - 1;
    TIM2->DIER |= TIM_DIER_UIE; //enable interrupt
    TIM2->CR1 |= TIM_CR1_CEN; //Enable tim2
    NVIC_EnableIRQ(TIM2_IRQn); //add interrupt
}

void TIM3_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = 7200 - 1;
    TIM3->ARR = 1000 - 1;
    TIM3->DIER |= TIM_DIER_UIE; //enable interrupt
    TIM3->CR1 |= TIM_CR1_CEN; //Enable tim2
    NVIC_EnableIRQ(TIM3_IRQn); //add interrupt
}
