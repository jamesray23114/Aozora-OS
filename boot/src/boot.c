#include <efi/efi.h>

#include <bootlib/memmap.h> 
#include <bootlib/gop.h>

#include <typedef.h>
#include <lib/cpu.h>
#include <lib/gl/gl.h>
#include <lib/gl/text.h>
#include <lib/pci/disk/ide.h>
#include <lib/pci/pci.h>
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

    if( map_fetch(ImageHandle) )
        while(1);

    uintn ksize = 2097152;
    void* kernel = map_alloc(&ksize, AOZORA_MEMORY_KERNEL);

    //mem_print();
    //apic_init();

    while (1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));