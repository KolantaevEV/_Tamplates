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
    GPIOA->CRH |= GPIO_CRH_CNF10_0;  //Pin to floating input
    GPIOA->CRH &= ~GPIO_CRH_MODE10;   //Pin to output max speed (50MHz)
//----------------USART_config---------------
    USART1->BRR = 0xEA6;    //clk divider, 115200 bod
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    
    USART1->CR1 |= USART_CR1_RXNEIE; // rx interrupt enable
    NVIC_EnableIRQ(USART1_IRQn);
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
    GPIOA->CRL |= GPIO_CRL_CNF3_0;  //Pin to floating input
    GPIOA->CRL &= ~GPIO_CRL_MODE3;  //Pin to input
//----------------USART_config---------------
    USART2->BRR = 0x753;    //clk divider, 115200 bod
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    
    USART2->CR1 |= USART_CR1_RXNEIE; // rx interrupt enable
    NVIC_EnableIRQ(USART2_IRQn);
}

void Rbuff_clear(Rbuff *buff)
{
    buff->head = 0;
    buff->tail = 0;
    buff->cnt = 0;
}

void Rbuff_write(Rbuff *buff, uint8_t data)
{
    if (buff->cnt < (RBUFF_SIZE - 1)) {
        buff->data[buff->tail] = data;
        buff->tail++;
        buff->cnt++;
        if (buff->tail == RBUFF_SIZE) buff->tail = 0;
    }
}

uint8_t Rbuff_read(Rbuff *buff)
{
    uint8_t byte = 0;
    byte = buff->data[buff->head];
    buff->head++;
    buff->cnt--;
    if (buff->head == RBUFF_SIZE) buff->head = 0;

    return byte;
}

void Uword_clear(Uword *word)
{
    memset(word->data, '\0', UWORD_SIZE);
    word->size = 0;
}

void USART1_Send_byte(uint8_t byte)
{
    while(!(USART1->SR & USART_SR_TC));
    USART1->DR = byte;
}

void USART1_Send_Word(uint8_t *word, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++) USART1_Send_byte(word[i]);
}

void USART2_Send_byte(uint8_t byte)
{
    while(!(USART2->SR & USART_SR_TC));
    USART2->DR = byte;
}

void USART2_Send_Word(uint8_t *word, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++) USART1_Send_byte(word[i]);
}