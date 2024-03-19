/**
 * @file dualSmart_command.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include "dualSmart_commands.h"
#include "custom_user_if_fsm.h"
#include "command_class.h"

/**
 * @brief This function initializes the command list, and the RX and TX related FSMs.
 * 
 */
void init_dualSmart_commands(){
    init_command_list();

    init_custom_user_if_fsm();

    /* Here init the fsm related with rx */
}
