#ifndef TYPEDEF
#define TYPEDEF

typedef enum{
    OFF = 0,
    ON = 1,
    FALSE = 0,
    TRUE = 1,
    END = 2,
    USART_RESPONSE_TIME = 10000U, //ms
    GPIO_RESPONSE_TIME = 500U //ms
} main_const;

typedef enum{
    START,
    TIMER_START,
    RECEIVE,
    TASK,
    TRANSMIT,
    TIMER_STOP
} main_state_const;

typedef enum{
//---------GENERAL_CMD-----------
    TASK_START,
    TASK_ERROR,
    GET_ERROR,
    TASK_IN_PROGRESS,
    TASK_DONE,
    NO_TASK,
    SET_NO_TASK,
    CLEAR_TASK,
    CLEAR_SMS,
//---------TASK_TYPE----------
    AT_CMGS,
    CMTI,
    AT_CMGR,
    AT_CMGDA,
//---------TASK_CMD-----------
    OK,
    CALL_READY,
    POWER_DOWN,
    ENTER_MSG,
    STARTED,
    STOPPED
} task_state_const;

#endif
