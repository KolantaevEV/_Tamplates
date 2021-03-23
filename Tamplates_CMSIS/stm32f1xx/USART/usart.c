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
    USART1->BRR = 0x271;    //clk divider
    USART1->CR3 |= USART_CR3_DMAT | USART_CR3_DMAR | USART_CR3_EIE; //enable DMA
    USART1->CR1 |= USART_CR1_M | USART_CR1_PCE; //8bit data + 1bit parity check (even)
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    USART1->CR1 |= USART_CR1_IDLEIE | USART_CR1_PEIE; // interrupts enable
}

void USART3_init(void)
{
//---------------RCC---------------
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//----------------TX---------------
    GPIOB->CRH &= ~GPIO_CRH_CNF10;   //reset CNF
    GPIOB->CRH |= GPIO_CRH_CNF10_1;  //Pin to alt. func. push-pull
    GPIOB->CRH |= GPIO_CRH_MODE10;   //Pin to output max speed (50MHz)
//----------------RX---------------
    GPIOB->CRH &= ~GPIO_CRH_CNF11;   //reset CNF
    GPIOB->CRH |= GPIO_CRH_CNF11_1;  //Pin to input with pull_up
    GPIOB->CRH &= ~GPIO_CRH_MODE11;  //Pin to input
    GPIOB->BSRR = GPIO_BSRR_BS11;   //Set pull_up
//----------------USART_config---------------
    USART3->BRR = 0x138;    //clk divider
    USART3->CR3 |= USART_CR3_DMAT | USART_CR3_DMAR | USART_CR3_EIE; //enable DMA
    USART3->CR1 |= USART_CR1_M | USART_CR1_PCE; //8bit data + 1bit parity check (even)
    USART3->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    USART3->CR1 |= USART_CR1_IDLEIE | USART_CR1_PEIE; // interrupts enable
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
