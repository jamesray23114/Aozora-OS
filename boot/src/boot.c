#include <efi/efi.h>

#include <bootlib/memmap.h> 
#include <bootlib/print.h>
#include <bootlib/gop.h>
#include <bootlib/io.h>

#include <lib/gl/gl.h>
#include <lib/gl/text.h>
#include <lib/typedef.h>

EFI_SYSTEM_TABLE*   ST;
EFI_BOOT_SERVICES*  BS;

void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;

    BTSV->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);

    if( fetch_memory_map(ImageHandle) )
        while(1);

    uintn ksize = 2097152;
    void* kernel = mapalloc(&ksize, AOZORA_MEMORY_KERNEL);

    //print_map();

    //print_all_pci_devices();
    //print_all_pci_devices_long();
    
    while (1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

/*
*/
 