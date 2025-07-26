#include <stdint.h>
#include <stdbool.h>

#include "../drivers/vga.h"
#include "../drivers/keyboard.h"

#include "../lib/string.h"

// SHELL MAIN

unsigned int shell_main(){
	CLS();                                       // clear screen
	char scan;
	bool running = true;                         // running flag
	char cmd[100];                           // somewhere to store user input
	println("Clam Shell");
	while(running){
		print("~$ ");
		bool typing = true;                      // typing flag
		strclr(cmd);
		print("cmd after reset: ");
		println(cmd);
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
					CRLF();
					println(cmd);
					printc(cmdlen);
					CRLF();                      // newline
					if(!strcmp(cmd, "test")){
						println("works");
					}
					typing = false;
					break;
			}
		}
	}
	return 0;
}
