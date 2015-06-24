/**
  ******************************************************************************
  * @file    MBATypes.h
  * @author  Javier Fernández Cepeda
  * @brief   This file defines useful types.
  *
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup MBA
  * @{
  *
  *	@addtogroup MBA_Library
  *	@{
  *
  *	@addtogroup MBA_Types
  *	@{
  *		@brief Common types for the whole MBA library.
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MBATYPES_H
#define __MBATYPES_H

#ifdef __cplusplus
 extern "C" {
#endif 

 /* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include <stdint.h>
/* HW dependent types: it must be filtered in function of the architecture used */
#if MCU_STM32F4XX > 0
#include "stm32f4xx.h"
#endif
/* Exported define ------------------------------------------------------------*/
/* Operation defines */
#define BYTE_SHIFT	8
#define WORD_SHIFT	16
#define DWORD_24_SHIFT  24
#define DWORD_SHIFT	32

#define WORD_LOW_MASK   0x00FF
#define WORD_HIGH_MASK	0xFF00

#define DWORD_0_BYTE_MASK 0x000000FF
#define DWORD_1_BYTE_MASK 0x0000FF00
#define DWORD_2_BYTE_MASK 0x00FF0000
#define DWORD_3_BYTE_MASK 0xFF000000


 /* Exported types ------------------------------------------------------------*/

typedef void (*voidFuncPtr)(void);

typedef enum
{
  FUNC_KO = 0,
  FUNC_OK = 1,
} Function_Status;

typedef enum
{
  FALSE = 0,
  TRUE = 1,
}Bolean_State;

typedef enum
{
  DISABLED = 0,
  ENABLED = 1,
}SystemTest_State;

 /* Exported constants --------------------------------------------------------*/
 /* Exported macro ------------------------------------------------------------*/
 /* Exported functions ------------------------------------------------------- */

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

#endif /* __MBATYPES_H */
