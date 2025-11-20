#include <stdint.h>
#include <stdbool.h>

#include "lib/vga.h"
#include "lib/io.h"
#include "lib/keyboard.h"

#include "apps/shell.h"

// REBOOT

void reboot(){
	asm volatile("jmp *%0" : : "r" (0xFFFF));
}

// MAIN

void main(){
	print_clear();
	print("RosaOS v1.0\n");
	print("personal project dedicated to Rosa the Otter <3\n");
	print("Press [t] to open terminal\n");
	uint8_t scan;                                                    // declare var for scancode 
	bool running = true;                                             // running flag
	while(running){                                                  // while running...
		scan = kb_read();                                            // read scancode from keyboard
		if(kb_translate(scan) == 't'){                               // if char is 't'...
			if(shell_main() == -1){
				reboot();
			}
		}
	}
}
