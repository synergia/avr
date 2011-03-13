/* Project info here */

#include <avr/io.h>
#include <util/delay.h>
#include "../lib/lcd/lcd.h"
#include "mouse.h"


int main(void){
    	

	char a=0;
	int x=0;
	int y=0;
	
	Pos_Delta delta;
	Mouse_Data data;
	
	MOUSE mouse;
	LCD lcd;
	
	lcd.cursorOff();
	lcd.gotoxy(0,0);
	lcd.clear();
	
	
	//a = mouse_read(0x00);
	//a |= 0x01;
	//mouse_write(0x00, a);
	
	
	for(;;)
	{	
		
		mouse >> delta;
		lcd.gotoxy(0,0);
		lcd << "x:";
		lcd << (int)delta.x;
		lcd << "  ";
		
		
		lcd.gotoxy(0,1);
		lcd << "y:";
		lcd << (int)delta.y; 
		lcd << "  ";
		
		mouse >> data;
		lcd.gotoxy(6,0);
		lcd << "Qual: ";
		lcd << (int)(unsigned char)data.qual;
		lcd << "     ";
		
	}
    return 0;
}
