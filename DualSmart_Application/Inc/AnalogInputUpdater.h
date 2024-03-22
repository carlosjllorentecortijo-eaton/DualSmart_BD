#ifndef B0A65670_2AE9_4D92_BB57_6C920EECF6C3
#define B0A65670_2AE9_4D92_BB57_6C920EECF6C3

/** @addtogroup EATON_CEAG_Modules
 * @{
 */

/** @addtogroup Analog_Input_Updater
 * @{
 */

#include "DualSmartConfig.h"
#include "StmAdcControl.h"

/**
 * @brief Analog Updater
 *
 */
typedef struct AnalogInputUpdater {
    DualSmartAdc_t* p_analog_inputs;
    size_t analog_object_size;
    size_t analog_struct_size;
    StmAdcChannel_t* start_address;
    StmAdcChannel_t* end_address;
} AnalogInputUpdater_t;

/**
 * @brief Initializes Analog Updater. Expects a struct to all the AD channel objects.
 *
 * @param p_inputs
 */
void AnalogInputUpdater_Init(DualSmartAdc_t* p_inputs);

/**
 * @brief Task to update the analog inputs
 *
 */
void AnalogInputUpdater_Task(void);

/**
 * @}
 */

/**
 * @}
 */

#endif /* B0A65670_2AE9_4D92_BB57_6C920EECF6C3 */
