#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void RCC_init(void);
void GPIO_init(void);
void vTask_BUTTON_PA0(void *argument);
void USART_init(void);
void USART1_Send_byte(uint8_t byte);
void USART1_Send_Word(uint8_t *word, uint16_t size);
void TIM4_init(void);
void vTask_PWM(void *argument);