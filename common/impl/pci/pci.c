#include <lib/pci/pci.h>

#define PRINTPCI(string, bus, device, function, data) gl_print_string(string); gl_print_string("BUS "); gl_print_num(bus, 10, 1, 0); gl_print_string(" DEV "); gl_print_num(device, 10, 1, 0); gl_print_string(" FUN "); gl_print_num(function, 10, 1, 0); gl_print_string(": "); gl_print_num(data, 16, 8, '0'); gl_print_string("\n\r");

void print_all_pci_devices()
{
    uint16 bus;
    byte device;
    byte function;

    for (bus = 0; bus < 256; bus++)    
        for (device = 0; device < 64; device++)      
            for(function = 0; function < 4; function++)
                print_single_pci_device(bus, device, function); 
        
    
}

void print_single_pci_device(byte bus, byte device, byte function)
{
    uint32 data = pci_read(bus, device, function, 0);
    if(data != 0xFFFFFFFF)
    {
        PRINTPCI("VID -> ", bus, device, function, data);
        data = pci_read(bus, device, function, 8);
        PRINTPCI("USE -> ", bus, device, function, data);
    }
}