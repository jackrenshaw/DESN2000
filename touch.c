#include "touch.h"
#include "lpc24xx.h"

#define CS_PIN            0x00100000        //P0.20

static unsigned char touch_read(unsigned char command);

void touch_init(void)
{
	//Implement this as you see fit
	//Remember to setup CS_TP as a GPIO output
	FIO0DIR |= CS_PIN;
	FIO0PIN |= CS_PIN;
	S0SPCR |= 0x093C; //SPI control register setup
	S0SPCCR |= 0x24;
	//CS_PIN &= 0x01;
	PINSEL0 |=  0xC0000000;//SCLK
	PINSEL1 |=  0x0000003C;//MISO AND MIOS
}

void touch_read_xy(char *x, char* y)
{
	//Read X co-ordinate from the touch screen controller
	*x = touch_read(0xDB);
	//Read Y co-ordinate from the touch screen controller
	*y = touch_read(0x98);
}

static unsigned char touch_read(unsigned char command)
{
	unsigned short result;

	//Set CS_TP pin low to begin SPI transmission
		FIO0PIN &= ~CS_PIN;
	//Transmit command byte on MOSI, ignore MISO (full read write cycle)
	S0SPDR = command;
	while((S0SPSR & 0x80) != (0)){
		
	}
	//Transmit 0x00 on MOSI, read in requested result on MISO (another full read write cycle)
	S0SPDR = 0x00;
	while((S0SPSR & 0x80) != (0)){
		
	}		
	//MISO AND MIOS
	result = S0SPDR;
	//Transmission complete, set CS_TP pin back to high
		FIO0PIN |= CS_PIN;
	
	//Return 8 bit result.
	return (unsigned char) result;
}	

