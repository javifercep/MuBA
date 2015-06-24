/**
  ******************************************************************************
  * @file    MBALib.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA Library for upper layers
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
  *		@brief Multi-Bus Analyzer Library configuration.
  *		@details
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MBALIB_H
#define __MBALIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include  "MBAProtocols/MBATransferProtocol.h"
#include  "MBAProtocols/MBAOperationProtocol.h"
#include  "MBADictionary/MBADictionary.h"

/* Exported define -----------------------------------------------------------*/
/******************************************************************************/
/*	Available protocols & functions	                                      */
/******************************************************************************/
/* These defines indicate which MBA protocols are available                   */

/* This define enables the TRANSFER PROTOCOL 	                              */
#define TRANSFER_PROTOCOL			1

/* This define enables the CONFIGURATION PROTOCOL                             */
#define CONFIGURATION_PROTOCOL			1

/* This define enables the OPERATION PROTOCOL	                              */
#define OPERATION_PROTOCOL			1

/* If Log is active, Log messages are sent through USB                        */
#define LOG_ACTIVE 				0

/* Number of MBALIB process executed. This value is usually 1 */
#define MBALIB_INSTANCES			1 	

/* Default size of the INPUT QUEUE. This QUEUE is used to receive data from all
	 the Bus instances. */
#define MBA_QUEUE_SIZE       				16  

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define MBAInit()               OperationProtocolInit();
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

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
#endif /* __MBALIB_H */
