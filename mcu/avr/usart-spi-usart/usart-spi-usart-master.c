#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char data;

/* When receive data over USART */
ISR(USART_RX_vect)
{
  /* Get USART data*/
  data = UDR0;
  /* Set SPI data */
  SPDR = data;
  /* Slave select */
  PORTB &= 0b11111011;
  while (!(SPSR & (1<<SPIF)));
  /* Slave free */
  PORTB |= 0b00000100;
}

int main()
{
  // PB3 - MOSI , PB4 - MISO, PB5 - SCK, PB2 - SS
  DDRB |= 0b00101100;
  /* Slave free */
  PORTB |= 0b00000100;

  /* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity. */
  /* RX Complete Interrupt Enable */
  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0) | (1 << RXCIE0) ;
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
  /* Baud Rate Setting for f_osc = 16MHz */
  unsigned int ubrr = 103;
  UBRR0H = ( unsigned char ) ( ubrr>>8) ;
  UBRR0L = ( unsigned char ) ubrr ;

  /* SPI Interrupt Enable, Master, SCK = f_osc/4, polarity = 0, phase = 0 */
  SPCR |= (1<<SPE) | (1<<MSTR);
  
  sei();
  
  while(1){}

  return 0;
}

