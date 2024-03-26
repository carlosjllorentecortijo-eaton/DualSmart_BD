/**
 * @file CustomUserRxThread.h
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DF235FC1_3CC4_4C16_8AC3_D76B94D83FC4
#define DF235FC1_3CC4_4C16_8AC3_D76B94D83FC4

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <stdint.h>

/* ----------------------------------------------------- TYPEDEF ---------------------------------------------------- */
typedef struct custom_user_rx_data_s custom_user_rx_data_t;

/* ------------------------------------------------ STRUCT DEFINITION ----------------------------------------------- */
struct custom_user_rx_data_s {
    uint8_t dummy_data;
};

/* ------------------------------------------------ PUBLIC FUNCTIONS ------------------------------------------------ */
void start_custom_user_rx(void *argument);
void change_desired_led_current(uint16_t led_current_ma);

#endif /* DF235FC1_3CC4_4C16_8AC3_D76B94D83FC4 */