#pragma once

#include <lib/typedef.h>
#include <lib/gl/text.h>

void  inline outb(int64 address, byte data)  {               asm ( "outb %0, %1\n" : : "a" (data),   "Nd" (address) ); }
byte  inline inb(int64 address)              { byte data;    asm ( "inb %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outw(int64 address, int16 data) {               asm ( "outw %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int16 inline inw(int64 address)              { int16 data;   asm ( "inw %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outl(int64 address, int32 data) {               asm ( "outl %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int32 inline inl(int64 address)              { int32 data;   asm ( "inl %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outq(int64 address, int64 data) {               asm ( "outq %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int64 inline inq(int64 address)              { int64 data;   asm ( "inq %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void    print_all_pci_devices();
void    print_single_pci_device(byte bus, byte device, byte function);
void    pci_add_memmap();
void    pci_add_single_memmap(byte bus, byte device);

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
void    pci_write(uint8 bus, uint8 device, uint8 func, uint8 offset, uint32 data);