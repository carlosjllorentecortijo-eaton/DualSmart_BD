/**
 ******************************************************************************
 * @file    movingAverage.c
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
#include <movingAverage.h>

/** @brief
 *
 * calculates the average over an array
 *
 * @param *p_array     	: pointer to array
 * @retval retVal: 		: average value over given array
 */
uint16_t calculateAvarage(uint16_t *p_array, uint8_t arraySize)
{
    uint16_t retVal = 0;
    uint32_t sum = 0;

    for (int i = 0; i < arraySize; i++)
    {
        sum += p_array[i];
    }

    retVal = sum / arraySize;

    return retVal;
}

/** @brief
 *
 * moves the values in an array by 1 to the left and adds a new value to the end
 * the first value in the array gets scrapped
 *
 * @param *p_array     	: pointer to array
 * @retval retVal: 		: average value over given array
 *
 * TODO: include memcpy
 */
void moveAndAddArray(uint16_t *p_array, uint8_t arraySize, uint16_t newValue)
{

    for (int i = 0; i < arraySize; i++)
    {
        p_array[i] = p_array[i + 1];
    }

    p_array[arraySize - 1] = newValue;

}
/*********************** (C) COPYRIGHT EATON *****END OF FILE****/
