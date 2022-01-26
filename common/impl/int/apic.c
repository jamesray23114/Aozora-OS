#include <lib/int/apic.h>
#include <lib/cpu.h>
#include <lib/io.h>

#define APIC_BASE 0xFEE00000

static inline void apic_write(const uint reg, uint data)
{
    uint* mem = (uint*) APIC_BASE;

    mem[reg / sizeof(uint)] = data;
}

static inline uint apic_read(const uint reg)
{
    uint* mem = (uint*) APIC_BASE;

    return mem[reg / sizeof(uint)];
}

bool apic_init()
{

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

    
    cpu_setMSR(0x1B, APIC_BASE, 0);

    apic_write(0x3E0, 0b1011);
    apic_write(0x380, 0xFFFFFFFF);

    int i = 0;
    while (true)
    {
        printf("timer: %d\n", apic_read(0x390));
        gl_setCursor(0, 0);
    }
}
