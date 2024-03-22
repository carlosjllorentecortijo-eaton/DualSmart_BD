#ifndef A4358536_1B37_45E1_9D41_04EF21AC3AEB
#define A4358536_1B37_45E1_9D41_04EF21AC3AEB

/** @addtogroup EATON_CEAG_Modules
 * @{
 */

/** @addtogroup Digital_Output_Control
 * @{
 */

#include "FunctionPrototypes.h"

/**
 * @brief Class to describe a digital output. Contains one funciton pointer each for setting pin high and low and for getting the status.
 * Contains the paramters for the functions to be called.
 *
 */
typedef struct DigitalOutput {
    Function_TakesConstObject_t pf_set_high;
    const void* p_set_high_param;
    Function_TakesConstObject_t pf_set_low;
    const void* p_set_low_param;
    Function_TakesConstObject_ReturnsBoolean_t pf_pin_state;
    const void* p_pin_state_param;
    bool pin_is_high;
} DigitalOutput_t;

/**
 * @brief Initialization of output object. Expects the function poiinters for setting a pin high, low and returning its status. Expects the
 * pointers to the parameters for the functions to be called.
 *
 * @param p_this
 * @param pf_set_high
 * @param p_set_high_param
 * @param pf_set_low
 * @param p_set_low_param
 * @param pf_pin_state
 * @param p_pin_state_param
 * @return
 */
void DigitalOutputControl_InitPin(DigitalOutput_t* const p_this, Function_TakesConstObject_t pf_set_high,
                                  const void* const p_set_high_param, Function_TakesConstObject_t pf_set_low,
                                  const void* const p_set_low_param, Function_TakesConstObject_ReturnsBoolean_t pf_pin_state,
                                  const void* const p_pin_state_param);

/**
 * @brief Sets the output of the object high.
 *
 * @param p_this
 * @return
 */
void DigitalOutputControl_SetPinHigh(DigitalOutput_t* const p_this);

/**
 * @brief Sets the output of the object low.
 *
 * @param p_this
 * @return
 */
void DigitalOutputControl_SetPinLow(DigitalOutput_t* const p_this);

/**
 * @brief Returns the state of the output object.
 *
 * @param p_this
 * @return
 */
bool DigitalOutputControl_GetPinStatus(const DigitalOutput_t* const p_this);

/**
 * @}
 */

/**
 * @}
 */

#endif /* A4358536_1B37_45E1_9D41_04EF21AC3AEB */
