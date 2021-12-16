#pragma once

#include <Aozora/typedefs.h>

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

    //from aozora

    AOZORA_MEMORY_MAP,
    AOZORA_MEMORY_KERNEL,
    AOZORA_MEMORY_CODE,
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