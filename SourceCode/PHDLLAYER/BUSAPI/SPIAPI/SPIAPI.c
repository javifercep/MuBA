/**
	******************************************************************************
	* @file    SPIAPI.c
	* @author  Javier Fernandez Cepeda
	* @brief   This file contains functions descriptions which help users develop
	* 		   	 with SPI.
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
	*	@addtogroup SPI_API
	*	@{
	*		@brief SPI_API.
	*		@details 
*/

/* Includes ------------------------------------------------------------------*/
#include "SPIAPI.h"
#if SPI_API > 0
#include "../BUSAPI.h"

#include "Driver_SPI.h"                 // ::CMSIS Driver:SPI


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

#ifndef GNU_COMP
/* SPI Driver */
extern ARM_DRIVER_SPI B2B_SPI_DRIVER;
#endif

/* Private function prototypes -----------------------------------------------*/

#if SPI_MASTER > 0
static void SPI_SYNC_CallBack(void);
	#if SPI_POLLING_MODE == 0
		static void SPI_IRQ_CallBack(void);
	#endif
#endif

static void SPIEventCallBack(uint32_t event);

/* Private functions ---------------------------------------------------------*/

/**
* @brief   This function initializes SPI configuration:
* 			- Master or Slave
* 			- Bidirectional
* 			- Baud rate: 1 Mbps
* 			- Data size: 8b MSB
* 			- Enables DMA Rx & Tx
* @param  bufferSize: size of transmit&receive buffer
* @retval SPI_OK if configuration is successful,
* 		  SPI_FAIl otherwise.
*/
int32_t SPIInit(void)
{
	uint32_t debugRet;
	int32_t Ret = SPI_OK;
	ARM_DRIVER_SPI* SPIdrv = &B2B_SPI_DRIVER;
		
	#ifdef DEBUG
	  ARM_DRIVER_VERSION version;
		ARM_SPI_CAPABILITIES drv_capabilities;
	
		version = SPIdrv->GetVersion();
		if (version.api < 0x200) /* requires at minimum API version 2.00 or higher */
		{ /* error handling */
			return;
		}
		
		drv_capabilities = SPIdrv->GetCapabilities();
		if (drv_capabilities.event_mode_fault == 0)
		{ /* error handling */
			return;
		}
	#endif
		
	/* Initialize the SPI driver */
	debugRet = SPIdrv->Initialize(SPIEventCallBack);
	if(debugRet != ARM_DRIVER_OK)
	{
		Ret = SPI_KO;
		/* Add fail analysis */
	}
	/* Power up the SPI peripheral */
	SPIdrv->PowerControl(ARM_POWER_FULL);
	
	/* Configure the SPI to Master */
	#if SPI_MASTER > 0
	SPIdrv->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL0_CPHA0 | ARM_SPI_MSB_LSB | 
									ARM_SPI_SS_MASTER_SW | ARM_SPI_DATA_BITS(SPI_BITS), SPI_INIT_BAUDRATE);
	/* SS line = INACTIVE = HIGH */
	SPIdrv->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
	#else
	SPIdrv->Control(ARM_SPI_MODE_SLAVE | ARM_SPI_CPOL0_CPHA0 | ARM_SPI_MSB_LSB | 
									ARM_SPI_SS_SLAVE_SW | ARM_SPI_DATA_BITS(SPI_BITS), SPI_INIT_BAUDRATE);
	/* SS line = INACTIVE = HIGH */
	SPIdrv->Control(ARM_SPI_CONTROL_SS, ARM_SPI_SS_INACTIVE);
	#endif
	
	return Ret;
}

/**
* @brief   This function restores default SPI configuration
* @param  None
* @retval SPI_OK if configuration is successful,
*/
int32_t SPIDeInit(void)
{
	uint32_t debugRet;
	int32_t Ret = SPI_OK;
	/*Disabling SPI*/
	ARM_DRIVER_SPI* SPIdrv = &B2B_SPI_DRIVER;
	
	debugRet = SPIdrv->Uninitialize();
	if(debugRet != ARM_DRIVER_OK)
	{
		Ret = SPI_KO;
		/* Add analysis code */
	}
	return Ret;
}


/**
* @brief  This function configures SPI Speed
* @param  baud: SPI Speed rate
* @retval SPI_OK or SPI_FAIL
*/
int32_t SPISetSpeed(uint32_t baud)
{
	uint32_t debugRet;
	int32_t Ret = SPI_OK;
	/*Disabling SPI*/
	ARM_DRIVER_SPI* SPIdrv = &B2B_SPI_DRIVER;
	
	debugRet = SPIdrv->Control(ARM_SPI_SET_BUS_SPEED, baud);
	if(debugRet != ARM_DRIVER_OK)
	{
		Ret = SPI_KO;
		/* Add analysis code */
	}
	return Ret;

}


/**
* @brief  This function starts the SPI transfer
* @param  *pBuff: Buffer with data to send
* 		   size:  transmit buffer size
* @retval  SPI_TX_BUFFER_OVERFLOW if transmit can't be initiated
* 		   FUNC_OK otherwise.
*/
uint32_t SPIWrite(uint8_t *pBuf, uint32_t size)
{
	uint8_t ErrorCode;
	
	return ErrorCode;
}


/**
  * @brief  This function gets the frame in the first buffer position except the last 2 bytes of the frame.
  * @param  pBuf: pointer to buffer to be write
  * @retval Size of frame
  */
uint32_t SPIRead(uint8_t *pBuf, uint32_t Size)
{
	uint32_t readData;
	return (uint16_t)readData;
}


uint32_t SPIDataAvailable(void)
{
	return 0;
}
uint32_t SPISizeDataAvailable(void)
{
	return 0;
}
int32_t SPIConfiguration(uint16_t param, void *arg)
{
  int32_t RetValue = 0;
  
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
    case SPI_DEFAULT_CONFIG:
      RetValue = 0;
      break;
    default:
      RetValue = -1;
      break;
  }
  
	return RetValue;
}
/*********************************************************************************************/
/*****		STATIC FUNCTIONS		**********************************************************/
/*********************************************************************************************/


#if SPI_MASTER > 0
/**
  * @brief  This function handle SPI SYNC interrupt callback. When slave is redy to transfer more data
  * 		it set to LOW its SYNC PIN. Then, the master enables the SPI_TXE_Interrupt or the DMA_Transfer
  * @param  None
  * @retval None
  */
static void SPI_SYNC_CallBack()
{

}
#if SPI_POLLING_MODE == 0

/**
  * @brief  This function handle SPI IRQ interrupt callback.
  * @param  None
  * @retval None
  */
static void SPI_IRQ_CallBack()
{

}
#endif /*SPI_POLLING_MODE*/
#endif /*SPI_MASTER*/


static void SPIEventCallBack(uint32_t event)
{
	switch (event)
	{
		case ARM_SPI_EVENT_TRANSFER_COMPLETE:
			/* Success: Wakeup Thread */
			//osSignalSet(tid_mySPI_Thread, 0x01);
		break;
		case ARM_SPI_EVENT_DATA_LOST:
			/* Occurs in slave mode when data is requested/sent by master
			but send/receive/transfer operation has not been started
			and indicates that data is lost. */
			__breakpoint(0); /* Error: Call debugger or replace with custom error handling */
		break;
		case ARM_SPI_EVENT_MODE_FAULT:
			/* Occurs in master mode when Slave Select is deactivated and
			indicates Master Mode Fault. */
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
