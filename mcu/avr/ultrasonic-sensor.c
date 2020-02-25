/* Configure and send "Distance: %d cm\n" through USART */

/* Ultrasonic ranging module HC - SR04 provides */
/* 2cm - 400cm non-contact  measurement function, */
/* the ranging accuracy can reach to 3mm */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


/* String buffer */
char buffer[32];

/* States */
volatile unsigned char state; 

/* Counter */
volatile unsigned int counter;

/* Const to convert clock of counter to uS */
volatile float constClock2uSec = 0.5;  

/* Pulse of 10uS to the trigger */
void sendTrigger()
{
  /* Set PB0 to HIGH */
  PORTB |= 0b00000001;

  /* Wait 10us */
  _delay_us(10);

  /* Set PB5 to LOW */
  PORTB &= 0b11111110;
}

/* Send the buffer over USART */
unsigned char usartString()
{
  unsigned char c = 0;
  while( buffer[c] != '\0' )
  {
    while (!( UCSR0A & (1<<UDRE0) )) ;
    UDR0 = buffer[c];
    c++;
  }

}

/* External Interrupt for echo */
ISR(INT0_vect)
{
  switch(state)
  {
    case 0:
      /* State = 0, do nothing*/
      break;
    case 1:
      /* State = 1, begin of echo pulse */
      state = 2;
      /* Reset counter and wait to next interruption */
      TCNT1 = 0;  
      break;
    case 2: 
      /* State = 2, end of echo pulse */
      state = 0;
      /* Get counter */
      counter = TCNT1;
      /* Calculate time and format the buffer */
      sprintf(buffer,"Distance: %d cm\n",(int)( (constClock2uSec*((float)counter))/58 ));
      /* Send buffer through USART */
      usartString();
      break;
    default:
      break;
  } 
}


int main()
{
  /* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity */
  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0);
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
  /* Baud Rate Setting for f_osc = 16MHz */
  unsigned int ubrr = 103;
  UBRR0H = ( unsigned char ) ( ubrr>>8) ;
  UBRR0L = ( unsigned char ) ubrr ;
  
  /* Configure External Interrupt */
  EICRA |= (1 << ISC00);
  EIMSK |= (1 << INT0);

  /* TIMER1 - Normal, Prescaling = 8*/
  TCCR1B |= (1 << CS11);

  /* Set Global Interrupt Enable */
  sei();

  /* Configure PB0 (trigger) to be output */
  /* PD2 (echo) is input by default  */
  DDRB |= 0b00000001;

  /* Initial values */ 
  state = 0;
  buffer[0] = '\0';

  while(1)
  { 
    sendTrigger();
    state = 1;
  
    /* Wait 60ms */
    _delay_ms(60);
  }
  
  return 0;
}

