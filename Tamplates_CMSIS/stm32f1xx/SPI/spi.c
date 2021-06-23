#include "spi.h"

void SPI_1_init(void)
{
/*===============MASTER_MODE==============*/
//---------------RCC---------------
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//----------------NSS---------------
    GPIOA->CRL &= ~GPIO_CRL_CNF4;   //reset CNF
    GPIOA->CRL |= GPIO_CRL_CNF4_1;  //Pin to alt. func. push-pull
    GPIOA->CRL |= GPIO_CRL_MODE4;   //Pin to output max speed (50MHz)
//----------------SCK---------------
    GPIOA->CRL &= ~GPIO_CRL_CNF5;   //reset CNF
    GPIOA->CRL |= GPIO_CRL_CNF5_1;  //Pin to AF with push/pull
    GPIOA->CRL |= GPIO_CRL_MODE5;  //Max speed
//----------------MISO---------------
    GPIOA->CRL &= ~GPIO_CRL_CNF6;   //reset CNF
    GPIOA->CRL |= GPIO_CRL_CNF6_0;  //Pin to input with pull_up
    GPIOA->CRL &= ~GPIO_CRL_MODE6;  //Pin to input
    GPIOA->BSRR = GPIO_BSRR_BS6;   //Set pull_up
//----------------MOSI---------------
    GPIOA->CRL &= ~GPIO_CRL_CNF7;   //reset CNF
    GPIOA->CRL |= GPIO_CRL_CNF7_1;  //Pin to AF with push/pull
    GPIOA->CRL |= GPIO_CRL_MODE7;  //Max speed
//----------------SPI_config---------------
    SPI1->CR1 &= ~SPI_CR1_DFF;   //8/16 bit data
    SPI1->CR1 &= ~SPI_CR1_CPOL;  //set polaryti
    SPI1->CR1 &= ~SPI_CR1_CPHA;  //set phase
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;  //MSB/LSB
    SPI1->CR1 &= ~SPI_CR1_SSM;   //software NSS
    SPI1->CR1 &= ~SPI_CR1_SSI;   //soft NSS state
    SPI1->CR1 |= SPI_CR1_MSTR; //master/slave
    SPI1->CR1 |= SPI_CR1_BR;   //baud rate (not in slave)
    SPI1->CR1 &= ~SPI_CR1_CRCEN; //CRC
    SPI1->CR1 &= ~SPI_CR1_CRCNEXT;   //CRC transfer
    SPI1->CR2 |= SPI_CR2_SSOE; //hardware NSS: type = disable
    SPI1->CR1 |= SPI_CR1_SPE;   //spi enable
}

void SPI_2_init(void)
{
/*===============SLAVE_MODE==============*/
//---------------RCC---------------
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
//----------------NSS---------------
    GPIOB->CRH &= ~GPIO_CRH_CNF12;   //reset CNF
//    GPIOB->CRH |= GPIO_CRH_CNF12_1;  //Pin to input up/down
    GPIOB->CRH |= GPIO_CRH_CNF12_0;  //Pin to input floating
    GPIOB->CRH &= ~GPIO_CRH_MODE12;   //Pin to input
//    GPIOB->BSRR = GPIO_BSRR_BS12;   //Set pull_up
//----------------SCK---------------
    GPIOB->CRH &= ~GPIO_CRH_CNF13;   //reset CNF
    GPIOB->CRH |= GPIO_CRH_CNF13_0;  //Pin to floating input
    GPIOB->CRH &= ~GPIO_CRH_MODE13;   //Pin to input
//----------------MISO---------------
    GPIOB->CRH &= ~GPIO_CRH_CNF14;   //reset CNF
    GPIOB->CRH |= GPIO_CRH_CNF14_1;  //Pin to AF with push/pull
    GPIOB->CRH |= GPIO_CRH_MODE14;  //Max speed
//----------------MOSI---------------
    GPIOB->CRH &= ~GPIO_CRH_CNF15;   //reset CNF
    GPIOB->CRH |= GPIO_CRH_CNF15_0;  //Pin to floating input
    GPIOB->CRH &= ~GPIO_CRH_MODE15;   //Pin to input
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