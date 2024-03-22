#ifndef A088CA55_162C_4768_854B_C08FDDA42401
#define A088CA55_162C_4768_854B_C08FDDA42401

/** @addtogroup EATON_CEAG_Modules
 * @{
 */

/** @addtogroup STM32_PWM_Control
 * @{
 */

#include "PWMInterface.h"
#include "tim.h"
#include <stdbool.h>

/**
 * @brief
 *
 */
typedef struct StmPwmPin {
    TIM_HandleTypeDef* p_pwm_handle;
    uint32_t ui32_pwm_channel;
    uint16_t ui16_pwm_pulse;
    uint8_t ui8_pwm_duty_cycle;
    PWMInterface_t pwm_interface;
    bool b_coupled_channel;
} StmPwmPin_t;

/**
 * @brief Initilisation of the pwm object. Expects the pwm handle, the channel and if it a coupled channel (e.g. CH1 and CH1N).
 *
 * @param p_this
 * @param p_pwm_handle
 * @param ui32_pwm_channel
 * @param b_coupled_channel
 */
void StmPwmControl_InitPwm(StmPwmPin_t* p_this, TIM_HandleTypeDef* p_pwm_handle, uint32_t ui32_pwm_channel, bool b_coupled_channel);

/**
 * @brief Changes the duty cycle of the pwm object.
 *
 * @param p_this
 * @param ui8_duty_cycle
 */
void StmPwmControl_ChangeDutyCycle(StmPwmPin_t* p_this, uint8_t ui8_duty_cycle);

/**
 * @brief Stops the pwm object.
 *
 * @param p_this
 */
void StmPwmControl_StopPwm(StmPwmPin_t* p_this);

/**
 * @brief
 *
 */
PWMInterface_t* StmPwmControl_GetPWMInterface(StmPwmPin_t* p_this);

/**
 * @}
 */

/**
 * @}
 */

#endif /* A088CA55_162C_4768_854B_C08FDDA42401 */
