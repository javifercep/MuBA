/**
  ******************************************************************************
  * @file    MBADictionary.h
  * @author  Javier Fernández Cepeda
  * @brief   Configuration registers for the communication settings
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
  *	@addtogroup MBA_Dictionary
  *	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MBADICTIONARY_H
#define __MBADICTIONARY_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
#include "../MBAProtocols/MBATransferProtocol.h"
 /* Exported define -----------------------------------------------------------*/
#define MAX_NAME_DESCRIPTION	20 	/*!< Max. chars for a register description */

/* Index areas: TBD*/
#define FRAME_AREA_LOW		0x1000
#define FRAME_AREA_HIGH		0x1FFF

/* Size options */
#define BYTE_SIZE	1	/*!< Byte size in bytes:  	1 */
#define SHORT_SIZE	2	/*!< short size in bytes: 	2 */
#define WORD_SIZE	4	/*!< int size in bytes:   	4 */
#define DWORD_SIZE	8	/*!< long size in bytes:  	8 */
#define MAX_STRING_SIZE	40	/*!< Max. string size in bytes: 40 */

/* type/access options */
#define SIGNED_DATA	0x01 /*!< Data type: 	Signed */
#define UNSIGNED_DATA	0x00 /*!< Data type: 	Unsigned */
#define CHAR_DATA	0x02 /*!< Data type: 	Char. Could be signed or unsigned */
#define READ_DATA	0x10 /*!< Access type: 	Read data from register */
#define WRITE_DATA	0x20 /*!< Access type: 	Write data into register */
#define READ_INFO	0x40 /*!< Access type: 	Read information from register */
#define WRITE_INFO	0x80 /* NOT IMPLEMENTED */

/* Common access combinations */
/** @brief Full access to a register. For standard registers */
#define FULL_ACCESS		(READ_DATA | WRITE_DATA | READ_INFO | WRITE_INFO)
/** @brief Read only access to a register. For non writtable registers */
#define READ_ONLY_ACCESS	(READ_DATA | READ_INFO)
/** @brief Write only access to a register. Note that the register description can be
  *        read */
#define WRITE_ONLY_ACCESS	(WRITE_DATA | READ_INFO)
/** @brief Protected Access. Description cannot be read. For passwords or other protected
  *        functions*/
#define PROTECTED_ACCESS	(WRITE_DATA) 


 /* Exported types ------------------------------------------------------------*/
 /**
  * @brief
  */
 typedef enum
 {
   WRITE_DATA_SUCCESS	= 4,	/*!< Register written successfully */
   READ_INFO_SUCCESS	= 3,	/*!< Register description read it successfully */
   READ_DATA_SUCCESS	= 2,	/*!< Register read successfully */
   OBJECT_FOUND 	= 1,	/*!< Registers exists in the dictionary */
   OBJECT_SUCCESS	= 0,	/*!< General dictionary function has been executed successfully*/
   OBJECT_NOT_FOUND	= -1,	/*!< Register doesn't exists in the dictionary */
   INCORRECT_SIZE	= -2,	/*!< Size doesn't match the expected value */
   INCORRECT_ACCESS	= -3	/*!< Incorrect request to a register */
 }ObjectRet;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
 /* Global dictionary functions */
void InitDictionary(void);
ObjectRet CheckObjectInDictionary(uint16_t RegisterID);
ObjectRet ProcessObject(uint16_t RegisterID, uint8_t *TypeAccess, uint32_t *Size, uint8_t **Data);

/* Function to attach variables and callbacks from other modules to the dictionary registers */
int32_t AttachVariableToRegister(uint16_t RegisterID, void *Variable, uint16_t size);
int32_t AttachCallBackToRegister(uint16_t RegisterID, voidFuncPtr Callback);

/************************ Dictionary variables **********************/

/************************ Dictionary Functions prototype **********************/

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

#endif /* __MBADICTIONARY_H */
