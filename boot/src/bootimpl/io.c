#include <bootlib/io.h>

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
      RTSV->ResetSystem(EfiResetCold, 0, 0, null);
   }

   outb(0x3f8 + 4, 0x0F);
}

void write_com1(byte data)
{
    outb(0x3f8, data);  
}