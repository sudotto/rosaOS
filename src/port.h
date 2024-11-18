#ifndef PORT_H
#define PORT_H

#include <stdint.h>

void outb(uint16_t port, uint8_t value);                   // function to write a byte to port

uint8_t inb(uint16_t port);                                // function to read byte from port

#endif
