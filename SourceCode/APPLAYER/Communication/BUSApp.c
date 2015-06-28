/**
  ******************************************************************************
  * @file    BUSApp.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains BUS (CAN, USB, LIN, etc) application
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  *	@addtogroup Bus
  *	@{
  *		@brief	 Bus module is the responsible of manage all the available physical
  *						 interfaces in each MBA device.
  *		@details
  *
  *	@addtogroup Bus_Application
  *	@{
  *		@brief   A task for each available bus interface is created and managed.
  *		@details All the tasks have access to the MBA instance to process the
  *		network frames. Two modes will be available to include this functionality
  *		in multiple architectures:
  *			-	Through a RTOS / OS. Each bus interface has its own thread. OS tools like
  *				mutex and mailbox are used for synchronization and shared resources.
  *			- Loop process. Where a OS cannot be implemented or in some special applic
  *				ations, these functions are included in a super loop structure. BufferFu
  *				nctions API and other tools will be used for task communication and sync
  *				hronization.
  *
  * 	All the Bus tasks follow a common structure to increase the modularity and
  * 	scalability of the project. Refercto @ref BUSAPI.c file for further informat
  *		ion.
  */

/* Includes ------------------------------------------------------------------*/
#include "BUSApp.h"			/*!< Bus application parameters */
#include "../../MBALIBRARY/MBALib.h"		/*!< Access to MBA instance */
#include "../../PHDLLAYER/BUSAPI/BUSAPI.h" 	/*!< Main API of this file */
#include "../../TOOLS/MemoryManagement.h" 	/*!< Definition of memory functions */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
	
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

THREAD_ID ThreadIDBUSReadProcess[BUS_INSTANCES];  /*!< Thread IDs */
THREAD_ID ThreadIDBUSWriteProcess[BUS_INSTANCES];  /*!< Thread IDs */

/**
 * @brief A mail queue for each bus thread is created. This mailbox are used to 
 * receive data from MBA process or other bus threads
 */
MAIL_QUEUE_ID QueueIDBusQueue[BUS_INSTANCES];
 

#if BUS_INSTANCES > 0
/**
 * @brief BusQueue_1 is the queue for the interface 0. See @ref InstanceID.
 */
DEFINE_MAIL_QUEUE (BusQueue_1, BUS_QUEUE_SIZE, TransProtFrame);  
#endif
#if BUS_INSTANCES > 1
/**
 * @brief BusQueue_2 is the queue for the interface 1. See @ref InstanceID.
 */
DEFINE_MAIL_QUEUE (BusQueue_2, BUS_QUEUE_SIZE, TransProtFrame);
#endif
#if BUS_INSTANCES > 2
/**
 * @brief BusQueue_2 is the queue for the interface 1. See @ref InstanceID.
 */
DEFINE_MAIL_QUEUE (BusQueue_3, BUS_QUEUE_SIZE, TransProtFrame);
#endif

/**
 * @brief Queues of MBA Instances. Usually only one Queue.
 */
extern MAIL_QUEUE_ID QueueIDMBAQueue;


/**
 * @brief A mutex is needed to get access to the MBA Queue. This Queue is shared
 *				by all available bus interfaces
 */
DEFINE_MUTEX(MBAMutex);	
MUTEX_ID MidMBAMutex;              /*!< Mutex ID */
														  

/**
 * @brief Thread argument. The BUS ID is used by each bus thread to point to the
 *				correct bus functions. Other arguments may be added in the future.
 */
int32_t InstanceID[BUS_INSTANCES] =
{
 BUS_ID_1,
 BUS_ID_2
#if BUS_INSTANCES > 2
 , BUS_ID_3
#endif
 };

/* Private function prototypes -----------------------------------------------*/
OS_THREAD_TYPE BUSReadProcess (OS_THREAD_ARG argument);	 /*!< Bus thread function */
OS_THREAD_TYPE BUSWriteProcess (OS_THREAD_ARG argument); /*!< Bus thread function */

/**
 * @brief Thread definition. There are as many instances as available bus interfaces
 */
DEFINE_THREAD(BUSReadProcess, osPriorityNormal, BUS_INSTANCES, BUS_STACKSIZE);
DEFINE_THREAD(BUSWriteProcess, osPriorityNormal, BUS_INSTANCES, BUS_STACKSIZE);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes BUS App process
  * @details Mail queues, threads and all elements needed for tasks initialization.
  * @retval @ref BusInstanceRet
  */
int32_t InitBUSProcess(void) 
{
  int32_t ret = INSTANCE_OK;
  int32_t FuncRet;

  /* Create Bus buffers */
#if BUS_INSTANCES > 0
  CreateMailQueue(FuncRet, QueueIDBusQueue[BUS_ID_1],MAIL_QUEUE_REF(BusQueue_1), NULL);
  if(!FuncRet)
  {
	  ret = BUFFER_ERROR; // Mail Queue object not created
  }
#endif
#if BUS_INSTANCES > 1
	
  CreateMailQueue(FuncRet, QueueIDBusQueue[BUS_ID_2] ,MAIL_QUEUE_REF(BusQueue_2), NULL);
  if(!FuncRet)
  {
	  ret = BUFFER_ERROR; // Mail Queue object not created
  }
#endif
#if BUS_INSTANCES > 2
  CreateMailQueue(FuncRet, QueueIDBusQueue[BUS_ID_3], MAIL_QUEUE_REF(BusQueue_3), NULL);
  if(!QueueIDBusQueue[BUS_ID_3])
  {
	ret = BUFFER_ERROR; // Mail Queue object not created
  }
#endif
	
  /* Create synchronization tools */
  CreateMutex(MidMBAMutex, MUTEX_REF(MBAMutex));
  if (!MidMBAMutex)
  {
      ret = SYNC_TOOL_ERROR; // Mutex object not created
  }

  return ret;
}

/**
  * @brief   Creates a new thread form an external module.
  * @param[in] 	Thread ID
  */
void LaunchBUSInstance(uint8_t BusInstanceID)
{
  uint32_t FuncRet;
  CreateThread (FuncRet, ThreadIDBUSReadProcess[BusInstanceID],THREAD_REF(BUSReadProcess), &(InstanceID[BusInstanceID]));
  if(!FuncRet)
  {
	  /* Handle Erro */
  }
}
/**
  * @brief   Bus task instance.
  * @details This task must be called for each available bus interface. It is the
  *	     responsible of the initialization and configuration of the physical bus
  *	     interface. Furthermore, data transfer are transmitted /
  *	     received to / from the MBA instance and the linked Bus.
  * @param[in] 	argument Bus identification
  */
OS_THREAD_TYPE BUSReadProcess (OS_THREAD_ARG argument)
{
  uint8_t *BusBuffer; 	/* Temporal buffer to save data from/to linked bus */
  uint32_t FrameSize, FuncRet;	/* Saves size of the received/transmitted frames */
  TransProtFrame *TxFrame = NULL;  /* Transfer protocol buffers to transfer data */
  OSRetValue	RetMutex;

  /* Get BUS Identification */
  int32_t BUSId = *((int32_t *)argument);

  /* Initialize BUS functions, buffer and variables */
  BusInstances[BUSId].Init();

  /* Configure Bus HW interface to start the communication */
  if(BusInstances[BUSId].Configuration(1,0) < 0)
  {
      BusInstances[BUSId].DeInit();
      ForceBusInterfaceStop(BUSId);
      TransferProtocolUpdateInterfaceState(BUSId);
      ForceStopThread(FuncRet, ThreadIDBUSReadProcess[BUSId]);
  }
  else
  {
    /* Once the Interface is enabled, launch the read process */
    CreateThread (FuncRet, ThreadIDBUSWriteProcess[BUSId],THREAD_REF(BUSWriteProcess),&(InstanceID[BUSId]));
    if(!FuncRet)
    {
  	/* handle Error */
    }
  }

  while (1)
  {
    /* Check data from Bus */
    if(BusInstances[BUSId].DataAvailable() > 0)
    {
      /* Alloc memory for temporal buffer */
      FrameSize = BusInstances[BUSId].SizeDataAvailable();
      BusBuffer = (uint8_t*) MemAlloc(FrameSize);

      if(BusBuffer != NULL)
      {
        /* Read data in from the bus */
        BusInstances[BUSId].Read(BusBuffer, FrameSize);

        /* Put data into mailbox */
        MailAlloc(TxFrame, QueueIDMBAQueue, 0);        // Allocate memory
        if(TxFrame)
        {
          /* Cast data from bus into transfer protocol frame */
          TransferProtocolCast(TxFrame, BusBuffer, FrameSize, BUSId,
          TransferProtocolGetInterfaceType(BUSId) | FROM_BUFFER);

          /* Check is the resource is available */
          RetMutex = MutexWait(MidMBAMutex);
          switch(RetMutex)
          {
            case OS_OK:
            /* Put data into MBA buffer */
            MailPut(QueueIDMBAQueue, TxFrame);
            MutexRelease(MidMBAMutex);
            break;
            case OS_TIMEOUT:
            break;
            case OS_ERROR:
            break;
            default:
            break;
          }
        }
      }

      if(BusBuffer != NULL)
      {
        /* Free allocated data */
        MemFree(BusBuffer);
        BusBuffer = NULL;
      }
    }
  }
}
/**
  * @brief  	Bus task instance.
  * @details	This task must be called for each available bus interface. It is the
  *		        responsible of the initialization and configuration of the physical bus
  *		        interface. Furthermore, data transfer are transmitted /
  *		        received to / from the MBA instance and the linked Bus.
  * @param[in] 	argument Bus identification
  */
OS_THREAD_TYPE BUSWriteProcess (OS_THREAD_ARG argument)
{
  uint8_t *BusBuffer; 	/* Temporal buffer to save data from/to linked bus */
  uint32_t FrameSize;	/* Saves size of the received/transmitted frames */

  TransProtFrame *RxFrame = NULL; /* Transfer protocol buffers to transfer data
				    to/from the MBA instante */
  OSGlobalRet  RetMail;

  /* Get BUS Identification */
  int32_t BUSId = *((int32_t *)argument);

  /* If this thread is enabled, it means that this interface is initializated
   * for continuous communication, therefore this interface is set ACTIVE
   */
  SetBusInstanceState(BUSId, BUS_ACTIVE);
  TransferProtocolUpdateInterfaceState(BUSId);

  while (1)
  {

    /* if there is data in the mailbox, read it */
    MailGet(RetMail, QueueIDBusQueue[BUSId]);
    if (RetMail.RetValue == OS_OK)
    {
      RxFrame = RetMail.Data;
      FrameSize = GetFrameSizeP(RxFrame);

      /* Allocate memory for busbuffer */
      BusBuffer = (uint8_t*) MemAlloc(FrameSize);

      if(BusBuffer != NULL)
      {
        /* Cast from transfer protocol to buffer format */
        FrameSize = TransferProtocolCast(RxFrame, BusBuffer, FrameSize, BUSId,
        TransferProtocolGetInterfaceType(BUSId) | TO_BUFFER);

        /* Add new frame into Bus buffer to send it */
        BusInstances[BUSId].Write(BusBuffer, FrameSize);

        /* Free allocated data */
        MailFree(QueueIDBusQueue[BUSId], RxFrame);

        if(BusBuffer != NULL)
        {
          /* Free allocated data */
          MemFree(BusBuffer);
          BusBuffer = NULL;
        }
      }
    }
  }
}
/**
  *@}
  */
/**
  *@}
  */
