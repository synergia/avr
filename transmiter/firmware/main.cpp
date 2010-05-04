/* Project info here */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"

#define SCK  1 // PB1
#define SDO  2 // PB2
#define SDI  3 // PB3
#define CS   0 // PB0 (NSEL, PB4)

#define NIRQ 0 // PD0

#define HI(x) PORTB |= (1<<(x))
#define LO(x) PORTB &= ~(1<<(x))
#define WAIT_NIRQ_LOW() while(PIND & (1<<NIRQ))

USART0(usb);

void portInit(){
	HI(CS);
	HI(SDI);
	LO(SCK);
	DDRB = (1<<CS)|(1<<SDI)|(1<<SCK);
	DDRD = 0;
}

unsigned int writeCmd(unsigned int cmd){
	unsigned char i;
	unsigned int recv;
	recv = 0;
	LO(SCK);
	LO(CS);
	for(i=0; i<16; i++){
		if(cmd & 0x8000) HI(SDI);
		else LO(SDI);
	    HI(SCK);
		recv <<= 1;
		if(PINB & (1<<SDO)){
			recv |= 0x0001;
		}
		
		LO(SCK);
		cmd <<= 1;
	}
	HI(CS);
	return recv;
}

void rfInit(){
	writeCmd(0x80E7); // EL,EF,868band,12.0pF 
	writeCmd(0x8239); // !er,!ebb,ET,ES,EX,!eb,!ew,DC 
	writeCmd(0xA640); // frequency select 
	writeCmd(0xC647); // 4.8kbps 
	writeCmd(0x94A0); // VDI,FAST,134kHz,0dBm,-103dBm 
	writeCmd(0xC2AC); // AL,!ml,DIG,DQD4 
	writeCmd(0xCA81); // FIFO8,SYNC,!ff,DR 
	writeCmd(0xCED4); // SYNC=2DD4AG 
	writeCmd(0xC483); // @PWR,NO RSTRIC,!st,!fi,OE,EN 
	writeCmd(0x9850); // !mp,90kHz,MAX OUT 
	writeCmd(0xCC17); // OB1ACOB0, LPX,Iddy,CDDIT,CBW0 
	writeCmd(0xE000); // NOT USED 
	writeCmd(0xC800); // NOT USED 
	writeCmd(0xC040); // 1.66MHz,2.2V
}

void rfSend(unsigned char data){
	WAIT_NIRQ_LOW();
	writeCmd(0xB800 + data);
}

void rfSendPackage(){
	usb << "SENDING PACKAGE\n\r";
	writeCmd(0x0000);
	rfSend(0xAA); // PREAMBLE
	rfSend(0xAA); // PREAMBLE
	rfSend(0xAA); // PREAMBLE
	rfSend(0x2D); // SYNC
	rfSend(0xD4);
	
	// send 16 bytes package
	for(int i=0; i<16; i++){
		rfSend(0x30 + i);
	}
	
	rfSend(0xAA); // DUMMY
	rfSend(0xAA); // DUMMY
	rfSend(0xAA); // DUMMY
}

int main(){
	sei();
	asm("cli");
	_delay_ms(1000);
	
	usb << "ALL SYSTEMS GO\n\r";
	
	portInit();
	rfInit(); 
	
	while(1){
		usb << "USART TEST\n\r";
		rfSendPackage();
		_delay_ms(1000);
	}
	
}













