/**
 * @file CommandClass.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file implements the class methods and initializes the list of commands.
 * @version 0.1
 * @date 2024-03-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* ---------------------------------------------------- INCLUDES ---------------------------------------------------- */
#include "CommandClass.h"
#include "SettingsCustom.h"
#include "user_g3_common.h"
#include "user_if.h"
#include "utils.h"
#include "mem_pool.h"
#include <stdint.h>

#define PRINT_COLOR(format, color, args...)					user_if_printf(true,  color, NULL, format, ## args)

/* ------------------------------------------------ PRIVATE VARIABLES ----------------------------------------------- */
extern command_class_t p_command_list[NUMBER_COMMANDS];
extern custom_user_rx_data_t custom_user_rx_data;

/* --------------------------------------------- MENU CREATION FUNCTION --------------------------------------------- */
void menu_generation() {
    PRINT_BLANK_LINE();
    PRINT("<< Custom Commands >>\n\n");
    for (int i = 0; i < NUMBER_COMMANDS; i++){
        if ( p_command_list[i].ui8_shown_in_menu ) {
            PRINT("%u) %s\n", p_command_list[i].ui8_menu_number, p_command_list[i].ui8_menu_text);
        }
    }
}

/* --------------------------------------------- CLASS INTERFACE FUNTION -------------------------------------------- */
/**
 * @brief 
 * 
 * @param ui8_user_input 
 */
void action_on_selection(const uint8_t ui8_user_input, custom_user_if_fsm_t* custom_user_if_fsm) {
    for (int i = 0; i < NUMBER_COMMANDS; i++){
        if ( p_command_list[i].ui8_shown_in_menu && (p_command_list[i].ui8_menu_number == ui8_user_input) ){
            if ( p_command_list[i].pf_action_on_selection_cb != NULL ){
            	PRINT_COLOR("CUSTOM COMMAND SELECTED 0x%02x\n", color_green, p_command_list[i].ui8_command_id);
                p_command_list[i].pf_action_on_selection_cb(custom_user_if_fsm);
            }
            return;
        }
    }
	#if DEBUG_COMMANDS >= DEBUG_LEVEL_WARNING
    PRINT_COLOR("No command found with menu number %u\n", color_red, ui8_user_input);
	#endif
}

/**
 * @brief 
 * 
 * @param ui8_command_id 
 */
void action_on_rx(const void* payload) {
	const IP_DataIndication_t    *ip_udp_ind   = payload;
	const IP_UdpDataIndication_t *udp_data_ind = hi_ipv6_extract_udp_from_ip(ip_udp_ind);
	udp_packet_t incoming_packet;

	assert(udp_data_ind != NULL);

	incoming_packet.length = udp_data_ind->data_len;

	if( incoming_packet.length > 0 ){
		#if DEBUG_COMMANDS >= DEBUG_LEVEL_INFO
		incoming_packet.connection_id	= udp_data_ind->connection_id;
		incoming_packet.ip_addr 		= udp_data_ind->source_address;
		incoming_packet.port 			= udp_data_ind->source_port;
		#endif

		const uint8_t* pui8_data = udp_data_ind->data;
		const uint8_t ui8_command_id = pui8_data[0];
		for (int i = 0; i < NUMBER_COMMANDS; i++){
			if ( p_command_list[i].ui8_command_id == ui8_command_id ){
				#if DEBUG_COMMANDS >= DEBUG_LEVEL_INFO
				ALLOC_DYNAMIC_HEX_STRING(src_ip_addr_str, udp_data_ind->source_address.u8, sizeof(udp_data_ind->source_address.u8));
				PRINT("Received custom command in UDP packet of %u bytes from connection %u, IPv6 %s, remote port %u\n", udp_data_ind->data_len, udp_data_ind->connection_id, src_ip_addr_str, udp_data_ind->source_port);
				FREE_DYNAMIC_HEX_STRING(src_ip_addr_str);
				#endif
				PRINT_COLOR("CUSTOM COMMAND RECEIVED 0x%02x\n", color_green, ui8_command_id);
				if ( p_command_list[i].pf_action_on_rx_cb != NULL ){
					p_command_list[i].pf_action_on_rx_cb(pui8_data, &custom_user_rx_data);
				}
				return;
			}
		}
		#if DEBUG_COMMANDS >= DEBUG_LEVEL_WARNING
		PRINT_COLOR("No command found with command id %u\n", color_red, ui8_command_id);
		#endif
	}
}

/**
 * @brief 
 * 
 * @param ui8_command_id
 */
bool b_is_udp_data_custom(const void* payload) {
	const IP_DataIndication_t    *ip_udp_ind   = payload;
	const IP_UdpDataIndication_t *udp_data_ind = hi_ipv6_extract_udp_from_ip(ip_udp_ind);
	udp_packet_t incoming_packet;

	assert(udp_data_ind != NULL);

	incoming_packet.length = udp_data_ind->data_len;

	if( incoming_packet.length > 0 ){
		#if DEBUG_COMMANDS >= DEBUG_LEVEL_INFO
		incoming_packet.connection_id	= udp_data_ind->connection_id;
		incoming_packet.ip_addr 		= udp_data_ind->source_address;
		incoming_packet.port 			= udp_data_ind->source_port;
		#endif

		const uint8_t* pui8_data = udp_data_ind->data;
		const uint8_t ui8_command_id = pui8_data[0];
		for (int i = 0; i < NUMBER_COMMANDS; i++){
			if ( p_command_list[i].ui8_command_id == ui8_command_id ){
				return true;
			}
		}

		#if DEBUG_COMMANDS >= DEBUG_LEVEL_WARNING
		PRINT_COLOR("No command found with command id %u\n", color_red, ui8_command_id);
		#endif
	}
	return false;
}

/**
 * @brief
 *
 */
void init_command_list() {
    populate_command_list();
}

