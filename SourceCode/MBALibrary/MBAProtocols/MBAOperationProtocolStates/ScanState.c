/**
  ******************************************************************************
  * @file    ScanState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Init state functions 
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
  *	@addtogroup Scan_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "ScanState.h"
#include "../MBAOperationProtocol.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Scan state
  * @retval TransitionSuccessful if the system can enter in the Scan State.
  *			TransitionError otherwise.
  */
TransitionRetValues ScanStateOnEnter(void)
{
  return TransitionSuccessful;
}

/**
  * @brief  Main Scan state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t ScanProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Scan state
  * @retval TransitionSuccessful if the system can enter in the Scan State.
  *	    TransitionError otherwise.
  */
TransitionRetValues ScanStateOnExit(void)
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
	
