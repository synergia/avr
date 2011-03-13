#define SDIO 1
#define SCK 0
#define M_PORT PORTB
#define M_DDR DDRB
#define M_PIN PINB

#ifndef _MOUSE_H_
#define _MOUSE_H_


void sck_switch();

void sck(int state);

char mouse_read(int addr);

void mouse_write(int addr, int value);

void mouse_init();

#endif