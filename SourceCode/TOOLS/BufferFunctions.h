/**
  ******************************************************************************
  * @file    BufferFunctions.h
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
*/

#ifndef BUFFERFUNCTIONS_H_
#define BUFFERFUNCTIONS_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#include "../MBALibrary/MBATypes.h"

#if (RTOS_ACTIVE > 0) && (COOS > 0)
	#include <CoOS.h>
#endif

 /* Exported define ------------------------------------------------------------*/
#define FBUF_EMPTY 	0x01 /*!< Frame buffer is empty */
#define FBUF_NOTEMPTY 	0x00 /*!< Frame buffer is not empty */
#define FBUF_FULL  	0x01 /*!< Frame buffer is full */
#define FBUF_NOTFULL	0x00 /*!< Frame buffer is not full */
#define FC_EMPTY	0x01 /*!< Frame container is empty */
#define FC_NOTEMPTY	0x00 /*!< Frame container is not empty */
#define FC_FULL	 	0x01 /*!< Frame container is full */
#define FC_NOTFULL	0x00 /*!< Frame container is not full */


/* Exported types ------------------------------------------------------------*/
 /**
  * @brief Frame container structure
  */
typedef struct{
  uint32_t size; 	/*!< Container size */
  uint32_t count; 	/*!< Number of elements in container */
  uint32_t start;	/*!< First element index */
  uint8_t *Data;	/*!< Data array pointer */
}FrameContainer;

typedef struct{
  uint32_t size;		/*!< Buffer size */
  uint32_t start;		/*!< Number of container in buffer */
  uint32_t count;		/*!< First container index */
  FrameContainer* DataC;	/*!< Container array pointer */
}FramesBuffer;
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Buffer frames Functions*/
// Basic Functions
uint32_t 	FBufferAlloc			(volatile FramesBuffer *pBuffer, uint32_t Size);
uint32_t 	FBufferFree			(volatile FramesBuffer *pBuffer);
uint32_t 	FBufferRead			(volatile FramesBuffer *pBuffer, uint8_t *pData, uint32_t Size);
uint32_t	FBufferWrite			(volatile FramesBuffer *pBuffer, uint8_t *pData, uint32_t Size);

#define 	IsFBufferFull(pBuffer)	      	(pBuffer.count == pBuffer.size)?FBUF_FULL:FBUF_NOTFULL
#define 	IsFBufferEmpty(pBuffer)	      	(pBuffer.count == 0)?FBUF_EMPTY:FBUF_NOTEMPTY
#define 	FBufferNumData(pBuffer)	      	pBuffer.count
#define 	FBufferSize(pBuffer)		pBuffer.size
#define  	FBufferFirstDataSize(pBuffer) 	FContainerNumData(pBuffer.DataC[pBuffer.start])

// Extended Functions
uint32_t	FBufferToContainer		(volatile FramesBuffer *pBuffer, volatile FrameContainer *pContainer, uint32_t Size);
uint32_t	FBufferFromContainer		(volatile FramesBuffer *pBuffer, volatile FrameContainer *pContainer, uint32_t Size);
uint8_t 	FBufferGetLastIndex		(volatile FramesBuffer *pBuffer);

/* Container frames Fucntions */
//Basic Functions
uint32_t 	FContainerAlloc			(volatile FrameContainer *pContainer, uint32_t Size);
uint32_t 	FContainerFree			(volatile FrameContainer *pContainer);
uint8_t 	FContainerRead			(volatile FrameContainer *pContainer);
uint8_t		FContainerWrite			(volatile FrameContainer *pContainer, uint8_t  Data);

#define 	IsFContainerFull(pContainer)	(pContainer.count == pContainer.size)?FC_FULL:FC_NOTFULL
#define 	IsFContainerEmpty(pContainer)	(pContainer.count == 0)?FC_EMPTY:FC_NOTEMPTY
#define 	FContainerNumData(pContainer)	pContainer.count
#define 	FContainerSize(pContainer)	pContainer.size

// Extended Functions
uint32_t 	FContainerToContainer		(volatile FrameContainer *pDstContainer, volatile FrameContainer *pSrcContainer, uint32_t Size);
uint32_t 	FContainerToArray		(volatile FrameContainer *pContainer, uint8_t *pData, uint32_t Size);
uint32_t	FContainerFromArray		(volatile FrameContainer *pContainer, uint8_t *pData, uint32_t Size);
uint8_t 	FContainerToInt			(volatile FrameContainer *pContainer, uint32_t *Data);
uint8_t		FContainerFromInt		(volatile FrameContainer *pContainer, uint32_t Data);
uint32_t 	FContainerChangeSize		(volatile FrameContainer *pContainer, uint32_t NewSize);
uint8_t 	FContainerDataAtIndex		(volatile FrameContainer *pContainer, uint32_t Index);

/**
 * @}
 */
 /**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* GENERALFUNCTIONS_H_ */
