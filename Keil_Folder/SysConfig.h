/**
  ******************************************************************************
  * @file    SysConfig.h
  * @author  Javier Fernández Cepeda
  * @brief   This file configures the system application needs.
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @page Configuration
  * @{
  *	@brief		A set of parameters must be set to adapt the FW to the target
  *			device
  *	@details	The most relevant parameters are:
  *			- The RTOS / OS used.
  *			- Special modes for debugging and testing
  *			- Available interfaces in the device
  *			- Compiler settings
  *			- External libraries settings
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSCONFIG_H
#define __SYSCONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef ECLIPSE
/*----------------------------------------------------------------------------*/
/*	GENERAL SETTINGS																	*/
/*----------------------------------------------------------------------------*/ 
#define DEBUG_ACTIVE 		0 /*!< If debug is active, Debug messages are sent through USB  */
#define SYSTEM_TEST_MODE 	0 /*!< If set, allows to run test functions   */
	 
/*----------------------------------------------------------------------------*/
/*	RTOS SETTINGS																	*/
/*----------------------------------------------------------------------------*/	 
#define OS_ACTIVE 		1 /*!< Enable / disable the OS. In time-critial applications
				   *   may not be interesting to use an OS even a RTOS */

 /* Select the RTOS */
#if OS_ACTIVE != 0
	 
  /*** Select RTOS ************************************************************/
  #define COOS 			0 /*!< Legacy. The first implementation was with this RTOS  */
  #define FREERTOS 		0 /*!< Free source code. It will be always available */
  #define KEIL_RTX		1 /*!< For KEIL contest.  */
  #define WINDOWS		0 /*!< For PC instance.  */
	
  /**** RTOS Services *********************************************************/
#if WINDOWS == 0
  #define HEARTBEAT_TIMER	1 /*!< If set, a LED will blink continuosly. It helps to
							   * developer to know if the board is alive.  */
#endif
#endif

/*----------------------------------------------------------------------------*/
/*	MBADEVICE SETTINGS																*/
/*----------------------------------------------------------------------------*/
#define AVAILABLE_INTERFACES	3  /*!<  Available interfaces in the device */

/* Determines BUS interfaces */
#define USB_API    		1 /*!<  USB API activated */
#define USB_HOST_API	0 /*!<  USB Host API activated */
#define SPI_API			  1 /*!<  SPI API activated */
#define CAN_API			  0 /*!<  CAN API activated */
#define LIN_API			  0 /*!<  LIN API activated */
#define	USART_API		  1 /*!<  USART API activated */
#define I2C_API			  0 /*!<  I2C API activated */
#define SOCKET_API		0 /*!<  SOCKETS API activated */

#define ENABLE_FLOW_CONTROL 0 /*!<  Enable additional buffers into each BUS */

/* Device support*/
#define DEVICE_SUPPORT		1 /*!<  For HW that need initialization or has additional functions */
/* MCU */
#define MCU_STM32F4XX		  1  /*!<  Indentifies specific HW */
/*----------------------------------------------------------------------------*/
/*	COMPILER SETTINGS																*/
/*----------------------------------------------------------------------------*/
#define ARMCC_COMPILER		1 /*!< For Keil contest */
#define GNU_COMPILER		  0 /*!< Is free. It will be always available */
#define CYGWIN_COMPILER		0 /*!< For windows instance */

/*----------------------------------------------------------------------------*/
/*	STORAGE & MEMORY SUPPORT																*/
/*----------------------------------------------------------------------------*/
#define DINAMIC_MEMORY_CONTROL	0
#define DICTIONARY_IN_FILE	    0
/**
 * @}
 */
#else
 /*----------------------------------------------------------------------------*/
 /*	GENERAL SETTINGS														*/
 /*----------------------------------------------------------------------------*/
 #define DEBUG_ACTIVE 		0 /*!< If debug is active, Debug messages are sent through USB  */
 #define SYSTEM_TEST_MODE 	0 /*!< If set, allows to run test functions   */

 /*----------------------------------------------------------------------------*/
 /*	RTOS SETTINGS			 */
 /*----------------------------------------------------------------------------*/
 #define OS_ACTIVE 		1 /*!< Enable / disable the OS. In time-critial applications
 				   	       *    may not be interesting to use an OS even a RTOS */

  /* Select the RTOS */
 #if OS_ACTIVE != 0

   /*** Select RTOS ************************************************************/
   #define COOS 		0 /*!< Legacy. The first implementation was with this RTOS  */
   #define FREERTOS 	0 /*!< Free source code. It will be always available */
   #define KEIL_RTX		0 /*!< For KEIL contest.  */
   #define WINDOWS		1 /*!< For PC instance.  */

   /**** RTOS Services *********************************************************/
 #if WINDOWS == 0
   #define HEARTBEAT_TIMER	1 /*!< If set, a LED will blink continuosly. It helps to
 							   * developer to know if the board is alive.  */
 #endif
 #endif

 /*----------------------------------------------------------------------------*/
 /*	MBADEVICE SETTINGS																*/
 /*----------------------------------------------------------------------------*/
 #define AVAILABLE_INTERFACES	2  /*!<  Available interfaces in the device */

 /* Determines BUS interfaces */
 #define USB_API    		0 /*!<  USB API activated */
 #define USB_HOST_API		1 /*!<  USB Host API activated */
 #define SPI_API			0 /*!<  SPI API activated */
 #define CAN_API			0 /*!<  CAN API activated */
 #define LIN_API			0 /*!<  LIN API activated */
 #define USART_API			0 /*!<  USART API activated */
 #define I2C_API			0 /*!<  I2C API activated */
 #define SOCKET_API			1 /*!<  SOCKETS API activated */

 #define ENABLE_FLOW_CONTROL 0 /*!<  Enable additional buffers into each BUS */

 /* Device support*/
 #define DEVICE_SUPPORT		0 /*!<  For HW that need initialization or has additional functions */
 /* MCU */
 #define MCU_STM32F4XX		0  /*!<  Indentifies specific HW */
 /*----------------------------------------------------------------------------*/
 /*	COMPILER SETTINGS																*/
 /*----------------------------------------------------------------------------*/
 #define ARMCC_COMPILER		0 /*!< For Keil contest */
 #define GNU_COMPILER		0 /*!< Is free. It will be always available */
 #define CYGWIN_COMPILER	1 /*!< For windows instance */

 /*----------------------------------------------------------------------------*/
 /*	STORAGE & MEMORY SUPPORT																*/
 /*----------------------------------------------------------------------------*/
 #define DINAMIC_MEMORY_CONTROL	0
 #define DICTIONARY_IN_FILE	0
#endif
#if (ARMCC_COMPILER != 0) && (GNU_COMPILER != 0) && (CYGWIN_COMPILER != 0)
#error "More than one compiler selected."
#endif
 
#ifdef __cplusplus
}
#endif

#endif /* __SYSCONFIG_H */
