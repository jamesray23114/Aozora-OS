#pragma once

#include <efi.h>
#include <efilib.h>

#include <Aozora/memory.h>

#include "lib/print.h"

uintn traslate_map(EFI_MEMORY_DESCRIPTOR* memmap, UINTN* size)
{
    aozora_memory* a_memmap = (aozora_memory*) 0x8000;
    uintn asize = *size / sizeof(EFI_MEMORY_DESCRIPTOR);

    for(int i = 0; i < *size / sizeof(EFI_MEMORY_DESCRIPTOR); i++)
    {
        if(memmap[i].Type == EfiRuntimeServicesCode || memmap[i].Type == EfiRuntimeServicesData || memmap[i].Type == EfiPalCode)
        {
            a_memmap[i].type =          AOZORA_MEMORY_RESERVED;
            a_memmap[i].low_address =   memmap[i].PhysicalStart;
            a_memmap[i].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiACPIReclaimMemory)
        {
            a_memmap[i].type =          AOZORA_MEMORY_ACPI;
            a_memmap[i].low_address =   memmap[i].PhysicalStart;
            a_memmap[i].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiACPIMemoryNVS)
        {
            a_memmap[i].type =          AOZORA_MEMORY_NVS;
            a_memmap[i].low_address =   memmap[i].PhysicalStart;
            a_memmap[i].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiMemoryMappedIO || memmap[i].Type == EfiMemoryMappedIOPortSpace)
        {
            a_memmap[i].type =          AOZORA_MEMORY_IO;
            a_memmap[i].low_address =   memmap[i].PhysicalStart;
            a_memmap[i].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].NumberOfPages == 0)
        {
            a_memmap[i].type =          AOZORA_MEMORY_SIZEZERO;
            a_memmap[i].low_address =   memmap[i].PhysicalStart;
            a_memmap[i].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type > EfiMaxMemoryType)
        {
            a_memmap[i].type =          AOZORA_MEMORY_INVALID;
            a_memmap[i].low_address =   memmap[i].PhysicalStart;
            a_memmap[i].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
    }

    return asize;
    
}

void memmap_cull(EFI_MEMORY_DESCRIPTOR* memmap, UINTN* size)
{
    for(int i = 0; i < *size / sizeof(EFI_MEMORY_DESCRIPTOR); i++)
    {

        if( //  memmap[i].NumberOfPages == 0
            //|| memmap[i].Type == 0
            memmap[i].Type == EfiBootServicesData
            || memmap[i].Type == EfiBootServicesCode )
        {
            *size -= sizeof(EFI_MEMORY_DESCRIPTOR);

            for(int j = i--; j < *size / sizeof(EFI_MEMORY_DESCRIPTOR); j++)            
                memmap[j] = memmap[j + 1];      
        }
    }
}