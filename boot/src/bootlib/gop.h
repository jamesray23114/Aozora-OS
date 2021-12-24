#pragma once

#include <efi/efi.h>
#include <bootlib/print.h>
#include <lib/gl/gl.h>

EFI_GRAPHICS_OUTPUT_PROTOCOL* locateGOP();
void set_resolution(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, uint32 resx, uint32 resy);
void set_graphics_mode(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, uint32 mode);
void draw_pixel_xy(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, int x, int y, int pixel);
void draw_pixel_pos(EFI_GRAPHICS_OUTPUT_PROTOCOL* gop, int pos, int pixel);