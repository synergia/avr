/* Project info here */

#include <avr/io.h>
#include <util/delay.h>
#include "../lib/lcd/lcd.h"
#include "mouse.h"


int main(void){

	int x=0;
	int y=0;
	
	PosDelta delta;
	MouseData data;
	LCD lcd;


	lcd.cursorOff();
	lcd << "Synergia 2011";
	lcd.gotoxy(0,1);
	for (a=0; a<16; a++)
	{
		lcd << "*";
		_delay_ms(150);
	}
	lcd.clear();
	
	
	for(;;)
	{	
		
		mouse >> delta;
		x+=delta.x;
		y+=delta.y;
		
		lcd.gotoxy(0,0);
		lcd << "x:";
		lcd << (int)x/40;
		lcd << "  ";
		
		
		lcd.gotoxy(0,1);
		lcd << "y:";
		lcd << (int)y/40; 
		lcd << "  ";
		
		mouse >> data;
		lcd.gotoxy(6,0);
		lcd << "Qual: ";
		lcd << (int)(unsigned char)data.qual;
		lcd << "     ";
		
		if (!(PINB & (1<<2)))
		{
			x=0;
			y=0;
		}
		
	}
    return 0;
}
