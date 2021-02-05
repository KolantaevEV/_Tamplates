#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

void RCC_init(void);
void GPIO_init(void);
void vTask_LED_12(void *argument);
void vTask_LED_13(void *argument);
void vTask_LED_15(void *argument);
void LED_15_shim(uint16_t state, uint16_t period);
void vTask_BUTTON_PA0(void *argument);
void USART_init(void);
void USART1_Send_byte(uint8_t byte);
void USART1_Send_Word(uint8_t *word, uint16_t size);