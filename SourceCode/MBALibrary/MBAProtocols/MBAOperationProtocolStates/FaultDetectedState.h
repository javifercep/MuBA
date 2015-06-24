/**
  ******************************************************************************
  * @file    FaultDetectedState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Fault Detected state functions 
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
  *	@addtogroup Fault_Detected_State
  *	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FAULT_DETECTED_STATE_H
#define __FAULT_DETECTED_STATE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../../MBATypes.h"
#include "../MBATransferProtocol.h"
#include "../MBAOperationProtocol.h"
	 
/* Exported define -----------------------------------------------------------*/ 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

TransitionRetValues FaultDetectedStateOnEnter(void);
int32_t FaultDetectedProcess(TransProtFrame **GeneratedFrame);
TransitionRetValues FaultDetectedStateOnExit(void);


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
	
#ifdef __cplusplus
}
 
#endif
#endif /*__FAULT_DETECTED_STATE_H */
