/* Send "Hi!\n" every 500ms through USART */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


/* Send and receive one byte over USART. */
unsigned char usartByte(unsigned char value)
{
   while (!( UCSR0A & (1<<UDRE0) )) ;
   UDR0 = value;
   value = UDR0;
   return value;
}


int main()
{
  /* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity. */
  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0);
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
  /* Baud Rate Setting for f_osc = 16MHz */
  unsigned int ubrr = 103;
  UBRR0H = ( unsigned char ) ( ubrr>>8) ;
  UBRR0L = ( unsigned char ) ubrr ;
  
  /* Set Global Interrupt Enable */
  sei();
  
  while(1)
  { 
    usartByte('H');
    usartByte('i');
    usartByte('!');
    usartByte('\n');
      
    /* Wait 500ms */
    _delay_ms(500);  
  }
  
  return 0;
}
