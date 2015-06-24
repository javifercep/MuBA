/**
  ******************************************************************************
  * @file    USARTAPI.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains constants definitions which help users develop
  * 		 with USART.
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
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USARTAPI_H
#define __USARTAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

 /*Includes ------------------------------------------------------------------*/

 /*MCU includes*/
#include "SysConfig.h"
#if USART_API > 0
#if MCU_STM32F4XX > 0
#include "stm32f4xx.h"                  // Keil::Device:Startup
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic
#endif

/*Other includes*/

/* Exported define ------------------------------------------------------------*/
/* USART default configuration */
#define USART_BITS						  8
#define USART_INIT_BAUDRATE			115200 /* baud/s */ 

#define USART_OK 		0
#define USART_KO 		1 
   
/* Specific USART parameters */
#define USART_DEFAULT_CONFIG  0x0001
#define USART_MODE            0x0002
#define USART_DATA_BITS       0x0003
#define USART_PARITY          0x0004
#define USART_STOP_BITS       0x0005
#define USART_FLOW_CONTROL    0x0006
#define USART_BAUD_RATE       0x0007

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and deinitialization functions*/
int32_t USARTInit(void);
int32_t USARTDeInit(void);

/* Communication functions */
uint32_t USARTDataAvailable(void);
uint32_t USARTSizeDataAvailable(void);
uint32_t USARTWrite(uint8_t *pBuf, uint32_t size);
uint32_t USARTRead(uint8_t *pBuf, uint32_t size);
 
/* Configuration functions */
int32_t USARTConfiguration(uint16_t param, void *arg);
 
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

#endif /* __USARTAPI_H */
