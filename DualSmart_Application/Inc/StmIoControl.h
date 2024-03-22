#ifndef INC_STMIOCONTROL_H_
#define INC_STMIOCONTROL_H_

/** @addtogroup EATON_CEAG_Modules
 * @{
 */

/** @addtogroup STM32_Input_Output_Control
 * @{
 */

#include "gpio.h"
#include <stdbool.h>

/**
 * @brief
 *
 */
typedef struct StmGpio {
    GPIO_TypeDef* p_gpiox;
    uint32_t ui32_pin_mask;
} StmGpio_t;

/**
 * @brief
 *
 */
typedef struct StmOutput {
    StmGpio_t output_pin;
    bool pin_is_high;
} StmOutput_t;

/**
 * @brief
 *
 */
typedef struct StmInput {
    StmGpio_t input_pin;
    bool pin_is_high;
} StmInput_t;

/**
 * @brief
 *
 * @param p_this
 * @param p_gpiox
 * @param ui32_pin_mask
 */
void StmIoControl_OutputInit(StmOutput_t* const p_this, GPIO_TypeDef* p_gpiox, uint32_t ui32_pin_mask);

/**
 * @brief
 *
 * @param p_this
 * @param p_gpiox
 * @param ui32_pin_mask
 */
void StmIoControl_InputInit(StmInput_t* const p_this, GPIO_TypeDef* p_gpiox, uint32_t ui32_pin_mask);

/**
 * @brief
 *
 * @param p_this
 * @param high_not_low
 * @return uint32_t
 */
uint32_t ui32_StmIoControl_SetOutputPinState(StmOutput_t* const p_this, bool high_not_low);

/**
 * @brief
 *
 * @param p_this
 * @return uint32_t
 */
uint32_t ui32_StmIoControl_SetOutputPinHigh(StmOutput_t* const p_this);

/**
 * @brief
 *
 * @param p_this
 * @return
 */
uint32_t ui32_StmIoControl_SetOutputPinLow(StmOutput_t* const p_this);

/**
 * @brief
 *
 *@param p_this
 * @return uint32_t
 */
bool ui32_StmIoControl_GetOutputPinState(StmOutput_t* const p_this);

/**
 * @brief
 *
 *@param p_this
 * @return uint32_t
 */
bool ui32_StmIoControl_GetInputPinState(StmInput_t* const p_this);

/**
 * @}
 */

/**
 * @}
 */

#endif /*INC_STMIOCONTROL_H_*/