/**
	******************************************************************************
	* @file    USARTAPI.c
	* @author  Javier Fernandez Cepeda
	* @brief   This file contains functions descriptions which help users develop
	* 		   with USART.
	*******************************************************************************
	* Copyright (c) 2015, Javier Fernandez. All rights reserved.
	*******************************************************************************
	*
	* @addtogroup Bus
	*	@{
	*
	*	@addtogroup Bus_Interface
	*	@{
	*	
	*	@addtogroup USART_API
	*	@{
	*		@brief USART_API.
	*		@details 
*/

/* Includes ------------------------------------------------------------------*/
#include "USARTAPI.h"
#if USART_API > 0
#include "../../../TOOLS/BufferFunctions.h"
#include "../../../TOOLS/MemoryManagement.h"
#include "../BUSAPI.h"

#include "Driver_USART.h"                 // ::CMSIS Driver:USART


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USART_BUS_DRIVER					Driver_USART4

#define RX_BUFFER_SIZE            10
#if ENABLE_FLOW_CONTROL > 0
#define FLOW_CONTROL_SIZE         10
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Local buffer for flow control */
#if ENABLE_FLOW_CONTROL > 0
static volatile FramesBuffer USARTTxBuffer;
static uint8_t NumberOfTransfersInQueue;
#endif

static volatile FramesBuffer USARTRxBuffer;
static uint8_t *CurrentTxBuffer;
static uint16_t ReadByte;
static uint16_t NumberOfReadBytes;

static uint8_t EndFieldValue;

/* TODO: Remove it */
static uint8_t ReceiveBuffer[40]; // Size must be variable and configurable

#ifndef GNU_COMP
/* SPI Driver */
extern ARM_DRIVER_USART USART_BUS_DRIVER;
#endif

/* Private function prototypes -----------------------------------------------*/

static void USARTEventCallBack(uint32_t event);

/* Private functions ---------------------------------------------------------*/

/**
* @brief  This function initializes USART configuration:
* @retval USART_OK if configuration is successful,
* 		  USART_FAIl otherwise.
*/
int32_t USARTInit(void)
{
	uint32_t debugRet;
	int32_t Ret = USART_OK;
	ARM_DRIVER_USART* USARTdrv = &USART_BUS_DRIVER;
		
	#ifdef DEBUG
		ARM_DRIVER_VERSION version;
		ARM_USART_CAPABILITIES drv_capabilities;
	
		version = USARTdrv->GetVersion();
		if (version.api < 0x200) /* requires at minimum API version 2.00 or higher */
		{ /* error handling */
			return;
		}
		
		drv_capabilities = USARTdrv->GetCapabilities();
		if (drv_capabilities.event_mode_fault == 0)
		{ /* error handling */
			return;
		}
	#endif
		
	/* Initialize the USART driver */
	debugRet = USARTdrv->Initialize(USARTEventCallBack);
	if(debugRet != ARM_DRIVER_OK)
	{
		Ret = USART_KO;
		/* Add fail analysis */
	}
	/* Power up the USART peripheral */
	USARTdrv->PowerControl(ARM_POWER_FULL);
	
	/* Initializes USART paramteres */
  USARTdrv->Control(ARM_USART_MODE_ASYNCHRONOUS |
                    ARM_USART_DATA_BITS_8 |
                    ARM_USART_PARITY_NONE |
                    ARM_USART_STOP_BITS_1 |
                    ARM_USART_FLOW_CONTROL_NONE, USART_INIT_BAUDRATE);
  
    /* Create flow control buffers */
  if(FBufferAlloc(&USARTRxBuffer, RX_BUFFER_SIZE)!= RX_BUFFER_SIZE)
	{
		/*TODO: Add some signal */
	}
  
  #if ENABLE_FLOW_CONTROL > 0
  
  if(FBufferAlloc(&USARTTxBuffer, FLOW_CONTROL_SIZE)!= FLOW_CONTROL_SIZE)
	{
		/*TODO: Add some signal */
	}
  
  /* Initialize the counter of transfers waiting for transfer */
  NumberOfTransfersInQueue = 0;
  #endif
  
  /* Enable Receiver and Transmitter lines */
  USARTdrv->Control (ARM_USART_CONTROL_TX, 1);
  USARTdrv->Control (ARM_USART_CONTROL_RX, 1);
  
  /*TODO: Remove it after test */
  EndFieldValue = '\r';
  NumberOfReadBytes = 0;
  USARTdrv->Receive(&ReadByte,1);
  
	return Ret;
}

/**
* @brief  This function restores default USART configuration
* @retval USART_OK if configuration is successful,
*/
int32_t USARTDeInit(void)
{
	uint32_t debugRet;
	int32_t Ret = USART_OK;
	/*Disabling SPI*/
	ARM_DRIVER_USART* USARTdrv = &USART_BUS_DRIVER;
	
	debugRet = USARTdrv->Uninitialize();
	if(debugRet != ARM_DRIVER_OK)
	{
		Ret = USART_KO;
		/* Add analysis code */
	}
  
  FBufferFree(&USARTRxBuffer);
  #if ENABLE_FLOW_CONTROL > 0
  FBufferFree(&USARTTxBuffer);
  NumberOfTransfersInQueue = 0;
  #endif
	
  return Ret;
}

/**
* @brief  This function starts the USART transfer
* @param  *pBuff: Buffer with data to send
* 		   size:  transmit buffer size
* @retval  
*/
uint32_t USARTWrite(uint8_t *pBuf, uint32_t size)
{
  ARM_DRIVER_USART* USARTdrv = &USART_BUS_DRIVER;
  uint32_t debugRet = 0;
  uint8_t *SendBuffer  = pBuf;
 
  #if ENABLE_FLOW_CONTROL > 0  
  /* If there is still data to be sent, save new frame into flow
   * control buffer */
  if(NumberOfTransfersInQueue > 0)
  {
    if(IsFBufferFull(USARTTxBuffer) == FBUF_NOTFULL)
    {
      FBufferWrite(&USARTTxBuffer, SendBuffer, size);
      NumberOfTransfersInQueue++;
    }
    else
    {
      debugRet = -1;
    }
  }
  else
  {
  #endif
    /* Copy received data into output buffer. This ensures to the
     * upper layers that they could remove the buffer */
    CurrentTxBuffer = (uint8_t *)MemAlloc(size);
    memcpy(CurrentTxBuffer, SendBuffer, size);
    
    /* Send data */
    debugRet = USARTdrv->Send(CurrentTxBuffer, size);
    if (debugRet != ARM_DRIVER_OK)
    {
      /* handle error */
    }
    
#if ENABLE_FLOW_CONTROL > 0   
    NumberOfTransfersInQueue++;
  }
#endif

	return debugRet;
}


/**
  * @brief  This function gets the frame in the first buffer position
  * @param  pBuf: pointer to buffer to be write
  * @retval 
  */
uint32_t USARTRead(uint8_t *pBuf, uint32_t Size)
{
    uint8_t *pTemp = pBuf;
	  return FBufferRead(&USARTRxBuffer, pTemp, Size);
}


uint32_t USARTDataAvailable(void)
{
	return FBufferNumData(USARTRxBuffer);
}
uint32_t USARTSizeDataAvailable(void)
{
	return FBufferFirstDataSize(USARTRxBuffer);
}
int32_t USARTConfiguration(uint16_t param, void *arg)
{
  int32_t RetValue;
  
  switch(param)
  {
    case  BUS_FRAME_DETECTION:
      break;
    case  BUS_TIMEOUT:
      break;
    case  BUS_TIMEOUT_DETECTION:
      break;
    case  BUS_FIELD_SIZE_DETECTION:
      break;
    case  BUS_END_FIELD_DETECTION:
      break;
    case USART_DEFAULT_CONFIG:
      RetValue = 0;
      break;
    case  USART_MODE:
      break;
    case  USART_DATA_BITS:
      break;
    case  USART_PARITY:
      break;
    case  USART_STOP_BITS:
      break;
    case  USART_FLOW_CONTROL:
      break;
    case USART_BAUD_RATE:
      break;
    default:
      RetValue = -1;
      break;
  }
  
	return RetValue;
}
/***************************************************************************************/
/*****		STATIC FUNCTIONS		**********************************************************/
/***************************************************************************************/

static void USARTEventCallBack(uint32_t event)
{
  #if ENABLE_FLOW_CONTROL > 0 
  uint32_t TempSize;
  uint32_t debugRet;
  #endif
  ARM_DRIVER_USART* USARTdrv = &USART_BUS_DRIVER;
  
	switch (event)
	{
		case ARM_USART_EVENT_RECEIVE_COMPLETE:
      if(ReadByte != EndFieldValue)
      { 
        ReceiveBuffer[NumberOfReadBytes++] = (uint16_t)ReadByte;
      }
      else
      {
        FBufferWrite(&USARTRxBuffer, ReceiveBuffer, NumberOfReadBytes);
        NumberOfReadBytes = 0;
      }
      USARTdrv->Receive(&ReadByte,1);
      break;
    case ARM_USART_EVENT_SEND_COMPLETE:
      #if ENABLE_FLOW_CONTROL > 0  
      /* Check if there is still stored frames to be sent */
      if(FBufferNumData(USARTTxBuffer) > 0)
      {
        TempSize = FBufferFirstDataSize(USARTTxBuffer);
        CurrentTxBuffer = MemRealloc(CurrentTxBuffer, TempSize);
        FBufferRead(&USARTTxBuffer,CurrentTxBuffer, TempSize);
        /* Send data */
        debugRet = USARTdrv->Send(CurrentTxBuffer, TempSize);
        if (debugRet != ARM_DRIVER_OK)
        {
          /* handle error */
        }
      }
      else
      {
      #endif
      
      MemFree(CurrentTxBuffer);
        
      #if ENABLE_FLOW_CONTROL > 0  
      }
      NumberOfTransfersInQueue--;
      #endif
      break;
    
    case ARM_USART_EVENT_TRANSFER_COMPLETE:
    case ARM_USART_EVENT_TX_COMPLETE:
    
		break;
		 case ARM_USART_EVENT_RX_TIMEOUT:
			__breakpoint(0); /* Error: Call debugger or replace with custom error handling */
		break;
		case ARM_USART_EVENT_RX_OVERFLOW:
    case ARM_USART_EVENT_TX_UNDERFLOW:
			__breakpoint(0); /* Error: Call debugger or replace with custom error handling */
		break;
	}
}

#endif

/**
	*@}
	*/
/**
	*@}
	*/
/**
	*@}
	*/
