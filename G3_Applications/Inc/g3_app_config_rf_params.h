/*****************************************************************************
*   @file    g3_app_config_rf_params.h
*   @author  AMG/IPC Application Team
*   @brief   This file contains the RF parameters structures.
*
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
*******************************************************************************/

#ifndef G3_APP_CONFIG_RF_PARAMS_H_
#define G3_APP_CONFIG_RF_PARAMS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Inclusions */
#include <settings.h>
#include <g3_app_config.h>

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
#define RF_PARAM_868_BASE_FREQ        	863100000
#define RF_PARAM_868_POWER_DBM        	35
#define RF_PARAM_868_IRQ_GPIO_PIN     	0x00
#define RF_PARAM_868_FEM_ENABLED      	0x00
#define RF_PARAM_868_FEM_GPIO_PIN_CSD 	0xFF
#define RF_PARAM_868_FEM_GPIO_PIN_CPS 	0xFF
#define RF_PARAM_868_FEM_GPIO_PIN_CTX 	0xFF


#if USE_STANDARD_ETSI_RF
#define RF_PARAM_915_BASE_FREQ        	863100000	/* In Hz */
#define RF_PARAM_915_POWER_DBM        	17			/* (17 - 31) dBm + 28 dB = +14 dBm */
#elif USE_STANDARD_FCC_RF
#define RF_PARAM_915_BASE_FREQ        	915000000	/* In Hz */
#define RF_PARAM_915_POWER_DBM        	30			/* (30 - 31) dBm + 28 dB = +27 dBm */
#endif

#define RF_PARAM_915_IRQ_GPIO_PIN     	0x03
#define RF_PARAM_915_FEM_ENABLED      	0x01
#define RF_PARAM_915_FEM_GPIO_PIN_CSD 	0x00
#define RF_PARAM_915_FEM_GPIO_PIN_CPS 	0x01
#define RF_PARAM_915_FEM_GPIO_PIN_CTX 	0x02

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

#endif /* G3_APP_CONFIG_RF_PARAMS_H_ */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
