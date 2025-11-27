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
	print("Clam Shell#n");
	while(running){
		print("~$ ");
		strclrfull(cmd, 100);
		input(cmd);
		char cmdlen = strlen(cmd) + '0';
		print("#n");
		if(!strcmp(cmd, "test")){
			print("works#n");
		} else if(!strcmp(cmd, "diskw")){
			uint8_t buffer[512] = {0};
			buffer[0] = 'a';
			if(ata_write_sector(10, buffer) == 1){
				print("#c04[ERROR] disk write failed idk :P#n");
				print("#c07");
			}
		} else if(!strcmp(cmd, "diskr")){
			uint8_t buffer[512] = {0};
			if(ata_read_sector(10, buffer) != 1){
				char test = buffer[0];
				printc(test);      // print the char
				print("#n");
			} else {
				print("#c04[ERROR] disk read failed#n");
				print("#c07");
			}
		} else if(!strcmp(cmd, "reboot")){
			return -1;                      // -1 = kernel reboot flag (make a enum for this later)
		} else if(!strcmp(cmd, "otter")){
			print("#c07  ___#n");
			print("#c06<#c07/._.\\#c06>#n");
			print("#c07 \\ w /#c06____#n");
			print("#c06 | 3 3   3--_#n");
			print("#c01^^^^^^^^^^^^^^#n");
			print("#c07");
		} else if(!strcmp(cmd, "colors")){
			for(int i = 0; i <= 7; i++){
				char str[10];
				strclrfull(str, 10);
				strcat(str, "#c");
				strpush(str, i + '0');
				strpush(str, (7 - i) + '0');
				//strcat(str, "ROSA#n");
				print(str);
				print("ROSA#n");
			}
			print("#c07");
		} else if(!strcmp(cmd, "echo") || strcmp(cmd, "echo") >= 4){
			char msg[100];
			strclr(msg);
			strcut(cmd, msg, 5);
			print(msg);
			print("#n");
		} else if(!strcmp(cmd, "clear")){
			print_clear();
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
