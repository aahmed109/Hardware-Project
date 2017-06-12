/*
 * GccApplication2.c
 *
 * Created: 9/06/2017 2:44:29 AM
 * Author : Ahmed
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00;
	DDRB = 0xff;
	unsigned char c;
    while (1) 
    {
		c = PINA;
		PORTB =c;
    }
}

