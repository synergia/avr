#include <avr/io.h>
#include <util/delay.h>
#include "mouse.h"




void sck_switch()
{
	M_PORT ^= 1<<SCK;
}

void sck(int state)
{
	if (state == 1) M_PORT |= (1 << SCK);
	else M_PORT &= ~(1<<SCK);
}

	
char mouse_read(int addr)
{
	char value=0;
	int i;
	
	M_DDR |= (1 << SDIO); // set both SDIO & SCK as output
	
	for (i=7; i>=0; i--)
	{
		sck(0);
		
		//send i(th) register adress bit
		if ((addr & (1<<i)) != 0) M_PORT |= (1<<SDIO);
		else M_PORT &= ~(1<<SDIO);
		
		sck(1);	
	}
	
	_delay_us(100); //wait for mouse to read data
	M_DDR &= ~(1 << SDIO); //set SDIO as input
	
	//receive data
	for (i=7; i>=0; i--)
	{
		sck(0);
		value |= (M_PIN & (1<<SDIO)) << i;
		sck(1);
	}
	_delay_us(100);
	return value;
}

void mouse_write(int addr, int value)
{
	int i;
	
	addr |= (1<<7); //to enable write mode
	
	M_DDR |= (1 << SDIO); // set both SDIO & SCK as output
	
	for (i=7; i>=0; i--)
	{
		sck(0);
		
		//send i(th) register adress bit
		if ((addr & (1<<i)) != 0) M_PORT |= (1<<SDIO);
		else M_PORT &= ~(1<<SDIO);
		
		sck(1);	
	}
	
	for (i=7; i>=0; i--)
	{
		sck(0);
		
		//send i(th) register adress bit
		if ((value & (1<<i)) != 0) M_PORT |= (1<<SDIO);
		else M_PORT &= ~(1<<SDIO);
		
		sck(1);	
	}
	
}

void mouse_init()
{
	int a;
	
	M_DDR |= (1 << SCK);
	M_PORT |= (1 << SCK);
	_delay_us(5);
	M_PORT &= ~(1 << SCK);
	_delay_us(1);
	M_PORT |= (1 << SCK);
	_delay_ms(1000);
	a = mouse_read(0x00);
	a &= ~0x01;
	mouse_write(0x00, a);
}