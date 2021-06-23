#include "spi.h"

void SPI_1_init(void)
{
/*===============SLAVE_MODE==============*/
//---------------RCC---------------
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //GPIO RCC
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; //SPI1 RCC
//----------------NSS---------------
    GPIOA->MODER &= ~GPIO_MODER_MODE4; //reset (00 - input)
    GPIOA->MODER |= GPIO_MODER_MODE4_1; //alternative func (10)
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT4; //push-pull (reset - 00)
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED4; //Max speed (11)
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4; //(reset - 00 - floating)
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL4_0 | GPIO_AFRL_AFSEL4_2;
//----------------SCK---------------
    GPIOA->MODER &= ~GPIO_MODER_MODE5; //reset (00 - input)
    GPIOA->MODER |= GPIO_MODER_MODE5_1; //alternative func (10)
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5; //push-pull (reset - 00)
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5; //Max speed (11)
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5; //(reset - 00 - floating)
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2;
//----------------MISO---------------
    GPIOA->MODER &= ~GPIO_MODER_MODE6; //reset (00 - input)
    GPIOA->MODER |= GPIO_MODER_MODE6_1; //alternative func (10)
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT6; //push-pull (reset - 00)
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED6; //Max speed (11)
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD6; //(reset - 00 - floating)
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_2;
//----------------MOSI---------------
    GPIOA->MODER &= ~GPIO_MODER_MODE7; //reset (00 - input)
    GPIOA->MODER |= GPIO_MODER_MODE7_1; //alternative func (10)
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT7; //push-pull (reset - 00)
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED7; //Max speed (11)
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD7; //(reset - 00 - floating)
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_2;
//----------------SPI_config---------------
    SPI1->CR1 &= ~SPI_CR1_DFF;   //8/16 bit data
    SPI1->CR1 &= ~SPI_CR1_CPOL;  //set polarity
    SPI1->CR1 &= ~SPI_CR1_CPHA;  //set phase
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;  //MSB/LSB
    SPI1->CR1 &= ~SPI_CR1_SSM;   //soft NSS
    SPI1->CR1 &= ~SPI_CR1_SSI;   //soft NSS state
    SPI1->CR1 &= ~SPI_CR1_MSTR; //master/slave
    SPI1->CR1 &= ~SPI_CR1_BR;   //baud rate (not in slave)
    SPI1->CR1 &= ~SPI_CR1_CRCEN; //CRC
    SPI1->CR1 &= ~SPI_CR1_CRCNEXT;  //CRC transfer
    SPI1->CR2 &= ~SPI_CR2_SSOE; //hardware NSS type (not in slave)
    SPI1->CR1 |= SPI_CR1_SPE;   //spi enable
}

void SPI_2_init(void)
{
/*===============SLAVE_MODE==============*/
//---------------RCC---------------

//----------------NSS---------------

//----------------SCK---------------

//----------------MISO---------------

//----------------MOSI---------------

//----------------SPI_config---------------
    SPI2->CR1 &= ~SPI_CR1_DFF;   //8/16 bit data
    SPI2->CR1 &= ~SPI_CR1_CPOL;  //set polaryti
    SPI2->CR1 &= ~SPI_CR1_CPHA;  //set phase
    SPI2->CR1 &= ~SPI_CR1_LSBFIRST;  //MSB/LSB
    SPI2->CR1 &= ~SPI_CR1_SSM;   //software NSS
    SPI2->CR1 &= ~SPI_CR1_SSI;   //soft NSS state
    SPI2->CR1 &= ~SPI_CR1_MSTR; //master/slave
    SPI2->CR1 &= ~SPI_CR1_BR;   //baud rate (not in slave)
    SPI2->CR1 &= ~SPI_CR1_CRCEN; //CRC
    SPI2->CR1 &= ~SPI_CR1_CRCNEXT;   //CRC transfer
    SPI2->CR2 &= ~SPI_CR2_SSOE; //hardware NSS type
    SPI2->CR1 |= SPI_CR1_SPE;   //spi enable
}

void SPI_send_byte(SPI_TypeDef *SPI_x, uint8_t byte)
{
    while (!(SPI_x->SR & SPI_SR_TXE));
    SPI_x->DR = byte;
}

void SPI_send_word(SPI_TypeDef *SPI_x, uint8_t *word, uint16_t word_size)
{
    for (uint16_t i = 0; i < word_size; ++i) SPI_send_byte(SPI_x, word[i]);
}