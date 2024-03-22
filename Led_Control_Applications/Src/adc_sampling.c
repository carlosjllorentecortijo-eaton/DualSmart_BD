/**
 ******************************************************************************
 * @file    adc_sampling.c
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

#include "adc_sampling.h"
#include <movingAverage.h>
#include <stdlib.h>

uint16_t ui16_aTempLedCurrent[5][10] =
{
{ 0x00, 0x00 } };
uint16_t ui16_finalLedCurrent = 0x00;

/** @brief Select ADC channel
 *
 * This function is used to select the ADC channels.
 *
 * @param ui8_channelSelect     : channel number to select
 * @retval None
 */
void selectAdcChannel(uint8_t ui8_channelSelect)
{
    ADC_ChannelConfTypeDef sConfig =
    { 0 };

    switch (ui8_channelSelect)
    {
        case REF_28V_ADC_CHANNEL:
        {
            sConfig.Channel = ADC_CHANNEL_0;
            break;
        }

        case LED_VOLTAGE_ADC_CHANNEL:
        {
            sConfig.Channel = ADC_CHANNEL_1;
            break;
        }

        case LED_CURRENT_ADC_CHANNEL:
        {
            sConfig.Channel = ADC_CHANNEL_2;
            break;
        }

        case HARDWARE_REVISION_ADC_CHANNEL:
        {
            sConfig.Channel = ADC_CHANNEL_7;
            break;
        }

        case INTERNAL_TEMPERATURE_ADC_CHANNEL:
        {
            sConfig.Channel = ADC_CHANNEL_16;
            break;
        }

        default:
        {
            break;
        }
    }

    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @fn bool startAdcConversion(void)
 * @brief starts ADC conversion in polling mode
 *
 * @return returns successful ADC conversion
 */
bool startAdcConversion(void)
{
    bool samplingCompleted = false;
    uint16_t tempAdcCount = 0;
    uint16_t convertedAdcValue = 0;
    // 10 samples
    for (uint8_t ui8_j = 0; ui8_j < MAX_NUMBER_ADC_SAMPLE; ui8_j++)
    {
        // 4 different ADCs
        for (uint8_t ui8_i = 0; ui8_i < MAX_NUMBER_ADC_USED; ui8_i++)
        {
            selectAdcChannel(ui8_i);
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
            tempAdcCount = HAL_ADC_GetValue(&hadc1);

            switch (ui8_i)
            {
                case REF_28V_ADC_CHANNEL:
                {
                    convertedAdcValue = tempAdcCount;     // count can reach upto 0 - 4095
                    break;
                }

                case LED_VOLTAGE_ADC_CHANNEL:
                {
                    convertedAdcValue = tempAdcCount;
                    break;
                }

                case LED_CURRENT_ADC_CHANNEL:
                {
                    convertedAdcValue = tempAdcCount;
                    break;
                }

                case HARDWARE_REVISION_ADC_CHANNEL:
                {
                    convertedAdcValue = tempAdcCount;
                    break;
                }

                case INTERNAL_TEMPERATURE_ADC_CHANNEL:
                {
                    convertedAdcValue = tempAdcCount;
                    break;
                }

                default:
                {
                    break;
                }
            }

            ui16_aTempLedCurrent[ui8_i][ui8_j] = convertedAdcValue;

            convertedAdcValue = 0;
            tempAdcCount = 0;
        }
    }

    return samplingCompleted = true;
}

/**
 * @fn void averageAdcValue(void)
 * @brief calculates the average of the ADC buffer
 *
 */
void averageAdcValue(void)
{

    bool conversionStatus = false;
    uint32_t ui32_sumValue = 0;

    while (true != conversionStatus)
    {
        // do nothing
    }

    // Do the averaging of the current value
    for (uint8_t ui8_i = 0; ui8_i < 10; ui8_i++)
    {
        ui32_sumValue += ui16_aTempLedCurrent[2][ui8_i];
    }

    ui16_finalLedCurrent = ui32_sumValue / 10;
}

/** @brief read single ADC value
 *
 * This function is used to read a single ADC value based on a selected channel.
 *
 * @param ui8_channelSelect     : channel to select -> see predefined macros
 * @retval adcResult: Raw adc result
 */
uint16_t readAdcChannel(uint8_t ui8_channelSelect)
{
    uint16_t adcResult = 0;
    selectAdcChannel(ui8_channelSelect);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    adcResult = HAL_ADC_GetValue(&hadc1);
    return adcResult;
}

/**
 * @fn uint16_t calculateAdcVoltage(uint16_t)
 * @brief Calculates the voltage read by the ADC
 *
 * @param adcValue Raw ADC value
 * @return Voltage in mV
 */
uint16_t calculateAdcVoltage(uint16_t adcValue)
{
    uint16_t retVal = 0;
    retVal = (uint32_t) (((adcValue * 3.3) / 4095) * 1000);
    return retVal;
}

/*********************** (C) COPYRIGHT EATON *****END OF FILE****/
