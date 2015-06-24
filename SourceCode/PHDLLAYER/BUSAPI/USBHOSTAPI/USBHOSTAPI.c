/**
  ******************************************************************************
  * @file    USBHOSTAPI.c
  * @author  Javier Fernandez Cepeda
  * @brief   USB Host API.
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup Bus
  * @{
  *
  *	@addtogroup Bus_Interface
  *	@{
  *
  *		@addtogroup USB_API
  *		@{
  *			@brief USB_API.
  *			@details
*/

/* Includes ------------------------------------------------------------------*/
#include "../USBHOSTAPI/USBHOSTAPI.h"
#include "SysConfig.h"
#include "../BUSAPI.h"

#if WINDOWS > 0
#include <stdio.h>
#include <libusb-1.0/libusb.h>
#endif

#if ARMCC > 0
#include "rl_usb.h"                     // Keil.MDK-Pro::USB:CORE
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifndef HSDEVICE
#define HSDEVICE 	1
#endif
#ifndef EPIN
#define EPIN		0x81
#endif
#ifndef EPOUT
#define EPOUT		0x01
#endif

#define VID		0xDEAD
#define PID		0xBEEF
#define CONFIG		1
#define DATA_INTF 	0

#define MAX_PACKET_SIZE	512

/* Specific configuration commands */
#define USB_DEVICE_CONNECTION	1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
libusb_device_handle *devhandler = NULL; /* the device handle */
static uint8_t RxBuffer[MAX_PACKET_SIZE];
static uint32_t ReadSize;

/* Private function prototypes -----------------------------------------------*/
static int32_t USBHostConnect(void);

/* Private functions ---------------------------------------------------------*/


/********************************************************************************/
/*	Basic functions	 							*/
/********************************************************************************/

 /**
   * @brief  This functions initializes USB
   * @param  Size Size of the USB Buffer
   * @retval USB_OK if USB can be initialized, ERROR otherwise
   */
int32_t USBHostInit(void)
{
  int ret;

  ret = libusb_init(NULL); /* initialize the library */
  if(ret < 0)
  {

  }
  return ret;
 }

/**
  * @brief  This functions deinitializes USB
  * @param  None
  * @retval USB_OK if USB can be initialized, ERROR otherwise
  */
int32_t USBHostDeInit(void)
{
  int ret;
  if (devhandler)
  {
    ret = libusb_release_interface(devhandler, DATA_INTF);
    if(ret < 0)
    {

    }

    libusb_close(devhandler);
  }

  return USB_OK;
}
 /**
   * @brief  Check if there is a frame available
   * @param  None.
   * @retval Number of data available.
   */
uint32_t USBHostDataAvailable(void)
{
   int ret, CurrentLength;
   ret = libusb_bulk_transfer(devhandler, EPIN, RxBuffer, MAX_PACKET_SIZE, &CurrentLength, 0);
   if(ret == 0)
   {
       ReadSize = CurrentLength;
   }
   else
   {
       ReadSize = 0;
   }

   return ReadSize;
 }

/**
  * @brief  Returns the size of the frame in the first position
  * @param  None.
  * @retval Number of data available.
  */
uint32_t USBHostSizeDataAvailable(void)
{
  return ReadSize;
}

 /**
   * @brief  Reads the data in USB buffer
   * @param  Data: pointer to the destination buffer.
   * @param  Size: Size of data to read
   * @retval Read data.
   */
uint32_t USBHostRead(uint8_t *pData, uint32_t Size)
{
  uint8_t *pTemp = pData;
  memcpy(pTemp,RxBuffer, Size);

  return ReadSize;
}


 /**
   * @brief  Write data through USB
   * @param  Data: pointer to the destination buffer.
   * @param	 Size: Size of data to read
   * @retval FUNC_OK.
   */
uint32_t USBHostWrite(uint8_t *pData, uint32_t Size)
 {
     uint8_t *pTemp = pData;
     int ret, CurrentLength;

     ret = libusb_bulk_transfer(devhandler, EPOUT, pTemp, Size, &CurrentLength, 5000);
     if(ret != 0)
     {

     }

     return 0;
 }

  /**
   * @brief  Write data through USB
   * @param  Data: pointer to the destination buffer.
   * @param	 Size: Size of data to read
   * @retval FUNC_OK.
   */
int32_t USBHostConfiguration(uint16_t param, void *arg)
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
    case USB_DEVICE_CONNECTION:
      RetValue = USBHostConnect();
      break;
    default:
      RetValue = -1;
      break;
  }
  return RetValue;
} 

 /************* Static function description *********************/
 /**
    * @brief  Send a debug message
    * @param  s: string with message to send.
    * @retval none.
    */
 static int32_t USBHostConnect(void)
 {
   libusb_device **devs;
   struct libusb_device_descriptor desc;
   int i;
   int ret = -1;
   ssize_t devices = libusb_get_device_list(NULL, &devs);

   for(i = 0; i < devices; i++)
   {
     int r = libusb_get_device_descriptor(devs[i],&desc);
     if(r >= 0 && desc.idVendor == VID && desc.idProduct == PID)
     {
 	    ret = libusb_open(devs[i], &devhandler);
     }
   }

   ret = libusb_set_configuration(devhandler, CONFIG);

   if (ret < 0)
   {
	   libusb_close(devhandler);
   }

   if (libusb_claim_interface(devhandler, DATA_INTF) < 0)
   {
	   libusb_close(devhandler);
   }

   return ret;
 }
/**
 *@}
 */
/**
  *@}
  */
/**
  *@}
  */
