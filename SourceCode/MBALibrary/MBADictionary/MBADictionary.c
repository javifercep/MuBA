/**
  ******************************************************************************
  * @file    MBADictionary.c
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
  *		@brief Register dictionary.
  *		@details The MBA dictionary contains all parameters and configurations
  *			 about the bus interfaces and device functions
*/


/* Includes ------------------------------------------------------------------*/
#include "MBADictionary.h"			/*!< Dictionary header file */
#include "../../TOOLS/MemoryManagement.h"	/*!< Memory tools */

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief Each register (or object) is composed by the shown elements
  */
typedef struct
{
    uint16_t 	  index;				                /*!< Register position in the dicionary*/
    const char  name[MAX_NAME_DESCRIPTION]; 	/*!< Register description */
    uint16_t	  nameSize;			                /*!< Size of the register description */
    uint8_t  	  size;				                  /*!< Size of the register data */
    uint8_t  	  typeAccess;			              /*!< Type and access identification */
    void*	      data;				                  /*!< Register data */
    voidFuncPtr	callback;			                /*!< Register callback */
}ObjectStruct;
/* Private define ------------------------------------------------------------*/

#define DICTIONARY_SIZE		      (sizeof(Dictionary)/sizeof(ObjectStruct))
#define	OBJECT_SIZE		          2
#define OBJECT_SIZE_INDEX_LOW	  0
#define OBJECT_SIZE_INDEX_HIGH	1
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t VendorID;

/**
  * @brief Dictionary
  * @details The dictionary registers are represented as:
  *           - {index, name, Namesize, size, typeAccess, data, callback}
  */
static ObjectStruct Dictionary[] =
{
    /* Global Identification registers */
    {0x0100, "Device name",		      sizeof("Device name") - 1,		    sizeof("Noodleboard") - 1,  	READ_ONLY_ACCESS | CHAR_DATA, 	 	"Noodleboard",  NULL},
    {0x0101, "Vendor ID",  		      sizeof("Vendor ID") - 1, 		      sizeof(VendorID),		          READ_ONLY_ACCESS | UNSIGNED_DATA, &VendorID,	    NULL},
    /* State machine registers */
    {0x0A00, "Actual State",    	  sizeof("Actual State") - 1,       0,                       	    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,		        NULL},
    {0x0A0A, "Requested State", 	  sizeof("Requested State") - 1,    0,                          	READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,		        NULL},
    /* Device Identification in network */
    {0x0F00, "Device ID", 		      sizeof("Device ID") - 1,	   	    0,				                    FULL_ACCESS | UNSIGNED_DATA, 		  NULL,		        NULL},
    {0x0F10, "Device Interfaces", 	sizeof("Device Interfaces") - 1,  0,                       	    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,		        NULL},
#if AVAILABLE_INTERFACES > 0
    /* Interface 0 description: USB */
    {0x1000, "Interface 0", 	    	sizeof("Interface 0") - 1, 		    0,				                    READ_ONLY_ACCESS | UNSIGNED_DATA,	NULL,		        NULL},
    {0x1001, "Interface ID", 	    	sizeof("Interface ID") - 1, 	    0,				                    READ_ONLY_ACCESS | CHAR_DATA, 		NULL,		        NULL},
    {0x1002, "Interface Link",    	sizeof("Interface Link") - 1,     0, 				                    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1003, "Interface Type",    	sizeof("Interface Type") - 1,     0, 				                    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1004, "Interface State",   	sizeof("Interface State") - 1,    0, 				                    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x1200, "PHDL Fields",       	sizeof("PHDL Fields") - 1,        0,                       	    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x1201, "Field 0",           	sizeof("Field 0") - 1,            0,                       	    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x1300, "PHDL Parameters",    	sizeof("PHDL Parameters") - 1,    0,                       	    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x1600, "Protocol Fields",   	sizeof("Protocol Fields") - 1,    0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1601, "Field 0",           	sizeof("Field 0") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1602, "Field 1",           	sizeof("Field 1") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1603, "Field 2",           	sizeof("Field 2") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1604, "Field 3",          	  sizeof("Field 3") - 1,           	0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1605, "Field 4",           	sizeof("Field 4") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1606, "Field 5",           	sizeof("Field 5") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1607, "Field 6",           	sizeof("Field 6") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1608, "Field 7",           	sizeof("Field 7") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1609, "Field 8",           	sizeof("Field 8") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x160A, "Field 9",           	sizeof("Field 9") - 1,            0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x160B, "Field 10",         	  sizeof("Field 10") - 1,          	0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x160C, "Field 11",          	sizeof("Field 11") - 1,           0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x160D, "Field 12",          	sizeof("Field 12") - 1,           0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x160E, "Field 13",          	sizeof("Field 13") - 1,           0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x160F, "Field 14",          	sizeof("Field 14") - 1,           0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1610, "Field 15",          	sizeof("Field 15") - 1,           0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1700, "Frame Detection",   	sizeof("Frame detection") - 1,    0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1701, "Field Detection",   	sizeof("Field detection") - 1,    0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1710, "Global Timeout",    	sizeof("Global Timeout") - 1,     0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1711, "Decoding Timeout",  	sizeof("Decoding Timeout") - 1,   0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1720, "Detection Field",   	sizeof("Detection field") - 1,    0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1730, "Size Field",        	sizeof("Size Field") - 1,         0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x1740, "Split Value",       	sizeof("Split value") - 1,        0,                       	    FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
#endif  
#if AVAILABLE_INTERFACES > 1
    /* Interface 1 description: SPI */
    {0x2000, "Interface 1", 	  sizeof("Interface 1") - 1, 		        0, 				                    READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x2001, "Interface ID", 	  sizeof("Interface ID") - 1, 	    	  0, 				                    READ_ONLY_ACCESS | CHAR_DATA,		  NULL,					  NULL},
    {0x2002, "Interface Link",    sizeof("Interface Link") - 1,       0, 											      FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2003, "Interface Type",    sizeof("Interface Type") - 1,       0, 											      FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2004, "Interface State",   sizeof("Interface State") - 1,      0, 			                      READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x2200, "PHDL Fields",       sizeof("PHDL Fields") - 1,          0,                            READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x2201, "Field 0",           sizeof("Field 0") - 1,              0,                            READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x2300, "PHDL parameters",   sizeof("PHDL parameters") - 1,      0,                            READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x2600, "Protocol Fields",   sizeof("Protocol Fields") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2601, "Field 0",           sizeof("Field 0") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2602, "Field 1",           sizeof("Field 1") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2603, "Field 2",           sizeof("Field 2") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2604, "Field 3",           sizeof("Field 3") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2605, "Field 4",           sizeof("Field 4") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2606, "Field 5",           sizeof("Field 5") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2607, "Field 6",           sizeof("Field 6") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2608, "Field 7",           sizeof("Field 7") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2609, "Field 8",           sizeof("Field 8") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x260A, "Field 9",           sizeof("Field 9") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x260B, "Field 10",          sizeof("Field 10") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x260C, "Field 11",          sizeof("Field 11") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x260D, "Field 12",          sizeof("Field 12") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x260E, "Field 13",          sizeof("Field 13") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x260F, "Field 14",          sizeof("Field 14") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2610, "Field 15",          sizeof("Field 15") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2700, "Frame Detection",   sizeof("Frame detection") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2701, "Field Detection",   sizeof("Field detection") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2710, "Global Timeout",    sizeof("Global Timeout")- 1,        0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2711, "Decoding Timeout",  sizeof("Decoding Timeout") - 1,     0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2720, "Detection Field",   sizeof("Detection field") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2730, "Size Field",        sizeof("Size Field") - 1,           0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x2740, "Split Value",       sizeof("Split value") - 1,          0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
#endif
    /* Interface 2 description: USART */
#if AVAILABLE_INTERFACES > 2
    {0x3000, "Interface 2", 	    sizeof("Interface 2") - 1, 	        0,			                      READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x3001, "Interface ID", 	    sizeof("Interface ID") - 1, 	      0,			                      READ_ONLY_ACCESS | CHAR_DATA,	  NULL,					    NULL},
    {0x3002, "Interface Link",    sizeof("Interface Link") - 1,       0,			                      FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3003, "Interface Type",    sizeof("Interface Type") - 1,       0,			                      FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3004, "Interface State",   sizeof("Interface State") - 1,      0, 			                      FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3200, "PHDL Fields",       sizeof("PHDL Fields") - 1,          0,                            READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x3201, "Field 0",           sizeof("Field 0") - 1,              0,                            READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x3300, "PHDL paramters",    sizeof("PHDL parameters") - 1,      0,                            READ_ONLY_ACCESS | UNSIGNED_DATA, NULL,					  NULL},
    {0x3600, "Protocol Fields",   sizeof("Protocol Fields") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3601, "Field 0",           sizeof("Field 0") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3602, "Field 1",           sizeof("Field 1") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3603, "Field 2",           sizeof("Field 2") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3604, "Field 3",           sizeof("Field 3") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3605, "Field 4",           sizeof("Field 4") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3606, "Field 5",           sizeof("Field 5") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3607, "Field 6",           sizeof("Field 6") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3608, "Field 7",           sizeof("Field 7") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3609, "Field 8",           sizeof("Field 8") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x360A, "Field 9",           sizeof("Field 9") - 1,              0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x360B, "Field 10",          sizeof("Field 10") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x360C, "Field 11",          sizeof("Field 11") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x360D, "Field 12",          sizeof("Field 12") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x360E, "Field 13",          sizeof("Field 13") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x360F, "Field 14",          sizeof("Field 14") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3610, "Field 15",          sizeof("Field 15") - 1,             0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3700, "Frame Detection",   sizeof("Frame detection") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3701, "Field Detection",   sizeof("Field detection") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3710, "Global Timeout",    sizeof("Global Timeout") - 1,       0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3711, "Decoding Timeout",  sizeof("Decoding Timeout") - 1,     0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3720, "Detection Field",   sizeof("Detection field") - 1,      0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3730, "Size Field",        sizeof("Size Field") - 1,           0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
    {0x3740, "Split Value",       sizeof("Split value") - 1,          0,                            FULL_ACCESS      | UNSIGNED_DATA, NULL,					  NULL},
#endif

#if   DEVICE_SUPPORT > 0
    /* Board support registers */
    {0xA000, "Board LEDs",  	    sizeof("Board LEDs") - 1, 	        0,			                      FULL_ACCESS      | UNSIGNED_DATA, NULL,           NULL},
#endif
    {0xFFFF, "Reset",  	    	    sizeof("Reset") - 1,  		          1,			                      WRITE_ONLY_ACCESS| UNSIGNED_DATA, NULL,           NULL}
};
/* Private function prototypes -----------------------------------------------*/

static ObjectRet CheckObjectIndex(uint16_t Index, uint16_t *DictionaryIndex);
static uint8_t GetObjectType(uint16_t DictionaryIndex);
static void ExecuteObjectCallBack(uint16_t DictionaryIndex);

/* Write/Read functions */
static ObjectRet WriteObjectData(uint16_t DictionaryIndex, uint8_t *Data, uint32_t Size);
static ObjectRet ReadObjectInfo(uint16_t DictionaryIndex, uint8_t *TypeAccess, uint8_t **Data, uint32_t *Size);
static ObjectRet ReadObjectData(uint16_t DictionaryIndex, uint8_t **Data, uint32_t *Size);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize object values
  */
void InitDictionary(void)
{
	VendorID = 0x2C;
}

/**
  * @brief  	Check if a register exists in the dictionary
  * @param[in]  RegisterID	Register index in the dictionary
  * @retval 	OBJECT_FOUND if the registers exists,
  *		OBJECT_NOT_FOUND otherwise
  */
ObjectRet CheckObjectInDictionary(uint16_t RegisterID)
{
	/* Check if configuration object exists */
	return CheckObjectIndex(RegisterID, NULL);
}

/**
  * @brief  Process a config protocol request
  * @details Execute the requested access in the next order:
  *          - Write access
  *          - Read description access
  *          - Read access
  * @param[in]     RegisterID	Object index
  * @param[in]	   TypeAccess	Requested access
  * @param[in,out] Size data size to be written and data size to be read
  * @param[in,out] Data Data to be written and data to be read
  * @retval Refer to @ref ObjectRet
  */
ObjectRet ProcessObject(uint16_t RegisterID, uint8_t *TypeAccess, uint32_t *Size, uint8_t **Data)
{
    ObjectRet ret;
    uint8_t *pDataTemp = *Data;		/* Temporal pointer for data access */
    uint8_t *pReadTemp = NULL;		/* temporal pointer for read access */
    uint32_t TempSize, TempFullReadSize;
    uint16_t LocalDictionaryIndex = 0;
    uint8_t CommandAccess = *TypeAccess, TempTypeAccess;

    /* Check if configuration object exists */
    ret = CheckObjectIndex(RegisterID, &LocalDictionaryIndex);

    /* Check if the configuration object has to be written */
    if(((CommandAccess & WRITE_DATA) != 0) && ((GetObjectType(LocalDictionaryIndex) & WRITE_DATA) != 0))
    {
      ret = WriteObjectData(LocalDictionaryIndex, pDataTemp, *Size);

      /* Execute callback if exists */
      if(ret == WRITE_DATA_SUCCESS)
      {
        ExecuteObjectCallBack(LocalDictionaryIndex);
        ret = OBJECT_SUCCESS;
      }
    }
    /* TODO: Implement write info */

    /* If there is only write functions, no reply will be. Reset Size for
     * readings functions and free allocated memory for write functions */
    if(pDataTemp != NULL)
    {
      /* Once the object is written, free the allocated memory */
      MemFree(pDataTemp);
      pDataTemp = NULL;
    }
    *Size = 0;

    /* Check if the configuration object has to be read */
    if(((CommandAccess & READ_INFO) != 0) && ((GetObjectType(LocalDictionaryIndex) & READ_INFO) != 0))
    {
      /* Use pReadTemp as temporal buffer */
      ret = ReadObjectInfo( LocalDictionaryIndex, &TempTypeAccess, &pReadTemp, &TempSize);
      if(ret == READ_INFO_SUCCESS)
      {
          *TypeAccess = TempTypeAccess;
          pDataTemp = (uint8_t*)MemAlloc((TempSize)*sizeof(uint8_t));
          if(pDataTemp != NULL)
          {
            memcpy(pDataTemp, pReadTemp, TempSize);
            *Data = pDataTemp;
            *Size = TempSize;
            ret = OBJECT_SUCCESS;
          }
          else
          {
            ret = INCORRECT_SIZE;
          }
      }
      if(pReadTemp != NULL)
      {
          /* Free the allocated data for pReadTemp */
          MemFree(pReadTemp);
          pReadTemp = NULL;
      }
    }
    if(((CommandAccess & READ_DATA) != 0) && ((GetObjectType(LocalDictionaryIndex) & READ_DATA) != 0))
    {
      TempFullReadSize = TempSize;
      /* Use pReadTemp as temporal buffer */
      ret = ReadObjectData( LocalDictionaryIndex, &pReadTemp, &TempSize);
      if(ret == READ_DATA_SUCCESS)
      {
          /* If a read info has been executed, copy new data at the end of the
           * pDataTemp buffer */
          if(pDataTemp != NULL)
          {
            pDataTemp = (uint8_t *)MemRealloc(pDataTemp, (Dictionary[LocalDictionaryIndex].size + TempFullReadSize)*sizeof(uint8_t));
            *Data = pDataTemp;
            pDataTemp += TempFullReadSize;
          }
          else
          {
            pDataTemp = (uint8_t*)MemAlloc((TempSize)*sizeof(uint8_t));
            *Data = pDataTemp;
          }
          memcpy(pDataTemp, pReadTemp, TempSize);
          *Size += TempSize;
          ret = OBJECT_SUCCESS;
      }
      if(pReadTemp != NULL)
      {
          /* Free the allocated data for pReadTemp */
          MemFree(pReadTemp);
          pReadTemp = NULL;
      }
    }
    return ret;
}

/**
  * @brief  Attach a variable of other modules into the dictionary variable
  * @param[in]  RegisterID Object index to attach the external variable
  * @param[in]	Variable Address of the external variable where the dictionary
  *		pointer must point.
  * @param[in]	Size Size of the external variable
  * @retval 	0 if success, -1 otherwise. The ObjectRet enum is not used for better
  *		code modularity
  */
int32_t AttachVariableToRegister(uint16_t RegisterID, void *Variable, uint16_t Size)
{
    ObjectRet SearchRet;
    int32_t Ret;
    uint16_t DictionaryIndex;

    /* Look for the register into the dictionary */
    SearchRet = CheckObjectIndex(RegisterID, &DictionaryIndex);

    /* If the register exists, change the object pointers */
    if (SearchRet == OBJECT_FOUND)
    {
	Dictionary[DictionaryIndex].data = Variable;
	Dictionary[DictionaryIndex].size = Size;
	Ret = 0;
    }
    else
    {
	Ret = -1;
    }

    return Ret;
}

/**
  * @brief	Attachs a function of other modules into the dictionary callback
  * @param[in]  RegisterID Object index to attach the external variable
  * @param[in]	Callback external function pointer.
  * @retval 	0 if success, -1 otherwise. The ObjectRet enum is not used for better
  *		code modularity
  */
int32_t AttachCallBackToRegister(uint16_t RegisterID, voidFuncPtr Callback)
{
    ObjectRet SearchRet;
    int32_t Ret;
    uint16_t DictionaryIndex;

    /* Look for the register into the dictionary */
    SearchRet = CheckObjectIndex(RegisterID, &DictionaryIndex);

    /* If the register exists, change the object pointers */
    if (SearchRet == OBJECT_FOUND)
    {
	Dictionary[DictionaryIndex].callback = Callback;
	Ret = 0;
    }
    else
    {
	Ret = -1;
    }

    return Ret;
}

/************** Static Functions **********************************/
/**
  * @brief  Check if an object exists in the dictionary
  * @param[in]  Index Object index
  * @param[out] DictionaryIndex Internal dictionary array index
  * @retval refer to @ref ObjectRet
  */
ObjectRet CheckObjectIndex(uint16_t Index, uint16_t *DictionaryIndex)
{
    uint16_t IndexCount;
    uint16_t *RetIndex;
    ObjectRet ret = OBJECT_NOT_FOUND;
    IndexCount = 0;

    if(DictionaryIndex != NULL)
    {
	RetIndex = DictionaryIndex;
    }

    /* Look for the object index */
    while(IndexCount < DICTIONARY_SIZE)
    {
      if(Dictionary[IndexCount].index == Index)
      {
	  *RetIndex = IndexCount;
	  ret = OBJECT_FOUND;
	  break;
      }
      IndexCount++;
    }
    return ret;
}

/**
  * @brief  Get the typeaccess parameter of a register.
  * @note   Use the index returned by the function @ref CheckObjectIndex
  * @param[in] DictionaryIndex	Object index in the dictionary array
  * @retval Typeaccess parameter
  */
uint8_t GetObjectType(uint16_t DictionaryIndex)
{
    return Dictionary[DictionaryIndex].typeAccess;
}

/**
  * @brief  Launches a register callback
  * @note   Use the index returned by the function @ref CheckObjectIndex
  * @param[in] DictionaryIndex Object index in the dictionary array
  */
void ExecuteObjectCallBack(uint16_t DictionaryIndex)
{
    if(Dictionary[DictionaryIndex].callback != NULL)
    {
	Dictionary[DictionaryIndex].callback();
    }
}

/* Write/Read functions */
/**
  * @brief  Write operation.
  * @note   Use the index returned by the function @ref CheckObjectIndex
  * @param[in] DictionaryIndex Object index in the dictionary array
  * @param[in] Data	Data to be written
  * @param[in] Size	Size of data to be written
  * @retval refer to @refer ObjectRet
  */
ObjectRet WriteObjectData(uint16_t DictionaryIndex, uint8_t *Data, uint32_t Size)
{
    uint8_t *pDataTemp = Data;
    memcpy(Dictionary[DictionaryIndex].data, pDataTemp, Size);

    return WRITE_DATA_SUCCESS;
}

/**
  * @brief  	Read description operation.
  * @note 	Use the index returned by the function @ref CheckObjectIndex
  * @param[in]  DictionaryIndex Object index in the dictionary array
  * @param[out] TypeAccess Typeaccess parameter of the requested register
  * @param[out] Data	Size and description of the requested register
  * @param[out]	Size	Size of the returned Data buffer.
  * @retval refer to @refer ObjectRet
  */
ObjectRet ReadObjectInfo(uint16_t DictionaryIndex, uint8_t *TypeAccess, uint8_t **Data, uint32_t *Size)
{
    uint8_t *pTemp;
    uint32_t TempSize;
    ObjectRet ret = READ_INFO_SUCCESS;

    /* Compute size of the generated buffer: description array size + 2 bytes of the size field */
    TempSize = Dictionary[DictionaryIndex].nameSize + OBJECT_SIZE;

    /* Get the object typeaccess parameter */
    *TypeAccess = Dictionary[DictionaryIndex].typeAccess;

    /* Alloc memory into a temporal buffer to copy dictionary information into Data */
    pTemp = (uint8_t*) MemAlloc((TempSize)*sizeof(uint8_t));

    if(pTemp == NULL)
    {
      ret = INCORRECT_SIZE;
      *Size = 0;
    }
    else
    {
      *Data = pTemp;
      /* Copy object size */
      pTemp[OBJECT_SIZE_INDEX_HIGH] = (uint8_t)((Dictionary[DictionaryIndex].size >> 8) & 0x00FF);
      pTemp[OBJECT_SIZE_INDEX_LOW] = (uint8_t)(Dictionary[DictionaryIndex].size & 0x00FF);
      pTemp += OBJECT_SIZE;
	
      /* Copy object description */
      memcpy(pTemp, Dictionary[DictionaryIndex].name, Dictionary[DictionaryIndex].nameSize);
	
      /* return the size of the generated data bufer */
      *Size = TempSize;
    }

    return ret;
}

/**
  * @brief Read operation.
  * @note  Use the index returned by the function @ref CheckObjectIndex
  * @param[in] DictionaryIndex Object index in the dictionary array
  * @param[out] Data	Data value of the requested register
  * @param[out]	Size	Size of the returned Data buffer.
  * @retval refer to @refer ObjectRet
  */
ObjectRet ReadObjectData(uint16_t DictionaryIndex, uint8_t **Data, uint32_t *Size)
{
    uint8_t *pTemp;
    ObjectRet ret = READ_DATA_SUCCESS;

    /* Alloc memory into a temporatl buffer to copy the object value */
    pTemp = (uint8_t*) MemAlloc(Dictionary[DictionaryIndex].size);

    if(pTemp == NULL)
    {
	ret = INCORRECT_SIZE;
	*Size = 0;
    }
    else
    {
	/* Copy data value */
	*Data = pTemp;
	memcpy(pTemp, Dictionary[DictionaryIndex].data, Dictionary[DictionaryIndex].size);

	/* return the size of the generated data bufer */
	*Size = Dictionary[DictionaryIndex].size;
    }

    return ret;
}

/*********************** Dictionary functions ****************************************/


/**
  *@}
  */
/**
  *@}
  */
/**
  *@}
  */
