/**
  ******************************************************************************
  * @file    USBHOSTAPI.h
  * @author  Javier Fernandez Cepeda
  * @brief   USB Host API
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup Bus
  *@{
  *
  *	@addtogroup Bus_Interface
  *	@{
  *
  *		@addtogroup USB_API
  *		@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBHOSTAPI_H
#define __USBHOSTAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported define ------------------------------------------------------------*/
#define MBA_USB_DRIVER 	1
	 
#define USB_OK 		0
#define USB_KO		1
   
/* Configuration parameters */
	 
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and deinitialization functions*/
int32_t USBHostInit(void);
int32_t USBHostDeInit(void);
 
/* Communication functions */
uint32_t USBHostDataAvailable(void);
uint32_t USBHostSizeDataAvailable(void);
uint32_t USBHostRead(uint8_t *data, uint32_t size);
uint32_t USBHostWrite(uint8_t *data, uint32_t size);
 
/* Configuration functions */
int32_t USBHostConfiguration(uint16_t param, void *arg);


/**
	*@}
	*/
/**
	*@}
	*/
/**
	*@}
	*/


#ifdef __cplusplus
}
#endif

#endif /* __USBHOSTAPI_H */
