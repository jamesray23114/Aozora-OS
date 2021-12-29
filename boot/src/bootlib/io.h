#pragma once    

#include <efi/efi.h>

#include <lib/pci/pci.h>

void init_com1();
void write_com1(byte data);