#pragma once

#include <efi/efi.h>
#include <Aozora/memory.h>

#include "lib/io.h"

void print_num(int64 num, unsigned char radix, int pad, char padchar);
void print_string(char* string);
void print_aozora_memory(aozora_memory memory);
void print_map();

#if QEMUBUILD
void print_num(int64 num, unsigned char radix, int pad, char padchar)
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

void print_string(char* string)
{
	int i = 0;
	while(string[i]) write_com1(string[i++]);
}

inline char* aozora_memory_type_to_string(EFI_MEMORY_TYPE type)
{
	switch (type)
	{
		case AOZORA_MEMORY_INVALID:
			return "AOZORA_MEMORY_ERROR ";
		case AOZORA_MEMORY_SIZEZERO:
			return "AOZORA_MEMORY_SZ    ";
		case AOZORA_MEMORY_FREE:
			return "AOZORA_MEMORY_FREE  ";
		case AOZORA_MEMORY_RESERVED:
			return "AOZORA_MEMORY_RESVD ";
		case AOZORA_MEMORY_ACPI:
			return "AOZORA_MEMORY_ACPI  ";
		case AOZORA_MEMORY_NVS:
			return "AOZORA_MEMORY_NVS   ";
		case AOZORA_MEMORY_IO:
			return "AOZORA_MEMORY_IO    ";   
		case AOZORA_MEMORY_BAD:
			return "AOZORA_MEMORY_BAD   ";
		case AOZORA_MEMORY_PERSISTENT:
			return "AOZORA_MEMORY_PERST ";
		case AOZORA_MEMORY_RANGE:
			return "AOZORA_MEMORY_RANGE ";
		case AOZORA_MEMORY_MAP:
			return "AOZORA_MEMORY_MAP   ";
		case AOZORA_MEMORY_KERNEL:
			return "AOZORA_MEMORY_KERNEL";
		case AOZORA_MEMORY_CODE:
			return "AOZORA_MEMORY_CODE  ";
		case AOZORA_MEMORY_SHARED:
			return "AOZORA_MEMORY_SHARED";
		case AOZORA_MEMORY_DATA:
			return "AOZORA_MEMORY_DATA  ";
		case AOZORA_MEMORY_GOP:
			return "AOZORA_MEMORY_GOP   ";
		default:
		print_string("\033[1;32mx");
			print_num(type, 16, 1, 0);
			return "\033[m";
	}
}

void print_aozora_memory(aozora_memory memory)
{		
	print_string(aozora_memory_type_to_string(memory.type));

	print_string(" ");
	print_num(memory.low_address, 16, 9, ' ');
	print_string(" -> ");
	print_num(memory.high_address, 16, 9, ' ');

	print_string(": size = ");
	print_num(memory.high_address - memory.low_address, 10, 1, 0);

	print_string(" bytes\n\r");
}

void print_map()
{
	aozora_memory* map = (aozora_memory*) 0x8000;

	uintn count = map[0].low_address;
	uintn size  = map[0].high_address;

	print_num(count, 10, 1, 0);
	print_string(" aozora memory mappings \n\r");
	print_num(size, 10, 1, 0);
	print_string(" bytes of ram \n\r");

    for(int i = 1; i < count + 1; i++)
    {
		print_string("memory ");
		print_num(i, 10, 2, ' ');
		print_string(": ");

		print_aozora_memory(map[i]);
    }
	print_string("\n");
}

//inline char* efi_memory_type_to_string(EFI_MEMORY_TYPE type)
//{
//	switch (type)
//	{
//		case EfiReservedMemoryType: 
//			return "\033[31mEfiReservedMemoryType\033[m";
//		case EfiLoaderCode: 
//			return "EfiLoaderCode";
//		case EfiLoaderData: 
//			return "EfiLoaderData";
//		case EfiBootServicesCode: 
//			return "EfiBootServicesCode";
//		case EfiBootServicesData: 
//			return "EfiBootServicesData";
//		case EfiRuntimeServicesCode: 
//			return "EfiRuntimeServicesCode";
//		case EfiRuntimeServicesData: 
//			return "EfiRuntimeServicesData";
//		case EfiConventionalMemory: 
//			return "EfiConventionalMemory";
//		case EfiUnusableMemory: 
//			return "EfiUnusableMemory";
//		case EfiACPIReclaimMemory: 
//			return "EfiACPIReclaimMemory";
//		case EfiACPIMemoryNVS: 
//			return "EfiACPIMemoryNVS";
//		case EfiMemoryMappedIO: 
//			return "EfiMemoryMappedIO";
//		case EfiMemoryMappedIOPortSpace: 
//			return "EfiMemoryMappedIOPortSpace";
//		case EfiPalCode: 
//			return "EfiPalCode";
//		case EfiPersistentMemory:
//			return "EfiPersistentMemory";
//		case EfiMaxMemoryType: 
//			return "EfiMaxMemoryType";
//		default:
//		print_string("\033[1;32mx");
//			print_num(type, 16, 1, 0);
//			return "\033[m";
//	}
//}
//
//void print_memory_desc(EFI_MEMORY_DESCRIPTOR memory)
//{		
//	print_string("\n\r\t size -> ");
//	print_num(memory.NumberOfPages * 4096, 10, 1, 0);
//	print_string(" bytes\n\r\t type -> ");
//	print_string(efi_memory_type_to_string(memory.Type));
//
//	print_string("\n\r\t flags -> ");
//	if(memory.Attribute & 0x8000000000000000)
//		print_string("\033[1;32m RT \033[m");
//	if(memory.Attribute & 0x0000000000020000)
//		print_string("\033[1;32m RO \033[m");
//	if(memory.Attribute & 0x0000000000001000)
//		print_string("\033[1;36m WP \033[m");
//	if(memory.Attribute & 0x0000000000002000)
//		print_string("\033[1;36m RP \033[m");
//	if(memory.Attribute & 0x0000000000004000)
//		print_string("\033[1;36m XP \033[m");
//	if(memory.Attribute & 0x0000000000008000)
//		print_string("\033[1;36m PM \033[m");
//	if(memory.NumberOfPages == 0)
//		print_string("\033[31m SZ \033[m");
//	else if(!memory.Attribute)
//		print_string("\033[1;33m NM \033[m");
//
//
//	print_string("\n\r\t physical address: ");
//	print_num(memory.PhysicalStart, 16, 16, 'x');
//	print_string(" -> ");
//	print_num(memory.PhysicalStart + memory.NumberOfPages * 4096, 16, 16, 'x');
//
//	print_string("\n\r\t virtual address:  ");
//	print_num(memory.VirtualStart, 16, 16, 'x');
//	print_string(" -> ");
//	print_num(memory.VirtualStart + memory.NumberOfPages * 4096, 16, 16, 'x');
//
//	print_string("\n\n\r");
//}
//
//void print_mmap(EFI_MEMORY_DESCRIPTOR* memmap, intn size)
//{
//	print_num(size / sizeof(EFI_MEMORY_DESCRIPTOR), 10, 1, 0);
//	print_string(" memory mappings \n\n\r");
//
//    for(int i = 0; i < size / sizeof(EFI_MEMORY_DESCRIPTOR); i++)
//    {
//		print_string("memory ");
//		print_num(i, 10, 2, ' ');
//		print_string(":");
//
//		print_memory_desc(memmap[i]);
//    }
//}

#endif //QEMUBUILD