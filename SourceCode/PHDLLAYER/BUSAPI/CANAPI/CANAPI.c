/*
  ******************************************************************************
  * @file    CANAPI.c
  * @author  Javier Fernandez Cepeda
  * @version V0.0.2
  * @date    10-August-2013
  * @brief   This file contains functions descriptions which help users develop
  * 		 CAN applications.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "CANAPI.h"
#if CAN_API > 0
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t count7=0,count8=0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   This funtions initializes CAN1 default configuration:
  * 			TTCM  		= DISABLE
  * 			ABOM  		= DISABLE
  * 			AWUM  		= DISABLE
  * 			NART  		= DISABLE
  * 			RFLM  		= DISABLE
  * 			TXFP  		= DISABLE
  * 			SJW   		= 1tq
  * 			BS1   		= 5tq
  * 			BS2   		= 2tq
  * 			Preescaler 	= 3
  * 		 Configures IRQ RX0 (NVIC)
  * 		CAN Speed:
  * 		tq = (1/42Mhz)*(3+1) = 95,2 ns
  * 		baudrate = 1/((1+5+2)*tq)=1312500 => 1Mbps
  * @param  None
  * @retval None
  */
 void InitCAN1_DefaultConfig(void)
 {
//	 CAN_InitTypeDef        CAN_InitStructure;
//	 GPIO_InitTypeDef 	    GPIO_InitStructure;
//	 NVIC_InitTypeDef 		NVIC_InitStructure;

//	 /*Enable CAN1 clock*/
//	 RCC_APB1PeriphClockCmd(CAN1_CLK, ENABLE);

//	 /*Enable GPIO clock*/
//	 RCC_APB2PeriphClockCmd(CAN1_PIN_CLK, ENABLE);

//	 /*CAN1_Tx*/
//	 GPIO_InitStructure.GPIO_Pin = CAN1_PINTX;
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	 GPIO_Init(CAN1_PORT, &GPIO_InitStructure);

//	 /*CAN1_Rx*/
//	 GPIO_InitStructure.GPIO_Pin = CAN1_PINRX;
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	 GPIO_Init(CAN1_PORT, &GPIO_InitStructure);

//	 /* CAN register init */
//	 CAN_DeInit(CAN1);

//	 /* CAN cell init */
//	 CAN_InitStructure.CAN_TTCM = DISABLE;
//	 CAN_InitStructure.CAN_ABOM = DISABLE;
//	 CAN_InitStructure.CAN_AWUM = DISABLE;
//	 CAN_InitStructure.CAN_NART = DISABLE;
//	 CAN_InitStructure.CAN_RFLM = DISABLE;
//	 CAN_InitStructure.CAN_TXFP = DISABLE;
//	 CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//	 CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
//	 CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;
//	 CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
//	 CAN_InitStructure.CAN_Prescaler = 3;
//	 CAN_Init(CAN1, &CAN_InitStructure);

//	 /* Enable CANx RX0 interrupt IRQ channel */
//	 NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	 NVIC_Init(&NVIC_InitStructure);

// }

// /**
//   * @brief   This funtions initializes CAN2 default configuration:
//   * 			TTCM  		= DISABLE
//   * 			ABOM  		= DISABLE
//   * 			AWUM  		= DISABLE
//   * 			NART  		= DISABLE
//   * 			RFLM  		= DISABLE
//   * 			TXFP  		= DISABLE
//   * 			SJW   		= 1tq
//   * 			BS1   		= 6tq
//   * 			BS2   		= 8tq
//   * 			Preescaler 	= 5
//   * 		 Configures IRQ RX1 (NVIC)
//   * 		CAN Speed:
//   * 		tq = (1/42Mhz)*(5+1) = 142,9 ns
//   * 		baudrate = 1/((1+6+8)*tq) = 466,7 kbps
//   * @param  None
//   * @retval None
//   */
// void InitCAN2_DefaultConfig(void)
// {
//	 CAN_InitTypeDef        CAN_InitStructure;
//	 GPIO_InitTypeDef 	    GPIO_InitStructure;
//	 NVIC_InitTypeDef 		NVIC_InitStructure;

//	 /*Enable CAN2 clock*/
//	 RCC_APB1PeriphClockCmd(CAN2_CLK, ENABLE);

//	 /*Enable GPIO clock*/
//	 RCC_APB2PeriphClockCmd(CAN2_PIN_CLK, ENABLE);

//	 /*CAN2_Tx*/
//	 GPIO_InitStructure.GPIO_Pin = CAN2_PINTX;
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	 GPIO_Init(CAN2_PORT, &GPIO_InitStructure);

//	 /*CAN2_Rx*/
//	 GPIO_InitStructure.GPIO_Pin = CAN2_PINRX;
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	 GPIO_Init(CAN2_PORT, &GPIO_InitStructure);

//	 /* CAN register init */
//	 CAN_DeInit(CAN2);

//	 /* CAN cell init */
//	 CAN_InitStructure.CAN_TTCM = DISABLE;
//	 CAN_InitStructure.CAN_ABOM = DISABLE;
//	 CAN_InitStructure.CAN_AWUM = DISABLE;
//	 CAN_InitStructure.CAN_NART = DISABLE;
//	 CAN_InitStructure.CAN_RFLM = DISABLE;
//	 CAN_InitStructure.CAN_TXFP = DISABLE;
//	 CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//	 CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
//	 CAN_InitStructure.CAN_BS1 = CAN_BS1_6tq;
//	 CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;
//	 CAN_InitStructure.CAN_Prescaler = 5;
//	 CAN_Init(CAN2, &CAN_InitStructure);

//	 /* Enable CANx RX0 interrupt IRQ channel */
//	 NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
//	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
//	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	 NVIC_Init(&NVIC_InitStructure);

 }


 /**
   * @brief   This funtions initializes CAN Filters default configuration:
   * 			Mode = IdMask
   * 			Scale = 32bit
   * 			Id High = 0x0000
   * 			Id Low = 0x0000
   * 			Mask Id High = 0x0000
   * 			Mask Id Low = 0x0000
   * 			FIFO Assignment = CAN_FIFO0
   * 		  The first bank filter for Slave (CAN2) is 10 and have the same
   * 		  configuration than master (CAN1) except:
   * 		  	FIFO Assignment = CAN_FIFO1
   *
   * @param  None
   * @retval None
   */
 void InitCANFilters_DefaultConfig(void)
 {
//	 CAN_FilterInitTypeDef  CAN_FilterInitStructure;

//	 /* CAN1 filter init */
//	 CAN_FilterInitStructure.CAN_FilterNumber = 0;
//	 CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//	 CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//	 CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
//	 CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//	 CAN_FilterInit(&CAN_FilterInitStructure);

//	 CAN_SlaveStartBank(10);

//	 /* CAN2 filter init */
//	 CAN_FilterInitStructure.CAN_FilterNumber = 10;
//	 CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
//	 CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
//	 CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
//	 CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO1;
//	 CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
//	 CAN_FilterInit(&CAN_FilterInitStructure);
 }

 /**
   * @brief   This funtion enables CAN1 interrupt if there is a pending message in FIFO0.
   * 		  Remember to complete the code of stm32f10x_it.c file.
   * @param  None
   * @retval None
   */
 void CAN1_EnableInterrupt(void)
 {
	 /* CAN FIFO0 message pending interrupt enable */
	 //CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
 }

 /**
    * @brief  This funtion disables CAN1 interrupt.
    * @param  None
    * @retval None
    */
  void CAN1_DisableInterrupt(void)
  {
 	 /* CAN FIFO0 message pending interrupt enable */
 	 //CAN_ITConfig(CAN1, CAN_IT_FMP0, DISABLE);
  }


 /**
   * @brief   This funtion enables CAN2 interrupt if there is a pending message in FIFO1.
   * 		  Remember to complete the code of stm32f10x_it.c file.
   * @param  None
   * @retval None
   */
 void CAN2_EnableInterrupt(void)
 {
	 /* CAN FIFO1 message pending interrupt enable */
	 //CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);
 }

#endif

