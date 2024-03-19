/**
 * @file command_class.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file implements the class methods and initializes the list of commands.
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include "command_class.h"
#include <stdint.h>

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
extern command_class_t p_command_list[NUMBER_COMMANDS];

/* --------------------------------------------- MENU CREATION FUNCTION --------------------------------------------- */
void menu_generation() {
    PRINT_BLANK_LINE();
    PRINT("<< Custom Commands >>\n\n");
    for (int i = 0; i < NUMBER_COMMANDS; i++){
        PRINT("%u) %s\n", p_command_list[i].ui8_menu_number, p_command_list[i].ui8_menu_text);
    }
}

/* --------------------------------------------- CLASS INTERFACE FUNTION -------------------------------------------- */
/**
 * @brief 
 * 
 * @param ui8_user_input 
 */
void action_on_selection(uint8_t ui8_user_input, custom_user_if_fsm_t custom_user_if_fsm) {
    for (int i = 0; i < NUMBER_COMMANDS; i++){
        if ( p_command_list[i].ui8_menu_number == ui8_user_input ){
            p_command_list[i].pf_action_on_selection_cb(custom_user_if_fsm);
            break;
        }
    }

    PRINT("No command found with user input %u", ui8_user_input);
}

/**
 * @brief 
 * 
 * @param ui8_command_id 
 */
void action_on_rx(uint8_t ui8_command_id) {
    for (int i = 0; i < NUMBER_COMMANDS; i++){
        if ( p_command_list[i].ui8_command_id == ui8_command_id ){
            p_command_list[i].pf_action_on_rx_cb();
            break;
        }
    }

    PRINT("No command found with command id %u", ui8_command_id);
}

/**
 * @brief 
 * 
 */
void init_command_list() {
    populate_command_list();
}
