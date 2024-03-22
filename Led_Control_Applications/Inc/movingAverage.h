/**
 ******************************************************************************
 * @file    movingAverage.h
 * @author  E0755809
 * @brief   calculate a moving average
 @verbatim
 @endverbatim

 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */

#include "math.h"
#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef MOVINGAVERAGE_H_
#define MOVINGAVERAGE_H_

#define MAX_ARRAY_SIZE 25

/** @addtogroup Moving_Average
 * @{
 */

uint16_t calculateAvarage(uint16_t *p_array, uint8_t arraySize);
void moveAndAddArray(uint16_t *p_array, uint8_t arraySize, uint16_t newValue);

/**
 * @}
 */

#endif /* MOVINGAVERAGE_H_ */
/*********************** (C) COPYRIGHT EATON *****END OF FILE****/
