/**
 ******************************************************************************
 * @file    pwm.c
 * @author  E0458337 / E0755809
 * @brief   Header file for the ADC management.
 @verbatim
 @endverbatim
 ******************************************************************************
 */
#include "pwm.h"

/** @brief Duty Cycle Calculation
 *
 * This fucntion is used to calculate the duty cycle based on the current level
 *
 * @param ui16_currentLevel     : Led current level
 * @retval None
 */

uint8_t dutyCycleCalculation(uint16_t ui16_currentLevel)
{
    uint8_t ui8_ledCurrentDutyCyle = 0;

    // 1000mA is max .current and 100 to convert it into percentage.
    return ui8_ledCurrentDutyCyle = (100 / 1000) * ui16_currentLevel;
}

/** @brief Initialize and start PWM
 *
 * This function is used to initialize and start the PWM
 * PWM1 - tim1 -> 20Khz -> PWM_I_LED1
 * PWM2 - tim4 -> 200hz -> PWM_DIM_LED1
 *
 * @retval None
 */
void initializeAndStartLedCurrent1Pwm(void)
{
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

void initializeAndStartLedDimm1Pwm(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

/** @brief Change LED current PWM duty cycle
 *
 * This function is used to change the duty cycle of the LED current PWM.
 *
 * @param ui8_dutyCycle     : duty cycle
 *
 * @retval None
 */
void changeCurrentLevelPwmDutyCycle(uint16_t ui16_dutyCycle)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, ui16_dutyCycle);
}

/** @brief Change LED DIM level PWM duty cycle
 *
 * This function is used to change the duty cycle of the LED DIM level PWM.
 *
 * @param ui8_dutyCycle     : duty cycle
 *
 * @retval None
 */
void changeDimLevelPwmDutyCycle(uint16_t ui16_dutyCycle)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, ui16_dutyCycle);
}

/** @brief Stop LED DIM level PWM
 *
 * This function is used to stop the LED DIM level PWM.
 *
 * @retval None
 */

void stopLedCurrent1Pwm(void)
{
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
}

/** @brief Stop LED DIM level PWM
 *
 * This function is used to stop the LED DIM level PWM.
 *
 * @retval None
 */
void stopLedDimm1Pwm(void)
{
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
}

void initializeAndStartPWM(void)
{
    initializeAndStartLedCurrent1Pwm();
    initializeAndStartLedDimm1Pwm();
}

