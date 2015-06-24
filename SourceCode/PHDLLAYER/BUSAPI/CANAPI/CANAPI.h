/*
  ******************************************************************************
  * @file    CANAPI.h
  * @author  Javier Fern�ndez Cepeda
  * @version V0.0.3
  * @date    26-August-2013
  * @brief   This file contains constants definitions which help users develop
  * 		 CAN applications.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CANAPI_H
#define __CANAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#if CAN_API > 0

#if MCU_STM32F4XX > 0
#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic
#endif

#include <stdlib.h>

/* Exported define -----------------------------------------------------------*/

/* Default Configuration */
#define CAN1_SPEED 5
#define CAN2_SPEED 5

/* CAN1 SBACAN Board interface */
#define CAN1_CLK 		RCC_APB1Periph_CAN1
#define CAN1_PIN_CLK 	RCC_APB2Periph_GPIOA
#define CAN1_PORT		GPIOA
#define CAN1_PINTX		GPIO_Pin_12
#define CAN1_PINRX		GPIO_Pin_11


/* CAN2 SBACAN Board interface */
#define CAN2_CLK 		RCC_APB1Periph_CAN2
#define CAN2_PIN_CLK 	RCC_APB2Periph_GPIOB
#define CAN2_PORT		GPIOB
#define CAN2_PINTX		GPIO_Pin_13
#define CAN2_PINRX		GPIO_Pin_12


#define CANBuf_EMPTY 0x01
#define CANBuf_FULL  0x01

/* Exported types ------------------------------------------------------------*/

 typedef struct{
	 uint8_t  size;
	 uint8_t  start;
	 uint8_t  count;
	 //CanRxMsg *Data;
 }CANBuffer;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void InitCAN1_DefaultConfig(void);
void InitCAN2_DefaultConfig(void);
void InitCANFilters_DefaultConfig(void);
void CAN1_EnableInterrupt(void);
void CAN1_DisableInterrupt(void);
void CAN2_EnableInterrupt(void);

///*Functions for Manage buffer*/
//void Init_CANBuffer(__IO CANBuffer *pBuffer, uint8_t BufferLength);
//void Free_CANBuffer(__IO CANBuffer *pBuffer);
//uint8_t CANBufferisFull(__IO CANBuffer *pBuffer);
//uint8_t CANBufferisEmpty(__IO CANBuffer *pBuffer);
//void Read_CANMessage(__IO CANBuffer *pBuffer,  CanRxMsg *pMessage);
//void Write_CANMessage(__IO CANBuffer *pBuffer, CanRxMsg *pMessage);
//uint8_t numDatainCANBuffer(__IO CANBuffer *pBuffer);

#endif

#ifdef __cplusplus
}
#endif

#endif /* __CANAPI_H */
