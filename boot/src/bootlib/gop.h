#pragma once

#include <efi/efi.h>

static inline EFI_GRAPHICS_OUTPUT_PROTOCOL* gop_locate()
{
    EFI_GUID guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
    BS->LocateProtocol(&guid, null, (void**)&gop);
    gop->QueryMode(gop, 0, null, null);

    return gop;
}

static inline void gop_setResolution(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, uint32 resx, uint32 resy)
{
    uint32 count = gop->Mode->MaxMode;

    for(int i = 0; i < count; i++)
    {
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* info;
        uintn SizeOfInfo;
        gop->QueryMode(gop, i, &SizeOfInfo, &info);

        if(info->HorizontalResolution == resx && info->VerticalResolution == resy)
        {
            gop->SetMode(gop, i);
            return;
        }
    }
}

static inline void gop_setGraphicsMode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, uint32 mode)
{
    gop->SetMode(gop, mode);
}