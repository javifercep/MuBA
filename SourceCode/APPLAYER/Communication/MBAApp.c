/**
  ******************************************************************************
  * @file    MBAApp.c
  * @author  Javier Fernández Cepeda
  * @brief   This file contains multi bus analyzer application
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  *	@addtogroup MBA
  *	@{
  *		@brief	 MBA module is the responsible of processing data received from differ
  *			 ent interfaces and translate to a supported format for other inter
  *			 face.
  *		@details
  *
  *	@addtogroup MBA_Application
  *	@{
  *		@brief   A global MBA task is created to manage all MBA functions.
  *		@details All the tasks have access to the MBA instance to process the
  *			 network frames. The MBA includes a set of protocols to get the maximum
  *			 flexibility:
  *		- @ref Transfer_Protocol.
  *		- @ref Configuration_Protocol.
  *		- @ref State_Machine_Protocol.
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"		/*!< System paramters */
#include "../OSSupport.h"		/*!< Operating sytem functions */
#include "MBAApp.h"			/*!< MBA application parameters */
#include "BusApp.h"
#include "../../MBALibrary/MBALib.h"	/*!< Access to MBA instance */

#include "stdio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MBAPROCESS_SIZE_STACK		0	/*!< Thread stack size */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
THREAD_ID ThreadIDMBAProcess; 																/*!< Thread ID */
MAIL_QUEUE_ID QueueIDMBAQueue;                                /*!< Mail queue id */
DEFINE_MAIL_QUEUE (MBAQueue, MBA_QUEUE_SIZE, TransProtFrame); /*!<  Mail queue object */

/* Call to BusApp variables to give thread management to the MBA thread*/
extern BusInstance BusInstances[];
extern MAIL_QUEUE_ID QueueIDBusQueue[];
extern THREAD_ID ThreadIDBUSReadProcess[BUS_INSTANCES];  /*!< Thread IDs */

/* Private function prototypes -----------------------------------------------*/

OS_THREAD_TYPE MBAProcess (OS_THREAD_ARG argument);          /*!<  Thread function  */
DEFINE_THREAD (MBAProcess, osPriorityNormal, MBALIB_INSTANCES, MBAPROCESS_SIZE_STACK);
void MBABusInterfaceUpdate(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes MBA App thread
  * @retval @ref InstanceRet
  */
int32_t InitMBAProcess(void) 
{
  int32_t ret = 0;
  int32_t FuncRet;
  
  /* Initializes the MBA module */
  MBAInit();
	
  CreateMailQueue(FuncRet, QueueIDMBAQueue,MAIL_QUEUE_REF(MBAQueue), NULL);	// create mail queue
  if(!FuncRet)
  {
    ret = BUFFER_ERROR; // Mail Queue object not created, handle failure
  }
  CreateThread (FuncRet, ThreadIDMBAProcess,THREAD_REF(MBAProcess), NULL);
  if(!FuncRet)
  {
    ret = TASK_ERROR;
  }
  
  /* Once the state machine is updated, launch related threads */
  MBABusInterfaceUpdate();
  return ret;
}

/**
  * @brief  		BUS app Thread
  * @param[in]  argument Not used.
  */
OS_THREAD_TYPE MBAProcess (OS_THREAD_ARG argument) {
	
  OSGlobalRet    RetMBAMail;
  int32_t	 TPInterfaceID = 0, OPInterfaceID = 0;
  TransProtFrame *RxFrame = NULL;
  TransProtFrame *TxFrame = NULL;
  TransProtFrame SMFrame, ProcessedFrame;

  TransferProtocolFrameInit(&ProcessedFrame);
  TransferProtocolFrameInit(&SMFrame);
	
  while (1) 
  {

    /******************** Process Input data ***************************/

    /* if there is data in the mailbox, read it */
    MailGet(RetMBAMail, QueueIDMBAQueue);

    if (RetMBAMail.RetValue == OS_OK)
    {
      RxFrame = RetMBAMail.Data;
      /* Process Received Data */
      TPInterfaceID = TransferProtocolProcess(&ProcessedFrame, RxFrame);
      if(TPInterfaceID < 0)
      {
	/* Handle error */
      }
      if(RxFrame)
      {
        MailFree(QueueIDMBAQueue, RxFrame); // free memory allocated for mail
      }
    }
    
/******************** End Process Input data ***************************/

/******************** Process State machine  ***************************/
  
    /* Execute state machine operations */
   OPInterfaceID = OperationProtocolUpdate(&SMFrame);

   /* Once the Operation State machine is processed, check all the bus instance
    * states and update them.
    */
   MBABusInterfaceUpdate();
   TransferProtocolUpdateInterfaceState(OPInterfaceID);
  
   /* If a frame is generated due a state trasition, put it into the Queue */
    if(GetFrameDataSize(SMFrame) > 0)
    {
      if((OPInterfaceID >= 0) && (OPInterfaceID < AVAILABLE_INTERFACES))
      {
        MailAlloc(TxFrame, QueueIDBusQueue[OPInterfaceID], 0); // Allocate memory
        if(TxFrame)
        {
          TransferProtocolCopy(TxFrame, &SMFrame);
          MailPut(QueueIDBusQueue[OPInterfaceID],TxFrame);     // Send Mail

          /* Initializa ProcessedFrame to avoid multiple access*/
          TransferProtocolFrameInit(&SMFrame);
        }
      }
    }
/***************** End Process State machine  ************************/
    
/******************** Process Output data ***************************/

    if(GetFrameDataSize(ProcessedFrame) > 0)
    {
      if((TPInterfaceID >= 0) && (TPInterfaceID < AVAILABLE_INTERFACES))
      {
        MailAlloc(TxFrame, QueueIDBusQueue[TPInterfaceID], 0); // Allocate memory
        if(TxFrame)
        {
          TransferProtocolCopy(TxFrame, &ProcessedFrame);
          MailPut(QueueIDBusQueue[TPInterfaceID],TxFrame);  	// Send Mail

          /* Initializa ProcessedFrame to avoid multiple access*/
          TransferProtocolFrameInit(&ProcessedFrame);
        }
      }
    }
/******************* End Process Output data *************************/
  }
}

/*********************************************************************************************/
/*****	STATIC FUNCTIONS 	    **********************************************************/
/*********************************************************************************************/
void MBABusInterfaceUpdate(void)
{
  int32_t FuncRet;
  uint8_t InterfaceCounter;

  for(InterfaceCounter = 0; InterfaceCounter < AVAILABLE_INTERFACES; InterfaceCounter++)
  {
    switch(GetBusInstanceStateTransition(InterfaceCounter))
    {
      case BUS_INIT_2_INACTIVE:
        LaunchBUSInstance(InterfaceCounter);
        if(!FuncRet)
        {
          /* Handle error */
        }
        break;
            case BUS_INACTIVE_2_ACTIVE:
        break;
      case BUS_ACTIVE_2_STOP:
        StopThread(FuncRet, ThreadIDBUSReadProcess[InterfaceCounter]);
        if(FuncRet != 0)
        {
          /* Handle Error */
        }
        BusInstances[InterfaceCounter].DeInit();
      break;
     case BUS_NO_TRANSITION:
      break;
    }
  }
}


