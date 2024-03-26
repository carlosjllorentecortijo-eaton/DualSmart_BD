/**
 * @file PopulateCommandListCoord.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the definition of the commands.
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#if IS_COORD

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <stdio.h>
#include "g3_app_boot.h"
#include "user_g3_common.h"
#include "utils.h"
#include "mem_pool.h"
#include <CommandClass.h>
#include <CustomUserIfFsm.h>

/* ----------------------------------------------------- MACROS ----------------------------------------------------- */
#define ADD_COMMAND(index_, command_)   strncpy(p_command_list[index_].ui8_menu_text, command_.ui8_menu_text, 128); \
                                        p_command_list[index_].ui8_shown_in_menu = command_.ui8_shown_in_menu; \
                                        p_command_list[index_].ui8_menu_number = command_.ui8_menu_number; \
                                        p_command_list[index_].ui8_command_id = command_.ui8_command_id; \
                                        p_command_list[index_].pf_action_on_selection_cb = command_.pf_action_on_selection_cb; \
                                        p_command_list[index_].pf_action_on_rx_cb = command_.pf_action_on_rx_cb; \
                                        p_command_list[index_].p_user_data = command_.p_user_data;

/* ------------------------------------------------ PUBLIC VARIABLES ----------------------------------------------- */
command_class_t p_command_list[NUMBER_COMMANDS];

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
static uint8_t broadcast_arr[IP_IPV6_ADDR128_UINT8_LEN] = IPV6_MULTICAST_ADDR;

/* ----------------------------------------------- AUXILIAR FUNCTIONS ----------------------------------------------- */
/**
 * @brief Function that prints the connected devices.
 * 
 */
static void print_connected_devices() {
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
}

/**
 * @brief 
 * 
 */
static void print_brightness_menu() {
    PRINT("Input PWM Duty Cycle to be sent (0-100) (ONLY UNSIGNED INTEGERS):\n");
    PRINT_BLANK_LINE();
}

/* ------------------------------------------- COMMAND FUNCTION DEFINITION ------------------------------------------ */

/* -------------------------------------------------- SINGLE LED OFF ------------------------------------------------- */
void single_led_off_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
        step++;
    } else if ( step == 1 ) {
        uint8_t ui8_node_id;
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command = COMMAND_ID_SINGLE_LED_OFF;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED OFF to node id %u\n", ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, &ui8_command, 1);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- SINGLE LED DIM1 ------------------------------------------------ */
void single_led_dim1_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
        step++;
    } else if ( step == 1 ) {
        uint8_t ui8_node_id;
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command = COMMAND_ID_SINGLE_LED_DIM1;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED DIM1 to node id %u\n", ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, &ui8_command, 1);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- SINGLE LED DIM2 ------------------------------------------------ */
void single_led_dim2_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
        step++;
    } else if ( step == 1 ) {
        uint8_t ui8_node_id;
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command = COMMAND_ID_SINGLE_LED_DIM2;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED DIM2 to node id %u\n", ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, &ui8_command, 1);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- SINGLE LED DIM3 ------------------------------------------------ */
void single_led_dim3_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
        step++;
    } else if ( step == 1 ) {
        uint8_t ui8_node_id;
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command = COMMAND_ID_SINGLE_LED_DIM3;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED DIM3 to node id %u\n", ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, &ui8_command, 1);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- SINGLE LED DIM4 ------------------------------------------------ */
void single_led_dim4_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
        step++;
    } else if ( step == 1 ) {
        uint8_t ui8_node_id;
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command = COMMAND_ID_SINGLE_LED_DIM4;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED DIM4 to node id %u\n", ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, &ui8_command, 1);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- SINGLE LED ON ------------------------------------------------ */
void single_led_on_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;

    /* 0) Print menu for selecting luminaire */
    /* 1) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
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
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- SINGLE LED CUSTOM ------------------------------------------------ */
void single_led_custom_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;
    static uint8_t ui8_node_id;

    /* 0) Print menu for selecting luminaire */
    /* 1) Print menu for selecting brightness*/
    /* 2) Send to selected luminaire and reset step */

    if ( step == 0) {
        print_connected_devices();
        step++;
    } else if ( step == 1 ) {
        user_input_t* user_input = user_if_get_input();

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_node_id = (uint8_t)atoi(user_input->payload);
            print_brightness_menu();
            step++;
        }
    } else if ( step == 2 ) {
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command[2];
        ui8_command[0] = COMMAND_ID_SINGLE_LED_CUSTOM;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_command[1] = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED CUSTOM with PWM Duty Cycle %u to node id %u\n", ui8_command[1], ui8_node_id);
            UserG3_SendUdpDataToShortAddress(0, ui8_node_id, ui8_command, 2);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- ALL LED ON ------------------------------------------------ */
void all_led_on_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    uint8_t ui8_command = COMMAND_ID_ALL_LED_ON;
    ip6_addr_t dst_ip_addr;

    PRINT("Sending LED ON to all nodes\n");
    memcpy(dst_ip_addr.u8, broadcast_arr, IP_IPV6_ADDR128_UINT8_LEN);
    UserG3_SendUdpData(0, dst_ip_addr, &ui8_command, 1);
    
    custom_user_if_fsm->ui8_command_ended = 1;
}

/* ------------------------------------------------- ALL LED OFF ------------------------------------------------ */
void all_led_off_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    uint8_t ui8_command = COMMAND_ID_ALL_LED_OFF;
    ip6_addr_t dst_ip_addr;

    PRINT("Sending LED OFF to all nodes\n");
    memcpy(dst_ip_addr.u8, broadcast_arr, IP_IPV6_ADDR128_UINT8_LEN);
    UserG3_SendUdpData(0, dst_ip_addr, &ui8_command, 1);
    
    custom_user_if_fsm->ui8_command_ended = 1;
}

/* ------------------------------------------------- ALL LED CUSTOM ------------------------------------------------ */
void all_led_custom_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    static int step = 0;
    ip6_addr_t dst_ip_addr;

    /* 0) Print menu for selecting brightness*/
    /* 1) Send and reset step */

    if ( step == 0) {
        print_brightness_menu();
        step++;
    } else if ( step == 1 ) {
        user_input_t* user_input = user_if_get_input();
        uint8_t ui8_command[2];
        ui8_command[0] = COMMAND_ID_ALL_LED_CUSTOM;

        if (PARSE_CMD_ANY_CHAR) {
        	ui8_command[1] = (uint8_t)atoi(user_input->payload);
            PRINT("Sending LED CUSTOM with PWM Duty Cycle %u to all nodes\n", ui8_command[1]);
            memcpy(dst_ip_addr.u8, broadcast_arr, IP_IPV6_ADDR128_UINT8_LEN);
            UserG3_SendUdpData(0, dst_ip_addr, &ui8_command, 2);
            
            step = 0;
            custom_user_if_fsm->ui8_command_ended = 1;
        }
    }
}

/* ------------------------------------------------- ALL LED TOGGLE ------------------------------------------------ */
void all_led_toggle_on_selection_cb(custom_user_if_fsm_t* custom_user_if_fsm) {
    uint8_t ui8_command = COMMAND_ID_ALL_LED_TOGGLE;
    ip6_addr_t dst_ip_addr;

    PRINT("Sending LED TOGGLE to all nodes\n");
    memcpy(dst_ip_addr.u8, broadcast_arr, IP_IPV6_ADDR128_UINT8_LEN);
    UserG3_SendUdpData(0, dst_ip_addr, &ui8_command, 1);
    
    custom_user_if_fsm->ui8_command_ended = 1;
}

/* ------------------------------------------------- PUBLIC FUNTION ------------------------------------------------- */
void populate_command_list() {
    command_class_t command;

    /* Command SINGLE LED ON */
    strcpy(command.ui8_menu_text, "Turn a single LED Off");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 1;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_OFF;
    command.pf_action_on_selection_cb = single_led_off_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(0, command);

    /* Command SINGLE LED DIM1 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM1");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 2;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM1;
    command.pf_action_on_selection_cb = single_led_dim1_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(1, command);

    /* Command SINGLE LED DIM2 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM2");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 3;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM2;
    command.pf_action_on_selection_cb = single_led_dim2_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(2, command);

    /* Command SINGLE LED DIM3 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM3");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 4;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM3;
    command.pf_action_on_selection_cb = single_led_dim3_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(3, command);

    /* Command SINGLE LED DIM4 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM4");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 5;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM4;
    command.pf_action_on_selection_cb = single_led_dim4_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(4, command);

    /* Command SINGLE LED ON */
    strcpy(command.ui8_menu_text, "Turn a single LED On");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 6;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_ON;
    command.pf_action_on_selection_cb = single_led_on_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(5, command);

    /* Command SINGLE LED CUSTOM */
    strcpy(command.ui8_menu_text, "Turn a single LED to a custom level");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 7;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_CUSTOM;
    command.pf_action_on_selection_cb = single_led_custom_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(6, command);

    /* Command ALL LEDs ON */
    strcpy(command.ui8_menu_text, "Turn all LEDs On");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 8;
    command.ui8_command_id = COMMAND_ID_ALL_LED_ON;
    command.pf_action_on_selection_cb = all_led_on_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(7, command);

    /* Command ALL LEDs OFF */
    strcpy(command.ui8_menu_text, "Turn all LEDs Off");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 9;
    command.ui8_command_id = COMMAND_ID_ALL_LED_OFF;
    command.pf_action_on_selection_cb = all_led_off_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(8, command);

    /* Command ALL LEDs CUSTOM */
    strcpy(command.ui8_menu_text, "Turn all LEDs Custom");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 10;
    command.ui8_command_id = COMMAND_ID_ALL_LED_CUSTOM;
    command.pf_action_on_selection_cb = all_led_custom_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(9, command);

    /* Command ALL LEDs TOGGLE */
    strcpy(command.ui8_menu_text, "Turn all LEDs Toggle");
    command.ui8_shown_in_menu = 1;
    command.ui8_menu_number = 11;
    command.ui8_command_id = COMMAND_ID_ALL_LED_TOGGLE;
    command.pf_action_on_selection_cb = all_led_toggle_on_selection_cb;
    command.pf_action_on_rx_cb = NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(10, command);
}

#endif
