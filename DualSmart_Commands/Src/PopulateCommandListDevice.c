/**
 * @file PopulateCommandListDevice.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the definition of the commands.
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#if !IS_COORD 

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <stdio.h>
#include "g3_app_boot.h"
#include "user_g3_common.h"
#include "utils.h"
#include "mem_pool.h"
#include "CommandClass.h"
#include "CustomUserIfFsm.h"
#include "CustomUserRxThread.h"
#include "StmPwmControl.h"

/* ----------------------------------------------------- MACROS ----------------------------------------------------- */
#define ADD_COMMAND(index_, command_)   strncpy(p_command_list[index_].ui8_menu_text, command_.ui8_menu_text, 128); \
                                        p_command_list[index_].ui8_shown_in_menu = command_.ui8_shown_in_menu; \
                                        p_command_list[index_].ui8_menu_number = 0; \
                                        p_command_list[index_].ui8_command_id = command_.ui8_command_id; \
                                        p_command_list[index_].pf_action_on_rx_cb = command_.pf_action_on_rx_cb; \
                                        p_command_list[index_].pf_action_on_rx_cb = command_.pf_action_on_rx_cb; \
                                        p_command_list[index_].p_user_data = command_.p_user_data;

/* ------------------------------------------------ PUBLIC VARIABLES ----------------------------------------------- */
command_class_t p_command_list[NUMBER_COMMANDS];

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
static uint8_t ui8_led_on;

/* ------------------------------------------- COMMAND FUNCTION DEFINITION ------------------------------------------ */

/* -------------------------------------------------- SINGLE LED OFF ------------------------------------------------- */
void single_led_off_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 100);
    ui8_led_on = 0;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- SINGLE LED DIM1 ------------------------------------------------ */
void single_led_dim1_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 75);
    ui8_led_on = 1;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- SINGLE LED DIM2 ------------------------------------------------ */
void single_led_dim2_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 50);
    ui8_led_on = 1;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- SINGLE LED DIM3 ------------------------------------------------ */
void single_led_dim3_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 25);
    ui8_led_on = 1;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- SINGLE LED DIM4 ------------------------------------------------ */
void single_led_dim4_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 0);
    ui8_led_on = 1;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- SINGLE LED ON ------------------------------------------------ */
void single_led_on_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 0);
    ui8_led_on = 1;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- SINGLE LED CUSTOM ------------------------------------------------ */
void single_led_custom_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
    uint8_t ui8_pwm_duty_cycle = data[0];
    PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, (ui8_pwm_duty_cycle / 100));
    if ( ui8_pwm_duty_cycle == 0 ) {
        ui8_led_on = 0;
    } else {
        ui8_led_on = 1;
    }
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- ALL LED ON ------------------------------------------------ */
void all_led_on_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 0);
    ui8_led_on = 1;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- ALL LED OFF ------------------------------------------------ */
void all_led_off_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, 100);
    ui8_led_on = 0;
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- ALL LED CUSTOM ------------------------------------------------ */
void all_led_custom_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
    uint8_t ui8_pwm_duty_cycle = data[0];
    PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, (ui8_pwm_duty_cycle / 100));
    if ( ui8_pwm_duty_cycle == 0 ) {
        ui8_led_on = 0;
    } else {
        ui8_led_on = 1;
    }
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- ALL LED TOGGLE ------------------------------------------------ */
void all_led_toggle_on_rx_cb(const uint8_t* data, custom_user_rx_data_t* custom_user_rx_data) {
	PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data->v_led1_pwm);
	led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data->v_led1_pwm, ui8_led_on ? 100 : 0);
    if ( ui8_led_on == 0 ) {
        ui8_led_on = 1;
    } else {
        ui8_led_on = 0;
    }
    custom_user_rx_data->b_on_init = false;
}

/* ------------------------------------------------- PUBLIC FUNTION ------------------------------------------------- */
void populate_command_list() {
    command_class_t command;

    /* Command SINGLE LED ON */
    strcpy(command.ui8_menu_text, "Turn a single LED Off");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_OFF;
    command.pf_action_on_rx_cb = single_led_off_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(0, command);

    /* Command SINGLE LED DIM1 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM1");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM1;
    command.pf_action_on_rx_cb = single_led_dim1_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(1, command);

    /* Command SINGLE LED DIM2 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM2");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM2;
    command.pf_action_on_rx_cb = single_led_dim2_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(2, command);

    /* Command SINGLE LED DIM3 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM3");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM3;
    command.pf_action_on_rx_cb = single_led_dim3_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(3, command);

    /* Command SINGLE LED DIM4 */
    strcpy(command.ui8_menu_text, "Turn a single LED to DIM4");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_DIM4;
    command.pf_action_on_rx_cb = single_led_dim4_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(4, command);

    /* Command SINGLE LED ON */
    strcpy(command.ui8_menu_text, "Turn a single LED On");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_ON;
    command.pf_action_on_rx_cb = single_led_on_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(5, command);

    /* Command SINGLE LED CUSTOM */
    strcpy(command.ui8_menu_text, "Turn a single LED to a custom level");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_SINGLE_LED_CUSTOM;
    command.pf_action_on_rx_cb = single_led_custom_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(6, command);

    /* Command ALL LEDs ON */
    strcpy(command.ui8_menu_text, "Turn all LEDs On");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_ALL_LED_ON;
    command.pf_action_on_rx_cb = all_led_on_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(7, command);

    /* Command ALL LEDs OFF */
    strcpy(command.ui8_menu_text, "Turn all LEDs Off");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_ALL_LED_OFF;
    command.pf_action_on_rx_cb = all_led_off_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(8, command);

    /* Command ALL LEDs CUSTOM */
    strcpy(command.ui8_menu_text, "Turn all LEDs Custom");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_ALL_LED_CUSTOM;
    command.pf_action_on_rx_cb = all_led_custom_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(9, command);

    /* Command ALL LEDs TOGGLE */
    strcpy(command.ui8_menu_text, "Turn all LEDs Toggle");
    command.ui8_shown_in_menu = 0;
    command.ui8_command_id = COMMAND_ID_ALL_LED_TOGGLE;
    command.pf_action_on_rx_cb = all_led_toggle_on_rx_cb;
    command.pf_action_on_selection_cb= NULL;
    command.p_user_data = NULL;
    ADD_COMMAND(10, command);
}

#endif
