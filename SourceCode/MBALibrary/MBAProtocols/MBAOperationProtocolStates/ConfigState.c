/**
  ******************************************************************************
  * @file    ConfigState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Config state functions 
  *			 for the operation protocol
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup MBA
  * @{
  *
  *	@addtogroup MBA_Library
  *	@{
  *	
  *	@addtogroup MBA_Operation_Protocol
  *	@{
  *
  *	@addtogroup Config_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "ConfigState.h"
#include "../MBAOperationProtocol.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Config state
  * @retval TransitionSuccessful if the system can enter in the Config State.
  *	    TransitionError otherwise.
  */
TransitionRetValues ConfigStateOnEnter(void)
{
   return TransitionSuccessful;
}

/**
  * @brief  Main Config state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t ConfigProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Config state
  * @retval TransitionSuccessful if the system can exit from the Config State.
  *	    TransitionError otherwise.
  */
TransitionRetValues ConfigStateOnExit(void)
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
	
