/*
 * uart.h
 *
 * Created: 05.09.2020 13:59:36
 *  Author: marth
 */ 

#ifndef UART_H_
#define UART_H_

// This is the CMD receive buffer, when it is filled we know we have a full CMD
#define CMD_LEN 10		// The full buffer: [CMD_NO, CMD_SUBNO, ARG0, ARG1, ... ]
#define ARG_OFFSET 2	// The offset to get to the first ARG
volatile uint8_t cmd_buffer[CMD_LEN];
volatile uint8_t cmd_receive_counter;

void init_UART();

uint8_t UART_rx_polling();

void UART_tx_polling(uint8_t data);

ISR(USART0_RXC_vect);

// Points to the correct CMDs
#define UART_BASIC_CMD	0	// NOTE: This _must_ be at number 0

#define UART_MCP2515_CMD 2
void UART_execute_cmd();

// Basic commands
// CMD_SUBNO:
//   0: Synchronize - send the number 1. Used to sync the UART protocol
//   1: ECHO - return the full argument
#define UART_BASIC_CMD_SYNCHRONIZE	0	// Note: THIS _must_ be at number 0
#define UART_BASIC_CMD_ECHO			1
void UART_execute_basic_cmd();


// MCP2515 commands
// CMD_SUBNO:
//   0: Read status - Checks if possible to read status of CAN controller
#define UART_MCP2515_CMD_READSTATUS 0
#define UART_MCP2515_CMD_INIT 1
#define UART_MCP2515_CMD_WRITE 2
void UART_execute_mcp2515_cmd();


#endif /* UART_H_ */