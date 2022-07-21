#include <lib/acpi.h>
#include <lib/memory.h>

typedef struct acpi_rsdp_desc_s {
    char signature[8];
    uint8 checksum;
    char oemid[6];
    uint8 revision;
    uint32 unused;
    uint32 length;
    void* xsdt_address;
    uint8 extended_checksum;
    uint8 reserved[3];
} __attribute__ ((packed)) acpi_rsdp_desc; // seperated to avoid attribute issues

typedef struct acpi_xsdt_desc_s {
    char signature[4];
    uint32 length;
    uint8 revision;
    uint8 checksum;
    char oemid[14];
    uint32 oem_revision;
    uint32 creator_id;
    uint32 creator_revision;
} __attribute__ ((packed)) acpi_xsdt_desc;

typedef struct acpi_xsdt_s
{
    acpi_xsdt_desc header;
    uintn desc_array[];
} __attribute__ ((packed)) acpi_xsdt;

typedef struct apic_entry_s
{
    byte entry_type;
    byte record_length;
    union 
    {
        struct // entry 0
        {
            byte proc_id;
            byte apic_id;
            uint32 flags;
        } __attribute__ ((packed)) local_apic;
        struct // entry 1
        {
            byte ioapic_id;
            byte reserved;
            uint32 ioapic_address;
            uint32 sys_interrupt_base;
        } __attribute__ ((packed)) ioapic;
        struct // entry 2
        {
            byte bus_source;
            byte irq_source;
            uint32 global_system_interrupt;
            uint16 flags;
        } __attribute__ ((packed)) ioapic_source_override;
        struct // entry 3
        {
            byte source;
            byte reserved;
            uint16 flags;
            uint32 global_system_interrupt;
        } __attribute__ ((packed)) ioapic_nmi_source;
        struct // entry 4
        {
            byte proc_id;
            uint16 flags;
            byte lint_num; // 0 or 1
        } __attribute__ ((packed)) local_apic_nmi;
        struct // entry 5
        {
            uint16 reserved;
            uintn local_apic_adr;
        } __attribute__ ((packed)) local_apic_override;
    };
} __attribute__ ((packed)) apic_entry;

typedef struct acpi_apic_s
{
    acpi_xsdt_desc header;
    uint32 local_apic;
    uint32 flags;
    apic_entry entries[]; //TODO: find better way of representing
} __attribute__ ((packed)) acpi_apic;

// code


// returns a table of pointers to rxdt descriptors
// pointers returned are null if they dont exist
acpi_root_table rxdt_parse(void* rsdp)
{
    acpi_root_table ret = {0};

    acpi_rsdp_desc* roottable = (acpi_rsdp_desc*) rsdp;
    acpi_xsdt* xsdt = roottable->xsdt_address;

    uint64 count = (xsdt->header.length - sizeof(acpi_xsdt_desc)) / 8;

    for(int i = 0; i < count; i++)
    {
        acpi_xsdt_desc* desc = ((acpi_xsdt_desc*)xsdt->desc_array[i]);

        if(memcmp(desc->signature, "APIC", 4))
            ret.madt = desc;
        else if(memcmp(desc->signature, "DSDT", 4))
            ret.dstd = desc;
        else if(memcmp(desc->signature, "FACP", 4))
            ret.fadt = desc;
        else if(memcmp(desc->signature, "SRAT", 4))
            ret.srat = desc;
        else if(memcmp(desc->signature, "SSDT", 4))
            ret.ssdt = desc;
    }   

    return ret;
}

#define NEXTENTRY() left -= current->record_length; current = (apic_entry*)(((uintn)current) + current->record_length)

acpi_apic_table madt_parse(void* madt)
{
    acpi_apic* apic = (acpi_apic*) madt;
    acpi_apic_table ret = {0};

    uintn left = apic->header.length - sizeof(acpi_apic);
    apic_entry* current = &(apic->entries[0]);
    uintn cpu_count = 0;

    while(left)
    {
        switch(current->entry_type)
        {
            case 0: // processor local apic

                ret.cpu_count += 1;

                NEXTENTRY();
                break;

            case 1: // io apic

                ret.ioapic = (void*) (uintn) current->ioapic.ioapic_address;
                ret.ioapic_id = current->ioapic.ioapic_id;
                ret.sys_interrupt_base = (void*) (uintn) current->ioapic.sys_interrupt_base;

                NEXTENTRY();
                break; 

            case 2: // io apic interrupt source override
                //printf("irq:\n\t" "isrc: %d\n\t" "bsrc: %d\n\t" "flags: %b\n\t" "gsi: %d\n",
                //    (uintn) current->ioapic_source_override.irq_source,
                //    (uintn) current->ioapic_source_override.bus_source,
                //    (uintn) current->ioapic_source_override.flags,
                //    (uintn) current->ioapic_source_override.global_system_interrupt
                //);


                NEXTENTRY();
                break;

            case 3: // io apic nmi source
    
                NEXTENTRY();
                break;

            case 4: // local apic nmi

                NEXTENTRY();
                break;

            case 5: // local apic address override
            
                ret.local_apic = (void*) current->local_apic_override.local_apic_adr;

                NEXTENTRY();
                break;

            default:
                printf("MADT PARSE: case %u not impimented\n", (uintn) current->entry_type);
                NEXTENTRY();
                break;
        }
    }

#undef NEXTENTRY

    return ret;
}

void madt_print(acpi_apic_table info)
{
    printf("madt info: \n\t" "cpu count: %d\n\t" "local apic address: %X\n\t" "io apic address: %X\n\t" "io apic id: %b\n\t" "interrupt base: %X\n",
        info.cpu_count,
        info.local_apic,
        info.ioapic,
        info.ioapic_id,
        info.sys_interrupt_base
    );
}

