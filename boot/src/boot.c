#include <efi.h>
 
#include "lib/print.h"
#include "lib/gop.h"
#include "lib/io.h"

#include "efi/memmap.h"

#define COUT ST->ConOut
#define CIN  ST->ConIn
#define BTSV ST->BootServices    // cSpell:ignore BTSV
#define RTSV ST->RuntimeServices // cSpell:ignore RTSV

void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;
    char* memory = 0;

    BTSV->SetWatchdogTimer(0, 0, 0, NULL);
    COUT->ClearScreen(COUT);

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = locateGOP();
    set_graphics_mode(gop, 8);

    EFI_MEMORY_DESCRIPTOR     memmap[80];
    UINTN                     size = sizeof(memmap);
    UINTN                     key;

    BTSV->GetMemoryMap(&size, memmap, &key, null, null);
    BTSV->ExitBootServices(ImageHandle, key);

    memmap_cull(memmap, &size);
    print_mmap(memmap, size);

    uintn asize = traslate_map(memmap, &size);
    print_amap(asize);

    while (1);
}

//asm ("call getrip\n getrip: mov (%%esp), %0\n" : "=r" (reg));

