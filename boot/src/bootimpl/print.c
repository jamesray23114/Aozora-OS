#include <bootlib/print.h>

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
		return "\033[30mAOZORA_MEMORY_INVALID\033[m   ";
    case AOZORA_MEMORY_FREE:
		return "\033[32mAOZORA_MEMORY_FREE\033[m      ";
    case AOZORA_MEMORY_RESERVED:
		return "\033[33mAOZORA_MEMORY_RESERVED\033[m  ";
    case AOZORA_MEMORY_NVS:
		return "\033[33mAOZORA_MEMORY_NVS\033[m       ";
    case AOZORA_MEMORY_IO:
		return "\033[33mAOZORA_MEMORY_IO\033[m        ";
    case AOZORA_MEMORY_BAD:
		return "\033[30mAOZORA_MEMORY_BAD\033[m       ";
    case AOZORA_MEMORY_PERSISTENT:
		return "\033[32mAOZORA_MEMORY_PERSISTENT\033[m";
    case AOZORA_MEMORY_GOP:
		return "\033[33mAOZORA_MEMORY_GOP\033[m       ";
    case AOZORA_MEMORY_MAP:
		return "\033[35mAOZORA_MEMORY_MAP\033[m       ";
    case AOZORA_MEMORY_KERNEL:
		return "\033[35mAOZORA_MEMORY_KERNEL\033[m    ";
    case AOZORA_MEMORY_CODE:
		return "\033[36mAOZORA_MEMORY_CODE\033[m      ";
    case AOZORA_MEMORY_DATA:
		return "\033[36mAOZORA_MEMORY_DATA\033[m      ";
    case AOZORA_MEMORY_SHARED:
		return "\033[36mAOZORA_MEMORY_SHARED\033[m    ";
    case AOZORA_MEMORY_BOOT:
		return "\033[32mAOZORA_MEMORY_BOOT\033[m      ";
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
	uintn count = aos_memmap[0].low_address;
	uintn size  = aos_memmap[0].high_address;

	uintn free = 0;

	print_num(count, 10, 1, 0);
	print_string(" aozora memory mappings \n\r");
	print_num(size, 10, 1, 0);
	print_string(" bytes of ram \n\r");

    for(int i = 1; i < count + 1; i++)
    {
		print_string("memory ");
		print_num(i, 10, 2, ' ');
		print_string(": ");

		if(aos_memmap[i].type == AOZORA_MEMORY_FREE)
			free += (aos_memmap[i].high_address - aos_memmap[i].low_address);

		print_aozora_memory(aos_memmap[i]);
  	}	

 	print_string("free memory: ");
	print_num(free, 10, 0, 0);
	print_string(" bytes \n\n\r");
}