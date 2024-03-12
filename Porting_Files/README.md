## Porting change log ##

12/3/2024 -> First version for FW version 2.3.0. Module folder with original passthrough files and strong definition for *pin_management.c*. Passthrough function to be called from main created in *Src/main_porting.c*. EXTI handlers defined in *Src/stm32f4xx_it.c*.

## Porting guide ##

This folder contains the SW needed to port STM G3-PLC Hybrid FW version 2.3.0 to EATON designed board (running on a STM32F412CEU6).
To successfully port the following must be done.
1. Import the ported *.ioc file, the new STM FW and the *Porting_Files* folder.
2. Include the *porting.h* header to *main.c*.
2. Add the *passthrough_mode* function in the *main.c* file between the image downloading code and the *osKernelInitialize* function.
3. Make the functions *readBootModeST8500*, *readRfSelect*, *readFCCSelect*, *readMacSelect* and *readModbusMasterSelect* in *Modules/Pin_Management/Src/pin_management.c* weak.
4. Change the strong definition of the function named above to the expected behavior in *Porting_Files/Modules/Pin_Management/Src/pin_management.c*.
5. Change the naming of the pins (if changed in current FW version) and the EXTI line of the EXTI interruption handler functions in *Porting_Files/stm32f4xx_it.c*.
6. Change the CENELEC band used in function *g3_task_init* in *G3_Applications/Src/g3_task.c* to BOOT_BANDPLAN_CENELEC_B (probably is set to BOOT_BANDPLAN_CENELEC_A).