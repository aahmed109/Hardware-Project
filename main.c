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

unsigned char obs[32];
unsigned char person1[32];
unsigned char person2[32];
unsigned char jPerson1[32];
unsigned char jPerson2[32];

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
	0b00011000,
	0b00100100,
	0b01000010,
	0b00100100,
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
	0b01000010,
	0b00101010,
	0b00011000,
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
	0b10010010,
	0b10000010,
	0b00000000,
0b00000000};
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
	0b11111000,
	0b11111110,
	0b11111000
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
	0b01111100,
	0b11111111,
	0b00111111,
	0b11111010,
	0b00001010,
	0b00001010, //matrix 1
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
	for(int i = 0; i < 70; i++){
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

void MoveLeft(){
	if(obstacle[0]) return;
	if(px==13) {
		obstacle[7]=obstacle[18];
		obstacle[18]=0;		
		obstacle[6]=obstacle[17];
		obstacle[17] =0;
		obstacle[5] = obstacle[16];
		obstacle[16]=0;
		//px=0;
	}
	
	
	unsigned char a = obstacle[0];
	unsigned char b = obstacle[1];
	unsigned char c = obstacle[2];
	for(int i=1; i<32; i++){
		//if(i<=7||i>16){
			obstacle[i-1]=obstacle[i];
		//}
		/*else{
			
		}*/
		
	}
	px++;
	//obstacle[29] = a;
	//obstacle[30] = b;
	obstacle[31] = a;
	a=b;
	b=c;
	c=0;
	//obstacle[31] = 0;
	if(px>17) 
	{
		for (int i=0;i<32;i++){
			obstacle[i] = obs[i];
		}
		px=0;
	}
	
	char buffer[1];
	itoa(px,buffer);
	Lcd4_Write_String(buffer);
	
	return;
}
void MoveUp(){
	unsigned char a[32];
	if(py>=7&& pym<7){MoveDown();}
	
	else if(py>=7 && pym>=7) {py =0; pym = 0; return;}
	
	else{
	for(int i=8; i<16; i++){

		unsigned char cat = right_rotate_dig(person[i]);
		person[i]>>=1;
		
		jPerson[i]>>=1;
		jPerson[i]=jPerson[i]|cat;
		//cat = 0x00;
		//jPerson[i] = 0b11111111;
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

void Draw(){
	for(int8_t j = 0; j < 32; j++){
		pickColumn(j);
		
		PORTB = person[j]|road[j]|obstacle[j];
		PORTC = jPerson[j];
		_delay_ms(1);
	}
}

int main(void)
{
    MCUCSR = 1<<JTD;
   	MCUCSR = 1<<JTD;
	unsigned int result;
	float voltage;
	DDRA = 0xff;// Column mux
	DDRC = 0xff;// Row
	DDRB = 0xff;// Row
	DDRD = 0xff;// LCDs
	ADMUX = 0b01100101;
	ADCSRA = 0b10000111;

	Lcd4_Init();
	Lcd4_Clear();
	//Lcd4_Set_Cursor(1,1);
	//Lcd4_Write_String("Patience!!");
	//_delay_ms(5000);
	Lcd4_Clear();
	for(int i = 0; i<32; i++) {obs[i]= obstacle[i];}
	for(int i=0;i<32;i++) {person1[i]=person[i]; person2[i] = person[i];}
	init();
    while (1) 
    {
		Lcd4_Set_Cursor(1,1);
		
		Lcd4_Write_String("Patience!!");
		result = ADCL;
		result = (result>>6) | (ADCH<<2);
		voltage = (float)result*5.0/1024.0;
		//if(voltage >3.0){MoveLeft();}		
		Draw();
		//if(voltage >0.0){MoveLeft();}
		MoveLeft();
		MoveUp();
		//MoveDown();
    }
}

