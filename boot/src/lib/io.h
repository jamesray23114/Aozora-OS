#pragma once    

#include <efi.h>
#include <efilib.h>

#define RTSV ST->RuntimeServices // cSpell:ignore RTSV

BOOLEAN com1_init = 0;

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

void init_com1()
{
    outb(0x3f8 + 1, 0x00);    
    outb(0x3f8 + 3, 0x80);    
    outb(0x3f8 + 0, 0x03);    
    outb(0x3f8 + 1, 0x00);    
    outb(0x3f8 + 3, 0x03);    
    outb(0x3f8 + 2, 0xC7);    
    outb(0x3f8 + 4, 0x0B);    
    outb(0x3f8 + 4, 0x1E);    
    outb(0x3f8 + 0, 77);

    if(inb(0x3f8) != 77) {
      RTSV->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
   }

   outb(0x3f8 + 4, 0x0F);

   com1_init = 1;
}

void write_com1(char data)
{
    if(!com1_init)
        init_com1();

    outb(0x3f8, data);  
}