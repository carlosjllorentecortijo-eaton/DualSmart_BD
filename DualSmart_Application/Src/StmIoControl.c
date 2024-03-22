/* Private includes*/
#include <StmIoControl.h>
#include <assert.h>

/**
 * @brief
 *
 * @param p_this
 * @param p_gpiox
 * @param ui32_pin_mask
 */
static void prv_StmIoControl_Init(StmGpio_t* const p_this, GPIO_TypeDef* p_gpiox, uint32_t ui32_pin_mask);

void prv_StmIoControl_Init(StmGpio_t* const p_this, GPIO_TypeDef* p_gpiox, uint32_t ui32_pin_mask) {
    assert(NULL != p_this);
    assert(NULL != p_gpiox);

    p_this->p_gpiox = p_gpiox;
    p_this->ui32_pin_mask = ui32_pin_mask;
}

void StmIoControl_OutputInit(StmOutput_t* const p_this, GPIO_TypeDef* p_gpiox, uint32_t ui32_pin_mask) {
    assert(NULL != p_this);
    assert(NULL != p_gpiox);

    prv_StmIoControl_Init(&p_this->output_pin, p_gpiox, ui32_pin_mask);
}

void StmIoControl_InputInit(StmInput_t* const p_this, GPIO_TypeDef* p_gpiox, uint32_t ui32_pin_mask) {
    assert(NULL != p_this);
    assert(NULL != p_gpiox);

    prv_StmIoControl_Init(&p_this->input_pin, p_gpiox, ui32_pin_mask);
}

uint32_t ui32_StmIoControl_SetOutputPinState(StmOutput_t* const p_this, bool high_not_low) {
    assert(NULL != p_this);

    uint32_t ret_val = 0;

    if (true == high_not_low) {
        LL_GPIO_SetOutputPin(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);
    } else if (false == high_not_low) {
        LL_GPIO_ResetOutputPin(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);
    }

    ret_val = LL_GPIO_IsOutputPinSet(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);
    p_this->pin_is_high = ret_val;
    return ret_val;
}

uint32_t ui32_StmIoControl_SetOutputPinHigh(StmOutput_t* const p_this) {
    assert(NULL != p_this);

    uint32_t ret_val = 0;

    LL_GPIO_SetOutputPin(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);

    ret_val = LL_GPIO_IsOutputPinSet(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);
    p_this->pin_is_high = ret_val;
    return ret_val;
}

uint32_t ui32_StmIoControl_SetOutputPinLow(StmOutput_t* const p_this) {
    assert(NULL != p_this);

    uint32_t ret_val = 0;

    LL_GPIO_ResetOutputPin(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);

    ret_val = LL_GPIO_IsOutputPinSet(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);
    p_this->pin_is_high = ret_val;
    return ret_val;
}

bool ui32_StmIoControl_GetOutputPinState(StmOutput_t* const p_this) {
    assert(NULL != p_this);

    uint32_t ret_val = 0;

    ret_val = LL_GPIO_IsOutputPinSet(p_this->output_pin.p_gpiox, p_this->output_pin.ui32_pin_mask);
    p_this->pin_is_high = ret_val;
    return (bool)ret_val;
}

bool ui32_StmIoControl_GetInputPinState(StmInput_t* const p_this) {
    assert(NULL != p_this);

    uint32_t ret_val = 0;

    ret_val = LL_GPIO_IsInputPinSet(p_this->input_pin.p_gpiox, p_this->input_pin.ui32_pin_mask);
    p_this->pin_is_high = ret_val;
    return (bool)ret_val;
}