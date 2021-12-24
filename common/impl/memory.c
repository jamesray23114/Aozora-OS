#include <lib/memory.h>

#include <bootlib/print.h>

void splitmap(uintn at, uintn size, const byte loc) 
// loc = 0 split on both sides
// loc = 1 leave free below
// loc = 2 leave free above
{  
    if(loc == 0)
    {
        size += 2;
        aos_memmap[0].low_address = size;
        for( ; size > at; size--)
            aos_memmap[size] = aos_memmap[size - 2];
    }
    else if(loc == 1)
    {
        size += 1;
        aos_memmap[0].low_address = size;
        for( ; size > at; size--)
            aos_memmap[size] = aos_memmap[size - 1];
    }
    else if(loc == 2)
    {
        size += 1;
        aos_memmap[0].low_address = size;
        for( ; size > at - 1; size--)
            aos_memmap[size] = aos_memmap[size - 1];
    }
}

void mergemap(uintn at, uintn size, const byte loc)
// loc = 0 merge twice
// loc = 1 merge once
{
    if(loc == 0)
    {
        size -= 2;
        aos_memmap[0].low_address = size;
        for( ; size + 1 > at; at++)
            aos_memmap[at] = aos_memmap[at + 2];
    }
    else if(loc == 1)
    {
        size -= 1;
        aos_memmap[0].low_address = size;
        for( ; size + 1 > at; at++)
            aos_memmap[at] = aos_memmap[at + 1];
    }
}

void addmap(aozora_memory memory) // does no check to ensure memory can fit in memmap
{
    uintn size = aos_memmap[0].low_address;

    for(int i = 1; i <= size + 1; i++)
    {
        if(memory.low_address <= aos_memmap[i].low_address)
        {
            if(memory.low_address == aos_memmap[i].low_address && memory.high_address == aos_memmap[i].high_address )
            {
                 aos_memmap[i] = memory;
                 return;
            }
            else if(memory.low_address == aos_memmap[i].low_address)
            {
                splitmap(i, size, 1);
                aos_memmap[i] = memory;
                aos_memmap[i + 1].low_address = memory.high_address;
                return;
            }
            else if(memory.high_address == aos_memmap[i - 1].high_address)
            {
                splitmap(i, size, 2);
                aos_memmap[i] = memory;
                aos_memmap[i - 1].high_address = memory.low_address;
                return;
            }
            else if(aos_memmap[i - 1].type == AOZORA_MEMORY_FREE)
            {
                splitmap(i, size, 0);
                aos_memmap[i - 1].high_address = memory.low_address;
                aos_memmap[i] = memory;
                aos_memmap[i + 1].type =            AOZORA_MEMORY_FREE;
                aos_memmap[i + 1].low_address =     memory.high_address;
                aos_memmap[i + 1].high_address =    aos_memmap[i + 2].low_address;
                return;
            }
            else
            {
                splitmap(i, size, 2);
                aos_memmap[i] = memory;
                return;
            }
        } 
    }
    size++;
    aos_memmap[size] = memory;
    aos_memmap[0].low_address = size;

}

inline bool validatetype(aozora_memory_type type) // returns true for types that should not be alocated or freed
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
    case AOZORA_MEMORY_KERNEL:
        return true;

    case AOZORA_MEMORY_CODE:
    case AOZORA_MEMORY_DATA:
    case AOZORA_MEMORY_SHARED:
    case AOZORA_MEMORY_BOOT:
        return false;

    default:
        return true;
    }
}

void* mapalloc(void* ptr, uintn* size, aozora_memory_type type)
{
    uintn mapsize = aos_memmap[0].low_address;
    uintn maxsize = aos_memmap[0].high_address;

    ptr = 0;

    if(*size == 0 || *size > maxsize || validatetype(type))
        return 0;

    for(int i = 1; i <= mapsize + 1; i++)
    {
        if(aos_memmap[i].high_address - aos_memmap[i].low_address >= *size && aos_memmap[i].type == AOZORA_MEMORY_FREE)
            {
                aozora_memory t;

                ptr = (void*) aos_memmap[i].low_address;
                t.low_address = aos_memmap[i].low_address;
                t.type = type;
                
                if(aos_memmap[i].high_address - aos_memmap[i].low_address - 0x100000 <= *size)   
                {             
                    t.high_address = aos_memmap[i].high_address;
                    *size = aos_memmap[i].high_address - aos_memmap[i].low_address;
                }
                else
                    t.high_address = aos_memmap[i].low_address + *size;

                addmap(t);
                return ptr;
            }
    }
    return 0;
}

void mapfree(void* ptr)
{
    uintn mapsize = aos_memmap[0].low_address;
    uintn maxsize = aos_memmap[0].high_address;

    if((uintn) ptr == 0 || (uintn) ptr > maxsize)
        return;

    for(int i = 1; i < mapsize; i++)
    {
        if((uintn) ptr == aos_memmap[i].low_address)
        {
            if(validatetype(aos_memmap[i].type))
                return;

            if(aos_memmap[i - 1].type == AOZORA_MEMORY_FREE && aos_memmap[i + 1].type == AOZORA_MEMORY_FREE)
            {
                mergemap(i, mapsize, 0);
                aos_memmap[i - 1].high_address = aos_memmap[i].low_address;
            }
            else if(aos_memmap[i - 1].type == AOZORA_MEMORY_FREE)
            {
                mergemap(i, mapsize, 1);
                aos_memmap[i - 1].high_address = aos_memmap[i].low_address;
            }
            else if(aos_memmap[i + 1].type == AOZORA_MEMORY_FREE)
            {
                mergemap(i, mapsize, 1);
                aos_memmap[i].low_address = aos_memmap[i - 1].high_address;
            }
            else    
            {      
                aos_memmap[i].type = AOZORA_MEMORY_FREE;
            }
        }
    }
}