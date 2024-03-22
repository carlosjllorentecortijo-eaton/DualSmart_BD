#include "Reset.h"
#include "cmsis_os2.h"

static ResetCause_t g_reset_cause = 0;
static ResetCause_t g_saved_cause = 0;

void Reset_SaveCause(void) {

    if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)) {
        g_saved_cause = RESET_CAUSE_LOW_POWER_RESET;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)) {
        g_saved_cause = RESET_CAUSE_WINDOW_WATCHDOG_RESET;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) {
        g_saved_cause = RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) {
        // This reset is induced by calling the ARM CMSIS
        // `NVIC_SystemReset()` function!
        g_saved_cause = RESET_CAUSE_SOFTWARE_RESET;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PWRRST)) {
        g_saved_cause = RESET_CAUSE_BOR_POR_PDR_RESET;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)) {
        g_saved_cause = RESET_CAUSE_EXTERNAL_RESET_PIN_RESET;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST)) {
        g_saved_cause = RESET_CAUSE_OPTION_BYTE_LOADER_RESET;
    } else {
        g_saved_cause = RESET_CAUSE_UNKNOWN;
    }
    __HAL_RCC_CLEAR_RESET_FLAGS();
}

void Reset_UpdateCause(void) {
    g_reset_cause = g_saved_cause;
}

ResetCause_t Reset_GetCause(void) {
    return g_reset_cause;
}

const char* reset_cause_get_name(ResetCause_t reset_cause) {
    static const char* reset_cause_name = "TBD";

    switch (reset_cause) {
        case RESET_CAUSE_UNKNOWN:
            reset_cause_name = "UNKNOWN_RESET";
            break;
        case RESET_CAUSE_OPTION_BYTE_LOADER_RESET:
            reset_cause_name = "OPTION_BYTE_LOADER_RESET";
            break;
        case RESET_CAUSE_EXTERNAL_RESET_PIN_RESET:
            reset_cause_name = "EXTERNAL_RESET_PIN_RESET";
            break;
        case RESET_CAUSE_BOR_POR_PDR_RESET:
            reset_cause_name = "BOR_POR_PDR_RESET";
            break;
        case RESET_CAUSE_SOFTWARE_RESET:
            reset_cause_name = "SOFTWARE_RESET";
            break;
        case RESET_CAUSE_WINDOW_WATCHDOG_RESET:
            reset_cause_name = "WINDOW_WATCHDOG_RESET";
            break;
        case RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET:
            reset_cause_name = "INDEPENDENT_WATCHDOG_RESET";
            break;
        case RESET_CAUSE_LOW_POWER_RESET:
            reset_cause_name = "LOW_POWER_RESET";
            break;
    }
    return reset_cause_name;
}