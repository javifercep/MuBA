/**
  ******************************************************************************
  * @file    BUSApp.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains BUS (CAN, USB, LIN, etc) application
  * @details A task for each available bus interface is created and managed. All
  *	     the taskschave access to the MBA instance to process the network frames. Two
  *	     modes will be available to include this functionality in multiple
  *          architectures:
  *		- Through a RTOS / OS. Each bus interface has its own thread. OS tools like
  *		  mutex and mailbox are used for synchronization and shared resources.
  *		- Loop process. Where a OS cannot be implemented or in some special applic-
  *		  ations, these functions are included in a super loop structure. BufferFu-
  *		  nctions API and other tools will be used for task communication and sync-
  *		  hronization.
  * 	     All the Bus tasks follow a common structure to increase the modularity and
  * 	     scalability of the project. Refercto @ref BUSAPI.c file for further informat-
  * 	     ion.
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  *	@addtogroup Bus
  *	@{
*/

/**
  *@addtogroup Bus_Application
  *@{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUSAPP_H
#define __BUSAPP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#include "../OSSupport.h"		/*!< Operating sytem functions */
/* Exported define -----------------------------------------------------------*/
#define BUS_QUEUE_SIZE	8 /*!<default queue sizes for bus threads */
/* Thread paramters definition */
#define BUS_STACKSIZE 	0		/*!< Thread stack size */

#define BUS_ID_1	0	/* Check BUSInstance Array */
#define BUS_ID_2	1	/* Check BUSInstance Array */
#define BUS_ID_3    2	/* Check BUSInstance Array */
#define BUS_ID_4	3	/* Check BUSInstance Array */
#define BUS_ID_5	4	/* Check BUSInstance Array */
#define BUS_ID_6    5	/* Check BUSInstance Array */
#define BUS_ID_7	6	/* Check BUSInstance Array */
#define BUS_ID_8	7	/* Check BUSInstance Array */

	 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int InitBUSProcess(void);
void LaunchBUSInstance(uint8_t BusInstanceID);

/**
  *@}
  */
/**
  *@}
  */

#ifdef __cplusplus
}
#endif
#endif /* __BUSAPP_H */
