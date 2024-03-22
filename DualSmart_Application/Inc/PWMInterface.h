#ifndef C01E4B76_09B9_4D1B_8049_D071588C5732
#define C01E4B76_09B9_4D1B_8049_D071588C5732

/** @addtogroup EATON_CEAG_Interfaces
 * @{
 */

/** @addtogroup PWM_Interface
 * @{
 */

#include "FunctionPrototypes.h"
#include <stddef.h>

/**
 * @brief
 *
 */
typedef uint16_t (*PWMInterface_ChangeDutyCycle_t)(void* const p_obj, uint8_t ui8_duty_cycle);

/**
 * @brief
 *
 */
typedef uint16_t (*PWMInterface_StopPwm_t)(void* const p_obj);

/**
 * @brief
 *
 */
typedef struct PWMInterface {
    PWMInterface_ChangeDutyCycle_t pf_change_duty_cycle;
    PWMInterface_StopPwm_t pf_stop;
    void* p_pwm_obj;
} PWMInterface_t;

/**
 * @}
 */

/**
 * @}
 */

#endif /* C01E4B76_09B9_4D1B_8049_D071588C5732 */
