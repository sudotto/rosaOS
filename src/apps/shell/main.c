#include <stdint.h>
#include <stdbool.h>

#include "../../lib/vga.h"
#include "../../lib/io.h"
#include "../../lib/keyboard.h"
#include "../../lib/string.h"
#include "../../lib/disk.h"

#include "cmd.h"

// SHELL MAIN

int shell_main(){
	print_clear();                                       // clear screen
	char scan;
	bool running = true;                         // running flag
	char cmd[100];                           // somewhere to store user input
	print("Clam Shell#n");
	while(running){
		print("~$ ");
		strclrfull(cmd, 100);
		input(cmd);
		char cmdlen = strlen(cmd) + '0';
		print("#n");
		if(!strcmp(cmd, "test")){
			vga_scroll(1);
			print("works#n");
		} else if(!strcmp(cmd, "diskw")){
			cmd_diskw();
		} else if(!strcmp(cmd, "diskr")){
			cmd_diskr();
		} else if(!strcmp(cmd, "reboot")){
			return -1;                      // -1 = kernel reboot flag (make a enum for this later)
		} else if(!strcmp(cmd, "otter")){
			cmd_otter();
		} else if(!strcmp(cmd, "colors")){
			cmd_colors();
		} else if(!strcmp(cmd, "echo") || strcmp(cmd, "echo") >= 4){
			cmd_echo(cmd);
		} else if(!strcmp(cmd, "clear")){
			print_clear();
		} else if(!strcmp(cmd, "help")){
			cmd_help();
		} else {
			char msg[100];
			strclr(msg);
			strcat(msg, "#c04[ERROR] ");
			strcat(msg, cmd);
			strcat(msg, " is not recognized as a command,#n or maybe the os is broken who knows?#n");
			print(msg);
			print("#c07");
		}
	}
	return 0;
}
