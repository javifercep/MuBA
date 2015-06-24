/**
  ******************************************************************************
  * @file    MemoryManagement.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains functions descriptions which help users to manage
  * 	     dynamic memory.
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

/* Includes ------------------------------------------------------------------*/
#if DINAMIC_MEMORY_CONTROL > 0
#include "MBALibrary/MBATypes.h"
#include "PHDLLAYER/BUSAPI/USBAPI.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define isGlobalMemManageFull(GlobalMemManage) (GlobalMemManage.CurrentTotalStackSize\
											   > GlobalMemManage.TotalStackSize)
#define isGlobalMemManagerCorrupted(GlobalMemManage) (GlobalMemManage.TotalBlocksSize < 0)
#define isGlobalMemManageFullofBlocks(GlobalMemManage) (GlobalMemManage.TotalBlocksSize\
											   > GlobalMemManage.TotalStackSize)
/* Private variables ---------------------------------------------------------*/
static volatile GlobalMemoryControlStack GlobalMemManage;
static volatile LocalMemoryControlStack	FreeBlock;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static MemManageRetValue AddFreeBlockManager(volatile LocalMemoryControlStack *MemMan);
static MemManageRetValue RemoveFreeBlockManager(volatile LocalMemoryControlStack *MemMan, uint32_t Size);


/* Global Memory Management functions */

/**
* @brief  This function initializes Memory Management Tool
* @param  Size: Size of the total stack
* @retval None
*/
void MemoryManagementInit(uint32_t Size)
{
	SetGlobalStackMaxSize(GlobalMemManage, Size);
	SetCurrentTotalUsedStack(GlobalMemManage, 0);
	SetBLocksUsedStack(GlobalMemManage, 0);
	if(MMAddBlock(&FreeBlock,FREEBLOCKNUM, DEFAULTFREEBLOCKSIZE) != RET_SUCCESS)
	{
		if(isUSBDebugActive)
		{
			USBSendDebug("FreeBlock can't be allocated\n");
		}
	}
}

/**
* @brief  This function deinitializes Memory Management Tool
* @param  None
* @retval None
*/
void MemoryManagementDeInit(void)
{
	SetGlobalStackMaxSize(GlobalMemManage, 0);
	SetCurrentTotalUsedStack(GlobalMemManage, 0);
	SetBLocksUsedStack(GlobalMemManage, DEFAULTFREEBLOCKSIZE);
	SetNumBlocks  (GlobalMemManage, 1);
	MMRemoveBlock (&FreeBlock);
}

/**
* @brief  This function add a new block memory in the global memory manager
* @param  MemMan: 	Local memory manager handler
* @param  blockNum: ID of the new block
* @param  MaxSize: Maximum size of this block
* @retval SUCCESS if the block is added correctly, MemManage ERROR otherwise
*/
MemManageRetValue	MMAddBlock		(volatile LocalMemoryControlStack *MemMan, uint16_t blockNum, uint32_t MaxSize)
{
	MemManageRetValue ret = RET_SUCCESS;
	GlobalMemManage.TotalBlocksSize += MaxSize;
	if(!isGlobalMemManageFullofBlocks(GlobalMemManage))
	{
		GlobalMemManage.NumBlocks++;
		MemMan->MaxStackSize = MaxSize;
		MemMan->BlockNum = blockNum;
		MemMan->CurrentUsedStack = 0;
		MemMan->isFreeBlockUsed = 0;
	}
	else
	{
		ret = GLOBAL_STACK_FULL;
		if(isUSBDebugActive)
		{
			USBSendDebug("A block can't be allocated\n");
		}
	}
	return ret;
}

/**
* @brief  This function remove a block memory from the global memory manager
* @param  MemMan: 	Local memory manager handler
* @retval Size of the removed block
*/
int32_t MMRemoveBlock(volatile LocalMemoryControlStack *MemMan)
{
	uint16_t ret = MemMan->MaxStackSize;

	GlobalMemManage.TotalBlocksSize -= ret;
	if(!isGlobalMemManagerCorrupted(GlobalMemManage))
	{
		GlobalMemManage.NumBlocks--;
		MemMan->MaxStackSize = 0;
		MemMan->CurrentUsedStack = 0;
		MemMan->BlockNum = 0;
		MemMan->isFreeBlockUsed = 0;
	}
	else
	{
		GlobalMemManage.TotalBlocksSize += ret;
		ret = GLOBAL_STACK_CORRUPTED;
		if(isUSBDebugActive)
		{
			USBSendDebug("Stack is corrupted\n");
		}
	}
	return ret;
}

/* Local Memory Management function */
/**
* @brief  This function add data to the local memory
* @param  MemMan: 	Local memory manager handler
* @param  Size:		Size of data
* @retval SUCCESS if data can be saved, error otherwise
*/
MemManageRetValue 	MMAddData  (volatile LocalMemoryControlStack *MemMan, uint32_t Size)
{
	MemManageRetValue ret = RET_SUCCESS;

	MemMan->CurrentUsedStack += Size;
	if(MemMan->CurrentUsedStack > MemMan->MaxStackSize)
	{
		ret = AddFreeBlockManager(MemMan);
		if(isUSBDebugActive)
		{
			USBSendDebug("Data is added to FreeBlock\n");
		}
	}
	else
	{
		GlobalMemManage.CurrentTotalStackSize += Size;
	}
	return ret;

}

/**
* @brief  This function remove data from the local memory
* @param  MemMan: 	Local memory manager handler
* @param  Size:		Size of data
* @retval SUCCESS if data can be removed, error otherwise
*/
MemManageRetValue	MMRemoveData	(volatile LocalMemoryControlStack *MemMan, uint32_t Size)
{
	MemManageRetValue ret = RET_SUCCESS;

	MemMan->CurrentUsedStack -= Size;
	if(MemMan->CurrentUsedStack < 0)
	{
		MemMan->CurrentUsedStack += Size;
		ret = LOCAL_STACK_CORRUPTED;
	}
	else
	{
		if(MemMan->isFreeBlockUsed == TRUE)
		{
			ret = RemoveFreeBlockManager(MemMan, Size);
			USBSendDebug("Data is removed from FreeBlock\n");
		}
		GlobalMemManage.CurrentTotalStackSize -= Size;
	}
	return ret;
}

/**
* @brief  This function manages the free block if a local block exceeds its stack size
* @param  MemMan: 	Local memory manager handler
* @retval SUCCESS if the FreeBlock can manage the extra data, ERROR otherwise
*/
static MemManageRetValue AddFreeBlockManager(volatile LocalMemoryControlStack *MemMan)
{
	MemManageRetValue ret = RET_SUCCESS;
	uint16_t SizeToSave = MemMan->CurrentUsedStack - MemMan->MaxStackSize;

	if(SizeToSave < (FreeBlock.CurrentUsedStack - FreeBlock.MaxStackSize))
	{
		FreeBlock.CurrentUsedStack += SizeToSave;
		GlobalMemManage.CurrentTotalStackSize += SizeToSave;
		MemMan->DataInFreeBlock = SizeToSave;
		MemMan->isFreeBlockUsed = TRUE;
	}
	else
	{
		if(FreeBlock.CurrentUsedStack > FreeBlock.MaxStackSize)
		{
			GlobalMemManage.CurrentTotalStackSize += SizeToSave;
			if(isGlobalMemManageFull(GlobalMemManage))
			{
				ret = GLOBAL_STACK_FULL;
			}
			else
			{
				ret = FREEBLOCK_FULL;
			}
			GlobalMemManage.CurrentTotalStackSize -= SizeToSave;
		}
		else
		{
			ret = NOT_ENOUGH_SPACE;
		}
	}
	return ret;
}

/**
* @brief  This function manages the free block if a local block is using this block and
* 		  frees data.
* @param  MemMan: 	Local memory manager handler
* @retval SUCCESS if the FreeBlock can manage the extra data, ERROR otherwise
*/
static MemManageRetValue RemoveFreeBlockManager(volatile LocalMemoryControlStack *MemMan, uint32_t Size)
{
	MemManageRetValue ret = RET_SUCCESS;

	FreeBlock.CurrentUsedStack -= MemMan->DataInFreeBlock;
	if(Size >= MemMan->DataInFreeBlock)
	{
		MemMan->DataInFreeBlock = 0;
		MemMan->isFreeBlockUsed = FALSE;
	}
	else
	{
		MemMan->DataInFreeBlock -= Size;
	}
	return ret;
}
#endif
/**
 * @}
 */
/**
 * @}
 */

