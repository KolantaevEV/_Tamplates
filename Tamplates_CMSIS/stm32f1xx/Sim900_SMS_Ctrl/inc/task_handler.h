#ifndef TASK_HANDLER
#define TASK_HANDLER

#include <string.h>
#include <stdint.h>
#include "typedefs.h"
#include "usart.h"


main_const WordFind(uint8_t *strmain, uint16_t strmain_size, uint8_t *strfind, uint16_t strfind_size);
task_state_const Task_Handler(Uword *word_rcv, Uword *word_tr, Uword *word_msg);
task_state_const Get_Task_Type(Uword *task);

#endif
