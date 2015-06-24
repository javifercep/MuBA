/*
  ******************************************************************************
  * @file    Interrupt_Functions.h
  * @author  Javier Fernández Cepeda
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INTERRUPT_FUNCTIONS_H
#define __INTERRUPT_FUNCTIONS_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#if MCU_STM32F4XX > 0
#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void); //not used
void HardFault_Handler(void); //not used
void MemManage_Handler(void); //not used
void BusFault_Handler(void); //not used
void UsageFault_Handler(void); //not used
void SVC_Handler(void); //not used
void DebugMon_Handler(void); //not used
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void TIM7_IRQHandler(void);

//void PendSV_Handler(void);
//void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */
