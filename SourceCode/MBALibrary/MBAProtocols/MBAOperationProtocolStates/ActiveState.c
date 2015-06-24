/**
  ******************************************************************************
  * @file    ActiveState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Active state functions 
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
  *	@addtogroup Active_State
  *	@{
*/

/* Includes ------------------------------------------------------------------*/
#include "ActiveState.h"

/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initial functions on enter in the Active state
  * @retval TransitionSuccessful if the system can enter in the Active State.
  *			TransitionError otherwise.
  */
TransitionRetValues ActiveStateOnEnter(void)
{
  uint8_t InterfaceCounter;

  for(InterfaceCounter = 0; InterfaceCounter < AVAILABLE_INTERFACES; InterfaceCounter++)
  {
    if ((TransferProtocolGetInterfaceType(InterfaceCounter) == END_BUS) &&
        (TransferProtocolGetInterfaceState(InterfaceCounter)== BUS_INACTIVE ))
    {
        SetBusInstanceState(InterfaceCounter, BUS_INACTIVE);
    }
  }
  return TransitionSuccessful;
}

/**
  * @brief  Main Active state function
  * @retval TransProtFram with a generated Transfer protocol frame
  */
int32_t ActiveProcess(TransProtFrame **GeneratedFrame)
{
  int32_t RetInterfaceStatus = -1;
  return RetInterfaceStatus;
}

/**
  * @brief  Last functions on exits from the Active state
  * @retval TransitionSuccessful if the system can exit from the Active State.
  *			TransitionError otherwise.
  */
TransitionRetValues ActiveStateOnExit(void)
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
	
