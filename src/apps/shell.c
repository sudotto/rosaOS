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
				strpush(cmd, key);
			}
			switch(scan){                        // if scancode is...
				case 14:                         // the backspace key...
					strpop(cmd);
					BS();                        // backspace
					break;
				case 28:                         // the enter key...
					char cmdlen = strlen(cmd) + '0';
					CRLF();
					if(!strcmp(cmd, "test")){
						println("works");
					} else if(!strcmp(cmd, "diskw")){
						uint8_t buffer[512] = {0};
						buffer[0] = 'a';
						if(ata_write_sector(10, buffer) == 1){
							println("[ERROR] disk write failed idk :P");
						}
					} else if(!strcmp(cmd, "diskr")){
						uint8_t buffer[512] = {0};
						if(ata_read_sector(10, buffer) != 1){
							char test = buffer[0];
							printc(test);
							CRLF();
						} else {
							println("[ERROR] disk read failed");
						}
					} else if(!strcmp(cmd, "reboot")){
						return -1;                      // -1 = kernel reboot flag (make a enum for this later)
					} else if(!strcmp(cmd, "otter")){
						println("  ___");
						println("</._.\\>");
						println(" \\_^_/");
						println(" / 3@3");
					} else {
						println("[ERROR] unknown command please check spelling");
					} 
					typing = false;
					break;
			}
		}
	}
	return 0;
}
