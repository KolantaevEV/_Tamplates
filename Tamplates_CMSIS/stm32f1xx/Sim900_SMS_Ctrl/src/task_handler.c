#include "task_handler.h"

task_state_const Task_Handler(Uword *word_rcv, Uword *word_tr, Uword *word_msg)
{
    static task_state_const sms_state = CLEAR_SMS;
    task_state_const task_cmd = TASK_START;
    task_state_const task_type = TASK_START;
    task_type = Get_Task_Type(word_tr);
    if (task_type == NO_TASK) task_type = Get_Task_Type(word_rcv);

    while(task_cmd != TASK_IN_PROGRESS && task_cmd != TASK_DONE && task_cmd != TASK_ERROR && task_cmd != NO_TASK)
    {
        switch (task_type)
        {
            case AT_CMGS:
                    switch (task_cmd)
                    {
                        case TASK_START:
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"OK", 2) == TRUE) {task_cmd = OK; break;}
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"\x3E\x20", 2) == TRUE) {task_cmd = ENTER_MSG; break;}
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"ERROR", 5) == TRUE) {task_cmd = GET_ERROR; break;}
                                task_cmd = SET_NO_TASK;
                            break;

                        case OK:
                                task_cmd = TASK_DONE;
                            break;

                        case ENTER_MSG:
                                Uword_clear(word_tr);
                                memcpy(word_tr->data, word_msg->data, (word_tr->size = word_msg->size));
                                task_cmd = TASK_IN_PROGRESS;
                            break;

                        case GET_ERROR:
                                Uword_clear(word_tr);
                                Uword_clear(word_msg);
                                Uword_clear(word_rcv);
                                task_cmd = TASK_ERROR;
                            break;

                        default:                    
                                task_cmd = NO_TASK;
                            break;                        
                    }
                break;

            case CMTI:
                    Uword_clear(word_tr);
                    memcpy(word_tr->data, "AT+CMGR=1\x0D", (word_tr->size = 10));
                    task_cmd = TASK_IN_PROGRESS;
                break;

            case AT_CMGR:
                    switch (task_cmd)
                    {
                        case TASK_START:
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"START", 5) == TRUE) {task_cmd = STARTED; break;}
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"STOP", 4) == TRUE) {task_cmd = STOPPED; break;}
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"ERROR", 5) == TRUE) {task_cmd = GET_ERROR; break;}
                                task_cmd = SET_NO_TASK;
                            break;

                        case STARTED:
                                GPIOC->BSRR = GPIO_BSRR_BR13;
                                GPIOB->BSRR = GPIO_BSRR_BR5;
                                Uword_clear(word_tr);
                                memcpy(word_tr->data, "AT+CMGS=\"+79111660225\"\x0D", (word_tr->size = 23));
                                Uword_clear(word_msg);
                                memcpy(word_msg->data, "STARTED\x1A", (word_msg->size = 8));
                                sms_state = CLEAR_SMS;
                                task_cmd = TASK_IN_PROGRESS;
                            break;

                        case STOPPED:
                                GPIOC->BSRR = GPIO_BSRR_BS13;
                                GPIOB->BSRR = GPIO_BSRR_BS5;
                                Uword_clear(word_tr);
                                memcpy(word_tr->data, "AT+CMGS=\"+79111660225\"\x0D", (word_tr->size = 23));
                                Uword_clear(word_msg);
                                memcpy(word_msg->data, "STOPPED\x1A", (word_msg->size = 8));
                                sms_state = CLEAR_SMS;
                                task_cmd = TASK_IN_PROGRESS;
                            break;

                        case GET_ERROR:
                                Uword_clear(word_tr);
                                Uword_clear(word_msg);
                                Uword_clear(word_rcv);
                                sms_state = CLEAR_SMS;
                                task_cmd = TASK_ERROR;
                            break;
                        
                        default:
                                Uword_clear(word_tr);
                                Uword_clear(word_msg);
                                Uword_clear(word_rcv);
                                sms_state = CLEAR_SMS;
                                task_cmd = NO_TASK;
                            break;
                    }

                break;

            case AT_CMGDA:
                switch (task_cmd)
                    {
                        case TASK_START:
                                if (WordFind(word_rcv->data, word_rcv->size, (uint8_t*)"OK", 2) == TRUE) {task_cmd = OK; break;}
                                task_cmd = SET_NO_TASK;
                            break;

                        case OK:
                                sms_state = NO_TASK;
                                task_cmd = TASK_DONE;
                            break;
                        
                        default:
                                task_cmd = NO_TASK;
                            break;
                    }
                break;

            case NO_TASK:
                    if (sms_state == CLEAR_SMS) {
                        Uword_clear(word_tr);
                        memcpy(word_tr->data, "AT+CMGDA=\"DEL ALL\"\x0D", (word_tr->size = 19));
                        task_cmd = TASK_IN_PROGRESS;
                    }
                    else task_cmd = NO_TASK;
                break;

            default:
                    task_cmd = TASK_ERROR;
                break;
        }
    }

    return task_cmd;
}

main_const WordFind(uint8_t *strmain, uint16_t strmain_size, uint8_t *strfind, uint16_t strfind_size)
{
    main_const state = FALSE;
    for (uint16_t i = 0; (i + strfind_size) <= strmain_size; i++) {
        if (memcmp(strmain + i, strfind, strfind_size) == 0) {
            state = TRUE;
            break;
        }
    }
    return state;
}

task_state_const Get_Task_Type(Uword *task)
{
    task_state_const task_type = NO_TASK;

    if (task->size > 0)
    {
        if (WordFind(task->data, task->size, (uint8_t*)"AT+CMGS", 7) == TRUE) {task_type = AT_CMGS; return task_type;}
        if (WordFind(task->data, task->size, (uint8_t*)"CMTI", 4) == TRUE) {task_type = CMTI; return task_type;}
        if (WordFind(task->data, task->size, (uint8_t*)"AT+CMGR", 7) == TRUE) {task_type = AT_CMGR; return task_type;}
        if (WordFind(task->data, task->size, (uint8_t*)"AT+CMGDA", 7) == TRUE) {task_type = AT_CMGDA; return task_type;}
    }

    return task_type;
}