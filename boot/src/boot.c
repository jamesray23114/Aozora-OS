#include <efi/efi.h>

#include <lib/memmap.h> 
#include <lib/print.h>
#include <lib/gop.h>
#include <lib/io.h>

void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;

    BTSV->SetWatchdogTimer(0, 0, 0, null);
    COUT->ClearScreen(COUT);

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = locateGOP();
    get_graphics_mode(gop, 5);
    set_graphics_mode(gop, 5);

    fetch_memory_map(ImageHandle, gop->Mode->FrameBufferBase, gop->Mode->FrameBufferSize);
    print_map();

    while (1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

