/**
 * @file CommandClass.h
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This header file defines the class that rules the behavior of the commands in both coordinator and device side.
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef E8E2567B_EB62_42B9_BD80_08ED4D22C324
#define E8E2567B_EB62_42B9_BD80_08ED4D22C324

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <CustomUserIfFsm.h>
#include <CustomUserRxThread.h>
#include <stdint.h>
#include "user_if.h"

/* ----------------------------------------------------- DEFINES ---------------------------------------------------- */
#define IPV6_MULTICAST_ADDR 	{ 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }
#define NUMBER_COMMANDS               11
/* --------------------------------------------------- COMMAND IDS -------------------------------------------------- */
#define COMMAND_ID_SINGLE_LED_OFF     0xA0
#define COMMAND_ID_SINGLE_LED_DIM1    0xA1
#define COMMAND_ID_SINGLE_LED_DIM2    0xA2
#define COMMAND_ID_SINGLE_LED_DIM3    0xA3
#define COMMAND_ID_SINGLE_LED_DIM4    0xA4
#define COMMAND_ID_SINGLE_LED_ON      0xA5
#define COMMAND_ID_SINGLE_LED_CUSTOM  0xA6
#define COMMAND_ID_ALL_LED_ON         0xA7
#define COMMAND_ID_ALL_LED_OFF        0xA8
#define COMMAND_ID_ALL_LED_CUSTOM     0xA9
#define COMMAND_ID_ALL_LED_TOGGLE     0xAA

/* ----------------------------------------------------- MACROS ----------------------------------------------------- */
#define GET_CMD_DIGIT()			(user_input->payload[0U] - '0')
#define PARSE_CMD_ANY_CHAR          (user_input != NULL)
#define PRINT_BLANK_LINE()     		PRINT_NOTS("\n")

/* ---------------------------------------------------- TYPEDEFS ---------------------------------------------------- */
typedef struct command_class_s command_class_t;

/* ----------------------------------------------- STRUCT DEFINITIONS ----------------------------------------------- */
struct command_class_s {
    char ui8_menu_text[128];
    uint8_t ui8_shown_in_menu;
    uint8_t ui8_menu_number;
    uint8_t ui8_command_id;
    void (*pf_action_on_selection_cb)(custom_user_if_fsm_t* custom_user_if_fsm);
    void (*pf_action_on_rx_cb)(const uint8_t* data);
    void* p_user_data;
};

/* ------------------------------------------------ PUBLIC FUNCTIONS ------------------------------------------------ */
void menu_generation();
void action_on_selection(const uint8_t ui8_user_input, custom_user_if_fsm_t* custom_user_if_fsm);
void action_on_rx(const void* payload);
bool b_is_udp_data_custom(const void* payload);

void init_command_list();
void populate_command_list();


#endif /* E8E2567B_EB62_42B9_BD80_08ED4D22C324 */
