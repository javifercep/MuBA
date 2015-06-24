/**
  ******************************************************************************
  * @file    MBAOperationProtocol.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA operation protocol functions 
  * 	     for upper layers
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
  *		@brief Operation Protocol is the responsible
  *		@details
*/

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#include "MBAOperationProtocol.h"
#include "MBAOperationProtocolStates/InitState.h"
#include "MBAOperationProtocolStates/ConfigState.h"
#include "MBAOperationProtocolStates/ScanState.h"
#include "MBAOperationProtocolStates/InactiveState.h"
#include "MBAOperationProtocolStates/ActiveState.h"
#include "MBAOperationProtocolStates/FaultDetectedState.h"
#include "MBAOperationProtocolStates/FaultState.h"
#include "../MBADictionary/MBADictionary.h"
#include "../../TOOLS/MemoryManagement.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Config cast masks */
#define DIR_MASK	0x01 /*!< Cast direction */

/*Config cast modes */
#define OPERATION_FROM_BUFF	0 /*!< Cast direction */
#define OPERATION_TO_BUFF	1 /*!< Cast direction */

/* Operation commands */
#define REQUEST             0x00 /*!< Request command  */
#define REPLY               0x80 /*!< Reply command  */

/* Frame defines */
#define OP_FRAME_SIZE		2 /*!< Operation frame size  */

#define COMMAND_STATE_INDEX 	0 /*!< Command state buffer index  */
#define TARGET_INTERFACE_INDEX	1 /*!< Target interface buffer index */

/* Operation protocol dictionary parameters */
#define ACTUAL_STATE_INDEX           0x0A00 /*!< Global state index */
#define LAST_REQUESTED_STATE_INDEX   0x0A0A /*!< Global last state index */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static OperationStates ActualState;
static OperationStates LastRequestedState;
/* Private function prototypes -----------------------------------------------*/
OpProtRet OperationFrameCast(OpProtFrame *OPFrame, uint8_t *pBuf, uint32_t Size, uint8_t Mode);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize Transfer protocol
  */
void OperationProtocolInit(void)
{
   /* Initialize All state machines */
  ActualState = INVALID_STATE;
  OperationProtocolNewState(INIT);

  AttachVariableToRegister(ACTUAL_STATE_INDEX, &ActualState, sizeof(ActualState));
  AttachVariableToRegister(LAST_REQUESTED_STATE_INDEX, &LastRequestedState, sizeof(LastRequestedState));
 
}

/**
  * @brief  Initialize Transfer protocol frames
  * @param  Frame		Transfer protocol frame for initialization
  */
int32_t OperationProtocolUpdate(TransProtFrame *TPFrameDest)
{
  int32_t InterfaceID = -1;  
  TransProtFrame *TPFrameTemp = TPFrameDest;
  
    switch(ActualState)
    {
      case INIT:
        InterfaceID = InitProcess(&TPFrameTemp);
        break;
      case CONFIG:
        InterfaceID = ConfigProcess(&TPFrameTemp);
        break;
      case SCAN:
        InterfaceID = ScanProcess(&TPFrameTemp);
        break;
      case INACTIVE:
        InterfaceID = InactiveProcess(&TPFrameTemp);
        break;
      case ACTIVE:
        InterfaceID = ActiveProcess(&TPFrameTemp);
        break;
      case FAULT_DETECTED:
        InterfaceID = FaultDetectedProcess(&TPFrameTemp);
        break;
      case FAULT:
        InterfaceID = FaultProcess(&TPFrameTemp);
        break;
      default: 
        break;
    }
    
    return InterfaceID;
}

/**
  * @brief  Execute a State transition to a new state
  * @param[in]  NewState	Requested state
  * @retval 		TransitionSuccessful if the newstate is reached,
  *             TransitionError otherwise
  */
TransitionRetValues OperationProtocolNewState(OperationStates NewState)
{
  TransitionRetValues RetVal = TransitionSuccessful;
  
  LastRequestedState = NewState;
  
  if(NewState != ActualState)
  {
    switch(ActualState)
    {
      case INIT:
        RetVal = InitStateOnExit();
        break;
      case CONFIG:
        RetVal = ConfigStateOnExit();
        break;
      case SCAN:
        RetVal = ScanStateOnExit();
        break;
      case INACTIVE:
        RetVal = InactiveStateOnExit();
        break;
      case ACTIVE:
        RetVal = ActiveStateOnExit();
        break;
      case FAULT_DETECTED:
        RetVal = FaultDetectedStateOnExit();
        break;
      case FAULT:
        RetVal = FaultStateOnExit();
        break;
      default: 
        break;
    }
      
    if(RetVal == TransitionSuccessful)
    {
      switch(NewState)
      {
        case INIT:
          RetVal = InitStateOnEnter();
          break;
        case CONFIG:
          RetVal = ConfigStateOnEnter();
          break;
        case SCAN:
          RetVal = ScanStateOnEnter();
          break;
        case INACTIVE:
          RetVal = InactiveStateOnEnter();
          break;
        case ACTIVE:
          RetVal = ActiveStateOnEnter();
          break;
        case FAULT_DETECTED:
          RetVal = FaultDetectedStateOnEnter();
          break;
        case FAULT:
          RetVal = FaultStateOnEnter();
          break;
        default: 
          break;
      }
      if(RetVal != TransitionSuccessful)
      {
          ForceFaultSate();
          ActualState = FAULT;
      }
      else
      {
        ActualState = NewState;
      }
    }
  }
  return RetVal;
}

/**
  * @brief  Returns the actual state
  * @retval Actual state.
  */
OperationStates OperationProtocolGetState(void)
{
  return ActualState;
}

/**
  * @brief  Casts standard buffers into Transfer protocol frames and vice versa
  * @param[out] TPFrame Transfer protocol frame to be processed
  * @param[in]  pBuf	 Standard buffer to be processed
  * @param[in]		 Size Number of bytes to be casted
  * @retval 		 0 if OK.
  */
int32_t OperationProtocolProcess(uint8_t **OperationProtFrameOut, uint8_t *OperationProtFrameIn, uint32_t InputSize)
{
    OpProtFrame OPFrame;
    uint8_t *DataIn = OperationProtFrameIn;
    uint8_t *DataOut;
    TransitionRetValues TransitionRet;
	
    /* A ObjectFrame is created from DataIn*/
    OperationFrameCast(&OPFrame, DataIn, InputSize, OPERATION_FROM_BUFF);
  
    if(GetOPCommand(OPFrame) == REQUEST)
    {
      if(OPFrame.Interface == 0xFF)
      {
        TransitionRet = OperationProtocolNewState(GetOPState(OPFrame));
        if(TransitionRet != TransitionSuccessful)
        {
          /* Handle Error */
        }
      }
      else
      {
        if(TransferProtocolGetInterfaceType(OPFrame.Interface) == MBA_BRIDGE)
        {
            SetBusInstanceState(OPFrame.Interface, GetOPState(OPFrame));
        }
        /* if the destination interface is an End bus, update the dictionary state, but not the
         * internal. This interface will be activated in active state.
         */
        else
        {
            TransferProtocolForceInterfaceState(OPFrame.Interface, GetOPState(OPFrame));
        }
      }
      DataOut = (uint8_t *)MemAlloc(OP_FRAME_SIZE);
      DataOut[COMMAND_STATE_INDEX] = REPLY | ActualState;
      DataOut[TARGET_INTERFACE_INDEX] = OPFrame.Interface;
      *OperationProtFrameOut = DataOut;
  }
  else
  {
      /* Handle reply */
  }
  
  return OP_FRAME_SIZE;
}

/*********************************************************************************************/
/*****	STATIC FUNCTIONS 	    **********************************************************/
/*********************************************************************************************/

/**
  * @brief  Casts standard buffers into Operation protocol frames and vice versa
  * @details The transfer protocol data field is read as standard buffer. This function
  *	     translates this buffer into a operation frame to process it.
  * @param[in,out]  OPFrame:  	Operation protocol frame to be processed. Could be the
  *                           	source or the destination buffer in function of the Mode
  *                           	value.
  * @param[in,out]  pBuf:	Standard buffer to be processed. Could be the source or
  *				the destination buffer in function of the Mode value.
  * @param[in]	Size: 		Number of bytes to be casted
  * @param[in]  Mode:		Cast parameters: Direction and cast mode
  * @retval 			OP_SUCCESS if the cast has been executed correctly, OP_ERROR otherwise
  */
OpProtRet OperationFrameCast(OpProtFrame *OPFrame, uint8_t *pBuf, uint32_t Size, uint8_t Mode)
{
  OpProtFrame   *OPTemp = OPFrame;	/* Temporal pointer for data processing */
  OpProtRet  ret = OP_SUCCESS;

  /* If the standard buffer is the input and the Config frame the output: */
  if((Mode & DIR_MASK) == OPERATION_FROM_BUFF)
  {
      OPTemp->StateCommand = pBuf[COMMAND_STATE_INDEX];
      OPTemp->Interface = pBuf[TARGET_INTERFACE_INDEX];
  }
  else
  {
      pBuf[COMMAND_STATE_INDEX] = OPTemp->StateCommand;
      pBuf[TARGET_INTERFACE_INDEX] = OPTemp->Interface;
  }

  return ret;
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

