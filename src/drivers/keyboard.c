#define KB_DATA_PORT 0x60
#define KB_STATUS_PORT 0x64

#include <stdint.h>
#include <stdbool.h>

#include "keyboard.h"
#include "../port.h"

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

// KEY LIST

char* keys[] = {
	0,
	"esc",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0",
	"-",
	"=",
	"back",
	"tab",
	"q",
	"w",
	"e",
	"r",
	"t",
	"y",
	"u",
	"i",
	"o",
	"p",
	"[",
	"]",
	"ret",
	"ctrl",
	"a",
	"s",
	"d",
	"f",
	"g",
	"h",
	"j",
	"k",
	"l",
	";",
	"\'",
	"`",
	"lshift",
	"\\",
	"z",
	"x",
	"c",
	"v",
	"b",
	"n",
	"m",
	",",
	".",
	"/",
	"rshift",
	"*",
	"lalt",
	" "
};

// TRANSLATE KB SCANCODES

char kb_translate(uint8_t scancode){
	bool upper = false;
	switch(scancode){
		case 0x2a:                                         // left shift is pressed
			upper = true;
			break;
		case 0xe5:                                         // right shift is pressed
			upper = false;
			break;
	}
	if(scancode > 58){                                     // 58 is outside of typeable chars
		return 0;                                          // return untypeable
	}
	if(upper){                                             // if the char is flagged as uppercase
		return ascii[scancode] - 32;                       // a (97) - 32 = A (65)
	} else {
		return ascii[scancode];                            // return normal char
	}
}

//
