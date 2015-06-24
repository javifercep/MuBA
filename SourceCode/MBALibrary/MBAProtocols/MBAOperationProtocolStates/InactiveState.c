/**
  ******************************************************************************
  * @file    InactiveState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Inactive state functions 
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
  *	@addtogroup Inactive_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "InactiveState.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Inactive state
  * @retval TransitionSuccessful if the system can enter in the Inactive State.
  *	    TransitionError otherwise.
  */
TransitionRetValues InactiveStateOnEnter(void)
{
  return TransitionSuccessful;
}

/**
  * @brief  Main Inactive state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t InactiveProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Inactive state
  * @retval TransitionSuccessful if the system can enter in the Inactive State.
  *	    TransitionError otherwise.
  */
TransitionRetValues InactiveStateOnExit(void)
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
	
