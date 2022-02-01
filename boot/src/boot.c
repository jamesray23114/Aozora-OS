#include <efi/efi.h>

#include <bootlib/memmap.h> 
#include <bootlib/gop.h>

#include <typedef.h>
#include <lib/cpu.h>
#include <lib/acpi.h>
#include <lib/gl/gl.h>
#include <lib/gl/text.h>
#include <lib/io/pci/disk/ide.h>
#include <lib/io/pci/pci.h>
#include <lib/io/ps2.h>
#include <lib/int/apic.h>

#include <aoslib.h>

EFI_SYSTEM_TABLE*   ST;
EFI_BOOT_SERVICES*  BS;

void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;

    BTSV->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);

    void* rsdp = get_rsdp(SystemTable); // ONLY SUPPORTS RSDP 2

    if(map_fetch(ImageHandle)) while(1);

    void* kernel = map_alloc(2097152, AOZORA_MEMORY_KERNEL);

// begin

    acpi_root_table artb = rxdt_parse(rsdp);
    acpi_apic_table madt = madt_parse(artb.madt);
    
    cpu_enableInt();
    apic_init(madt);

    ps2_init();

    asm("sti");

    while (true);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

