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
//	MCUCSR = 1<<JTD;
//	MCUCSR = 1<<JTD;
	DDRA = 0x00;
	DDRB = 0xff;
//	DDRD = 0b01111111;
//	DDRC = 0b11111111;
	unsigned char c;
    while (1) 
    {
		/*if(PIND & (PD0) == 1){
			PORTA |= (1<<PA5);
			PORTC |= (1<<PC0);
		}*/
		c = PINA;
		PORTB =c;
    }
}

