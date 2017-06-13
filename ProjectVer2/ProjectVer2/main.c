/*
 * ProjectVer2.c
 *
 * Created: 10/06/2017 7:54:31 PM
 * Author : Ahmed
 */ 

#define F_CPU 1000000UL
#define F_CPU 1000000UL
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTD0
#define EN eS_PORTD1

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
int px;
int py;
int pym;
int hit;
int score;
int times;
int jumping;
int delayer;
unsigned char obs[32];
unsigned char person1[32];
unsigned char person2[32];
unsigned char jPerson1[32];
unsigned char jPerson2[32];

unsigned char all[] = {
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111
	};

unsigned char dino[] = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b01111110,
	0b01000010,
	0b00100100,
	0b00011000,
	0b00000000,
	0b01111110,
	0b00000000,
	0b01111110,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01111110,
	0b00000000,
	0b00111100,
	0b01000010,
	0b01000010,
	0b01000010,
	0b00111100,
	0b00000000,
	0b00000000
};

unsigned char game[] = {0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00111100,
	0b01000010,
	0b01001010,
	0b00111010,
	0b00000000,
	0b00000000,
	0b01111100,
	0b00100010,
	0b01111100,
	0b00000000,
	0b01111110,
	0b00000100,
	0b00001000,
	0b00000100,
	0b01111110,
	0b00000000,
	0b01111110,
	0b01010010,
	0b01000010,
	0b00000000,
	0b00000000
};

unsigned char over[] = {0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00111100,
	0b01000010,
	0b01000010,
	0b01000010,
	0b00111100,
	0b00000000,
	0b00111110,
	0b01000000,
	0b00111110,
	0b00000000,
	0b01111110,
	0b01010010,
	0b01000010,
	0b00000000,
	0b01111100,
	0b00100010,
	0b00110010,
	0b01101100,
	0b00000000,
	0b10111110,
	0b00000000
};
unsigned char road[] = {
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000,
	0b10000000
};

unsigned char obstacle[] = {	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b11110000,
	0b11111000,
	0b11110000
};

unsigned char jPerson[] = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000, //matrix 1
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};
unsigned char person[] = {
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b10000000,
	0b01110000,
	0b11111100,
	0b01111100,
	0b11111100,
	0b00101000,
	0b00101000,
	0b00000000, //matrix 1
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000,
	0b00000000
};

unsigned char right_rotate_dig(unsigned char a){
	return (((a & 00000001)<<7)& 0xFF);
}

unsigned char left_rotate_dig(unsigned char a){
	return (((a & 10000000)>>7));
}

void pickColumn(int8_t colNum){
	PORTA = (PORTA & 0b11100000) | colNum;
}

void clearColumn(){
	for(int i = 0; i < 32; i++){
		dino[i] = 0b00000000;
		game[i] = 0b00000000;
	}
}

void init(){
	for(int i = 0; i < 100; i++){
		for(int8_t j = 0; j < 32; j++){
			pickColumn(j);
			//PORTB = 0X00;
			PORTC = dino[j];
			//PORTC = 0X00;
			PORTB = game[j];
			_delay_ms(1);
		}
	}
}

void drawOver(){
 while(1){
	for(int8_t j = 0; j < 32; j++){
		pickColumn(j);
		//PORTB = 0X00;
		PORTC = game[j];
		//PORTC = 0X00;
		PORTB = over[j];
		_delay_ms(1);
	}
	 
 }	
}

void MoveLeft(){
	
	for (int i = 1; i < 32; i++)
	{
		if (i == 16)
		{
			obstacle[7] = obstacle[16];
		}
		else
		{
			obstacle[i-1] = obstacle[i];
		}
	}
	obstacle[31] = obstacle[0];
		
	char buffer[1];
	itoa(px,buffer);
	Lcd4_Write_String(buffer);
	
	return;
}
void MoveUp(){
	unsigned char a[32];
	if(py>=10 && pym<10){MoveDown();}
	
	else if(py>=10 && pym>=10) {py =0; pym = 0; return;}
	
	else{
	for(int i=8; i<16; i++){

		unsigned char cat = right_rotate_dig(person[i]);
		person[i]>>=1;
		
		jPerson[i]>>=1;
		jPerson[i]=jPerson[i]|cat;
	}
	py++;
	}
	return;
}
void MoveDown(){
	//unsigned char person1[]=person;
	for(int i=8; i<16; i++){
		unsigned char bat = left_rotate_dig(jPerson[i]);
		jPerson[i]<<=1;
		person[i]<<=1;
		person[i] = person[i]|bat;
	}
	pym++;
	return;
}

void drawAll(){
	for(int8_t j = 0; j < 32; j++){
		pickColumn(j);
		
		PORTB = all[j];
		PORTC = all[j];
		
		_delay_ms(1);
	}
}
void Draw(){
	for(int8_t j = 0; j < 32; j++){
		pickColumn(j);
		
		PORTB = person[j]|road[j]|obstacle[j];
		PORTC = jPerson[j];
		if((person[j+8] & obstacle[j]) != 0) {hit = 1;}
		_delay_ms(1);
	}
}

int main(void)
{
    MCUCSR = 1<<JTD;
   	MCUCSR = 1<<JTD;
	unsigned int result;
	float voltage;
	DDRA = 0b00011111;// Column mux & jump input
	DDRC = 0xff;// Row
	DDRB = 0xff;// Row
	DDRD = 0xff;// LCDs
	//ADMUX = 0b01100101;
	//ADCSRA = 0b10000111;

	//Lcd4_Init();
	//Lcd4_Clear();
	//Lcd4_Set_Cursor(1,4);
	//Lcd4_Write_String("New Game!!");
	//_delay_ms(5000);
	//Lcd4_Clear();
	for(int i = 0; i<32; i++) {obs[i]= obstacle[i];}
	for(int i=0;i<32;i++) {person1[i]=person[i]; person2[i] = person[i];}
	init();
	int k = 2;
    while (1) 
    {
		times++;
		if(times >= 100) {score++; times = 0;}//this will go to other atmel program too
		/*Lcd4_Set_Cursor(2,1);
		
		result = ADCL;
		result = (result>>6) | (ADCH<<2);
		voltage = (float)result*5.0/1024.0;
		//if(voltage >3.0){MoveUp();}*/		
		
		for (int q = 0; q<3;q++)
		{
			Draw();
		}
		//if (hit == 2) {for (int i = 0; i < 100; i++) Draw(); hit = 1;}
		if(hit == 1) {while(1) {
			drawOver();
			/*pickColumn(0);
			PORTB = 0xFF;
			PORTC = 0xFF;*/
			}}
			
		/*if(delayer == 1) {MoveLeft(); delayer = 0;}
		else delayer = 1;*/
		MoveLeft();
		if(jumping==0){
			if((PINA & (1<<PA5)) == 32) {
				 jumping =1;
			}
		}
		else{
			MoveUp();
			jumping++;
			if (jumping>20)
			{
				jumping = 0;
				py=0;pym=0;
			}
		}
		//MoveDown();
    }
	//drawOver();
}

