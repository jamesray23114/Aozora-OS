#pragma once    

#include <efi/efi.h>


void outb(int64 address, char data);
char inb(int64 address); 
void init_com1();
void write_com1(char data);