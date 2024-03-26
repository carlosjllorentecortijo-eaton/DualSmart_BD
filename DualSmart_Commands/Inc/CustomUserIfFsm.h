/**
 * @file CustomUserIfFsm.h
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef B5BEBCD7_5293_4399_9499_7023A767722E
#define B5BEBCD7_5293_4399_9499_7023A767722E

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <Fsm.h>
#include <stdint.h>
#include "user_terminal.h"

/* ----------------------------------------------------- TYPEDEF ---------------------------------------------------- */
typedef struct custom_user_if_fsm_s custom_user_if_fsm_t;

/* ------------------------------------------------ STRUCT DEFINITION ----------------------------------------------- */
struct custom_user_if_fsm_s {
    /* Pointer to actual FSM */
    fsm_t* p_fsm;
    /* Add flags or other useful data */
    uint8_t ui8_command_ended : 1;
    uint8_t ui8_actual_command;
    /* Extra data */
    void* user_data;
};


/* ------------------------------------------------- PUBLIC FUNCTION ------------------------------------------------ */
void reset_custom_user_if_fsm();
void user_term_state_custom(user_term_action_t action);
void init_custom_user_if_fsm();

#endif /* B5BEBCD7_5293_4399_9499_7023A767722E */
