#include "io.h"
#include "disk.h"
#include "string.h"

#include "fs.h"

File new_file(char* name, char* desc){
	print(" > start of newfile");
	File file;
	strcpy(name, file.name);
	strcpy(desc, file.desc);
	print(" > b4 clearing");
	strclrfull(file.data, 24448);
	print(" > cleared file data");
	close_file(&file);
	print(" > fclosed");
	return file;
}

int open_file(File* file){
	char buffer[512] = {0};
	if(ata_read_sector(10, buffer) != 1){                                 // replace 10 with proper LBA
		for(int i = 0; i < 2; i++){
			char buffer2[32];
			strcut(buffer, buffer2, i * 32);
			switch(i){
				case 0:
					strcpy(buffer2, file->name);
					break;
				case 1:
					strcpy(buffer2, file->desc);
					break;
			}
		}
		char buffer2[4];
		strcut(buffer, buffer2, 64);
		int psector = buffer2[0] | buffer2[1] | buffer2[2] | buffer2[3] << 8;
		file->psector = psector;
	}
	strclrfull(file->data, DATA_SIZE);
}

int close_file(File* file){
	char buffer[FILE_SIZE];
	strcat(buffer, file->name);
	for(int i = 0; i < 32 - strlen(file->name); i++){ // padding
		strpush(buffer, '\0');
	}
	print(" > catted and padded name");
	strcat(buffer, file->desc);
	for(int i = 0; i < 32 - strlen(file->desc); i++){ // padding
		strpush(buffer, '\0');
	}
	print(" > catted and padded desc");
	unsigned char psector[4];
	psector[0] = (file->psector >> 24) & 0xFF;
	psector[1] = (file->psector >> 16) & 0xFF;
	psector[2] = (file->psector >> 8) & 0xFF;
	psector[3] = file->psector & 0xFF;
	for(int i = 0; i < 4; i++){
		strpush(buffer, psector[i]);
	}
	print(" > pushed psector");
	for(int i = 0; i < DATA_SIZE; i++){
		strpush(buffer, file->data[i]);
	}
	print(" > pushed data");
	for(int sectors = 0; sectors < FILE_SIZE / 512; sectors++){
		int offset = sectors * 512;
		for(int bytes = 0; bytes < 512; bytes++){
			char buffer2[512] = {0};
			for(int i = 0; i < 512; i++){
				buffer2[i] = buffer[i + offset];
			}
			if(ata_write_sector(10, buffer) == 1){
				print("fclose fucked up :(#n");
			}
			print(" > iterated through sector bytes");
		}
		print(" > moving to new sector");
	}
}
