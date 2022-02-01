#pragma once

#include <cpuid.h>

#include <typedef.h>
#include <lib/cpu.h>
#include <lib/acpi.h>
#include <lib/gl/text.h>

#define APIC_BASE 0xFEE00000

bool apic_init(acpi_apic_table madt);
void apic_addIrq(byte irq, byte vector);

inline void apic_write(const uint reg, uint data)
{
    *((volatile uint32*) APIC_BASE + (reg / sizeof(uint32))) = data;
}

inline uint32 apic_read(const uint32 reg)
{
    return *((volatile uint32*) APIC_BASE + reg / sizeof(uint32));
}

void int_timer(frame* stack);