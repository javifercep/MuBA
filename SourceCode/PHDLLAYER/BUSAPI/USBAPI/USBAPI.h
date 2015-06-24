/**
  ******************************************************************************
  * @file    USBSerial.h
  * @author  Javier Fernandez Cepeda
  * @brief   USB API
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
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBAPI_H
#define __USBAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#if USB_API > 0
#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic

/* Exported define ------------------------------------------------------------*/
#define MBA_USB_DRIVER 1
	 
#define USB_OK 		0
#define USB_KO		1
   
/* Specific configuration parameters */
#define USB_DEFAULT_CONFIG    0x0001
   
/* Configuration parameters */
	 
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and deinitialization functions*/
int32_t USBInit(void);
int32_t USBDeInit(void);
 
/* Communication functions */
uint32_t USBDataAvailable(void);
uint32_t USBSizeDataAvailable(void);
uint32_t USBRead(uint8_t *data, uint32_t size);
uint32_t USBWrite(uint8_t *data, uint32_t size);
 
/* Configuration functions */
int32_t USBConfiguration(uint16_t param, void *arg);

/* Debug & Error control functions */
void USBSendError(char *s);
void USBSendDebug(const char *s);

/**
	*@}
	*/
/**
	*@}
	*/
/**
	*@}
	*/
#endif

#ifdef __cplusplus
}
#endif

#endif /* __USBAPI_H */
