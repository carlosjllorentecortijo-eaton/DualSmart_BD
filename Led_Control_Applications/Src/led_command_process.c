#include <adc_sampling.h>
#include <movingAverage.h>
#include <string.h>
#include "pwm.h"
#include "adc.h"
#include <sflash_driver.h>

static uint16_t ledCurrAdcValues[MAX_ARRAY_SIZE];


uint16_t calculateLedCurrent(uint16_t ui16_adcVoltage,
        uint16_t led_current_pulse);

/** @brief read led value
 *
 * This function is used to read the moving average voltage from the ADC which is representing the LED current
 *
 * @param *p_array    : pointer to array with ADC values
 * @param channel    : ADC channel to read
 *
 * @retval none
 */
uint16_t read_led_value(uint16_t *p_array, uint8_t channel)
{
    uint16_t adcResult = 0;
    uint16_t avgAdcValue = 0;
    uint16_t adcVoltage = 0;

    adcResult = readAdcChannel(channel);
    moveAndAddArray(p_array, MAX_ARRAY_SIZE, adcResult);
    avgAdcValue = calculateAvarage(p_array, MAX_ARRAY_SIZE);
    adcVoltage = calculateAdcVoltage(avgAdcValue);

    return adcVoltage;
}

/** @brief current control loop
 *
 * This function is used to keep the current flowing through the LED constant
 * Implemented by an empirically determined PI controller.
 *
 * @param desiredCurrent_mA    : desired current in mA
 *
 * @retval none
 *
 * @todo remove magic numbers
 */
void currentControlLoop(uint16_t ui16_desired_current_mA)
{
    uint16_t ui16_led_adc_mV = 0;
    static uint16_t ui16_led_current_mA = LUMINARE_MAX_CURRENT;
    static uint16_t ui16_led_current_pulse = DEFAULT_LED_CURRENT_LEVEL;
    static uint8_t ui32_counter = 1;

    /*PI Controller parameters*/
    static const float f_kp = 3.00;
    static const float f_ti = 0.02;

    /*Controller varables*/
    static int16_t i16s_err = 0;
    static int32_t i32s_err_integ = 0;

    ui16_led_adc_mV = read_led_value(ledCurrAdcValues, LED_CURRENT_ADC_CHANNEL);

    ui16_led_current_mA = calculateLedCurrent(ui16_led_adc_mV,
            ui16_led_current_pulse);

    if ((ui32_counter++ % MAX_ARRAY_SIZE) == 0)
    {
        i16s_err = ui16_desired_current_mA - ui16_led_current_mA;
        i32s_err_integ += i16s_err;

        ui16_led_current_pulse += (f_kp * (i16s_err + (f_ti * i32s_err_integ)));
    }

    changeCurrentLevelPwmDutyCycle(ui16_led_current_pulse);
}

/** @brief calculate LED current
 *
 * This function is used to calculate the current flowing through the LED
 *
 * @param ui16_adcVoltage    :voltage measured by ADC
 *
 * @retval retVal			:current in mA
 */
uint16_t calculateLedCurrent(uint16_t ui16_adcVoltage,
        uint16_t ui16_led_current_pulse)
{
    /*constants based on HW design*/
    static const uint8_t ui8_GainMAX4073 = 50;		//MAX4073
    static const uint8_t ui8_resistorDivider = 2;     //10k + 10k
    static const float f_shuntResistor = 0.2;	    //0,2 Ohms
    static const uint16_t ui16_lookup_pwm[] =
    { 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400,
            2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500,
            3600, 3700, 3800, 3900, 4000, 4100, 4200 };
    static const float f_lookup_corr[] =
    { 1.5364, 1.5364, 1.5413, 1.5435, 1.5467, 1.5779, 1.6069, 1.633, 1.6623,
            1.6859, 1.7357, 1.7537, 1.7994, 1.8446, 1.8877, 1.929, 1.9697,
            2.009, 2.0478, 2.0856, 2.1367, 2.1868, 2.2213, 2.2689, 2.3146,
            2.3397, 2.3408, 2.4304, 2.4348, 2.4628 };

    static float f_corrFakt = 1;
    static uint8_t ui8_counter = 0;

    uint16_t retVal = 0;

    //Lookup table for current correction
    if ((ui16_led_current_pulse > ui16_lookup_pwm[ui8_counter])
            && (ui8_counter < 29))
    {
        ui8_counter++;
    }
    else if ((ui16_led_current_pulse < ui16_lookup_pwm[ui8_counter])
            && (ui8_counter > 0))
    {
        ui8_counter--;
    }
    f_corrFakt = f_lookup_corr[ui8_counter];

    //linear approximation
    //f_corrFakt = ((0.0004*ui16_led_current_pulse)+0.9515);

    retVal = (uint16_t) (((ui16_adcVoltage
            / (ui8_GainMAX4073 / ui8_resistorDivider)) / f_shuntResistor)
            * f_corrFakt);

    return retVal;
}
