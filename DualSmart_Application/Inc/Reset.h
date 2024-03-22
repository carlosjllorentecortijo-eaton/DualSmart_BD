#ifndef E53738E9_F152_4E2D_9EFA_F3616A5836AC
#define E53738E9_F152_4E2D_9EFA_F3616A5836AC

#include "stm32g0xx_hal.h"

/// @brief  Possible STM32 system reset causes
typedef enum ResetCause {
    RESET_CAUSE_UNKNOWN = 0,
    RESET_CAUSE_OPTION_BYTE_LOADER_RESET,
    RESET_CAUSE_EXTERNAL_RESET_PIN_RESET,
    RESET_CAUSE_BOR_POR_PDR_RESET,
    RESET_CAUSE_SOFTWARE_RESET,
    RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET,
    RESET_CAUSE_WINDOW_WATCHDOG_RESET,
    RESET_CAUSE_LOW_POWER_RESET,
} ResetCause_t;

/// @brief      Obtain the STM32 system reset cause
/// @param      None
void Reset_SaveCause(void);

/**
 * @brief
 *
 */
void Reset_UpdateCause(void);

/**
 * @brief
 *
 * @param
 * @return
 */
ResetCause_t Reset_GetCause(void);

/// @brief      Obtain the system reset cause as an ASCII-printable name string
///             from a reset cause type
/// @param[in]  reset_cause     The previously-obtained system reset cause
/// @return     A null-terminated ASCII name string describing the system
///             reset cause
const char* Reset_GetCauseName(ResetCause_t reset_cause);

#endif /* E53738E9_F152_4E2D_9EFA_F3616A5836AC */
