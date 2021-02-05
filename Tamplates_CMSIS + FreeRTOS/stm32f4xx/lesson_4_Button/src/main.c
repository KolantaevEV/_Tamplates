#include "main.h"

int main(void)
{
    RCC_init();
    GPIO_init();

    xTaskCreate(vTask_LED_12, "Led_12", 64, NULL, 4, NULL);
    xTaskCreate(vTask_LED_13, "Led_13", 64, NULL, 2, NULL);
    xTaskCreate(vTask_LED_15, "Led_15", 64, NULL, 3, NULL);
    xTaskCreate(vTask_BUTTON_PA0, "BUTTON_PA0", 64, NULL, 1, NULL);

    vTaskStartScheduler();
    
    while (1)
    {
        GPIOD->BSRR |= GPIO_BSRR_BS14;
    }

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
            vTaskDelay(100000);
            if (GPIOA->IDR & GPIO_IDR_ID0) GPIOD->BSRR = GPIO_BSRR_BS14;
            else GPIOD->BSRR = GPIO_BSRR_BR14;
        }
        else if (!(GPIOA->IDR & GPIO_IDR_ID0)) GPIOD->BSRR = GPIO_BSRR_BR14;
    }
}