#include <stdint.h>
#include <stdbool.h>

#include "text.h"
#include "drivers/keyboard.h"

// MAIN

void main(){
	cls();
	println("RosaOS v1.0");
	println("personal project dedicated to Rosa the Otter <3");
	char key;
	bool running = true;
	while(running){
		key = kb_translate(kb_read());
		if(key){
			printc(key);
		}
	}
}
