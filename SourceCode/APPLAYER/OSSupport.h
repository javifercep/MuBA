/**
  ******************************************************************************
  * @file    OSSupport.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains links to the OS used by the application
	*
	*******************************************************************************
	* Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
	*
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OSSUPPORT_H
#define __OSSUPPORT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#include "OSSupport.h"
	
#if OS_ACTIVE != 0
	 /* Common Exported types ------------------------------------------------------*/
	 /**
		* @brief Global OS enum return values
		*/
	 typedef enum
	 {
		 OS_TIMEOUT = -2,		/*!< OS timeout reached */
		 OS_ERROR 	= -1,		/*!< An OS error has been produced */
		 OS_OK 			= 0			/*!< OS resource works correclty*/
	 } OSRetValue;
	 
	 /**
		* @brief Global ret value.
		*/
	 typedef struct
	 {
		 int RetValue; 	/*!< OS functions return value. See @ref OsRetValue*/
		 void*	 Data;	/*!< Pointer to data returned by a OS function*/
	 }OSGlobalRet;
	
	 typedef enum
	 {
		SYNC_TOOL_ERROR 	= -3, /*!<Synchronization tool cannot be initializated */
		BUFFER_ERROR 		= -2, /*!<Mail queue or buffer cannot be initializated*/
		TASK_ERROR 			= -1, /*!<Task / Thread cannot be initializated */
		INSTANCE_OK 		= 0		/*!<Instance correctly initializated*/
	}InstanceRet;
	/**
		* @addtogroup KEIL_RTX
		*	@{
		*		@brief KEIL RTX OS function mapping. Refer to RTX doc 
		*		http://www.keil.com/support/man/docs/rlarm/rlarm_ar_artxarm.htm
		*/
	#if KEIL_RTX != 0
		/* Includes ------------------------------------------------------------------*/
		#include <cmsis_os.h>     		/*!< CMSIS RTOS header files */
		#define osObjectsPublic         // define objects in main module
		#include "osObjects.h"          // RTOS object definitions	 
	 
		/* Exported define -----------------------------------------------------------*/
		#define THREAD_REF(name)			osThread(name)
		#define MUTEX_REF(name)				osMutex(name)
		#define MAIL_QUEUE_REF(name)	osMailQ(name)
		#define TIMER_REF(name)
				
		/* Exported types ------------------------------------------------------------*/
		#define MUTEX_RET					osStatus		
		#define MAIL_QUEUE_RET		osEvent
		#define TIMER_RET					osStatus
	 
		#define THREAD_ID					osThreadId
		#define MUTEX_ID					osMutexId
		#define	MAIL_QUEUE_ID			osMailQId
		#define TIMER_ID					osTimerId
    
    #define OS_THREAD_TYPE	  void
    #define OS_THREAD_ARG		  void const *
	 
		
		/* Exported constants --------------------------------------------------------*/
		/* Exported macro ------------------------------------------------------------*/
		#define OS_INIT()					osKernelInitialize()
		#define OS_START()				osKernelStart()
		
		#define DEFINE_THREAD(func, prior, inst, size) 	osThreadDef(func, prior, inst, size)
		#define DEFINE_MUTEX(name)						          osMutexDef(name)
		#define DEFINE_MAIL_QUEUE(name,size,data) 		  osMailQDef(name, size, data) 
		#define DEFINE_TIMER(name, callback)			      osTimerDef(name, callback);

		/* Exported variables --------------------------------------------------------*/

		/* Exported functions ------------------------------------------------------- */
		/* Init functions */
		#define CreateThread(ret,threadid,thread, arg)	threadid = osThreadCreate (thread, arg)
    #define StopThread(ret, threadid);			        ret = osThreadTerminate(threadid);
    #define ForceStopThread(ret,threadid);		      ret = osThreadTerminate(threadid);
		
		/* Mutex functions */
		#define CreateMutex(retID, mutex)				        retID = osMutexCreate(mutex)
		#define MutexWait(MutexID) 						          MutexWaitFunc(&MutexID)
		OSRetValue MutexWaitFunc(MUTEX_ID *MutexID);
		#define MutexRelease(MutexID)					          osMutexRelease(MutexID)
		
		/* Mail function */
		#define CreateMailQueue(ret, retID, queue, param)	  retID = osMailCreate(queue, param);
		#define MailAlloc(RetData,MailID, time)				      RetData = osMailAlloc(MailID, time)
		#define MailFree(MailID, data)						          osMailFree(MailID, data)
		#define MailPut(MailID, data)						            osMailPut(MailID, data)
		#define MailGet(RetMail,MailID)			                RetMail = MailGetFunc(&MailID)		
		OSGlobalRet MailGetFunc(MAIL_QUEUE_ID *MailID);
		
		/* Timer function */
		#define CreateTimer(timer, mode, arg) 			osTimerCreate (timer, mode, arg)
    #define TimerStart(Ret, TimerID, Period)    Ret = TimerStartFunc(TimerID, Period)
		OSRetValue TimerStartFunc(TIMER_ID TimerID, unsigned int Period);
	/**
		*	@}
		*/
	
	#elif FREERTOS != 0
	/**
		* @addtogroup FREERTOS
		*	@{
		*		@brief FreeRTOS OS function mapping. Refer to FreeRTOS doc 
		*		http://www.freertos.org/RTOS.html
		*/
	/* Includes ------------------------------------------------------------------*/
	#include <FreeRTOS.h>             		/*!< FreeRTOS header files */ 
	/* Exported define -----------------------------------------------------------*/
	#define THREAD_REF(name)												
	#define MUTEX_REF(name)													
	#define MAIL_QUEUE_REF(name)									
			
	/* Exported types ------------------------------------------------------------*/
	#define MUTEX_RET																							
	#define MAIL_QUEUE_RET													
 
	#define THREAD_ID																
	#define MUTEX_ID																
	#define	MAIL_QUEUE_ID														
 
	
	/* Exported constants --------------------------------------------------------*/
	/* Exported macro ------------------------------------------------------------*/
	#define DEFINE_THREAD(func, prior, inst, size) 	
	#define DEFINE_MUTEX(name)											
	#define DEFINE_MAIL_QUEUE(name,size,data) 			 

	/* Exported variables --------------------------------------------------------*/

	/* Exported functions ------------------------------------------------------- */
	/* Init functions */
	#define CreateThread(thread, arg)								
	#define CreateMutex(mutex)											
	#define CreateMailQueue(queue, param)						
	
	/* Mutex functions */
	#define MutexWait(MutexID)
	#define MutexRelease(MutexID)								
	
	/* Mail function */
	#define MailAlloc(MailID, time)								
	#define MailFree(MailID, data)								
	#define MailPut(MailID, data)								
	#define MailGet(MailID)
	/**
	  *@}
	  */
	#elif WINDOWS != 0
	/**
	* @addtogroup WINDOWS
	*	@{
	*		@brief Windos OS function mapping. Based on pThread.
	*/
	/* Includes ------------------------------------------------------------------*/
	#include <pthread.h>             	/*!< pThread header file */
	#include "../TOOLS/pqueue.h"
	#include "../TOOLS/MemoryManagement.h"
	#include "../MBALibrary/MBAProtocols/MBATransferProtocol.h"

	/* Exported define -----------------------------------------------------------*/
	#define TIMER_AVAILABLE 	0


	#define THREAD_REF(name)	name
	#define MUTEX_REF(name)
	#define MAIL_QUEUE_REF(name)

	/* Exported types ------------------------------------------------------------*/
	#define MUTEX_RET		int
	#define MAIL_QUEUE_RET	int

	#define THREAD_ID	 	pthread_t
	#define MUTEX_ID	 	pthread_mutex_t
	#define MAIL_QUEUE_ID		pqueue

	#define OS_THREAD_TYPE	void*
	#define OS_THREAD_ARG		void*


	/* Exported constants --------------------------------------------------------*/
	/* Exported macro ------------------------------------------------------------*/
	#define OS_INIT()
	#define OS_START()		pthread_exit(NULL);

	#define DEFINE_THREAD(func, prior, inst, size)
	#define DEFINE_MUTEX(name)
	#define DEFINE_MAIL_QUEUE(name,size,data)

	/* Exported variables --------------------------------------------------------*/

	/* Exported functions ------------------------------------------------------- */
	/* Thread functions */
	#define CreateThread(ret,threadid,thread,arg)   	ret=pthread_create(&threadid, NULL, thread, arg)
	#define StopThread(ret, threadid);			ret=pthread_cancel(threadid)
	#define ForceStopThread(ret,threadid);		pthread_exit(NULL);

	/* Mutex functions */
	#define CreateMutex(retID,mutex)		  	pthread_mutex_init(&retID, NULL)
	#define MutexWait(MutexID) 				MutexWaitFunc(&MutexID)
	OSRetValue MutexWaitFunc(MUTEX_ID *MutexID);
	#define MutexRelease(MutexID) 			pthread_mutex_unlock(&MutexID)

	/* Mail function */
	#define CreateMailQueue(ret ,retID, queue, param)	pqueue_init(&retID); ret = 1;
	#define MailAlloc(RetData,MailID,time)		RetData = (TransProtFrame *)MemAlloc(sizeof(TransProtFrame))
	#define MailFree(MailID, data)				MemFree(data)
	#define MailPut(MailID, data)				pqueue_push(&MailID, data);
	#define MailGet(RetMail,MailID)				RetMail = MailGetFunc(&MailID)

	OSGlobalRet MailGetFunc(MAIL_QUEUE_ID *MailID);

  /**
    *@}
    */  
	#else
	
	#error "An OS must be selected if the OS_ACTIVE parameter is enabled"
	#endif

#endif

/**
	*@}
	*/
	 
#ifdef __cplusplus
}
#endif
#endif /* __OSSUPPORT_H */
