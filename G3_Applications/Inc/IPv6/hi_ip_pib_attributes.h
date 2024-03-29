/*****************************************************************************
*   @file    hi_ip_pib_attributes.h
*   @author  AMG/IPC Application Team
*   @brief   Header file for HI IP attributes.
*
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HI_IP_PIB_ATTRIBUTES_H
#define HI_IP_PIB_ATTRIBUTES_H

#include <stdint.h>
#include <hi_ip_pib_types.h>

/** @addtogroup HI_DRIVER ST8500 HI DRIVER
  * @{
  */

/** @defgroup hif_ip_drv HIF IP DRV
  * @{
  */

/** @defgroup IP_PIB_Attributes IP PIB Attributes
  * @brief IP PIB Attributes module
  * @details  This module contains the definition/handling of IP PIB Attributes, which are defined to serve IP functions.
  *           @n There's also an additional set of IP PIB Attributes, which are implementation specific.
  *           @n Below there's the description of each implemented PIB Attribute.
  * @{
  */

/** @defgroup IP_PIB_Attributes_TypesDefinitions IP PIB Attributes Types Definitions
  * @brief    IP PIB Attributes types definitions
  * @{
  */

/* G3-PLC PIB attribute ID definitions */
#define IP_IPV6ADDRESSPREFIX_ID         ((uint16_t)0x6000)  /**< @brief ipIpv6AddressPrefix Attribute: IPv6 Prefix */
#define IP_SRCPANID_ID                  ((uint16_t)0x6001)  /**< @brief ipSrcPanId Attribute: Define the PAN ID for the local COMET. */
#define IP_LOCALSHORTADDRESS_ID         ((uint16_t)0x6002)  /**< @brief ipLocalShortAddress Attribute: Source address of UDP connection and ICMP requests or replies  */
#define IP_LOCALPORT_ID                 ((uint16_t)0x6003)  /**< @brief ipLocalPort Attribute: Source port of UDP connection  */
#define IP_DSTPANID_ID                  ((uint16_t)0x6004)  /**< @brief ipDstPanId Attribute: Destination PAN ID of UDP connection */
#define IP_REMOTESHORTADDRESS_ID        ((uint16_t)0x6005)  /**< @brief ipRemoteShortAddress Attribute: Destination address of UDP connection*/
#define IP_REMOTEPORT_ID                ((uint16_t)0x6006)  /**< @brief ipRemotePort Attribute: Destination port of UDP connection  */
#define IP_MULTICASTADDRESS_ID          ((uint16_t)0x6007)  /**< @brief ipMultiCast Attribute: 4 Multicast addresses */
#define IP_UDPECHOONOFF_ID              ((uint16_t)0x6008)  /**< @brief ipEchoOnOff Attribute: Switch to enable the UDP echo responder */

#define IP_RANGE_MASK                   ((uint16_t)0xF000)  /**< @brief ipEchoOnOff Attribute: Switch to enable the UDP echo responder */
#define IP_RANGE_PARAMETERS             ((uint16_t)0x6000)  /**< @brief ipEchoOnOff Attribute: Switch to enable the UDP echo responder */

#define IP_VECT_ATTRIBUTEVALUE_LEN       ((uint8_t)16)   /**< @brief Length (in bytes) of a vectorial PIB Attribute */

// SAP Interface Macros
#define IP_PIB_SUCCESS                  ((uint8_t)0x00)  /**< @brief Operation on PIB correctly performed */
#define IP_PIB_UNSUPPORTEDATTRIBUTE     ((uint8_t)0x01)  /**< @brief Operation on PIB cannot be performed for unsupported attribute */
#define IP_PIB_READONLY                 ((uint8_t)0x02)  /**< @brief Operation on PIB cannot be performed for read only parameter */
#define IP_PIB_INVALIDPARAMETER         ((uint8_t)0x03)  /**< @brief Operation on PIB cannot be performed for invalid parameter */
#define IP_PIB_INVALIDINDEX             ((uint8_t)0x04)  /**< @brief Operation on PIB cannot be performed for invalid index */
#define IP_PIB_FAILED                   ((uint8_t)0xFF)  /**< @brief Operation on PIB failed */

// Internal Interface Macros
#define IP_PIBTABLE_ENTRY_FOUND     ((uint8_t)0x00)  /**< @brief Short Address found in the table */
#define IP_PIBTABLE_ENTRY_NOTFOUND  ((uint8_t)0x01)  /**< @brief Short Address not found in the table */

#define IP_EXTMODE_ERROR                ((uint8_t)0x00)  /**< @brief Extended Mode: bad value  */
#define IP_EXTMODE_IPV6                 ((uint8_t)0x01)  /**< @brief Extended Mode: IPv6 stack  */
#define IP_EXTMODE_HI                   ((uint8_t)0x02)  /**< @brief Extended Mode: Host Interface  */


/**
  * @brief  Used only to get the max length of an attribute
  */
typedef union
{
    uint8_t                     Vect[IP_VECT_ATTRIBUTEVALUE_LEN]; /**< @brief General buffer for the value */
    IP_Addr128_t                MulticastEntry;   /**< @brief buffer for the Multicast Table entry */
    IP_Addr128_t                Ipv6PrefixEntry;   /**< @brief buffer for the Multicast Table entry */
} IP_PIBStructsType;


/**< @brief Maximum size of the value for one ADP Attribute */
#define IP_MAX_ATTRIBUTEVALUE_LEN  ((uint16_t)sizeof(IP_PIBStructsType)) /**< @brief Maximum size of one value in the ADP PIB  */

/**
  * @brief  IP PIB Attribute Values set
  */
typedef union
{
  uint32_t  Value32;                              /**< @brief 32-bit unsigned value option */
  uint16_t  Value16;                              /**< @brief 16-bit unsigned value option  */
  uint8_t   Value8;                               /**< @brief 8-bit unsigned value option  */
  int8_t    ValueS8;                              /**< @brief 8-bit signed value option  */
} IP_Value_t;

/**
  * @brief  ADP PIB Attribute generic structure
  */
typedef struct
{
  uint16_t          Identifier;    /**< @brief PIB Attribute Id */
  uint8_t           ReadOnly;      /**< @brief Read-Only on/off property */
  uint8_t           Type;          /**< @brief PIB Attribute value type (8-16-32-64 bit or more, signed/unsigned) */
  uint8_t           ValueLen;      /**< @brief PIB Attribute value len */
  IP_Value_t        Value;         /**< @brief PIB Attribute value */
} IP_PIBAttribute_t;

/**
  * @brief  ADP PIB Attribute generic structure for List Attributes
  */
typedef struct
{
  uint16_t          Identifier;    /**< @brief PIB Attribute Id */
  uint8_t           ReadOnly;      /**< @brief Read-Only on/off property */
  uint8_t           Type;          /**< @brief PIB Attribute value type (8-16-32-64 bit or more, signed/unsigned) */
  uint8_t           ValueLen;      /**< @brief PIB Attribute value len */
  IP_Addr128_t      Value;         /**< @brief PIB Attribute value */
} IP_PIBAttribute128_t;


/**
  * @brief  IP PIB Attribute information to use in IP-SAP commands
  */
typedef struct
{
  uint32_t   PIBAttributeId;                                 /**< @brief PIB Attribute Id */
  uint16_t   PIBAttributeIndex;                              /**< @brief PIB Attribute index (valid only for List Attributes) */
  uint16_t   PIBAttributeValueLen;                           /**< @brief PIB Attribute value len */
  uint8_t    PIBAttributeValue[IP_MAX_ATTRIBUTEVALUE_LEN];  /**< @brief PIB Attribute value */
} IP_PIBAttributeInfo_t;


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* HI_IP_PIB_ATTRIBUTES_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
