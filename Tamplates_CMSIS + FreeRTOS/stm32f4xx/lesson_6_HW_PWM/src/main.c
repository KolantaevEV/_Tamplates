#include "main.h"

int main(void)
{
    RCC_init();
    GPIO_init();
    USART_init();
    TIM4_init();

    xTaskCreate(vTask_BUTTON_PA0, "BUTTON_PA0", 64, NULL, 1, NULL);
    xTaskCreate(vTask_PWM, "PWM", 64, NULL, 1, NULL);

    vTaskStartScheduler();
    
    while (1)
    {
        GPIOD->BSRR |= GPIO_BSRR_BS14;
    }

}

void vTask_BUTTON_PA0(void *argument) //button with delay on push
{
    while (1)
    {
        vTaskDelay(50);
        if ((GPIOA->IDR & GPIO_IDR_ID0) && !(GPIOD->ODR & GPIO_ODR_OD14)) {
            vTaskDelay(50);
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

}

void GPIO_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//To output, push_pull

    GPIOD->MODER &= ~GPIO_MODER_MODE14;
    GPIOD->MODER |= GPIO_MODER_MODE14_0;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT14;
    GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED14;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD14;

//--------------discret-inputs--------------------
    GPIOA->MODER &= ~GPIO_MODER_MODE0; //input
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT0; //not needed when input
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDER_OSPEEDR0; //not needed when input
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_1; //pull down
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

void TIM4_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

//--------------TIM4-CH1-GPIO-PD12-init-----
    GPIOD->MODER &= ~GPIO_MODER_MODE12;
    GPIOD->MODER |= GPIO_MODER_MODE12_1;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT12;
    GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12;
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPD12;
    GPIOD->AFR[1] |= GPIO_AFRH_AFSEL12_1; // AF7 - TIM4
//--------------TIM4-CH1_config-------------
    TIM4->PSC = 42000 - 1; //42000000/42000 = 1000
    TIM4->ARR = 100; //count to.. 1000/100 = 10 Hz fshim
    TIM4->CCR1 = 0; //koeff zapoln.
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; //PWM mode 1
    TIM4->CCER |= TIM_CCER_CC1E; //enable tim4-ch1
    TIM4->CR1 |= TIM_CR1_CEN; //Enable tim4
}

void vTask_PWM(void *argument)
{
    static uint8_t i = 0;
    while (1)
    {
        if (i <= 100) TIM4->CCR1 = i;
        else if (i <= 200) TIM4->CCR1 = 200 - i;
        else i = 0;
        i++;
        vTaskDelay(10);
    }
}