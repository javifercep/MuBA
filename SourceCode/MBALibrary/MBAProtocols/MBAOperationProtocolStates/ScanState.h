/**
  ******************************************************************************
  * @file    ScanState.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the Scan state functions 
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
  *	@addtogroup Scan_State
  *	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SCAN_STATE_H
#define __SCAN_STATE_H

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

TransitionRetValues ScanStateOnEnter(void);
int32_t ScanProcess(TransProtFrame **GeneratedFrame);
TransitionRetValues ScanStateOnExit(void);


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
#endif /*__SCAN_STATE_H */
