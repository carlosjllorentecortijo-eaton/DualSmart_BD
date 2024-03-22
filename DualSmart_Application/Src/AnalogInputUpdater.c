#include "AnalogInputUpdater.h"

AnalogInputUpdater_t analog_input_updater_struct;

void AnalogInputUpdater_Init(DualSmartAdc_t* p_inputs) {
    analog_input_updater_struct.p_analog_inputs = p_inputs;
    analog_input_updater_struct.analog_object_size = sizeof(StmAdcChannel_t);
    analog_input_updater_struct.analog_struct_size = sizeof(DualSmartAdc_t);
    analog_input_updater_struct.start_address = &analog_input_updater_struct.p_analog_inputs->battery_voltage;
    analog_input_updater_struct.end_address =
        analog_input_updater_struct.start_address +
        ((analog_input_updater_struct.analog_struct_size / analog_input_updater_struct.analog_object_size) - 1);
}

void AnalogInputUpdater_Task(void) {
    for (StmAdcChannel_t* call_address = analog_input_updater_struct.start_address; call_address <= analog_input_updater_struct.end_address;
         call_address++) {
        ui16_StmAdcControl_StartAndReadSingleConversion(call_address);
    }
}