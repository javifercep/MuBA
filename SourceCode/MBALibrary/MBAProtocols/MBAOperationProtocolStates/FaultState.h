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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FAULT_STATE_H
#define __FAULT_STATE_H

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

TransitionRetValues FaultStateOnEnter(void);
int32_t FaultProcess(TransProtFrame **GeneratedFrame);
TransitionRetValues FaultStateOnExit(void);
void ForceFaultSate(void);


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
#endif /*__FAULT_STATE_H */
