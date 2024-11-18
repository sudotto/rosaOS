#define KB_DATA_PORT 0x60
#define KB_STATUS_PORT 0x64

#include <stdint.h>

#include "keyboard.h"
#include "../port.h"

// GET KEYBOARD STATUS

int kb_status() {
	uint8_t status = inb(KB_STATUS_PORT);                            // get status byte from keyboard controller
	return (status & 0x01);                                          // return the least significant bit to determine if data is ready to read
}

// READ KEYBOARD DATA

uint8_t kb_read() {
	while(!kb_status()){};                                           // wait until data is ready to read...
	return inb(KB_DATA_PORT);                                        // read data
}
