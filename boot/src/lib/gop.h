#pragma once

#include <efi.h>

#include "lib/print.h"

BOOLEAN gop_init = 0;

EFI_GRAPHICS_OUTPUT_PROTOCOL* locateGOP()
{
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
    BS->LocateProtocol(&gop_guid, NULL, (void**)&gop);

    return gop;
}

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* get_cur_graphics_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop)
{
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
    UINTN SizeOfInfo, numModes, nativeMode;

    gop->QueryMode(gop, gop->Mode == NULL ? 0 : gop->Mode->Mode, &SizeOfInfo, &info);

    gop_init = 1;

    return info;
}

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* get_graphics_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, UINT32 mode)
{
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
    UINTN SizeOfInfo, numModes, nativeMode;

    gop->QueryMode(gop, mode, &SizeOfInfo, &info);

    gop_init = 1;

    return info;
}

void set_graphics_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, UINT32 mode)
{
    if(!gop_init)
        get_cur_graphics_mode(gop);
    gop->SetMode(gop, mode);
}

inline void draw_pixel_xy(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, int x, int y, int pixel)
{
    if(!gop_init)
        get_cur_graphics_mode(gop);
   *((uint32_t*)(gop->Mode->FrameBufferBase + 4 * gop->Mode->Info->PixelsPerScanLine * y + 4 * x)) = pixel;
}

inline void draw_pixel_pos(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, int pos, int pixel)
{
    if(!gop_init)
        get_cur_graphics_mode(gop);
   *((uint32_t*)(gop->Mode->FrameBufferBase + 4 * pos)) = pixel;
}