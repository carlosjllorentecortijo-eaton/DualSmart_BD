/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define huartHostIf huart2
#define hspiSFlash hspi3
#define htimSys htim11
#define huartUserIf huart1
#define ST8500_RESET_N_Pin GPIO_PIN_0
#define ST8500_RESET_N_GPIO_Port GPIOA
#define LP_MODE_N_Pin GPIO_PIN_1
#define LP_MODE_N_GPIO_Port GPIOA
#define HIF_TX_Pin GPIO_PIN_2
#define HIF_TX_GPIO_Port GPIOA
#define HIF_RX_Pin GPIO_PIN_3
#define HIF_RX_GPIO_Port GPIOA
#define BOOT0_Pin GPIO_PIN_4
#define BOOT0_GPIO_Port GPIOA
#define BOOT1_Pin GPIO_PIN_5
#define BOOT1_GPIO_Port GPIOA
#define BOOT2_Pin GPIO_PIN_6
#define BOOT2_GPIO_Port GPIOA
#define STM32_MODE_Pin GPIO_PIN_1
#define STM32_MODE_GPIO_Port GPIOB
#define UIF_TX_Pin GPIO_PIN_9
#define UIF_TX_GPIO_Port GPIOA
#define UIF_RX_Pin GPIO_PIN_10
#define UIF_RX_GPIO_Port GPIOA
#define SYS_SWDIO_Pin GPIO_PIN_13
#define SYS_SWDIO_GPIO_Port GPIOA
#define SYS_SWCLK_Pin GPIO_PIN_14
#define SYS_SWCLK_GPIO_Port GPIOA
#define SFLASH_CS_N_Pin GPIO_PIN_15
#define SFLASH_CS_N_GPIO_Port GPIOA
#define eFlash_SCK_Pin GPIO_PIN_3
#define eFlash_SCK_GPIO_Port GPIOB
#define eFlash_MISO_Pin GPIO_PIN_4
#define eFlash_MISO_GPIO_Port GPIOB
#define eFlash_MOSI_Pin GPIO_PIN_5
#define eFlash_MOSI_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
