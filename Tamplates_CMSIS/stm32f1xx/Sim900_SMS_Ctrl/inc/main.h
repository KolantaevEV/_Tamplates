#ifndef MAIN
#define MAIN

#include "stm32f1xx.h"
#include "gpio.h"
#include "rcc.h"
#include "sim900.h"
#include "usart.h"
#include "typedefs.h"
#include "string.h"
#include "tim.h"
#include "task_handler.h"
#include "interrupts.h"

main_const transmit_check(uint8_t *data_in, uint16_t data_in_size, uint8_t *data_target, uint16_t data_target_size);

#endif