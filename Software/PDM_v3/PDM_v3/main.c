/*
 * PDM_v3.c
 *
 * Created: 8/22/2018 9:05:36 AM
 * Author : Ant
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"

void init_PDM(void);


int main(void)
{
    init_PDM();
	greenON;
	HL12enableON;
	HL34enableON;
	HC1ON;			//chassis controller power on
	HC2ON;			//BMS power on
	HC3ON;			//shutdown positive on
	HLchan2OFF;		//shutdown negative on
	HLchan4ON;		//inverter power on
	HC8ON;			//steering wheel and radio power on
    while (1) 
    {
		_delay_ms(500);
		amberON;
		greenOFF;
		_delay_ms(500);
		amberOFF;
		greenON;
    }
}

void init_PDM(void)
{
	DDRA |= 0b00000001;		//PA0 - CAN_SS
	DDRB |= 0b10010110;		//PB7 PWM13; PB4 PWM10; PB2 MOSI; PB1 SCK
	DDRD |= 0b00000000;		//nil
	DDRE |= 0b00111011;		//PE5 PWM2; PE4 PWM1; PE3 PWM9; PE1 greenLED; PE0 amberLED
	DDRG |= 0b00100011;		//PG5 PWM12; PG1 HL34enable; PG0 HL34disable
	DDRH |= 0b01111000;		//PH6 PWM11; PH5 PWM4; PH3 PWM3; PH2 PWM7
	DDRJ |= 0b00011000;		//PJ4 HL12disable; PJ3 HL12enable
	DDRL |= 0b00111000;		//PL3 PWM6; PL2 PWM8; PL1 PWM5
	
	PORTA &= ~0b00000001;	//CAN_SS off
	PORTB &= ~0b10010110;	//PWMs off; MOSI off
	PORTD &= ~0b11000000;	//HL34enable off; HL34disable on
	PORTE &= ~0b00111110;	//3 x PWMs off; LEDs off
	PORTG &= ~0b00100011;	//PWM12 off
	PORTH &= ~0b01111000;	//4 x PWMs off; HL34disable on; HL34enable off
	PORTJ &= ~0b00011000;	//HL12disable on; HL12enable off
	PORTL &= ~0b00111000;	//3 x PWMs off
}

