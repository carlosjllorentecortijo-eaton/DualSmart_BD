/**
 ******************************************************************************
 * @file    pwm.h
 * @author  E0458337 / E0755809
 * @brief   Header file for the ADC management.
 @verbatim
 @endverbatim
 ******************************************************************************
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "tim.h"

//measured PWM pulse to achieve required current value
#define LED_CURRENT_350MA_LEVEL     1330
#define LED_CURRENT_500MA_LEVEL     1802
#define LED_CURRENT_750MA_LEVEL     2950
#define LED_CURRENT_1000MA_LEVEL    4200
#define DEFAULT_LED_CURRENT_LEVEL   LED_CURRENT_350MA_LEVEL
#define LUMINARE_MAX_CURRENT		950
//PWM pulse to achieve 0-100% duty-cycle
//Note: PWM input for LED driver IC is inverted

#define LED_DIM_LEVEL_0				5000
#define LED_DIM_LEVEL_25			3750
#define LED_DIM_LEVEL_50			2500
#define LED_DIM_LEVEL_75			1250
#define LED_DIM_LEVEL_100			0
#define LED_OFF						LED_DIM_LEVEL_0
#define LED_ON						LED_DIM_LEVEL_100
#define DEFAULT_LED_DIM_LEVEL   	LED_DIM_LEVEL_100

uint8_t dutyCycleCalculation(uint16_t ui16_currentLevel);
void initializeAndStartLedCurrent1Pwm(void);
void initializeAndStartLedDimm1Pwm(void);
void initializeAndStartPWM(void);
void changeCurrentLevelPwmDutyCycle(uint16_t ui8_dutyCycle);
void changeDimLevelPwmDutyCycle(uint16_t ui8_dutyCycle);
void stopLedCurrent1Pwm(void);
void stopLedDimm1Pwm(void);
void initializeAndStartPWM1(void);
void user_led_pwm_setvalue(uint16_t value);
void user_dim_pwm_setvalue(uint16_t value);

#endif /* INC_PWM_H_ */
