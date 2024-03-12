/**
 * @file pin_management.h
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This header file contains the strong definition of the pin management related functions. This file objective is to easily
 * port the STM G3 FW to different HW.
 * @version 0.1
 * @date 2024-03-12
 * @note FUNCTIONS DEFINED HERE MUST BE DECLARED AS WEAK IN Modules/Pin_Manangement/Src/pin_management.c
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef PIN_MANAGEMENT
#define PIN_MANAGEMENT

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ST8500_Gpio_Management ST8500 GPIO Management
  * @{
  */

/**
  * @}
  */

/* Inclusions */
#include <stdint.h>
#include <stdbool.h>

/** @addtogroup ST8500_Gpio_Management
  * @{
  */

/* Public functions */

/* Switches for STM32/ST8500 boot modes */
st8500_boot_mode_t readBootModeST8500(void);

/* Switches and configuration */
bool readRfSelect(void);
bool readFCCSelect(void);
bool readMacSelect(void);
bool readModbusMasterSelect(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PIN_MANAGEMENT */