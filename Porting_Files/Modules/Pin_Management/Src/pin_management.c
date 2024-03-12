/**
 * @file pin_management.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the definition of the function THAT MUST BE DEFINED AS WEAK in the Modules/Pin_Manangement/Src/pin_management.c
 * file. This allows porting the implementation to HW containing different pinout or expected functionality.
 * @version 0.1
 * @date 2024-03-12
 * @note FUNCTIONS DEFINED HERE MUST BE DECLARED AS WEAK IN Modules/Pin_Manangement/Src/pin_management.c
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <pin_management.h>

/**
 * @brief  This function reads the ST8500 boot mode.
 * @param  None
 * @return ST8500 boot mode, boot from UART (0), or boot from SFLASH attached to ST8500 (1).
 */
st8500_boot_mode_t readBootModeST8500(void)
{
	/* LOW GPIO LEVEL  -> 0 -> Boot from UART */
	/* HIGH GPIO LEVEL -> 1 -> Boot from FLASH */

	return ST8500_BOOT_FROM_UART;
}

/**
 * @brief  This function reads the MAC_SELECT pin.
 * @param  None
 * @return true, if MAC_SELECT is enabled, false otherwise.
 */
bool readRfSelect(void)
{
	/* LOW GPIO LEVEL  -> 0 -> 915 module selected */
	/* HIGH GPIO LEVEL -> 1 -> 868 module selected */

	return 1;
}

/**
 * @brief  This function reads the selected bandplan (CEN-A/FCC).
 * @param  None
 * @return STM32 boot mode, default (0), or in sleep mode (1).
 */
bool readFCCSelect(void)
{
	/* SWITCH UP   -> LOW GPIO LEVEL  -> 0 -> CENB */
	/* SWITCH DOWN -> HIGH GPIO LEVEL -> 1 -> FCC  */

	return 0;
}

/**
 * @brief  This function reads the MAC_SELECT pin.
 * @param  None
 * @return true, if MAC_SELECT is enabled, false otherwise.
 */
bool readMacSelect(void)
{
	/* LOW GPIO LEVEL  -> 0 -> Normal mode */
	/* HIGH GPIO LEVEL -> 1 -> MAC mode */

	return 0;
}

/**
 * @brief  This function reads the MAC_SELECT pin.
 * @param  None
 * @return true, if MAC_SELECT is enabled, false otherwise.
 */
bool readModbusMasterSelect(void)
{
	/* LOW GPIO LEVEL  -> 0 -> Slave mode */
	/* HIGH GPIO LEVEL -> 1 -> Master mode */

	return 0;
}