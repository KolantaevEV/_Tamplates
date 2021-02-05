#include "gpio.h"

void GPIO_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
//------------PC13 to output-------------
    GPIOC->CRH &= ~(GPIO_CRH_CNF | GPIO_CRH_MODE); //reset CRH
    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // PC13 to push-pull
    GPIOC->CRH |= GPIO_CRH_MODE13;  // PC13 to output max speed (50MHz)
    GPIOC->BSRR = GPIO_BSRR_BS13;   // SET bit
//---------------PB3 to input----------------
    GPIOB->CRL &= ~(GPIO_CRL_CNF | GPIO_CRL_MODE); //reset CRH
    GPIOB->CRL |= GPIO_CRL_CNF3_1;  // PB3 to push-pull
    GPIOB->CRL &= ~GPIO_CRL_MODE3;  // PB3 to input
    GPIOB->ODR &= ~GPIO_ODR_ODR3;   // pull-down
}
