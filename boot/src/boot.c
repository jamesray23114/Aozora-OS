#include <efi.h>
#include <efilib.h>
 
#include "lib/print.h"
#include "lib/gop.h"

#define COUT ST->ConOut
#define CIN  ST->ConIn
#define BTSV ST->BootServices    // cSpell:ignore BTSV
#define RTSV ST->RuntimeServices // cSpell:ignore RTSV

void inline outb(int64_t address, char data)
{
    asm volatile ( "outb %0, %1" : : "a" (data), "Nd" (address));
}

char inline inb(int64_t address)
{
    char data;
    asm volatile( "inb %1, %0" : "=a" (data) : "Nd" (address) );

    return data;
}    

void efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
 
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
 
    get_cur_graphics_mode(gop);
    set_graphics_mode(gop, 3);

    EFI_STATUS mm = BTSV->GetMemoryMap(&size, mem_map, &key, &dsize, &dver);
    EFI_STATUS ex = BTSV->ExitBootServices(ImageHandle, key);

    uint64_t resolution = gop->Mode->Info->VerticalResolution * gop->Mode->Info->HorizontalResolution;

    for(int i = 0; i < resolution; i += 4)
    {
        draw_pixel_pos(gop, i, i);
        draw_pixel_pos(gop, i + 1, 0);
        draw_pixel_pos(gop, i + 2, 0);
        draw_pixel_pos(gop, i + 3, 0);
    }

    outb(0x3f8 + 1, 0x00);    
    outb(0x3f8 + 3, 0x80);    
    outb(0x3f8 + 0, 0x03);    
    outb(0x3f8 + 1, 0x00);    
    outb(0x3f8 + 3, 0x03);    
    outb(0x3f8 + 2, 0xC7);    
    outb(0x3f8 + 4, 0x0B);    
    outb(0x3f8 + 4, 0x1E);    
    outb(0x3f8 + 0, 'c');

    if(inb(0x3f8) != 'c') {
      RTSV->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
   }

    outb(0x3f8 + 4, 0x0F);

    outb(0x3f8, 't');
    outb(0x3f8, 'e');
    outb(0x3f8, 's');
    outb(0x3f8, 't');
    
    while (1);
}
