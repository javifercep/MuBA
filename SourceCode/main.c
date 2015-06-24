/**
  ******************************************************************************
  * @file    main.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the main application
  * @details The main function inializes and starts all the modules.
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @page Overview
  * @{
  *
  *	@brief  The Multi-Bus analyzer project pretends to offer a flexible hardware
  *		design and a firmware & software implementation to create custom bridges
  *		between two buses /protocols interface such as CAN, LIN, FlesRay, etc.
  * 	@details The MBA Firmware is based on two main elements:
  *		 - Multi-bus analyzer library. This library offer a set of protocols
  *		   that allows to configure all the parameters needed to configure a
  *		   bridge between two Bus. Furthermore, this Library is able to attach
  *		   custom higher protocol to any of the available interfaces in a device.
  *		 - Bus instance management. An instance for each available Bus in the
  *		   device is created and is the responible of the data transmission and
  *		   protocol casting.
  *
  *		   On the other hand, if the device has specific special features, such as
  *		   a heartbeat led function, a device process is launch to include this funtion
  *		   alities.
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"

#include "APPLAYER/OSSupport.h"

#if   DEVICE_SUPPORT > 0
#include "APPLAYER/DeviceInterface/DeviceApp.h"
#endif

#include "APPLAYER/Communication/BUSApp.h"
#include "APPLAYER/Communication/MBAApp.h"

/**
  * @brief  initialize and start the system
  * @param  None
  * @retval None
  */
int main (void) {
	
    /* Initialize Clock sources and HW components */
#if   DEVICE_SUPPORT > 0
    InitDevice();
#endif

    /* Initialize CMSIS-RTOS */
    OS_INIT();

    /* Create BUS interfaces resources: Queue, Mutex...*/
    InitBUSProcess();
    /* Initialize Main MBA thread*/
    InitMBAProcess();
#if   DEVICE_SUPPORT > 0
    InitDeviceProcess();
#endif
    
  /* Start thread execution */
    OS_START();

    return 0;
}
