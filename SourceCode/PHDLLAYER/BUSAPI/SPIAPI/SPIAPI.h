/**
  ******************************************************************************
  * @file    SPIAPI.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains constants definitions which help users develop
  * 		 with SPI1.
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
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPIAPI_H
#define __SPIAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

 /*Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#if SPI_API > 0

#if MCU_STM32F4XX > 0
 /*MCU includes*/
#include "stm32f4xx.h"                  // Keil::Device:Startup
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic
#endif

/*Other includes*/

/* Exported define ------------------------------------------------------------*/
 
#define SPI_BITS								8
#define SPI_INIT_BAUDRATE				1000000 /* 1 Mbps */
#define B2B_SPI_DRIVER					Driver_SPI3

/* Determines if SPI firmwares acts as Master or Slave */
#define SPI_MASTER 				1	/* 1 for SBAUSB, 0 otherwise */
	 
#define SPI_OK 		0
#define SPI_KO 		1

/* Specific configuration parameters */
#define SPI_DEFAULT_CONFIG    0x0001

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and deinitialization functions*/
int32_t SPIInit(void);
int32_t SPIDeInit(void);

/* Communication functions */
uint32_t SPIDataAvailable(void);
uint32_t SPISizeDataAvailable(void);
uint32_t SPIWrite(uint8_t *pBuf, uint32_t size);
uint32_t SPIRead(uint8_t *pBuf, uint32_t size);
 
/* Configuration functions */
int32_t SPIConfiguration(uint16_t param, void *arg);
 
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

#endif /* __SPIAPI_H */
