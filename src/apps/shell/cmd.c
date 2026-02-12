#include <stdint.h>
#include <stdbool.h>

#include "../../lib/vga.h"
#include "../../lib/io.h"
#include "../../lib/keyboard.h"
#include "../../lib/string.h"
#include "../../lib/disk.h"
#include "../../lib/fs.h"

#include "cmd.h"

void cmd_test(){
}

void cmd_diskw(){
	char buffer[512] = {0};
	buffer[0] = 'a';
	if(ata_write_sector(10, buffer) == 1){
		print("#c04[ERROR] disk write failed idk :P#n");
		print("#c07");
	}
}

void cmd_diskr(){
	uint8_t buffer[512] = {0};
	if(ata_read_sector(10, buffer) == 1){
		print("#c04[ERROR] disk read failed#n");
		print("#c07");
		return;
	}
	char test = buffer[0];
	printc(test);      // print the char
	print("#n");
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
		print(str);
		print("ROSA#n");
	}
	print("#c07");
}

void cmd_echo(char* cmd){
	char msg[100];
	strclrfull(msg, 100);
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
	print("   [file] makes a file with name provided file, ie. file test#n");
	print("   [tag] sets the description of given file, ie. tag test tagged#n");
	print("   [filetest] prints shit about the file, ie. filetest test#n");
}

/*void cmd_file(){
	new_file("file 2", "DESC\0");
}*/

void cmd_file(char* cmd){
	char name[100];
	strclrfull(name, 100);
	strcut(cmd, name, 5);
	new_file(name, "");
}

void cmd_tag(char* cmd){
	char name[100];
	strclrfull(name, 100);
	char tag[100];
	strclrfull(tag, 100);
	strcut(cmd, name, 4);
	for(int i = 0; i < 100; i++){
		if(name[i] == ' '){
			strcut(name, tag, i);
		}
	}
	File file;
	if(open_file(&file, name) == 1){
		print("#c04fopen failed :(#n");
		print("#c07");
		return;
	}
	strcpy(tag, file.desc);
	close_file(&file);
}

void cmd_filetest(char* cmd){
	char name[100];
	strclrfull(name, 100);
	strcut(cmd, name, 9);
	File file;
	if(open_file(&file, name) == 1){
		print("#c04fopen failed :(#n");
		print("#c07");
		return;
	}
	print("filename: ");
	print(file.name);
	print("#n");
	print("description: ");
	print(file.desc);
	print("#n");
}
