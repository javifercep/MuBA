/**
  ******************************************************************************
  * @file    boardAPI.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains functions descriptions which help users develop
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
	*		@brief Board API.
	*		@details 
*/

/* Includes ------------------------------------------------------------------*/
#include "boardAPI.h"
#if DEVICE_SUPPORT > 0
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* GPIO Pin identifier */
typedef struct _GPIO_PIN {
	GPIO_TypeDef *port;
  uint16_t      pin;
	uint16_t			IRQExti;
} GPIO_PIN;

/* LED GPIO Pins */
static const GPIO_PIN LED_PIN[] = {
  {LED1_GPIO_PORT, LED1_PIN, NULL},
  {LED2_GPIO_PORT, LED2_PIN, NULL},
	{LED3_GPIO_PORT, LED3_PIN, NULL},
	{LED4_GPIO_PORT, LED4_PIN, NULL}
};

/* LED GPIO Pins */
static const GPIO_PIN BOARD_PINS[] = {
  {PIN0_GPIO_PORT, 		PIN0_PIN, PIN0_EXTI_IRQn},
  {PIN1_GPIO_PORT, 		PIN1_PIN, PIN1_EXTI_IRQn},
	{PIN2_GPIO_PORT, 		PIN2_PIN, PIN2_EXTI_IRQn},
	{PIN3_GPIO_PORT, 		PIN3_PIN, PIN3_EXTI_IRQn},
	{PIN4_GPIO_PORT, 		PIN4_PIN, PIN4_EXTI_IRQn},
  {PIN5_GPIO_PORT, 		PIN5_PIN, PIN5_EXTI_IRQn},
	{PIN6_GPIO_PORT, 		PIN6_PIN, PIN6_EXTI_IRQn},
	{PIN7_GPIO_PORT, 		PIN7_PIN, PIN7_EXTI_IRQn},
	{PIN8_GPIO_PORT, 		PIN8_PIN, PIN8_EXTI_IRQn},
  {PIN9_GPIO_PORT, 		PIN9_PIN, PIN9_EXTI_IRQn},
	{PIN10_GPIO_PORT, 	PIN10_PIN, PIN10_EXTI_IRQn},
	{PIN11_GPIO_PORT, 	PIN11_PIN, PIN11_EXTI_IRQn},
	{PIN12_GPIO_PORT, 	PIN12_PIN, PIN12_EXTI_IRQn},
  {PIN13_GPIO_PORT, 	PIN13_PIN, PIN13_EXTI_IRQn},
	{PIN14_GPIO_PORT, 	PIN14_PIN, PIN14_EXTI_IRQn},
	{PIN15_GPIO_PORT, 	PIN15_PIN, PIN15_EXTI_IRQn},
	{PIN16_GPIO_PORT, 	PIN16_PIN, PIN16_EXTI_IRQn},
  {PINA0_GPIO_PORT, 	PINA0_PIN, PINA0_EXTI_IRQn},
	{PINA1_GPIO_PORT, 	PINA1_PIN, PINA1_EXTI_IRQn},
	{PINA2_GPIO_PORT, 	PINA2_PIN, PINA2_EXTI_IRQn},
	{PINA3_GPIO_PORT, 	PINA3_PIN, PINA3_EXTI_IRQn},
  {PINA4_GPIO_PORT, 	PINA4_PIN, PINA4_EXTI_IRQn},
	{PINA5_GPIO_PORT, 	PINA5_PIN, PINA5_EXTI_IRQn},
	{PINA6_GPIO_PORT, 	PINA6_PIN, PINA6_EXTI_IRQn},
	{PINA7_GPIO_PORT, 	PINA7_PIN, PINA7_EXTI_IRQn},
  {PINA8_GPIO_PORT, 	PINA8_PIN, PINA8_EXTI_IRQn},
	{PINA9_GPIO_PORT, 	PINA9_PIN, PINA9_EXTI_IRQn},
	{PINA10_GPIO_PORT, 	PINA10_PIN, PINA10_EXTI_IRQn},
	{PINA11_GPIO_PORT, 	PINA11_PIN, PINA11_EXTI_IRQn}
};

__IO voidFuncPtr EXTI_CallBack[numPins];



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/********************************************************************************************/
/******************                 LED FUNCTIONS          **********************************/
/********************************************************************************************/

/**
  * @brief  Configures all LEDs GPIO.
  * @param  None
  * @retval None
  */
void BoardInitialize(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  uint8_t Led;

	/* Enable Clock for GPIO and LEDs */
	ENABLE_BOARD_PIN_CLK();
	
	/* Initialize all LEDs */
  for (Led=0; Led < numLEDs; Led++)
  { 
	  /* Configure the GPIO_LED pin */
		GPIO_InitStructure.Pin = LED_PIN[Led].pin;
		GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStructure.Speed = GPIO_SPEED_MEDIUM;
		GPIO_InitStructure.Pull = GPIO_PULLUP;
		HAL_GPIO_Init(LED_PIN[Led].port, &GPIO_InitStructure);
  }
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDOn(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PIN[Led].port,LED_PIN[Led].pin, GPIO_PIN_SET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDOff(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PIN[Led].port,LED_PIN[Led].pin, GPIO_PIN_RESET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void LEDToggle(Led_TypeDef Led)
{
	HAL_GPIO_TogglePin(LED_PIN[Led].port,LED_PIN[Led].pin);
}


/**
  * @brief  Turns all LEDs On.
  * @param  None
  * @retval None
  */
void LEDOnAll(void)
{
	uint8_t Led;
	  
	for (Led=0; Led < numLEDs; Led++)
	{
		HAL_GPIO_WritePin(LED_PIN[Led].port,LED_PIN[Led].pin, GPIO_PIN_SET);
	}
}

/**
  * @brief  Turns all LEDs Off.
  * @param  None
  * @retval None
  */
void LEDOffAll(void)
{
	uint8_t Led;
	  
	for(Led=0; Led < numLEDs; Led++)
	{
		HAL_GPIO_WritePin(LED_PIN[Led].port,LED_PIN[Led].pin, GPIO_PIN_RESET);
	}
}

/**
  * @brief  Toggle all LEDs.
  * @param  None
  * @retval None
  */
void LEDToggleAll(void)
{
	uint8_t Led;
	  
	for(Led=0; Led < numLEDs; Led++)
	{
		HAL_GPIO_TogglePin(LED_PIN[Led].port,LED_PIN[Led].pin);
	}
}


/********************************************************************************************/
/*****************                 DIGITAL PIN FUNCTIONS          ***************************/
/********************************************************************************************/


/**
  * @brief  Configures GPIO.
  * @param  pinNumber: Specifies the pin to be configured.
  * @param  Mode: Specifies the mode of the specified pin
  *   This parameter can be one of following parameters:
  *     @arg INPUT_PULLUP 			(PullUp Input)
  *     @arg INPUT_PULLDOWN	 		(PullDowm Input)
  *     @arg INPUT_OD				(Floating Input)
  *     @arg OUPUT_PULLUP			(PullUp Output)
  *     @arg OUPUT_PULLDOWN			(PullDown Output)
  *     @arg OUTPUT_OD				(OpenDrain Output)
  * @param  Mode: Specifies how it generates the interrupt:
  * 	@arg EXTI_Trigger_Rising
  * 	@arg EXTI_Trigger_Falling
  * 	@arg EXTI_Trigger_Rising_Falling
	* @param userFunc: Pointer to the callback function
  * @retval None
  */
void PinMode(uint32_t pinNumber, pinMode_Typedef Mode, InterruptEventMode IntEvent, void (*userFunc)(void))
{
	 GPIO_InitTypeDef  GPIO_InitStructure;

	 /* Configure the PIN pin */
	 GPIO_InitStructure.Pin = BOARD_PINS[pinNumber].pin;
	 GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;

	 switch(Mode)
	 {

	 	 case INPUT_PULLUP:
				 GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
				 GPIO_InitStructure.Pull = GPIO_PULLUP;
			break;

	 	 case INPUT_PULLDOWN:
				 GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
				 GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	 		break;

	 	 case INPUT_OD:
				 GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
				 GPIO_InitStructure.Pull = GPIO_NOPULL;
			break;

	 	 case OUTPUT_PULLUP:
				 GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
				 GPIO_InitStructure.Pull = GPIO_PULLUP;
			break;

		 case OUTPUT_PULLDOWN:
				 GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
				 GPIO_InitStructure.Pull = GPIO_PULLDOWN;
			break;

		 case OUTPUT_OD:
				 GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
				 GPIO_InitStructure.Pull = GPIO_NOPULL;
			break;

		 default:
			 break;
	 }
	 
	 /* Attach interrupt if a assigned function exists */
	 if (userFunc != NULL)
	 {
		 	HAL_NVIC_SetPriority((IRQn_Type)BOARD_PINS[pinNumber].IRQExti, BOARD_PIN_PREEMPTION_PRIORITY, BOARD_PIN_SUBPRIORITY + pinNumber);

			HAL_NVIC_EnableIRQ((IRQn_Type)BOARD_PINS[pinNumber].IRQExti);
		 
		  switch(IntEvent)
			{
				case RISING_EDGE:
					GPIO_InitStructure.Mode |= GPIO_MODE_IT_RISING;
					break;
				
				case FALLING_EDGE:
					GPIO_InitStructure.Mode |= GPIO_MODE_IT_FALLING;
					break;
				
				case RISING_FALLING_EDGE:
					GPIO_InitStructure.Mode |= GPIO_MODE_IT_RISING_FALLING;
					break;
				default:
					break;

			}
			
			EXTI_CallBack[pinNumber] = userFunc;
	 }

	 HAL_GPIO_Init(BOARD_PINS[pinNumber].port, &GPIO_InitStructure);
}


/**
  * @brief  Puts selected Output Pin HIGH or LOW.
  * @param  pinNumber: Specifies the pin to be configured.
  * @param  State: Specifies the state of the specified pin
  *   This parameter can be one of following parameters:
  *     @arg HIGH
  *     @arg LOW
  * @retval None
  */
void PinWrite(uint32_t pinNumber, PinState State)
{
	HAL_GPIO_WritePin(BOARD_PINS[pinNumber].port,BOARD_PINS[pinNumber].pin, (GPIO_PinState) State);
}

/**
  * @brief  Returns the selected pin state.
  * @param  pinNumber: Specifies the pin to be read.
  * @retval The GPIO pin value.
  */
PinState PinRead(uint32_t pinNumber)
{
	return (PinState)HAL_GPIO_ReadPin(BOARD_PINS[pinNumber].port,BOARD_PINS[pinNumber].pin);
}

/**
  * @brief  Toggles the selected pin state.
  * @param  pinNumber: Specifies the pin to be read.
  * @retval None.
  */
void PinToggle(uint32_t pinNumber)
{
	HAL_GPIO_TogglePin(BOARD_PINS[pinNumber].port,BOARD_PINS[pinNumber].pin);
}


/* System Clock Configuration */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the
     device is clocked below the maximum system frequency (see datasheet). */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
                                RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

#endif
/**
	*@}
	*/
/**
	*@}
	*/
/**
	*@}
	*/
