#ifndef CUSTOM_USER_RX_THREAD
#define CUSTOM_USER_RX_THREAD

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

#endif /* CUSTOM_USER_RX_THREAD */
