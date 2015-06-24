/**
  ******************************************************************************
  * @file    MBAOperationProtocol.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA operation protocol functions 
  *			 for upper layers
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
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MBAOPERATIONPROTOCOL_H
#define __MBAOPERATIONPROTOCOL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../MBATypes.h"
#include "MBATransferProtocol.h"
/* Include BUSAPI interface for the BUS state machine management */
#include "../../PHDLLAYER/BUSAPI/BUSAPI.h"
	 
/* Exported define -----------------------------------------------------------*/ 
/* Exported types ------------------------------------------------------------*/
/**
 * @brief Node states
 */
typedef enum
{
  INIT = 0,      //!< INIT
  CONFIG,        //!< CONFIG
  SCAN,          //!< SCAN
  INACTIVE,      //!< INACTIVE
  ACTIVE,        //!< ACTIVE
  FAULT_DETECTED,//!< FAULT_DETECTED
  FAULT,         //!< FAULT
  INVALID_STATE  //!< INVALID_STATE
}OperationStates;

/**
 * @brief Transition results
 */
typedef enum
{
  TransitionError      = -1,//!< TransitionError
  TransitionSuccessful = 0  //!< TransitionSuccessful
}TransitionRetValues;

/**
 * @brief Local return function values
 */
typedef enum
{
  OP_ERROR = -1,	/*!< An error occur during function execution */
  OP_SUCCESS = 0	/*!< The function has been executed successfully */
}OpProtRet;

/**
 * @brief Operation protocol frame
 */
typedef struct
{
  uint8_t	StateCommand;	/*!< Command and new state */
  uint8_t 	Interface;	/*!< Target interface */
}OpProtFrame;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
  * @brief Reads the requested/replied state
  */
#define GetOPState(OpProtFrame)     (OPFrame.StateCommand & 0x7F)
/**
  * @brief Reads the transmitted command: Request or reply
  */
#define GetOPCommand(OpProtFrame)   ((OPFrame.StateCommand) & 0x80)
/**
  * @brief Reads the requested/replied state
  */
#define GetOPStateP(OpProtFrame)     (OPFrame->StateCommand & 0x7F)
/**
  * @brief Reads the transmitted command: Request or reply
  */
#define GetOPCommandP(OpProtFrame)   ((OPFrame->StateCommand) & 0x80)
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization */
void OperationProtocolInit(void);

/* Main operation functions */ 
int32_t OperationProtocolUpdate(TransProtFrame *TPFrameDest);
TransitionRetValues OperationProtocolNewState(OperationStates NewState);
OperationStates OperationProtocolGetState(void);

/* Frame management */
int32_t OperationProtocolProcess(uint8_t **OperationProtFrameOut, uint8_t *OperationProtFrameIn, uint32_t InputSize);

/**
  *@}
  */
/**
  *@}
  */
/**
  *@}
  */
	
#ifdef __cplusplus
}
 
#endif
#endif /*__MBATRANSFERPROTOCOL_H */
