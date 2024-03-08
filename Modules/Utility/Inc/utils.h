/**
  ******************************************************************************
  * @file    utils.h
  * @author  AMG/IPC Application Team
  * @brief   utility functions
  *          This file provides some general utility functions.
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
  * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
  * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
  * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
  * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  *******************************************************************************/

#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Inclusions */
#include <stdint.h>
#include <stdbool.h>
#include <main.h>

/** @defgroup Utility Generic utility macros and functions
  * @{
  */

/* Macros */
#define LOW_BYTE(x)         			((uint8_t)( (x)       & 0xFF))
#define HIGH_BYTE(x)        			((uint8_t)(((x) >> 8) & 0xFF))
#define TAKE_BYTE(x, n) 				((uint8_t)(((x) >> (n * 8)) & 0xFF))
#define TAKE_BYTE_MASK(x, n, mask) 		((uint8_t)(((x) >> (n * 8)) & mask))
#define MASK_AND_SHIFTR(x, mask, shift)	((uint8_t)(((x) & mask) >> shift))

#define ASSEMBLE_U8(b1, b0)				(                              ((b1) << 4) | (b0))
#define ASSEMBLE_U16(b1, b0)			(                              ((b1) << 8) | (b0))
#define ASSEMBLE_U24(b2, b1, b0)		(               ((b2) << 16) | ((b1) << 8) | (b0))
#define ASSEMBLE_U32(b3, b2, b1, b0)	(((b3) << 24) | ((b2) << 16) | ((b1) << 8) | (b0))

#define BIT_SET(x, bit)			(x |=  (1U << bit))
#define BIT_CLEAR(x, bit)		(x &= ~(1U << bit))

#define BIT_IS_SET(x, bit)		(((x) & (1U << bit)) != 0)
#define BIT_IS_CLEAR(x, bit)	(((x) & (1U << bit)) == 0)

#define MASK_IS_SET(x, mask)	(((x) & (mask)) != 0)
#define MASK_IS_CLEAR(x, mask)	(((x) & (mask)) == 0)

#define NUM_OF_ELEM(x)			(sizeof(x)/sizeof(x[0]))

#define SWAP_U16(x) 			((((x) >> 8) & 0x00FF) | (((x) << 8) & 0xFF00))

/* Definitions */
#define VAR_SIZE_POINTER_OFFSET(field, offset)			 ((uint8_t*)  (((uint8_t*) &(field)) - offset))
#define VAR_SIZE_PAYLOAD_OFFSET(field, offset)			*((uint8_t*)  (((uint8_t*) &(field)) - offset))

#define OS_IS_ACTIVE()					(osKernelGetState() == osKernelRunning)

/* Allocation of strings to display hex values */
#define ALLOC_STATIC_HEX_STRING(str_name, array, array_len) 	char str_name[(array_len)*2 + 1];								\
																utils_convet_array_to_hex_string(str_name, array, array_len)

#define ALLOC_DYNAMIC_HEX_STRING(str_name, array, array_len) 	char *str_name = MEMPOOL_MALLOC((array_len)*2 + 1);				\
																utils_convet_array_to_hex_string(str_name, array, array_len)

#define FREE_DYNAMIC_HEX_STRING(str_name) 						MEMPOOL_FREE(str_name);


/* Public functions */
void	utils_delay_ms(uint32_t time_in_ms);
void 	utils_reverse_array(uint8_t *array, const uint8_t array_size);
char*	utils_convet_array_to_hex_string(char* string, const uint8_t *array, const uint8_t array_size);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* UTILS_H_ */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

