/**
 * @file CustomUserRxThread.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "CustomUserRxThread.h"
#if !IS_COORD
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_adc.h"
#include "StmPwmControl.h"
#include "PWMInterface.h"
#include "StmAdcControl.h"
#include "ADCInterface.h"
#include "main.h"
#endif

#if !IS_COORD
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
#endif

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
custom_user_rx_data_t custom_user_rx_data;

/* ------------------------------------------------ PRIVATE FUNCTIONS ----------------------------------------------- */
/**
 * @brief Custom User RX thread routine.
 * 
 */
void custom_user_rx_exec() {
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 1;

    /* Initialize wake time and LED to ON */
    xLastWakeTime = xTaskGetTickCount();
    #if !IS_COORD 
    static uint16_t ui16_count = 0;
    static bool ui8_direction_indicator = true;
    PWMInterface_t* led1_pwm_interface = StmPwmControl_GetPWMInterface(&custom_user_rx_data.v_led1_pwm);
    #endif

    /* Infinite loop */
    for(;;) {
        // Wait for the 10 Ms to execute the LED oeprations
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        #if !IS_COORD
        // to get the info that the controller is awake
        if(custom_user_rx_data.b_on_init && (ui16_count % 50) == 0) {
			led1_pwm_interface->pf_change_duty_cycle(&custom_user_rx_data.v_led1_pwm, (uint8_t)(ui16_count/20));
		}

        if(ui8_direction_indicator) {
        	ui16_count++;
        } else if (!ui8_direction_indicator) {
        	ui16_count--;
        }

        if(ui8_direction_indicator && ui16_count >= 2000) {
        	ui8_direction_indicator = false;
		} else if (!ui8_direction_indicator && ui16_count <= 0) {
			ui8_direction_indicator = true;
		}
        #endif
    }
}

/* ------------------------------------------------ PUBLIC FUNCTIONS ------------------------------------------------ */
/**
 * @brief Custom User RX Thread entry point.
 * 
 */
void start_custom_user_rx(){

	custom_user_rx_data.b_on_init = true;

    /* Initialize PWM Objects */
    #if !IS_COORD
    StmPwmControl_InitPwm(&custom_user_rx_data.v_led1_pwm, &htim3, TIM_CHANNEL_3, false);
    StmPwmControl_InitPwm(&custom_user_rx_data.i_led1_pwm, &htim1, TIM_CHANNEL_1, false);
    #endif

    /* Initialize ADC Objects */
	#if !IS_COORD
    StmAdcControl_InitAdcObj(&custom_user_rx_data.hw_revision_adc, 	&hadc1, ADC_CHANNEL_7);
    StmAdcControl_InitAdcObj(&custom_user_rx_data.i_led1_adc,		&hadc1, ADC_CHANNEL_2);
    StmAdcControl_InitAdcObj(&custom_user_rx_data.temp_adc, 		&hadc1, ADC_CHANNEL_TEMPSENSOR);
    StmAdcControl_InitAdcObj(&custom_user_rx_data.v_28v_adc, 		&hadc1, ADC_CHANNEL_0);
    StmAdcControl_InitAdcObj(&custom_user_rx_data.v_led1_adc, 		&hadc1, ADC_CHANNEL_1);
    #endif

    custom_user_rx_exec();
}
