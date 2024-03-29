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
7. Add the network attributes to *G3_Applications/Src/g3_app_attrib_tbl.c*. The last updated version of this file is stored in the *Porting_Files* folder, change the original with the content of this file.
8. Server discovery time and PSK timeout must be changed in the appropriate defines in *G3_Applications/BOOT/g3_app_boot_constants.h* (BOOT_SERVER_DISCOVERY_TIME = 2 and BOOT_SERVER_PSK_GET_TIMEOUT = 10000).
9. Activate the following event indications (*Inc/settings.h*)
- ENABLE_EVENTINDICATION_ERROR
- ENABLE_EVENTINDICATION_GMK
- ENABLE_EVENTINDICATION_ACTKEY
- ENABLE_EVENTINDICATION_PANID
- ENABLE_EVENTINDICATION_SHORTADDR
- ENABLE_EVENTINDICATION_THERMEV
- ENABLE_EVENTINDICATION_PREQ
- ENABLE_EVENTINDICATION_SURGEEV
- ENABLE_EVENTINDICATION_RTEWARN
- ENABLE_EVENTINDICATION_RTEPOLL
- ENABLE_EVENTINDICATION_BOOTMAXRETIES
- ENABLE_EVENTINDICATION_BANDMISMATCH
- ENABLE_EVENTINDICATION_MACUPDATE
- ENABLE_EVENTINDICATION_MEMLEAK
- ENABLE_EVENTINDICATION_TIMERERR
10. Exchange the file *G3_Applications/Src/g3_app_keep_alive.c* with *Porting_Files/G3_Applications/Src/g3_app_keep_alive.c* (the original uses the state of a LED to check Keep-Alive status).