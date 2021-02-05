#include "main.h"

ring_buffer buff_uart1;
ring_buffer buff_uart2;

int main()
{
    RCC_init();
    GPIO_init();
    GPIOC->BSRR = GPIO_BSRR_BS13;
    USART1_init();
    USART2_init();

    Rbuff_clear(&buff_uart1);
    Rbuff_clear(&buff_uart2);

    while (1)
    {
        if (buff_uart1.cnt > 0) USART2_Send_byte(Rbuff_read(&buff_uart1));
        if (buff_uart2.cnt > 0) USART1_Send_byte(Rbuff_read(&buff_uart2));
    }
}

void Rbuff_clear(ring_buffer *buff)
{
    buff->head = 0;
    buff->tail = 0;
    buff->cnt = 0;
}

void Rbuff_write(ring_buffer *buff, uint8_t data)
{
    if (buff->cnt < buff_size) {
        buff->data[buff->tail] = data;
        buff->tail++;
        buff->cnt++;
        if (buff->tail == buff_size) buff->tail = 0;
    }
}

uint8_t Rbuff_read(ring_buffer *buff)
{
    uint8_t byte = 0;
    byte = buff->data[buff->head];
    buff->head++;
    buff->cnt--;
    if (buff->head == buff_size) buff->head = 0;

    return byte;
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


//**********************Inits************************

void RCC_init(void)
{
//----------Config for max clocks without USB and ADC----------------------
    FLASH->ACR |= FLASH_ACR_LATENCY_1;  //FLASH latency = 2 (because 48 - 72MHz)

    RCC->CR |= RCC_CR_HSEON;    //HSE ON
    while (!(RCC->CR & RCC_CR_HSERDY)); //HSE is READY?

    RCC->CFGR |= RCC_CFGR_PLLMULL9; //PLL prescaler
    RCC->CFGR |= RCC_CFGR_PLLSRC;   //PLL sourse = HSE
    RCC->CR |= RCC_CR_PLLON;    //PLL enable
    while (!(RCC->CR & RCC_CR_PLLRDY)); //PLL is READY?

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; //AHB divider
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; //APB1 divider
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; //APB2 divider

    RCC->CFGR |= RCC_CFGR_SW_PLL; // Switch to PLL
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)); //is switched to PLL?

    RCC->CR &= ~RCC_CR_HSION; //HSI OFF if needed....(for energy saving)
}

void GPIO_init(void)
{
//------------example for PC13 to output-------------
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    GPIOC->CRH &= ~(GPIO_CRH_CNF  | GPIO_CRH_MODE); //reset CRH

    GPIOC->CRH &= ~GPIO_CRH_CNF13;  // PC13 to push-pull
    GPIOC->CRH |= GPIO_CRH_MODE13;  // PC13 to output max speed (50MHz)
}

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
    USART1->BRR = 0xEA6;    //clk divider
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    USART1->CR1 |= USART_CR1_RXNEIE; // rx interrupt enable
    NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)    
{
    Rbuff_write(&buff_uart1, USART1->DR);
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
    USART2->BRR = 0x3A98;    //clk divider
    USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE; //enable rx, tx, uart
    USART2->CR1 |= USART_CR1_RXNEIE; // rx interrupt enable
    NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_IRQHandler(void)
{
        Rbuff_write(&buff_uart2, USART2->DR);
}