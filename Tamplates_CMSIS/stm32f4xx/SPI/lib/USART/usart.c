#include "usart.h"

void USART1_init(void)
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
    USART1->BRR = 0x2D9; //84Mhz 115200baud if over8 = 0
    USART1->CR1 &= ~USART_CR1_OVER8; //Oversampling mode
    USART1->CR1 |= USART_CR1_M; //Word length
    USART1->CR1 &= ~USART_CR1_WAKE;  //Wake up method
    USART1->CR1 |= USART_CR1_PCE;   //Parity control
    USART1->CR1 &= ~USART_CR1_PS;    //Parity type
    USART1->CR1 &= ~USART_CR1_RWU; //Active or mute mode
    USART1->CR1 &= ~USART_CR1_SBK;   //Send break
    USART1->CR3 &= ~USART_CR3_ONEBIT;   //Sample method
    USART1->CR3 &= ~USART_CR3_CTSE; //Enable CTS flow control
    USART1->CR3 &= ~USART_CR3_RTSE; //Enable RTS flow control
    USART1->CR3 |= USART_CR3_DMAT; //Enable DMA TX
    USART1->CR3 |= USART_CR3_DMAR; //Enable DMA RX
    USART1->CR1 |= USART_CR1_PEIE;  //Enable Parity error interrupt
    USART1->CR1 &= ~USART_CR1_TXEIE; //Enable TX empty interrupt
    USART1->CR1 &= ~USART_CR1_TCIE;  //Enable TC interrupt
    USART1->CR1 &= ~USART_CR1_RXNEIE;    //Enable RX data ready to read interrupt
    USART1->CR1 |= USART_CR1_IDLEIE;    //Idle line detected interrupt
    USART1->CR3 &= ~USART_CR3_CTSIE;    //Enable CTS interrupt
    USART1->CR3 |= USART_CR3_EIE;   //Enable Errors interrupt in DMA
    USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE; //enable rx, tx, uart
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
