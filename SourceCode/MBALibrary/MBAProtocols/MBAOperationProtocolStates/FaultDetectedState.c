/**
  ******************************************************************************
  * @file    FaultDetectedState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Fault Detected state functions 
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
  *	@addtogroup Fault_Detected_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "FaultDetectedState.h"
#include "../MBAOperationProtocol.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the FaultDetected state
  * @retval TransitionSuccessful if the system can enter in the FaultDetected State.
  *	    TransitionError otherwise.
  */
TransitionRetValues FaultDetectedStateOnEnter(void)
{
  return TransitionSuccessful;
}

/**
  * @brief  Main FaultDetected state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t FaultDetectedProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the FaultDetected state
  * @retval TransitionSuccessful if the system can enter in the FaultDetected State.
  *			TransitionError otherwise.
  */
TransitionRetValues FaultDetectedStateOnExit(void)
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
	
