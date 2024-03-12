/**
  ******************************************************************************
  * @file    passthrough.c
  * @author  AMG/IPC Application Team
  * @brief   Handler functions for the ST8500 GPIOs.
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
#include <spi.h>
#include <usart.h>
#include <main.h>
#include <passthrough.h>
#include <utils.h>

/** @addtogroup ST8500_Gpio_Management
  * @{
  */


/* Public functions */

/**
 * @brief  This function initializes and activates the passthough mode.
 * @param  None
 * @retval None
 */
void activatePassthrough(void)
{
	/* Const to ease portability */
	const IRQn_Type EXTI_SIDE_1_RX_IRQn = EXTI3_IRQn;
	const IRQn_Type EXTI_SIDE_2_RX_IRQn = EXTI15_10_IRQn;

	/* To enable the passthrough mode, we need to
	 * Deactivate all other peripherals
	 * Disable system TIM6 interrupt
	 * Reconfigure the GPIO pins into EXTI lines
	 */

	/* DeInitialize used peripherals */
	HAL_UART_MspDeInit(&huartHostIf);
	HAL_UART_MspDeInit(&huartUserIf);
	HAL_SPI_MspDeInit(&hspiSFlash);

	HAL_SuspendTick(); /* Slows down IT handling, system Tick must be disabled */

	GPIO_InitTypeDef pin_struct_in  = EXTI_RISE_FALL_PIN_STR(HIF_RX_Pin);

	/* Configure HIF/HOST RX pins as GPIO input (Rx) and EXTI pins (Tx) */
	HAL_GPIO_Init(HIF_RX_GPIO_Port, &pin_struct_in);

	pin_struct_in.Pin   = UIF_RX_Pin;
	HAL_GPIO_Init(UIF_RX_GPIO_Port, &pin_struct_in);

	/*Sets the Tx pin High as it is the UART "IDLE" state --> must be done before reconfiguring the GPIO */
	HAL_GPIO_WritePin(HIF_TX_GPIO_Port,  HIF_TX_Pin,  GPIO_PIN_SET);
	HAL_GPIO_WritePin(UIF_TX_GPIO_Port, UIF_TX_Pin, GPIO_PIN_SET);

	GPIO_InitTypeDef pin_struct_out = OUT_PIN_STR(HIF_TX_Pin);

	HAL_GPIO_Init(HIF_TX_GPIO_Port, &pin_struct_out);

	pin_struct_out.Pin   = UIF_TX_Pin;
	HAL_GPIO_Init(UIF_TX_GPIO_Port, &pin_struct_out);

	/* EXTI interrupt init for first side RX, maximum priority */
	HAL_NVIC_SetPriority(    EXTI_SIDE_1_RX_IRQn, 0, 0);
	HAL_NVIC_ClearPendingIRQ(EXTI_SIDE_1_RX_IRQn);
	HAL_NVIC_EnableIRQ(      EXTI_SIDE_1_RX_IRQn);

	/* EXTI interrupt init for second side RX, maximum priority */
	HAL_NVIC_SetPriority(    EXTI_SIDE_2_RX_IRQn, 0, 0);
	HAL_NVIC_ClearPendingIRQ(EXTI_SIDE_2_RX_IRQn);
	HAL_NVIC_EnableIRQ(      EXTI_SIDE_2_RX_IRQn);

	/* Waits for EXTI interrupts forever */
	for(;;)
	{
		__WFI();
	}
}

/**
  * @}
  */

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
