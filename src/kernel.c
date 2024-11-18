#include <stdint.h>
#include <stdbool.h>

#include "text.h"
#include "drivers/keyboard.h"

// MAIN

void main(){
	cls();
	println("RosaOS v1.0");
	println("personal project dedicated to Rosa the Otter <3");
	uint8_t scancode;
	bool running = true;
	while(running){
		scancode = kb_read();
		if(scancode == 0x0e){
			println("backspace");
		}
	}
}
