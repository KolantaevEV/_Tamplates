#include "tim.h"

//===================Advanced-control timers (TIM1 and TIM8)=====================
void TIM1_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    RCC->APB1ENR |= RCC_APB2ENR_TIM1EN;
/*
//--------------PE9-CH1_output-------------
    GPIOE->MODER &= ~GPIO_MODER_MODE9;  //reset
    GPIOE->MODER |= GPIO_MODER_MODE9_1; // AF
    GPIOE->OTYPER &= ~GPIO_OTYPER_OT9;  // Push_pull
    GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED9; // very high speed
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD9;  // no pu/pd
    GPIOE->AFR[1] |= GPIO_AFRH_AFSEL9_0; // AF1 - TIM1
*/
//--------------TIM1-CH1_config-------------
    TIM1->PSC = 8400 - 1; //84000000/8400 = 10000
    TIM1->ARR = 1000; //count to.. 10000/1000 = 10 Hz fshim
    TIM1->CCR1 = 0; //koeff zapoln.
    TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //PWM mode 1
    TIM1->CCER |= TIM_CCER_CC1E; //enable ch1
    TIM1->DIER |= TIM_DIER_UIE;  //Update interrupt
    TIM1->CR1 |= TIM_CR1_ARPE;  //Auto preload
    TIM1->CR1 &= ~TIM_CR1_CMS;  //Counter mode
    TIM1->CR1 &= ~TIM_CR1_DIR;  //Counter direction
    TIM1->CR1 |= TIM_CR1_CEN; //Enable
}

//===================General-purpose timers (TIM2 to TIM5 and TIM9 to TIM14)=====================
void TIM2_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
/*
//--------------PA0-CH1_output-------------
    GPIOA->MODER &= ~GPIO_MODER_MODE0;  //reset
    GPIOA->MODER |= GPIO_MODER_MODE0_1; // AF
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT0;  // Push_pull
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED0; // very high speed
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;  // no pu/pd
    GPIOA->AFR[0] |= GPIO_AFRH_AFSEL0_0; // AF1 - TIM1
*/
//--------------TIM2-CH1_config-------------
    TIM2->PSC = 42000 - 1; //42000000/42000 = 1000
    TIM2->ARR = 100; //count to.. 1000/100 = 10 Hz fshim
    TIM2->CCR1 = 0; //koeff zapoln.
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //PWM mode 1
    TIM2->CCER |= TIM_CCER_CC1E; //enable ch1
    TIM2->DIER |= TIM_DIER_UIE;  //Update interrupt
    TIM2->CR1 |= TIM_CR1_ARPE;  //Auto preload
    TIM2->CR1 &= ~TIM_CR1_CMS;  //Counter mode
    TIM2->CR1 &= ~TIM_CR1_DIR;  //Counter direction
    TIM2->CR1 |= TIM_CR1_CEN; //Enable
}

//===================Basic timers (TIM6 and TIM7)==============================
void TIM6_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

//--------------TIM2-CH1_config-------------
    TIM1->PSC = 42000 - 1; //42000000/42000 = 1000
    TIM1->ARR = 100; //count to.. 1000/100 = 10 Hz fshim
    TIM1->DIER |= TIM_DIER_UIE;  //Update interrupt
    TIM1->CR1 |= TIM_CR1_ARPE;  //Auto preload
    TIM1->CR1 |= TIM_CR1_CEN; //Enable tim4
}
