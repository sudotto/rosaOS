#ifndef DISK
#define DISK

#include <stdint.h>

// ATA PORTS

// tip: (low, med, high bytes are basically just parts that make up one larger number) 

#define ATA_DATA        0x1F0                    // where the data is
#define ATA_SECTORS     0x1F2                    // how many sectors to read
#define ATA_LBA_LOW     0x1F3                    // low byte of sector address 
#define ATA_LBA_MID     0x1F4                    // mid byte
#define ATA_LBA_HIGH    0x1F5                    // high byte
#define ATA_DISK        0x1F6                    // which disk
#define ATA_CMD         0x1F7                    // what to do, read, write, etc.
#define ATA_STATUS      0x1F7                    // return flag, ie. did it work or not

// WAIT FOR ATA

void ata_wait();                                         // wait for drive ot be ready

// WRITE SECTOR

uint8_t ata_write_sector(uint32_t lba, uint8_t* data);  // write to a sector

// READ SECTOR

uint8_t ata_read_sector(uint32_t lba, uint8_t* buffer); // write to a sector

#endif
