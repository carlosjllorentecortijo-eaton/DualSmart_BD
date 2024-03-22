/**
 * @file command_fsm.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <stdlib.h>
#include "mem_pool.h"
#include "user_if.h"
#include "command_class.h"
#include "fsm.h"
#include "user_terminal.h"

/* ----------------------------------------------------- DEFINES ---------------------------------------------------- */

/* --------------------------------------------------- FSM STATES --------------------------------------------------- */
enum fsm_states {
    IDLE = 0,
    SHOW_MENU,
    PROCESS_COMMAND
};

/* ------------------------------------------- GUARD FUNCTION DECLARATION ------------------------------------------- */
static int i_always(fsm_t* this);
static int i_check_input_command(fsm_t* this);
static int i_check_command_not_ended(fsm_t* this);
static int i_check_command_ended(fsm_t* this);

/* ----------------------------------------- ACTIVATION FUNCTION DECLARATION ---------------------------------------- */
static void print_menu(fsm_t* this);
static void execute_command(fsm_t* this);
static void change_user_if_state(fsm_t* this);

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
static custom_user_if_fsm_t custom_user_if_fsm;

static fsm_trans_t tt[] = {
    {IDLE,              i_always,                   SHOW_MENU,          print_menu},
    {SHOW_MENU,         i_check_input_command,      PROCESS_COMMAND,    execute_command},
    {PROCESS_COMMAND,   i_check_command_not_ended,  PROCESS_COMMAND,    execute_command},
    {PROCESS_COMMAND,   i_check_command_ended,      IDLE,               change_user_if_state},
    {-1,                NULL,                       -1,                 NULL}
};

/* ------------------------------------------------ PRIVATE FUNCTIONS ----------------------------------------------- */
/* --------------------------------------------------- FSM Guards --------------------------------------------------- */
/**
 * @brief 
 * 
 * @param this 
 * @return int 
 */
static int i_always(fsm_t* this) {
    return 1;
}

/**
 * @brief 
 * 
 * @param this 
 * @return int 
 */
static int i_check_input_command(fsm_t* this) {
    user_input_t* user_input = user_if_get_input();

    if (PARSE_CMD_ANY_CHAR) {
        custom_user_if_fsm.ui8_actual_command = (uint8_t)atoi(user_input->payload);;
        return 1;
    }

    return 0;
}

/**
 * @brief 
 * 
 * @param this 
 * @return int 
 */
static int i_check_command_not_ended(fsm_t* this) {
    return !custom_user_if_fsm.ui8_command_ended;
}

/**
 * @brief 
 * 
 * @param this 
 * @return int 
 */
static int i_check_command_ended(fsm_t* this) {
    return custom_user_if_fsm.ui8_command_ended;
}
/* ------------------------------------------------- FSM Activations ------------------------------------------------ */
/**
 * @brief Activation function that prints the whole command menu.
 * 
 * @param this 
 */
static void print_menu(fsm_t* this) {
    menu_generation();
}

/**
 * @brief Activation function that calls the command selection cb.
 * 
 * @param this 
 */
static void execute_command(fsm_t* this) {
    action_on_selection(custom_user_if_fsm.ui8_actual_command, &custom_user_if_fsm);
}

/**
 * @brief 
 * 
 * @param this 
 */
static void change_user_if_state(fsm_t* this) {
    custom_user_if_fsm.ui8_command_ended = 0;

    user_term_reset_to_main();
}

/* ------------------------------------------------ PUBLIC FUNCTIONS ------------------------------------------------ */

/**
 * @brief Function called when the user presses escape. Clear the possible active flags and resets the FSM.
 * 
 */
void reset_custom_user_if_fsm() {
    custom_user_if_fsm.p_fsm->current_state = IDLE;

    custom_user_if_fsm.ui8_command_ended = 0;
    custom_user_if_fsm.ui8_actual_command = 0;
    if ( custom_user_if_fsm.user_data != NULL ) {
        MEMPOOL_FREE(custom_user_if_fsm.user_data);
    }
}

/**
 * @brief Function called from the main process. Just fires the FSM.
 * 
 */
void user_term_state_custom(user_term_action_t action) {
    fsm_fire(custom_user_if_fsm.p_fsm);

    if ( custom_user_if_fsm.ui8_command_ended ) {
		PRINT("To return to the main menu, press ENTER\n");
	}
}

/**
 * @brief Function called from the main process. Initializes the commands list and initializes the FSM.
 * 
 */
void init_custom_user_if_fsm() {
    custom_user_if_fsm.p_fsm = fsm_new(IDLE, tt, &custom_user_if_fsm);
}
