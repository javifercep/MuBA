/**
  ******************************************************************************
  * @file    BUSAPI.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains BUS API for manage the target BUS to be sniffed.
	*******************************************************************************
	* Copyright (c) 2015, Javier Fernandez. All rights reserved.
	*******************************************************************************
	*
	* @addtogroup Bus
	*	@{
	*
	*	@addtogroup Bus_Interface
	*	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUSAPI_H
#define __BUSAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if MCU_STM32F4XX
#include "stm32f4xx.h"
#endif

#include <stdint.h>
#include "SysConfig.h"
/* Exported define ------------------------------------------------------------*/
#define BUS_INSTANCES		  AVAILABLE_INTERFACES
   
/* Global bus parameters */
#define BUS_FRAME_DETECTION         0x0100 /*!< Frame detection strategy */
#define BUS_TIMEOUT                 0x0200 /*!< Timeout for waiting data */
#define BUS_TIMEOUT_DETECTION       0x0300 /*!< Timeout used for frame detection */
#define BUS_FIELD_SIZE_DETECTION    0x0400 /*!< Location of the field with frame
                                            *   size information */
#define BUS_END_FIELD_DETECTION     0x0500 /*!< Value of the end detection field */

/* Frame detection option */
#define FRAME_DETECTION_SIZE        0  /*!< A field indicates the size of the frame */
#define FRAME_DETECTION_END_FIELD   1  /*!< The last field indicates the end of frame */
#define FRAME_DETECTION_TIMEOUT     2  /*!< The detection of the end of frame is based
                                            on a timeout after the last data is received*/
  
	 
/* Exported types ------------------------------------------------------------*/
 /**
  * @brief BUS interface states.
  */
 typedef enum
 {
   BUS_INIT = 0, //!< BUS_INIT
   BUS_INACTIVE, //!< BUS_INACTIVE
   BUS_ACTIVE,   //!< BUS_ACTIVE
   BUS_STOP      //!< BUS_STOP
 }BusInstanceStates;

 /**
  * @brief BUS interface transitions
  */
 typedef enum
 {
   BUS_NO_TRANSITION = 0,//!< BUS_NO_TRANSITION
   BUS_INIT_2_INACTIVE,  //!< BUS_INIT_2_INACTIVE
   BUS_INACTIVE_2_ACTIVE,//!< BUS_INACTIVE_2_ACTIVE
   BUS_ACTIVE_2_STOP     //!< BUS_ACTIVE_2_STOP
 }BusInstanceTransitions;

 /**
  * @ brief Bus Instance
  */
typedef struct
{
  int32_t  (*Init) 	      		(void);				//!< Init
  int32_t  (*DeInit) 	      	(void);				//!< DeInit
  uint32_t (*DataAvailable)     (void);				//!< DataAvailable
  uint32_t (*SizeDataAvailable) (void);				//!< SizeDataAvailable
  uint32_t (*Read)	      		(uint8_t *data, uint32_t size);	//!< Read
  uint32_t (*Write)	      		(uint8_t *data, uint32_t size);	//!< Write
  int32_t  (*Configuration)     (uint16_t param, void *arg);	//!< Configuration
}const BusInstance;
/* Exported constants --------------------------------------------------------*/
extern BusInstance BusInstances[];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
BusInstanceStates GetBusInstanceState(uint8_t InterfaceID);
BusInstanceTransitions GetBusInstanceStateTransition(uint8_t InterfaceID);
void SetBusInstanceState(uint8_t InterfaceID, BusInstanceStates State);
void ForceBusInterfaceStop(uint8_t InterfaceID);

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

#endif /* __BUSAPI_H */
