/**
  ******************************************************************************
  * @file    MBAConfigProtocol.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA configuration protocol functions 
  *    	     for upper layers
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
  *	@addtogroup MBA_Configuration_Protocol
  *	@{
  *		@brief	 The configuration protocol is the responsible of manage the
  *						 device dictionary.
  *		@details
*/

/* Includes ------------------------------------------------------------------*/
#include "MBAConfigProtocol.h"
#include "../MBADictionary/MBADictionary.h"
#include "../../TOOLS/MemoryManagement.h"

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief Configuration protocol struct. It is used to process data if a
  *	   configuration protocol frame has been sent by some device.
  */

typedef struct
{
    uint16_t  	RegisterID; /*!< ID of the regiter to be written/read*/
    uint8_t 	TypeAccess; /*!< Type of data & access */
    uint8_t	*Data;      /*!< Data to be written / read */
}ConfigProtFrame;

/* Private define ------------------------------------------------------------*/
/* Config cast masks */
#define DIR_MASK	0x01 /*!< Cast direction */

/*Config cast modes */
#define CONFIG_FROM_BUFF	0	/*!< Cast direction */
#define CONFIG_TO_BUFF		1	/*!< Cast direction */


#define CONFIG_FRAME_HEADER	3 /*!< Configuration frame size */

/* Config frame field index */
#define REGID_LOW_INDEX		0 /*!< Register id low byte buffer index */
#define REGID_HIGH_INDEX	1 /*!< Register id high byte buffer index */
#define TYPEACCESS_INDEX	2 /*!< Type & access buffer index */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
ConfigProtRet ConfigFrameCast(ConfigProtFrame *CPFrame, uint8_t *pBuf, uint32_t Size, uint8_t Mode);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Configuration protocol main routine.
  * @details Takes data from a transfer protocol frame, cast it to a configuration
  *   	     protocol frame and process it. 4 kind of operations are available:
  *		- Read operation: Reads data from any readable register
  *		- Write operation: Writes data into any writable register
  *		- Read information: Reads information about a register (Size,
  *		  description, access and data type)
  *		- Write information: Not implemented
  * @param[out]	ConfigProtFrameOut Buffer to write the operation result
  * @param[in]  ConfigProtFrameIn Buffer where the configuration frame is.
  * @param[in]	InputSize Number of bytes of the input buffer
  * @retval 	Size of the output buffer
  */
uint32_t ConfigProtocolProcess(uint8_t **ConfigProtFrameOut, uint8_t *ConfigProtFrameIn, uint32_t InputSize)
{
    ObjectRet ret;
    ConfigProtFrame ObjectFrame;
    uint8_t *DataIn = ConfigProtFrameIn;
    uint8_t *DataOut, *DataObject;
    uint32_t ObjectSize;

    /* A ObjectFrame is created from DataIn*/
    ConfigFrameCast(&ObjectFrame, DataIn, InputSize, CONFIG_FROM_BUFF);
    ObjectSize = InputSize - CONFIG_FRAME_HEADER;

    /* Copy data to be written into the register */
    DataObject = ObjectFrame.Data;

    /* Checks if the requested register exists */
    ret = CheckObjectInDictionary(ObjectFrame.RegisterID);

    if(ret == OBJECT_FOUND)
    {
      /* Process the requested operation: read, write, read info or write info */
      ret = ProcessObject(ObjectFrame.RegisterID, &(ObjectFrame.TypeAccess), &ObjectSize, &(DataObject));
      
      /* If the requested operation has been executed successfully, create the reply message */
      if (ret == OBJECT_SUCCESS)
      {
          ObjectFrame.Data = DataObject;
          DataOut = (uint8_t *)MemAlloc(ObjectSize + CONFIG_FRAME_HEADER);

          /* A ObjectFrame is destroyed and copied to DataOut */
          ConfigFrameCast(&ObjectFrame, DataOut, ObjectSize, CONFIG_TO_BUFF);
          *ConfigProtFrameOut = DataOut;
          ObjectSize += CONFIG_FRAME_HEADER;
      }
    }

    return ObjectSize;
}

/*********************************************************************************************/
/*****		   STATIC FUNCTIONS		    **********************************************************/
/*********************************************************************************************/
/**
  * @brief  Casts standard buffers into Config protocol frames and vice versa
  * @details The transfer protocol data field is read as standard buffer. This function
  *	     translates this buffer into a config frame to process it.
  * @param[in,out]  CPFrame:	Config protocol frame to be processed. Could be the source or
  *				the destination buffer in function of the Mode value.
  * @param[in,out]  pBuf:	Standard buffer to be processed. Could be the source or
  *				the destination buffer in function of the Mode value.
  * @param[in]			Size: Number of bytes to be casted
  * @param[in]  		Mode: Cast parameters: Direction and cast mode
  * @retval 			CP_SUCCESS if the cast has been executed correctly, CP_ERROR otherwise
  */
ConfigProtRet ConfigFrameCast(ConfigProtFrame *CPFrame, uint8_t *pBuf, uint32_t Size, uint8_t Mode)
{
    ConfigProtFrame *CPTemp = CPFrame;	/* Temporal pointer for data processing */
    uint8_t	    *pBufTemp;							/* Temporal pointer for data processing */
    ConfigProtRet   ret = CP_SUCCESS;

    /* If the standard buffer is the input and the Config frame the output: */
    if((Mode & DIR_MASK) == CONFIG_FROM_BUFF)
    {
	/* pTemp is used to point into different areas of the input standard buffer */
	pBufTemp = pBuf;

	/* Register ID */
	CPTemp->RegisterID = (uint16_t)(pBuf[REGID_LOW_INDEX] & WORD_LOW_MASK);
	CPTemp->RegisterID |= (uint16_t)((pBuf[REGID_HIGH_INDEX] << BYTE_SHIFT) & WORD_HIGH_MASK);
	/* Access and data type */
	CPTemp->TypeAccess = pBuf[TYPEACCESS_INDEX];

	/* point pTemp to the config protocol data field */
	pBufTemp += CONFIG_FRAME_HEADER;
	
	/* Copy data field (if exists) into config frame struct */
	CPTemp->Data = (uint8_t*)MemAlloc(Size - CONFIG_FRAME_HEADER);
	if(CPTemp->Data != NULL)
	{
	    memcpy(CPTemp->Data, pBufTemp, Size - CONFIG_FRAME_HEADER);
	}
	else
	{
	    ret = CP_ERROR;
	}
    }
    else
    {
	/* Allocate memory for output buffer and copy data from config frame*/
	pBufTemp = pBuf;
	
	if(pBufTemp != NULL)
	{
	  /* Copy config protocol header */
	  //memcpy(pTemp, CPTemp, CONFIG_FRAME_HEADER);
	  pBufTemp[REGID_LOW_INDEX] = (uint8_t)(CPTemp->RegisterID & WORD_LOW_MASK);
	  pBufTemp[REGID_HIGH_INDEX] = (uint8_t)((CPTemp->RegisterID >> BYTE_SHIFT) & WORD_LOW_MASK);
	  pBufTemp[TYPEACCESS_INDEX] = CPTemp->TypeAccess;
	  /* Point pTemp to the config protocol data field */
	  pBufTemp += CONFIG_FRAME_HEADER;
	  /* Copy data field */
	  memcpy(pBufTemp, CPTemp->Data, Size);
	}
	else
	{
	    ret = CP_ERROR;
	}
	if(CPTemp->Data != NULL)
	{
	  /* Free the allocated memory for ConfigFrame */
	  MemFree(CPTemp->Data);
	  CPTemp->Data = NULL;
	}
    }

    return ret;
}

/**
  *@}
  */
/**
  *@}
  */
/**
  *@}
  */

