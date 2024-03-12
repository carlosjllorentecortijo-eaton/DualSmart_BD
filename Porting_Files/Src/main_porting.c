/**
 * @file main_porting.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the definition of the function to be used in the main.c file of the STM G3 FW.
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <passthrough.h>

/**
 * @brief This file activates the passthrough mode. Note this is necessary to be included as actual STM G3 FW versions deal with this
 * behavior via SW. Our boards deal with this thorough HW.
 * 
 */
void passthrough_mode(){
	bool passthrough_requested = (readBootModeSTM32()  == STM32_BOOT_PASSTHROUGH);
	/* If passthrough mode is requested */
	if (passthrough_requested == true)
	{
		/* Activates passthrough mode (program remains here), BOOT pins are left in output */
		activatePassthrough();
	}
}
