#define SDIO 1			//SDIO PIN
#define SCK 0			//SCK PIN
#define M_PORT PORTB	//MOUSE PORT
#define M_DDR DDRB		//MOUSE PORT DDR
#define M_PIN PINB		//MOUSE PIN

#ifndef _MOUSE_H_
#define _MOUSE_H_


void sck_switch();

void sck(int state);

char mouse_read(int addr);

void mouse_write(int addr, int value);

void mouse_init();

#endif