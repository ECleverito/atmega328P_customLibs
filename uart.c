
#include <stdlib.h>
#include <avr/io.h>

#ifndef UART_H
#define UART_H

//F_CPU must be defined, as it is used in setbaud.h to set up baud rate config. Same with BAUD a few lines down.
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#include <util/setbaud.h>

void uart_init(void) {
	//UBRR0H and UBRR0L are higher 4 bits and lower 8 bits of register
	//for configuring baud rate of USART communications
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    
//May have to set this value of the control register
//if conditions apply (see util/setbaud.h).
	#if USE_2X
		UCSR0A |= _BV(U2X0);
	#else
		UCSR0A &= ~(_BV(U2X0));
	#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */ 
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */    
}

void uart_putchar(char c) {
    if (c == '\n') {
        uart_putchar('\r');
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
	
	//could also wait until transmission is complete before exiting this function:
	//	UDR0 = c;
	//	loop_until_bit_is_set(UCSR0A, TXC0);
}

char uart_getchar() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void uart_putstr(char *data) {
    // Loop until end of string writing char by char.
    while((*data!='\n')&&(*data!='\0'))
	{
      uart_putchar(*data++);
    }
	
	uart_putchar('\n');
}

//Remember to free up memory that this function points to.
//The input string length is currently limited to 20 characters.
char* uart_getstr()
{
	char *stringLoc;
	stringLoc = (char*) malloc(21*sizeof(char));
	
	for(int i=0;i<21;i++)
	{
		*(stringLoc+i) = uart_getchar();
		uart_putchar(*(stringLoc+i));
		if(*(stringLoc+i)=='\r')
		{
			*(stringLoc+i) = '\0';
			return stringLoc;
		}
	}
	
}

#endif
