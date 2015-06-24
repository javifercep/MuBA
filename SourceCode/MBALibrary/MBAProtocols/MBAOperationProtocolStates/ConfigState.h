/**
  ******************************************************************************
  * @file    ConfigState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Config state functions 
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
  *	@addtogroup Config_State
  *	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_STATE_H
#define __CONFIG_STATE_H

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

TransitionRetValues ConfigStateOnEnter(void);
int32_t ConfigProcess(TransProtFrame **GeneratedFrame);
TransitionRetValues ConfigStateOnExit(void);


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
#endif /*__CONFIG_STATE_H */
