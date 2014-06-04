/*
 * main.c
 *
 *  Created on: 04 июня 2014 г.
 *      Author: igor
 */
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>



#define FOSC 14745600
#define BAUD 19200
//#define MYUBRR FOSC/16/BAUD-1
#define MYUBRR (((((FOSC * 10) / (16L * BAUD)) + 5) / 10) - 1)

void usart_init( unsigned int ubrr);
char usart_getchar(void);
void usart_putchar(char data);
char usart_kbhit(void);
void usart_pstr(char *s);
int usart_putchar_printf(char var, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);

void usart_init( unsigned int ubrr)
{

    // Set baud rate

    UBRR0H = (uint8_t)(ubrr>>8);
    UBRR0L = (uint8_t)ubrr;

    // Enable receiver and transmitter

    UCSR0B = (1<<RXEN0)|(1<<TXEN0);

    // Set frame format: 8data, 1stop bit

    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}


char usart_getchar(void) {

    // Wait for incoming data

    while ( !(UCSR0A & (1<<RXC0) ) );

    // Return the data

    return UDR0;
}

void usart_putchar(char data) {
	//Wait until the transmitter is ready
	while(!(UCSR0A & (1<<UDRE0)))
	{
		;//Do nothing
	}
	//Now write the data to USART buffer
	UDR0=data;
}

char usart_kbhit(void) {

    //return nonzero if char waiting polled version

    unsigned char b;
    b=0;
    if(UCSR0A & (1<<RXC0)) b=1;
    return b;
}

void usart_pstr(char *s) {

    // loop through entire string

    while (*s) {
        usart_putchar(*s);
        s++;
    }
}


// this function is called by printf as a stream handler

int usart_putchar_printf(char var, FILE *stream) {

    // translate \n to \r for br@y++ terminal

    if (var == '\n') usart_putchar('\r');
    usart_putchar(var);
    return 0;
}
unsigned int adc_read(void)
{
	ADCSRA  |= (1<<ADSC);				// Start conversion
	while (ADCSRA &  (1<<ADSC));		// wait until conversion  completes; ADSC=0 means Complete
	return ADCW;
}

void adc_init( void )
{
	ADCSRA |= (1<<ADEN); //Enable the ADC
	ADCSRA |= (1<<ADPS2); //Use prescale factor 16 -> ADC clock is 500kHz
	ADMUX |= (1<<MUX1);	 //Initial channel selection
	ADMUX |= (1<<MUX2);
	ADMUX |= (1<<REFS0); //Set source of reference signal
	ADMUX |= (0<<REFS1);
}


int main(void)
{
	usart_init(MYUBRR);
	adc_init();
	stdout = &mystdout;
	int i=0;
    while(1)
    {
    	printf("%4d ", adc_read());
    	//_delay_ms(1);
    	if (i >= 30)
    	{
    		i = 0;
    		printf("\n");
    	}
    	i++;
	}
}
