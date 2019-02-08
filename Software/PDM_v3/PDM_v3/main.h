/*
 * main.h
 *
 * Created: 8/22/2018 9:46:53 AM
 *  Author: Ant
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define greenON PORTE |= 2
#define amberON PORTE |= 1
#define greenOFF PORTE &= ~2
#define amberOFF PORTE &= ~1
#define HL12enableON PORTJ |= 8
#define HL12enableOFF PORTJ &= ~8
#define HL34enableON PORTG |= 2
#define HL34enableOFF PORTG &= ~2
#define HLchan1ON PORTB |= 16
#define HLchan1OFF PORTB &= ~16
#define HLchan2ON PORTH |= 64
#define HLchan2OFF PORTH &= ~64
#define HLchan3ON PORTG |= 32
#define HLchan3OFF PORTG &= ~32
#define HLchan4ON PORTB |= 128
#define HLchan4OFF PORTB &= ~128

#define HC1ON PORTH |= 16;
#define HC1OFF PORTH &= ~16;
#define HC2ON PORTE |= 32;
#define HC2OFF PORTE &= ~32;
#define HC3ON PORTE |= 16;
#define HC3OFF PORTE &= ~16;
#define HC4ON PORTH |= 32;
#define HC4OFF PORTH &= ~32;
#define HC5ON PORTL |= 8;
#define HC5OFF PORTL &= ~8;
#define HC6ON PORTL |= 32;
#define HC6OFF PORTL &= ~32;
#define HC7ON PORTH |= 8;
#define HC7OFF PORTH &= ~8;
#define HC8ON PORTL |= 16;
#define HC8OFF PORTL &= ~16;
#define HC9ON PORTE |= 8;
#define HC9OFF PORTE &= ~8;



#endif /* MAIN_H_ */