#include "tim.h"

void TIM2_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 72000 - 1; //36000000/36000 = 1000
    TIM2->ARR = 1000 - 1; //count to.. 1000/1000 = 1 Hz fshim
    TIM2->DIER |= TIM_DIER_UIE; //enable interrupt
    TIM2->CR1 &= ~TIM_CR1_CEN; //Disable tim2
}

void TIM3_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 72000 - 1; //36000000/36000 = 1000
    TIM3->ARR = 1000 - 1; //count to.. 1000/1000 = 1 Hz fshim
    TIM3->DIER |= TIM_DIER_UIE; //enable interrupt
    TIM3->CR1 &= ~TIM_CR1_CEN; //Disable tim2
}

void TIM2_switch(uint16_t time, uint8_t state) //time in ms
{
    if (state == 1) {
        if (!(TIM2->CR1 & TIM_CR1_CEN)) {
            TIM2->CNT = 0;
            TIM2->ARR = time - 1;
            TIM2->CR1 |= TIM_CR1_CEN; //Enable tim2
        }
    }
    else {
        if (TIM2->CR1 & TIM_CR1_CEN) {
            TIM2->CR1 &= ~TIM_CR1_CEN; //Disable tim2
            TIM2->CNT = 0;
        }
    }
}

void TIM3_switch(uint16_t time, uint8_t state) //time in ms
{
    if (state == 1) {
        if (!(TIM3->CR1 & TIM_CR1_CEN)) {
            TIM3->CNT = 0;
            TIM3->ARR = time - 1;
            TIM3->CR1 |= TIM_CR1_CEN; //Enable tim3
        }
    }
    else {
        if (TIM3->CR1 & TIM_CR1_CEN) {
            TIM3->CR1 &= ~TIM_CR1_CEN; //Disable tim3
            TIM3->CNT = 0;
        }
    }
}