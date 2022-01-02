#include <lib/pci/pci.h>
#include <lib/pci/pci_class.h>

void print_single_pci_device(pci_device device)
{
    gl_print_string("bus: ");
    gl_print_num(device.bus, 10, 3, '0');
    gl_print_string(" / device: ");
    gl_print_num(device.device, 10, 3, '0');    
    gl_print_string(" / function: ");
    gl_print_num(device.function, 10, 3, '0');   

    gl_print_string(" -> ");
    gl_print_string(pci_class_to_string(device.class, device.subclass));
    gl_print_string("\n\r");
}

void print_single_pci_device_long(pci_device device)
{
    gl_print_string("bus: ");
    gl_print_num(device.bus, 10, 3, '0');
    gl_print_string(" / device: ");
    gl_print_num(device.device, 10, 3, '0');    
    gl_print_string(" / function: ");
    gl_print_num(device.function, 10, 3, '0');   

    gl_print_string(" -> ");
    gl_print_string(pci_class_to_string(device.class, device.subclass));
    gl_print_string("\n\r");

    gl_print_string(" -> vender id: ");
    gl_print_num(device.vendorid, 16, 4, '0');
    gl_print_string(" / device id: ");
    gl_print_num(device.deviceid, 16, 4, '0');
    gl_print_string("\n\r");

    gl_print_string(" -> interface: ");
    gl_print_num(device.intr, 10, 0, 0);
    gl_print_string(" / header: ");
    gl_print_num(device.header_ver, 10, 0, 0);
    gl_print_string("\n\r");


    uint32 data = pci_read(device.bus, device.device, device.function, 4);

    gl_print_string(" -> command reg:");

    if(data & 0b00000000000000000000000000000001)
        gl_print_string(" IO ");
    if(data & 0b00000000000000000000000000000010)
        gl_print_string(" MEM ");
    if(data & 0b00000000000000000000000000000100)
        gl_print_string(" BUS ");
    if(data & 0b00000000000000000000000000001000)
        gl_print_string(" SPC ");
    if(data & 0b00000000000000000000000000010000)
        gl_print_string(" GMW ");
    if(data & 0b00000000000000000000000000100000)
        gl_print_string(" VGA ");
    if(data & 0b00000000000000000000000001000000)
        gl_print_string(" ER ");
    if(data & 0b00000000000000000000000100000000)
        gl_print_string(" SERR ");
    if(data & 0b00000000000000000000001000000000)
        gl_print_string(" FBB ");
    if(data & 0b00000000000000000000001000000000)
        gl_print_string(" INTD ");

    gl_print_string("\n\r -> status reg:");

    if(data & 0b00000000000010000000000000000000)
        gl_print_string(" INT ");
    if(data & 0b00000000000100000000000000000000)
        gl_print_string(" CPL ");
    if(data & 0b00000000001000000000000000000000)
        gl_print_string(" 66MHz ");
    if(data & 0b00000000100000000000000000000000)
        gl_print_string(" FBB ");
    if(data & 0b11000001000000000000000000000000)
        gl_print_string(" ER ");
    if(data & 0b00111000000000000000000000000000)
        gl_print_string(" EXIT ");

    gl_print_string("\n\r");
}

void print_all_pci_devices()
{
    int count = PCIMAP[0].deviceid;

    for(int i = 1; i < count; i++)
    {
        gl_print_string("PCI: ");
        gl_print_num(i - 1, 10, 2, ' ');
        gl_print_string(" / ");
        print_single_pci_device(PCIMAP[i]);
    }
}

void print_all_pci_devices_long()
{
    int count = PCIMAP[0].deviceid;

    for(int i = 1; i < count; i++)
    {
        gl_print_string("PCI: ");
        gl_print_num(i - 1, 10, 2, ' ');
        gl_print_string("\n\r -> ");
        print_single_pci_device_long(PCIMAP[i]);
        gl_print_string("\n\r");
    }
}

void pci_add_memmap()
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

                uint32 id = pci_read(bus, device, function, 0);
                uint32 class = pci_read(bus, device, function, 8);
                uint32 etc = pci_read(bus, device, function, 12);

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