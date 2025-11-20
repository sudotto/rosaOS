#include <stdint.h>
#include <stdbool.h>

#include "../lib/vga.h"
#include "../lib/io.h"
#include "../lib/keyboard.h"
#include "../lib/string.h"
#include "../lib/disk.h"

// SHELL MAIN

int shell_main(){
	print_clear();                                       // clear screen
	char scan;
	bool running = true;                         // running flag
	char cmd[100];                           // somewhere to store user input
	print("Clam Shell\n");
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
					print("\b");
					break;
				case 28:                         // the enter key...
					char cmdlen = strlen(cmd) + '0';
					print("\n");
					if(!strcmp(cmd, "test")){
						print("works\n");
					} else if(!strcmp(cmd, "diskw")){
						uint8_t buffer[512] = {0};
						buffer[0] = 'a';
						if(ata_write_sector(10, buffer) == 1){
							print("[ERROR] disk write failed idk :P\n");
						}
					} else if(!strcmp(cmd, "diskr")){
						uint8_t buffer[512] = {0};
						if(ata_read_sector(10, buffer) != 1){
							char test = buffer[0];
							printc(test);      // print the char
							print("\n");
						} else {
							print("[ERROR] disk read failed\n");
						}
					} else if(!strcmp(cmd, "reboot")){
						return -1;                      // -1 = kernel reboot flag (make a enum for this later)
					} else if(!strcmp(cmd, "otter")){
						print("!07  ___\n");
						print("!04<!07/._.\\!04>\n");
						print("!07 \\_W_/\n");
						print("!04 / 3!06@!043!07\n");
					} else if(!strcmp(cmd, "colors")){
						for(int i = 0; i <= 7; i++){
							char str[10];
							strclr(str);
							strpush(str, '!');
							strpush(str, i + '0');
							strpush(str, (7 - i) + '0');
							strcat(str, "ROSA\n");
							print(str);
							print("!07");
						}
					} else if(!strcmp(cmd, "echo") || strcmp(cmd, "echo") >= 4){
						char msg[100];
						strclr(msg);
						strcut(cmd, msg, 5);
						print(msg);
						print("\n");
					} else if(!strcmp(cmd, "clear")){
						print_clear();
					} else {
						printc(strcmp(cmd, "echo") + '0');
						print("[ERROR] unknown command please check spelling\n");
					} 
					typing = false;
					break;
			}
		}
	}
	return 0;
}
