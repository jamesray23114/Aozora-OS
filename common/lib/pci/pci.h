#pragma once

#include <lib/typedef.h>
#include <lib/gl/text.h>

#define PCIMAP pci_memmap

typedef struct pci_device_s pci_device;

void  inline outb(int64 address, byte data)  {               asm volatile ( "outb %0, %1\n" : : "a" (data),   "Nd" (address) ); }
byte  inline inb(int64 address)              { byte data;    asm volatile ( "inb %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outw(int64 address, int16 data) {               asm volatile ( "outw %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int16 inline inw(int64 address)              { int16 data;   asm volatile ( "inw %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outl(int64 address, int32 data) {               asm volatile ( "outl %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int32 inline inl(int64 address)              { int32 data;   asm volatile ( "inl %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outq(int64 address, int64 data) {               asm volatile ( "outq %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int64 inline inq(int64 address)              { int64 data;   asm volatile ( "inq %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void    print_all_pci_devices();
void    print_all_pci_devices_long();
void    pci_add_memmap();
void    print_single_pci_device(pci_device device);
void    print_single_pci_device_long(pci_device device);

inline uint32 pci_read(uint32 bus, uint32 device, uint32 func, uint8 offset)
{
    uint32 adr, tmp;
    adr =   (bus << 16)     | 
            (device << 11)  |
            (func << 8)     | 
            (offset & 0xFC) | 
            0x80000000;
   
    outl(0xCF8, adr);

    return inl(0xCFC);
}

inline void pci_write(uint8 bus, uint8 device, uint8 func, uint8 offset, uint32 data) 
{

};

typedef struct pci_device_s
{
    byte bus;
    byte device;
    byte function;

    uint16 deviceid;
    uint16 vendorid;

    byte class;
    byte subclass;
    byte intr;
    byte version;

    byte header_ver;
    byte bist;

} pci_device;

static pci_device* pci_memmap = (pci_device*) 0x14480;