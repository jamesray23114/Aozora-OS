#include <lib/int/apic.h>
#include <lib/cpu.h>
#include <lib/io/io.h>

uint32* ioapic_base = (uint32*) 0xfec00000;

inline void ioapic_write(const uint32 reg, uint data)
{
    *((volatile uint32*) ioapic_base) = reg;
    *((volatile uint32*) ioapic_base + 4) = data;
}

inline uint32 ioapic_read(const uint reg)
{
    *((volatile uint32*) ioapic_base) = reg;
    return *((volatile uint32*) ioapic_base + 4); 
}

bool apic_init(acpi_apic_table madt)
{
    asm(".intel_syntax noprefix"); // TODO: set all static inline asembly to be intel syntax
    asm volatile 
    (
        "push rax;"
        "mov al, 0xff;"
        "out 0xa1, al;"
        "out 0x21, al;"
        "pop rax;"
    );
    asm(".att_syntax prefix");

    ioapic_base = (uint32*) madt.ioapic;
    
    asm ("sti\n");
    cpu_setMSR(0x1B, APIC_BASE | 0x800, 0); 

    // TODO: write a proper timer interrupt handler

    apic_write(0xF0,  0x1ff);           // enable spurious interrupts
    apic_write(0x3E0, 0b1010);          // set divide clock register to 128 
    apic_write(0x380, 1000000);         // wait x clock cycles 
    apic_write(0x320, 0x20020);         // make clock repeat and trigger interrupt 32

    cpu_addHandler(int_timer, 0x20, false);

    ioapic_write(0x12, 0b00000000000100001);
    ioapic_write(0x28, 0b00000000000100010);

    asm ("cli\n");
}

void apic_addIrq(byte irq, byte vector)
{
    
}