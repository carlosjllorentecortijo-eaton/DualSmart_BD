/**
 * @file populate_command_list.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the definition of the commands.
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <stdio.h>
#include "g3_app_boot.h"
#include "user_g3_common.h"
#include "utils.h"
#include "mem_pool.h"
#include "command_class.h"
#include "custom_user_if_fsm.h"

/* ----------------------------------------------------- MACROS ----------------------------------------------------- */
#define ADD_COMMAND(index_, command_)   memcpy(p_command_list[index_].ui8_menu_text, command_.ui8_menu_text, 128); \
                                        p_command_list[index_].ui8_menu_number = command_.ui8_menu_number; \
                                        p_command_list[index_].ui8_command_id = command_.ui8_command_id; \
                                        p_command_list[index_].pf_action_on_selection_cb = command_.pf_action_on_selection_cb; \
                                        p_command_list[index_].pf_action_on_rx_cb = command_.pf_action_on_rx_cb; \
                                        p_command_list[index_].p_user_data = command_.p_user_data;

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
command_class_t p_command_list[NUMBER_COMMANDS];

/* ------------------------------------------- COMMAND FUNCTION DEFINITION ------------------------------------------ */

/* -------------------------------------------------- SINGLE LED ON ------------------------------------------------- */
#if IS_COORD
void single_led_on_on_selection_cb(custom_user_if_fsm_t custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        uint16_t device_count = 0;
        boot_device_t *boot_device;

        PRINT("Connected devices:\n");
        do {
            boot_device = g3_app_boot_get_device_by_index(device_count, boot_state_connected);

            if (boot_device != NULL) {
                ALLOC_DYNAMIC_HEX_STRING(ext_addr_str, boot_device->ext_addr, MAC_ADDR64_SIZE);
                PRINT("\tDevice %s - short address %u\n", ext_addr_str, boot_device->short_addr);
                FREE_DYNAMIC_HEX_STRING(ext_addr_str);

                device_count++;
            }
        } while (boot_device != NULL);

        if ( device_count == 0 ) {
            PRINT("No connected devices\n");
        }

        PRINT_BLANK_LINE();

        step++;
    } else if ( step == 1 ) {
        uint8_t ui8_node_id;
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command = COMMAND_ID_SINGLE_LED_ON;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED ON to node id %u\n", ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, &ui8_command, 1);
            
            step = 0;
            custom_user_if_fsm.ui8_command_ended = 1;
        }
    }
}
#else
void single_led_on_on_selection_cb(){
    ;
}
#endif

void single_led_on_on_rx_cb(){
    ;
}
/* ------------------------------------------------- SINGLE LED OFF ------------------------------------------------- */
void single_led_off_on_selection_cb(custom_user_if_fsm_t custom_user_if_fsm) {
    ;
}

void single_led_off_on_rx_cb(){
    ;
}

/* --------------------------------------------------- ALL LED ON --------------------------------------------------- */
void all_led_on_on_selection_cb(custom_user_if_fsm_t custom_user_if_fsm) {
    ;
}

void all_led_on_on_rx_cb(){
    ;
}

/* --------------------------------------------------- ALL LED OFF -------------------------------------------------- */
void all_led_off_on_selection_cb(custom_user_if_fsm_t custom_user_if_fsm) {
    ;
}

void all_led_off_on_rx_cb(){
    ;
}

/* ------------------------------------------------- PUBLIC FUNTION ------------------------------------------------- */
void populate_command_list() {
    command_class_t command;

    /* Command SINGLE LED ON */
    strcpy(command.ui8_menu_text, "Turn a single LED On");
    command.ui8_menu_number = 1;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_ON;
    command.pf_action_on_selection_cb = single_led_on_on_selection_cb;
    command.pf_action_on_rx_cb = single_led_on_on_rx_cb;
    command.p_user_data = NULL;
    ADD_COMMAND(0, command);

    /* Command SINGLE LED OFF */
    strcpy(command.ui8_menu_text, "Turn a single LED Off");
    command.ui8_menu_number = 2;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_OFF;
    command.pf_action_on_selection_cb = single_led_off_on_selection_cb;
    command.pf_action_on_rx_cb = single_led_off_on_rx_cb;
    command.p_user_data = NULL;
    ADD_COMMAND(1, command);

    /* Command ALL LEDs ON */
    strcpy(command.ui8_menu_text, "Turn all LEDs On");
    command.ui8_menu_number = 3;
    command.ui8_command_id = COMMAND_ID_ALL_LED_ON;
    command.pf_action_on_selection_cb = all_led_on_on_selection_cb;
    command.pf_action_on_rx_cb = single_led_on_on_rx_cb;
    command.p_user_data = NULL;
    ADD_COMMAND(2, command);

    /* Command SINGLE LED OFF */
    strcpy(command.ui8_menu_text, "Turn all LEDs Off");
    command.ui8_menu_number = 4;
    command.ui8_command_id = COMMAND_ID_ALL_LED_OFF;
    command.pf_action_on_selection_cb = all_led_off_on_selection_cb;
    command.pf_action_on_rx_cb = all_led_off_on_rx_cb;
    command.p_user_data = NULL;
    ADD_COMMAND(3, command);
}
