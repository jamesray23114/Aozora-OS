#include <lib/int/apic.h>
#include <lib/cpu.h>

bool apic_init()
{
    uint eax, edx;

    __get_cpuid(1, null, null, null, &edx); // TODO: replace with function that gets cpuid features
    if(!(edx & (1 << 9))) // check for apic
        return false;   
    
    asm(".intel_syntax noprefix"); // TODO: set all static inline asembly to be intel syntax
    asm volatile 
    (
        "push ax;"
        "mov al, 0xff;"
        "out 0xa1, al;"
        "out 0x21, al;"
        "pop rax;"
    );
    asm(".att_syntax prefix");

    // TODO: replace with single static inline statement
    cpu_getMSR(0x1B, &eax, &edx);
    eax &= 0xfffff000;
    eax |= 0x800;
    cpu_setMSR(0x1B, eax, edx);

    gl_putnum(eax, 16, 0, 0);
}
