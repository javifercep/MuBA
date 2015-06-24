/**
  ******************************************************************************
  * @file    DeviceApp.c
  * @author  Javier Fernández Cepeda
  * @brief   This file contains general application functions.
	******************************************************************************
	* Copyright (c) 2015, Javier Fernandez. All rights reserved.
  ******************************************************************************
	* @addtogroup Device
	*	@{
	*		@brief	The device module includes all functionalities related to each 
	*						specific device.
	*		@details The first implementation was developed for low speed industrial
	*						 protocols where the time control was the most critical element. 
	*						 Current implementation has been designed to add this firmware in
	*						 different architectures to reach high speed buses like Ethernet
	*						 based protocols. Therefore an abstract API is needed to include the
	*						 same services to different devices.
	*		
	*		@addtogroup Device_Application
	*		@{
	*			@brief	The device services are launched.
	*			@details The available services are:
	*							- Heartbeat LED. This LED is used to know the status of the device
*/

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"

#if HEARTBEAT_TIMER != 0
#include "../OSSupport.h"                    
#include "DeviceApp.h"
#include "../../PHDLLAYER/BOARDAPI/boardAPI.h"
#include "../../MBALibrary/MBALib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#if HEARTBEAT_TIMER != 0
#define HEARTBEAT_PERIOD 	500 	/*!< in ticks: 1 tick = 1 ms */
#define HEARTBEAT_LED			LED4	/*!< LED used for this purpose */
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if HEARTBEAT_TIMER != 0
static TIMER_ID HeartBeat_id;   /*!< timer id */
static uint32_t  HeartBeat_arg; /*!< argument for the timer callback function */
#endif
static uint16_t MockValue;
/* Private function prototypes -----------------------------------------------*/
#if HEARTBEAT_TIMER != 0
static void HeartBeatCallback  (void const *arg);  /*!< prototype for timer callback function */
static DEFINE_TIMER(HeartBeat, HeartBeatCallback);    /*!< define timer */
#endif
static void MockFunction (void);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the XBA device
  */
void InitDevice(void)
{
		SystemClock_Config();
		BoardInitialize();
}
	
/**
  * @brief  Initializes soft Timer - Heart beat initialization
  * @param  None
  * @retval None
  */
void InitDeviceProcess (void) 
{
  OSRetValue  status;    // function return status
 
  // Create periodic timer
  HeartBeat_arg = NULL;
  HeartBeat_id = CreateTimer(osTimer(HeartBeat), osTimerPeriodic, &HeartBeat_arg);
  if (HeartBeat_id != NULL)   // Periodic timer created 
	{     
		// start timer with periodic 500 ms interval
    TimerStart(status, HeartBeat_id, HEARTBEAT_PERIOD);     
    if (status != OS_OK)  
		{
      // Timer could not be started
    }
  }	
	/* Add device specific variables and callbacks into the MBA Dictionary */
	AttachVariableToRegister(0xA000, &MockValue, sizeof(MockValue));
	AttachCallBackToRegister(0xA000, MockFunction);
}

/*********************************************************************************************/
/*****		STATIC FUNCTIONS		**********************************************************/
/*********************************************************************************************/

/**
  * @brief  Soft Timer callback - Updates heart beat LED
  * @param  arg None
  */
static void HeartBeatCallback  (void const *arg)  
{
	LEDToggle(HEARTBEAT_LED);
}

/**
  * @brief  Soft Timer callback - Updates heart beat LED
  * @param  arg None
  */
void MockFunction(void)
{
	if((MockValue & 0x1) == 0x1)
	{
		LEDOn(LED1);
	}
	else
	{
		LEDOff(LED1);
	}

	if((MockValue & 0x2) == 0x2)
	{
		LEDOn(LED2);
	}
	else
	{
		LEDOff(LED2);
	}

	if((MockValue & 0x4) == 0x4)
	{
		LEDOn(LED3);
	}
	else
	{
		LEDOff(LED3);
	}
}

/**
	* @}
	*/
/**
	* @}
	*/

#endif
