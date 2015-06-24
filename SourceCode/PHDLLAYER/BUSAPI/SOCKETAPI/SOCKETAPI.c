/*
  ******************************************************************************
  * @file    SOCKETAPI.c
  * @author  Javier Fernandez Cepeda
  * @brief   Socket interface: This file implements sockets to give an homogeneous
  * 	     interface that allows communication for multiple applications
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "SocketAPI.h"
#include "../BUSAPI.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_CONNECTIONS_SUPPORTED 	1
#define DEFAULT_PORT			10005
#define MAX_PACKET_SIZE			512
/* Private macro -------------------------------------------------------------*/
/* Global variables ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int ClientSocketDescriptor;
static uint8_t RxBuffer[MAX_PACKET_SIZE];
static uint32_t ReadSize;

/* Private function prototypes -----------------------------------------------*/
int SocketAcceptConnection(void);

/**
  * @brief  Initializes socket interface.
  * @param  None
  * @retval 0 on success
  */
int32_t SocketInit(void)
{
  int sockfd;
  struct sockaddr_in serv_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
      printf("Error");
  }

  bzero((char *) &serv_addr , sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(DEFAULT_PORT);

  if (bind(sockfd, (struct sockaddr *) &serv_addr,
    sizeof(serv_addr)) < 0)
  {
      printf("Error");
  }

  listen(sockfd, MAX_CONNECTIONS_SUPPORTED);

  ClientSocketDescriptor = sockfd;
  return sockfd;
}


/**
  * @brief  Close communication with the client.
  * @param  None
  * @retval None
  */
int32_t SocketDeInit(void)
{
  close(ClientSocketDescriptor);
  return 0;
}

uint32_t SocketDataAvailable(void)
{
  ReadSize = read(ClientSocketDescriptor, RxBuffer, MAX_PACKET_SIZE);
  return ReadSize;
}

uint32_t SocketSizeDataAvailable(void)
{
  return ReadSize;
}

/**
  * @brief  Read data from client.
  * @param  buffer data buffer
  * @param  size   maximum number of bytes to be read
  * @retval Size of the read frame
  */
uint32_t SocketRead(uint8_t *data, uint32_t size)
{
  uint8_t *pTemp = data;

  memcpy(pTemp,RxBuffer, size);

  return ReadSize;
}

/**
  * @brief  Send data to a client.
  * @param  buffer data buffer
  * @param  size   maximum number of bytes to be read
  * @retval Size of the read frame
  */
uint32_t SocketWrite(uint8_t *data, uint32_t size)
{
  uint8_t *pTemp = data;
  uint32_t WrittenSize;

  WrittenSize = write(ClientSocketDescriptor,pTemp, size);

  return WrittenSize;
}

/**
  * @brief  Write data through USB
  * @param  Data: pointer to the destination buffer.
  * @param	 Size: Size of data to read
  * @retval FUNC_OK.
  */
int32_t SocketConfiguration(uint16_t param, void *arg)
{
 int32_t RetValue = 0;
 switch(param)
 {
   case  BUS_FRAME_DETECTION:
     break;
   case  BUS_TIMEOUT:
     break;
   case  BUS_TIMEOUT_DETECTION:
     break;
   case  BUS_FIELD_SIZE_DETECTION:
     break;
   case  BUS_END_FIELD_DETECTION:
     break;
   case ACCEPT_CONNECTION:
     SocketAcceptConnection();
     break;
   default:
     RetValue = -1;
     break;
 }
 return RetValue;
}

/************* Static function description *********************/
/**
  * @brief  Accepts a new client.
  * @param  None
  * @retval 0 on success
  */
int SocketAcceptConnection(void)
{
  socklen_t clilen;
  struct sockaddr_in cli_addr;

  clilen = sizeof(cli_addr);

  ClientSocketDescriptor = accept(ClientSocketDescriptor,
	  (struct sockaddr *) &cli_addr,
	  &clilen);

  return ClientSocketDescriptor;
}
