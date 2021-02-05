#include "main.h"

int main(void)
{
    RCC_init();
    GPIO_init();
    USART_init();

    xTaskCreate(vTask_LED_12, "Led_12", 64, NULL, 4, NULL);
    xTaskCreate(vTask_LED_13, "Led_13", 64, NULL, 1, NULL);
    xTaskCreate(vTask_LED_15, "Led_15", 64, NULL, 3, NULL);
    xTaskCreate(vTask_BUTTON_PA0, "BUTTON_PA0", 64, NULL, 2, NULL);

    vTaskStartScheduler();
    
    while (1)
    {
        GPIOD->BSRR |= GPIO_BSRR_BS14;
    }

}

void vTask_LED_12(void *argument)
{
    while (1)
    {
        vTaskDelay(50000);
        GPIOD->BSRR = GPIO_BSRR_BS12;
        vTaskDelay(50000);
        GPIOD->BSRR = GPIO_BSRR_BR12;
    }

}

void vTask_LED_13(void *argument)
{
    while (1)
    {
        vTaskDelay(6000);
        GPIOD->BSRR = GPIO_BSRR_BS13;
        vTaskDelay(6000);
        GPIOD->BSRR = GPIO_BSRR_BR13;
    }

}

void vTask_LED_15(void *argument)
{
    uint16_t s = 0;
    uint16_t p = 1000;
    uint8_t flag = 0;
    while (1)
    {
        if (flag == 0) {
            s++;
            if (s == 100) flag = 1;
        }
        else if (flag == 1){
            s--;
            if (s == 0) flag = 0;
        } 
        LED_15_shim(s, p);
    }

}

void LED_15_shim(uint16_t state, uint16_t period) //soft shim
{
    float state_buf = state;
    float period_buff = period;
    float t = period_buff*(state_buf/100);
    GPIOD->BSRR = GPIO_BSRR_BS15;
    vTaskDelay(t);
    GPIOD->BSRR = GPIO_BSRR_BR15;
    vTaskDelay(period_buff - (t));
}

void vTask_BUTTON_PA0(void *argument) //button with delay on push
{
    while (1)
    {
        vTaskDelay(5000);
        if ((GPIOA->IDR & GPIO_IDR_ID0) && !(GPIOD->ODR & GPIO_ODR_OD14)) {
            vTaskDelay(5000);
            if (GPIOA->IDR & GPIO_IDR_ID0) GPIOD->BSRR = GPIO_BSRR_BS14;
            else GPIOD->BSRR = GPIO_BSRR_BR14;
            USART1_Send_Word((uint8_t*)"Hellow_World!!!\r\n", 17);
        }
        else if (!(GPIOA->IDR & GPIO_IDR_ID0)) GPIOD->BSRR = GPIO_BSRR_BR14;
    }
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

void RCC_init(void)
{
    RCC->CR |= RCC_CR_HSEON; //HSE on
    while(!(RCC->CR & RCC_CR_HSERDY));

    FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_6WS;

// Max freq config on stm32f407vgt:
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; //PLL source is HSE clock
    
    RCC->CR &= ~RCC_CR_PLLON; //Disable PLL

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3; //Div 2

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_4;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_8; //Mult 336

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP; //Div 2

    RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_3; //Div 7

    RCC->CFGR &= ~RCC_CFGR_HPRE; //AHB Div 1

    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; //APB 1 Div 4

    RCC->CFGR &= ~RCC_CFGR_PPRE2;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; //APB 2 Div 2

//    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk; //SysTick Div 1

    RCC->CR |= RCC_CR_PLLON; //PLL on
    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL; //Main clock source is PLL
    while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));

// I2S_RCC_init
/*  RCC->CFGR &= ~RCC_CFGR_I2SSRC; //i2s clock input set to PLLI2S
    RCC->PLLI2SCFGR &= ~RCC_PLLI2SCFGR_PLLI2SN;
    RCC->PLLI2SCFGR |= RCC_PLLI2SCFGR_PLLI2SN_6; 
    RCC->PLLI2SCFGR |= RCC_PLLI2SCFGR_PLLI2SN_7; //Mult 192

    RCC->PLLI2SCFGR &= ~RCC_PLLI2SCFGR_PLLI2SR;
    RCC->PLLI2SCFGR |= RCC_PLLI2SCFGR_PLLI2SR_1; //Div 2
    
    RCC->CR |= RCC_CR_PLLI2SON;
    while(!(RCC->CR & RCC_CR_PLLI2SRDY));
*/
}

void GPIO_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//To output, push_pull
    GPIOD->MODER &= ~GPIO_MODER_MODE12; //direction reset
    GPIOD->MODER |= GPIO_MODER_MODE12_0; //direction set
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT12; //open drain or push-pull
    GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR12; //speed
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD12; //pull up-down

    GPIOD->MODER &= ~GPIO_MODER_MODE13;
    GPIOD->MODER |= GPIO_MODER_MODE13_0;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT13;
    GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR13;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD13;

    GPIOD->MODER &= ~GPIO_MODER_MODE14;
    GPIOD->MODER |= GPIO_MODER_MODE14_0;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT14;
    GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR14;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD14;

    GPIOD->MODER &= ~GPIO_MODER_MODE15;
    GPIOD->MODER |= GPIO_MODER_MODE15_0;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT15;
    GPIOD->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR15;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD15;

    GPIOA->MODER &= ~GPIO_MODER_MODE0; //input
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT0; //not needed when input
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0; //not needed when input
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1;
}

void USART_init(void)
{
//--------------RCC_enable----------------------------
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //USART1 on PB 6 and 7
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //enable RCC on USART1
//--------------TX-PA9--------------------------------
    GPIOB->MODER &= ~GPIO_MODER_MODE6; //reset (00 - input)
    GPIOB->MODER |= GPIO_MODER_MODE6_1; //alternative func (10)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT6; //push-pull (reset - 00)
    GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED6; //Max speed (11)
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD6; //(reset - 00 - floating)
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD6_0; //pull_up
    GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_2; // AF7 - USART1TX
//--------------RX-PA10-------------------------------
    GPIOB->MODER &= ~GPIO_MODER_MODE7; //reset (00 - input)
    GPIOB->MODER |= GPIO_MODER_MODE7_1; //alternative func (10)
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT7; //not needed when input
    GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED7; //not needed when input
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD7; //pull up/down (reset - 00 - floating)
    GPIOB->AFR[0] |= GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2; // AF7 - USART1RX
//--------------USART_config--------------------------
    USART1->BRR = 0x222E; //84Mhz 115200baud if over8 = 0
    USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE; //enable rx, tx, uart
    USART1->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void)    //ECHO MODE 
{
    if (USART1->SR & USART_SR_RXNE) //ADD ORE CHECK!!!!
    {
//        USART1->SR &= ~USART_SR_RXNE; //not need, it resets when read usart1->dr
        USART1_Send_byte(USART1->DR);
    }
}