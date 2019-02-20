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
#include "SPI.h"
#include "pdmCAN.h"
#include "MCP2515.h"

int main(void)
{
    firmware_init();
	//greenON;
	HL12enableON;
	HL34enableON;
	HC1ON;			//chassis controller power on
	HC2ON;			//BMS power on
	HC3ON;			//shutdown positive on
	HLchan2OFF;		//shutdown negative on
	HLchan4ON;		//inverter power on
	HC8ON;			//steering wheel and radio power on
	//HC5ON;		// Fan RHS -- current testbench
	HC4ON;			// Pump RHS -- currently on testbench
	//HC7ON;		// Fan LHS
	//HC6ON;		// Pump LHS
	//HLchan1ON;		// Break Light

	sei();
	//amberON;
    while (1) 
    {
		//_delay_ms(500);
		//amberON;
		//greenOFF;
		//_delay_ms(500);
		//amberOFF;
		//greenON;
    }
}

/**
 * @brief Configures the pins required for IO. Each port pin consists of three register bits: DDxn, PORTxn, and PINxn set by the following registers
 * 
 * 	DDRx   - Sets the direction of PINxn in bit DDxn (1 -> output, 0 -> input)
 * 
 * 	PORTx  - Activates the pull-up resistor for PINxn in bit PORTxn. The pull-up resistor will only be activated if written as logic 1 AND set as an input
 * 
 *  PINx   - The Port Input Pins I/O location is read only. 
 *           Writing a logic one to a bit in the PINx Register, will result in a toggle in the corresponding bit in the Data Register.
 * 		     Writing a logic one to PINxn toggles the value of PORTxn, independent on the value of DDRxn
 * 
 * Reference: ATmega Datasheet Chapter 13 (I/O-Ports)
 * 
 */
void io_init(void)
{
	DDRA |= 0b00000001;		//PA0 - CAN_SS
	DDRB |= 0b10010110;		//PB7 PWM13; PB4 PWM10; PB2 MOSI; PB1 SCK
	DDRD |= 0b00000000;		//nil
	DDRE |= 0b00111011;		//PE5 PWM2; PE4 PWM1; PE3 PWM9; PE1 greenLED; PE0 amberLED
	DDRG |= 0b00100011;		//PG5 PWM12; PG1 HL34enable; PG0 HL34disable
	DDRH |= 0b01111000;		//PH6 PWM11; PH5 PWM4; PH3 PWM3; PH2 PWM7
	DDRJ |= 0b01011000;		//PJ4 HL12disable; PJ3 HL12enable
	DDRL |= 0b00111000;		//PL3 PWM6; PL2 PWM8; PL1 PWM5
	
	PORTA &= ~0b00000001;	//CAN_SS off
	PORTB &= ~0b10010110;	//PWMs off; MOSI off
	PORTD &= ~0b11000000;	//HL34enable off; HL34disable on
	PORTE &= ~0b00111110;	//3 x PWMs off; LEDs off
	PORTG &= ~0b00100011;	//PWM12 off
	PORTH &= ~0b01111000;	//4 x PWMs off; HL34disable on; HL34enable off
	PORTJ &= ~0b01011000;	//HL12disable on; HL12enable off
	PORTL &= ~0b00111000;	//3 x PWMs off
}

/**
 * @brief Set up all devices in the ATmega and MCP2515. Initiates structs to hold data from other devices
 * 
 */
 void firmware_init() {
	io_init();
	PCMSK1 = 0b10000000; // Turning on the PCINT15 bit in PCMSK1 register
	// Enable interrupts for PCINT15
	// PCICR = (1<<PCIE1);
	PCICR = 0b00000010; // Turning on PCIE1 bit in PCICR register
	// Pin change mask register 1
	// PCMSK1 = (1<<PCINT15);
	//PCMSK1 = 0b10000000; // Turning on the PCINT15 bit in PCMSK1 register

	SPI_init();
	// Init CAN
	MCP2515_init(POWER_CAN);
 }

 // Interrupts

#define CHECK_BIT(var,pos) ((var) & (1<<pos))

/**
 * @brief Called whenever CANBUS interrupt is triggered
 *        * When ever there is data waiting on CAN
 */
ISR(PCINT1_vect) {	
	greenON;
	uint8_t data[8];
	uint32_t ID;
	uint8_t numBytes;

	CAN_pull_packet(POWER_CAN, &numBytes, data, &ID);
	//MCP2515_PullCanPacket(2, MCP2515_RXB0SIDH, &numBytes, data, &ID);
	//MCP2515_PullCanPacket(2, MCP2515_RXB1SIDH, &numBytes, data, &ID);
	_delay_ms(500);
	if (ID == 0x09000001) {
		//amberON;
	}
	if (CHECK_BIT(data[0], 5)) {
		//HLchan1ON;
		//amberON;
	}
	if (data[3] == 1) {
		//HLchan1ON;
		amberON;
	}
	_delay_ms(500);
	//HLchan1OFF;
	amberOFF;
}
//0x09000001
//0x09000001