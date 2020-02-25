/* 
 * Signal Generator with Arduino UNO (ATMEGA328P)
 * Signal of 8MHz to 1 Hz in PB1 (Port 9 in Arduino Uno) 
 * The frequency is selected with a potentiometer connected to A0 (ANALOG IN 0 in Arduino Uno)
 * The AD value and the frequency is send via text message via serial USART (Baud Rate of 9600)
 * PD2 (Port 2 in Arduino Uno) to the ground lock the selected freqency
 */

#define F_CPU 16000000UL
#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD- 1

#include <avr/io.h>

char buffer[32];
int ad;
int freq;

int main()
{
  /* Configure PB1 (9 on Arduino) is the counter 1 output A. */
  DDRB |= 0b00000010;

  /* Configure PD2 as pul-up input to lock the frequency update */
  DDRD &=  0b00000100;
  PORTD |= 0b00000100;

  /* Counter 0 to send text message via serial by interruption () */
  TCCR0B |= (1 << CS00) | (1 << CS02);
  TIMSK0 |= (1 << TOIE0);
  sei();

  /* Counter 1 to generate the frequency with Fast PWM with TOP on ICR1 and No Clock Prescaler (16 MHz) */
  TCCR1A |= (1 << COM1A1) |  (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10);
  ICR1 = 20000;
  OCR1A = 10000;

  /* USART - Character Size - 8, Stop Bit - 1, Baud Rate 9600, No Parity */
  UCSR0B |= ( 1 << RXEN0) | ( 1 << TXEN0);
  UCSR0C |= ( 1 << UCSZ01 ) | ( 1 << UCSZ00 ) | ( 1 << USBS0) ;
  /* Baud Rate Setting for f_osc = 16MHz */
  unsigned int ubrr = 103;
  UBRR0H = ( unsigned char ) ( ubrr>>8) ;
  UBRR0L = ( unsigned char ) ubrr ;

  /* AD configuration: Voltage Reference = AVCC. Input Channel = ADC0. ADC Enable. ADC Prescaler = 128 (125 KHz). */ 
  ADMUX |= (1<<REFS0);
  ADCSRA |= (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);

  while (1)
  {
    /* Stop interruption for ad and freq updates */
    cli();
    
    /* Start conversion */
    ADCSRA |= 0b01000000;
    /* Wait conversion */
    while ( !(ADCSRA & (1 << ADIF)) ){}
    /* Get AD conversion result */
    ad = ADC;

    /* Update TOP of counter and set pulse width to 50% based on AD range */
    if ((PIND &= 0b00000100) == 0)
    {
      ICR1 = (int) (2.0+ad*64.06) ;
      OCR1A = ICR1/2;
      freq = FOSC / (ICR1 + 1) ;
    }

    /* Start interruption */
    sei();
  }

  return 0;
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

/* Interruption to send text message via serial (overflow of counter 0) */
ISR(TIMER0_OVF_vect)
{
  /* Print value in serial buffer text */
  if ((PIND &= 0b00000100) == 0)
  {
    sprintf(buffer,"AD: %d and Frequency: %d Hz << Frequency Update Blocked! >>\n",ad,freq);
  }
  else
  {
    sprintf(buffer,"AD: %d and Frequency: %d Hz\n",ad,freq);
  }
            
  /* Send buffer through USART */
  usartString();
}
