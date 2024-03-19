/**
  ******************************************************************************
  * @file    user_terminal.h
  * @author  AMG/IPC Application Team
  * @brief   Header file for the User Terminal
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
  * AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
  * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
  * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
  * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  *******************************************************************************/


#ifndef USER_TERMINAL
#define USER_TERMINAL

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup User_Terminal User Terminal
  * @{
  */
  
/**
  * @}
  */  

/** @defgroup User_Terminal_Private_Code Private Code
  * @{
  */
  
/**
  * @}
  */

/** @defgroup User_Terminal_Exported_Code Exported Code
  * @{
  */
  
/**
  * @}
  */

/* Inclusions */


/** @addtogroup User_App
  * @{
  */  
  
/** @addtogroup User_Terminal
  * @{  
  */
  
/** @addtogroup User_Terminal_Exported_Code
  * @{
  */

/* Typedefs */
typedef enum user_term_action_str
{
	USER_TERM_ACT_DISPMENU,	/* Menu display */
	USER_TERM_ACT_PROCSEL,		/* Process selection */
	USER_TERM_ACT_CNT
} user_term_action_t;

/* Public functions */
void UserTerminal_Init(void);

void UserTerminal_FsmManager_IPv6(void);
void UserTerminal_FsmManager_MAC(void);

void UserTerminal_TimeoutCallback(void *argument);

void user_term_reset_to_main();

/**
  * @}
  */

/**
  * @}
  */

  /**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* USER_TERMINAL */

/*********************** (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
