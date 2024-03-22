#ifndef F2C83B7F_57F0_430B_A8B0_844137518001
#define F2C83B7F_57F0_430B_A8B0_844137518001

/** @addtogroup EATON_CEAG_Modules
 * @{
 */

/** @addtogroup STM32_ADC_Control
 * @{
 */

#include "ADCInterface.h"
#include "adc.h"
#include <stdbool.h>

/**
 * @brief Class which holds all needed variables for ADC object
 *
 */
typedef struct StmAdcChannel {
    ADCInterface_t adc_interface;
    uint32_t ui32_channel;
    ADC_HandleTypeDef* p_hadc;
    ADC_ChannelConfTypeDef sConfig;
    uint16_t converted_value;
    uint8_t value_delta_limit;
} StmAdcChannel_t;

/**
 * @brief Initiaizes ADC object.
 *
 * @param p_this pointer to instance of StmAdcChannel_t
 * @param p_hadc pointer to stm adc channel handler
 * @param ui8_channel number of the ADC channel which shall be linked to the object
 */
void StmAdcControl_InitAdcObj(StmAdcChannel_t* p_this, ADC_HandleTypeDef* p_hadc, uint32_t ui8_channel);

/**
 * @brief Starts a single conversion in blocking mode and returns its result.
 *
 * @param p_this pointer to instance of StmAdcChannel_t
 * @return result in digits
 */
uint16_t ui16_StmAdcControl_StartAndReadSingleConversion(StmAdcChannel_t* p_this);

/**
 * @brief Returns the last result, which was stored in the given object.
 *
 * @param p_this pointer to instance of StmAdcChannel_t
 * @return result in digits
 */
uint16_t ui16_StmAdcControl_GetAdcValueFromObject(const StmAdcChannel_t* const p_this);

/**
 * @brief
 *
 * @param p_this
 * @return ADCInterface_t*
 */
ADCInterface_t* StmAdcControl_GetADCInterface(StmAdcChannel_t* p_this);

/**
 * @}
 */

/**
 * @}
 */

#endif /* F2C83B7F_57F0_430B_A8B0_844137518001 */
