/**
  ******************************************************************************
  * @file    MBATransferProtocol.c
  * @author  Javier Fernandez Cepeda
  * @brief   This file contains the MBA transfer protocol functions 
  * 	     for upper layers
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
  *		@brief Transfer Protocol is the responsible to give an unique frame for
  *		       all interfaces.
  *		@details This protocol envolves multiple functionalities such as:
  *			 - Frame transfer for all interfaces
  *			 - Routing
  *			 - Casting
  *			 - Flow control
  *			- Time management
*/

/* Includes ------------------------------------------------------------------*/
#include "SysConfig.h"
#include "MBATransferProtocol.h"
#include "MBAConfigProtocol.h"
#include "MBAOperationProtocol.h"
#include "../../TOOLS/MemoryManagement.h"
/* Private typedef -----------------------------------------------------------*/

/**
  * @brief Each interface has an ID link which allows to link the different IDs
  */
typedef struct
{
  uint8_t             InterfaceID;      /*!< ID of the interfaces available in each device */
  uint16_t            ScanID;           /*!< Assigned ID during the scan process */
  uint8_t             LogicalID;        /*!< ID assigned by the application */
  uint8_t             LinkedDevice;     /*!< ID of the device linked to this interface */
  char                InterfaceName[10];/*!< Name of the related interface */
  uint8_t             NameSize;         /*!< Name size of the related interface */
  uint8_t             InterfaceType;    /*!< Interface type: MBA bridge or End bus */
  BusInstanceStates   InterfaceState;   /*!< Interface state: INIT, INACTIVE or ACTIVE*/
}TPIDLink;

typedef struct
{
  uint8_t LinkedLogicalID[10];
}TRouteTable;

typedef enum
{
    INTERFACE_TO_SCAN = 0,	/*!< Search link table mode */
    INTERFACE_TO_LOGICAL,	  /*!< Search link table mode */
    INTERFACE_TO_LINKEDDEV, /*!< Search link table mode */
    SCAN_TO_INTERFACE,      /*!< Search link table mode */
    SCAN_TO_LOGICAL,        /*!< Search link table mode */
    SCAN_TO_LINKEDDEV,      /*!< Search link table mode */
    LOGICAL_TO_INTERFACE,   /*!< Search link table mode */
    LOGICAL_TO_SCAN,        /*!< Search link table mode */
    LOGICAL_TO_LINKEDDEV,   /*!< Search link table mode */
    LINKEDDEV_TO_INTERFACE, /*!< Search link table mode */
    LINKEDDEV_TO_SCAN,      /*!< Search link table mode */
    LINKEDDEV_TO_LOGICAL    /*!< Search link table mode */
}TPLinkModes;

/* Private define ------------------------------------------------------------*/
/* Transfer cast masks */
#define DIR_MASK	0x01	/*!< Cast direction */
#define CAST_MASK	0x02	/*!< Cast mode */
#define CAST_ERROR      -1

/* Link table defines */
#define MAX_INTERFACES          8       /*!< Maximum interfaces per node */
#define DEFAULT_LOGICAL_ID 			10      /*!< Default node ID */
#define LOGICAL_ID_INDEX			  0x0F00  /*!< Logical ID index*/
#define DEVICE_INTERFACES_INDEX 0x0F10  /*!< Number of interfaces index */

#define INTERFACE_DESCRIPTION_BASE_ADDRESS	    0x1000  /*!< Interface base index */
#define INTERFACE_DESCRIPTION_NAME_OFFSET       1       /*!< Interface name index offset */
#define INTERFACE_DESCRIPTION_LINKEDDEV_OFFSET  2	      /*!< Interface linked device indexoffset */
#define INTERFACE_DESCRIPTION_TYPE_OFFSET       3	      /*!< Interface type index offset */
#define INTERFACE_DESCRIPTION_STATE_OFFSET      4	      /*!< Interface state index offset */

/* Frame defines */
#define DESTINATION_ID_INDEX    0 /*!< Destination id buffer index */
#define COMMAND_INDEX           1 /*!< Command buffer index */
#define SIZE_LOW_BYTE_INDEX     2 /*!< Low byte size buffer index */
#define SIZE_HIGH_BYTE_INDEX    3 /*!< High byte size buffer index */
#define SOURCE_ID_INDEX         4 /*!< Source id buffer index */
#define FLOW_CONTROL_INDEX      5 /*!< Flow control buffer index */
#define TIMESTAMP_0_BYTE_INDEX  6 /*!< TimeStamp byte 0 buffer index */
#define TIMESTAMP_1_BYTE_INDEX  7 /*!< TimeStamp byte 1 buffer index */
#define TIMESTAMP_2_BYTE_INDEX  8 /*!< TimeStamp byte 2 buffer index */
#define TIMESTAMP_3_BYTE_INDEX  9/*!< TimeStamp byte 3 buffer index */


/* This index are relative to the base address */
#define SIZE_LOW_BYTE_REL_INDEX		0 /*!< Low byte size buffer index */
#define SIZE_HIGH_BYTE_REL_INDEX	1 /*!< High byte size buffer index */
#define CHECKSUM_LOW_REL_INDEX		0 /*!< Checksum low relative index */
#define CHECKSUM_HIGH_REL_INDEX		1 /*!< Checksum high relative index */

#define SIZE_FIELD_SIZE		    2 /*!< Checksum low relative index */
#define TIME_STAMP_FIELD_SIZE	4 /*!< Checksum low relative index */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/**
  * @brief The ID table identifies each interface and node in the network with an
  *	   user ID (Logical ID). Initially, the only know ID are the related to
  *	   interface.
  */
static TPIDLink TPIDTable[AVAILABLE_INTERFACES] =
{
#if USB_API > 0
{0, 0, 80, 2,  "USB",  3, MBA_BRIDGE}
#endif
#if USB_HOST_API > 0
{0, 0, 16, 10,  "USB Host",  8, MBA_BRIDGE}
#endif
#if SOCKET_API > 0
,{1, 0, 17,  1,  "Socket", 	6, MBA_BRIDGE}
#endif
#if SPI_API > 0
,{1, 0, 81, 20, "SPI",  3, MBA_BRIDGE}
#endif
#if USART_API > 0
,{2, 0, 82, 1,  "USART",5, END_BUS}
#endif
};

static TRouteTable RouteTableLink[AVAILABLE_INTERFACES] =
{
  #if USB_API > 0
{{1,2,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}
#endif
#if USB_HOST_API > 0
{{10,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}
#endif
#if SOCKET_API > 0
,{{1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}
#endif
#if SPI_API > 0
,{{5,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}
#endif
#if USART_API > 0
,{{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}}
#endif
};

static uint8_t AvailableInterfaces;
static uint8_t LogicalID;

/* Private function prototypes -----------------------------------------------*/
int16_t TransferProtocolGetRouteInterface(uint16_t DestLogicalID);
int16_t TransferProtocolGetIDLink(uint16_t ID, TPLinkModes Mode);
void	TransferProtocolUpdateLinks(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initialize Transfer protocol
  */
void TransferProtocolInit(void)
{
    uint8_t InterfaceIndex;

    /* Initialize device addresses and attach related variables to object dictionary */
    LogicalID = TPIDTable[0].LogicalID >> 3;
    AvailableInterfaces = AVAILABLE_INTERFACES;
    for (InterfaceIndex = 0; InterfaceIndex < AvailableInterfaces; InterfaceIndex++)
    {
      TPIDTable[InterfaceIndex].InterfaceState = GetBusInstanceState(InterfaceIndex);
    }

    AttachVariableToRegister(LOGICAL_ID_INDEX, &LogicalID, sizeof(LogicalID));
    AttachCallBackToRegister(LOGICAL_ID_INDEX, TransferProtocolUpdateLinks);

    AttachVariableToRegister(DEVICE_INTERFACES_INDEX, &AvailableInterfaces, sizeof(AvailableInterfaces));

    for( InterfaceIndex = 0; InterfaceIndex < AvailableInterfaces; InterfaceIndex++)
    {
	    AttachVariableToRegister(INTERFACE_DESCRIPTION_BASE_ADDRESS*(InterfaceIndex + 1),
				     &(TPIDTable[InterfaceIndex].InterfaceID),
				     sizeof(TPIDTable[InterfaceIndex].InterfaceID));
	    AttachVariableToRegister(INTERFACE_DESCRIPTION_BASE_ADDRESS*(InterfaceIndex + 1) + INTERFACE_DESCRIPTION_NAME_OFFSET,
				     &(TPIDTable[InterfaceIndex].InterfaceName),
				     TPIDTable[InterfaceIndex].NameSize);
	    AttachVariableToRegister(INTERFACE_DESCRIPTION_BASE_ADDRESS*(InterfaceIndex + 1) + INTERFACE_DESCRIPTION_LINKEDDEV_OFFSET,
				     &(TPIDTable[InterfaceIndex].LinkedDevice),
				     sizeof(TPIDTable[InterfaceIndex].LinkedDevice));
	    AttachVariableToRegister(INTERFACE_DESCRIPTION_BASE_ADDRESS*(InterfaceIndex + 1) +
				     INTERFACE_DESCRIPTION_STATE_OFFSET,
				     &(TPIDTable[InterfaceIndex].InterfaceState),
				     sizeof(TPIDTable[InterfaceIndex].InterfaceState));
	    AttachVariableToRegister(INTERFACE_DESCRIPTION_BASE_ADDRESS*(InterfaceIndex + 1) + INTERFACE_DESCRIPTION_TYPE_OFFSET,
				     &(TPIDTable[InterfaceIndex].InterfaceType),
				     sizeof(TPIDTable[InterfaceIndex].InterfaceType));
    }

    /* Update all the table links */
    TransferProtocolUpdateLinks();
}

/**
  * @brief  	Initialize Transfer protocol frames
  * @param[in]  Frame Transfer protocol frame for initialization
  */
void TransferProtocolFrameInit(TransProtFrame *Frame)
{
    Frame->Header.DestinationID = 0;
    Frame->Header.Command       = 0;
    Frame->Header.Size          = 0; 
    Frame->Header.SourceID      = 0;
    Frame->Header.FlowControl   = 0;
    Frame->Header.TimeStamp     = 0;
    Frame->Checksum             = 0;
}


/**
  * @brief  Casts standard buffers into Transfer protocol frames and vice versa
  * @param[in,out]  TPFrame Transfer protocol frame to be processed
  * @param[in,out]  pBuf    Standard buffer to be processed
  * @param[in]	    Size    Number of bytes to be casted
  * @param[int]     Mode    Cast parameters: Direction and cast mode
  * @retval 	    0 if OK.
  */
int32_t TransferProtocolCast(TransProtFrame *TPFrame, uint8_t *pBuf, uint32_t Size, 
                             uint8_t InterfaceID, uint8_t Mode)
{
  int32_t NewFrameSize = Size;
  TransProtFrame *pTPTemp = TPFrame;
  uint8_t	 *pBufTemp = pBuf, *pAuxBufTemp;

  /* Check the cast direction */
  if((Mode & DIR_MASK) == FROM_BUFFER)
  {
      switch(Mode & CAST_MASK)
      {
        /* Check if the interface is a MBA_BRIDGE or an END_BUS */
        case MBA_BRIDGE:
        /* Copy header into Transfer protocol frame */
          pTPTemp->Header.DestinationID = *(pBufTemp++);
          pTPTemp->Header.Command = *(pBufTemp++);
          pTPTemp->Header.Size = ((uint16_t)pBufTemp[SIZE_LOW_BYTE_REL_INDEX] & WORD_LOW_MASK) +
               (((uint16_t)pBufTemp[SIZE_HIGH_BYTE_REL_INDEX] << BYTE_SHIFT) & WORD_HIGH_MASK);
          pBufTemp += SIZE_FIELD_SIZE;
          pTPTemp->Header.SourceID = *(pBufTemp++);
          pTPTemp->Header.FlowControl = *(pBufTemp++);

          pAuxBufTemp = (uint8_t *)&(pTPTemp->Header.TimeStamp);
          memcpy(pAuxBufTemp, pBufTemp, TIME_STAMP_FIELD_SIZE);
          pBufTemp += TIME_STAMP_FIELD_SIZE;

          if(GetFrameSizeP(pTPTemp) != Size)
          {
            /* handle error */
          }

          /* Alloc memory for transfer protocol data */
          pTPTemp->Data = (uint8_t *)MemAlloc(pTPTemp->Header.Size * sizeof(uint8_t));

          if(pTPTemp->Data != NULL)
          {
            /* Copy data into transfer protocol buffer */
            pAuxBufTemp = pTPTemp->Data;
            memcpy(pAuxBufTemp, pBufTemp, pTPTemp->Header.Size);
            pBufTemp += pTPTemp->Header.Size;
          }
          else
          {
            NewFrameSize = CAST_ERROR;
          }

          /* Copy checksum */
          pTPTemp->Checksum = (uint16_t)(pBufTemp[CHECKSUM_LOW_REL_INDEX] & WORD_LOW_MASK)  |
                  (uint16_t)((pBufTemp[CHECKSUM_HIGH_REL_INDEX] << BYTE_SHIFT) & WORD_HIGH_MASK);
          break;

        case END_BUS:
          pTPTemp->Header.Command = TRANSFER_COMMAND;
          pTPTemp->Header.Size = Size;
          pTPTemp->Header.FlowControl = 0;
          pTPTemp->Header.TimeStamp = 0;
            /* Update the Destination ID checking in the Link Table */
          pTPTemp->Header.DestinationID = SetLogicalId(TransferProtocolGetIDLink (InterfaceID, INTERFACE_TO_LINKEDDEV));
      
          /* Update the source ID with the device Logical ID */
          pTPTemp->Header.SourceID = SetLogicalId(LogicalID) |  SetInterfaceId(InterfaceID);

          /* Copy data */
          pTPTemp->Data = (uint8_t *)MemAlloc(Size);
          pAuxBufTemp = pTPTemp->Data;
          memcpy(pAuxBufTemp, pBufTemp, Size);

          pTPTemp->Checksum = 0;

          break;
      }
  }
  else
  {
      switch(Mode & CAST_MASK)
      {
        /* Check if the interface is a MBA_BRIDGE or an END_BUS */
        case MBA_BRIDGE:
          /* Frame defines */
          /* Copy header into Transfer protocol frame */
          pBufTemp[DESTINATION_ID_INDEX]   = pTPTemp->Header.DestinationID;
          pBufTemp[COMMAND_INDEX]          = pTPTemp->Header.Command;
          pBufTemp[SIZE_LOW_BYTE_INDEX]    = (uint8_t)(pTPTemp->Header.Size & WORD_LOW_MASK);
          pBufTemp[SIZE_HIGH_BYTE_INDEX]   = (uint8_t)((pTPTemp->Header.Size >> BYTE_SHIFT) & WORD_LOW_MASK);
          pBufTemp[SOURCE_ID_INDEX]        = pTPTemp->Header.SourceID;
          pBufTemp[FLOW_CONTROL_INDEX]     = pTPTemp->Header.FlowControl;
          pBufTemp[TIMESTAMP_0_BYTE_INDEX] = (uint8_t)(pTPTemp->Header.TimeStamp & DWORD_0_BYTE_MASK);
          pBufTemp[TIMESTAMP_1_BYTE_INDEX] = (uint8_t)((pTPTemp->Header.TimeStamp >> BYTE_SHIFT) & DWORD_0_BYTE_MASK);
          pBufTemp[TIMESTAMP_2_BYTE_INDEX] = (uint8_t)((pTPTemp->Header.TimeStamp >> WORD_SHIFT) & DWORD_0_BYTE_MASK);
          pBufTemp[TIMESTAMP_3_BYTE_INDEX] = (uint8_t)((pTPTemp->Header.TimeStamp >> DWORD_24_SHIFT) & DWORD_0_BYTE_MASK);

          pBufTemp += HEADER_SIZE;

          if(pTPTemp->Data != NULL)
          {
              /* Copy data into transfer protocol buffer */
              pAuxBufTemp = pTPTemp->Data;
              memcpy(pBufTemp, pAuxBufTemp, pTPTemp->Header.Size);
              pBufTemp += pTPTemp->Header.Size;
          }
          else
          {
              NewFrameSize = CAST_ERROR;
          }

          /* Copy checksum */
          pBufTemp[CHECKSUM_LOW_REL_INDEX]  = (uint8_t)pTPTemp->Checksum & WORD_LOW_MASK;
          pBufTemp[CHECKSUM_HIGH_REL_INDEX]  = (uint8_t)(pTPTemp->Checksum >> BYTE_SHIFT) & WORD_LOW_MASK;

          if(pTPTemp->Data != NULL)
          {
            /* Free allocated data for input transfer protocol frame */
            MemFree(pTPTemp->Data);
            pTPTemp->Data = NULL;
          }
          break;
			
        case END_BUS:
          pAuxBufTemp = pTPTemp->Data;
          memcpy(pBufTemp, pAuxBufTemp, pTPTemp->Header.Size);
          if(pTPTemp->Data != NULL)
          {
            /* Free allocated data for input transfer protocol frame */
            MemFree(pTPTemp->Data);
            pTPTemp->Data = NULL;
          }
          NewFrameSize = pTPTemp->Header.Size;
          break;
        }
  }
  return NewFrameSize;
}

/**
  * @brief  Copy an input transfer protocol into an output transfer protocol
  * @param[out]  TPFrameDest	Transfer protocol frame to be created
  * @param[in]   TPFrameSrc	Transfer protocol frame to be copied
  * @retval 0 if Ok
  */
int32_t TransferProtocolCopy(TransProtFrame *TPFrameDest, TransProtFrame *TPFrameSrc)
{
    int32_t ret = 0;
    TransProtFrame *pTPIn = TPFrameSrc;
    TransProtFrame *pTPOut = TPFrameDest;

    pTPOut->Header.DestinationID = pTPIn->Header.DestinationID;
    pTPOut->Header.Command 	 = pTPIn->Header.Command;
    pTPOut->Header.Size 	 = pTPIn->Header.Size;
    pTPOut->Header.SourceID 	 = pTPIn->Header.SourceID;
    pTPOut->Header.TimeStamp 	 = pTPIn->Header.TimeStamp;
    pTPOut->Header.FlowControl 	 = pTPIn->Header.FlowControl;
    pTPOut->Checksum 		 = pTPIn->Checksum;

    pTPOut->Data = (uint8_t*)MemAlloc(pTPIn->Header.Size *sizeof(uint8_t));
    if(pTPOut->Data != NULL)
    {
      memcpy(pTPOut->Data, pTPIn->Data, pTPIn->Header.Size);
    }
    if(pTPIn->Data != NULL)
    {
      /* Free allocated memory for input transfer protocol frame */
      MemFree(pTPIn->Data);
      pTPIn->Data = NULL;
    }

    return ret;
}

/**
  * @brief  	Main transfer protocol routine
  * @details	Data inside the transfer protocol is processed and a new
  *		message is generated
  * @param[out] TPFrameDest	Transfer protocol frame to be created
  * @param[in]  TPFrameSrc 	Transfer protocol frame to be processed
  * @retval	Return the destination interface if the frames have been processed
  *		successfully.
  */
int32_t TransferProtocolProcess(TransProtFrame *TPFrameDest, TransProtFrame *TPFrameSrc)
{
    uint32_t DestFrameSize;
    uint8_t DestNode;
    int32_t InterfaceLink = -1; /* Interface where the msg has to be sent */
    TransProtFrame *TPIn = TPFrameSrc;
    TransProtFrame *TPOut = TPFrameDest;

    /* Check if the msg is for this node */
    DestNode = GetDestLogicalIdP(TPIn);
    if(DestNode == LogicalID)
    {
      /* Check the transfer protocol command, and execute the operation */
      switch(GetFrameCommandP(TPIn))
      {
        case TRANSFER_COMMAND:
          /* This commands means that the received data goes to
           * an specific interface of this device */
          TransferProtocolCopy(TPOut, TPIn);
    
          /* Check what interface should send the message */
          InterfaceLink = (int32_t)GetDestInterfaceIdP(TPIn);
          break;
        case CONFIG_COMMAND:
          /* Process the Config protocol frame */
          DestFrameSize = ConfigProtocolProcess(&(TPOut->Data),TPIn->Data, TPIn->Header.Size);

          /* Process output to generate Transfer protocol header */
          TPOut->Header.DestinationID = TPIn->Header.SourceID;
          TPOut->Header.Command = CONFIG_COMMAND;
          TPOut->Header.SourceID = SetLogicalId(LogicalID);
          /* Check to which interface is linked the requested frame */
          TPOut->Header.SourceID |= (uint8_t)GetDestInterfaceIdP(TPIn);

          TPOut->Header.FlowControl = TPIn->Header.FlowControl;
          TPOut->Header.TimeStamp= TPIn->Header.TimeStamp;
          TPOut->Header.Size = DestFrameSize;
          TPOut->Checksum = 0;

          /* Update return value for upper functions */
          InterfaceLink = (int32_t)GetDestInterfaceIdP(TPIn);
          break;

        case OPERATION_COMMAND:
          DestFrameSize = OperationProtocolProcess(&(TPOut->Data),TPIn->Data, TPIn->Header.Size);

          /* Process output to generate Transfer protocol header */
          TPOut->Header.DestinationID = TPIn->Header.SourceID;
          TPOut->Header.Command = OPERATION_COMMAND;
          TPOut->Header.SourceID = SetLogicalId(LogicalID);
          /* Check to which interface is linked the requested frame */
          TPOut->Header.SourceID |= (uint8_t)GetDestInterfaceIdP(TPIn);;
          TPOut->Header.FlowControl = TPIn->Header.FlowControl;
          TPOut->Header.TimeStamp= TPIn->Header.TimeStamp;
          TPOut->Header.Size = DestFrameSize;
          TPOut->Checksum = 0;

          /* Update return value for upper functions */
          InterfaceLink = (int32_t)GetDestInterfaceIdP(TPIn);
          break;

	      default:
          break;
      }
    }
    else
    {
      /* Check if the destination Node ID is linked to some interface */
      InterfaceLink = (int32_t)TransferProtocolGetRouteInterface(DestNode);
      if(InterfaceLink != -1)
      {
          TransferProtocolCopy(TPOut, TPIn);
      }
      else
      {
          /* Generate an error */
      }
    }
    if(TPIn->Data != NULL)
    {
      /* Free allocated memory for input transfer protocol data */
      MemFree(TPIn->Data);
      TPIn->Data = NULL;
    }
    return InterfaceLink;
}

/**
  * @brief Set the IDs of a Transfer protocol frame in function of a Interface
  *        ID
  * @param[out]  TPFrameDest	Transfer protocol frame to be modified
  * @param[in]   InterfaceID	Interface source identification
  * @retval			TBD.
  */
int32_t TransferProtocolSetIDs(TransProtFrame *TPFrameDest, uint8_t InterfaceID)
{
  return 0;
}
/*****************************************************************************/
/* Interface Management */
/*****************************************************************************/

/**
  * @brief  Copy an input transfer protocol into an output transfer protocol
  * @param[out]  TPFrameDest	Transfer protocol frame to be created
  * @param[in]   TPFrameSrc	Transfer protocol frame to be copied
  * @retval 0 if Ok
  */
uint8_t TransferProtocolGetAvailableInterfaces(void)
{
  /* TODO: Add additional protections */
  return AvailableInterfaces;
}

/**
  * @brief  Copy an input transfer protocol into an output transfer protocol
  * @param[out]  TPFrameDest	Transfer protocol frame to be created
  * @param[in]   TPFrameSrc		Transfer protocol frame to be copied
  * @retval 0 if Ok
  */
uint8_t TransferProtocolGetInterfaceType(uint8_t InterfaceID)
{
  /* TODO: Add additional protections */
  return TPIDTable[InterfaceID].InterfaceType;
}
/**
  * @brief  Copy an input transfer protocol into an output transfer protocol
  * @param[out]  TPFrameDest	Transfer protocol frame to be created
  * @param[in]   TPFrameSrc	Transfer protocol frame to be copied
  * @retval 0 if Ok
  */
void TransferProtocolSetInterfaceType(uint8_t InterfaceID, uint8_t type)
{
  /* TODO: Add additional protections */
  TPIDTable[InterfaceID].InterfaceType = type;
}

/**
  * @brief  Update link table
  */
void TransferProtocolUpdateInterfaceState(uint8_t InterfaceID)
{
  if(TPIDTable[InterfaceID].InterfaceType == MBA_BRIDGE)
  {
      TPIDTable[InterfaceID].InterfaceState = GetBusInstanceState(InterfaceID);
  }
}

/**
  * @brief  Update link table
  */
uint8_t TransferProtocolGetInterfaceState(uint8_t InterfaceID)
{
  return TPIDTable[InterfaceID].InterfaceState;
}

/**
  * @brief  Update link table
  */
void TransferProtocolForceInterfaceState(uint8_t InterfaceID,   uint8_t State)
{
      TPIDTable[InterfaceID].InterfaceState = State;
}

/************** Static Functions **********************************/
/**
  * @brief  Routine to get links between IDs
  * @param[in]  ID	Source ID in any format (Interface, Scan, Logical & Linked)
	* @param[in]  Mode Link relationship
  * @retval ID in the desired format
  */
int16_t TransferProtocolGetRouteInterface(uint16_t DestLogicalID)
{
    uint8_t TableIndex = 0, InterfaceCount;
    int16_t retID = -1;
    for(InterfaceCount = 0; InterfaceCount < AVAILABLE_INTERFACES; InterfaceCount++)
    {
      while((RouteTableLink[InterfaceCount].LinkedLogicalID[TableIndex] != 0xFF) &&
            (RouteTableLink[InterfaceCount].LinkedLogicalID[TableIndex] != DestLogicalID))
      {
        TableIndex++;
      }
      if (RouteTableLink[InterfaceCount].LinkedLogicalID[TableIndex] == DestLogicalID)
      {
        break;
      }
      TableIndex = 0;
    }
    if(InterfaceCount < AVAILABLE_INTERFACES)
    {
      retID = InterfaceCount;
    }
    return retID;
}

/**
  * @brief  Routine to get links between IDs
  * @param[in]  ID	Source ID in any format (Interface, Scan, Logical & Linked)
	* @param[in]  Mode Link relationship
  * @retval ID in the desired format
  */
int16_t TransferProtocolGetIDLink(uint16_t ID, TPLinkModes Mode)
{
    uint8_t TableIndex = 0;
    int16_t retID = -1;
    switch(Mode)
    {
      case INTERFACE_TO_SCAN:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].InterfaceID == ID)
          {
              retID =  TPIDTable[TableIndex].ScanID;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case INTERFACE_TO_LOGICAL:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].InterfaceID == ID)
          {
              retID =  TPIDTable[TableIndex].LogicalID;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case INTERFACE_TO_LINKEDDEV:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].InterfaceID == ID)
          {
              retID =  TPIDTable[TableIndex].LinkedDevice;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case SCAN_TO_INTERFACE:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].ScanID == ID)
          {
              retID =  TPIDTable[TableIndex].InterfaceID;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case SCAN_TO_LOGICAL:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].ScanID == ID)
          {
              retID =  TPIDTable[TableIndex].LogicalID;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case SCAN_TO_LINKEDDEV:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].ScanID == ID)
          {
              retID =  TPIDTable[TableIndex].LinkedDevice;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case LOGICAL_TO_INTERFACE:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].LogicalID == ID)
          {
            retID =  TPIDTable[TableIndex].InterfaceID;
            break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case LOGICAL_TO_SCAN:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].LogicalID == ID)
          {
              retID =  TPIDTable[TableIndex].ScanID;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case LOGICAL_TO_LINKEDDEV:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].LogicalID == ID)
          {
            retID =  TPIDTable[TableIndex].LinkedDevice;
            break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case LINKEDDEV_TO_INTERFACE:
	      while(TableIndex < AvailableInterfaces)
	      {
          if(TPIDTable[TableIndex].LinkedDevice == ID)
          {
              retID =  TPIDTable[TableIndex].InterfaceID;
              break;
          }
          else
          {
              TableIndex++;
          }
	      }
	      break;
      case LINKEDDEV_TO_SCAN:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].LinkedDevice == ID)
          {
              retID =  TPIDTable[TableIndex].ScanID;
              break;
          }
          else
          {
              TableIndex++;
          }
        }
        break;
      case LINKEDDEV_TO_LOGICAL:
        while(TableIndex < AvailableInterfaces)
        {
          if(TPIDTable[TableIndex].LinkedDevice == ID)
          {
            retID =  TPIDTable[TableIndex].LogicalID;
            break;
          }
          else
          {
            TableIndex++;
          }
        }
        break;
      default:
        break;
    }
    return retID;
}

/**
  * @brief  Update link table
  */
void TransferProtocolUpdateLinks(void)
{
  uint8_t index;

  for ( index = 0; index < AVAILABLE_INTERFACES; index++)
  {
      TPIDTable[index].LogicalID = LogicalID + index;
  }
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

