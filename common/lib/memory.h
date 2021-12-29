#pragma once

#include <lib/typedef.h>

#define MEMMAP aos_memmap

typedef enum aozora_memory_type_e aozora_memory_type;
typedef struct aozora_memory_s aozora_memory;

void splitmap(uintn at, uintn size, const byte loc);
void addmap(aozora_memory memory); // does no check to ensure memory can fit in memmap
void* mapalloc(uintn* size, aozora_memory_type type);
void mapfree(void* ptr);

typedef enum aozora_memory_type_e
{
    //from firmware

    AOZORA_MEMORY_INVALID,
    AOZORA_MEMORY_FREE,
    AOZORA_MEMORY_RESERVED,
    AOZORA_MEMORY_NVS,
    AOZORA_MEMORY_IO,   
    AOZORA_MEMORY_BAD,
    AOZORA_MEMORY_PERSISTENT,
    AOZORA_MEMORY_GOP,

    //from aozora

    AOZORA_MEMORY_MAP,
    AOZORA_MEMORY_KERNEL,
    AOZORA_MEMORY_KDATA,
    AOZORA_MEMORY_CODE,
    AOZORA_MEMORY_DATA,
    AOZORA_MEMORY_SHARED,
    AOZORA_MEMORY_BOOT

} aozora_memory_type; 

typedef struct aozora_memory_s
{
    aozora_memory_type  type;
    uintn               low_address;
    uintn               high_address;    
} aozora_memory; 

static aozora_memory* aos_memmap = (aozora_memory*) 0x8000; //THIS CAN CAUSE ISSUES, PLEASE REVIEW IN FUTURE
