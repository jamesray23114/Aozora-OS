#pragma once

#include <aoslib.h>
#include <lib/int/apic.h>

#define INTFUNC __attribute__((interrupt)) void
#define EOI() apic_write(0xB0, 0)

typedef struct interrupt_frame_s
{
    uintn ip;
    uintn cs;
    uintn flags;
    uintn sp;
    uintn ss;
} frame;
