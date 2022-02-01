#pragma once

#include <typedef.h>

void  static inline outb(int64 address, byte data)  {               asm volatile ( "outb %0, %1\n" : : "a" (data),   "Nd" (address) ); }
byte  static inline inb(int64 address)              { byte data;    asm volatile ( "inb %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  static inline outw(int64 address, int16 data) {               asm volatile ( "outw %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int16 static inline inw(int64 address)              { int16 data;   asm volatile ( "inw %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  static inline outl(int64 address, int32 data) {               asm volatile ( "outl %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int32 static inline inl(int64 address)              { int32 data;   asm volatile ( "inl %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }

void  static inline outq(int64 address, int64 data) {               asm volatile ( "outq %0, %1\n" : : "a" (data),   "Nd" (address) ); }
int64 static inline inq(int64 address)              { int64 data;   asm volatile ( "inq %1, %0\n"  :   "=a" (data) : "Nd" (address) );  return data; }