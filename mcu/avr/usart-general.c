/*
	This file is part of mylibc by Augusto Damasceno.
	See: https://github.com/augustomatheuss/mylibc

 	Activate a buzzer with the frequency passed by the user via USART
	The user must send a 6 char with the ffrequency, the maximum is 500000

	State 0 to 5: receive the 6 digits of the frequency
	State 6: send message to the user
*/

/* Using 16MHz Clock */
#define F_CPU 16000000UL
/* Maximum Frequency */
#define MAXIMUM_FREQ 500000
/* Constant to convert period in half period in us */
#define CYCLE_US 500000

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Buffer for the formated message to send */
volatile char buffer[64];
/* Flag to send message to the user */
volatile char send;
/* State of system */
volatile char state;
volatile int frequency;
volatile int cycle;


int main(){
	/* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity. */
	/* RX Complete Interrupt Enable */
	UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0) | (1 << RXCIE0) ;
	UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
	/* Baud Rate Setting for f_osc = 16MHz */
	unsigned int ubrr = 103;
	UBRR0H = ( unsigned char ) ( ubrr>>8) ;
	UBRR0L = ( unsigned char ) ubrr ;

	/* Configure PB1 (9 on Arduino Uno/Duemilanove) to be output. */
	/* This is the signal to the buzzer */
	DDRB |= 0b00000010;

	int index = 0;
	state = 0;
	frequency = 0;
	cycle = 0;
	send = 0;
	char floatString[16];

	/* Format and send the buffer : inital message to the user. */
	sprintf((char*)buffer, "Enter with the frequency with 6 digits. Like: \"000440\" \n\n");
	while(buffer[index] != '\0'){
		while (!( UCSR0A & (1<<UDRE0) )) ;
		UDR0 = buffer[index];
		index++;
	}

	/* Set Global Interrupt Enable. */
	sei();

	while(1){
		/* Send message with frequency and period when the flag send is on. */
		if(send){
    		index = 0;
			/* Format and send the buffer */
			dtostrf(1000000.0/((float)frequency), 16, 8, floatString);
			sprintf((char*)buffer,
				"Frequency: %dHz. Calculated Period: %sus. Real period: %dus\n",
				frequency, floatString, (int)(2*cycle));
			while(buffer[index] != '\0'){
				while (!( UCSR0A & (1<<UDRE0) )) ;
				UDR0 = buffer[index];
				index++;
			}

			send=0;
			state=0;
		}

		/* Generates the signal with cycle delay (half period) */
		PORTB |= 0b00000010;
		for(index=0; index<cycle; index++)
			_delay_us(1);
		PORTB &= 0b11111101;
		for(index=0; index<cycle; index++)
			_delay_us(1);
	}

	return 0;
}


/* When receive data over USART */
ISR(USART_RX_vect)
{
	/* Get the data received from USART */
	char dataChar = UDR0;
	/* Convert char from '0' to '9' in decimal; '0' is 48 */
	int data = dataChar - 48;
	switch(state){
		case 0:
			frequency = data*100000;
			state++;
			break;
		case 1:
			frequency += data*10000;
			state++;
			break;
		case 2:
			frequency += data*1000;
			state++;
			break;
		case 3:
			frequency += data*100;
			state++;
			break;
		case 4:
			frequency += data*10;
			state++;
			break;
		case 5:
			frequency += data;
			state++;
			/* Limit the frequency to MAX_FREQ */
			if (frequency > MAXIMUM_FREQ)
				frequency = MAXIMUM_FREQ;
			cycle = CYCLE_US / frequency;
			send=1;
			break;
	}
}
