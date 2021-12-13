#include <efi.h>
#include <efilib.h>
 
#include "lib/print.h"
#include "lib/gop.h"
#include "lib/io.h"

#define COUT ST->ConOut
#define CIN  ST->ConIn
#define BTSV ST->BootServices    // cSpell:ignore BTSV
#define RTSV ST->RuntimeServices // cSpell:ignore RTSV

#define QEMUBUILD 1 // cSpell:ignore QEMUBUILD

void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    ST = SystemTable;
    BS = SystemTable->BootServices;

    BTSV->SetWatchdogTimer(0, 0, 0, NULL);

    EFI_MEMORY_DESCRIPTOR     mem_map[80];
    UINTN                     size = sizeof(mem_map);
    UINTN                     key;
    UINTN                     dsize;
    UINT32                    dver; // cSpell:ignore dver

    COUT->ClearScreen(COUT);

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = locateGOP();
 
    set_graphics_mode(gop, 8);

    BTSV->GetMemoryMap(&size, mem_map, &key, &dsize, &dver);
    BTSV->ExitBootServices(ImageHandle, key);

    uint64_t resolution = gop->Mode->Info->VerticalResolution * gop->Mode->Info->HorizontalResolution;
    for(int i = 0; i < resolution; i += 4)
    {
        draw_pixel_pos(gop, i, i);
        draw_pixel_pos(gop, i + 1, 0);
        draw_pixel_pos(gop, i + 2, 0);
        draw_pixel_pos(gop, i + 3, 0);
    }

    print_mmap(mem_map, size);

    while (1);
}
