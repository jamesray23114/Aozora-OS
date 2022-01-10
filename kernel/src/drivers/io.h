#pragma once

#include "lib/typedef.h"

void static inline outb(int64 address, byte data)
{
    asm volatile ( "outb %0, %1" : : "a" (data), "Nd" (address));
}   

byte static inline inb(int32 address)
{
    byte data;
    asm volatile( "inb %1, %0" : "=a" (data) : "Nd" (address) );

    return data;
}       