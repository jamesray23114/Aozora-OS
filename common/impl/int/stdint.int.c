#include <lib/cpu.h>

#define INTFUNC __attribute__((interrupt)) void
#define PUTINT(message, ...) printf(message " ran at %x, halting. " __VA_ARGS__ "\n", stack->ip)
#define HALTINT(name, message, ...) INTFUNC name(frame* stack) { PUTINT(message, __VA_ARGS__); cpu_halt(); }
#define EHALTINT(name, message, ...) INTFUNC name(frame* stack, uintn err) { PUTINT(message, __VA_ARGS__); cpu_halt(); }

typedef struct interrupt_frame_s
{
    uintn ip;
    uintn cs;
    uintn flags;
    uintn sp;
    uintn ss;
} frame;

INTFUNC int_divzero(frame* stack)
{
    PUTINT("Divide By Zero Exception (#DE)");
    stack->ip += 2; // TODO: dynamically determine the number of bytes we need to skip to resume intruction, may be worthwhile to have this halt instead, as this SHOULD NOT happen
}

HALTINT(int_stdint, "Standard Interrupt"); // TODO: find way to figure out which interrupt ran this and print it, may need to create a different one for each interrupt
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
#undef PUTINT
#undef INTFUNC