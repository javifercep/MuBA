/**
  ******************************************************************************
  * @file    USBSerial.c
  * @author  Javier Fernandez Cepeda
  * @brief   USB API.
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
	*	@addtogroup USB_API
	*	@{
	*		@brief USB_API.
	*		@details 
*/

/* Includes ------------------------------------------------------------------*/
#include "USBAPI.h"
#if USB_API > 0
#include "../../../TOOLS/BufferFunctions.h"
#include "../../../TOOLS/MemoryManagement.h"
#include "../BUSAPI.h"

#include "rl_usb.h"                     // Keil.MDK-Pro::USB:CORE

#ifndef HSDEVICE
#define HSDEVICE 	1
#endif
#ifndef EPIN
#define EPIN			0x81
#endif
#ifndef EPOUT
#define EPOUT			0x01
#endif

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* This buffer is shared by this API and the USB driver */
volatile FramesBuffer USBRxBuffer;


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/


/********************************************************************************/
/*								Basic functions									*/
/********************************************************************************/

 /**
   * @brief  This functions initializes USB
   * @param  Size Size of the USB Buffer
   * @retval USB_OK if USB can be initialized, ERROR otherwise
   */
int32_t USBInit(void)
{
	int32_t Ret = USB_OK;
	usbStatus ret;
	
	ret = USBD_Initialize(MBA_USB_DRIVER);
	if(ret != usbOK)
	{
		/*TODO: Add some signal */
	}
	ret = USBD_Connect(MBA_USB_DRIVER);
	if(ret != usbOK)
	{
		/*TODO: Add some signal */
	}
	if(FBufferAlloc(&USBRxBuffer, 10)!= 10)
	{
		/*TODO: Add some signal */
	}
	
	return Ret;
 }

/**
  * @brief  This functions deinitializes USB
  * @param  None
  * @retval USB_OK if USB can be initialized, ERROR otherwise
  */
int32_t USBDeInit(void)
{
	USBD_Disconnect(MBA_USB_DRIVER);
	USBD_Uninitialize(MBA_USB_DRIVER);

	return USB_OK;
}
 /**
   * @brief  Check if there is a frame available
   * @param  None.
   * @retval Number of data available.
   */
uint32_t USBDataAvailable(void)
 {
	 return FBufferNumData(USBRxBuffer);
 }

/**
  * @brief  Returns the size of the frame in the first position
  * @param  None.
  * @retval Number of data available.
  */
uint32_t USBSizeDataAvailable(void)
{
	return FBufferFirstDataSize(USBRxBuffer);
}

 /**
   * @brief  Reads the data in USB buffer
   * @param  Data: pointer to the destination buffer.
   * @param	 Size: Size of data to read
   * @retval Read data.
   */
uint32_t USBRead(uint8_t *pData, uint32_t Size)
{
	  uint8_t *pTemp = pData;
	  return FBufferRead(&USBRxBuffer, pTemp, Size);
}


 /**
   * @brief  Write data through USB
   * @param  Data: pointer to the destination buffer.
   * @param	 Size: Size of data to read
   * @retval FUNC_OK.
   */
uint32_t USBWrite(uint8_t *pData, uint32_t Size)
 {
	 uint8_t *pTemp = pData;
	 USBD_EndpointWrite(HSDEVICE, EPIN, pTemp, Size);
	 return FUNC_OK;
 }

  /**
   * @brief  Write data through USB
   * @param  Data: pointer to the destination buffer.
   * @param	 Size: Size of data to read
   * @retval FUNC_OK.
   */
int32_t USBConfiguration(uint16_t param, void *arg)
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
    case USB_DEFAULT_CONFIG:
      RetValue = 0;
      break;
    default:
      RetValue = -1;
      break;
  }
  return RetValue;
} 
/********************************************************************************/
/*						Debug & Error control functions 						*/
/********************************************************************************/
 /**
    * @brief  Send an error message
    * @param  s: string with message to send.
    * @retval none.
    */
 void USBSendError(char *s)
 {
	 //usb_sbausb_senBytes((uint8_t *)s, strlen(s), SBAUSB_ERR_EP);
 }

 /**
    * @brief  Send a debug message
    * @param  s: string with message to send.
    * @retval none.
    */
 void USBSendDebug(const char *s)
 {
	 //usb_sbausb_senBytes((uint8_t *)s, strlen(s), SBAUSB_ERR_EP);
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
