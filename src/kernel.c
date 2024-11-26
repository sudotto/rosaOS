#include <stdint.h>
#include <stdbool.h>

#include "drivers/vga.h"
#include "drivers/keyboard.h"

// MAIN

void main(){
	CLS();
	println("RosaOS v1.0");
	println("personal project dedicated to Rosa the Otter <3");
	uint8_t scan;                                                    // declare var for scancode 
	bool running = true;                                             // running flag
	while(running){                                                  // while running...
		scan = kb_read();                                            // read scancode from keyboard
		if(kb_translate(scan)){                                      // if char is typable...
			printc(kb_translate(scan));                              // print the char
		}
		switch(scan){                                                // if scancode is...
			case 14:                                                 // the backspace key...
				BS();                                                // backspace
				break;
			case 28:                                                 // the enter key...
				CRLF();                                              // newline
				break;
		}
	}
}
