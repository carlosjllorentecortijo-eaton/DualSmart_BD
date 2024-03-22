/*
 ********************************************************************************
 * @file    plc_message_handler.h
 * @author  E0458337
 * @date    Jul 18, 2023
 * @brief   
 ********************************************************************************
 */
#ifndef INC_PLC_MESSAGE_HANDLER_H_
#define INC_PLC_MESSAGE_HANDLER_H_


/************************************
 * INCLUDES
 ************************************/


#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include <print_task.h>
#include "debug_print.h"
#include <hi_msgs_impl.h>
#include "user_g3_common.h"
#include <g3_app_keep_alive.h>



# pragma pack(1)
















/************************************
 * MACROS AND DEFINES
 ************************************/



#define WEBSERVER_BLOCK_SIZE   8    //
#define SC_COMMAND_SIZE        28   // Size of the complete CGLine command

#define PREAMBLE               0x55
#define LED_CONTROL_COMMAND_IDENTIFIER    0xAA
#define PLC_IMAGE_COMMAND_IDENTIFIER      0xBB
#define PLC_OPERATION_COMMAND_IDENTIFIER  0xCC
//#define PLC_IMAGE_SEND         0xBB



// CGLRecvBuffer CmdState
#define  SC_RECV_NO_DATA   0x00
#define  SC_RECV_STARTED   0x01
#define  SC_RECV_COMPLETE  0x02

// Indirect arc power control commands
#define   SC_OFF                                          0
#define   SC_DIM1                                         1
#define   SC_DIM2                                         2
#define   SC_DIM3                                         3
#define   SC_DIM4                                         4
//#define   SC_UP                                           1
//#define   SC_DOWN                                         2
//#define   SC_STEP_UP                                      3
//#define   SC_STEP_DOWN                                    4
#define   SC_ON                                           5
//#define   SC_RECALL_MIN_LEVEL                             6
//#define   SC_STEP_DOWN_AND_OFF                            7
//#define   SC_ON_AND_STEP_UP                               8
//          RESERVED                               9 - 15
//#define   SC_GO_TO_SCENE                                 16
// General configuration commands
#define   SC_RESET                                       32
#define   SC_STORE_ACTUAL_LEVEL_IN_THE_DTR               33

// Arcpower parameters settings
//#define   SC_STORE_THE_DTR_AS_MAX_LEVEL                  42
//#define   SC_STORE_THE_DTR_AS_MIN_LEVEL                  43
//#define   SC_STORE_THE_DTR_AS_SYSTEM_FAILLEV             44
//#define   SC_STORE_THE_DTR_AS_POWER_ON_LEVEL             45
//#define   SC_STORE_THE_DTR_AS_FADE_TIME                  46
//#define   SC_STORE_THE_DTR_AS_FADE_RATE                  47
////        RESERVED                              48 - 63
//#define   SC_STORE_THE_DTR_AS_SCENE                      64

// System parameters settings
//#define   SC_REMOVE_FROM_SCENE                           80
#define   SC_ADD_TO_GROUP_0                              96
#define   SC_ADD_TO_GROUP_1                              97
#define   SC_ADD_TO_GROUP_2                              98
#define   SC_ADD_TO_GROUP_3                              99
#define   SC_ADD_TO_GROUP_4                             100
#define   SC_ADD_TO_GROUP_5                             101
#define   SC_ADD_TO_GROUP_6                             102
#define   SC_ADD_TO_GROUP_7                             103
#define   SC_ADD_TO_GROUP_8                             104
#define   SC_ADD_TO_GROUP_9                             105
#define   SC_ADD_TO_GROUP_10                            106
#define   SC_ADD_TO_GROUP_11                            107
#define   SC_ADD_TO_GROUP_12                            108
#define   SC_ADD_TO_GROUP_13                            109
#define   SC_ADD_TO_GROUP_14                            110
#define   SC_ADD_TO_GROUP_15                            111
#define   SC_REMOVE_FROM_GROUP_0                        112
#define   SC_REMOVE_FROM_GROUP_1                        113
#define   SC_REMOVE_FROM_GROUP_2                        114
#define   SC_REMOVE_FROM_GROUP_3                        115
#define   SC_REMOVE_FROM_GROUP_4                        116
#define   SC_REMOVE_FROM_GROUP_5                        117
#define   SC_REMOVE_FROM_GROUP_6                        118
#define   SC_REMOVE_FROM_GROUP_7                        119
#define   SC_REMOVE_FROM_GROUP_8                        120
#define   SC_REMOVE_FROM_GROUP_9                        121
#define   SC_REMOVE_FROM_GROUP_10                       122
#define   SC_REMOVE_FROM_GROUP_11                       123
#define   SC_REMOVE_FROM_GROUP_12                       124
#define   SC_REMOVE_FROM_GROUP_13                       125
#define   SC_REMOVE_FROM_GROUP_14                       126
#define   SC_REMOVE_FROM_GROUP_15                       127
#define   SC_STORE_DTR_AS_SHORT_ADDRESS                 128
#define   SC_ENABLE_WRITE_MEMORY                        129

// Queries related to status information
#define   SC_QUERY_STATUS                               144
#define   SC_QUERY_BALLAST                              145
#define   SC_QUERY_LAMP_FAILURE                         146
#define   SC_QUERY_LAMP_POWER_ON                        147
#define   SC_QUERY_LIMIT_ERROR                          148
#define   SC_QUERY_RESET_STATE                          149
#define   SC_QUERY_MISSING_SHORT_ADDRESS                150
#define   SC_QUERY_VERSION_NUMBER                       151
#define   SC_QUERY_CONTENT_DTR                          152
#define   SC_QUERY_DEVICE_TYPE                          153
//#define   SC_QUERY_PHYSICAL_MINIMUM_LEVEL               154
//#define   SC_QUERY_POWER_FAILURE                        155
#define   SC_QUERY_CONTENT_DTR1                         156
#define   SC_QUERY_CONTENT_DTR2                         157

// Queries related to arc power parameters settings
#define   SC_QUERY_ACTUAL_LEVEL                         160
//#define   SC_QUERY_MAX_LEVEL                            161
//#define   SC_QUERY_MIN_LEVEL                            162
//#define   SC_QUERY_POWER_ON_LEVEL                       163
//#define   SC_QUERY_SYSTEM_FAILURE_LEVEL                 164
//#define   SC_QUERY_FADE                                 165

// Queries related to system parameters settings
//#define   SC_QUERY_SCENE_LEVEL                          176
#define   SC_QUERY_GROUPS_0_7                           192
#define   SC_QUERY_GROUPS_8_15                          193
#define   SC_QUERY_RANDOM_ADDRESS_H                     194
#define   SC_QUERY_RANDOM_ADDRESS_M                     195
#define   SC_QUERY_RANDOM_ADDRESS_L                     196
#define   SC_QUERY_MEMORY_LOCATION                      197
//        RESERVED                                198 - 223

// Emergency Commands
#define   SC_REST                                       224
#define   SC_INHIBIT                                    225
#define   SC_RESET_INHIBIT                              226
#define   SC_START_FUNCTION_TEST                        227
#define   SC_START_DURATION_TEST                        228
#define   SC_STOP_TEST                                  229
#define   SC_RESET_FUNCTION_TEST_DONE_FLAG              230
#define   SC_RESET_DURATION_TEST_DONE_FLAG              231
#define   SC_RESET_LAMP_TIME                            232
#define   SC_STORE_DTR_AS_EMERGENCY_LEVEL               233
#define   SC_STORE_TEST_DELAY_TIMING_HIGH_BYTE          234
#define   SC_STORE_TEST_DELAY_TIMING_LOW_BYTE           235
#define   SC_STORE_FUNCTION_TEST_TIMING                 236
#define   SC_STORE_DURATION_TEST_TIMING                 237
#define   SC_STORE_TEST_EXECUTION_TIMEOUT               238
#define   SC_STORE_PROLONG_TIME                         239
#define   SC_START_IDENTIFICATION                       240
#define   SC_QUERY_BATTERY_CHARGE                       241
#define   SC_QUERY_TEST_TIMING                          242
#define   SC_QUERY_DURATION_TEST_RESULT                 243
#define   SC_QUERY_LAMP_EMERGENCY_TIME                  244
#define   SC_QUERY_LAMP_TOTAL_OPERATION_TIME            245
#define   SC_QUERY_EMERGENCY_LEVEL                      246
#define   SC_QUERY_EMERGENCY_MIN_LEVEL                  247
#define   SC_QUERY_EMERGENCY_MAX_LEVEL                  248
#define   SC_QUERY_RATED_DURATION                       249
#define   SC_QUERY_EMERGENCY_MODE                       250
#define   SC_QUERY_FEATURES                             251
#define   SC_QUERY_FAILURE_STATUS                       252
#define   SC_QUERY_EMERGENCY_STATUS                     253
#define   SC_DIRECT_LIGHT_LEVEL_CONTROL                 254
#define   SC_RESET_COMMUNICATION                        255

// Addressing commands
#define   SC_TERMINATE                                  256
#define   SC_DATA_TRANSFER_REGISTER                     257          // Download information to the dtr
#define   SC_INITIALISE                                 258
#define   SC_RANDOMISE                                  259
#define   SC_COMPARE                                    260
#define   SC_WITHDRAW                                   261
//        RESERVED                                      262
//        RESERVED                                      263
#define   SC_SEND_ADR_H                                 264
#define   SC_SEND_ADR_M                                 265
#define   SC_SEND_ADR_L                                 266
#define   SC_PROGRAM_SHORT_ADDRESS                      267
#define   SC_VERIFY_SHORT_ADDRESS                       268
#define   SC_QUERY_SHORT_ADDRESS                        269
#define   SC_PHYSICAL_SELECTION                         270


//Extended Emergency Commands
//        RESERVED                                      271
#define   SC_ENABLE_DEVICE_TYPE                         272
#define   SC_DATA_TRANSFER_REGISTER_1                   273
#define   SC_DATA_TRANSFER_REGISTER_2                   274
#define   SC_WRITE_MEMORY_LOCATION                      275
#define   SC_REST_OLD_CGLINE                            275
//        RESERVED                                276 - 287

// CGLINE+ Specifig Instruction
#define   SC_QUERY_STATUS_CHANGED                       400
#define   SC_REMOTE_CONTROL_INSTRUCTION                 401

// OPC Specifig Instruction (ARM <-> XMEGA)
#define   SC_SEARCH_LONG_ADRESS                         500
#define   SC_QUERY_IDS                                  501
#define   SC_TRANSMIT_LAMP_NAME                         502
#define   SC_QUERY_LAMP_NAME                            503
#define   SC_READ_LAMP_NAME                             504
#define   SC_SEND_SHORT_ADRESS                          505
#define   SC_QUERY_SHORT_ADRESS                         506
#define   SC_DELETE_SHORT_ADRESS                        507
#define   SC_SEND_LINE_NAME                             508
#define   SC_QUERY_LINE_NAME                            509
#define   SC_RESET_COMPLETE_LUM                         510
#define   SC_SEND_LAMP_INFO                             511
#define   SC_QUERY_LINE_STATE                           530
#define   SC_QUERY_SYSTEM_STATE                         531
#define   SC_RESEND_SYSTEM_STATE                        532
#define   SC_SEND_SYSTEM_NAME                           540
#define   SC_QUERY_SYSTEM_NAME                          541
#define   SC_SEND_GP_COMMAND                            550
#define   SC_SEND_GP_QUERY                              551
#define   SC_ANSWER_GP_QUERY                            552
#define   SC_LINE_PROGRESS                              580
#define   SC_BUS_INITIATE                               581
#define   SC_BUS_TERMINATE                              582
#define   SC_CHANGE_ZONE                                583
#define   SC_SET_200_400_MODE                           584
#define   SC_WATCHDOG_TELEGRAMM                         598
#define   SC_LOGIN_TELEGRAM                             599
#define   SC_GET_XMEGA_SW_VERSION                       600
#define   SC_SET_SYSTEM_TIME                            601
#define   SC_QUERY_SYSTEM_TIME                          602
#define   SC_SEND_TIMER_EVENT                           603
#define   SC_QUERY_TIMER_EVENT                          604
#define   SC_START_CONFIG_COMPLETE                      605
#define   SC_START_CONFIG_DIFFERENTIAL                  606
#define   SC_QUERY_INFORMATION                          607
#define   SC_QUERY_SW_VERSION_SD                        608
#define   SC_QUERY_NETWORK_CONFIGURATION                609
#define   SC_QUERY_LOGBOOK                              610
#define   SC_SET_RELAIS_STATUS                          611
#define   SC_GET_INPUT_STATE                            612
#define   SC_CHECKSUM_OK                                615
#define   SC_WRITE_COMM_STATUS                          616
#define   SC_READ_COMM_STATUS                           617
#define   SC_SET_WRITE_HANDLE                           618
#define   SC_READ_WRITE_HANDLE                          619
#define   SC_DELETE_LOGBOOK                             620
#define   SC_RESET_LOGBOOK                              621
#define   SC_QUERY_IO_NAME                              622
#define   SC_QUERY_IO_CFG                               623
#define   SC_QUERY_MANUFACTURING_DATE                   624
#define   SC_QUERY_SYSTEM_TYPE                          625
#define   SC_LINE_CONFIGURATION                         626
#define   SC_NUMBER_OF_TEST_GROUPS                      627
#define   SC_AUTO_TEST_GROUP                            628
#define   SC_SET_TEST_GROUP                             629

#define   SC_ZONE_STATUS                                630
#define   SC_SEND_LINE_INFO                             631
#define   SC_QUERY_LINE_INFO                            632
#define   SC_SEND_ZONE_NAME                             633
#define   SC_QUERY_ZONE_NAME                            634
#define   SC_SEND_ZONE_INFO                             635
#define   SC_QUERY_ZONE_INFO                            636
#define   SC_SEND_LAMP_INFORMATION                      637
#define   SC_QUERY_LAMP_INFORMATION                     638

#define   SC_SEND_LAMP_CONFIGURATION                    639
#define   SC_QUERY_LAMP_CONFIGURATION                   640
#define   SC_QUERY_LAMP_STATE                           641
#define   SC_QUERY_LINE_CONFIGURATION                   642
#define   SC_QUERY_DEVICE_ID                            643
#define   SC_QUERY_LAMP_GTIN                            644
#define   SC_SEND_COMPATIBILITY_TIMING                  645
#define   SC_QUERY_LAMPS_INSTALLED                      646
#define   SC_SEND_LAMPS_INSTALLED                       647
#define   SC_QUERY_BUS_QUALITY                          648

#define   SC_CREATE_LUM_SCAN_DAT                        650
#define   SC_REWRITE_COMPLETE_LAMP_CONFIG               651
#define   SC_CHANGE_LUM_STATUS_REFRESH_TIME             652
#define   SC_STOP_IDENTIFICATION                        653
#define   SC_DELETE_ALL                                 654

#define   SC_LED_ON                                     710
//#define   SC_RELAIS_ON                                  711

#define   SC_AUTO_ONOFF_MASK                            0x8000
#define   SC_AUTO_OFF                                   (SC_OFF|SC_AUTO_ONOFF_MASK)
#define   SC_AUTO_ON                                    (SC_ON|SC_AUTO_ONOFF_MASK)

#define   SC_CHECKSUM_ERROR                             0xFFFE
#define   SC_NO_COMMAND                                 0xFFFF




// enable only if the EMC test software is required
//#define PLC_RE_TEST
#define MAX_PLC_PAYLOAD   513


/************************************
 * TYPEDEFS
 ************************************/

/** \brief  Structure for the communication with the xMega
 */
typedef struct {
  uint32_t ui32_ID;	            //* ID number from this command
  uint32_t ui32_Timestamp;	    //* Timestamp at which time the command are created
  uint8_t  ui8_Line;	          //* line number 1-4, 255 (0xff) for all lines, 0 for ignore
  uint8_t  ui8_Zone; 	          //* zone number 1-16, 255 (0xff) for all zones, 0 for ignore
  uint8_t  ui8_TestGroup; 	    //* testgroup number 1-8, 255 (0xff) for all groups, 0 for ignore
  uint8_t  ui8_Reserve;         //* Reserved byte for future use
  uint16_t ui16_ShortAdr; 	    //* lamp number 1-400, 65535 (0xffff) for all lamps
  uint16_t ui16_Command;	      //* command seen below
  union Data{
    uint8_t  ui8_Data[WEBSERVER_BLOCK_SIZE];	//* Data to send
    struct s_ScLamp{
      uint32_t ui32_ID;
      uint8_t  ui8_Type;
      uint8_t  ui8_Version;
      uint8_t  ui8_DTTime;
      uint8_t  ui8_RatedDuration;
    }s_ScLamp;
    struct s_ScLampState{
      uint8_t  ui8_Mode;
      uint8_t  ui8_Failure;
      uint8_t  ui8_State;
    }s_ScLampState;
    struct s_ScEasycheckCfg{  //* for easicheck configuration
      uint8_t ui8_CellCfg;
      uint8_t ui8_ChargeFailAlarm;            // Charge Fail Alarm Threshold Setting, 2mA per bit
      uint8_t ui8_LampFailAlarm;              // Lamp Fail Alarm Threshold Setting, 8mA per bit
      uint8_t ui8_RatedDuration;
    }s_ScEasycheckCfg;
  }Data;
  uint16_t ui16_Reserve;
  uint16_t ui16_Checksum;	      //* Simple 16bit addend value
  uint8_t  ui8_Source;
  uint8_t  ui8_RetryCnt;
  uint32_t ui32_WaitTimer;
  uint32_t ui32_WaitTicks;
}CGLCommand_t;  // 28 Byte, Big endian

typedef struct CGLRecvBuffer_t{
  uint8_t  ui8_CmdState;
  uint8_t  ui8_Cnt;
  union Buffer{
    CGLCommand_t s_CGLineCmd;
    uint8_t ui8_Data[SC_COMMAND_SIZE];
  }Buffer;
}CGLRecvBuffer_t;



typedef struct{
	uint16_t ui16_size;
	uint8_t ui8_cmdidentifier;
	uint8_t ui8_command;
	uint8_t ui8_data[256];
}SCommandOverPlc_t;

typedef struct {
	uint8_t ui8_nodeId;
	SCommandOverPlc_t plc;
}SPlcData_t;


/************************************
 * EXPORTED VARIABLES
 ************************************/

/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/
uint8_t CalculateChecksum(uint8_t* ui8_rx_data, uint32_t ui32_size);
void LpsReceivedUdpData(void);
void ExtractLpsCommandFromUdp(uint8_t* pCommand , uint16_t ui16_size);
void SendUdpMessageCooridnator(void* pData, uint32_t ui32_lenght);
void CheckCommandReceived(uint8_t* pDataRecieved , uint16_t sizeOfdata);
//void packetDownload(uint8_t* pPayload , uint16_t size);
//void readPacketSend(void);
//void sendCommandReceivedFromUser(uint8_t* pDataRecieved);
void DeviceSendResponse(uint8_t ui8_cmdIdentifier, uint8_t ui8_command,uint8_t size , uint8_t*data);



#endif /* INC_PLC_MESSAGE_HANDLER_H_ */
