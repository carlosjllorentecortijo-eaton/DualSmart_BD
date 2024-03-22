#ifndef EA52D0BF_8118_4127_B3E2_58C98C8FDB7B
#define EA52D0BF_8118_4127_B3E2_58C98C8FDB7B

/** @addtogroup EATON_CEAG_Interfaces
 * @{
 */

/** @addtogroup ADC_Interface
 * @{
 */

#include "FunctionPrototypes.h"
#include <stddef.h>

/**
 * @brief ADC Interface to start a conversion and read the result
 *
 */
typedef uint16_t (*ADCInterface_StartAndRead_t)(void* const p_obj);

/**
 * @brief ADC Interface to read the last converted value
 *
 */
typedef uint16_t (*ADCInterface_ReadLastValue_t)(void* const p_obj);

/**
 * @brief ADC Interface description
 *
 */
typedef struct ADCInterface {
    ADCInterface_StartAndRead_t pf_start_and_read;
    ADCInterface_ReadLastValue_t pf_read_last_value;
    void* p_adc_obj;
} ADCInterface_t;

/**
 * @}
 */

/**
 * @}
 */

#endif /* EA52D0BF_8118_4127_B3E2_58C98C8FDB7B */
