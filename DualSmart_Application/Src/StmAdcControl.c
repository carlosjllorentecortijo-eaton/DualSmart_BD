#include "StmAdcControl.h"
#include <assert.h>

/**
 * @brief Sets the only available RANK to the ADC channel present in object.
 *
 * @param p_this pointer to instance of StmAdcChannel_t
 */
void prv_StmAdcControl_SelectChannel(StmAdcChannel_t* p_this);

/**
 * @brief Removes the only available RANK from the ADC channel present in object.
 *
 * @param p_this pointer to instance of StmAdcChannel_t
 */
void prv_StmAdcControl_FreeChannel(StmAdcChannel_t* p_this);

void StmAdcControl_InitAdcObj(StmAdcChannel_t* p_this, ADC_HandleTypeDef* p_hadc, uint32_t ui32_channel) {
    assert(NULL != p_this);
    assert(NULL != p_hadc);

    p_this->p_hadc = p_hadc;
    p_this->ui32_channel = ui32_channel;
    p_this->sConfig.Rank = ADC_RANK_NONE;
    p_this->sConfig.Channel = p_this->ui32_channel;
    p_this->sConfig.SamplingTime = ADC_SAMPLETIME_12CYCLES_5;
    p_this->adc_interface.pf_start_and_read = (ADCInterface_StartAndRead_t)ui16_StmAdcControl_StartAndReadSingleConversion;
    p_this->adc_interface.pf_read_last_value = (ADCInterface_ReadLastValue_t)ui16_StmAdcControl_GetAdcValueFromObject;
    p_this->adc_interface.p_adc_obj = p_this;
}

uint16_t ui16_StmAdcControl_StartAndReadSingleConversion(StmAdcChannel_t* p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_hadc);

    prv_StmAdcControl_SelectChannel(p_this);
    HAL_ADC_Start(p_this->p_hadc);
    if (HAL_ADC_PollForConversion(p_this->p_hadc, HAL_MAX_DELAY) == HAL_OK) {
        p_this->converted_value = HAL_ADC_GetValue(p_this->p_hadc);
    }
    HAL_ADC_Stop(p_this->p_hadc);
    prv_StmAdcControl_FreeChannel(p_this);
    return p_this->converted_value;
}

uint16_t ui16_StmAdcControl_GetAdcValueFromObject(const StmAdcChannel_t* const p_this) {
    assert(NULL != p_this);

    return p_this->converted_value;
}

ADCInterface_t* StmAdcControl_GetADCInterface(StmAdcChannel_t* p_this) {
    assert(NULL != p_this);

    return &p_this->adc_interface;
}

void prv_StmAdcControl_SelectChannel(StmAdcChannel_t* p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_hadc);

    p_this->sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    if (HAL_ADC_ConfigChannel(p_this->p_hadc, &p_this->sConfig) != HAL_OK) {
        Error_Handler();
    }
}

void prv_StmAdcControl_FreeChannel(StmAdcChannel_t* p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_hadc);

    p_this->sConfig.Rank = ADC_RANK_NONE;
    if (HAL_ADC_ConfigChannel(p_this->p_hadc, &p_this->sConfig) != HAL_OK) {
        Error_Handler();
    }
}