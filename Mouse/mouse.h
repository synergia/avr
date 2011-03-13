/*
Copyright (c) 2011 Grzegorz Hajdukiewicz
 
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
 
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#define SDIO 1			//SDIO PIN
#define SCK 0			//SCK PIN
#define M_PORT PORTB	//MOUSE PORT
#define M_DDR DDRB		//MOUSE PORT DDR
#define M_PIN PINB		//MOUSE PIN

#ifndef _MOUSE_H_
#define _MOUSE_H_

/**
 * @defgroup mouse OPTICAL SENSOR Library
 * 
 * @brief OPTICAL SENSOR serial communication (ADNS-2610)
 * 
 * @version 0.1
 * @author Grzegorz Hajdukiewicz
**/


/**
 * @struct POSITION DELTA
 * 
 * Keeps information about position change.
 * 
 * @ingroup mouse
**/
struct PosDelta{
	char x;
	char y;
};

/**
 * @struct MOUSE DATA
 * 
 * Keeps configuration data of sensor.
 * 
 * @ingroup mouse
**/
struct MouseData{
	char qual;
};



/**
 * @class MOUSE
 * 
 * ADNS-2610 optical sensor support
 * 
 * @ingroup mouse
**/
class MOUSE{

public:
	/**
	 * Default constructor.
	 * Synchronizes tramsmission
	**/
	MOUSE();
	
	/**
	 * Reads data from sensor
	 * 
	 * @param addr - Register address.
	 * @return Read value (from specified register)
	**/
	char read(char addr);
	
	/**
	 * Writes data to sensor
	 * 
	 * @param addr - Register address.
	 * @param data - Value to be written.
	**/
	void write(char addr, char data);
	
	/**
	 * Gets position change from mouse
	 * 
	 * @param delta - Pos_Delta structure.
	 * @return MOUSE object
	**/
	MOUSE & operator >> (PosDelta &delta);
	
	/**
	 * Gets configuration data from mouse
	 * 
	 * @param data - Mouse_Data structure.
	 * @return MOUSE object
	**/
	MOUSE & operator >> (MouseData &data);
		
private:
	
	//set clock state
	void sck(char state);

};

#endif
