#include "SPI.h"

uint8_t SPI_send_byte(uint8_t c)
{
	SPDR = c;					//write data to the transmission register. Writing to this initiates transmission.
	while(!(SPSR & (1<<SPIF)));
	return SPDR;				//return any data that was shifted into this register upon transmission.
}

void SPI_init()
{
	//MCUCR &= ~(1<<SPIPS);		//make sure we are getting spi not on the _A spi pins.
	SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR0)|(0<<SPR1);  //set interrupt, enable SPI, MSB mode, set as master, low is idle, read on leading edge, Set to speed(fosc/64) SPR0=1, SPR1=0
	SPSR = (1<<SPI2X);	//set whether we want 2x speed or not (1=2x speed).
	SPDR = 0x00;		//ensure data register has nothing in it
}