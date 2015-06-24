/**
  ******************************************************************************
  * @file    MBAConfigProtocol.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA configuration protocol functions 
  *	     for upper layers
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
  *	@addtogroup MBA_Configuration_Protocol
  *	@{
  *		@brief Configuration Protocol.
	*		@details 
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MBACONFIGPROTOCOL_H
#define __MBACONFIGPROTOCOL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../MBATypes.h"
#include "../MBALib.h"
/* Exported define -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  *@brief Config protocol return values
  */
typedef enum
{
	CP_ERROR = -1,	/*!< An error occur during function execution */
	CP_SUCCESS = 0	/*!< The function has been executed successfully */
}ConfigProtRet;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t ConfigProtocolGetSourceNodeID(uint8_t *ConfigProtFrame);
void ConfigProtocolSetSourceNodeID(uint8_t *ConfigProtFrame, uint8_t SourceNodeID);
uint32_t ConfigProtocolProcess(uint8_t **ConfigProtFrameOut, uint8_t *ConfigProtFrameIn, uint32_t InputSize);

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

#endif /*__MBACONFIGPROTOCOL_H */
