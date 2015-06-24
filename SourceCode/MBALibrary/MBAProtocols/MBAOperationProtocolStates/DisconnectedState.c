/**
  ******************************************************************************
  * @file    DisconnectedState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Disconnected state functions 
  *			 for the operation protocol
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup MBA
  *	@{
  *
  *	@addtogroup MBA_Library
  *	@{
  *	
  *	@addtogroup MBA_Operation_Protocol
  *	@{
  *
  *	@addtogroup Disconnected_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "DisconnectedState.h"
#include "../MBAOperationProtocol.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Disconnected state
  * @retval TransitionSuccessful if the system can enter in the Disconnected State.
  *			TransitionError otherwise.
  */
TransitionRetValues DisconnectedStateOnEnter(void)
{
  return TransitionSuccessful;
}

/**
  * @brief  Main Disconnected state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t DisconnectedProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Disconnected state
  * @retval TransitionSuccessful if the system can enter in the Disconnected State.
  *			TransitionError otherwise.
  */
TransitionRetValues DisconnectedStateOnExit(void)
{
  return TransitionSuccessful;
}


/**
  *@}
  */
/**
  *@}
  */
/**
  *@}
  */
/**
  *@}
  */
	
