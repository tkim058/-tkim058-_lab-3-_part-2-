/*
 * [tkim058]_lab[3]_part[2].c
 * Partner(s) Name & E-mail: MinHwan Oh
 * Lab Section: B01
 * Assignment: Lab #3  Exercise #2
 * Exercise Description: [Fuel Sensor]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work.
 */

#include <avr/io.h>
enum States{Start, Init, Wait, Add, Subtract}state;
unsigned char tmpC;

void Tick()
{
	
	switch(state)
	{
		case Start:
		tmpC = 7;
		PORTC = tmpC;
		state =Wait;break;
		case Init:
		state = Wait;
		tmpC = 0;
		break;
		case Wait:
		if((PINA & 0x01) && (PINA & 0x02))
		{
			state = Init;
		}
		else if((PINA & 0x01) && !(PINA & 0x02))
		{
			state = Add;
		}
		else if(!(PINA & 0x01) && (PINA & 0x02))
		{
			state = Subtract;
		
		}
		break;
		case Add:
		tmpC=(tmpC<9)?tmpC+1:tmpC;
		
		if((PINA & 0x01) && (PINA & 0x02))
		{
			state = Init;
		}
		else if(!(PINA & 0x01) && (PINA & 0x02))
		{
			state = Subtract;
		}
		else if(!(PINA & 0x01) && !(PINA & 0x02))
		{
			state = Wait;
		}
		PORTC = tmpC;
		break;
		case Subtract:
		tmpC = (tmpC > 0) ? tmpC-1:tmpC;
		
		if((PINA & 0x01) && (PINA & 0x02))
		{
			state = Init;
		}
		else if((PINA & 0x01) && !(PINA & 0x02))
		{
			state = Add;
		}
		else if(!(PINA & 0x01) && !(PINA & 0x02))
		{
			state = Wait;
		}
		PORTC = tmpC;
		break;
		
		default:
		state = Start;
		break;
	}
	switch (state) {
		case Init:  
		tmpC = 0;                         
		PORTC = tmpC; break;                
		default:
		break;
	}
}
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
    while (1) 
    {
		Tick();
	}
		
}

