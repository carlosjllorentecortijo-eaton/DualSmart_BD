/*****************************************************************************
*   @file    g3_app_config.h
*   @author  AMG/IPC Application Team
*   @brief   Header file that contains declarations for G3 configuration functionalities.
*
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
*******************************************************************************/

#ifndef G3_APP_CONFIG_H_
#define G3_APP_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup G3_App_Config G3 Configuration Application
  * @{
  */

/**
  * @}
  */

/** @defgroup G3_App_Config_Private_Code Private Code
  * @{
  */

/**
  * @}
  */

/** @defgroup G3_App_Config_Exported_Code Exported Code
  * @{
  */

/**
  * @}
  */

/* Inclusions */
#include <stdint.h>
#include <stdbool.h>
#include <g3_comm.h>
#include <hi_boot_sap_interface.h>

/** @addtogroup G3_App
  * @{
  */

/** @addtogroup G3_App_Config
  * @{
  */

/** @addtogroup G3_App_Config_Exported_Code
  * @{
  */

/* Definitions */

/* Define the RF type names */
#define RF_TYPE_STRING_915		"915 MHz"
#define RF_TYPE_STRING_868		"868 MHz"


#define RF_TYPE_STRING(rf_type)		(rf_type == RF_TYPE_915) ? RF_TYPE_STRING_915 : RF_TYPE_STRING_868

/* 868 minimum/maximum frequency */
#define RF_868_FREQ_MIN             863000000
#define RF_868_FREQ_MAX             870000000

/* 915 minimum/maximum frequency */
#define RF_915_FREQ_MIN             860000000
#define RF_915_FREQ_MAX             940000000

/* Public Functions */
char* g3_app_translate_g3_result(g3_result_t g3_result);

void g3_app_conf_init(void);
void g3_app_conf_start(void);
void g3_app_conf(void);

bool g3_app_conf_msg_needed( const g3_msg_t *g3_msg);
void g3_app_conf_msg_handler(const g3_msg_t *g3_msg);

bool g3_app_conf_ready(void);

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

#endif /* G3_APP_CONFIG_H_ */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
