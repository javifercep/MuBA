/**
  ******************************************************************************
  * @file    FaultState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Fault state functions 
  *	     for the operation protocol
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
  *	@addtogroup Fault_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "FaultState.h"
#include "../MBAOperationProtocol.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Fault state
  * @retval TransitionSuccessful if the system can enter in the Fault State.
  *	    TransitionError otherwise.
  */
TransitionRetValues FaultStateOnEnter(void)
{
  return TransitionSuccessful;
}

/**
  * @brief  Main Fault state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t FaultProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Fault state
  * @retval TransitionSuccessful if the system can enter in the Fault State.
  *	    TransitionError otherwise.
  */
TransitionRetValues FaultStateOnExit(void)
{
  return TransitionSuccessful;
}

/**
  * @brief  Force the system to enter in the Fault state
  */
void ForceFaultSate(void)
{
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
	
