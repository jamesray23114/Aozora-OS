#pragma once

#include <efi/efi.h>

#include <lib/print.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL* locateGOP()
{
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
    BS->LocateProtocol(&gop_guid, null, (void**)&gop);

    return gop;
}

EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* get_graphics_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, uint32 mode)
{
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
    uintn SizeOfInfo, numModes, nativeMode;

    gop->QueryMode(gop, mode, &SizeOfInfo, &info);

    return info;
}

void set_graphics_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, uint32 mode)
{
    gop->SetMode(gop, mode);
}

inline void draw_pixel_xy(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, int x, int y, int pixel)
{
    (((int*) ram)[gop->Mode->FrameBufferBase + 4 * gop->Mode->Info->PixelsPerScanLine * y + 4 * x]) = pixel;
}

inline void draw_pixel_pos(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, int pos, int pixel)
{
   *((uint32*)(gop->Mode->FrameBufferBase + 4 * pos)) = pixel;
}