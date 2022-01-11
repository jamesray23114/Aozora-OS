#pragma once

#include <typedef.h>
#include <lib/io.h>
#include <lib/gl/text.h>

#define PCIMAP pci_memmap

typedef struct pci_device_s pci_device;

void    pci_printAllDevices();
void    pci_printAllDevicesExt();
void    pci_addDevices();
void    pci_printDevice(pci_device device);
void    pci_printDeviceExt(pci_device device);

pci_device pci_getDevice(uintn class, uintn subclass);

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

static pci_device* pci_memmap = (pci_device*) 0x14480; // TODO: check if location exists at boot

static inline uint32 pci_read(pci_device dev, uint8 offset)
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

static inline void pci_write(pci_device dev, uint8 offset, uint32 data) 
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
