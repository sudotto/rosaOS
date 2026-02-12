#ifndef PORT_H
#define PORT_H

#include <stdint.h>

// WRITE BYTES

void outb(uint16_t port, uint8_t val);           // function to write byte to port

// READ BYTES

uint8_t inb(uint16_t port);                      // function to read byte from port

// WRITE WORD

void outw(uint16_t port, uint16_t val);          // function to write word to port 

// READ WORD

uint16_t inw(uint16_t port);                     // function to read word from port

void* memcpy(void* dest, const void* src, unsigned long n); 

#endif
