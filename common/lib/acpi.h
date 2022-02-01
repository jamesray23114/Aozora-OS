#pragma once

#include <aoslib.h>

// TODO: expand `apic_root_table` to allow for more descriptor pointers
typedef struct acpi_root_table_s
{
    void* madt;
    void* dstd;
    void* fadt;
    void* srat;
    void* ssdt;
} acpi_root_table;

typedef struct int_override_s
{
    byte source;
    byte irq;
    byte gsi;
    byte flags;
} int_override;

typedef struct acpi_apic_table_s
{
    uint cpu_count;
    //int_override intsource[32];
    void* local_apic;
    void* sys_interrupt_base;
    void* ioapic;
    byte ioapic_id;
} acpi_apic_table;

acpi_root_table rxdt_parse(void* rsdp);
acpi_apic_table madt_parse(void* madt);

void madt_print(acpi_apic_table info);