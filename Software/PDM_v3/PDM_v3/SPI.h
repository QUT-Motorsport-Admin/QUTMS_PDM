#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

uint8_t SPI_send_byte(uint8_t c);
void SPI_init();

#endif