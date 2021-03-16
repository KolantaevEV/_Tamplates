#include "usart.h"

void USART_init(void)
{
//--------------RCC_enable----------------------------
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //USART1 on PB6-TX and PB7-RX
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //enable RCC on USART1
//--------------TX-PB6--------------------------------
    GPIOB->MODER &= ~GPIO_MODER_MODE6; //reset (00 - input)
    GPIOB->MODER |= GPIO_MODER_MODE6_1; //alternative func (10)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT6; //push-pull (reset - 00)
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6; //Max speed (11)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6; //(reset - 00 - floating)
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0; //pull_up
    GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_2; // AF7 - USART1TX
//--------------RX-PB7-------------------------------
    GPIOB->MODER &= ~GPIO_MODER_MODE7; //reset (00 - input)
    GPIOB->MODER |= GPIO_MODER_MODE7_1; //alternative func (10)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT7; //not needed when input
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7; //not needed when input
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7; //pull up/down (reset - 00 - floating)
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD7_0; //pull_up
    GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2; // AF7 - USART1RX
//--------------USART_config--------------------------
    USART1->BRR = 0x222E; //84Mhz 115200baud if over8 = 0
    USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE; //enable rx, tx, uart
    USART1->CR1 |= USART_CR1_RXNEIE;
}

void USART_Send_byte(USART_TypeDef *USARTx, uint8_t byte)
{
    while(!(USARTx->SR & USART_SR_TXE));
    USARTx->DR = byte;
}

void USART_Send_Word(USART_TypeDef *USARTx, uint8_t *word, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++) USART_Send_byte(USARTx, word[i]);
}

void Udata_clear(Udata *word)
{
    memset(word->data, '\0', UDATA_SIZE);
    word->size = 0;
}
