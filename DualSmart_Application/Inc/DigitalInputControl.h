#ifndef F857CF8C_C694_45A5_A1F1_59CFB8CF24B5
#define F857CF8C_C694_45A5_A1F1_59CFB8CF24B5

/** @addtogroup EATON_CEAG_Modules
 * @{
 */

/** @addtogroup Digital_Input_Control
 * @{
 */

#include "FunctionPrototypes.h"

/**
 * @brief Class to describe a digital input.Contains a funciton  for getting the status.
 *
 */
typedef struct DigitalInput {
    const void* p_pin_state_param;
    Function_TakesConstObject_ReturnsBoolean_t pf_pin_state;
    bool pin_is_high;
} DigitalInput_t;

/**
 * @brief Initialization of input object. Expects the function poiinter for returning its status. Expects the
 * pointers to the parameter for the function to be called.
 *
 * @param p_this
 * @param pf_pin_state
 * @param p_pin_state_param
 */
void DigitalInputControl_InitPin(DigitalInput_t* const p_this, Function_TakesConstObject_ReturnsBoolean_t pf_pin_state,
                                 const void* const p_pin_state_param);

/**
 * @brief Updates and returns the state of the input object.
 *
 * @param p_this
 * @return
 */
bool DigitalInputControl_GetPinStatus(const DigitalInput_t* const p_this);

/**
 * @}
 */

/**
 * @}
 */

#endif /* F857CF8C_C694_45A5_A1F1_59CFB8CF24B5 */
