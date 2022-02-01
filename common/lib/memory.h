#pragma once

#include <typedef.h>
#include <lib/gl/gl.h>

#define MEMMAP aos_memmap

typedef enum aozora_memory_type_e aozora_memory_type;
typedef struct aozora_memory_s aozora_memory;

void    map_split(uintn at, uintn size, const byte loc);
void    map_add(aozora_memory memory); // does no check to ensure memory can fit in memmap
void*   map_alloc(uintn size, aozora_memory_type type);
void    map_ree(void* ptr);
void    map_print();

void    hd_printMap(void* mapptr);
void    hd_printMem(void* ptr, uintn count);

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
    AOZORA_MEMORY_APIC,

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

static aozora_memory* aos_memmap = (aozora_memory*) 0x8000; // TODO: this needs to be changed to allow for the moving of the memmap