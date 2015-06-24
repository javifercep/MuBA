/**
  ******************************************************************************
  * @file    BufferFunctions.c
  * @author  Javier Fernández Cepeda
  * @brief   The buffer functions tool helps users to manage Circular FIFO buffers.

  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup Tools
  * @{
  *
  *	@addtogroup Buffer_Tools
  *	@{
  * 		@brief	  Buffer tools
  * 		@details  There are two types of buffers:
  * 		 		- Containers -> Array of bytes (variable size)
  * 		 		- Buffers    -> Array of containers
  * 		 				(each container have is own size)
*/

/* Includes ------------------------------------------------------------------*/
#include "BufferFunctions.h"
#include "./MemoryManagement.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**************************************************************************************************/
/*************************            FRAMES BUFFER            ************************************/
/**************************************************************************************************/

/******* BASIC FUNCTIONS **************************************************************************/
/**
  * @brief  Initializes frames buffer.
  * @param[in]  pBuffer: pointer on the frames buffer
  * @param[in]  Size: size of the frames buffer
  * @retval Returns the size of the buffer
  */

uint32_t FBufferAlloc (volatile FramesBuffer *pBuffer, uint32_t Size)
{
  pBuffer->size	 = 0;
  pBuffer->start = 0;
  pBuffer->count = 0;
  pBuffer->DataC = (FrameContainer*)MemAlloc(Size*sizeof(FrameContainer));

  if(pBuffer->DataC != NULL)
  {
	pBuffer->size	= Size;
  }
  return pBuffer->size;
}


/**
  * @brief  	Frees memory.
  * @param[in]  pBuffer: pointer on the frames buffer
  * @retval 	Freed size
  */
uint32_t FBufferFree (volatile FramesBuffer *pBuffer)
{
    uint32_t SizeTemp = pBuffer->size, ii;

    for(ii = 0; ii < pBuffer->count; ii++)
    {
	FContainerFree(&(pBuffer->DataC[(pBuffer->start + ii) % pBuffer->size]));
    }
    MemFree(pBuffer->DataC);
    pBuffer->DataC = NULL;
    pBuffer->size = 0;
    pBuffer->start = 0;
    pBuffer->count = 0;

    return SizeTemp;
}


/**
  * @brief  Reads first Buffer's position.
  * @param[in]   pBuffer: pointer on the frames buffer
  * @param[out]  pData: pointer on destination buffer
  * @param[in]	 Size: size of frame vector
  * @retval Size of returned data
  */
uint32_t FBufferRead (volatile FramesBuffer *pBuffer, uint8_t *pData, uint32_t Size)
{
    uint32_t SizeTemp;
    uint8_t *pTemp = pData;

    FContainerToArray(&(pBuffer->DataC[pBuffer->start]), pTemp, Size);
    SizeTemp = FContainerFree(&(pBuffer->DataC[pBuffer->start]));

    pBuffer->start=(pBuffer->start + 1) % pBuffer->size; //update start pointer
    pBuffer->count--;
    //Update data count
    /*Frees memory reserved during write function*/
    return SizeTemp;
}

/**
  * @brief  Writes in the last position of frames buffer.
  * @param[out] pBuffer: pointer on the frames buffer
  * @param[in]  pData: pointer on source data
  * @param[in]	Size: size of frame vector
  * @retval 	Written data
  */
uint32_t FBufferWrite (volatile FramesBuffer *pBuffer, uint8_t *pData, uint32_t Size)
{
    uint32_t WrittenData = 0;
    FrameContainer *pConTemp;
    uint8_t *pTemp = pData;

    int end = (pBuffer->start + pBuffer->count) % pBuffer->size;

    pConTemp = &(pBuffer->DataC[end]);

    /*Reserves memory to save pData vector*/
    if(FContainerAlloc(pConTemp, Size) == Size)
    {
	WrittenData = FContainerFromArray (pConTemp, pTemp, Size);

	/*OVERWRITE SUPPORTED*/
	if(pBuffer->count == pBuffer->size)
	{
	    pBuffer->start=(pBuffer->start + 1) % pBuffer->size;
	}
	else
	{
	    pBuffer->count++;
	}
    }

    return WrittenData;
}


/******* EXTENDED FUNCTIONS ***********************************************************************/

/**
  * @brief  Reads first Buffer's position to FrameContainer.
  * @param[in]  pBuffer: pointer on the frames buffer
  * @param[out] pContainer: pointer on empty frame container
  * @param[in]  Size: size of the data to be copied
  * @retval 	Written data in the container
  * @note   	After call this function, check that all the desired data has been read. This function frees
  * 	    	the container data of the buffer, so is not possible to recover the data if an errors occurs.
  */
uint32_t FBufferToContainer(volatile FramesBuffer *pBuffer, volatile FrameContainer *pContainer, uint32_t Size)
{
  uint32_t WrittenData;

  WrittenData = FContainerToContainer(pContainer, &(pBuffer->DataC[pBuffer->start]), Size);

  /*Frees memory reserved during write function*/
  FContainerFree(&(pBuffer->DataC[pBuffer->start]));

  pBuffer->start=(pBuffer->start + 1) % pBuffer->size; //update start pointer
  pBuffer->count--;									 //Update data count

  return WrittenData;
}

/**
  * @brief  Writes in the last position of circular buffer from a FrameContainer(Struct).
  * @param[out] pBuffer: pointer on the frames buffer
  * @param[in]  pContainer: pointer on empty frame container
  * @param[in]  Size: size of the data to be copied
  * @retval 	Written data in the container of the buffer
  */
uint32_t FBufferFromContainer (volatile FramesBuffer *pBuffer, volatile FrameContainer *pContainer, uint32_t Size)
{
    uint32_t end = (pBuffer->start + pBuffer->count) % pBuffer->size;
    uint32_t WrittenData = 0;

    /*Reserves memory to save pContainer vector*/
    if(FContainerAlloc(&(pBuffer->DataC[end]),Size) == FUNC_OK)
    {
	WrittenData = FContainerToContainer(&(pBuffer->DataC[end]), pContainer, Size);
	/*OVERWRITE SUPPORTED*/
	if(pBuffer->count == pBuffer->size)
	  {
	      pBuffer->start=(pBuffer->start + 1) % pBuffer->size;
	  }

	else
	  {
	      pBuffer->count++;
	  }
    }

    return WrittenData;
}

/**
  * @brief  	Returns the position of the new data to write.
  * @param[in]  pBuffer: pointer on the frames buffer
  * @retval 	last available position
  */
uint8_t FBufferGetLastIndex (volatile FramesBuffer *pBuffer)
{
    return ((pBuffer->start + pBuffer->count) % pBuffer->size);
}


/**************************************************************************************************/
/*************************            FRAME CONTAINER          ************************************/
/**************************************************************************************************/

/******* BASIC FUNCTIONS **************************************************************************/
/**
  * @brief  	Initializes frame container.
  * @param[in]  pContainer: pointer on the frame Container
  * @param[in]  Size: size of the frame Container
  * @retval Allocated size
  */
uint32_t FContainerAlloc (volatile FrameContainer *pContainer, uint32_t Size)
{
    pContainer->size 	= 0;
    pContainer->count 	= 0;
    pContainer->start 	= 0;

    pContainer->Data = (uint8_t*)MemAlloc(sizeof(uint8_t)*Size);

    if(pContainer->Data != NULL)
    {
	pContainer->size = Size;
    }
    return pContainer->size;
}


/**
  * @brief     Frees memory.
  * @param[in] pContainer: pointer on the frame Container
  * @retval    Freed size
  */
uint32_t FContainerFree (volatile FrameContainer *pContainer)
{
  uint32_t SizeTemp = pContainer->size;

  MemFree(pContainer->Data);
  pContainer->Data = NULL;
  pContainer->size = 0;
  pContainer->start = 0;
  pContainer->count = 0;

  return SizeTemp;
}

/**
  * @brief  Reads first Container's position.
  * @param[in]  pContainer: pointer on the frame Container
  * @retval 	data
  */
uint8_t FContainerRead (volatile FrameContainer *pContainer)
{
  uint8_t temp;

  temp = pContainer->Data[pContainer->start]; 				 //get oldest data in the Container
  pContainer->start=(pContainer->start + 1) % pContainer->size; //update start pointer
  pContainer->count--;							//Update data count

  return temp;
}


/**
  * @brief  Writes in the last position of frame Container.
  * @param[in]  pContainer: pointer on the frame Container
  * @param[in]  Data: data to frame Container
  * @retval 	FUNC_OK if data has been written correctly
  * 		FUNC_KO if an overwrite has occurred
  */
uint8_t FContainerWrite (volatile FrameContainer *pContainer, uint8_t Data)
{
    uint32_t end = (pContainer->start + pContainer->count) % pContainer->size;
    uint8_t isWrittenCorrectly = FUNC_OK;

    pContainer->Data[end] = Data;

    /*OVERWRITE SUPPORTED*/
    if(pContainer->count == pContainer->size)
    {
	pContainer->start=(pContainer->start + 1) % pContainer->size;
	isWrittenCorrectly = FUNC_KO;
    }
    else
    {
	pContainer->count++;
    }

    return isWrittenCorrectly;
}



/******* EXTENDED FUNCTIONS ***********************************************************************/

/**
  * @brief  Copy the data of the source container into the data of the destination container.
  * @param[out]  pDstContainer: pointer to the destination Container
  * @param[in]	 pSrcContainer:	pointer to the source Container
  * @param[in]	 Size:	size of data to be copied
  * @retval 	 Number of copied data
  * @note	 OVERWRITE is not supported in this function.
  */
uint32_t FContainerToContainer	(volatile FrameContainer *pDstContainer, volatile FrameContainer *pSrcContainer, uint32_t Size)
{
    uint32_t end = (pDstContainer->start + pDstContainer->count) % pDstContainer->size;
    uint32_t CopiedData, ii;
    if((Size <= pDstContainer->size) && (Size <= pSrcContainer->size))
    {
	CopiedData = Size;
    }
    else if(pDstContainer->size >= pSrcContainer->size)
    {
	CopiedData = pSrcContainer->size;
    }
    else
    {
	CopiedData = pDstContainer->size;
    }

    for (ii = 0; ii < CopiedData; ii++)
    {
	pDstContainer->Data[end] = pSrcContainer->Data[pSrcContainer->start];

	/* Update the start pointer of the source container */
	pSrcContainer->start=(pSrcContainer->start + 1) % pSrcContainer->size;

	/* Update the end pointer of the destination container */
	end = (end + 1) % pDstContainer->size;
    }

    /* Update the count of both containers */
    pSrcContainer->count -= CopiedData;
    pDstContainer->count += CopiedData;

    return CopiedData;
}

/**
  * @brief  	 Copy the first Size bytes of a Container to an Array.
  * @param[in]   pContainer: pointer on the frame Container
  * @param[out]  pData:	pointer to destination array
  * @param[in]   Size:	size of data to be copied
  * @retval 	 Number of copied data
  */
uint32_t FContainerToArray (volatile FrameContainer *pContainer, uint8_t *pData, uint32_t Size)
{
    uint32_t CopiedData, ii;
    if(Size < pContainer->count)
    {
	CopiedData = Size;
    }
    else
    {
	CopiedData = pContainer->count;
    }
    for(ii = 0; ii < CopiedData; ii++)
    {
	pData[ii] = pContainer->Data[pContainer->start]; //get oldest data in the Container
	pContainer->start=(pContainer->start + 1) % pContainer->size; //update start pointer
    }
    pContainer->count -= CopiedData;	//Update data count

    return CopiedData;
}


/**
  * @brief  Copy the first Size bytes of an Array to a Container.
  * @param[out]  pContainer: pointer on the frame Container
  * @param[in]   pData:	pointer to destination array
  * @param[in]   Size:	size of data to be copied
  * @retval 	Number of copied data
  * @note   	OVERWRITE is not supported in this function. Use FContainerWrite instead.
  */

uint32_t FContainerFromArray (volatile FrameContainer *pContainer, uint8_t *pData, uint32_t Size)
{
    uint32_t end = (pContainer->start + pContainer->count) % pContainer->size;
    uint32_t CopiedData, ii;

    if(Size < pContainer->size - pContainer->count)
    {
	CopiedData = Size;
    }
    else
    {
	CopiedData = pContainer->size - pContainer->count;
    }
    for(ii = 0; ii < CopiedData; ii++)
    {
	pContainer->Data[end] = pData[ii];
	end = (end + 1) % pContainer->size;
    }

    pContainer->count += CopiedData;

    return CopiedData;

}

/**
  * @brief  Reads first Container's position.
  * @param[in]  pContainer: pointer on the frame Container
  * @param[out] data integer output
  * @retval 	FUNC_OK if the integer has been copied correctly
  * 	    	FUNC_KO otherwise
  */
uint8_t FContainerToInt (volatile FrameContainer *pContainer, uint32_t *Data )
{
    uint8_t ii, ret = FUNC_OK;

    if(pContainer->count >= 4)
    {
	for(ii=0; ii<4; ii++)
	{
	    *Data |= (FContainerRead(pContainer)) << (8*(3-ii));
	}
    }
    return ret;
}

/**
  * @brief  Writes in the last position of frame Container more than single data at once.
  * @param[in] 	pContainer: pointer on the frame Container
  * @param[in]  data: integer to write on container
  * @retval 	FUNC_OK if the integer has been copied correctly,
  * 	   	 FUNC_KO otherwise
  */
uint8_t FContainerFromInt (volatile FrameContainer *pContainer, uint32_t Data)
{
    uint8_t i, ret = FUNC_OK;

    if(pContainer->size >= 4)
    {
	for(i=0; i<4; i++)
	{
	    if(pContainer->count != pContainer->size)
	    {
		FContainerWrite(pContainer,((Data >> 8*(3-i))&0xFF));
	    }
	    else
	    {
		ret = FUNC_KO;
		break;
	    }
	}
    }
    return ret;
}

/**
  * @brief  Change the container size.
  * @param[in]  pContainer: pointer on the Container
  * @param[in]	NewSize: new buffer size
  * @retval New allocated size
  */
uint32_t FContainerChangeSize (volatile FrameContainer *pContainer, uint32_t NewSize)
{
    uint8_t *tempBuf;
    uint32_t currentDataSize, newAllocatedSize;

    currentDataSize = pContainer->count;
    /* Create a temporal buffer to save the current data */
    tempBuf = (uint8_t*)MemAlloc(sizeof(uint8_t)*currentDataSize);

    if(tempBuf == NULL)
    {
	    newAllocatedSize = pContainer->size;
	    goto Exit;
    }
    /* Copy the current data to the temportal buffer */
    FContainerToArray (pContainer, tempBuf, currentDataSize);
    /* Frees the container before re-allocate it*/
    FContainerFree(pContainer);

    /* Alloc new size memory */
    if(FContainerAlloc (pContainer, NewSize) == NewSize)
    {
	    newAllocatedSize = 0;
	    goto Exit;
    }

    newAllocatedSize = NewSize;
    FContainerFromArray(pContainer, tempBuf, currentDataSize);

    Exit:	MemFree(tempBuf);

    return newAllocatedSize;
}

/**
  * @brief  Return the container value at index position.
  * @param[in]  pContainer: pointer on the Container
  * @param[in]  index: position of the desired data
  * @retval Internal index bufer position of the desired input index
  * @note   This function doens't remove the data from the container
  */
uint8_t FContainerDataAtIndex (volatile FrameContainer *pContainer, uint32_t index)
{
  return pContainer->Data[(pContainer->start + index) % pContainer->size]; //update start pointer
}

/**
 * @}
 */
/**
 * @}
 */
