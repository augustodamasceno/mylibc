#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char data;

/* When receive data over SPI */
ISR(SPI_STC_vect)
{
   data = SPDR;
   while (!( UCSR0A & (1<<UDRE0) )) ;
   UDR0 = data;
}

int main()
{
  // PB3 - MOSI , PB4 - MISO, PB5 - SCK, PB2 - SS
  DDRB |= 0b00010000;
  
  /* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity */
  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0);
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
  /* Baud Rate Setting for f_osc = 16MHz */
  unsigned int ubrr = 103;
  UBRR0H = ( unsigned char ) ( ubrr>>8) ;
  UBRR0L = ( unsigned char ) ubrr ;
  
  /* SPI Interrupt Enable, Slave, SCK = f_osc/4, polarity = 0, phase = 0 */
  SPCR |= (1<<SPIE) | (1<<SPE);
  
  /* Set Global Interrupt Enable */
  sei();

  while(1){}
  
  return 0;
}

