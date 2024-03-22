#include "DigitalOutputControl.h"
#include <assert.h>
#include <stddef.h>

/* PUBLIC FUNCTIONS */
void DigitalOutputControl_InitPin(DigitalOutput_t* const p_this, Function_TakesConstObject_t pf_set_high,
                                  const void* const p_set_high_param, Function_TakesConstObject_t pf_set_low,
                                  const void* const p_set_low_param, Function_TakesConstObject_ReturnsBoolean_t pf_pin_state,
                                  const void* const p_pin_state_param) {
    assert(NULL != p_this);
    assert(NULL != pf_set_high);
    assert(NULL != pf_set_low);
    assert(NULL != pf_pin_state);
    assert(NULL != p_set_high_param);
    assert(NULL != p_set_low_param);
    assert(NULL != p_pin_state_param);

    p_this->pf_set_high = pf_set_high;
    p_this->pf_set_low = pf_set_low;
    p_this->pf_pin_state = pf_pin_state;
    p_this->p_set_high_param = p_set_high_param;
    p_this->p_set_low_param = p_set_low_param;
    p_this->p_pin_state_param = p_pin_state_param;
}

void DigitalOutputControl_SetPinHigh(DigitalOutput_t* const p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_set_high_param);
    assert(NULL != p_this->pf_set_high);
    if (false == p_this->pin_is_high) {
        p_this->pin_is_high = true;
        p_this->pf_set_high(p_this->p_set_high_param);
    }
}

void DigitalOutputControl_SetPinLow(DigitalOutput_t* const p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_set_low_param);
    assert(NULL != p_this->pf_set_low);
    if (true == p_this->pin_is_high) {
        p_this->pin_is_high = false;
        p_this->pf_set_low(p_this->p_set_low_param);
    }
}

bool DigitalOutputControl_GetPinStatus(const DigitalOutput_t* const p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->pf_pin_state);
    assert(NULL != p_this->p_pin_state_param);
    bool ret_val = false;

    ret_val = p_this->pf_pin_state(p_this->p_pin_state_param);

    return ret_val;
}
