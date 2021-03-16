#include "gpio.h"

void GPIO_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//------------PD12 to output-------------
    GPIOD->MODER &= ~GPIO_MODER_MODE12;    // reset mode
    GPIOD->MODER |= GPIO_MODER_MODE12_0;   // set mode (Out/Input/AF/Analog)
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT12;     // set OD or Push/Pull
    GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED12; // set Speed
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD12; //set pull up/down
    GPIOD->BSRR = GPIO_BSRR_BS12;  // initial output state
//---------------PA0 to input----------------
    GPIOA->MODER &= ~GPIO_MODER_MODE0; //input
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT0; //not needed when input
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED0; //not needed when input
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;  //reset pull up/down
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1; // pull down
}
