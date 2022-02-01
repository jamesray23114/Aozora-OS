#pragma once

#include <lib/gl/gl.h>

#define CHARHEIGHT  12
#define CHARWIDTH   10

void    gl_putc(char c);

void    gl_puts(const char* string);
void    gl_putnum(uintn number, const byte radix, byte pad, char topad);
void    gl_setCursor(uintn x, uintn y);

uintn   gl_getX();
uintn   gl_getY();