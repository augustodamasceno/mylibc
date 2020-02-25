/* Test a SPI Bus - Slave */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Define the number of MCU here (0, 1, 2 or 3) */
#define MCU 0

/* When receive data over SPI */
ISR(SPI_STC_vect)
{
#if MCU == 0
	if (SPDR == '0')
	{
		SPDR = 'A';
	}
	else
	{
		SPDR = '0';
	}
#elif MCU == 1
	if (SPDR == '1')
	{
		SPDR = 'B';
	}
	else
	{
		SPDR = '1';
	}
#elif MCU == 2
	if (SPDR == '2')
	{
		SPDR = 'C';
	}
	else
	{
		SPDR = '2';
	}
#elif MCU == 3
	if (SPDR == '3')
	{
		SPDR = 'D';
	}
	else
	{
		SPDR = '3';
	}
#else
	/* Note that this is a number, not an ascii value */
	SPDR = MCU;
#endif
}

int main()
{
	/* PB3 - MOSI */
	/* PB4 - MISO */
	/* PB5 - SCK */
	/* PB2 - SS */
	DDRB |= 0b00010000;
 
	/* SPI Interrupt Enable */
	/* Slave, SCK = f_osc/4, polarity = 0, phase = 0 */
	SPCR |= (1<<SPIE) | (1<<SPE);
  
	/* Set Global Interrupt Enable */
	sei();

	while(1){}
  
	return 0;
}

