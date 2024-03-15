/*****************************************************************************
*   @file    g3_app_attrib_tbl.h
*   @author  AMG/IPC Application Team
*   @brief   Header file for the attribute table management.
*
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
*******************************************************************************/

#ifndef G3_APP_ATTRIB_TBL_H_
#define G3_APP_ATTRIB_TBL_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup G3_App_Attrib_Tbl G3 Attribute Table
  * @{
  */

/**
  * @}
  */

/** @defgroup G3_App_Attrib_Tbl_Private_Code Private Code
  * @{
  */

/**
  * @}
  */

/** @defgroup G3_App_Attrib_Tbl_Exported_Code Exported Code
  * @{
  */

/**
  * @}
  */

/* Inclusions */
#include <stdbool.h>
#include <hi_g3lib_attributes.h>

/** @addtogroup G3_App
  * @{
  */

/** @addtogroup G3_App_Attrib_Tbl
  * @{
  */

/** @addtogroup G3_App_Attrib_Tbl_Exported_Code
  * @{
  */

/* Attribute values */
#define PAN_ID          0x8C57	/* PAN ID to set */
#define COORD_ADDRESS   0x0000	/* Coordinator short address to set, must be set to 0 */

#define RTE_GPIO   		0x3931 /* Value used to use GPIO0_6 ad TX, GPIO0_7 as RX */

/* Default PSK value */
#define DEFAULT_PSK {	0xABU, 0x10U, 0x34U, 0x11U, \
						0x45U, 0x11U, 0x1BU, 0xC3U, \
						0xC1U, 0x2DU, 0xE8U, 0xFFU, \
						0x11U, 0x14U, 0x22U, 0x04U }

/* Default GMK value */
#define DEFAULT_GMK	{	0xAF, 0x4D, 0x6D, 0xCC, \
		                0xF1, 0x4D, 0xE7, 0xC1, \
						0xC4, 0x23, 0x5E, 0x6F, \
						0xEF, 0x6C, 0x15, 0x1F }

/* Default GMK index */
#define DEFAULT_GMK_INDEX	0

/* Public functions */
void 	 g3_app_attrib_tbl_init(void);
bool 	 g3_app_attrib_tbl_extract(G3_LIB_PIB_t *attr_data);
bool 	 g3_app_attrib_tbl_exists(uint32_t attribute_id, uint32_t attribute_index);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* G3_APP_ATTRIB_TBL_H_ */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
