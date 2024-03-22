#ifndef CFE01390_CE91_4B04_A9B6_B8C376A0CC16
#define CFE01390_CE91_4B04_A9B6_B8C376A0CC16

/** @addtogroup EATON_CEAG_Macros
 * @{
 */

/** @addtogroup Bit_Operations
 * @{
 */

#include <stdbool.h>

#define SET_BIT_NUM(var, bit_num) var |= (1U << (bit_num));
#define CLR_BIT_NUM(var, bit_num) var &= ~((1U << (bit_num)));
#define BIT_NUM_IS_SET(var, bit_num) ((var & (1U << (bit_num))) ? true : false)
#define BIT_NUM_IS_CLR(var, bit_num) ((var & (1U << (bit_num))) ? false : true)

#define SET_BIT_HEX(var, bit_hex) (var |= bit_hex);
#define CLR_BIT_HEX(var, bit_hex) (var &= ~bit_hex;
#define BIT_HEX_IS_SET(var, bit_hex) ((var & bit_hex) ? true : false)

/**
 * @}
 */

/**
 * @}
 */

#endif /* CFE01390_CE91_4B04_A9B6_B8C376A0CC16 */
