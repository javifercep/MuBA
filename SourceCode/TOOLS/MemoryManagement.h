/**
  ******************************************************************************
  * @file    MemoryManagement.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains constants definitions which help users to manage
  * 	     dinamic memory
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup Tools
  * @{
  *
  *	@addtogroup Memory_Tools
  *	@{
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MEMORYMANAGEMENT_H
#define __MEMORYMANAGEMENT_H

#ifdef __cplusplus
 extern "C" {
#endif

/*Includes ------------------------------------------------------------------*/

/* Types includes*/
#include "SysConfig.h"
#if MCU_STM32F4XX > 0
  #include "stm32f4xx.h"
#endif

#if ARMCC_COMPILER > 0
  #include <stdlib.h>
  #include <string.h>
#else
  #include <malloc.h>
  #include <stdlib.h>
  #include <string.h>
  #include <stdint.h>
#endif

/*Other includes*/

/* Exported define ------------------------------------------------------------*/
#if DINAMIC_MEMORY_CONTROL > 0
#define FREEBLOCKNUM		0	/*!< Size */
#define DEFAULTFREEBLOCKSIZE	200	/*!< Size */

#define SPIBLOCKNUM		1	/*!< Size */
#define DEFAULTSPIBLOCKSIZE	200	/*!< Size */



/* Exported types ------------------------------------------------------------*/
 typedef struct
 {
	 uint16_t MaxStackSize;
	 uint16_t CurrentUsedStack;
	 uint16_t BlockNum;
	 uint8_t  isFreeBlockUsed;
	 uint16_t DataInFreeBlock;
 }LocalMemoryControlStack;

 typedef struct
 {
	 uint16_t NumBlocks;
	 uint32_t TotalStackSize;
	 uint32_t CurrentTotalStackSize;
	 uint32_t TotalBlocksSize;
 }GlobalMemoryControlStack;

 typedef enum
 {
	 GLOBAL_STACK_CORRUPTED = -2,
	 LOCAL_STACK_CORRUPTED = -1,
	 RET_SUCCESS = 0,
	 GLOBAL_STACK_FULL,
	 LOCAL_STACK_FULL,
	 FREEBLOCK_FULL,
	 NOT_ENOUGH_SPACE
 }MemManageRetValue;
#endif


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* This macros are used to unify all the malloc functions for each compiler*/
#if ARMCC_COMPILER > 0
#define MemAlloc				malloc
#define MemFree					free
#define MemRealloc				realloc
#else
#define MemAlloc				malloc
#define MemFree					free
#define MemRealloc				realloc
#endif

#if DINAMIC_MEMORY_CONTROL > 0
/* Local memory management macro*/
#define GetLocalStackMaxSize(MemStack)		MemStack.MaxStackSize
#define GetCurrentUsedStack(MemStack)		MemStack.CurrentUsedStack
#define GetBLocksUsedStack(MemStack)		MemStack.TotalBlocksSize
#define GetBlockNum(MemStack)			MemStack.BlockNum

#define SetLocalStackMaxSize(MemStack, Size)	MemStack.MaxStackSize = Size
#define SetCurrentUsedStack(MemStack, Size) 	MemStack.CurrentUsedStack = Size
#define SetBLocksUsedStack(MemStack, Size)	MemStack.TotalBlocksSize = Size
#define SetBlockNum(MemStack, Num)	 	MemStack.BlockNum = Num

/* Global memory management macro*/
#define GetGlobalStackMaxSize(MemStack)		MemStack.TotalStackSize
#define GetCurrentTotalUsedStack(MemStack)	MemStack.CurrentTotalStackSize
#define GetNumBlocks(MemStack)			MemStack.NumBlocks

#define SetGlobalStackMaxSize(MemStack, Size)	MemStack.TotalStackSize = Size
#define SetCurrentTotalUsedStack(MemStack, Size)MemStack.CurrentTotalStackSize = Size
#define SetNumBlocks(MemStack, Num)		MemStack.NumBlocks = Num

/* Exported functions ------------------------------------------------------- */
/* Global Memory Management functions */
void MemoryManagementInit		(uint32_t Size);
void MemoryManagementDeInit		(void);

MemManageRetValue	MMAddBlock	(volatile LocalMemoryControlStack *MemMan, uint16_t blockNum, uint32_t MaxSize);
int32_t 		MMRemoveBlock	(volatile LocalMemoryControlStack *MemMan);

/* Local Memory Management function */
MemManageRetValue 	MMAddData 	(volatile LocalMemoryControlStack *MemMan, uint32_t Size);
MemManageRetValue	MMRemoveData	(volatile LocalMemoryControlStack *MemMan, uint32_t Size);
#endif

/**
 * @}
 */
/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif
#endif /* __MEMORYMANAGEMENT_H */
