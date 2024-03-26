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
#include <CustomUserRxThread.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cmsis_os.h"
#if IS_COORD == 0
#include "led_command_process.h"
#include "pwm.h"
#endif

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
static uint16_t ui16_desired_led_current;
static custom_user_rx_data_t custom_user_rx_data;
static osMutexId_t custom_user_rx_mutexHandle;

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
    #if IS_COORD == 0
    static uint16_t ui16_count = 0;
    changeDimLevelPwmDutyCycle( LED_ON);
    #endif

    /* Infinite loop */
    for(;;) {
        // Wait for the 10 Ms to execute the LED oeprations
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        #if IS_COORD == 0
        xSemaphoreTake(custom_user_rx_mutexHandle, portMAX_DELAY );
        currentControlLoop(ui16_desired_led_current);
        xSemaphoreGive(custom_user_rx_mutexHandle);

        // to get the info that the controller is awake
        if(ui16_count++ >= 1000) {
        	HAL_GPIO_TogglePin( DEBUG_LED1_GPIO_Port, DEBUG_LED1_Pin);
            ui16_count = 0;
        }
        #endif
    }
}

/* ------------------------------------------------ PUBLIC FUNCTIONS ------------------------------------------------ */
/**
 * @brief 
 * 
 * @param led_current_ma 
 */
void change_desired_led_current(uint16_t led_current_ma) {
	xSemaphoreTake(custom_user_rx_mutexHandle, portMAX_DELAY );
    ui16_desired_led_current = led_current_ma;
    xSemaphoreGive(custom_user_rx_mutexHandle);
}

/**
 * @brief Custom User RX Thread entry point.
 * 
 */
void start_custom_user_rx(void* custom_user_rx_mutex){
    custom_user_rx_mutexHandle = *((osMutexId_t*)custom_user_rx_mutex);
    custom_user_rx_data.dummy_data = 0;

    custom_user_rx_exec();
}
