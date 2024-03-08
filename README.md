## Coding Standard
We follow the Barr Group's 'Embedded C Coding Standard' with a couple of deviations:
- Standard integers (defined by stdint.h) shall have 'ui8_', 'ui16_',... as a prefix for variables and functions
       
        uint8_t ui8_my_variable = 0;
 
- Constants shall have 'c_' as a prefix, e.g. 'ui8c_' for a uint8_t prefix
 
        static const uint8_t ui8c_my_constant = 0;
 
- Function pointers shall have 'pf_' as a prefix
 
        *pf_my_pointer_to_function;
 
- Private functions shall have 'prv_' as prefix
   
        prv_ui8_GetValue()
 
- Typedefs shall have a '_t' as a postfix
 
        typedef struct MyStructure {
            uint8_t ui8_my_variable;
            bool b_my_bool;
            static const uint8_t ui8c_my_constant;
            void (*pf_my_pointer_to_function)(uint8_t ui8_my_parameter)
        } MyStructure_t;
 
- Indentation style is K&R variant 1TBS(OTBS). See https://en.wikipedia.org/wiki/Indentation_style#K&R_style
- Variable names are all lowercase
- Function names are camel case with return type and module name separated by an underscore
       
        ui8_Battery_GetBlockCount()
- File names correspond to module names and are written in camel case, e.g.
 
        Battery.c
 
The full standard can be found here: https://barrgroup.com/embedded-systems/books/embedded-c-coding-standard.

## Documenting the code
- Use 'Doxygen 1.9.1' to have automated code documentation
- Comments (if needed) are written in that they can be processed by Doxygen.