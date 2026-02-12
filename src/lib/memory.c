#include <stdint.h>

#include "memory.h"

// WRITE BYTES

void outb(uint16_t port, uint8_t val) {                              // function to write a byte to port
	asm volatile ("outb %0, %1" : : "a"(val), "d"(port));            // put value into port
}

// READ BYTES

uint8_t inb(uint16_t port) {                                         // function to read byte from port
	uint8_t result;                                                  // var to store byte
	asm volatile ("inb %1, %0" : "=a"(result) : "d"(port));          // assign value from port to result
	return result;                                                   // return the result
}

// WRITE WORD

void outw(uint16_t port, uint16_t val) {
    asm volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}


// READ WORD

uint16_t inw(uint16_t port) {                                         // function to read byte from port
	uint16_t result;                                                  // var to store byte
	asm volatile ("inw %1, %0" : "=a"(result) : "Nd"(port));         // assign value from port to result
	return result;                                                   // return the result
}


void* memcpy(void* dest, const void* src, unsigned long n){                 // stole this code no idea how it works (yet)
	for(int i = 0; i < n; i++){
		((char*)dest)[i] = ((char*)src)[i];
	}
}
