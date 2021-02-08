#include "main.h"

uint16_t timer_TIM2 = 0;
uint16_t timer_TIM3 = 0;
Rbuff buff_uart_1;
Rbuff buff_uart_2;

int main()
{
    main_state_const state = REBOOT;
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
            case REBOOT:
                    timer_restart("TIM_2");
                    GPIOA->BSRR = GPIO_BSRR_BR8;
                    while(timer_TIM2 < 50);
                    GPIOA->BSRR = GPIO_BSRR_BS8;
                    if (transmit_check(0, 0, (uint8_t*)"Call Ready", 10) == FALSE) break;
                    state = START;
                break;

            case START:
                    Uword_clear(&word_tr);
                    Uword_clear(&word_rcv);
                    Uword_clear(&word_msg);
                    if (transmit_check((uint8_t*)"ATE0\x0D", 5, (uint8_t*)"OK", 2) == FALSE) break;
                    if (transmit_check((uint8_t*)"AT+CMGF=1\x0D", 10, (uint8_t*)"OK", 2) == FALSE) break;
                    if (transmit_check((uint8_t*)"AT+CSCS=\"GSM\"\x0D", 14, (uint8_t*)"OK", 2) == FALSE) break;
                    Rbuff_clear(&buff_uart_1);
                    Rbuff_clear(&buff_uart_2);
                    state = TIMER_START;
                break;

            case TIMER_START:
                    Uword_clear(&word_rcv);
                    timer_restart("TIM_2");
                    timer_restart("TIM_3");
                    state = RECEIVE;
                break;

            case RECEIVE:
                    if ((GPIOB->IDR & GPIO_IDR_IDR7) && (GPIO_input == FALSE) && (task_state != TASK_IN_PROGRESS)) {
                        if (timer_TIM3 > GPIO_RESPONSE_TIME) {
                            GPIO_input = TRUE;
                            Uword_clear(&word_tr);
                            memcpy(word_tr.data, (uint8_t*)"AT+CMGS=\"+79111660225\"\x0D", (word_tr.size = 23));
                            Uword_clear(&word_msg);
                            memcpy(word_msg.data, (uint8_t*)"START_Hellow World!!!\x1A", (word_msg.size = 22));
                            state = TRANSMIT;
                            break;
                        }
                    }
                    else if (!(GPIOB->IDR & GPIO_IDR_IDR7) && (GPIO_input == TRUE) && (task_state != TASK_IN_PROGRESS)) {
                        GPIO_input = FALSE;
                        Uword_clear(&word_tr);
                        memcpy(word_tr.data, (uint8_t*)"AT+CMGS=\"+79111660225\"\x0D", (word_tr.size = 23));
                        Uword_clear(&word_msg);
                        memcpy(word_msg.data, (uint8_t*)"STOP_Hellow World!!!\x1A", (word_msg.size = 21));
                        state = TRANSMIT;
                        break;
                    }
                    else timer_restart("TIM_3");
                    
                    if (buff_uart_1.cnt > 0) {
                        word_rcv.data[word_rcv.size] = Rbuff_read(&buff_uart_1);
                        USART2_Send_byte(word_rcv.data[word_rcv.size]);
                        word_rcv.size++;
                        timer_restart("TIM_2");
                    }
                    else if (timer_TIM2 > (USART_RESPONSE_TIME)) state = TASK;
                break;

            case TASK:

                    task_state = Task_Handler(&word_rcv, &word_tr, &word_msg);
                    if (task_state == TASK_DONE) {
                        Uword_clear(&word_tr);
                        Uword_clear(&word_msg);
                        state = TIMER_START;
                    }
                    else if (task_state == TASK_ERROR) state = REBOOT;
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
    Uword word_rcv2;
        Uword_clear(&word_rcv2);

    if (data_in_size > 0) USART1_Send_Word(data_in, data_in_size);
    timer_restart("TIM_2");
    while (timer_TIM2 < START_RESPONSE_TIME)
    {
        if (buff_uart_1.cnt > 0) {
            word_rcv2.data[word_rcv2.size] = Rbuff_read(&buff_uart_1);
            USART2_Send_byte(word_rcv2.data[word_rcv2.size]);
            word_rcv2.size++;
            timer_restart("TIM_2");
        }
        else if (WordFind(word_rcv2.data, word_rcv2.size, data_target, data_target_size) == TRUE) {
            state = TRUE;
            break;
        }
    }

    return state;
}

void timer_restart(char *TIM_x)
{
    if (strcmp(TIM_x, "TIM_2") == 0) {
        TIM2->CNT = 0;
        timer_TIM2 = 0;
    }
    else if (strcmp(TIM_x, "TIM_3") == 0) {
        TIM3->CNT = 0;
        timer_TIM3 = 0;
    }
}

