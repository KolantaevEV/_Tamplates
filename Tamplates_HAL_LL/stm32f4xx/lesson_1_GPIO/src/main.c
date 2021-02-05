#include "main.h"

int main(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    GPIO_init();

    while (1)
    {
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_14);
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_13);
        if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_0)) LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_15);
        else LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_15);
    }
    return 0;
}

void GPIO_init (void)
{
    LL_GPIO_InitTypeDef gpio_struct;
    LL_GPIO_StructInit(&gpio_struct);
    gpio_struct.Pin = LL_GPIO_PIN_14;
    gpio_struct.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpio_struct.Pull = LL_GPIO_PULL_NO;
    gpio_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOD, &gpio_struct);
    gpio_struct.Pin = LL_GPIO_PIN_13;
    LL_GPIO_Init(GPIOD, &gpio_struct);
    gpio_struct.Pin = LL_GPIO_PIN_15;
    LL_GPIO_Init(GPIOD, &gpio_struct);

    gpio_struct.Pin = LL_GPIO_PIN_0;
    gpio_struct.Mode = LL_GPIO_MODE_INPUT;
    gpio_struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpio_struct.Pull = LL_GPIO_PULL_DOWN;
    gpio_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &gpio_struct);
}