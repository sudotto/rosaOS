#include <stdint.h>

#include "port.h"

// WRITE BYTES

void outb(uint16_t port, uint8_t value) {                            // function to write a byte to port
	asm volatile ("outb %0, %1" : : "a"(value), "d"(port));          // put value into port
}

// READ BYTES

uint8_t inb(uint16_t port) {                                         // function to read byte from port
	uint8_t result;                                                  // var to store byte
	asm volatile ("inb %1, %0" : "=a"(result) : "d"(port));          // assign value from port to result
	return result;                                                   // return the result
}
