#include <lib/cpu.h>
#include <lib/int/apic.h>
#include <lib/int/int.h>

#define PUTHALT(message, ...) printf(message " ran at %x, halting. " __VA_ARGS__ "\n", stack->ip)
#define HALTINT(name, message, ...) INTFUNC name(frame* stack) { asm("cli"); PUTHALT(message, __VA_ARGS__); cpu_halt(); }
#define EHALTINT(name, message, ...) INTFUNC name(frame* stack, uintn err) { asm("cli"); PUTHALT(message, __VA_ARGS__); cpu_halt(); }

INTFUNC int_stdint(frame* stack)
{
    printf("stdint ran\n");
    EOI();
}

INTFUNC int_divzero(frame* stack)
{
    printf("Divide By Zero Exception (#DE) ran at %x\n", stack->ip);
    stack->ip += 2; // TODO: dynamically determine the number of bytes we need to skip to resume intruction, may be worthwhile to have this halt instead, as this SHOULD NOT happen
}

HALTINT(int_debug, "UNUSED: Debug Exception (#DB)");
HALTINT(int_nmi, "TODO: Non-Maskable Interrupt (NMI)");
HALTINT(int_breakpoint, "TODO: Breakpoint (#BP)");
HALTINT(int_overflow, "TODO: Overflow Exception (#OF)");
HALTINT(int_range, "TODO: Range Exception (#BR)");
HALTINT(int_invopcode, "TODO: Invalid Opcode (#UD)");
HALTINT(int_devna, "UNUSED: Device Not Avalaible Exception (#NM)", "FPU cannot be found or was somehow disabled, this is not intended within Aozora-OS.");
EHALTINT(int_doublefault, "Double Fault (#DF)");
EHALTINT(int_invtss, "UNUSED: Invalid TSS Exception (#TS)", "Aozora-OS uses software task switching.");
EHALTINT(int_segmentna, "UNUSED: Segment Not Found Exception (#NP)");
EHALTINT(int_ssfault, "UNUSED: Stack Segment Fault (#SS)", "Aozora-OS does not dynamically alter the stack.");
EHALTINT(int_gpfault, "TODO: General Protection Fault (#GP)");
EHALTINT(int_pagefault, "TODO: Page Fault (#PF)");
HALTINT(int_float, "x87 Floating-Point Exception (#MF)");
EHALTINT(int_aligncheck, "UNUSED: Alignment Check (#AC)");
HALTINT(int_devicechesk, "UNUSED: Machine Check (#MC)");
HALTINT(int_simd, "SIMD Floating-Point Exception (#XM)");
HALTINT(int_virt, "UNUSED: Virtualization Exception (#VE)");
EHALTINT(int_control, "UNUSED: Control Protection Exception (#CP)");
HALTINT(int_vminject, "UNUSED: Hypervisor Injection Exception (#HV)");
EHALTINT(int_vmmcomm, "UNUSED: VMM Communication Exception (#VC)");
EHALTINT(int_security, "UNUSED: Security Exception (#SX)");

#undef EHALTFUNC
#undef HALTFUNC
#undef PUTHALT
#undef INTFUNC