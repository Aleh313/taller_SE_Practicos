/*
 * sapi_uart.c
 *
 *  Created on: 7 jul. 2021
 *      Author: MARCO
 */

#include "sapi_uart.h"
#include "string.h"
#include "chip.h"
#include "stdint.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

//-------------------------------------------------------------

// Return TRUE if have unread data in RX FIFO
bool_t uartRxReady( uartMap_t uart )
{
	bool_t data_rxbool;
		switch(uart){
				case UART_0:
					data_rxbool = Chip_UART_ReadLineStatus( LPC_UART0 ) & UART_LSR_RDR;
						break;

				case UART_485:
					data_rxbool = Chip_UART_ReadLineStatus( LPC_UART1 ) & UART_LSR_RDR;
						break;
				case UART_2:
					data_rxbool = Chip_UART_ReadLineStatus( LPC_UART2 ) & UART_LSR_RDR;
						break;
				case UART_3:
					data_rxbool = Chip_UART_ReadLineStatus( LPC_UART3 ) & UART_LSR_RDR;
						break;
				default:
						break;
				}

		return data_rxbool;


}

// Return TRUE if have space in TX FIFO
bool_t uartTxReady( uartMap_t uart )
{

	bool_t data_txbool;
			switch(uart){
					case UART_0:
						data_txbool = Chip_UART_ReadLineStatus( LPC_UART0 ) & UART_LSR_THRE;
							break;

					case UART_485:
						data_txbool = Chip_UART_ReadLineStatus( LPC_UART1 ) & UART_LSR_THRE;
							break;
					case UART_2:
						data_txbool = Chip_UART_ReadLineStatus( LPC_UART2 ) & UART_LSR_THRE;
							break;
					case UART_3:
						data_txbool = Chip_UART_ReadLineStatus( LPC_UART3 ) & UART_LSR_THRE;
							break;
					default:
							break;
					}

			return data_txbool;

}

// Read from RX FIFO
uint8_t uartRxRead( uartMap_t uart )
{
	uint8_t datorx;
	switch(uart){
			case UART_0:
					datorx = Chip_UART_ReadByte(LPC_UART0);
					break;

			case UART_485:
					datorx = Chip_UART_ReadByte(LPC_UART1);
					break;
			case UART_2:
					datorx = Chip_UART_ReadByte(LPC_UART2);
					break;
			case UART_3:
					datorx = Chip_UART_ReadByte(LPC_UART3);
					break;
			default:
					break;
			}

	return datorx;
}

// Read all bytes from RX FIFO and discards
void uartRxFlush( uartMap_t uart )
{
   while ( uartRxReady(uart) ) {
      uartRxRead(uart);
   }
}

// Write in TX FIFO
void uartTxWrite( uartMap_t uart, const uint8_t value )
{

	switch(uart){
		case UART_0:
				Chip_UART_SendByte(LPC_UART0,value);
				break;

		case UART_485:
				Chip_UART_SendByte(LPC_UART1,value);
				break;
		case UART_2:
				Chip_UART_SendByte(LPC_UART2,value);
				break;
		case UART_3:
				Chip_UART_SendByte(LPC_UART3,value);
				break;
		default:
				break;
		}

}

//-------------------------------------------------------------

// UART Initialization
void uartInit( uartMap_t uart, uint32_t baudRate )
{

	switch(uart){
	case UART_0:
			Chip_UART_Init(LPC_UART0);
			Chip_UART_SetBaud(LPC_UART0, baudRate);
			Chip_UART_SetupFIFOS(LPC_UART0,( UART_FCR_FIFO_EN | UART_FCR_RX_RS |UART_FCR_TX_RS | UART_FCR_DMAMODE_SEL | UART_FCR_TRG_LEV0));
			Chip_UART_ReadByte(LPC_UART0);
			Chip_UART_TXEnable(LPC_UART0);
			break;

	case UART_485:

			Chip_UART_Init(LPC_UART1);
			Chip_UART_SetBaud(LPC_UART1, baudRate);
			Chip_UART_SetupFIFOS(LPC_UART1,( UART_FCR_FIFO_EN | UART_FCR_RX_RS |UART_FCR_TX_RS | UART_FCR_DMAMODE_SEL | UART_FCR_TRG_LEV0));
			Chip_UART_ReadByte(LPC_UART1);
			Chip_UART_TXEnable(LPC_UART1);
			Chip_UART_SetRS485Flags( LPC_UART1,UART_RS485CTRL_DCTRL_EN | UART_RS485CTRL_OINV_1);
			break;
	case UART_2:

			Chip_UART_Init(LPC_UART2);
			Chip_UART_SetBaud(LPC_UART2, baudRate);

			/* Reset FIFOs, Enable FIFOs and DMA mode in UART */
			Chip_UART_SetupFIFOS(LPC_UART2, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |UART_FCR_TX_RS | UART_FCR_DMAMODE_SEL | UART_FCR_TRG_LEV0));
			Chip_UART_ReadByte(LPC_UART2);
			Chip_UART_TXEnable(LPC_UART2);
			break;

	case UART_3:

			Chip_UART_Init(LPC_UART3);
			Chip_UART_SetBaud(LPC_UART3, baudRate);

			/* Reset FIFOs, Enable FIFOs and DMA mode in UART */
			Chip_UART_SetupFIFOS(LPC_UART3, (UART_FCR_FIFO_EN | UART_FCR_RX_RS |UART_FCR_TX_RS | UART_FCR_DMAMODE_SEL | UART_FCR_TRG_LEV0));
			Chip_UART_ReadByte(LPC_UART3);
			Chip_UART_TXEnable(LPC_UART3);
			break;

	default:
			break;

	}
}



// Read 1 byte from RX FIFO, check first if exist aviable data
bool_t uartReadByte( uartMap_t uart, uint8_t* receivedByte )
{
   bool_t retVal = TRUE;
   if ( uartRxReady(uart) ) {
      *receivedByte = uartRxRead(uart);
   } else {
      retVal = FALSE;
   }
   return retVal;
}

// Blocking Write 1 byte to TX FIFO
void uartWriteByte( uartMap_t uart, const uint8_t value )
{
   // Wait for space in FIFO (blocking)
   while( uartTxReady( uart ) == FALSE );
   // Send byte
   uartTxWrite( uart, value );
}

// Blocking Send a string
void uartWriteString( uartMap_t uart, const char* str )
{
   while( *str != 0 ) {
      uartWriteByte( uart, (uint8_t)*str );
      str++;
   }
}

// Blocking, Send a Byte Array
void uartWriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen )
{
   uint32_t i = 0;
   for( i=0; i<byteArrayLen; i++ ) {
      uartWriteByte( uart, byteArray[i] );
   }
}



