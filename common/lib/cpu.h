#pragma once

#include <typedef.h>
#include <aoslib.h>
#include <lib/memory.h>

typedef struct interrupt_frame_s frame;

typedef struct interrupt_descriptor_s {
   uint16 offset_1;        // offset bits 0..15
   uint16 selector;        // a code segment selector in GDT or LDT
   uint8  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8  type_attributes; // gate type, dpl, and p fields
   uint16 offset_2;        // offset bits 16..31
   uint32 offset_3;        // offset bits 32..63
   uint32 zero;            // reserved
} interrupt_descriptor;

static interrupt_descriptor* idt = (interrupt_descriptor*) 0x1000;

void cpu_enablePaging();
void cpu_enableInt();
void cpu_addHandler(void* func, byte vec, bool istrap);

void int_stdint(frame* stack);
void int_divzero(frame* stack);

static inline void cpu_getMSR(uint32 msr, uint32 *lo, uint32 *hi) { asm volatile("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr)); }
static inline void cpu_setMSR(uint32 msr, uint32 lo, uint32 hi) { asm volatile("wrmsr" : : "a"(lo), "d"(hi), "c"(msr)); }
static inline void cpu_halt() { asm volatile( "hlt" ); }