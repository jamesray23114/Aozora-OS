#include <lib/io/pci/pci.h>
#include <lib/io/pci/pci_class.h>

static inline uint32 _read(uint32 bus, uint32 device, uint32 func, uint8 offset)
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

void pci_printDevice(pci_device device)
{
    gl_puts("bus: ");
    gl_putnum(device.bus, 10, 3, '0');
    gl_puts(" / device: ");
    gl_putnum(device.device, 10, 3, '0');    
    gl_puts(" / function: ");
    gl_putnum(device.function, 10, 3, '0');   

    gl_puts(" -> ");
    gl_puts(pci_toString(device.class, device.subclass));
    gl_puts("\n\r");
}

void pci_printDeviceExt(pci_device device)
{
    gl_puts("bus: ");
    gl_putnum(device.bus, 10, 3, '0');
    gl_puts(" / device: ");
    gl_putnum(device.device, 10, 3, '0');    
    gl_puts(" / function: ");
    gl_putnum(device.function, 10, 3, '0');   

    gl_puts(" -> ");
    gl_puts(pci_toString(device.class, device.subclass));
    gl_puts("\n\r");

    gl_puts(" -> vender id: ");
    gl_putnum(device.vendorid, 16, 4, '0');
    gl_puts(" / device id: ");
    gl_putnum(device.deviceid, 16, 4, '0');
    gl_puts("\n\r");

    gl_puts(" -> interface: ");
    gl_putnum(device.intr, 16, 0, 0);
    gl_puts(" / header: ");
    gl_putnum(device.header_ver, 10, 0, 0);
    gl_puts("\n\r");


    uint32 data = pci_read(device, 4);

    gl_puts(" -> command reg:");

    if(data & 0b00000000000000000000000000000001)
        gl_puts(" IO ");
    if(data & 0b00000000000000000000000000000010)
        gl_puts(" MEM ");
    if(data & 0b00000000000000000000000000000100)
        gl_puts(" BUS ");
    if(data & 0b00000000000000000000000000001000)
        gl_puts(" SPC ");
    if(data & 0b00000000000000000000000000010000)
        gl_puts(" GMW ");
    if(data & 0b00000000000000000000000000100000)
        gl_puts(" VGA ");
    if(data & 0b00000000000000000000000001000000)
        gl_puts(" ER ");
    if(data & 0b00000000000000000000000100000000)
        gl_puts(" SERR ");
    if(data & 0b00000000000000000000001000000000)
        gl_puts(" FBB ");
    if(data & 0b00000000000000000000001000000000)
        gl_puts(" INTD ");

    gl_puts("\n\r -> status reg:");

    if(data & 0b00000000000010000000000000000000)
        gl_puts(" INT ");
    if(data & 0b00000000000100000000000000000000)
        gl_puts(" CPL ");
    if(data & 0b00000000001000000000000000000000)
        gl_puts(" 66MHz ");
    if(data & 0b00000000100000000000000000000000)
        gl_puts(" FBB ");
    if(data & 0b11000001000000000000000000000000)
        gl_puts(" ER ");
    if(data & 0b00111000000000000000000000000000)
        gl_puts(" EXIT ");

    gl_puts("\n\r");
}

void pci_printAllDevices()
{
    int count = PCIMAP[0].deviceid;

    for(int i = 1; i < count; i++)
    {
        gl_puts("PCI: ");
        gl_putnum(i - 1, 10, 2, ' ');
        gl_puts(" / ");
        pci_printDevice(PCIMAP[i]);
    }
}

void pci_printAllDevicesExt()
{
    int count = PCIMAP[0].deviceid;

    for(int i = 1; i < count; i++)
    {
        gl_puts("PCI: ");
        gl_putnum(i - 1, 10, 2, ' ');
        gl_puts("\n\r -> ");
        pci_printDeviceExt(PCIMAP[i]);
        gl_puts("\n\r");
    }
}

void pci_addDevices()
{
    uint16 bus;
    byte device;
    byte function;

    int count = 1;

    for (bus = 0; bus < 256; bus++)    
        for (device = 0; device < 64; device++)      
            for(function = 0; function < 4; function++)
            {
                pci_device pci;

                uint32 id =     _read(bus, device, function, 0);
                uint32 class =  _read(bus, device, function, 8);
                uint32 etc =    _read(bus, device, function, 12);

                if(id != 0xFFFFFFFF)
                {
                    pci.bus = bus;
                    pci.device = device;
                    pci.function = function;

                    pci.deviceid    = (uint16)(id >> 16);
                    pci.vendorid    = (uint16)(id);

                    pci.class       = (byte)(class >> 24);
                    pci.subclass    = (byte)(class >> 16);
                    pci.intr        = (byte)(class >> 8);
                    pci.version     = (byte)(class);

                    pci.bist        = (byte)(etc >> 24);
                    pci.header_ver  = (byte)(etc >> 16);

                    PCIMAP[count++] = pci;
                }
            }
    
    PCIMAP[0].deviceid = count;
}

pci_device pci_getDevice(uintn class, uintn subclass) // returns a device with a header version of 100 if no device is found
{
    uintn size = PCIMAP[0].deviceid;

    for(int i = 1; i < size + 1; i++)
        if(PCIMAP[i].class == class && PCIMAP[i].subclass == subclass)
            return PCIMAP[i];

    pci_device na = {.header_ver = 100};
    return na; 
}