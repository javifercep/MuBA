/**
  ******************************************************************************
  * @file    MBATransferProtocol.h
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA transfer protocol functions 
  *	     for upper layers
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
  *	@addtogroup MBA_Transfer_Protocol
  *	@{
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MBATRANSFERPROTOCOL_H
#define __MBATRANSFERPROTOCOL_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../MBATypes.h"
#include "SysConfig.h"
	 
/* Exported define -----------------------------------------------------------*/
#define HEADER_SIZE			10  /*!< Header Transfer protocol size */
#define CRC_SIZE			2   /*!< CRC Transfer protocol size */
	 
/* Commands inside a transfer protocol frame */
#define TRANSFER_COMMAND		0x00  /*!< Bridge command */
#define OPERATION_COMMAND		0x01  /*!< State machine command */
#define CONFIG_COMMAND			0x02  /*!< Dictionary management command */
	 
/* Transfer protocol cast modes *************/
/* Cast direction */
#define TO_BUFFER			0x00 /*!< Cast direction */
#define FROM_BUFFER			0x01 /*!< Cast direction */
/* Cast mode		*/
#define END_BUS				0x00 /*!< The cast add transfer protocol parameters */
#define	MBA_BRIDGE			0x02 /*!< There is no cast	*/
	 
/* Exported types ------------------------------------------------------------*/


/**
  * @brief Transfer protocol header
  */
typedef struct
{
    uint8_t  DestinationID; /*!< Contains the address of the destination node. This
			     *   ID is composed by the "Logical address" (5 MSB) &
			     *   the target interface address (3 LSB) */
    uint8_t  Command;	    /*!< Operation to be executed. Currently 3 commands are
			     *   supported:
			     *     - Transfer command. Move data from one node to other
			     *     - Config command. Write/read dictionary objects
			     * 	   - Operation command. Manage the state machine */
    uint16_t Size;          /*!< TSize of the data field */
    uint8_t  SourceID;	    /*!< Contains the address of the source node. Same format
			     *   than @ref DestinationID. */
    uint8_t  FlowControl;   /*!< Not implemented */
    uint32_t TimeStamp;	    /*!< Not implemented */
}TransProtHeader;

/**
  * @brief Transfer protocol frame
  */
typedef struct
{
  TransProtHeader Header;   /*!< Header. Refer to @ref TransProtHeader	*/
  uint8_t	  *Data;    /*!< Data.	*/
  uint16_t	  Checksum; /*!< Checksum. Format to be defined	*/
}TransProtFrame;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* SET macros *******************************/
/* Global ID */
/**
  * @brief Sets the logical address.
  */
#define SetLogicalId(ID)			((ID <<  3) & 0xF8)
/**
  * @brief Sets the interface address.
  */
#define SetInterfaceId(ID)			(ID & 0x07)
/* GET macros *******************************/
/* Destination ID */
/**
  * @brief Reads destination ID
  */
#define GetDestNodeId(Frame)			(Frame.Header.DestinationID)
/**
  * @brief Reads the logical address of a destination ID
  */
#define GetDestLogicalId(Frame)			(Frame.Header.DestinationID >> 3)
/**
  * @brief Reads the interface address of a destination ID
  */
#define GetDestInterfaceId(Frame)		(Frame.Header.DestinationID & 0x07)
/**
  * @brief Reads destination ID. Pointer format.
  */
#define GetDestNodeIdP(Frame)			(Frame->Header.DestinationID)
/**
  * @brief Reads the logical address of a destination ID. Pointer format.
  */
#define GetDestLogicalIdP(Frame)		(Frame->Header.DestinationID >> 3)
/**
  * @brief Reads the interface address of a destination ID. Pointer format.
  */
#define GetDestInterfaceIdP(Frame)		(Frame->Header.DestinationID & 0x07)

/* Source ID */
/**
  * @brief Reads source ID
  */
#define GetSrcNodeId(Frame)			(Frame.Header.SourceID)
/**
  * @brief Reads the logical address of a source ID
  */
#define GetSrcLogicalId(Frame)			(Frame.Header.SourceID >> 3)
/**
  * @brief Reads the interface address of a source ID
  */
#define GetSrcInterfaceId(Frame)		(Frame.Header.SourceID & 0x07)
/**
  * @brief Reads source ID. Pointer format.
  */
#define GetSrcNodeIdP(Frame)			  (Frame->Header.SourceID)
/**
  * @brief Reads the logical address of a source ID. Pointer format.
  */
#define GetSrcLogicalIdP(Frame)			(Frame->Header.SourceID >> 3)
/**
  * @brief Reads the interface address of a source ID. Pointer format.
  */
#define GetSrcInterfaceIdP(Frame)		(Frame->Header.SourceID & 0x07)


/* Other header parameters */
/**
  * @brief Reads the command field.
  */
#define GetFrameCommand(Frame)			(Frame.Header.Command)
/**
  * @brief Reads the total size of a transfer protocol frame.
  */
#define GetFrameSize(Frame)			(Frame.Header.Size + HEADER_SIZE + CRC_SIZE)
/**
  * @brief Reads the data size of a transfer protocol frame.
  */
#define GetFrameDataSize(Frame)			(Frame.Header.Size)
/**
  * @brief Reads the command field. Pointer format.
  */
#define GetFrameCommandP(Frame)			(Frame->Header.Command)
/**
  * @brief Reads the total size of a transfer protocol frame. Pointer format.
  */
#define GetFrameSizeP(Frame)			(Frame->Header.Size + HEADER_SIZE + CRC_SIZE)
/**
  * @brief Reads the data size of a transfer protocol frame. Pointer format.
  */
#define GetFrameDataSizeP(Frame)(Frame->Header.Size)

/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Initialization */
void TransferProtocolInit(void);
void TransferProtocolFrameInit(TransProtFrame *Frame);

/* Frame management */
int32_t TransferProtocolCast(TransProtFrame *TPFrame, uint8_t *pBuf, uint32_t Size, 
                             uint8_t InterfaceID, uint8_t Mode);
int32_t TransferProtocolCopy(TransProtFrame *TPFrameDest, TransProtFrame *TPFrameSrc);
int32_t TransferProtocolProcess(TransProtFrame *TPFrameDest, TransProtFrame *TPFrameSrc);

/* Interfaces management */
uint8_t TransferProtocolGetAvailableInterfaces(void);

uint8_t TransferProtocolGetInterfaceType(uint8_t InterfaceID);
void TransferProtocolSetInterfaceType(uint8_t InterfaceID, uint8_t type);

void TransferProtocolUpdateInterfaceState(uint8_t InterfaceID);
uint8_t TransferProtocolGetInterfaceState(uint8_t InterfaceID);
void TransferProtocolForceInterfaceState(uint8_t InterfaceID,   uint8_t State);

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
#endif /*__MBATRANSFERPROTOCOL_H */
