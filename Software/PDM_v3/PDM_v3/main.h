/*
 * main.h
 *
 * Created: 8/22/2018 9:46:53 AM
 *  Author: Ant
 */ 


#ifndef MAIN_H_
#define MAIN_H_

/* LEDS */
#define greenON PORTE |= 2
#define amberON PORTE |= 1
#define greenOFF PORTE &= ~2
#define amberOFF PORTE &= ~1
#define greenTOGGLE PORTE ^= ~2
#define amberTOGGLE PORTE ^= ~1


#define HL12enableON PORTJ |= 8
#define HL12enableOFF PORTJ &= ~8

#define HL34enableON PORTG |= 2
#define HL34enableOFF PORTG &= ~2

/* Brake Light */
#define HLchan1ON PORTB |= 16		// Brake Light On
#define HLchan1OFF PORTB &= ~16		// Brake Light Off

/* Shutdown - */
#define HLchan2ON PORTH |= 64
#define HLchan2OFF PORTH &= ~64		// Shutdown - On (0b01000000)

#define HLchan3ON PORTG |= 32
#define HLchan3OFF PORTG &= ~32

/* Invertors */
#define HLchan4ON PORTB |= 128		// Inverter Power On
#define HLchan4OFF PORTB &= ~128	// Inverter Power Off

/* Chassis Controller */
#define HC1ON PORTH |= 16;		// Chassis Controller On 
#define HC1OFF PORTH &= ~16;	// Chassis Controller Off

/* BMS */	
#define HC2ON PORTE |= 32;		// BMS On
#define HC2OFF PORTE &= ~32;	// BMS Off

/* Shutdown + */	
#define HC3ON PORTE |= 16;		// Shutdown + On
#define HC3OFF PORTE &= ~16;	// Shutdown + Off

/* Pump RHS */
#define HC4ON PORTH |= 32;		// Pump RHS On
#define HC4OFF PORTH &= ~32;	// Pump RHS Off

/* Fan RHS */
#define HC5ON PORTL |= 8;		// Fan RHS On
#define HC5OFF PORTL &= ~8;		// Fan RHS On

/* Pump LHS */
#define HC6ON PORTL |= 32;		// Pump LHS On
#define HC6OFF PORTL &= ~32;	// Pump LHS Off

/* Fan LHS */
#define HC7ON PORTH |= 8;		// Fan LHS On
#define HC7OFF PORTH &= ~8;		// Fan LHS Off

/* Radio, Dash, Steering Wheel */
#define HC8ON PORTL |= 16;		// Radio, Dash, Steering Wheel On
#define HC8OFF PORTL &= ~16;	// Radio, Dash, Steering Wheel Off

/* RTD Siren */
#define HC9ON PORTE |= 8;		// RTD On
#define HC9OFF PORTE &= ~8;		// RTD Off

/* Functions */
void io_init();
void firmware_init();
void external_interrupt_init();
void board_init();
void pwm_init();
void CAN_read_packet();

#endif /* MAIN_H_ */