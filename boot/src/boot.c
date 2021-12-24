#include <efi/efi.h>

#include <bootlib/memmap.h> 
#include <bootlib/print.h>
#include <bootlib/gop.h>
#include <bootlib/io.h>

#include <lib/gl/gl.h>
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

    uint32 green = gl_pixel(0, 0, 255);
    uint32 red   = gl_pixel(255, 0, 0);

    gl_draw_rect(20, 20, 1800, 23, green, FILL);
    gl_draw_rect(20, 20, 1800, 23, red, OUTLINE1);
   

    print_map();

    while(1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

