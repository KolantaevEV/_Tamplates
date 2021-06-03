#include "main.h"
/*
volatile xSemaphoreHandle DMA_Ch4_semphr;
volatile xQueueHandle queue_to_DMA;
volatile xTimerHandle th_ADC_convert;
*/
int main(void)
{

//============Add_Timers============
/*    
    th_ADC_convert = xTimerCreate("ADC_convert",
                                pdMS_TO_TICKS(50),
                                pdTRUE,
                                NULL,
                                tc_ADC_convert);
    if (th_ADC_convert == NULL) {GPIOC->BSRR = GPIO_BSRR_BS13; while(1);}
    if (xTimerStart(th_ADC_convert, 0) != pdPASS) {GPIOC->BSRR = GPIO_BSRR_BS13; while(1);}
*/
//============Add_Queue============
/*
    queue_to_DMA = xQueueCreate(5 , sizeof(buff_t));
        if (queue_to_DMA == NULL) {GPIOC->BSRR = GPIO_BSRR_BS13; while(1);}
*/
//============Add_Semaphores========
/*
    DMA_Ch4_semphr = xSemaphoreCreateBinary();
        if (DMA_Ch4_semphr == NULL) {GPIOC->BSRR = GPIO_BSRR_BS13; while(1);}
*/
//============Add_Tasks=============
/*
    xTaskCreate(Task_ADC_to_UART, 
                "ADC_to_UART", 
                configMINIMAL_STACK_SIZE * 2, 
                NULL, 
                4,
                (xTaskHandle *) NULL);
*/

    vTaskStartScheduler();

    while (1)
    {
        //Error check
    }

    return 0;
}
