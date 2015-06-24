/**
  ******************************************************************************
  * @file    BUSAPI.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains BUS API for manage the target BUS to be sniffed.
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup Bus
  * @{
  *
  *	@addtogroup Bus_Interface
  *	@{
  *		@brief Bus Interface API.
  *		@details
*/

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#include "BUSAPI.h"
#if USB_API > 0
#include "USBAPI/USBAPI.h"
#endif
#if USART_API > 0
#include "USARTAPI/USARTAPI.h"
#endif
#if SPI_API > 0
#include "SPIAPI/SPIAPI.h"
#endif
#if USB_HOST_API > 0
#include "USBHOSTAPI/USBHOSTAPI.h"
#endif
#if SOCKET_API > 0
#include "SOCKETAPI/SOCKETAPI.h"
#endif


/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  BusInstanceStates State;
  BusInstanceTransitions CurrentTransition;
}BUSStateMachineInstance;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
BusInstance BusInstances[] = 
{
#if USB_API > 0
{ USBInit, USBDeInit, USBDataAvailable, USBSizeDataAvailable, USBRead, USBWrite, USBConfiguration },
#endif
#if USB_HOST_API > 0
{ USBHostInit, USBHostDeInit, USBHostDataAvailable, USBHostSizeDataAvailable, USBHostRead, USBHostWrite, USBHostConfiguration },
#endif
#if SOCKET_API > 0
{ SocketInit, SocketDeInit, SocketDataAvailable, SocketSizeDataAvailable, SocketRead, SocketWrite, SocketConfiguration },
#endif
#if SPI_API > 0	
{ SPIInit, SPIDeInit, SPIDataAvailable, SPISizeDataAvailable, SPIRead, SPIWrite, SPIConfiguration },	
#endif
#if USART_API > 0
{ USARTInit, USARTDeInit, USARTDataAvailable, USARTSizeDataAvailable, USARTRead, USARTWrite, USARTConfiguration }	
#endif
};
/* Initialize the Bus instances state to enable some interfaces by default */
BUSStateMachineInstance BusInstancesSM[AVAILABLE_INTERFACES] =
{
#if USB_HOST_API > 0
    {BUS_INIT, BUS_NO_TRANSITION},
#endif
#if USB_API > 0
    {BUS_INACTIVE, BUS_INIT_2_INACTIVE},
#endif
#if SOCKET_API > 0
    {BUS_INACTIVE, BUS_INIT_2_INACTIVE},
#endif
#if SPI_API > 0
    {BUS_INACTIVE, BUS_INIT_2_INACTIVE},
#endif
#if USART_API > 0
    {BUS_INIT, BUS_NO_TRANSITION}
#endif
};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**

  * @brief  	Execute a State transition to a new state
  * @param[in]  NewState Requested state
  * @retval 	TransitionSuccessful if the newstate is reached,
  *             TransitionError otherwise
  */
BusInstanceStates GetBusInstanceState(uint8_t InterfaceID)
{
  return BusInstancesSM[InterfaceID].State;
}

/**

  * @brief  	Execute a State transition to a new state
  * @param[in]  NewState Requested state
  * @retval 	TransitionSuccessful if the new state is reached,
  *             TransitionError otherwise
  */
BusInstanceTransitions GetBusInstanceStateTransition(uint8_t InterfaceID)
{
  BusInstanceTransitions RetTransition = BusInstancesSM[InterfaceID].CurrentTransition;

  /* If a transition is readed, restore the current transition to no transition to avoid
   * multiple function execution.
   */
  BusInstancesSM[InterfaceID].CurrentTransition = BUS_NO_TRANSITION;

  return RetTransition;
}

/**

  * @brief  	Execute a State transition to a new state
  * @param[in]  NewState Requested state
  * @retval 	TransitionSuccessful if the new state is reached,
  *             TransitionError otherwise
  */


void SetBusInstanceState(uint8_t InterfaceID, BusInstanceStates State)
{
  /* Check that the requested state is correct */
  if(InterfaceID <= AVAILABLE_INTERFACES)
  {
      if((State - BusInstancesSM[InterfaceID].State) == 1)
      {
	  switch(State)
	  {
	    case BUS_INIT:
	      /* The code never should enter here */
	      break;
	    case BUS_INACTIVE:
	      BusInstancesSM[InterfaceID].State = BUS_INACTIVE;
	      BusInstancesSM[InterfaceID].CurrentTransition = BUS_INIT_2_INACTIVE;
	      break;
	    case BUS_ACTIVE:
	      BusInstancesSM[InterfaceID].State = BUS_ACTIVE;
	      BusInstancesSM[InterfaceID].CurrentTransition = BUS_INACTIVE_2_ACTIVE;
	      break;
	    case BUS_STOP:
	      /* if a BUS_STOP is requested, the upper layers must execute the
	       * related function, and this API helps to control the BUS state
	       */
	      BusInstancesSM[InterfaceID].State = BUS_INIT;
	      BusInstancesSM[InterfaceID].CurrentTransition = BUS_ACTIVE_2_STOP;
	      break;
	  }
      }
      else
      {
	  BusInstancesSM[InterfaceID].CurrentTransition = BUS_NO_TRANSITION;
      }
  }
}

/**
  * @brief  	Execute a State transition to a new state
  * @param[in]  NewState Requested state
  * @retval 	TransitionSuccessful if the new state is reached,
  *             TransitionError otherwise
  */
void ForceBusInterfaceStop(uint8_t InterfaceID)
{
  BusInstancesSM[InterfaceID].State = BUS_INIT;
  BusInstancesSM[InterfaceID].CurrentTransition = BUS_NO_TRANSITION;
}
/*********************************************************************************************/
/*****	STATIC FUNCTIONS 	    **********************************************************/
/*********************************************************************************************/
/**
  *@}
  */
/**
  *@}
  */
/**
  *@}
  */

