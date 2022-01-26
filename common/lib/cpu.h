#pragma once

#include <typedef.h>
#include <aoslib.h>
#include <lib/memory.h>

typedef struct interrupt_frame_s frame;

typedef struct interrupt_descriptor_s {
   uint16 offset_1;        
   uint16 selector;        
   uint8  ist;             
   uint8  type_attributes; 
   uint16 offset_2;        
   uint32 offset_3;        
   uint32 zero;            
} interrupt_descriptor;

static interrupt_descriptor* idt = (interrupt_descriptor*) 0x1000;

void cpu_enablePaging();
void cpu_enableInt();
void cpu_addHandler(void* func, byte vec, bool istrap);
void cpu_addStdInts();

// INTERRUPTS: this is a list of all interrupts available to the kernel, the description of these interrupts may change in user space or in the future.
//
// USAGE:
// avaliable interrupts are ones that are meant to commonly be ran (or it is reasonable for them to be ran, for instance a double fault).
// unused interrupts are ones that are should never used by the os, if one of these are ran something has likely gone very wrong. these are always halting.
// TODO interrupts function as unused currently, but they are planned to be avaliable. 
//
// EXECUTION:
// halting interrupts are ones that halt the processor apon execution, this is typically due to them not being implimented or an error occuring 
// running interrupts are ones that attempt to allow for the resuming of execution after the last ran instruction.
// normal interrupts are ones that attempt to allow for the resuming of execution, rerunning the last read instruction.

// x86-64 exceptions:

void int_stdint(frame* stack);                  // Standard interrupt            -> available / halting
void int_divzero(frame* stack);                 // Divide by zero                -> available / running
void int_debug(frame* stack);                   // Debug                         -> unused / halting        
void int_nmi(frame* stack);                     // Non maskable interrupt        -> TODO / halting
void int_breakpoint(frame* stack);              // Breakpoint                    -> TODO / halting
void int_overflow(frame* stack);                // Overflow after INTO           -> TODO / halting 
void int_range(frame* stack);                   // BOUND instruction failed      -> TODO / halting
void int_invopcode(frame* stack);               // Invalid intruction            -> available / halting
void int_devna(frame* stack);                   // Device not available          -> unused / halting
void int_doublefault(frame* stack, uintn err);  // Double fault                  -> available / halting
void int_invtss(frame* stack, uintn err);       // Invalid TSS                   -> unused / halting
void int_segmentna(frame* stack, uintn err);    // Segment not present           -> unused / halting
void int_ssfault(frame* stack, uintn err);      // Stack segement fault          -> unused / halting 
void int_gpfault(frame* stack, uintn err);      // General protection fault      -> avaliable / halting
void int_pagefault(frame* stack, uintn err);    // Page fault                    -> avaliable / halting
void int_float(frame* stack);                   // Floating point exception      -> avaliable? / halting
void int_aligncheck(frame* stack, uintn err);   // Allignment checking           -> unused / halting
void int_devicechesk(frame* stack);             // Machine check                 -> unused / halting
void int_simd(frame* stack);                    // SIMD Floating-Point           -> unused? / halting
void int_virt(frame* stack);                    // Virtualization                -> unused / halting
void int_control(frame* stack, uintn err);      // Control protection            -> unused / halting   
void int_vminject(frame* stack);                // Hypervisor injection          -> unused / halting   
void int_vmmcomm(frame* stack, uintn err);      // VMM communication             -> unused / halting   
void int_security(frame* stack, uintn err);     // Security                      -> unused / halting 

static inline void cpu_getMSR(uint32 msr, uint32 *lo, uint32 *hi) { asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr)); }
static inline void cpu_setMSR(uint32 msr, uint32 lo, uint32 hi) { asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr)); }
static inline void cpu_halt() { asm volatile( "hlt" ); }