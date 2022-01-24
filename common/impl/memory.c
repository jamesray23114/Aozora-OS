#include <lib/memory.h>

static inline const char* _amtts(aozora_memory_type type)
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

void map_split(uintn at, uintn size, const byte loc) 
// loc = 0 split on both sides
// loc = 1 leave free below
// loc = 2 leave free above
{  
    if(loc == 0)
    {
        size += 2;
        MEMMAP[0].low_address = size;
        for( ; size > at; size--)
            MEMMAP[size] = MEMMAP[size - 2];
    }
    else if(loc == 1)
    {
        size += 1;
        MEMMAP[0].low_address = size;
        for( ; size > at; size--)
            MEMMAP[size] = MEMMAP[size - 1];
    }
    else if(loc == 2)
    {
        size += 1;
        MEMMAP[0].low_address = size;
        for( ; size > at - 1; size--)
            MEMMAP[size] = MEMMAP[size - 1];
    }
}

void mergemap(uintn at, uintn size, const byte loc)
// loc = 0 merge twice
// loc = 1 merge once
{
    if(loc == 0)
    {
        size -= 2;
        MEMMAP[0].low_address = size;
        for( ; size + 1 > at; at++)
            MEMMAP[at] = MEMMAP[at + 2];
    }
    else if(loc == 1)
    {
        size -= 1;
        MEMMAP[0].low_address = size;
        for( ; size + 1 > at; at++)
            MEMMAP[at] = MEMMAP[at + 1];
    }
}

void map_add(aozora_memory memory) // does no check to ensure memory can fit in memmap
{
    uintn size = MEMMAP[0].low_address;

    for(int i = 1; i <= size + 1; i++)
    {
        if(memory.low_address <= MEMMAP[i].low_address)
        {
            if(memory.low_address == MEMMAP[i].low_address && memory.high_address == MEMMAP[i].high_address )
            {
                 MEMMAP[i] = memory;
                 return;
            }
            else if(memory.low_address == MEMMAP[i].low_address)
            {
                map_split(i, size, 1);
                MEMMAP[i] = memory;
                MEMMAP[i + 1].low_address = memory.high_address;
                return;
            }
            else if(memory.high_address == MEMMAP[i - 1].high_address)
            {
                map_split(i, size, 2);
                MEMMAP[i] = memory;
                MEMMAP[i - 1].high_address = memory.low_address;
                return;
            }
            else if(MEMMAP[i - 1].type == AOZORA_MEMORY_FREE)
            {
                map_split(i, size, 0);
                MEMMAP[i - 1].high_address = memory.low_address;
                MEMMAP[i] = memory;
                MEMMAP[i + 1].type =            AOZORA_MEMORY_FREE;
                MEMMAP[i + 1].low_address =     memory.high_address;
                MEMMAP[i + 1].high_address =    MEMMAP[i + 2].low_address;
                return;
            }
            else
            {
                map_split(i, size, 2);
                MEMMAP[i] = memory;
                return;
            }
        } 
    }
    size++;
    MEMMAP[size] = memory;
    MEMMAP[0].low_address = size;

}

static inline bool validatetype(aozora_memory_type type) // returns true for types that should not be alocated or freed
{
    switch (type)
    {
    case AOZORA_MEMORY_INVALID:
    case AOZORA_MEMORY_RESERVED:
    case AOZORA_MEMORY_NVS:
    case AOZORA_MEMORY_FREE:
    case AOZORA_MEMORY_IO:
    case AOZORA_MEMORY_BAD:
    case AOZORA_MEMORY_PERSISTENT:
    case AOZORA_MEMORY_GOP:
    case AOZORA_MEMORY_MAP:
        return true;

    case AOZORA_MEMORY_KDATA:
    case AOZORA_MEMORY_KERNEL:
    case AOZORA_MEMORY_CODE:
    case AOZORA_MEMORY_DATA:
    case AOZORA_MEMORY_SHARED:
    case AOZORA_MEMORY_BOOT:
        return false;

    default:
        return true;
    }
}

void* map_alloc(uintn size, aozora_memory_type type)
{
    uintn mapsize = MEMMAP[0].low_address;
    uintn maxsize = MEMMAP[0].high_address;

    void* ptr = 0;

    if(size == 0 || size > maxsize || validatetype(type))
        return 0;

    for(int i = 1; i <= mapsize + 1; i++)
    {
        if(MEMMAP[i].high_address - MEMMAP[i].low_address >= size && MEMMAP[i].type == AOZORA_MEMORY_FREE)
            {
                aozora_memory t;

                ptr = (void*) MEMMAP[i].low_address;
                t.low_address = MEMMAP[i].low_address;
                t.type = type;
                
                if(MEMMAP[i].high_address - MEMMAP[i].low_address - 0x4000 <= size || MEMMAP[i].high_address - MEMMAP[i].low_address - 0x4000 >= __INT64_MAX__)   
                {             
                    t.high_address = MEMMAP[i].high_address;
                    size = MEMMAP[i].high_address - MEMMAP[i].low_address;
                }
                else
                    t.high_address = MEMMAP[i].low_address + size;

                map_add(t);
                return ptr;
            }
    }
    return 0;
}

void map_ree(void* ptr)
{
    uintn mapsize = MEMMAP[0].low_address;
    uintn maxsize = MEMMAP[0].high_address;

    if((uintn) ptr == 0 || (uintn) ptr > maxsize)
        return;

    for(int i = 1; i < mapsize; i++)
    {
        if((uintn) ptr == MEMMAP[i].low_address)
        {
            if(validatetype(MEMMAP[i].type))
                return;

            if(MEMMAP[i - 1].type == AOZORA_MEMORY_FREE && MEMMAP[i + 1].type == AOZORA_MEMORY_FREE)
            {
                mergemap(i, mapsize, 0);
                MEMMAP[i - 1].high_address = MEMMAP[i].low_address;
            }
            else if(MEMMAP[i - 1].type == AOZORA_MEMORY_FREE)
            {
                mergemap(i, mapsize, 1);
                MEMMAP[i - 1].high_address = MEMMAP[i].low_address;
            }
            else if(MEMMAP[i + 1].type == AOZORA_MEMORY_FREE)
            {
                mergemap(i, mapsize, 1);
                MEMMAP[i].low_address = MEMMAP[i - 1].high_address;
            }
            else    
            {      
                MEMMAP[i].type = AOZORA_MEMORY_FREE;
            }
        }
    }
}

void hd_printMap(void* mapptr)
{
    uintn size = MEMMAP[0].low_address;

    for(int i = 1; i < size; i++)
        if(MEMMAP[i].low_address == (uintn) mapptr)
            {
                size = MEMMAP[i].high_address - MEMMAP[i].low_address;
                hd_printMem(mapptr, size);
                return;
            }

    gl_puts("map at ");
    gl_putnum((uintn) mapptr, 16, 0, 0);
    gl_puts(" was not found.\n\r");
}

static inline void printBlockHex(byte* ind, int size)
{
    for(int i = 0; i < size; i++)
    {   
        gl_putc(' ');
        if(i % 4 == 0 && i)
            gl_putc(' ');

        gl_putnum(ind[i], 16, 2, '0');
    }
}

static inline void printBlockChar(byte* ind, int size)
{
    for(int i = 0; i < size; i++)
    {   
        byte ch = ind[i];

        if(ch < 0x20 || ch > 0x7f)
            gl_putc('.');
        else         
            gl_putc(ch);
    }
} 

void hd_printMem(void* ptr, uintn count)
{
    if(count > 0xfffe)
        count = 0xfffe;

    uint bsize = GLMODE->horizontal_resolution / CHARWIDTH; // number of bytes to print per line, math is done to ensure values will not go onto the next line regardless of resolution
    bsize /= 5;
    bsize -= bsize % 4; 

    uint blockcount = count / bsize; // number of lines to print


    if(blockcount % bsize != 0 || blockcount == 0)
        blockcount += 1;

    for(int i = 0; i < blockcount; i++)
    {
        gl_putnum(i * bsize, 16, 4, '0');
        gl_puts(" - ");
        gl_putnum((i + 1) * bsize, 16, 4, '0');
        gl_puts(":");
        
        printBlockHex(ptr + i * bsize, bsize);
        gl_puts(" |");
        printBlockChar(ptr + i * bsize, bsize);

        gl_puts("\n\r");
    }
}

static inline void print_aosmem(aozora_memory memory) 
{		
	gl_puts(_amtts(memory.type));

	gl_puts(" ");
	gl_putnum(memory.low_address, 16, 9, ' ');
	gl_puts(" -> ");
	gl_putnum(memory.high_address, 16, 9, ' ');

	gl_puts(": size = ");
	gl_putnum(memory.high_address - memory.low_address, 10, 1, 0);

	gl_puts(" bytes\n\r");
}

void map_print()
{
	uintn count = MEMMAP[0].low_address;
	uintn size  = MEMMAP[0].high_address;

	uintn free = 0;

	gl_putnum(count, 10, 1, 0);
	gl_puts(" aozora memory mappings \n\r");
	gl_putnum(size, 10, 1, 0);
	gl_puts(" bytes of ram \n\r");

    for(int i = 1; i < count + 1; i++)
    {
		gl_puts("memory ");
		gl_putnum(i, 10, 2, ' ');
		gl_puts(": ");

		if(MEMMAP[i].type == AOZORA_MEMORY_FREE)
			free += (MEMMAP[i].high_address - MEMMAP[i].low_address);

		print_aosmem(MEMMAP[i]); // TODO: replace with printf
  	}	

 	gl_puts("free memory: ");
	gl_putnum(free, 10, 0, 0);
	gl_puts(" bytes \n\n\r");
}