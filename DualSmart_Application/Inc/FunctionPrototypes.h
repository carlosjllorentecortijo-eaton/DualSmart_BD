/*Thanks to Karsten*/

#ifndef FBDA8229_8F4A_4DDE_9F78_B80060AB82DE
#define FBDA8229_8F4A_4DDE_9F78_B80060AB82DE

/** @addtogroup EATON_CEAG_Interfaces
 * @{
 */

/** @addtogroup Function_Prototypes
 * @{
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef bool (*Function_TakesConstObject_ReturnsBoolean_t)(const void* const p_obj);
typedef bool (*Function_TakesObject_ReturnsBoolean_t)(void* const p_obj);
typedef bool (*Function_TakesConstObjectInt32_ReturnsBoolean_t)(const void* const p_obj, int32_t si32_val1);
typedef bool (*Function_TakesObjectUint32_ReturnsBoolean_t)(void* const p_obj, uint32_t ui32_val1);
typedef char* (*Function_TakesConstObject_ReturnsString_t)(const void* const p_obj);
typedef float (*Function_TakesConstObject_ReturnsFloat_t)(const void* const p_obj);
typedef float (*Function_TakesConstObjectUi32_ReturnsFloat_t)(const void* const p_obj, uint32_t ui32_val1);
typedef int32_t (*Function_TakesConstObject_ReturnsInt32_t)(const void* const p_obj);
typedef uint16_t (*ui16_Function_TakesConstObject_ReturnsUi16_t)(const void* const p_obj);
typedef uint16_t (*ui16_Function_TakesConstObjectUint32_ReturnsUi16_t)(const void* const p_obj, uint32_t ui32_val1);
typedef uint32_t (*ui32_Function_TakesConstObjectUint32_ReturnsUi32_t)(const void* const p_obj, uint32_t ui32_val1);
typedef int16_t (*i16_Function_TakesConstObject_ReturnsI16_t)(const void* const p_obj);
typedef uint32_t (*ui32_Function_TakesConstObject_ReturnsUi32_t)(const void* const p_obj);
typedef uint8_t (*ui8_Function_TakesConstObject_ReturnsUi8_t)(const void* const p_obj);
typedef int8_t (*i8_Function_TakesConstObject_ReturnsI8_t)(const void* const p_obj);
typedef void (*Function_TakesConstObject_t)(const void* const p_obj);
typedef void (*Function_TakesObject_t)(void* const p_obj);
typedef void (*Function_TakesObjectFloat_t)(void* const p_obj, float value1);
typedef void (*Function_TakesObjectPtrUint8_t)(void* const p_obj, uint8_t* const p_ui8_data);
typedef void (*Function_TakesObjectString_t)(void* const p_obj, const char* const p_string);
typedef void (*Function_TakesObjectUint16_t)(void* const p_obj, uint16_t ui16_data);
typedef void (*Function_TakesObjectUint32_t)(void* const p_obj, uint32_t ui32_data);
typedef void (*Function_TakesObjectUint8_t)(void* const p_obj, uint8_t ui8_data);
typedef void (*Function_TakesObjectVarData_t)(void* const p_obj, void* const p_data, size_t data_size);

/**
 * @}
 */

/**
 * @}
 */

#endif /* FBDA8229_8F4A_4DDE_9F78_B80060AB82DE */
