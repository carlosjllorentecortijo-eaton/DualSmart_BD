/**
  ******************************************************************************
  * @file    passthrough.h
  * @author  AMG/IPC Application Team
  * @brief   Header file for the ST8500 GPIOs handler functions.
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
#ifndef PASSTHROUGH_H_
#define PASSTHROUGH_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ST8500_Host_Passthrough ST8500 Host UART Passthrough
  * @{
  */

/**
  * @}
  */

/* Inclusions */
#include <pin_management.h>

/** @addtogroup ST8500_Host_Passthrough
  * @{
  */

/* Definitions */

/* Public functions */

/* Passthrough mode */
void activatePassthrough(void);

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PASSTHROUGH_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
