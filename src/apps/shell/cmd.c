#include <stdint.h>
#include <stdbool.h>

#include "../../lib/vga.h"
#include "../../lib/io.h"
#include "../../lib/keyboard.h"
#include "../../lib/string.h"
#include "../../lib/disk.h"

#include "cmd.h"

void cmd_test(){
}

void cmd_diskw(){
	uint8_t buffer[512] = {0};
	buffer[0] = 'a';
	if(ata_write_sector(10, buffer) == 1){
		print("#c04[ERROR] disk write failed idk :P#n");
		print("#c07");
	}
}

void cmd_diskr(){
	uint8_t buffer[512] = {0};
	if(ata_read_sector(10, buffer) != 1){
		char test = buffer[0];
		printc(test);      // print the char
		print("#n");
	} else {
		print("#c04[ERROR] disk read failed#n");
		print("#c07");
	}
}

void cmd_otter(){
	print("#c07  ___#n");
	print("#c06<#c07/._.\\#c06>#n");
	print("#c07 \\ w /#c06____#n");
	print("#c06 | 3 3   3--_#n");
	print("#c01^^^^^^^^^^^^^^#n");
	print("#c07");
}

void cmd_colors(){
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
}

void cmd_echo(char* cmd){
	char msg[100];
	strclr(msg);
	strcut(cmd, msg, 5);
	print(msg);
	print("#n");
}

void cmd_clear(){}

void cmd_help(){
	print("commands:#n");
	print("-----#n");
	print("   [test]   prints \"works\"#n");
	print("   [diskw]  writes letter a to disk#n");
	print("   [diskr]  reads the spot that diskw writes to#n");
	print("   [otter]  otter#n");
	print("   [colors] prints vga colors#n");
	print("   [echo] prints whatever you write after echo, ie. echo hello#n");
}
