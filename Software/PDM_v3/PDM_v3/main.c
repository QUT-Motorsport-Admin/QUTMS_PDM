/*
 * PDM_v3.c
 *
 * Updated : 6/03/2019 4:09:20 PM	
 * Created : 8/22/2018 9:05:36 AM
 * Authors : Zoe Goodward, Anthony Kellam
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"
#include "SPI.h"
#include "pdmCAN.h"
#include "MCP2515.h"

#define CAN_ID_PDM 0x09000001 /* CAN Bus Identifier for PDM */
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

int main(void) {	
    firmware_init();
    sei();

	//Permanently energised boards
	board_init();
	
    while(1) {
		/* Wait for CAN interrupts */	
		CAN_read_packet();
		_delay_ms(100);
		amberOFF;
		greenOFF;
		_delay_ms(100);
	}
}

void firmware_init(void) {
	io_init();
    PCICR |= (1<<PCIE1); // Turning on PCIE1 bit in PCICR register
    PCMSK1 |= (1<<PCINT15); // Turning on the PCINT15 bit in PCMSK1 register
    SPI_init();
    MCP2515_init(POWER_CAN);
}

void board_init(void) {
	//Permanently energised boards
	HL12enableON;	// D1 of MC33932 - Disable state on: OUT1 & OUT2 are 3-state disabled  -  D1 input is used to 3-state disable the H-bridge outputs.
	HL34enableON;	//
	
	HC1ON;			//chassis controller power on
	HC2ON;			//BMS power on
	HC3ON;			//shutdown positive on - will be changed
	HLchan2OFF;		//shutdown negative on - will be changed
	HLchan4ON;		//inverter power on
	HC8ON;			//steering wheel and radio power on
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
void io_init(void) {
	DDRA |= 0b00000001;		//PA0 - CAN_SS // chip select
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

void CAN_read_packet() {
	uint8_t data[8];
	uint32_t ID;
	uint8_t numBytes;
	amberON;
	CAN_pull_packet(POWER_CAN, &numBytes, data, &ID);
	if (ID == CAN_ID_PDM) {
		if(numBytes > 3) {
			greenON;
			} else {
			greenOFF;
		}
		/* Byte 1 */
		if (CHECK_BIT(data[0], 0)) { /* Pump RHS */
			HC4ON;
			} else {
			HC4OFF;
		}
		if (CHECK_BIT(data[0], 1)) { /* Fan RHS */
			HC5ON;
			} else {
			HC5OFF;
		}
		if (CHECK_BIT(data[0], 2)) { /* Pump LHS */
			HC6ON;
			} else {
			HC6OFF;
		}
		if (CHECK_BIT(data[0], 3)) { /* Fan LHS */
			HC7ON;
			} else {
			HC7OFF;
		}
		if (CHECK_BIT(data[0], 4)) { /* Brake */
			HLchan1ON;
			} else {
			HLchan1OFF;
		}
		if (CHECK_BIT(data[0], 5)) {  /* Siren */
			HC9ON;
			} else {
			HC9OFF;
		}
		if (CHECK_BIT(data[0], 6)) { /* Shutdown - On */
			HLchan2ON;
			} else {
			HLchan2OFF; // Test?
		}
		if (CHECK_BIT(data[0], 7)) { /* Shutdown + On */
			HC3ON;
			} else {
			HC3OFF;
		}
		/* Byte 2 */

		/* Byte 3 */

		/* Byte 4 */

		/* Byte 5 */
	}
}

/**
 * @brief Called whenever CANBUS interrupt is triggered
 * CAN Packet 1
 * Byte 1													| Byte 2			| Byte 3			| Byte 4			| Byte 5			|
 * 0b  0,     0,     0,     0,     0,      0,     0,      0	| 0b00000000		| 0b00000000		| 0b00000000		| 0b00000000		|
 * SHDN+, SHDN-, Siren, Brake, Fan L, Pump L, Fan R, Pump R	| Fan L PWM 0-100	| Pump L PWM 0-100 	| Fan R PWM 0-100	| Pump R PWM 0-100	|
**/
ISR(PCINT1_vect) {	
	uint8_t data[8];
	uint32_t ID;
	uint8_t numBytes;
	amberON;
	CAN_pull_packet(POWER_CAN, &numBytes, data, &ID);
	if (ID == CAN_ID_PDM) {
		if(numBytes > 3) {	
			greenON;
		} else {
			greenOFF;
		}
		/* Byte 1 */
		if (CHECK_BIT(data[0], 0)) { /* Pump RHS */
			HC4ON;
		} else {
			HC4OFF;
		} 
		if (CHECK_BIT(data[0], 1)) { /* Fan RHS */
			HC5ON;
		} else {
			HC5OFF;
		}
		if (CHECK_BIT(data[0], 2)) { /* Pump LHS */
			HC6ON;
		} else {
			HC6OFF;
		}
		if (CHECK_BIT(data[0], 3)) { /* Fan LHS */
			HC7ON;
		} else {
			HC7OFF;
		}
		if (CHECK_BIT(data[0], 4)) { /* Brake */
			HLchan1ON;
		} else {
			HLchan1OFF;
		}
		if (CHECK_BIT(data[0], 5)) {  /* Siren */
			HC9ON;
		} else {
			HC9OFF;
		}
		if (CHECK_BIT(data[0], 6)) { /* Shutdown - On */
			HLchan2ON;
		} else {
			HLchan2OFF; // Test?
		}
		if (CHECK_BIT(data[0], 7)) { /* Shutdown + On */
			HC3ON;
		} else {
			HC3OFF;
		}
		/* Byte 2 */

		/* Byte 3 */

		/* Byte 4 */

		/* Byte 5 */
	}
}