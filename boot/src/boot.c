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

    fetch_memory_map(ImageHandle);

    print_map();

   gl_print_string("void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)");

    while(1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

/*
*/
 