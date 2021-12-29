#pragma once    

#include <efi/efi.h>


void  inline outb(int64 address, byte data)  {               asm ( "outb %0, %1\n" : : "a" (data),   "Nd" (address) ); }
byte  inline inb(int64 address)              { byte data;    asm ( "inb %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outw(int64 address, int16 data) {               asm ( "outw %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int16 inline inw(int64 address)              { int16 data;   asm ( "inw %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outl(int64 address, int32 data) {               asm ( "outl %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int32 inline inl(int64 address)              { int32 data;   asm ( "inl %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  inline outq(int64 address, int64 data) {               asm ( "outq %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int64 inline inq(int64 address)              { int64 data;   asm ( "inq %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void init_com1();
void write_com1(byte data);