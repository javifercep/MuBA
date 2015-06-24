/*
  ******************************************************************************
  * @file    SocketAPI.h
  * @author  Javier Fernandez Cepeda
  * @brief   Socket interface: This file implements sockets to gice an homogeneous
  * 	     interface that allows communication for multiple applications
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SOCKETAPI_H_
#define SOCKETAPI_H_

/* Includes ------------------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/
#define ACCEPT_CONNECTION	0x0001
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int32_t SocketInit(void);
int32_t SocketDeInit(void);

/* Communication functions */
uint32_t SocketDataAvailable(void);
uint32_t SocketSizeDataAvailable(void);
uint32_t SocketRead(uint8_t *data, uint32_t size);
uint32_t SocketWrite(uint8_t *data, uint32_t size);

/* Configuration functions */
int32_t SocketConfiguration(uint16_t param, void *arg);

#endif /* SRC_SOCKETINTERFACE_SOCKETINTERFACE_H_ */
