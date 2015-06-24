/**
  ******************************************************************************
  * @file    boardAPI.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains constants definitions which help users develop
  * 		 with MBA boards.
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
	*	@addtogroup Board_API
	*	@{ 
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BOARDAPI_H
#define __BOARDAPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#if DEVICE_SUPPORT > 0
/* MCU specific includes */
#include "stm32f4xx.h"
#include "stm32f4xx_hal_conf.h"         // Keil::Device:STM32Cube Framework:Classic


/*Other includes*/
#include "../../MBALibrary/MBATypes.h"


 /* Exported define ------------------------------------------------------------*/

 /* LEDx boards Interface */

#define numLEDs						4

#define LED1_PIN							GPIO_PIN_9
#define LED1_GPIO_PORT				GPIOC

#define LED2_PIN							GPIO_PIN_8
#define LED2_GPIO_PORT				GPIOC

#define LED3_PIN							GPIO_PIN_7
#define LED3_GPIO_PORT				GPIOC

#define LED4_PIN							GPIO_PIN_6
#define LED4_GPIO_PORT				GPIOC


/* Total expansion pin */
#define numPins 29

/*analog Pins mapping*/

#define A0		17
#define A1		18
#define A2		19
#define A3		20
#define A4		21
#define A5		22
#define A6		23
#define A7		24
#define A8		25
#define A9		26
#define A10	    27
#define A11		28

/* digital Pins boards Interface */

#define ENABLE_BOARD_PIN_CLK()		{__GPIOA_CLK_ENABLE();\
																	 __GPIOB_CLK_ENABLE();\
																	 __GPIOC_CLK_ENABLE();\
																	 __GPIOD_CLK_ENABLE();}

#define PIN0_PIN								GPIO_PIN_1
#define PIN0_GPIO_PORT					GPIOA
#define PIN0_EXTI_LINE					EXTI_Line1
#define PIN0_EXTI_IRQn          EXTI1_IRQn

#define PIN1_PIN								GPIO_PIN_0
#define PIN1_GPIO_PORT					GPIOA
#define PIN1_GPIO_CLK						RCC_AHB1Periph_GPIOA
#define PIN1_GPIO_SOURCE				EXTI_PinSource0
#define PIN1_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN1_EXTI_LINE					EXTI_Line0
#define PIN1_EXTI_IRQn          EXTI0_IRQn

#define PIN2_PIN								GPIO_PIN_14
#define PIN2_GPIO_PORT					GPIOB
#define PIN2_GPIO_CLK						RCC_AHB1Periph_GPIOB
#define PIN2_GPIO_SOURCE				EXTI_PinSource14
#define PIN2_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PIN2_EXTI_LINE					EXTI_Line14
#define PIN2_EXTI_IRQn          EXTI15_10_IRQn

#define PIN3_PIN								GPIO_PIN_8
#define PIN3_GPIO_PORT					GPIOA
#define PIN3_GPIO_CLK						RCC_AHB1Periph_GPIOA
#define PIN3_GPIO_SOURCE				EXTI_PinSource8
#define PIN3_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN3_EXTI_LINE					EXTI_Line8
#define PIN3_EXTI_IRQn          EXTI9_5_IRQn

#define PIN4_PIN								GPIO_PIN_15
#define PIN4_GPIO_PORT					GPIOB
#define PIN4_GPIO_CLK						RCC_AHB1Periph_GPIOB
#define PIN4_GPIO_SOURCE				EXTI_PinSource15
#define PIN4_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PIN4_EXTI_LINE					EXTI_Line15
#define PIN4_EXTI_IRQn          EXTI15_10_IRQn

#define PIN5_PIN								GPIO_PIN_9
#define PIN5_GPIO_PORT					GPIOA
#define PIN5_GPIO_CLK						RCC_AHB1Periph_GPIOA
#define PIN5_GPIO_SOURCE				EXTI_PinSource9
#define PIN5_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN5_EXTI_LINE					EXTI_Line9
#define PIN5_EXTI_IRQn          EXTI9_5_IRQn

#define PIN6_PIN								GPIO_PIN_10
#define PIN6_GPIO_PORT					GPIOA
#define PIN6_GPIO_CLK						RCC_AHB1Periph_GPIOA
#define PIN6_GPIO_SOURCE				EXTI_PinSource10
#define PIN6_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN6_EXTI_LINE					EXTI_Line10
#define PIN6_EXTI_IRQn          EXTI15_10_IRQn

#define PIN7_PIN								GPIO_PIN_12
#define PIN7_GPIO_PORT					GPIOA
#define PIN7_GPIO_CLK						RCC_AHB1Periph_GPIOA
#define PIN7_GPIO_SOURCE				EXTI_PinSource12
#define PIN7_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN7_EXTI_LINE					EXTI_Line12
#define PIN7_EXTI_IRQn          EXTI15_10_IRQn

#define PIN8_PIN								GPIO_PIN_2
#define PIN8_GPIO_PORT					GPIOD
#define PIN8_GPIO_CLK						RCC_AHB1Periph_GPIOD
#define PIN8_GPIO_SOURCE				EXTI_PinSource2
#define PIN8_PORT_SOURCE				EXTI_PortSourceGPIOD
#define PIN8_EXTI_LINE					EXTI_Line2
#define PIN8_EXTI_IRQn          EXTI2_IRQn

#define PIN9_PIN								GPIO_PIN_11
#define PIN9_GPIO_PORT					GPIOA
#define PIN9_GPIO_CLK						RCC_AHB1Periph_GPIOA
#define PIN9_GPIO_SOURCE				EXTI_PinSource11
#define PIN9_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN9_EXTI_LINE					EXTI_Line11
#define PIN9_EXTI_IRQn          EXTI15_10_IRQn

#define PIN10_PIN								GPIO_PIN_15
#define PIN10_GPIO_PORT					GPIOA
#define PIN10_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PIN10_GPIO_SOURCE				EXTI_PinSource15
#define PIN10_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PIN10_EXTI_LINE					EXTI_Line15
#define PIN10_EXTI_IRQn        	EXTI15_10_IRQn

#define PIN11_PIN								GPIO_PIN_12
#define PIN11_GPIO_PORT					GPIOC
#define PIN11_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN11_GPIO_SOURCE				EXTI_PinSource12
#define PIN11_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PIN11_EXTI_LINE					EXTI_Line12
#define PIN11_EXTI_IRQn         EXTI15_10_IRQn

#define PIN12_PIN								GPIO_PIN_11
#define PIN12_GPIO_PORT					GPIOC
#define PIN12_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN12_GPIO_SOURCE				EXTI_PinSource11
#define PIN12_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PIN12_EXTI_LINE					EXTI_Line11
#define PIN12_EXTI_IRQn         EXTI15_10_IRQn

#define PIN13_PIN								GPIO_PIN_10
#define PIN13_GPIO_PORT					GPIOC
#define PIN13_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN13_GPIO_SOURCE				EXTI_PinSource10
#define PIN13_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PIN13_EXTI_LINE					EXTI_Line10
#define PIN13_EXTI_IRQn         EXTI15_10_IRQn

#define PIN14_PIN								GPIO_PIN_2
#define PIN14_GPIO_PORT					GPIOB
#define PIN14_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PIN14_GPIO_SOURCE				EXTI_PinSource2
#define PIN14_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PIN14_EXTI_LINE					EXTI_Line2
#define PIN14_EXTI_IRQn         EXTI2_IRQn

#define PIN15_PIN								GPIO_PIN_5
#define PIN15_GPIO_PORT					GPIOC
#define PIN15_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN15_GPIO_SOURCE				EXTI_PinSource5
#define PIN15_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PIN15_EXTI_LINE					EXTI_Line5
#define PIN15_EXTI_IRQn         EXTI9_5_IRQn

#define PIN16_PIN								GPIO_PIN_4
#define PIN16_GPIO_PORT					GPIOC
#define PIN16_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PIN16_GPIO_SOURCE				EXTI_PinSource4
#define PIN16_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PIN16_EXTI_LINE					EXTI_Line4
#define PIN16_EXTI_IRQn         EXTI4_IRQn


#define PINA0_PIN								GPIO_PIN_8
#define PINA0_GPIO_PORT					GPIOB
#define PINA0_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PINA0_GPIO_SOURCE				EXTI_PinSource8
#define PINA0_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PINA0_EXTI_LINE					EXTI_Line8
#define PINA0_EXTI_IRQn         EXTI9_5_IRQn

#define PINA1_PIN								GPIO_PIN_13
#define PINA1_GPIO_PORT					GPIOC
#define PINA1_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA1_GPIO_SOURCE				EXTI_PinSource13
#define PINA1_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PINA1_EXTI_LINE					EXTI_Line13
#define PINA1_EXTI_IRQn         EXTI15_10_IRQn

#define PINA2_PIN								GPIO_PIN_15
#define PINA2_GPIO_PORT					GPIOC
#define PINA2_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA2_GPIO_SOURCE				EXTI_PinSource15
#define PINA2_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PINA2_EXTI_LINE					EXTI_Line15
#define PINA2_EXTI_IRQn         EXTI15_10_IRQn

#define PINA3_PIN								GPIO_PIN_2
#define PINA3_GPIO_PORT					GPIOA
#define PINA3_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PINA3_GPIO_SOURCE				EXTI_PinSource2
#define PINA3_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PINA3_EXTI_LINE					EXTI_Line2
#define PINA3_EXTI_IRQn         EXTI2_IRQn

#define PINA4_PIN								GPIO_PIN_7
#define PINA4_GPIO_PORT					GPIOB
#define PINA4_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PINA4_GPIO_SOURCE				EXTI_PinSource7
#define PINA4_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PINA4_EXTI_LINE					EXTI_Line7
#define PINA4_EXTI_IRQn         EXTI9_5_IRQn

#define PINA5_PIN								GPIO_PIN_6
#define PINA5_GPIO_PORT					GPIOB
#define PINA5_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PINA5_GPIO_SOURCE				EXTI_PinSource6
#define PINA5_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PINA5_EXTI_LINE					EXTI_Line6
#define PINA5_EXTI_IRQn         EXTI9_5_IRQn

#define PINA6_PIN								GPIO_PIN_9
#define PINA6_GPIO_PORT					GPIOB
#define PINA6_GPIO_CLK					RCC_AHB1Periph_GPIOB
#define PINA6_GPIO_SOURCE				EXTI_PinSource9
#define PINA6_PORT_SOURCE				EXTI_PortSourceGPIOB
#define PINA6_EXTI_LINE					EXTI_Line9
#define PINA6_EXTI_IRQn         EXTI9_5_IRQn

#define PINA7_PIN								GPIO_PIN_14
#define PINA7_GPIO_PORT					GPIOC
#define PINA7_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA7_GPIO_SOURCE				EXTI_PinSource14
#define PINA7_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PINA7_EXTI_LINE					EXTI_Line14
#define PINA7_EXTI_IRQn         EXTI15_10_IRQn

#define PINA8_PIN								GPIO_PIN_1
#define PINA8_GPIO_PORT					GPIOC
#define PINA8_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define PINA8_GPIO_SOURCE				EXTI_PinSource1
#define PINA8_PORT_SOURCE				EXTI_PortSourceGPIOC
#define PINA8_EXTI_LINE					EXTI_Line1
#define PINA8_EXTI_IRQn         EXTI1_IRQn

#define PINA9_PIN								GPIO_PIN_4
#define PINA9_GPIO_PORT					GPIOA
#define PINA9_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PINA9_GPIO_SOURCE				EXTI_PinSource4
#define PINA9_PORT_SOURCE				EXTI_PortSourceGPIOA
#define PINA9_EXTI_LINE					EXTI_Line4
#define PINA9_EXTI_IRQn         EXTI4_IRQn

#define PINA10_PIN							GPIO_PIN_6
#define PINA10_GPIO_PORT				GPIOA
#define PINA10_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PINA10_GPIO_SOURCE			EXTI_PinSource6
#define PINA10_PORT_SOURCE			EXTI_PortSourceGPIOA
#define PINA10_EXTI_LINE				EXTI_Line6
#define PINA10_EXTI_IRQn        EXTI9_5_IRQn

#define PINA11_PIN							GPIO_PIN_7
#define PINA11_GPIO_PORT				GPIOA
#define PINA11_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define PINA11_GPIO_SOURCE			EXTI_PinSource7
#define PINA11_PORT_SOURCE			EXTI_PortSourceGPIOA
#define PINA11_EXTI_LINE				EXTI_Line7
#define PINA11_EXTI_IRQn        EXTI9_5_IRQn

/* Interrupt priorities */
#define BOARD_PIN_PREEMPTION_PRIORITY	 0x00
#define BOARD_PIN_SUBPRIORITY					 0x07



/* Exported types ------------------------------------------------------------*/

typedef enum
{
	LED1 = 0,
	LED2 = 1,
	LED3 = 2,
	LED4 = 3
} Led_TypeDef;


typedef enum
{
	INPUT_PULLUP		= 0,
	INPUT_PULLDOWN 	= 1,
	INPUT_OD				= 2,
	OUTPUT_PULLUP		= 3,
	OUTPUT_PULLDOWN = 4,
	OUTPUT_OD				= 5,
}pinMode_Typedef;

typedef enum
{
	LOW = 0,
	HIGH = 1,
} PinState;

typedef enum
{
	NONE = 0,
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
} InterruptEventMode;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*LED functions*/
void BoardInitialize(void);

/* Individual functions */
void LEDOn(Led_TypeDef Led);
void LEDOff(Led_TypeDef Led);
void LEDToggle(Led_TypeDef Led);

/* Block functions */
void LEDOnAll(void);
void LEDOffAll(void);
void LEDToggleAll(void);

/*General Input/Output Functions */
void PinMode(uint32_t pinNumber, pinMode_Typedef Mode, InterruptEventMode IntEvent, void (*userFunc)(void));
void PinWrite(uint32_t pinNumber, PinState State);
PinState PinRead(uint32_t pinNumber);
void PinToggle(uint32_t pinNumber);


/* System Clock Configuration */
void SystemClock_Config(void);

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

#endif /* __BOARDAPI_H */
