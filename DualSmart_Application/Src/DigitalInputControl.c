#include "DigitalInputControl.h"
#include <assert.h>
#include <stddef.h>

void DigitalInputControl_InitPin(DigitalInput_t* const p_this, Function_TakesConstObject_ReturnsBoolean_t pf_pin_state,
                                 const void* const p_pin_state_param) {
    assert(NULL != p_this);
    assert(NULL != pf_pin_state);
    assert(NULL != p_pin_state_param);

    p_this->pf_pin_state = pf_pin_state;
    p_this->p_pin_state_param = p_pin_state_param;
}

bool DigitalInputControl_GetPinStatus(const DigitalInput_t* const p_this) {
    assert(NULL != p_this);
    assert(NULL != p_this->p_pin_state_param);
    assert(NULL != p_this->pf_pin_state);

    bool ret_val = p_this->pf_pin_state(p_this->p_pin_state_param);

    return ret_val;
}
