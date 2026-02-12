#include "io.h"
#include "disk.h"
#include "string.h"
#include "memory.h"

#include "fs.h"

void new_file(char* name, char* desc){
	File file;

	file.init = true;
	file.sector = -1;

	strclrfull(file.name, 32);
	strcpy(name, file.name);

	strclrfull(file.desc, 32);
	strcpy(desc, file.desc);


	strclrfull(file.data, DATA_SIZE);
	close_file(&file);
}

int open_file(File* file, char* filename){
	char buffer[512] = {0};
	int offset = 1;  // +1 at start bc of init flag
	int sector = search_fs(filename); 
	if(sector == -1){
		return 1;
	}
	if(ata_read_sector(sector + FS_START, buffer) == 1){
		return 1;
	}
	file->sector = sector;
	for(int i = 0; i < 32; i++){
		file->name[i] = buffer[i+offset]; 
	}
	offset += 32;
	file->name[31] = 0;

	for(int i = 0; i < 32; i++){
		file->desc[i] = buffer[i+offset]; 
	}
	file->desc[31] = 0;
	offset += 32;

	char psector[4];
	strcut(buffer, psector, offset);
	file->psector = psector[0] | psector[1] | psector[2] | psector[3] << 8;
	strclrfull(file->data, DATA_SIZE);
	return 0;
}

int close_file(File* file){
	char buffer[FILE_SIZE];
	strclrfull(buffer, FILE_SIZE);
	buffer[0] = 1;

	// FILENAME

	file->name[strlen(file->name)] = 10;
	strcat(buffer, file->name);
	for(int i = 0; i < 32 - strlen(file->name); i++){ // padding
		strpush(buffer, 10);
	}

	// DESC

	strcat(buffer, file->desc);
	for(int i = 0; i < 32 - strlen(file->desc); i++){ // padding
		strpush(buffer, 10);
	}

	// PSEC

	unsigned char psector[4];
	psector[0] = (file->psector >> 24) & 0xFF;
	psector[1] = (file->psector >> 16) & 0xFF;
	psector[2] = (file->psector >> 8) & 0xFF;
	psector[3] = file->psector & 0xFF;
	for(int i = 0; i < 4; i++){
		strpush(buffer, psector[i]);
	}

	// DATA SEG

	for(int i = 0; i < DATA_SIZE; i++){
		strpush(buffer, file->data[i]);
	}

	// SAVING

	for(int sector = 0; sector < FILE_SIZE / 512; sector++){
		int offset = sector * 512;
		char buffer2[512] = {0};
		for(int byte = 0; byte < 512; byte++){
			if(buffer[byte + offset] == 10){
				buffer[byte + offset] = 0;
			}
			buffer2[byte] = buffer[byte + offset];
		}
		if(file->sector == -1){
			file->sector = end_of_fs();
		}
		if(ata_write_sector(file->sector + offset + FS_START, buffer) == 1){
			return 1;
		}
	}
	return 0;
}

int new_fs(){
	for(int i = 0; i < 512; i++){
		char buffer[512] = {0};
		int sector = i * (FILE_SIZE / 512);
		for(int j = 0; j < FILE_SIZE; i++){
			buffer[j] = 0;
		}
		if(ata_write_sector(10, buffer) == 1){
			return 1;
		}
	}
	return 0;
}

int search_fs(char* filename){
	for(int file = 0; file < end_of_fs(); file++){
		char buffer[512] = {0};
		char diskname[32];
		int sector = file * (FILE_SIZE / 512);
		if(ata_read_sector(sector + FS_START, buffer) == 1){
			return -1;
		}
		for(int j = 0; j < 32; j++){
			diskname[j] = buffer[j + 1]; 
		}
		diskname[31] = 0;
		if(!strcmp(filename, diskname)){
			return file;
		}
	}
	return -1;
}

int end_of_fs(){
	for(int file = 0; file < 512; file++){
		char buffer[512] = {0};
		int sector = file * (FILE_SIZE / 512);
		if(ata_read_sector(sector + FS_START, buffer) == 1){
			return -1;
		}
		if(buffer[0] == 0){
			return sector;
		}
	}
}
