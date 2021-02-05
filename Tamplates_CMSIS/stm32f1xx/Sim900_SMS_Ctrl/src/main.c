#include "main.h"

Rbuff buff_uart_1;
Rbuff buff_uart_2;

int main()
{
    main_state_const state = START;
    main_const GPIO_input = FALSE;
    task_state_const task_state = TASK_DONE;
    Uword word_rcv;
        Uword_clear(&word_rcv);
    Uword word_tr;
        Uword_clear(&word_tr);
    Uword word_msg;
        Uword_clear(&word_msg);

    RCC_init();
    GPIO_init();
    USART1_init();
    USART2_init();
    TIM2_Init();
    TIM3_Init();
    Rbuff_clear(&buff_uart_1);
    Rbuff_clear(&buff_uart_2);

    while (1)
    {
        switch (state)
        {
            case START:
                    Uword_clear(&word_tr);
                    Uword_clear(&word_rcv);
                    Uword_clear(&word_msg);
//                    if (transmit_check((uint8_t*)"AT+CPOWD=1\x0D", 11, (uint8_t*)"Call Ready", 10) == FALSE) break;
//                    if (transmit_check(0, 0, (uint8_t*)"Call Ready", 10) == FALSE) break;
//                    if (transmit_check((uint8_t*)"ATE0\x0D", 5, (uint8_t*)"OK", 2) == FALSE) break;
                    GPIOC->BSRR = GPIO_BSRR_BS13;
                    if (transmit_check((uint8_t*)"AT+CMGF=1\x0D", 10, (uint8_t*)"OK", 2) == FALSE) break;
                    GPIOC->BSRR = GPIO_BSRR_BS13;
                    if (transmit_check((uint8_t*)"AT+CSCS=\"GSM\"\x0D", 14, (uint8_t*)"OK", 2) == FALSE) break;
                    GPIOC->BSRR = GPIO_BSRR_BS13;
                    
                    Rbuff_clear(&buff_uart_1);
                    Rbuff_clear(&buff_uart_2);
                    state = TIMER_START;
                break;

            case TIMER_START:
                    GPIO_input = FALSE;
                    Uword_clear(&word_rcv);
                    TIM2_switch(USART_RESPONSE_TIME, ENABLE);
                    TIM3_switch(GPIO_RESPONSE_TIME, ENABLE);
                    state = RECEIVE;
                break;

            case RECEIVE:
                    if ((GPIOB->IDR & GPIO_IDR_IDR3) && (GPIO_input == FALSE)) {
                        if (!(TIM3->CR1 & TIM_CR1_CEN)) {
                            GPIO_input = TRUE;
                            Uword_clear(&word_tr);
                            memcpy(word_tr.data, (uint8_t*)"AT+CMGS=\"+79111660225\"\x0D", (word_tr.size = 23));
                            Uword_clear(&word_msg);
                            memcpy(word_msg.data, (uint8_t*)"START_Hellow World!!!\x1A", (word_msg.size = 22));
                            state = TASK;
                        }
                    }
                    else if (!(GPIOB->IDR & GPIO_IDR_IDR3) && (GPIO_input == TRUE)) {
                        GPIO_input = FALSE;
                        Uword_clear(&word_tr);
                        memcpy(word_tr.data, (uint8_t*)"AT+CMGS=\"+79111660225\"\x0D", (word_tr.size = 23));
                        Uword_clear(&word_msg);
                        memcpy(word_msg.data, (uint8_t*)"STOP_Hellow World!!!\x1A", (word_msg.size = 21));
                        state = TASK;
                    }
                    else TIM3->CNT = 0;
                    
                    if (buff_uart_1.cnt > 0) {
                        word_rcv.data[word_rcv.size] = Rbuff_read(&buff_uart_1);
                        USART2_Send_byte(word_rcv.data[word_rcv.size]);
                        word_rcv.size++;
                        TIM2->CNT = 0;
                    }
                    else if (!(TIM2->CR1 & TIM_CR1_CEN)) state = TASK;

                break;

            case TASK:

                    TIM2_switch(USART_RESPONSE_TIME, DISABLE);
                    TIM3_switch(GPIO_RESPONSE_TIME, DISABLE);
                    task_state = Task_Handler(&word_rcv, &word_tr, &word_msg);
                    if (task_state == TASK_DONE) {
                        Uword_clear(&word_tr);
                        Uword_clear(&word_msg);
                        state = TIMER_START;
                    }
                    else if (task_state == TASK_ERROR) state = START;
                    else if (task_state == NO_TASK) state = TIMER_START;
                    else state = TRANSMIT;
                break;

            case TRANSMIT:
                    if (word_tr.size > 0) {
                        USART1_Send_Word(word_tr.data, word_tr.size);
                    }
                    state = TIMER_START;

                break;

            default:
                break;
        }
    }
}

main_const transmit_check(uint8_t *data_in, uint16_t data_in_size, uint8_t *data_target, uint16_t data_target_size)
{
    main_const state = FALSE;
    Uword word_rcv;
        Uword_clear(&word_rcv);

    if (data_in_size > 0) USART1_Send_Word(data_in, data_in_size);
    TIM2_switch(USART_RESPONSE_TIME, ENABLE);
    GPIOC->BSRR = GPIO_BSRR_BR13;
    while (TIM2->CR1 & TIM_CR1_CEN)
    {        
        if (buff_uart_1.cnt > 0) {
            word_rcv.data[word_rcv.size] = Rbuff_read(&buff_uart_1);
            USART2_Send_byte(word_rcv.data[word_rcv.size]);
            word_rcv.size++;
            TIM2->CNT = 0;
        }
        else if (WordFind(word_rcv.data, word_rcv.size, data_target, data_target_size) == TRUE) {
            state = TRUE; 
            TIM2_switch(USART_RESPONSE_TIME, DISABLE);            
            break;
        }
    }

    return state;
}

