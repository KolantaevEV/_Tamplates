#include "usart.h"

void USART1_init(void)
{
//---------------RCC---------------
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//----------------TX---------------
    GPIOA->CRH &= ~GPIO_CRH_CNF9;   //reset CNF
    GPIOA->CRH |= GPIO_CRH_CNF9_1;  //Pin to alt. func. push-pull
    GPIOA->CRH |= GPIO_CRH_MODE9;   //Pin to output max speed (50MHz)
//----------------RX---------------
    GPIOA->CRH &= ~GPIO_CRH_CNF10;   //reset CNF
    GPIOA->CRH |= GPIO_CRH_CNF10_1;  //Pin to input with pull_up
    GPIOA->CRH &= ~GPIO_CRH_MODE10;   //Pin to input
    GPIOA->BSRR = GPIO_BSRR_BS10;   //Set pull_up
//----------------USART_config---------------
    USART1->BRR = 0xEA6;    //clk divider
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    USART1->CR1 |= USART_CR1_RXNEIE; // rx interrupt enable
}

void USART2_init(void)
{
//---------------RCC---------------
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//----------------TX---------------
    GPIOA->CRL &= ~GPIO_CRL_CNF2;   //reset CNF
    GPIOA->CRL |= GPIO_CRL_CNF2_1;  //Pin to alt. func. push-pull
    GPIOA->CRL |= GPIO_CRL_MODE2;   //Pin to output max speed (50MHz)
//----------------RX---------------
    GPIOA->CRL &= ~GPIO_CRL_CNF3;   //reset CNF
    GPIOA->CRL |= GPIO_CRL_CNF3_1;  //Pin to input with pull_up
    GPIOA->CRL &= ~GPIO_CRL_MODE3;  //Pin to input
    GPIOA->BSRR = GPIO_BSRR_BS3;   //Set pull_up
//----------------USART_config---------------
    USART2->BRR = 0x753;    //clk divider
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    USART2->CR1 |= USART_CR1_RXNEIE; // rx interrupt enable
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
