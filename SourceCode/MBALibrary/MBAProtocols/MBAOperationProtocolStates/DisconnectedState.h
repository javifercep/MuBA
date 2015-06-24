/**
  ******************************************************************************
  * @file    DisconnectedState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Disconnected state functions 
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
  *	@addtogroup Disconnected_State
  *	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISCONNECTED_STATE_H
#define __DISCONNECTED_STATE_H

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

TransitionRetValues DisconnectedStateOnEnter(void);
int32_t DisconnectedProcess(TransProtFrame **GeneratedFrame);
TransitionRetValues DisconnectedStateOnExit(void);


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
#endif /*__DISCONNECTED_STATE_H */
