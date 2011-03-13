/* Project info here */

#include <avr/io.h>
#include <util/delay.h>
#include "../lib/lcd/lcd.h"
#include "mouse.h"

LCD lcd;



int main(void){
    	

	char a=0;
	int x=0;
	int y=0;
	int x_mm=0;
	int y_mm=0;
	
	
	lcd.cursorOff();
	lcd.gotoxy(0,0);
	lcd.clear();
	
	mouse_init();
	//a = mouse_read(0x00);
	//a |= 0x01;
	//mouse_write(0x00, a);
	
	
	for(;;)
	{	
		a = mouse_read(0x03);
		x+=a;
		lcd.gotoxy(0,0);
		lcd << "x:";
		lcd << x/40;
		lcd << "  ";
		
		a = mouse_read(0x02);
		y+=a;
		lcd.gotoxy(0,1);
		lcd << "y:";
		lcd << y/40; 
		lcd << "  ";
		
		
		a = mouse_read(0x04);
		lcd.gotoxy(5,0);
		lcd << "Qual: ";
		lcd << (int)(unsigned char)a;
		lcd << "     ";
		
	}
    return 0;
}
