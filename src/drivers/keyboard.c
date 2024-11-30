#define KB_DATA_PORT 0x60
#define KB_STATUS_PORT 0x64

#include <stdint.h>
#include <stdbool.h>

#include "keyboard.h"
#include "../memory.h"

// GET KEYBOARD STATUS

uint8_t kb_status() {
	uint8_t status = inb(KB_STATUS_PORT);                            // get status byte from keyboard controller
	return (status & 0x01);                                          // return the least significant bit to determine if data is ready to read
}

// READ KEYBOARD DATA

uint8_t kb_read() {
	while(!kb_status()){};                                           // wait until data is ready to read...
	return inb(KB_DATA_PORT);                                        // read data
}

// ASCII TABLE

char ascii[] = {
	0,
	0,
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	0,
	0,
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	0,
	0,
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'`',
	0,
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	0,
	'*',
	0,
	' '
};

char num_upper[] = {
	')',
	'!',
	'@',
	'#',
	'$',
	'%',
	'^',
	'&',
	'*',
	'(',
};

// GLOBAL SHIFT PRESSED FLAG

bool upper = false;

// TRANSLATE KB SCANCODES

char kb_translate(uint8_t scancode){
	switch(scancode){
		case 0x2a:                                         // left shift is pressed
		case 0xe5:                                         // right shift is pressed
			upper = true;
			return 0;
			break;
		case 0xaa:                                         // lshift is released
		case 0xb6:                                         // rshift is released
			upper = false;
			return 0;
			break;
	}
	if(scancode < 58){
		return 0;
	}
	if(ascii[scancode] >= 'a' && ascii[scancode] <= 'z'){      // check if char is within alphabet (thank you arcoute9108)
		if(upper){                                         // if the char is flagged as uppercase
			return ascii[scancode] - 32;               // capitalize: a (97) - 32 = A (65)
		}
	}
	if(ascii[scancode] >= '0' && ascii[scancode] <= '9'){
		if(upper){
			return num_upper[ascii[scancode] - '0'];   // return shift + num ie. (1 = !) (2 = @) etc...     
		}
	}
	if(ascii[scancode]){                                       // if char is typable
		return ascii[scancode];                            // return char
	}
	return 0;
}
