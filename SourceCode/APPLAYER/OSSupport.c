/**
  ******************************************************************************
  * @file    BUSApp.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains global OS functions
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"	/*!< System paramters */
#include "OSSupport.h"	/*!< Operating sytem functions */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/				
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Global mutex wait function.
  * @details This function process the return value of each OS specific mutex
  *          module.
  * @param[in] 	MutexID Mutex identification
  * @retval	OS_OK if the thread get access, OS_ERROR Otherwise
  */
OSRetValue MutexWaitFunc(MUTEX_ID *MutexID)
{
  OSRetValue ret;
  MUTEX_RET RetMutex;

  #if KEIL_RTX != 0

  RetMutex = osMutexWait(*MutexID, osWaitForever);
  switch(RetMutex)
  {
	  case osOK:
		  ret = OS_OK;
		  break;
	  case osErrorTimeoutResource:
		  ret = OS_TIMEOUT;
		  break;
	  case osErrorResource:
		  ret = OS_ERROR;
		  break;
	  case osErrorParameter:
		  ret = OS_ERROR;
		  break;
	  case osErrorISR:
		  ret = OS_ERROR;
		  break;
	  default:
		  ret = OS_ERROR;
		  break;
  }
  #elif WINDOWS > 0
  RetMutex = pthread_mutex_trylock(MutexID);
  if(RetMutex == 0)
  {
	ret = OS_OK;
  }
  else
  {
	ret = OS_ERROR;
  }
  #endif

  return ret;
}


/**
  * @brief   Global mail get function.
  * @details This function process the return value of each OS specific mail
  *	     module and returns a mail message is available.
  * @param[in] 	MailID Mail Queue identification
  * @param[out] MailMsg Null if there is not data available, pointer to data otherwise
  * @retval	OS_OK if the thread get access, OS_ERROR Otherwise
  */
OSGlobalRet MailGetFunc(MAIL_QUEUE_ID *MailID)
{
  OSGlobalRet ret;

  #if KEIL_RTX != 0
  MAIL_QUEUE_RET BusQueueEvent;
  BusQueueEvent = osMailGet(*MailID, osWaitForever);
  if (BusQueueEvent.status == osEventMail)
  {
	  /* Copy data from Mailbox */
	  ret.Data = BusQueueEvent.value.p;
	  ret.RetValue = OS_OK;
  }
  else
  {
	  ret.Data = NULL;
	  ret.RetValue = OS_ERROR;
  }
  #elif WINDOWS != 0
  ret.Data = pqueue_pop(MailID);
  ret.RetValue = OS_OK;
  #endif

  return ret;
}


#if HEARTBEAT_TIMER > 0
/**
  * @brief  	 Global Timer start function.
  * @details	This function starts a software timer.
  * @param[in] 	TimerID Timer identification
  * @param[in] 	Period In OS ticks
  * @retval	OS_OK if the thread get access, OS_ERROR Otherwise
  */
OSRetValue TimerStartFunc(TIMER_ID TimerID, unsigned int Period)
{
	OSRetValue ret;
	TIMER_RET  status;  
	
	#if KEIL_RTX != 0
	/* start timer with periodic 500 ms interval */
	status = osTimerStart (TimerID, Period);            
	if (status != osOK)  
	{
		ret = OS_OK;
	}
	else
	{
		ret = OS_ERROR;
	}
	#endif
	
	return ret;
}
#endif
