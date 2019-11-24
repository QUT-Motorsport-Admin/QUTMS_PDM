/**
 * @file pdmCAN.h
 * @author Jonn Dillon
 * @date 16/4/2018
 * @brief Defines and outlines all varibles and definitions related to the CANBUS system
 **/

#ifndef PDM_CAN_H
#define PDM_CAN_H

#include <stdlib.h>
#include <avr/io.h>

#define STATUS_REG 			GPIOR0 /**< Status Register */
#define CAN1_DataWaiting	1 /**< CAN Bus 1 Has Data Waiting flag */
#define CAN2_DataWaiting	2 /**< CAN Bus 2 Has Data Waiting flag */
#define CAN3_DataWaiting	4 /**< CAN Bus 3 Has Data Waiting flag */
#define IGNITION			8 /**< Car Is Starting flag */

// Destination IDs for send_heartbeat()
#define INVERTERS_ID    0 /**< Heartbeat Identifier for Inverters */
#define AMU_ID          1 /**< Heartbeat Identifier for AMU */
#define PDM_ID          2 /**< Heartbeat Identifier for PDM */
#define WHEEL_ID        3 /**< Heartbeat Identifier for Wheel */

#define CAN_ID_INV	        0x0C000000 /**< CAN Bus Identifier for Inverters */
#define	CAN_ID_AMU	        0x0A000000 /**< CAN Bus Identifier for AMU */
//#define CAN_ID_PDM	        0x09000000 /**< CAN Bus Identifier for PDM */
#define CAN_ID_WHEEL	    0x00400000 /**< CAN Bus Identifier for Wheel */

/**
 * @brief Appears Unused?
 * 
 */
// unsigned char CANreceiver = 0;

/**
 * @brief Used in radiator temperature checks
 * 
 * TODO Needs more descriptive comment
 * 
 */
// unsigned int radiator_cals_acewell_22k[27] = {801,	800, 799, 797, 791, 785, 767, 750, 734, 707, 689, 671, 637, 598, 581, 562, 529, 493, 464, 443, 359, 338, 317, 297, 278, 234, 204};

/**
 * @brief Increments on heartbeat
 * 
 */
// volatile int heartbeatTimer = 0;

/**
 * @brief Appears Unused?
 * 
 */
// char CANdiagnostics[10][20]; 

/**
 * @brief Temporary buffer used for UART
 * 
 */
// uint8_t tempBuffer[10]; 

// #define CANselect PORTC &= ~1 /**< Appears Unused? */
// #define CANdeselect	  PORTC |= 1 /**< Appears Unused? */

// ===================================== FUNCTION DECLARATIONS =====================================

/**
 * @brief Serves as a wrapper for MCP2515_TX in MCP2515_TX.h - for more info refer
 * 		  to that.
 * 
 * @param CANbus CAN bus to send data on. Use #defines in MCP2515_TX.h
 * @param numBytes Number of bytes to send
 * @param data Pointer to data to send
 * @param ID CAN Packet Identifier. Use CAN_ID_constructor.
 */
void CAN_send(uint8_t CANbus, uint8_t numBytes, uint8_t * data, uint32_t ID);

/**
 * @brief Construct a unique CAN packet identifier
 * 
 * @param sendingID First 8 bits, define the device to send to
 * @param type What sort of command to send
 * @param address Specific address to send to
 * @param status Sub ID?
 * @return uint32_t A unique CAN packet identifer
 */
uint32_t CAN_ID_constructor(uint32_t sendingID, unsigned char type, unsigned char address, uint32_t status);

/**
* @brief	Serves as a wrapper for the MCP2515_PullCanPacket(..) in MCP2515.h - For more info
*			refer to that.
*
*	Example Code:

*		uint8_t data[8];

*		uint32_t ID;

*		uint8_t numBytes;
*
*		CAN_pull_packet(MCP2515_CANx, &numBytes, data, &ID); // Where x is the CAN bus number
*
*	Reference: Microchip MCP2515 Datasheet Chapter 4 (Message Reception)
*
* @param CANbus The CAN Bus to pull data from - use #defines in MCP2515.h
* @param numBytes Pointer to store number of bytes in
* @param data Pointer to store data in
* @param ID Pointer to store packet identifier
*
* @return void
* 
* @author Pedro Alves
**/
void CAN_pull_packet(uint8_t CANbus, uint8_t* numBytes, uint8_t* data, uint32_t* ID);

#endif // PDM_CAN_H