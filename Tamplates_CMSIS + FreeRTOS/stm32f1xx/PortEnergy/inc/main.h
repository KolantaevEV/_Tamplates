#ifndef INC_MAIN
#define INC_MAIN

/*=========C_std_lib==========*/
#include <stdint.h>
#include <string.h>
#include <stdio.h>
/*=========CMSIS===========*/
#include "stm32f1xx.h"
/*=========HAL_LL===========*/

/*=========FreeRTOS===========*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
/*========User_Libs==========*/
#include "adc.h"
#include "can.h"
#include "dma.h"
#include "gpio.h"
#include "rcc.h"
#include "usart_ll.h"
/*========Other=============*/
#include "typedefs.h"
#include "interrupts.h"
#include "hook.h"

void Task_ADC_to_UART(void *pvParameters);
void Task_UART_to_CAN(void *pvParameters);
void Task_CAN_to_UART(void *pvParameters);
void tc_ADC_convert(xTimerHandle pxTimer);
void Task_DMA_to_UART(void *pvParameters);

#endif  /*INC_MAIN*/