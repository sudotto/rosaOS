#include <stdint.h>
#include <stdbool.h>

#include "../lib/vga.h"
#include "../lib/keyboard.h"
#include "../lib/string.h"
#include "../lib/disk.h"

// SHELL MAIN

int shell_main(){
	CLS();                                       // clear screen
	char scan;
	bool running = true;                         // running flag
	char cmd[100];                           // somewhere to store user input
	println("Clam Shell");
	while(running){
		print("~$ ");
		bool typing = true;                      // typing flag
		strclr(cmd);
		while(typing){
			scan = kb_read();
			if(kb_translate(scan)){              // if char is typable...
				printc(kb_translate(scan));      // print the char
				char key = kb_translate(scan);
				strappend(cmd, key);
			}
			switch(scan){                        // if scancode is...
				case 14:                         // the backspace key...
					BS();                        // backspace
					break;
				case 28:                         // the enter key...
					char cmdlen = strlen(cmd) + '0';
					CRLF();                      // newline
					if(!strcmp(cmd, "test")){
						println("works");
					} else if(!strcmp(cmd, "diskw")){
						uint8_t buffer[512] = {0};
						buffer[0] = 'a';
						ata_write_sector(10, buffer);
					} else if(!strcmp(cmd, "diskr")){
						uint8_t buffer[512] = {0};
						ata_read_sector(10, buffer);
						char test = buffer[0];
						printc(test);
						CRLF();
					} 
					typing = false;
					break;
			}
		}
	}
	return 0;
}
