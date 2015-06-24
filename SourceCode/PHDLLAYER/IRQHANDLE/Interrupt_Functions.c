/*
  ******************************************************************************
  * @file    Interrupt Functions.c
  * @author  Javier Fernández Cepeda
  * @brief   Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and
  *         peripherals interrupt service routine.
  ******************************************************************************
*/


/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#if WINDOWS == 0

#include "Interrupt_Functions.h"
#include "../../MBALibrary/MBATypes.h"
#include "../BOARDAPI/boardAPI.h"

#include "../BUSAPI/USBAPI/USBAPI.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifndef WEAK
	#define WEAK __attribute__ ((weak))
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* TODO Add interrupt manager */
extern volatile voidFuncPtr EXTI_CallBack[numPins];
extern volatile voidFuncPtr Timer_CallBack;

//#if USB_FIRM > 0
//extern USB_OTG_CORE_HANDLE           USB_OTG_dev;
//extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);

//#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
//extern uint32_t USBD_OTG_EP1IN_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
//extern uint32_t USBD_OTG_EP1OUT_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
//#endif
//#endif /* USB_FIRM */
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void WEAK SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/



/**
  * @brief  This function handles EXTI0 Handler.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	  /* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN1_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN1_PIN);
    if(EXTI_CallBack[1]){ EXTI_CallBack[1](); }
  }
}


/**
  * @brief  This function handles EXTI1 Handler.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN1_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN1_PIN);
		if(EXTI_CallBack[0]){ EXTI_CallBack[0](); }
  }
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA8_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA8_PIN);
		if(EXTI_CallBack[A8]){ EXTI_CallBack[A8](); }
	}
}

/**
  * @brief  This function handles EXTI0 Handler.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
		/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN8_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN8_PIN);
		if(EXTI_CallBack[8]){ EXTI_CallBack[8](); }
  }
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN14_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN14_PIN);
		if(EXTI_CallBack[14]){ EXTI_CallBack[14](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA3_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA3_PIN);
		if(EXTI_CallBack[A3]){ EXTI_CallBack[A3](); }
	}
}

/**
  * @brief  This function handles EXTI3 Handler.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{

}


/**
  * @brief  This function handles EXTI4 Handler.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN16_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN16_PIN);
		if(EXTI_CallBack[16]){ EXTI_CallBack[16](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA9_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA9_PIN);
		if(EXTI_CallBack[A9]){ EXTI_CallBack[A9](); }
	}
}

/**
  * @brief  This function handles EXTI9_5 Handler.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN3_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN3_PIN);
		if(EXTI_CallBack[3]){ EXTI_CallBack[3](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN5_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN5_PIN);
		if(EXTI_CallBack[5]){ EXTI_CallBack[5](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN15_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN15_PIN);
		if(EXTI_CallBack[15]){ EXTI_CallBack[15](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA0_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA0_PIN);
		if(EXTI_CallBack[A0]){ EXTI_CallBack[A0](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA4_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA4_PIN);
		if(EXTI_CallBack[A4]){ EXTI_CallBack[A4](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA5_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA5_PIN);
		if(EXTI_CallBack[A5]){ EXTI_CallBack[A5](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA6_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA6_PIN);
		if(EXTI_CallBack[A6]){ EXTI_CallBack[A6](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA10_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA10_PIN);
		if(EXTI_CallBack[A10]){ EXTI_CallBack[A10](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA11_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA11_PIN);
		if(EXTI_CallBack[A11]){ EXTI_CallBack[A11](); }
	}
}


/**
  * @brief  This function handles EXTI15_10 Handler.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN2_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN2_PIN);
		if(EXTI_CallBack[2]){ EXTI_CallBack[2](); }
	}

	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN4_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN4_PIN);
		if(EXTI_CallBack[4]){ EXTI_CallBack[4](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN6_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN6_PIN);
		if(EXTI_CallBack[6]){ EXTI_CallBack[6](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN7_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN7_PIN);
		if(EXTI_CallBack[7]){ EXTI_CallBack[7](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN9_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN9_PIN);
		if(EXTI_CallBack[9]){ EXTI_CallBack[9](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN10_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN10_PIN);
		if(EXTI_CallBack[10]){ EXTI_CallBack[10](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN11_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN11_PIN);
		if(EXTI_CallBack[11]){ EXTI_CallBack[11](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN12_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN12_PIN);
		if(EXTI_CallBack[12]){ EXTI_CallBack[12](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PIN13_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PIN13_PIN);
		if(EXTI_CallBack[13]){ EXTI_CallBack[13](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA1_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA1_PIN);
		if(EXTI_CallBack[A1]){ EXTI_CallBack[A1](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA2_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA2_PIN);
		if(EXTI_CallBack[A2]){ EXTI_CallBack[A2](); }
	}
	
	/* EXTI line interrupt detected */
  if(__HAL_GPIO_EXTI_GET_IT(PINA7_PIN) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(PINA7_PIN);
		if(EXTI_CallBack[A7]){ EXTI_CallBack[A7](); }
	}

}

/**
  * @brief  This function handles USB FS Wake UP Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_FS
void OTG_FS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
  EXTI_ClearITPendingBit(EXTI_Line18);
}
#endif


/**
  * @brief  This function handles USB HS Wake UP Handler.
  * @param  None
  * @retval None
  */
#ifdef USE_USB_OTG_HS
void OTG_HS_WKUP_IRQHandler(void)
{
  if(USB_OTG_dev.cfg.low_power)
  {
    *(uint32_t *)(0xE000ED10) &= 0xFFFFFFF9 ;
    SystemInit();
    USB_OTG_UngateClock(&USB_OTG_dev);
  }
 // EXTI_ClearITPendingBit(EXTI_Line20);
}
#endif


///**
//  * @brief  This function handles OTG_HS Handler.
//  * @param  None
//  * @retval None
//  */
//#ifdef USE_USB_OTG_HS
//void OTG_HS_IRQHandler(void)
//#else
//void OTG_FS_IRQHandler(void)
//#endif
//{
////  USBD_OTG_ISR_Handler (&USB_OTG_dev);
//}

//#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
///**
//  * @brief  This function handles EP1_IN Handler.
//  * @param  None
//  * @retval None
//  */
//void OTG_HS_EP1_IN_IRQHandler(void)
//{
//  USBD_OTG_EP1IN_ISR_Handler (&USB_OTG_dev);
//}

///**
//  * @brief  This function handles EP1_OUT Handler.
//  * @param  None
//  * @retval None
//  */
//void OTG_HS_EP1_OUT_IRQHandler(void)
//{
//  USBD_OTG_EP1OUT_ISR_Handler (&USB_OTG_dev);
//}
//#endif


/**
  * @brief  This function handles Timer X interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
//	if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
//	{
//		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//		Timer_CallBack();
//	}
}


/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void WEAK PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void WEAK SysTick_Handler(void)
{

}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
#endif

