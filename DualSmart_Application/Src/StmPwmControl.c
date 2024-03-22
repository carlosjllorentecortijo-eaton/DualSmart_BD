#include "StmPwmControl.h"
#include <assert.h>

/**
 * @brief
 *
 * @param p_this
 * @return
 */
static uint16_t ui16_prv_StmPwmControl_CalculateAndSetPulse(StmPwmPin_t* p_this);

void StmPwmControl_InitPwm(StmPwmPin_t* p_this, TIM_HandleTypeDef* p_pwm_handle, uint32_t ui32_pwm_channel, bool b_coupled_channel) {
    assert(NULL != p_this);
    assert(NULL != p_pwm_handle);

    p_this->b_coupled_channel = b_coupled_channel;
    p_this->p_pwm_handle = p_pwm_handle;
    p_this->ui32_pwm_channel = ui32_pwm_channel;
    p_this->ui16_pwm_pulse = 0;

    p_this->pwm_interface.pf_change_duty_cycle = (PWMInterface_ChangeDutyCycle_t)StmPwmControl_ChangeDutyCycle;
    p_this->pwm_interface.pf_stop = (PWMInterface_StopPwm_t)StmPwmControl_StopPwm;
    p_this->pwm_interface.p_pwm_obj = p_this;

    HAL_TIM_PWM_Start(p_this->p_pwm_handle, p_this->ui32_pwm_channel);
    if (true == b_coupled_channel) {
        HAL_TIMEx_PWMN_Start(p_this->p_pwm_handle, p_this->ui32_pwm_channel);
    }
    StmPwmControl_ChangeDutyCycle(p_this, 50);
}

void StmPwmControl_ChangeDutyCycle(StmPwmPin_t* p_this, uint8_t ui8_duty_cycle) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_pwm_handle);

    p_this->ui8_pwm_duty_cycle = ui8_duty_cycle;
    ui16_prv_StmPwmControl_CalculateAndSetPulse(p_this);
    __HAL_TIM_SET_COMPARE(p_this->p_pwm_handle, p_this->ui32_pwm_channel, p_this->ui16_pwm_pulse);
}

void StmPwmControl_StopPwm(StmPwmPin_t* p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_pwm_handle);

    HAL_TIM_PWM_Stop(p_this->p_pwm_handle, p_this->ui32_pwm_channel);
}

uint16_t ui16_prv_StmPwmControl_CalculateAndSetPulse(StmPwmPin_t* p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_pwm_handle);

    uint8_t ui8_duty_cycle = p_this->ui8_pwm_duty_cycle;
    uint16_t ui16_period = p_this->p_pwm_handle->Init.Period;
    p_this->ui16_pwm_pulse = (uint16_t)((float)ui16_period * ((float)ui8_duty_cycle / 100.0));
    return p_this->ui16_pwm_pulse;
}

PWMInterface_t* StmPwmControl_GetPWMInterface(StmPwmPin_t* p_this) {
    assert(NULL != p_this);

    return &p_this->pwm_interface;
}