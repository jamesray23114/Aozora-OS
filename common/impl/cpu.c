#include <lib/cpu.h>

void cpu_enablePaging()
{
    
}

void cpu_enableInt()
{
    byte idtr[10] = {0};

    uintn stdintloc = ((uintn)int_stdint); 
    interrupt_descriptor std;
    std.offset_1 = stdintloc;
    std.offset_2 = stdintloc >> 16;
    std.offset_3 = stdintloc >> 32;
    std.selector = 0x38;
    std.ist = 0;
    std.type_attributes = 0x8e;

    for(int i = 0; i < 0x1000; i++)
        idt[i] = std;


    idtr[0] = 255;
    idtr[3] = 0x10; 

    asm volatile ("cli\n lidt %0" : : "m"(idtr));
    asm volatile ("sti\n");
    
}

void cpu_addHandler(void* func, byte vec, bool istrap)
{
    uintn funcloc = ((uintn)func);
    interrupt_descriptor desc;
    desc.offset_1 = funcloc;
    desc.offset_2 = funcloc >> 16;
    desc.offset_3 = funcloc >> 32;
    desc.selector = 0x38;
    desc.ist = 0;
    if(istrap)
        desc.type_attributes = 0x8f;
    else
        desc.type_attributes = 0x8e;

    idt[vec] = desc;
}