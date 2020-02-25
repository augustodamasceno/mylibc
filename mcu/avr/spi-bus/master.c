/* Test a SPI Bus - Master */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main()
{
	/* PB3 - MOSI */
	/* PB4 - MISO */
	/* PB5 - SCK */
	DDRB |= 0b00101000;
	/* SS MCU 0 - PD2 */	
	DDRD |= 0b00000100;
	PORTD |= 0b00000100;
	/* SS MCU 1 - PD4 */
	DDRD |= 0b00010000;
	PORTD |= 0b00010000;
	/* SS MCU 2 - PD7 */
	DDRD |= 0b10000000;
	PORTD |= 0b10000000;
	/* SS MCU 3 - PB0 */
	DDRB |= 0b00000001;
	PORTB |= 0b00000001;

	/* Uncomment the following 2 lines to use SPI Interruption */
	/* SPCR |= (1<<SPE) | (1<<MSTR); */
	/* sei(); */
  
	while(1)
	{
		/* Send '0' to MCU 0*/
		/* Set SPI data */
		SPDR = '0';
		/* Slave select */
		PORTD &= 0b11111011;
		/* Wait for transmission complete */
		while (!(SPSR & (1<<SPIF)));
		/* Slave free */
		PORTD |= 0b00000100;

		/* Response of MCU 0 in SPDR register! */

		/* Send '1' to MCU 1 */
		/* Set SPI data */
		SPDR = '1';
		/* Slave select */
		PORTD &= 0b11101111;
		/* Wait for transmission complete */
		while (!(SPSR & (1<<SPIF)));
		/* Slave free */
		PORTD |= 0b00010000;

		/* Response of MCU 1 in SPDR register! */

		/* Send '2' to MCU 2*/
		/* Set SPI data */
		SPDR = '2';
		/* Slave select */
		PORTD &= 0b01111111;
		/* Wait for transmission complete */
		while (!(SPSR & (1<<SPIF)));
		/* Slave free */
		PORTD |= 0b10000000;

		/* Response of MCU 2 in SPDR register! */

		/* Send '3' to MCU 3*/
		/* Set SPI data */
		SPDR = '3';
		/* Slave select */
		PORTB &= 0b11111110;
		/* Wait for transmission complete */
		while (!(SPSR & (1<<SPIF)));
		/* Slave free */
		PORTB |= 0b00000001;

		/* Response of MCU 3 in SPDR register! */
		
		/* Wait 1000ms */
		_delay_ms(1000);	
	}

	return 0;
}

