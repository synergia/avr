#define SDIO 1			//SDIO PIN
#define SCK 0			//SCK PIN
#define M_PORT PORTB	//MOUSE PORT
#define M_DDR DDRB		//MOUSE PORT DDR
#define M_PIN PINB		//MOUSE PIN

#ifndef _MOUSE_H_
#define _MOUSE_H_

struct Pos_Delta{
	char x;
	char y;
};

struct Mouse_Data{
	char qual;
};

class MOUSE{

public:
	MOUSE();
	char read(char addr);
	void write(char addr, char data);
	MOUSE & operator >> (Pos_Delta &delta);
	MOUSE & operator >> (Mouse_Data &data);
		
private:
	void sck(char state);

};

#endif
