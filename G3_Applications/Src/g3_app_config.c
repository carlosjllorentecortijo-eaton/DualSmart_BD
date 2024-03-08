/******************************************************************************
*   @file    g3_app_config.c
*   @author  AMG/IPC Application Team
*   @brief   This file contains the implementation of g3 configuration functionalities.
*
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
*******************************************************************************/

/* Inclusions */
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <mem_pool.h>
#include <utils.h>
#include <debug_print.h>
#include <hi_g3lib_sap_interface.h>
#include <hi_msgs_impl.h>
#include <g3_app_attrib_tbl.h>
#include <g3_app_config.h>
#include <g3_app_config_rf_params.h>
#include <g3_app_boot.h>
#include <user_modbus.h>
#include <settings.h>
#include <version.h>

/** @addtogroup G3_App
  * @{
  */

/** @addtogroup G3_App_Config
  * @{
  */

/** @addtogroup G3_App_Config_Private_Code
  * @{
  */

/* Macros */
#if DEBUG_G3_CONF
#define HANDLE_CNF_ERROR(cnf_id, status) if (status != G3_SUCCESS) PRINT_G3_CONF_CRITICAL("ERROR, received negative CNF (%u=%s) for %s\n", status, g3_app_translate_g3_result(status), translateG3cmd(cnf_id));
#else
#define HANDLE_CNF_ERROR(cnf_id, status)
#endif

/* Private types */
typedef enum conf_event_enum
{
    CONF_EV_NONE,
    CONF_EV_RECEIVED_SWRESET_CNF,
    CONF_EV_RECEIVED_SET_CNF,
	CONF_EV_RECEIVED_DBGTOOL_CNF,
    CONF_EV_RECEIVED_RFCONFIGSET_CNF,
    CONF_EV_RECEIVED_SRV_STOP_CNF,
    CONF_EV_RECEIVED_SRV_START_CNF,
    CONF_EV_CNT
} conf_event_t;

typedef enum conf_state_enum
{
    CONF_ST_WAIT_SWRESET_CNF,
    CONF_ST_WAIT_SET_CNF,
	CONF_ST_WAIT_DBGTOOL_CNF,
	CONF_ST_WAIT_RFCONFIGSET_CNF,
#if IS_COORD
    CONF_ST_WAIT_SRV_STOP_CNF,
	CONF_ST_WAIT_SRV_START_CNF,
#endif /* IS_COORD */
    CONF_ST_CNT
} g3_conf_state_t;

typedef struct g3_conf_fsm_info_str
{
    g3_conf_state_t curr_state;
    conf_event_t	curr_event;
    uint32_t		peVersion;
    bool			rf_connected;
    bool			g3_ready;
} g3_conf_fsm_info_t;

/* Private variables */

static g3_conf_fsm_info_t	g3_conf_fsm_info;
/**
  * @}
  */

/** @addtogroup G3_App_Config_Exported_Code
  * @{
  */

/* Global variables */
rf_type_t		rf_type;
BOOT_Bandplan_t	working_plc_band = BOOT_BANDPLAN_CENELEC_A;
plc_mode_t		working_plc_mode = PLC_MODE_PHY;
modbus_role_t   modbus_role;
uint8_t 		mac_address[MAC_ADDR64_SIZE] = {0};

/* External variables */

/**
  * @}
  */

/** @addtogroup G3_App_Config_Private_Code
  * @{
  */

/* Private function pointer type */
typedef g3_conf_state_t g3_conf_fsm_func(void);

/* Private FSM function prototypes */
static g3_conf_state_t g3_conf_fsm_default(void);
static g3_conf_state_t g3_conf_fsm_set_attribute(void);
static g3_conf_state_t g3_conf_fsm_received_dbgtool_cnf(void);
static g3_conf_state_t g3_conf_fsm_received_rfconfigset_cnf(void);
#if IS_COORD
static g3_conf_state_t g3_conf_fsm_received_srvstop_cnf(void);
static g3_conf_state_t g3_conf_fsm_received_srvstart_cnf(void);
#endif /* IS_COORD */

/* Private FSM function pointer array */

/**
  * @brief Calls a different function, depending on the current state and event.
  */
static g3_conf_fsm_func *g3_conf_fsm_func_tbl[CONF_ST_CNT][CONF_EV_CNT] = {
/*                               NONE,                RECEIVED_SWRESET_CNF,         RECEIVED_G3LIBSET_CNF,          RECEIVED_DBGTOOL_CNF,			    RECEIVED_RFCONFIGSET_CNF,               RECEIVED_SRVSTOP_CNF,			  RECEIVED_SRVSTART_CNF,             */
/* WAIT_SWRESET_CNF          */ {g3_conf_fsm_default, g3_conf_fsm_set_attribute, 	g3_conf_fsm_default,			g3_conf_fsm_default,            	g3_conf_fsm_default,        			g3_conf_fsm_default,        	  g3_conf_fsm_default				 },
/* WAIT_G3LIBSET_CNF         */ {g3_conf_fsm_default, g3_conf_fsm_default,        	g3_conf_fsm_set_attribute,		g3_conf_fsm_default,				g3_conf_fsm_default,            		g3_conf_fsm_default,        	  g3_conf_fsm_default        		 },
/* WAIT_DBGTOOL_CNF          */ {g3_conf_fsm_default, g3_conf_fsm_default,        	g3_conf_fsm_default,			g3_conf_fsm_received_dbgtool_cnf,	g3_conf_fsm_default, 					g3_conf_fsm_default,        	  g3_conf_fsm_default        		 },
/* WAIT_RFCONFIGSET_CNF      */ {g3_conf_fsm_default, g3_conf_fsm_default,        	g3_conf_fsm_default,			g3_conf_fsm_default,				g3_conf_fsm_received_rfconfigset_cnf,	g3_conf_fsm_default,        	  g3_conf_fsm_default        		 },
#if IS_COORD
/* WAIT_SRVSTOP_CNF          */ {g3_conf_fsm_default, g3_conf_fsm_default,        	g3_conf_fsm_default,			g3_conf_fsm_default,				g3_conf_fsm_default,            		g3_conf_fsm_received_srvstop_cnf, g3_conf_fsm_default      		     },
/* WAIT_SRVSTART_CNF         */ {g3_conf_fsm_default, g3_conf_fsm_default,        	g3_conf_fsm_default,			g3_conf_fsm_default,				g3_conf_fsm_default,            		g3_conf_fsm_default,        	  g3_conf_fsm_received_srvstart_cnf  }
#endif /* IS_COORD */
};

/* Private functions */

#if (DEBUG_G3_CONF >= DEBUG_LEVEL_FULL)
/**
  * @brief Function that translates an attribute of the G3 Configuration FSM to a string.
  * @param attribute Structure of the attribute to translate.
  * @return Pointer to a string representing the attribute of the G3 Configuration FSM.
  */
static char* g3_conf_translate_attribute(G3_LIB_PIB_ID_t attribute)
{
    switch(attribute.id)
    {
	case MAC_KEYTABLE_ID:			return "MAC_KEYTABLE";
    case MAC_PANID_ID:				return "MAC_PANID";
    case MAC_SHORTADDRESS_ID:		return "MAC_SHORTADDRESS";
	case ADP_ACTIVEKEYINDEX_ID:		return "ADP_ACTIVEKEYINDEX";
    case ADP_COORDSHORTADDRESS_ID:	return "ADP_COORDSHORTADDRESS";
    case ADP_EAPPSKKEY_ID:			return "ADP_EAPPSKKEY";
    case ADP_LASTGASP_ID:			return "ADP_LASTGASP";
    case G3_LIB_RTEGPIO_ID:			return "G3_LIB_RTEGPIO";
		/* Add more... */
    default:						return "UNKNOWN_ATTRIBUTE";
    }
}
#endif

/**
  * @brief Completes the configuration.
  * @param None
  * @return The next state of the G3 Configuration FSM (the starting one).
  */
static g3_conf_state_t g3_conf_complete(void)
{
	g3_conf_fsm_info.g3_ready = true;

	if (working_plc_mode == PLC_MODE_MAC)
	{
#if defined(DEBUG)
		PRINT("DEBUG MODE\n\n");
#endif /* defined(DEBUG) */
		PRINT("Kit name: %s\n", EVALKIT_NAME);
#if defined(STM32G070xx)
		PRINT("STM32G070 FW version: %u.%u.%u\n", FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_SUB);
#elif defined(STM32G474xx)
		PRINT("STM32G474 FW version: %u.%u.%u\n", FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_SUB);
#elif defined(STM32L476xx)
		PRINT("STM32L476 FW version: %u.%u.%u\n", FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_SUB);
#else
		PRINT("STM32 FW version: %u.%u.%u\n", FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_SUB);
#endif
		PRINT("Bandplan: %s\n", hi_boot_sap_translate_bandplan(working_plc_band));
		PRINT("PAN ID: %X\n", PAN_ID);

		ALLOC_STATIC_HEX_STRING(mac_address_str, mac_address, MAC_ADDR64_SIZE);
		PRINT("MAC address: %s\n", mac_address_str);

		/* Role not relevant in MAC mode */

#if ENABLE_MODBUS_TEST
		UserModbus_start();
#endif /* ENABLE_MODBUS_TEST */

		if (modbus_role == modbus_master)
		{
			PRINT("DUT: MAC test ready, press the ");
			PRINT_COLOR_NOTS("BLUE", color_blue);
			PRINT_NOTS(" push-button or enter the DUT extended address to start\n");
			PRINT("Format: EXT_ADDR.PLCRF|PLC|RF.MSG_N\n");
		}
		else
		{
			PRINT("Tester: MAC test ready, please start it from the DUT\n");

#if ENABLE_MODBUS_TEST
			UserModbus_exec();
#endif /* ENABLE_MODBUS_TEST */
		}
	}
#if !IS_COORD && ENABLE_BOOT_CLIENT_ON_HOST
	else
	{
		/* Starts the Boot Client */
		g3_app_boot_clt_start();
	}
#endif

	return CONF_ST_WAIT_SWRESET_CNF;
}

/**
  * @brief G3 Configuration FSM function that maintains the current state, with no further action.
  * @param None
  * @return The next state of the G3 Configuration FSM (equal to the current one).
  */
static g3_conf_state_t g3_conf_fsm_default(void)
{
    g3_conf_fsm_info.curr_event = CONF_EV_NONE;

    return g3_conf_fsm_info.curr_state;
}

/**
  * @brief G3 Configuration FSM function that sets another attribute of the list.
  * @param None
  * @return The next state of the G3 Configuration FSM.
  */
static g3_conf_state_t g3_conf_fsm_set_attribute(void)
{
    g3_conf_state_t next_state;

    g3_conf_fsm_info.curr_event = CONF_EV_NONE;

	G3_LIB_SetAttributeRequest_t *set_attr_req = MEMPOOL_MALLOC(sizeof(G3_LIB_SetAttributeRequest_t));

	/* Extracts next attribute from table  */
	bool found_attribute = g3_app_attrib_tbl_extract(&set_attr_req->attribute);

	/* Sets the extracted attribute */
	if (found_attribute)
	{
#if (DEBUG_G3_CONF >= DEBUG_LEVEL_FULL)
		/* uint16 attributes shall be displayed swapped (MAC_PANID_ID, MAC_SHORTADDRESS_ID...)*/
		ALLOC_DYNAMIC_HEX_STRING(attribute_value_str, set_attr_req->attribute.value, set_attr_req->attribute.len);
		PRINT_G3_CONF_INFO("Setting attribute %s = 0x%s\n", g3_conf_translate_attribute(set_attr_req->attribute.attribute_id), attribute_value_str);
		FREE_DYNAMIC_HEX_STRING(attribute_value_str)
#endif
		/* Calculates message length, then sends it to the ST8500 */
		uint16_t len = sizeof(set_attr_req->attribute) - sizeof(set_attr_req->attribute.value) + set_attr_req->attribute.len;
		g3_send_message(HIF_TX_MSG, HIF_G3LIB_SET_REQ, set_attr_req, len);
	}
	else
	{
		MEMPOOL_FREE(set_attr_req);
	}


    if (found_attribute)
    {
        /* Need to wait for the setup of the next attribute, remains in the same state */
        next_state = CONF_ST_WAIT_SET_CNF;
    }
    else
    {
    	/* If there are no more attributes left to set */
    	hi_dbgtool_req_t *dbgtool_req = MEMPOOL_MALLOC(sizeof(hi_dbgtool_req_t));

    	uint16_t len = hi_hostif_dbgtoolreq_fill(dbgtool_req, HI_TOOL_INFO, HI_TOOL_NO_CONF);
    	g3_send_message(HIF_TX_MSG, HIF_HI_DBGTOOL_REQ, dbgtool_req, len);

    	next_state = CONF_ST_WAIT_DBGTOOL_CNF;
	}

    return next_state;
}


/**
  * @brief G3 Configuration FSM function that executes after the reception of a DBGTOOL confirmation.
  * @note The behaviour of this function depends on the device type, the version of the ST8500 FW
  * and the presence of the RF module.
  * @param None
  * @return The next state of the G3 Configuration FSM.
  */
static g3_conf_state_t g3_conf_fsm_received_dbgtool_cnf(void)
{
	g3_conf_fsm_info.curr_event = CONF_EV_NONE;

	g3_conf_state_t next_state;

	if (g3_conf_fsm_info.rf_connected)
	{
		uint32_t base_frequency;

		/* Sets different parameters, depending on the module type (868 or 915) and frequency */

		if (rf_type == RF_TYPE_915)
		{
			base_frequency = RF_PARAM_915_BASE_FREQ;
		}
		else
		{
			base_frequency = RF_PARAM_868_BASE_FREQ;
		}

		hif_rfconfigset_req_t *rfconfig_req = MEMPOOL_MALLOC(sizeof(hif_rfconfigset_req_t));

		uint16_t len = hi_hostif_rfconfigsetreq_fill(rfconfig_req, base_frequency, rf_type);
		g3_send_message(HIF_TX_MSG, HIF_HI_RFCONFIGSET_REQ, rfconfig_req, len);

		PRINT_G3_CONF_INFO("Configured RF with frequency %u Hz, power gain %d dBm\n", rfconfig_req->s2lp_configdata.RadioBaseFreq, rfconfig_req->s2lp_configdata.PowerdBm - RF_POWER_DBM_OFFSET);

		next_state = CONF_ST_WAIT_RFCONFIGSET_CNF;
	}
	else
	{
		PRINT_G3_CONF_WARNING("S2LP module is not connected, RF configuration skipped\n");

#if IS_COORD
		if ((working_plc_mode == PLC_MODE_IPV6_BOOT) || (working_plc_mode == PLC_MODE_IPV6_ADP))
		{
			/* In order to start a custom server, it is necessary to stop the default one first */
			g3_send_message(BOOT_SERVER_MSG_TYPE, HIF_BOOT_SRV_STOP_REQ, NULL, 0);

			next_state = CONF_ST_WAIT_SRV_STOP_CNF;
		}
		else
		{
			/* Device ha completed configuration */
			next_state = g3_conf_complete();
		}
#else
		/* Device ha completed configuration */
		next_state = g3_conf_complete();
#endif /* IS_COORD */
	}

	return next_state;
}

/**
  * @brief G3 Configuration FSM function that executes after the reception of a RFCONFIGSET confirmation.
  * @note The behavior of this function depends on the device type.
  * @param None
  * @return The next state of the G3 Configuration FSM.
  */
static g3_conf_state_t g3_conf_fsm_received_rfconfigset_cnf(void)
{
    g3_conf_state_t next_state;

    g3_conf_fsm_info.curr_event = CONF_EV_NONE;
#if IS_COORD
    if ((working_plc_mode == PLC_MODE_IPV6_BOOT) || (working_plc_mode == PLC_MODE_IPV6_ADP))
	{
		/* In order to start a custom server, it is necessary to stop the default one first */
    	g3_send_message(BOOT_SERVER_MSG_TYPE, HIF_BOOT_SRV_STOP_REQ, NULL, 0);

		next_state = CONF_ST_WAIT_SRV_STOP_CNF;
	}
    else
    {
    	/* Device ha completed configuration */
		next_state = g3_conf_complete();
    }
#else
	/* Device ha completed configuration */
	next_state = g3_conf_complete();
#endif /* IS_COORD */

    return next_state;
}

#if IS_COORD
/**
  * @brief G3 Configuration FSM function that executes after the reception of the SRVSTOP confirmation.
  * @param None
  * @return The next state of the G3 Configuration FSM.
  */
static g3_conf_state_t g3_conf_fsm_received_srvstop_cnf(void)
{
    g3_conf_fsm_info.curr_event = CONF_EV_NONE;

	BOOT_ServerStartRequest_t *srvstart_req = MEMPOOL_MALLOC(sizeof(sizeof(BOOT_ServerStartRequest_t)));

	uint16_t len = hi_boot_srvstartreq_fill(srvstart_req, BOOT_START_NORMAL, PAN_ID, COORD_ADDRESS);
	g3_send_message(BOOT_SERVER_MSG_TYPE, HIF_BOOT_SRV_START_REQ, srvstart_req, len);

	return CONF_ST_WAIT_SRV_START_CNF;
}

/**
  * @brief G3 Configuration FSM function that executes after the reception of the SRVSTART confirmation.
  * @param None
  * @return The next state of the G3 Configuration FSM
  */
static g3_conf_state_t g3_conf_fsm_received_srvstart_cnf(void)
{
    g3_conf_fsm_info.curr_event = CONF_EV_NONE;

    /* Device ha completed configuration */
    return g3_conf_complete();
}

#endif /* IS_COORD */

/**
  * @brief Function that handles the reception of a SWRESET confirmation.
  * @param payload Pointer to the payload of the received message.
  * @retval None
  */
static void g3_conf_handle_swreset_cnf(const void *payload)
{
#if (DEBUG_G3_CONF >= DEBUG_LEVEL_CRITICAL)
	const G3_LIB_SWResetConfirm_t *sw_reset_cnf = payload;
    HANDLE_CNF_ERROR(HIF_G3LIB_SWRESET_CNF, sw_reset_cnf->status);
#else
    UNUSED(payload);
#endif

    g3_conf_fsm_info.curr_event = CONF_EV_RECEIVED_SWRESET_CNF;
}

/**
  * @brief Function that handles the reception of a G3LIB-SET.Confirm.
  * @param payload Pointer to the payload of the received message.
  * @retval None
  */
static void g3_conf_handle_set_cnf(const void *payload)
{
#if (DEBUG_G3_CONF >= DEBUG_LEVEL_CRITICAL)
	const G3_LIB_SetAttributeConfirm_t *set_attr_cnf = payload;
	HANDLE_CNF_ERROR(HIF_G3LIB_SET_CNF, set_attr_cnf->status);
#else
	UNUSED(payload);
#endif

    g3_conf_fsm_info.curr_event = CONF_EV_RECEIVED_SET_CNF;
}

/**
  * @brief Function that handles the reception of a HOSTIF-DBGTOOL.Confirm.
  * @param payload Pointer to the payload of the received message.
  * @retval None
  */
static void g3_conf_handle_dbgtool_cnf(const void *payload)
{
	const hi_dbgtool_cnf_t *hi_dbg_tools_cnf = payload;

	g3_conf_fsm_info.curr_event = CONF_EV_RECEIVED_DBGTOOL_CNF;

	g3_conf_fsm_info.peVersion	  = hi_dbg_tools_cnf->peVersion;
	g3_conf_fsm_info.rf_connected = hi_dbg_tools_cnf->RfConf;
	memcpy(mac_address, hi_dbg_tools_cnf->eui64, sizeof(mac_address));

	/* MAC address needs to be reversed */
	utils_reverse_array(mac_address, sizeof(mac_address));
}

/**
  * @brief Function that handles the reception of a RFCONFIGSET confirmation.
  * @param payload Pointer to the payload of the received message.
  * @retval None.
  */
static void g3_conf_handle_rfconfigset_cnf(const void *payload)
{
#if (DEBUG_G3_CONF >= DEBUG_LEVEL_CRITICAL)
    const hif_rfconfigset_cnf_t *rfconfigset_cnf = payload;
    HANDLE_CNF_ERROR(HIF_HI_RFCONFIGSET_CNF, rfconfigset_cnf->status);
#else
    UNUSED(payload);
#endif

    g3_conf_fsm_info.curr_event = CONF_EV_RECEIVED_RFCONFIGSET_CNF;
}

#if IS_COORD

/**
  * @brief Function that handles the reception of a SRVSTART confirmation.
  * @param payload Pointer to the payload of the received message.
  * @retval None
  */
static void g3_conf_handle_srvstart_cnf(const void *payload)
{
#if (DEBUG_G3_CONF >= DEBUG_LEVEL_CRITICAL)
	const BOOT_ServerStartConfirm_t *srv_start_cnf = payload;
    HANDLE_CNF_ERROR(HIF_BOOT_SRV_START_CNF, srv_start_cnf->status);
#else
    UNUSED(payload);
#endif

    g3_conf_fsm_info.curr_event = CONF_EV_RECEIVED_SRV_START_CNF;
}

/**
  * @brief Function that handles the reception of a SRVSTOP confirmation.
  * @param payload Pointer to the payload of the received message.
  * @retval None
  */
static void g3_conf_handle_srvstop_cnf(const void *payload)
{
#if (DEBUG_G3_CONF >= DEBUG_LEVEL_CRITICAL)
	const BOOT_ServerStopConfirm_t *srv_stop_cnf = payload;
	HANDLE_CNF_ERROR(HIF_BOOT_SRV_STOP_CNF, srv_stop_cnf->status);
#else
	UNUSED(payload);
#endif

    g3_conf_fsm_info.curr_event = CONF_EV_RECEIVED_SRV_STOP_CNF;
}

#endif /* IS_COORD */

/**
  * @brief Function that handles the FSM of the initial configuration of the device.
  * @param None
  * @retval None
  */
static void g3_conf_fsm_manager(void)
{
    g3_conf_fsm_info.curr_state = g3_conf_fsm_func_tbl[g3_conf_fsm_info.curr_state][g3_conf_fsm_info.curr_event]();
}

/**
  * @}
  */

/** @addtogroup G3_App_Config_Exported_Code
  * @{
  */

char* g3_app_translate_g3_result(g3_result_t g3_result)
{
	switch(g3_result)
	{
	case G3_SUCCESS: 					return "SUCCESS";
	case G3_WRONG_CRC: 					return "WRONG_CRC";
	case G3_WRONG_MSG_LEN: 				return "WRONG_MSG_LEN";
	case G3_WRONG_CMD_ID: 				return "G3_WRONG_CMD_ID";

	case G3_WRONG_MODE: 				return "WRONG_MODE";
	case G3_NOT_EXPECTED: 				return "NOT_EXPECTED";
	case G3_WRONG_STATE: 				return "WRONG_STATE";
#if 0
	case G3_WRONG_TRX_STATE: 			return "WRONG_TRX_STATE";
#endif
	case G3_NOT_ACCEPTABLE: 			return "NOT_ACCEPTABLE";
#if 0
	case G3_WRONG_TX_POWER: 			return "WRONG_TX_POWER";
	case G3_WRONG_MOD_SCHEME: 			return "WRONG_MOD_SCHEME";
	case G3_WRONG_MOD_TYPE: 			return "WRONG_MOD_TYPE";
	case G3_WRONG_PREEMPHASIS: 			return "WRONG_PREEMPHASIS";
	case G3_WRONG_TONEMAP: 				return "WRONG_TONEMAP";
	case G3_WRONG_TONEMASK: 			return "WRONG_TONEMASK";
	case G3_WRONG_FCH: 					return "WRONG_FCH";
	case G3_WRONG_VALUE_LEN: 			return "WRONG_VALUE_LEN";
	case G3_WRONG_TEST_MODE: 			return "WRONG_TEST_MODE";
	case G3_QUEUE_FULL: 				return "QUEUE_FULL";
#endif
	case G3_FAILED: 					return "FAILED";
#if 0
	case G3_TX_BUSY: 					return "TX_BUSY";
	case G3_RX_BUSY: 					return "RX_BUSY";
	case G3_PREVIOUS_REQUEST_FAILED: 	return "PREVIOUS_REQUEST_FAILED";
	case G3_NO_INDICATION: 				return "NO_INDICATION";
	case G3_WRONG_VALUE: 				return "WRONG_VALUE";
	case G3_WRONG_ATTR_NUM: 			return "WRONG_ATTR_NUM";
	case G3_WRONG_DT: 					return "WRONG_DT";
	case G3_RX_NACK: 					return "RX_NACK";
	case G3_TX_QUEUE_TO_SHORT: 			return "TX_QUEUE_TO_SHORT";
#endif
	case G3_INTERNAL_ERROR: 			return "INTERNAL_ERROR";
	case G3_NOT_IDLE: 					return "NOT_IDLE";
	case G3_WRONG_BAND: 				return "WRONG_BAND";
	case G3_NOT_SUPPORTED_BAND: 		return "NOT_SUPPORTED_BAND";
	case G3_NOT_ACCEPTABLE_LEN: 		return "NOT_ACCEPTABLE_LEN";
	case G3_PLC_DISABLED: 				return "PLC_DISABLED";
	case G3_WRONG_LEN: 					return "WRONG_LEN";
	case G3_BUSY: 						return "BUSY";
	case G3_INVALID_IPv6_FRAME: 		return "INVALID_IPv6_FRAME";
	case G3_INVALID_QOS: 				return "INVALID_QOS";

	case G3_ROUTE_ERROR:				return "ROUTE_ERROR";
#if 0
	case G3_BT_TABLE_FULL:				return "BT_TABLE_FULL";
	case G3_FRAME_NOT_BUFFERED:			return "FRAME_NOT_BUFFERED";
	case G3_STARTUP_FAILURE: 			return "STARTUP_FAILURE";
	case G3_NOT_PERMITTED: 				return "NOT_PERMITTED";
	case G3_UNKNOWN_DEVICE: 			return "UNKNOWN_DEVICE";
	case G3_PARAMETER_ERROR: 			return "PARAMETER_ERROR";
	case G3_WRONG_DEVICE_TYPE: 			return "WRONG_DEVICE_TYPE";
	case G3_MALLOC_FAIL: 				return "MALLOC_FAIL";
	case G3_RTEIPC_ERROR: 				return "RTEIPC_ERROR";
	case G3_WRONG_MEDIA_TYPE: 			return "WRONG_MEDIA_TYPE";
	case G3_UNAVAILABLE_MEDIA_TYPE: 	return "UNAVAILABLE_MEDIA_TYPE";
#endif
	case G3_DISABLED_MEDIA_TYPE: 		return "DISABLED_MEDIA_TYPE";
	case G3_JOINING_DECLINE: 			return "JOINING_DECLINE";
	case G3_JOINING_TIMEOUT: 			return "JOINING_TIMEOUT";
#if 0
	case G3_COUNTER_ERROR: 				return "COUNTER_ERROR";
	case G3_IMPROPER_KEY_TYPE: 			return "IMPROPER_KEY_TYPE";
	case G3_IMPROPER_SECURITY_LEVEL:	return "IMPROPER_SECURITY_LEVEL";
	case G3_UNSUPPORTED_LEGACY:			return "UNSUPPORTED_LEGACY";
	case G3_UNSUPPORTED_SECURITY: 		return "UNSUPPORTED_SECURITY";
	case G3_BEACON_LOSS: 				return "BEACON_LOSS";
	case G3_CHANNEL_ACCESS_FAILURE: 	return "CHANNEL_ACCESS_FAILURE";
	case G3_DENIED: 					return "DENIED";
	case G3_DISABLE_TRX_FAILURE: 		return "DISABLE_TRX_FAILURE";
	case G3_SECURITY_ERROR: 			return "SECURITY_ERROR";
	case G3_FRAME_TOO_LONG: 			return "FRAME_TOO_LONG";
	case G3_INVALID_HANDLE: 			return "INVALID_HANDLE";
#endif
	case G3_INVALID_PARAMETER: 			return "INVALID_PARAMETER";
	case G3_NO_ACK: 					return "NO_ACK";
	case G3_NO_BEACON: 					return "NO_BEACON";
	case G3_NO_DATA: 					return "NO_DATA";
	case G3_NO_SHORT_ADDRESS: 			return "NO_SHORT_ADDRESS";
	case G3_PAN_ID_CONFLICT: 			return "PAN_ID_CONFLICT";
	case G3_REALIGNMENT: 				return "REALIGNMENT";

	case G3_TRANSACTION_EXPIRED: 		return "TRANSACTION_EXPIRED";
	case G3_TRANSACTION_OVERFLOW: 		return "TRANSACTION_OVERFLOW";
#if 0
	case G3_TX_ACTIVE: 					return "TX_ACTIVE";
	case G3_UNAVAILABLE_KEY: 			return "UNAVAILABLE_KEY";
	case G3_UNSUPPORTED_ATTRIBUTE: 		return "UNSUPPORTED_ATTRIBUTE";
	case G3_INVALID_ADDRESS: 			return "INVALID_ADDRESS";
	case G3_INVALID_INDEX: 				return "INVALID_INDEX";
	case G3_LIMIT_REACHED: 				return "LIMIT_REACHED";
	case G3_READ_ONLY: 					return "READ_ONLY";
#endif
 	case G3_SCAN_IN_PROGRESS: 			return "SCAN_IN_PROGRESS";
 	default: 							return "OTHER";
	}
}

/**
  * @brief Initializes the G3 configuration application.
  * @param None
  * @retval None
  */
void g3_app_conf_init(void)
{
    g3_conf_fsm_info.curr_event = CONF_EV_NONE;
	g3_conf_fsm_info.curr_state = CONF_ST_WAIT_SWRESET_CNF;

	g3_conf_fsm_info.peVersion = 0x00000000;
	g3_conf_fsm_info.rf_connected = false;
	g3_conf_fsm_info.g3_ready = false;
}

/**
  * @brief Starts the G3 configuration application in a specified mode (working_plc_mode).
  * @param None
  * @retval None
  */
void g3_app_conf_start(void)
{
	/* Sends SW reset request, selecting:
	 * - the bandplan (Cenelec A, Cenelec B or FCC),
	 * - the device type (coordinator or device),
	 * - the boot PLC mode */

	g3_app_attrib_tbl_init();

	bool necessary_attribute_present = false;

	if ((working_plc_mode == PLC_MODE_IPV6_BOOT) || (working_plc_mode == PLC_MODE_IPV6_ADP))
	{
		/* Checks the presence of mandatory attributes inside the attribute table */
#if IS_COORD
		necessary_attribute_present  = g3_app_attrib_tbl_exists(MAC_PANID_ID, 0);
		necessary_attribute_present &= g3_app_attrib_tbl_exists(MAC_SHORTADDRESS_ID, 0);
#else
	   necessary_attribute_present = g3_app_attrib_tbl_exists(ADP_EAPPSKKEY_ID, 0);
#endif
	}
	else if (working_plc_mode == PLC_MODE_MAC)
	{
		necessary_attribute_present  = g3_app_attrib_tbl_exists(MAC_PANID_ID, 0);
	}

	/* There should be at least MAC_PANID_ID and MAC_SHORTADDRESS_ID for the coordinator and ADP_EAPPSKKEY_ID for the device */
	assert(necessary_attribute_present);

	g3_conf_fsm_info.g3_ready = false;

	G3_LIB_SWResetRequest_t	*swreset_req = MEMPOOL_MALLOC(sizeof(G3_LIB_SWResetRequest_t));

    uint16_t len = hi_g3lib_swresetreq_fill(swreset_req, working_plc_band, PLC_DEVICE_TYPE, working_plc_mode);
    g3_send_message(HIF_TX_MSG, HIF_G3LIB_SWRESET_REQ, swreset_req, len);
}

/**
  * @brief G3 configuration task routine.
  * @param None
  * @retval None
  */
void g3_app_conf(void)
{
	g3_conf_fsm_manager();
}

/**
  * @brief Checks if a message is needed by the G3 Configuration application.
  * @param g3_msg Pointer to the G3 message structure to evaluate
  * @return 'true' if the message is needed, 'false' otherwise.
  */
bool g3_app_conf_msg_needed(const g3_msg_t *g3_msg)
{
    switch (g3_msg->command_id)
    {
    case HIF_HI_DBGTOOL_CNF:
    case HIF_HI_RFCONFIGSET_CNF:
    case HIF_G3LIB_SET_CNF:
    case HIF_G3LIB_SWRESET_CNF:
#if IS_COORD
    case HIF_BOOT_SRV_START_CNF:
    case HIF_BOOT_SRV_STOP_CNF:
#endif /* IS_COORD */
        return true;
    default:
        return false;
    }
}

/**
  * @brief Handles message reception for the G3 Configuration application.
  * @param g3_msg Pointer to the G3 message structure
  * @retval None
  */
void g3_app_conf_msg_handler(const g3_msg_t *g3_msg)
{
    switch (g3_msg->command_id)
    {
    case HIF_HI_DBGTOOL_CNF:
    	g3_conf_handle_dbgtool_cnf(g3_msg->payload);
        break;
    case HIF_HI_RFCONFIGSET_CNF:
        g3_conf_handle_rfconfigset_cnf(g3_msg->payload);
        break;
    case HIF_G3LIB_SET_CNF:
        g3_conf_handle_set_cnf(g3_msg->payload);
        break;
    case HIF_G3LIB_SWRESET_CNF:
        g3_conf_handle_swreset_cnf(g3_msg->payload);
        break;
#if IS_COORD
    case HIF_BOOT_SRV_START_CNF:
        g3_conf_handle_srvstart_cnf(g3_msg->payload);
        break;
    case HIF_BOOT_SRV_STOP_CNF:
        g3_conf_handle_srvstop_cnf(g3_msg->payload);
        break;
#endif /* IS_COORD */
    default:
        break;
    }
}

/**
  * @brief Returns the completion the G3 configuration application.
  * @param None
  * @retval True if the G3 configuration has completed its procedure, false otherwise.
  */
bool g3_app_conf_ready(void)
{
	return g3_conf_fsm_info.g3_ready;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
