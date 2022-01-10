#pragma once

#include <typedef.h>
#include <lib/gl/text.h>

#define PCIMAP pci_memmap

typedef struct pci_device_s pci_device;

void  static inline outb(int64 address, byte data)  {               asm volatile ( "outb %0, %1\n" : : "a" (data),   "Nd" (address) ); }
byte  static inline inb(int64 address)              { byte data;    asm volatile ( "inb %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  static inline outw(int64 address, int16 data) {               asm volatile ( "outw %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int16 static inline inw(int64 address)              { int16 data;   asm volatile ( "inw %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  static inline outl(int64 address, int32 data) {               asm volatile ( "outl %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int32 static inline inl(int64 address)              { int32 data;   asm volatile ( "inl %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  static inline outq(int64 address, int64 data) {               asm volatile ( "outq %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int64 static inline inq(int64 address)              { int64 data;   asm volatile ( "inq %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void    print_all_pci_devices();
void    print_all_pci_devices_long();
void    pci_add_memmap();
void    print_single_pci_device(pci_device device);
void    print_single_pci_device_long(pci_device device);

pci_device get_device(uintn class, uintn subclass);

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

static inline uint32 pci_read(uint32 bus, uint32 device, uint32 func, uint8 offset)
{
    uint32 adr;
    adr =   (bus << 16)     | 
            (device << 11)  |
            (func << 8)     | 
            (offset & 0xFC) | 
            0x80000000;
   
    outl(0xCF8, adr);

    return inl(0xCFC);
}

static inline void pci_write(uint8 bus, uint8 device, uint8 func, uint8 offset, uint32 data) 
{
    uint32 adr;
    adr =   (bus << 16)     | 
            (device << 11)  |
            (func << 8)     | 
            (offset & 0xFC) | 
            0x80000000;

    outl(0xCFC, data);
    outl(0xCF8, adr);
};

static inline uint32 device_read(pci_device dev, uint8 offset)
{
    uint32 adr;
    adr =   (dev.bus << 16)     | 
            (dev.device << 11)  |
            (dev.function << 8) | 
            (offset & 0xFC)     | 
            0x80000000;
   
    outl(0xCF8, adr);

    return inl(0xCFC);
}

static inline void device_write(pci_device dev, uint8 offset, uint32 data) 
{
    uint32 adr;
    adr =   (dev.bus << 16)     | 
            (dev.device << 11)  |
            (dev.function << 8) | 
            (offset & 0xFC)     | 
            0x80000000;

    outl(0xCFC, data);
    outl(0xCF8, adr);
};

static pci_device* pci_memmap = (pci_device*) 0x14480;