#include "gpio.h"

void GPIO_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
//------------PC13 to output-------------
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // PC13 to push-pull
    GPIOC->CRH |= GPIO_CRH_MODE13;  // PC13 to output max speed (50MHz)
    GPIOC->BSRR = GPIO_BSRR_BS13;   // SET bit
//---------------PB3 to input----------------
    GPIOB->CRL &= ~GPIO_CRL_CNF7;
	GPIOB->CRL |= GPIO_CRL_CNF7_1;
	GPIOB->ODR &= ~GPIO_ODR_ODR7; 
//    GPIOB->ODR &= ~GPIO_ODR_ODR3;   // pull-down
//------------PB5 to output-------------
    GPIOB->CRL &= ~GPIO_CRL_CNF5;  // PC13 to push-pull
    GPIOB->CRL |= GPIO_CRL_MODE5;  // PC13 to output max speed (50MHz)
    GPIOB->BSRR = GPIO_BSRR_BS5;   // SET bit
//------------PA* to output-------------
    GPIOA->CRH &= ~GPIO_CRH_CNF8;  // PC13 to push-pull
    GPIOA->CRH |= GPIO_CRH_MODE8_0;  // PC13 to output max speed (50MHz)
    GPIOA->BSRR = GPIO_BSRR_BS8;   // SET bit
}
