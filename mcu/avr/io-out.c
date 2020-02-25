/* Blink an led */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


int main()
{
	/* Configure PB5 (13 on Arduino) to be output. */
	/* IO 13 is connected to the led on board. */
	DDRB |= 0b00100000;
 
	while(1)
	{ 
		/* Set PB5 to HIGH */
		PORTB |= 0b00100000;
      
		/* Wait 500ms */
		_delay_ms(500);
 
		/* Set PB5 to LOW */
		PORTB &= 0b11011111;
      
		/* Wait 500ms */
		_delay_ms(500); 
	}
  
	return 0;
}

