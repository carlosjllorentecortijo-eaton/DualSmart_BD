/*****************************************************************************
 *   @file    g3_app_attrib_tbl.c
 *   @author  AMG/IPC Application Team
 *   @brief   This file contains the implementation of the attribute table management.
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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <utils.h>
#include <g3_app_attrib_tbl.h>
#include <hi_boot_sap_interface.h>

/** @addtogroup G3_App
 * @{
 */

/** @addtogroup G3_App_Attrib_Tbl
 * @{
 */

/** @addtogroup G3_App_Attrib_Tbl_Private_Code
 * @{
 */

/* Definitions */
#if IS_COORD
#define MAX_ATTRIBUTE_NUMBER    6	/*!< Maximum number of attributes that can be stored in the table */
#else
#define MAX_ATTRIBUTE_NUMBER    5	/*!< Maximum number of attributes that can be stored in the table */
#endif
#define DEFAULT_MAC_KEY  {	0xAFU, 0x4DU, 0x6DU, 0xCCU, \
						    0xF1U, 0x4DU, 0xE7U, 0xC1U, \
						    0xC4U, 0x23U, 0x5EU, 0x6FU, \
						    0xEFU, 0x6CU, 0x15U, 0x1FU	\
					      }	/*!< Default ST8500 MAC */

/* Custom types */

/* Attribute table type */
typedef struct g3_attribute_tbl_str
{
	uint32_t 		index;								/*!< Index of the next attribute to extract from the table */
	uint32_t 		attr_n;								/*!< Number of attributes stored in the table */
	G3_LIB_PIB_t 	attribute[MAX_ATTRIBUTE_NUMBER];	/*!< Attribute array */
} g3_attribute_tbl_t;

/**
 * @}
 */

/** @addtogroup G3_App_Attrib_Tbl_Exported_Code
 * @{
 */

/* External variables */
extern plc_mode_t	working_plc_mode;

/**
 * @}
 */

/** @addtogroup G3_App_Attrib_Tbl_Private_Code
 * @{
 */

/* Private variables */
static g3_attribute_tbl_t g3_attribute_tbl;             /*!<  Attribute table */

/* Private functions */

/**
 * @brief Builds the bit map for the G3 event notifications to enable.
 * @param None
 * @return the event notification enable bit map (64 bit integer).
 */
static uint64_t g3_attrib_tbl_build_event_notifications(void)
{
	uint64_t pe_event_indication = 0;

#if ENABLE_EVENTINDICATION_ERROR
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_ERROR;
#endif
#if ENABLE_EVENTINDICATION_GMK
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_GMK;
#endif
#if ENABLE_EVENTINDICATION_CONTEXT
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_CONTEXT;
#endif

	/* Bit 3 is reserved */

#if ENABLE_EVENTINDICATION_ACTKEY
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_ACTKEY;
#endif
#if ENABLE_EVENTINDICATION_PANID
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_PANID;
#endif
#if ENABLE_EVENTINDICATION_SHORTADDR
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_SHORTADDR;
#endif
#if ENABLE_EVENTINDICATION_THERMEV
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_THERMEV;
#endif
#if ENABLE_EVENTINDICATION_TMRTX
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_TMRTX;
#endif
#if ENABLE_EVENTINDICATION_TMRRX
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_TMRRX;
#endif
#if ENABLE_EVENTINDICATION_ROUTE
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_ROUTE;
#endif
#if ENABLE_EVENTINDICATION_PREQ
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_PREQ;
#endif
#if ENABLE_EVENTINDICATION_SURGEEV
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_SURGEEV;
#endif
#if ENABLE_EVENTINDICATION_RTEWARN
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_RTEWARN;
#endif
#if ENABLE_EVENTINDICATION_RTEPOLL
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_RTEPOLL;
#endif
#if ENABLE_EVENTINDICATION_BOOTMAXRETIES
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_BOOTMAXRETIES;
#endif
#if ENABLE_EVENTINDICATION_BANDMISMATCH
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_BANDMISMATCH;
#endif
#if ENABLE_EVENTINDICATION_PHY_RX_QI
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_PHYQUALITY_RX;
#endif
#if ENABLE_EVENTINDICATION_PHY_TX_QI
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_PHYQUALITY_TX;
#endif
#if ENABLE_EVENTINDICATION_MACUPDATE
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_MACUPDATE;
#endif
#if ENABLE_EVENTINDICATION_MEMLEAK
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_MEMLEAK;
#endif
#if ENABLE_EVENTINDICATION_TIMERERR
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_TIMERERR;
#endif
#if ENABLE_EVENTINDICATION_PHY_RX_RF_QI
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_PHYQUALITY_RX_RF;
#endif
#if ENABLE_EVENTINDICATION_PHY_TX_RF_QI
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_PHYQUALITY_TX_RF;
#endif
#if ENABLE_EVENTINDICATION_ADPDATAFORWARD
	pe_event_indication |= G3_LIB_PEEVENTINDICATION_ADPDATAFORWARD;
#endif

	return pe_event_indication;
}

/**
 * @brief Adds an attribute to the attribute table.
 * @param id ID field of the attribute.
 * @param index Index field of the attribute.
 * @param length Length of the attribute, in bytes.
 * @param value_ptr Pointer to the variable/array/structure containing the value to set for the attribute.
 * @return None
 */
static void g3_attrib_tbl_add(const uint32_t id, const uint16_t index, const uint16_t length, const uint8_t *value_ptr)
{
	/* Check that the table is not full */
	assert(g3_attribute_tbl.attr_n < MAX_ATTRIBUTE_NUMBER);

	/* Check attribute length */
	assert(length < G3_LIB_MAX_ATTR_LEN);

	g3_attribute_tbl.attribute[g3_attribute_tbl.attr_n].attribute_id.id    = id;
	g3_attribute_tbl.attribute[g3_attribute_tbl.attr_n].attribute_id.index = index;
	g3_attribute_tbl.attribute[g3_attribute_tbl.attr_n].len                = length;

	/* Must swap because the user uses MSB arrays/values,m while the request uses LSB arrays */
	memcpy(g3_attribute_tbl.attribute[g3_attribute_tbl.attr_n].value, value_ptr, length);

	g3_attribute_tbl.attr_n++;
}

/**
 * @brief Looks for an attribute with a specific ID and index in the attribute table.
 * @param id ID of the attribute to find in the table.
 * @param index Index of the attribute to find in the table.
 * @return Pointer to the desired attribute entry of the table, if the attribute was found, NULL otherwise.
 */
static const G3_LIB_PIB_t *g3_attrib_tbl_find(uint32_t id, uint32_t index)
{
	G3_LIB_PIB_t *attribute = NULL;

	for (uint32_t i = 0; i < g3_attribute_tbl.attr_n; i++)
	{
		if (	(g3_attribute_tbl.attribute[i].attribute_id.id    == id		) &&
				(g3_attribute_tbl.attribute[i].attribute_id.index == index	) )
		{
			attribute = &g3_attribute_tbl.attribute[i];
			break;
		}
	}

	return attribute;
}

/**
 * @}
 */

/** @addtogroup G3_App_Attrib_Tbl_Exported_Code
 * @{
 */

/**
 * @brief Initializes the attribute table, filling it with the attributes to set at start-up.
 * @param None
 * @retval None
 */
void g3_app_attrib_tbl_init(void)
{
	g3_attribute_tbl.attr_n = 0;
	g3_attribute_tbl.index  = 0;

	/* Converts from 16 bit integer to byte array */
	const uint8_t pan_id[] = {LOW_BYTE(PAN_ID), HIGH_BYTE(PAN_ID)};

	if ((working_plc_mode == PLC_MODE_IPV6_BOOT) || (working_plc_mode == PLC_MODE_IPV6_ADP))
	{
		/* Converts from 16 bit integer to byte array */
		const uint8_t coord_addr[] = {LOW_BYTE(COORD_ADDRESS), HIGH_BYTE(COORD_ADDRESS)};

#if IS_COORD
		const uint32_t modulation_Shceme_Broadcast = 0x00000CFF;
		const uint8_t active_gmk_index = 0;
		const uint8_t mac_key[MAC_KEY_SIZE] = DEFAULT_MAC_KEY;

		g3_attrib_tbl_add(MAC_PANID_ID,             	0, sizeof(pan_id),      				pan_id);
		g3_attrib_tbl_add(MAC_SHORTADDRESS_ID,      	0, sizeof(coord_addr),  				coord_addr);
		g3_attrib_tbl_add(MAC_MODULATIONCONTROL_ID,   	0, sizeof(modulation_Shceme_Broadcast),	(uint8_t*)&modulation_Shceme_Broadcast);
		g3_attrib_tbl_add(ADP_ACTIVEKEYINDEX_ID,		0, sizeof(active_gmk_index),  			&active_gmk_index);
		g3_attrib_tbl_add(MAC_KEYTABLE_ID,				0, sizeof(mac_key),						mac_key);

		/* Add more attributes only for coordinator (increase MAX_ATTRIBUTE_NUMBER if necessary)... */
#else
		const uint8_t default_psk[]  = DEFAULT_PSK; /* PSK value used to connect to the coordinator */
		const uint8_t stopRepeatBroadcastMsg = 0x52;
		const uint8_t enableTrickleData = 0x01;
		const uint8_t enableClusterTrickle = 0x01;

		/* Mandatory attributes */
		g3_attrib_tbl_add(ADP_EAPPSKKEY_ID,         	0, sizeof(default_psk), 		 	default_psk);
		g3_attrib_tbl_add(ADP_OPTIONALFEATURES_ID,      0, sizeof(stopRepeatBroadcastMsg),	&stopRepeatBroadcastMsg);
		g3_attrib_tbl_add(ADP_TRICKLEDATAENABLED_ID,    0, sizeof(enableTrickleData), 		&enableTrickleData);
		g3_attrib_tbl_add(ADP_CLUSTERTRICKLEENABLED_ID, 0, sizeof(enableClusterTrickle), 	&enableClusterTrickle);

		/* MAC_PANID_ID, MAC_SHORTADDRESS_ID, MAC_KEYTABLE_ID and ADP_ACTIVEKEYINDEX_ID must not be set on DEVICE side
		 * since they are acquired through the bootstrap procedure */

		/* Add more attributes only for device (increase MAX_ATTRIBUTE_NUMBER if necessary)... */
#endif /* IS_COORD */

		/* Add more attributes for coordinator and device in IPv6 BOOT/ADP mode... */
	}
	else if (working_plc_mode == PLC_MODE_MAC)
	{
		/* Mandatory attributes */
		g3_attrib_tbl_add(MAC_PANID_ID,             0, sizeof(pan_id),      pan_id);

		/* Add more attributes in MAC mode (increase MAX_ATTRIBUTE_NUMBER if necessary)... */
	}

	uint64_t pe_event_indication = g3_attrib_tbl_build_event_notifications();

	/* Converts from 64 bit integer to byte array */
	const uint8_t pe_event_indication_array[]     = {	TAKE_BYTE(pe_event_indication, 0),
			TAKE_BYTE(pe_event_indication, 1),
			TAKE_BYTE(pe_event_indication, 2),
			TAKE_BYTE(pe_event_indication, 3),
			TAKE_BYTE(pe_event_indication, 4),
			TAKE_BYTE(pe_event_indication, 5),
			TAKE_BYTE(pe_event_indication, 6),
			TAKE_BYTE(pe_event_indication, 7) };

	g3_attrib_tbl_add(G3_LIB_PEEVENTINDICATION_ID, 0, sizeof(pe_event_indication_array), pe_event_indication_array);

	/* Add more attributes in every mode (increase MAX_ATTRIBUTE_NUMBER if necessary)... */
}

/**
 * @brief Extracts an attribute from the attribute table.
 * @param attr_data Pointer to the structure where the extracted attribute shall be stored.
 * @return 'true' if the attribute is extracted from the table, 'false' otherwise.
 */
bool g3_app_attrib_tbl_extract(G3_LIB_PIB_t *attr_data)
{
	bool attribute_found = false;

	if (g3_attribute_tbl.index < g3_attribute_tbl.attr_n)
	{
		*attr_data = g3_attribute_tbl.attribute[g3_attribute_tbl.index++];
		attribute_found = true;
	}

	return attribute_found;
}

/**
 * @brief Checks if an attribute is present in the attribute table.
 * @param attribute_id ID of the desired attribute.
 * @param attribute_index Index of the desired attribute.
 * @return 'true' if the attribute is found, 'false' otherwise.
 */
bool g3_app_attrib_tbl_exists(uint32_t attribute_id, uint32_t attribute_index)
{
	const G3_LIB_PIB_t *attribute_ptr = g3_attrib_tbl_find(attribute_id, attribute_index);

	return (attribute_ptr != NULL);
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
