/**
 ******************************************************************************
 * @file    adc_sampling.h
 * @author  E0458337 / E0755809
 * @brief   Header file for the ADC management.
 @verbatim
 @endverbatim

 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

#include "adc.h"
#include <string.h>
#include <stdbool.h>

#ifndef INC_ADC_SAMPLING_H_
#define INC_ADC_SAMPLING_H_

#define REF_28V_ADC_CHANNEL              0
#define LED_VOLTAGE_ADC_CHANNEL          1
#define LED_CURRENT_ADC_CHANNEL          2
#define HARDWARE_REVISION_ADC_CHANNEL    3
#define INTERNAL_TEMPERATURE_ADC_CHANNEL 4

#define MAX_NUMBER_ADC_USED              5
#define MAX_NUMBER_ADC_SAMPLE            10

void selectAdcChannel(uint8_t ui8_channelSelect);
bool startAdcConversion(void);
void averageAdcValue(void);
uint16_t readAdcChannel(uint8_t ui8_channelSelect);
uint16_t calculateAdcVoltage(uint16_t adcValue);

#endif /* INC_ADC_SAMPLING_H_ */

/*********************** (C) COPYRIGHT EATON *****END OF FILE****/
