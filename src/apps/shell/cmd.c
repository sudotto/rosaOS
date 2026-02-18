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
	print("  #c03[test]     #c07prints \"works\"#n");
	print("  #c03[diskw]    #c07writes letter a to disk#n");
	print("  #c03[diskr]    #c07reads the spot that diskw writes to#n");
	print("  #c03[otter]    #c07otter#n");
	print("  #c03[colors]   #c07prints vga colors#n");
	print("  #c03[echo]     #c07prints whatever you write after echo, ie. echo hello#n");
	print("  #c03[file]     #c07makes a file with name provided file, ie. file test#n");
	print("  #c03[name]     #c07renames file, ie. name test newname#n");
	print("  #c03[tag]      #c07sets the description of given file, ie. tag test tagged#n");
	print("  #c03[del]      #c07deletes file, ie. del test#n");
	print("  #c03[list]     #c07prints all filenames on disk#n");
	print("  #c03[filetest] #c07prints shit about the file, ie. filetest test#n");

}

/*void cmd_file(){
	new_file("file 2", "DESC\0");
}*/

void cmd_file(char* cmd){
	char name[100];
	strclrfull(name, 100);
	strcut(cmd, name, 5);
	if(!strcmp(name, "")){
		print("#c04[ERROR] you gotta tell me what to call the file, come on man#n");
		print("#c07");
		return;
	}
	new_file(name, "");
}

void cmd_name(char* cmd){
	char name[100];
	strclrfull(name, 100);
	char new[100];
	strclrfull(new, 100);
	strcut(cmd, name, 5);
	for(int i = 0; i < 100; i++){
		if(name[i] == ' '){
			char dump[100];
			strcut(name, new, i);
			strcpy(new, dump);
			strcut(dump, new, 1);
			new[strlen(new) - 1] = 0;
			break;
		}
	}
	File file;
	if(!strcmp(name, "")){
		print("#c04[ERROR] i need a filename, IDIOT#n");
		print("#c07");
		return;
	}
	if(!strcmp(new, "")){
		print("#c04[ERROR] oh yeah, lemme just rename ");
		print(name);
		print(" to \"\" i'll do that right away#n");
		print("#c07");
		return;
	}
	if(open_file(&file, name) == 1){
		print("#c04[ERROR] you typed the name wrong#n");
		print("#c07");
		return;
	}
	strclrfull(file.name, 100);
	strcpy(new, file.name);
	close_file(&file);
}

void cmd_tag(char* cmd){
	char name[100];
	strclrfull(name, 100);
	char tag[100];
	strclrfull(tag, 100);
	strcut(cmd, name, 4);
	for(int i = 0; i < 100; i++){
		if(name[i] == ' '){
			char dump[100];
			strcut(name, tag, i);
			strcpy(tag, dump);
			strcut(dump, tag, 1);
			tag[strlen(tag)-1] = 0;
			break;
		}
	}
	File file;
	if(!strcmp(name, "")){
		print("#c04[ERROR] i need a filename, IDIOT#n");
		print("#c07");
		return;
	}
	if(!strcmp(tag, "")){
		print("#c04[ERROR] i can't set the file tag to nothing#n");
		print("#c07");
		return;
	}
	if(open_file(&file, name) == 1){
		print("#c04[ERROR] you typed the name wrong#n");
		print("#c07");
		return;
	}
	strcpy(tag, file.desc);
	close_file(&file);
}

void cmd_list(){
	list_fs();
}

void cmd_del(char* cmd){
	char name[32];
	strclrfull(name, 32);
	strcut(cmd, name, 4);
	File file;
	if(open_file(&file, name) == 1){
		print("#c04[ERROR] you typed the name wrong#n");
		print("#c07");
		return;
	}
	del_file(&file);
}

void cmd_filetest(char* cmd){
	char name[100];
	strclrfull(name, 100);
	strcut(cmd, name, 9);
	File file;
	if(open_file(&file, name) == 1){
		print("#c04[ERROR] you typed the name wrong#n");
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
