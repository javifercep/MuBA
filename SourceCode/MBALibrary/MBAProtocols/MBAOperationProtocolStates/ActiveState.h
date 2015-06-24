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
  * @{
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ACTIVE_STATE_H
#define __ACTIVE_STATE_H

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

TransitionRetValues ActiveStateOnEnter(void);
int32_t ActiveProcess(TransProtFrame **GeneratedFrame);
TransitionRetValues ActiveStateOnExit(void);


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
#endif /*__ACTIVE_STATE_H */
