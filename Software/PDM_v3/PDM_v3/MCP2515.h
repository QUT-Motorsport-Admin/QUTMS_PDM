#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <string.h>

#define TRACTIVE_CAN_PORT_CS	PORTA	//pin 12
#define POWER_CAN_PORT_CS		PORTA	//pin 69
#define DATA_CAN_PORT_CS		PORTA	//pin 19
#define TRACTIVE_CAN_PIN_CS		PINA0	//pin 12
#define POWER_CAN_PIN_CS		PINA0	//pin 69
#define DATA_CAN_PIN_CS			PINA0	//pin 19

#define TRACTIVE_CAN	1
#define POWER_CAN		2
#define DATA_CAN		4

#define MCP2515_MODE_ONESHOT 0x08
#define MCP2515_MODE_NORMAL 0x00
//#define TRACTIVE_CAN_PORT_CS	PORTH			//pin 12
//#define DATA_CAN	PORTH			//pin 13
//#define DATA_CAN_PORT_CS	PORTB			//pin 19
//#define TRACTIVE_CAN_PIN_CS		PINH0			//pin 12
//#define POWER_CAN_PIN_CS		PINH1			//pin 13
//#define DATA_CAN_PIN_CS		PINB0			//pin 19


//#define MCP2515_PORT_CS		PORTB
//#define MCP2515_PIN_CS		PINB6		//***
//#define MCP2515_PIN_RESET	PINC5		//***
//#define MCP2515_PORT_RESET	PORTC


#define MCP2515_RESET		0xC0		//***
#define MCP2515_READ		0x03		//***
#define MCP2515_WRITE		0x02		//***send this, then send address byte, then send data
#define MCP2515_CNF1		0x2A		//***
#define MCP2515_CNF2		0x29		//***
#define MCP2515_CNF3		0x28		//***
#define MCP2515_CANCTRL		0x0F		//***
#define MCP2515_CANSTAT		0x0E		//***
#define MCP2515_CANINTE		0x2B		//***
#define MCP2515_CANINTF		0x2C		//***
#define MCP2515_EFLG		0x2D		//***
#define MCP2515_BITMODIFY	0x05		//***
#define MCP2515_RTSCTRL		0x0D		//***
#define MCP2515_RXSTATUS	0xB0

#define MCP2515_TX0			0x30		//***
#define MCP2515_TX0_CTRL	0x30		//***
#define MCP2515_TX0_SIDH	0x31		//***
#define MCP2515_TX0_SIDL	0x32		//***
#define MCP2515_TX0_EID8	0x33		//***
#define MCP2515_TX0_EID0	0x34		//***
#define MCP2515_TX0_DLC		0x35		//***
#define MCP2515_TX0_DATA	0x36		//***data for tx0 is from 0x36 to 0x3D. 0 to 7 respectively.
//#define MCP2515_TX0_RTSPIN	PINC7		//***

#define MCP2515_TX1			0x40		//***
#define MCP2515_TX1_CTRL	0x40		//***
#define MCP2515_TX1_SIDH	0x41		//***
#define MCP2515_TX1_SIDL	0x42		//***
#define MCP2515_TX1_EID8	0x43		//***
#define MCP2515_TX1_EID0	0x44		//***
#define MCP2515_TX1_DLC		0x45		//***
#define MCP2515_TX1_DATA	0x46		//***data for tx0 is from 0x46 to 0x4D. 0 to 7 respectively.

#define MCP2515_TX2			0x50		//***
#define MCP2515_TX2_CTRL	0x50		//***
#define MCP2515_TX2_SIDH	0x51		//***
#define MCP2515_TX2_SIDL	0x52		//***
#define MCP2515_TX2_EID8	0x53		//***
#define MCP2515_TX2_EID0	0x54		//***
#define MCP2515_TX2_DLC		0x55		//***
#define MCP2515_TX2_DATA	0x56		//***data for tx2 is from 0x56 to 0x5D. 0 to 7 respectively.

#define MCP2515_RXB0		0x60
#define MCP2515_RXB0CTRL 	0x60		//***
#define MCP2515_RXB0SIDH	0x61		//***
#define MCP2515_RXB0SIDL	0x62		//***
#define MCP2515_RXB0EID8	0x63		//***
#define MCP2515_RXB0EID0	0x64		//***
#define MCP2515_RXB0D0		0x66		//***

#define MCP2515_RXB1		0x70
#define MCP2515_RXB1CTRL 	0x70		//***
#define MCP2515_RXB1SIDH	0x71		//***
#define MCP2515_RXB1SIDL	0x72		//***
#define MCP2515_RXB1EID8	0x73		//***
#define MCP2515_RXB1EID0	0x74		//***
#define MCP2515_RXB1D0		0x76		//***

#define MCP2515_RXM0SIDH	0x20		//***
#define MCP2515_RXM0SIDL	0x21		//***
#define MCP2515_RXM0EID8	0x22		//***
#define MCP2515_RXM0EID0	0x23		//***

#define MCP2515_RXM1SIDH	0x24		//***
#define MCP2515_RXM1SIDL	0x25		//***
#define MCP2515_RXM1EID8	0x26		//***
#define MCP2515_RXM1EID0	0x27		//***

#define MCP2515_RXF0SIDH	0x00		//***
#define MCP2515_RXF0SIDL	0x01		//***
#define MCP2515_RXF0EID8	0x02		//***
#define MCP2515_RXF0EID0	0x03		//***

#define MCP2515_RXF1SIDH	0x04		//***
#define MCP2515_RXF1SIDL	0x05		//***
#define MCP2515_RXF1EID8	0x06		//***
#define MCP2515_RXF1EID0	0x07		//***

#define MCP2515_RXF2SIDH	0x08		//***
#define MCP2515_RXF2SIDL	0x09		//***
#define MCP2515_RXF2EID8	0x0A		//***
#define MCP2515_RXF2EID0	0x0B		//***

#define MCP2515_RXF3SIDH	0x10		//***
#define MCP2515_RXF3SIDL	0x11		//***
#define MCP2515_RXF3EID8	0x12		//***
#define MCP2515_RXF3EID0	0x13		//***

#define MCP2515_RXF4SIDH	0x14		//***
#define MCP2515_RXF4SIDL	0x15		//***
#define MCP2515_RXF4EID8	0x16		//***
#define MCP2515_RXF4EID0	0x17		//***

#define MCP2515_RXF5SIDH	0x18		//***
#define MCP2515_RXF5SIDL	0x19		//***
#define MCP2515_RXF5EID8	0x1A		//***
#define MCP2515_RXF5EID0	0x1B		//***

#define MCP2515_BFPCTRL  	0x0C		//***

void	MCP2515_init(uint8_t CANbus);
void	MCP2515_TX(uint8_t CANbus, int8_t mob, uint8_t numBytes, uint8_t * data, uint32_t ID);
void 	MCP2515_reg_write(uint8_t CANbus, uint8_t reg_address, uint8_t reg_value);
void 	MCP2515_instruction(uint8_t CANbus, uint8_t instruction);
void 	MCP2515_bit_modify(uint8_t CANbus, uint8_t reg_address, uint8_t reg_value, uint8_t reg_mask);
void	MCP2515_FilterInit(uint8_t CANbus, uint8_t filterNum, uint32_t filterID);
void	MCP2515_RxBufferRead(uint8_t CANbus, uint8_t * data, uint8_t rxBuffer);
uint8_t MCP2515_receive_status(uint8_t CANbus);
uint8_t MCP2515_reg_read(uint8_t CANbus, uint8_t reg_address);
uint8_t MCP2515_RXInit(uint8_t CANbus, int8_t mob, uint32_t IDmsk);
uint8_t MCP2515_check_receive_status(uint8_t CANbus);
uint8_t MCP2515_findFreeTxBuffer(uint8_t CANbus);
uint8_t MCP2515_send_test(uint8_t CANbus);
void MCP2515_PullCanPacket(uint8_t CANbus, uint8_t mob,uint8_t * numBytes , uint8_t * data, uint32_t * ID);