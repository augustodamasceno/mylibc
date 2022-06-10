#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char value;

/* When receive data over USART */
ISR(USART_RX_vect)
{
  value = UDR0;
  
  if(value == 'O')
  {
    /* Relay Mode ON */
    PORTB |= 0b00000001; 
  }
  else if(value == 'F')
  {
    /* Relay Mode OFF */
    PORTB &= 0b11111110;
  }
}

/* If you want to reply. */
void usartSendByte(unsigned char response)
{
   while (!( UCSR0A & (1<<UDRE0) )) ;
   UDR0 = response;
}


int main()
{
  /* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity. */
  /* RX Complete Interrupt Enable */
  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0) | (1 << RXCIE0) ;
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
  /* Baud Rate Setting for f_osc = 16MHz */
  unsigned int ubrr = 103;
  UBRR0H = ( unsigned char ) ( ubrr>>8) ;
  UBRR0L = ( unsigned char ) ubrr ;
  
  /* Set Global Interrupt Enable. */
  sei();
  
  /* Configure PB0 (8 on Arduino) to be output. */
  /* This is the signal to control the relay */
  DDRB |= 0b00000001;
  
  while(1)
  { 
    /* System Loop */
  }
  
  return 0;
}

