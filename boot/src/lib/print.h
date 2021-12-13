#pragma once

#include <efi.h>
#include <efilib.h>

#include "lib/io.h"

// print_num

#if QEMUBUILD
void print_num(UINT64 num, unsigned char radix, int pad, char padchar)
{
	if(num == 0)
	{
		if(pad) pad--;
		while (pad--) write_com1(padchar);
		write_com1('0');
		return;	
	}

	char buf[512];

	int i = 0;
	while(num)
	{
		unsigned char c = num % radix;
		num /= radix;
		buf[i++] = c < 10 ? c + '0' : c + '7';
		if(pad) pad--;
	}

	while (pad--) write_com1(padchar);
	while (i--) write_com1(buf[i]);
}
#else
void printnum(INT64 num, char radix, int pad, char padchar) { };
#endif

// print_string

#if QEMUBUILD
void print_string(char* string)
{
	int i = 0;
	while(string[i]) write_com1(string[i++]);
}
#else
void print_string(char* string) { };
#endif

// printmmap

inline char* memory_type_to_string(EFI_MEMORY_TYPE type)
{
	switch (type)
	{
		case EfiReservedMemoryType: 
			return "EfiReservedMemoryType";
		case EfiLoaderCode: 
			return "EfiLoaderCode";
		case EfiLoaderData: 
			return "EfiLoaderData";
		case EfiBootServicesCode: 
			return "EfiBootServicesCode";
		case EfiBootServicesData: 
			return "EfiBootServicesData";
		case EfiRuntimeServicesCode: 
			return "EfiRuntimeServicesCode";
		case EfiRuntimeServicesData: 
			return "EfiRuntimeServicesData";
		case EfiConventionalMemory: 
			return "EfiConventionalMemory";
		case EfiUnusableMemory: 
			return "EfiUnusableMemory";
		case EfiACPIReclaimMemory: 
			return "EfiACPIReclaimMemory";
		case EfiACPIMemoryNVS: 
			return "EfiACPIMemoryNVS";
		case EfiMemoryMappedIO: 
			return "EfiMemoryMappedIO";
		case EfiMemoryMappedIOPortSpace: 
			return "EfiMemoryMappedIOPortSpace";
		case EfiPalCode: 
			return "EfiPalCode";
		case EfiPersistentMemory:
			return "EfiPersistentMemory";
		case EfiMaxMemoryType: 
			return "EfiMaxMemoryType";
		default:
			print_num(type, 10, 1, 0);
			return "";
	}
}

#if QEMUBUILD
void print_mmap(EFI_MEMORY_DESCRIPTOR* mem_map, UINT64 size)
{

	print_num(size / sizeof(EFI_MEMORY_DESCRIPTOR), 10, 1, 0);
	print_string(" number of memory mappings \n\n\r");

    for(int i = 0; i < size / sizeof(EFI_MEMORY_DESCRIPTOR); i++)
    {
		print_string("memory ");
		print_num(i, 10, 2, ' ');

		print_string(":\n\r\t size -> ");
		print_num(mem_map[i].NumberOfPages * 4096, 10, 1, 0);
        print_string(" bytes\n\r\t type -> ");
		print_string(memory_type_to_string(mem_map[i].Type));
		
		print_string("\n\r\t flags -> ");
		if(mem_map[i].Attribute & 0x8000000000000000)
			print_string(" RT ");

		print_string("\n\r\t physical address: ");
        print_num(mem_map[i].PhysicalStart, 16, 16, 'x');
        print_string(" -> ");
        print_num(mem_map[i].PhysicalStart + mem_map[i].NumberOfPages * 4096, 16, 16, 'x');

		print_string("\n\r\t virtual address:  ");
        print_num(mem_map[i].VirtualStart, 16, 16, 'x');
        print_string(" -> ");
        print_num(mem_map[i].VirtualStart + mem_map[i].NumberOfPages * 4096, 16, 16, 'x');

        print_string("\n\n\r");
    }
}
#else
void printmmap(EFI_MEMORY_DESCRIPTOR* mem_map, UINT64 size) { };
#endif