#pragma once

#include <Aozora/typedef.h>

typedef enum aozora_memory_type_e
{
    //from firmware

    AOZORA_MEMORY_INVALID,
    AOZORA_MEMORY_SIZEZERO,
    AOZORA_MEMORY_FREE,
    AOZORA_MEMORY_RESERVED,
    AOZORA_MEMORY_ACPI,
    AOZORA_MEMORY_NVS,
    AOZORA_MEMORY_IO,   
    AOZORA_MEMORY_BAD,
    AOZORA_MEMORY_PERSISTENT,
    AOZORA_MEMORY_RANGE,
    AOZORA_MEMORY_GOP,
    
    //from aozora

    AOZORA_MEMORY_MAP,
    AOZORA_MEMORY_KERNEL,
    AOZORA_MEMORY_CODE,
    AOZORA_MEMORY_DATA,
    AOZORA_MEMORY_SHARED

} aozora_memory_type; 

typedef struct aozora_memory_s
{
    aozora_memory_type  type;
    uintn               low_address;
    uintn               high_address;    
} aozora_memory; 

typedef struct aozora_memmap_s
{
    uint16          count;
    aozora_memory*  memmap;
} aozora_memmap;

aozora_memory* aos_memmap = (aozora_memory*) 0x8000; //THIS CAN CAUSE ISSUES, PLEASE REVIEW IN FUTURE

aozora_status splitmap(uintn at, uintn size)
{
    size += 2;
    aos_memmap[0].low_address = size;

    for(int i = size; size > at; size--)
        aos_memmap[size] = aos_memmap[size - 2];
}

aozora_status addmap(aozora_memory memory) // does no check to ensure memory can fit in memmap
{
    uintn size = aos_memmap[0].low_address;

    for(int i = 1; i <= size + 1; i++)
    {
        if(memory.low_address < aos_memmap[i].low_address)
        {
            splitmap(i, size);
            aos_memmap[i - 1].high_address = memory.low_address;
            aos_memmap[i] = memory;
            aos_memmap[i + 1].type =            AOZORA_MEMORY_FREE;
            aos_memmap[i + 1].low_address =     memory.high_address;
            aos_memmap[i + 1].high_address =    aos_memmap[i + 2].low_address;
            return 0;
        }
    }

    if(memory.low_address > aos_memmap[size].low_address)
    {
        splitmap(size, size);
        aos_memmap[size].high_address = memory.low_address;
        aos_memmap[size + 1] = memory;
        aos_memmap[size + 2].type =            AOZORA_MEMORY_FREE;
        aos_memmap[size + 2].low_address =     memory.high_address;
        return 0;
    }

    return 1;
}

aozora_status mapalloc(void* ptr, uintn* size, aozora_memory_type type)
{

}

aozora_status mapfree(void* ptr)
{

}