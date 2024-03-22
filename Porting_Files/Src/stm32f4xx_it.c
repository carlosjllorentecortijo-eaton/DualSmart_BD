/**
 * @file stm32f4xx_it.c
 * @author E0768084 (CarlosJLlorentCortijo@eaton.com)
 * @brief This file contains the functions related to the EXTI handlers that are called once the board is set to passthrough mode.
 * @version 0.1
 * @date 2024-03-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <main.h>

#pragma GCC optimize("-Ofast")

/* Passthrough handler functions */

/**
 * @brief This code needs to be as simple as possible, to maintain the execution agile 
 * 
 */
void EXTI15_10_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(UIF_RX_Pin) != 0x00u)
	{
		if(UIF_RX_GPIO_Port->IDR & UIF_RX_Pin)/*Rising IT*/
		{
			__HAL_GPIO_EXTI_CLEAR_IT(UIF_RX_Pin);
			HIF_TX_GPIO_Port->BSRR = HIF_TX_Pin; /*Set Pin*/
		}
		else if(!(UIF_RX_GPIO_Port->IDR & UIF_RX_Pin)) /*Falling IT*/
		{
			__HAL_GPIO_EXTI_CLEAR_IT(UIF_RX_Pin);
			HIF_TX_GPIO_Port->BSRR = (uint32_t)HIF_TX_Pin << 16U; /*Reset Pin*/
		}
	}
}

/**
 * @brief This code needs to be as simple as possible, to maintain the execution agile 
 * 
 */
#if IS_COORD
void EXTI3_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(HIF_RX_Pin) != 0x00u)
	{
		if(HIF_RX_GPIO_Port->IDR & HIF_RX_Pin) /*Rising IT*/
		{
			__HAL_GPIO_EXTI_CLEAR_IT(HIF_RX_Pin);
			UIF_TX_GPIO_Port->BSRR = UIF_TX_Pin;
		}
		else if (!(HIF_RX_GPIO_Port->IDR & HIF_RX_Pin)) /*Falling IT*/
		{
			__HAL_GPIO_EXTI_CLEAR_IT(HIF_RX_Pin);
			UIF_TX_GPIO_Port->BSRR = (uint32_t)UIF_TX_Pin << 16U; /*Reset Pin*/
		}
	}
}
#else
void EXTI9_5_IRQHandler(void)
{
	if (__HAL_GPIO_EXTI_GET_IT(HIF_RX_Pin) != 0x00u)
	{
		if(HIF_RX_GPIO_Port->IDR & HIF_RX_Pin) /*Rising IT*/
		{
			__HAL_GPIO_EXTI_CLEAR_IT(HIF_RX_Pin);
			UIF_TX_GPIO_Port->BSRR = UIF_TX_Pin;
		}
		else if (!(HIF_RX_GPIO_Port->IDR & HIF_RX_Pin)) /*Falling IT*/
		{
			__HAL_GPIO_EXTI_CLEAR_IT(HIF_RX_Pin);
			UIF_TX_GPIO_Port->BSRR = (uint32_t)UIF_TX_Pin << 16U; /*Reset Pin*/
		}
	}
}
#endif
