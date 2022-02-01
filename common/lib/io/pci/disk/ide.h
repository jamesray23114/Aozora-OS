#pragma once

#include <typedef.h>
#include <lib/io/pci/pci.h>
#include <lib/gl/gl.h>

// TODO: simplify this file and comment to get better understanding of whats going on

// statuses

#define STA_ATA_BUSY     0x80    // Busy
#define STA_ATA_READY    0x40    // Drive ready
#define STA_ATA_FAULT    0x20    // Drive write fault
#define STA_ATA_SEEK     0x10    // Drive seek complete
#define STA_ATA_DATA     0x08    // Data request ready
#define STA_ATA_FIX      0x04    // Corrected data
#define STA_ATA_IDX      0x02    // Index
#define STA_ATA_ERR      0x01    // Error

// errors

#define ERR_ATA_BAD      0x80    // Bad block
#define ERR_ATA_UNFIX    0x40    // Data uncorrectable
#define ERR_ATA_CHNGE    0x20    // Media changed   
#define ERR_ATA_IDNF     0x10    // ID not found
#define ERR_ATA_MCR      0x08    // Media change requested
#define ERR_ATA_ABORT    0x04    // Command aborted 
#define ERR_ATA_ZRNF     0x02    // track 0 not found
#define ERR_ATA_NOADR    0x01    // no address

// commands

#define CMD_ATA_RD_PIO          0x20
#define CMD_ATA_RD_PIOEXT       0x24
#define CMD_ATA_RD_DMA          0xC8
#define CMD_ATA_RD_DMAEXT       0x25
#define CMD_ATA_WR_PIO          0x30
#define CMD_ATA_WR_PIOEXT       0x24
#define CMD_ATA_WR_DMA          0xCA
#define CMD_ATA_WR_DMAEXT       0x35
#define CMD_ATA_FLUSH           0xE7
#define CMD_ATA_FLUSH_EXT       0xEA
#define CMD_ATA_PACKET          0xA0
#define CMD_ATA_INTETIFY_PACKET 0xA1
#define CMD_ATA_IDENTIFY        0xEC
#define CMD_ATAPI_READ          0xA8
#define CMD_ATAPI_EJECT         0x1B

// indetifies

#define IDF_ATA_DEVICETYPE   0
#define IDF_ATA_CYLINDERS    2
#define IDF_ATA_HEADS        6
#define IDF_ATA_SECTORS      12
#define IDF_ATA_SERIAL       20
#define IDF_ATA_MODEL        54
#define IDF_ATA_CAPABILITIES 98
#define IDF_ATA_FIELDVALID   106
#define IDF_ATA_MAX_LBA      120
#define IDF_ATA_COMMANDSETS  164
#define IDF_ATA_MAX_LBA_EXT  200

// device types

#define ATA     0
#define ATAPI   1
#define MASTER  0
#define SLAVE   1

#define ATA_PRIMARY     0x00
#define ATA_SECONDARY   0x01
#define ATA_READ        0x00
#define ATA_WRITE       0x01

// registers

#define REG_ATA_DATA       0x00
#define REG_ATA_ERROR      0x01
#define REG_ATA_FEATURES   0x01
#define REG_ATA_SECCOUNT0  0x02
#define REG_ATA_LBA0       0x03
#define REG_ATA_LBA1       0x04
#define REG_ATA_LBA2       0x05
#define REG_ATA_HDDEVSEL   0x06
#define REG_ATA_COMMAND    0x07
#define REG_ATA_STATUS     0x07
#define REG_ATA_SECCOUNT1  0x08
#define REG_ATA_LBA3       0x09
#define REG_ATA_LBA4       0x0A
#define REG_ATA_LBA5       0x0B
#define REG_ATA_CONTROL    0x0C
#define REG_ATA_ALTSTATUS  0x0C
#define REG_ATA_DEVADDRESS 0x0D

//

bool ide_init();
// TODO: determine if these functions need to be extern or should be moved into c file
byte ide_read(byte channel, byte reg);
byte ide_write(byte channel, byte reg, byte data);
byte ide_poll(byte channel, bool advanced_check);
void ide_readBuffer(byte channel, byte reg, uint32 buffer, uint32 quads);
//

void ide_printError(unsigned int drive, unsigned char err); // TODO: implement

void ide_readSectors(byte drive, uintn location, uintn sectors, byte* buffer);
void ide_writeSectors(byte drive, uintn location, byte sectors, byte* buffer);