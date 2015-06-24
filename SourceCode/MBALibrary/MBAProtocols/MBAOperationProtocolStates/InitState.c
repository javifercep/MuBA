/**
  ******************************************************************************
  * @file    InitState.h
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
  *	@addtogroup Init_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "InitState.h"
#include "../MBAOperationProtocol.h"
#include "../MBATransferProtocol.h"
#include "../../MBADictionary/MBADictionary.h"
	 
/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Init state
  * @retval TransitionSuccessful if the system can enter in the Init State.
  *			TransitionError otherwise.
  */
TransitionRetValues InitStateOnEnter(void)
{
  InitDictionary();
  TransferProtocolInit();
  
  return TransitionSuccessful;
}

/**
  * @brief  Main Init state function
  * @param[out] GeneratedFrame If the state generates additional frame,
  *             These are saved in this buffer
  * @retval Interface ID of the generated frame or -1
  */
int32_t InitProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  OperationProtocolNewState(INACTIVE);
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Init state
  * @retval TransitionSuccessful if the system can exit from the Init State.
  *	    TransitionError otherwise.
  */
TransitionRetValues InitStateOnExit(void)
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
	
