#include <bootlib/print.h>

void print_num(int64 num, const byte radix, byte pad, char padchar)
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

static inline char* aozora_memory_type_to_string(EFI_MEMORY_TYPE type)
{
	switch (type)
	{
    case AOZORA_MEMORY_INVALID:
		return "AOZORA_MEMORY_INVALID   ";
    case AOZORA_MEMORY_FREE:
		return "AOZORA_MEMORY_FREE      ";
    case AOZORA_MEMORY_RESERVED:
		return "AOZORA_MEMORY_RESERVED  ";
    case AOZORA_MEMORY_NVS:
		return "AOZORA_MEMORY_NVS       ";
    case AOZORA_MEMORY_IO:
		return "AOZORA_MEMORY_IO        ";
    case AOZORA_MEMORY_BAD:
		return "AOZORA_MEMORY_BAD       ";
    case AOZORA_MEMORY_PERSISTENT:
		return "AOZORA_MEMORY_PERSISTENT";
    case AOZORA_MEMORY_GOP:
		return "AOZORA_MEMORY_GOP       ";
    case AOZORA_MEMORY_MAP:
		return "AOZORA_MEMORY_MAP       ";
    case AOZORA_MEMORY_KERNEL:
		return "AOZORA_MEMORY_KERNEL    ";
    case AOZORA_MEMORY_CODE:
		return "AOZORA_MEMORY_CODE      ";
    case AOZORA_MEMORY_DATA:
		return "AOZORA_MEMORY_DATA      ";
    case AOZORA_MEMORY_SHARED:
		return "AOZORA_MEMORY_SHARED    ";
    case AOZORA_MEMORY_BOOT:
		return "AOZORA_MEMORY_BOOT      ";
	case AOZORA_MEMORY_KDATA:
		return "AOZORA_MEMORY_KDATA     ";
	default:
		return "AOZORA_MEMORY_UNKNOWN   ";
	}
}

void print_aozora_memory(aozora_memory memory)
{		
	gl_print_string(aozora_memory_type_to_string(memory.type));

	gl_print_string(" ");
	gl_print_num(memory.low_address, 16, 9, ' ');
	gl_print_string(" -> ");
	gl_print_num(memory.high_address, 16, 9, ' ');

	gl_print_string(": size = ");
	gl_print_num(memory.high_address - memory.low_address, 10, 1, 0);

	gl_print_string(" bytes\n\r");
}

void print_map()
{
	uintn count = MEMMAP[0].low_address;
	uintn size  = MEMMAP[0].high_address;

	uintn free = 0;

	gl_print_num(count, 10, 1, 0);
	gl_print_string(" aozora memory mappings \n\r");
	gl_print_num(size, 10, 1, 0);
	gl_print_string(" bytes of ram \n\r");

    for(int i = 1; i < count + 1; i++)
    {
		gl_print_string("memory ");
		gl_print_num(i, 10, 2, ' ');
		gl_print_string(": ");

		if(MEMMAP[i].type == AOZORA_MEMORY_FREE)
			free += (MEMMAP[i].high_address - MEMMAP[i].low_address);

		print_aozora_memory(MEMMAP[i]);
  	}	

 	gl_print_string("free memory: ");
	gl_print_num(free, 10, 0, 0);
	gl_print_string(" bytes \n\n\r");
}