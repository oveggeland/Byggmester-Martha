/*
 * uart.c
 *
 * Created: 05.09.2020 13:59:53
 *  Author: marth
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define F_CPU	4915200
#define BAUD	9600
#define MYUBRR	F_CPU/16/BAUD-1

#include <util/delay.h>

#include "../inc/uart.h"

// NOTE: This has not been verified to work after refactoring, but I think
// it should work just fine.
ISR(USART0_RXC_vect){
	cli();

	sei();
}

void init_UART(){
	// Set Baudrate
	UBRR0L = MYUBRR;

	// Enable RX and TX
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);

	// Set frame format: 8data, 2stop bit
	UCSR0C = (1<<URSEL0) | (1<<USBS0) | (3<<UCSZ00);
	
	// Enable RX interrupt
	UCSR0B |= (1<<RXCIE0);
}

// receives one byte in polling mode
uint8_t UART_rx_polling(){
	// Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0) ));
	
	// Get data from UART and return
	return UDR0;
}

// transmits one byte in polling mode
void UART_tx_polling(uint8_t data){
	// Wait for empty transmit buffer
	while ( !(UCSR0A & (1<<UDRE0) ));
	
	// Put data into buffer, sends the data
	UDR0 = data;
}