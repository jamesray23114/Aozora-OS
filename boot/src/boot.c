#include <efi/efi.h>

#include <bootlib/memmap.h> 
#include <bootlib/print.h>
#include <bootlib/gop.h>
#include <bootlib/io.h>

#include <lib/typedef.h>
#include <lib/gl/gl.h>
#include <lib/gl/text.h>
#include <lib/pci/disk/ide.h>
#include <lib/pci/pci.h>

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

    if(ide_init())
    {
        byte buffer[2048] = {0};
        ide_read_sectors(0, 0, 2, buffer);
        printmem(buffer, 2048);
    }
    while (1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

/*
*/
 