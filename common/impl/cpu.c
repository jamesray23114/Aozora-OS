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

    for(int i = 0; i < 256; i++)
        cpu_addHandler(int_stdint, i, false);


    idtr[0] = 255;
    idtr[1] = 255;
    idtr[3] = 0x10; 

    asm volatile ("cli\n lidt %0" : : "m"(idtr));

    cpu_addHandler(int_divzero,     0, true);
    cpu_addHandler(int_debug,       1, true);
    cpu_addHandler(int_nmi,         2, true);
    cpu_addHandler(int_breakpoint,  3, true);
    cpu_addHandler(int_overflow,    4, true);
    cpu_addHandler(int_range,       5, true);
    cpu_addHandler(int_invopcode,   6, true);
    cpu_addHandler(int_devna,       7, true);
    cpu_addHandler(int_doublefault, 8, true);
    cpu_addHandler(int_invtss,      10, true);
    cpu_addHandler(int_segmentna,   11, true);
    cpu_addHandler(int_ssfault,     12, true);
    cpu_addHandler(int_gpfault,     13, true);
    cpu_addHandler(int_pagefault,   14, true);
    cpu_addHandler(int_float,       16, true);
    cpu_addHandler(int_aligncheck,  17, true);
    cpu_addHandler(int_devicechesk, 18, true);
    cpu_addHandler(int_simd,        19, true);
    cpu_addHandler(int_virt,        20, true);
    cpu_addHandler(int_control,     21, true);
    cpu_addHandler(int_vminject,    28, true);
    cpu_addHandler(int_vmmcomm,     29, true);
    cpu_addHandler(int_security,    30, true);
    
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
