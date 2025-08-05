#include <stdint.h>

#include "memory.h"
#include "vga.h"

#include "disk.h"

// WAIT FOR ATA

void ata_wait(){                                 // wait for drive ot be ready
	while (inb(ATA_STATUS) & 0x80){};            // wait for BSY (busy) to be false
	while (!(inb(ATA_STATUS) & 0x08)){};         // Wait for DRQ (read for data) to be true
}

// VERIFY DRIVE

uint8_t ata_verify_drive(){
	outb(ATA_DISK, 0xE0);
	uint8_t exists = inb(ATA_STATUS);
	if(exists == 0x00){
		println("drive doesnt exist");
		return 1;
	}
	return 0;
}

// WRITE SECTOR

uint8_t ata_write_sector(uint32_t lba, uint8_t* data){    // write to a sector
	if(ata_verify_drive()){return 1;};
	outb(ATA_SECTORS, 1);                                  // read 1 sector
	outb(ATA_LBA_LOW, (uint8_t)(lba));                     // | 
	outb(ATA_LBA_MID, (uint8_t)(lba >> 8));                // | specify the adress
	outb(ATA_LBA_HIGH, (uint8_t)(lba >> 16));              // |
	outb(ATA_DISK, 0xE0 | ((lba >> 24) & 0x0F));           // use the LBA to find the disk
	outb(ATA_CMD, 0x30);                                   // tell it to open sector for writing 
	ata_wait();                                            // wait for ata
	for (int i = 0; i < 256; i++) {                        // | write data to ata
		uint16_t word = ((uint16_t)data[i * 2]) | ((uint16_t)data[i * 2 + 1] << 8); // combine high and low
		outw(ATA_DATA, word);                              // |  
	}
	//ata_wait();                                          // wait for ata
	return inb(ATA_STATUS);                                // return :)
}

// READ SECTOR

uint8_t ata_read_sector(uint32_t lba, uint8_t* buffer){   // write to a sector
	if(ata_verify_drive()){return 1;};
	outb(ATA_SECTORS, 1);                                  // read 1 sector
	outb(ATA_LBA_LOW, (uint8_t)(lba));                     // | 
	outb(ATA_LBA_MID, (uint8_t)(lba >> 8));                // | specify the adress
	outb(ATA_LBA_HIGH, (uint8_t)(lba >> 16));              // |
	outb(ATA_DISK, 0xE0 | ((lba >> 24) & 0x0F));           // use the LBA to find the disk
	outb(ATA_CMD, 0x20);                                   // tell it to open sector for reading
	ata_wait();                                            // wait for ata
	for (int i = 0; i < 256; i++) {                            // | write ata to buffer
		uint16_t word = inw(ATA_DATA);                         // | 
		buffer[i * 2] = (uint8_t)(word & 0x00FF);
		buffer[i * 2 + 1] = (uint8_t)((word >> 8) & 0x00FF);
	}
	printc(buffer[0]);
	//ata_wait();                                          // wait for ata
	return inb(ATA_STATUS);                                // return :)
}
