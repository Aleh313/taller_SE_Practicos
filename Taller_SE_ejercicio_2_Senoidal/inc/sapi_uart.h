/*
 * sapi_uart.h
 *
 *  Created on: 7 jul. 2021
 *      Author: MARCO
 */
#include <sapi_datatypes.h>
#include "chip.h"
#include "stdint.h"

#ifndef SAPI_UART_H_
#define SAPI_UART_H_

/*==================[external functions declaration]=========================*/

// Return TRUE if have unread data in RX FIFO
bool_t uartRxReady( uartMap_t uart );

// Return TRUE if have space in TX FIFO
bool_t uartTxReady( uartMap_t uart );

// Read from RX FIFO
uint8_t uartRxRead( uartMap_t uart );

// Read all bytes from RX FIFO and discards
void uartRxFlush( uartMap_t uart );

// Write in TX FIFO
void uartTxWrite( uartMap_t uart, uint8_t value );

//-------------------------------------------------------------
// UART Initialization
void uartInit( uartMap_t uart, uint32_t baudRate );


// Read 1 byte from RX FIFO, check first if exist aviable data
bool_t uartReadByte( uartMap_t uart, uint8_t* receivedByte );
// Blocking, Write 1 byte to TX FIFO
void uartWriteByte( uartMap_t uart, const uint8_t value );

// Blocking, Send a string
void uartWriteString( uartMap_t uart, const char* str );

// Blocking, Send a Byte Array
void uartWriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen );

#endif /* SAPI_UART_H_ */
