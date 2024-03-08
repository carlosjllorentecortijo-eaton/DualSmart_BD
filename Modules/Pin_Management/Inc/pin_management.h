/**
  ******************************************************************************
  * @file    pin_management.h
  * @author  AMG/IPC Application Team
  * @brief   Header file for the ST8500 GPIOs handler functions.
  @verbatim
  @endverbatim

  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PIN_MANAGEMENT_H_
#define PIN_MANAGEMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ST8500_Gpio_Management ST8500 GPIO Management
  * @{
  */

/**
  * @}
  */

/* Inclusions */
#include <stdint.h>
#include <stdbool.h>

/** @addtogroup ST8500_Gpio_Management
  * @{
  */

/* Definitions */
#define RESET_PULSE_DURATION	5	/* In ms */

/* Definitions */
#define BOOT_PIN_SETUP_WAIT	1	/* In ms */
#define BOOT_PIN_HOLD_WAIT	1	/* In ms */

/* Custom types */
typedef enum {
  STM32_BOOT_DEFAULT = 0,
  STM32_BOOT_PASSTHROUGH
} stm32_boot_mode_t;

typedef enum {
  ST8500_BOOT_FROM_UART = 0,
  ST8500_BOOT_FROM_SFLASH
} st8500_boot_mode_t;

/* Macros */

#define IN_PIN_STR(pin)				{	.Pin   = pin, 						\
										.Mode  = MODE_INPUT, 	 			\
										.Pull  = GPIO_NOPULL,  				\
										.Speed = GPIO_SPEED_FREQ_VERY_HIGH  \
									}

#define EXTI_RISE_FALL_PIN_STR(pin)	{											\
										.Pin   = pin, 							\
										.Mode  = GPIO_MODE_IT_RISING_FALLING, 	\
										.Pull  = GPIO_PULLUP, 					\
										.Speed = GPIO_SPEED_FREQ_VERY_HIGH 		\
									}

#define OUT_PIN_STR(pin)			{										\
										.Pin   = pin, 						\
										.Mode  = GPIO_MODE_OUTPUT_PP, 		\
										.Pull  = GPIO_NOPULL,				\
										.Speed = GPIO_SPEED_FREQ_VERY_HIGH 	\
									}

/* Public functions */

/* Switches for STM32/ST8500 boot modes */
stm32_boot_mode_t  readBootModeSTM32(void);
st8500_boot_mode_t readBootModeST8500(void);

/* ST8500 reset pin */
void assertResetOnST8500(void);
void deassertResetOnST8500(void);

/* ST8500 BOOT pins */
void setBootPinsAsInput(void);
void setBootPinsAsOutput(bool boot_st8500_from_uart);

/* Switches and configuration */
bool readRfSelect(void);
bool readFCCSelect(void);
bool readMacSelect(void);
bool readModbusMasterSelect(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PIN_MANAGEMENT_H_ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
