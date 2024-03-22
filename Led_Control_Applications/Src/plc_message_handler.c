/*
 ********************************************************************************
 * @file    plc_message_handler.c
 * @author  E0458337
 * @date    Jul 18, 2023
 * @brief   
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/

#include <plc_message_handler.h>
#include <string.h>
#include "app_image_transfer.h"
#include <sflash_driver.h>
#include "plc_operations.h"
#include <led_command_process.h>


/************************************
 * EXTERN VARIABLES
 ************************************/

/************************************
 * PRIVATE MACROS AND DEFINES
 ************************************/

/************************************
 * PRIVATE TYPEDEFS
 ************************************/

/************************************
 * STATIC VARIABLES
 ************************************/

/************************************
 * GLOBAL VARIABLES
 ************************************/

/************************************
 * STATIC FUNCTION PROTOTYPES
 ************************************/

/************************************
 * STATIC FUNCTIONS
 ************************************/

/************************************
 * GLOBAL FUNCTIONS
 ************************************/





#define DEBUG_IMAGE_TRANSMISSION


bool send_to_coordinator = false;
extern user_g3_common_data_t 	UserG3_CommonEvt;
extern plcType_t    	dev_type;

static uint8_t ui8_aReceivedPlcData[MAX_PLC_PAYLOAD] = {0x00};

SPlcData_t deviceCommandResponse;


void DeviceSendResponse(uint8_t ui8_cmdIdentifier, uint8_t ui8_command,uint8_t size , uint8_t*data)
{
	uint16_t ui16_dest_short_id = g3_app_ka_get_coord_short_addr();

	deviceCommandResponse.plc.ui8_cmdidentifier = ui8_cmdIdentifier;
	deviceCommandResponse.plc.ui8_command       = ui8_command;
	deviceCommandResponse.ui8_nodeId            =  ui16_dest_short_id;
	deviceCommandResponse.plc.ui16_size         = size;

	if(deviceCommandResponse.plc.ui16_size != 0x00)
	{
		memcpy(&deviceCommandResponse.plc.ui8_data[0], &data[0] , deviceCommandResponse.plc.ui16_size );
	}

	SendUdpMessageCooridnator((void*)&deviceCommandResponse, sizeof(deviceCommandResponse));
	SendUdpMessageCooridnator((void*)&deviceCommandResponse, (0x05 + size));//sizeof(deviceCommandResponse));
}

/** @brief Receive UDP data
*
* This function process the UDP message received between the devices and coordinator.
*
* @retval None
*/
void LpsReceivedUdpData(void)
{
	PRINT(" LPS UDP message received content is: \n");
//	UserTerm_LowLevelPrint(UserG3_CommonEvt.UdpData.pPayload, UserG3_CommonEvt.UdpData.Length);
	ExtractLpsCommandFromUdp(UserG3_CommonEvt.UdpData.pPayload , UserG3_CommonEvt.UdpData.Length);
}

/** @brief Extract LPS command from UDP message
*
* This function is used to extract the message used for processing the LPS commands.
*
* @param *pCommand     : pointer to the variable holding the data to process
* @param ui16_size  : size of the data to extract
*
* @retval None
*/
void ExtractLpsCommandFromUdp(uint8_t* pCommand , uint16_t ui16_size)
{
	if( (pCommand != NULL) && (ui16_size > 0U))
	{
		memcpy((uint8_t*)&ui8_aReceivedPlcData[0] , (uint8_t*)&pCommand[0] , ui16_size);
		CheckCommandReceived( ui8_aReceivedPlcData, ui16_size);
	}
}

/** @brief Send UDP message to coordinator
*
* This function is used to prepare and send UDP message to coordinator from device
*
* @param *pData     : pointer to the variable holding the data to be sent
* @param ui32_lenght  : length of the message to be sent
*
* @retval None
*/
void SendUdpMessageCooridnator(void* pData, uint32_t ui32_lenght)
{
	uint16_t ui16_dest_pan_id = g3_app_ka_get_pan_id();
	uint16_t ui16_dest_short_id = g3_app_ka_get_coord_short_addr();

	PRINT_G3_USER("Data going back from Device is at SendUDpToDest.\n");
	UserG3_SendUdpDataToDest(TEST_CONN_ID, (void *)pData, ui32_lenght, ui16_dest_short_id , ui16_dest_pan_id);
}




/** @brief check Command received
*
* This function is used to check if the message is for the device or coordinator
*
* @param *pDataRecieved     : pointer to the variable holding the data
* @param ui16_sizeOfdata  : size of the data
*
* @retval None
*/

void CheckCommandReceived(uint8_t* pDataRecieved , uint16_t ui16_sizeOfdata)
{
	SPlcData_t* pCommandReceived = (SPlcData_t*)&pDataRecieved[0];

	if(PLC_G3_DEVICE == dev_type)
	{
		switch(pCommandReceived->plc.ui8_cmdidentifier)
		{
		case LED_CONTROL_COMMAND_IDENTIFIER: // for device
		{
			// fetch the command
			PRINT(" LPS UDP command for LED is : %d ",pCommandReceived->plc.ui8_command );
			LedControlCmdHandler(pCommandReceived->plc.ui8_command  ,(uint32_t)NULL);

		}
		break;

		case PLC_IMAGE_COMMAND_IDENTIFIER: // for device
		{
			PRINT(" LPS UDP command for PLC Image Upgrade is : %d ",pCommandReceived->plc.ui8_command );
			// extract the data for the image download
			ImageDownload(&pDataRecieved[0] , ui16_sizeOfdata);
		}
		break;

		case PLC_OPERATION_COMMAND_IDENTIFIER: // for device
		{
			// fetch the command
			PlcNetworkOperationCommandProcess(pCommandReceived->plc.ui8_command , pCommandReceived->ui8_nodeId);
		}
		break;

		}
	}
}

