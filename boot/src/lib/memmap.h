#pragma once

#include <Aozora/memory.h>
#include <Aozora/typedef.h>

#include "lib/print.h"

void traslate_map(EFI_MEMORY_DESCRIPTOR* memmap, uintn size)
{
    uintn asize = size / sizeof(EFI_MEMORY_DESCRIPTOR);

    uintn last = 0, maxsize = 0;
    bool ismapped = false;

    for(int i = 0, j = 0; i <= size / sizeof(EFI_MEMORY_DESCRIPTOR); i++)
    {
        if(memmap[i].Type == EfiMaxMemoryType && !maxsize)
        {
            maxsize = memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
            asize--;
            j++;
        }
        else if(memmap[i].PhysicalStart <= 0x10)
        {
            asize--;
            j++;
        }
        else if(memmap[i].Type == EfiRuntimeServicesCode || memmap[i].Type == EfiRuntimeServicesData || memmap[i].Type == EfiPalCode)
        {   
            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
            aos_memmap[i - j + 1].low_address =   last; 
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart;

            j--; asize++;

            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_RESERVED;
            aos_memmap[i - j + 1].low_address =   memmap[i].PhysicalStart;
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;

            last = memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiACPIReclaimMemory)
        {
            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
            aos_memmap[i - j + 1].low_address =   last; 
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart;

            j--; asize++;

            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_ACPI;
            aos_memmap[i - j + 1].low_address =   memmap[i].PhysicalStart;
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;

            last = memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiACPIMemoryNVS)
        {
            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
            aos_memmap[i - j + 1].low_address =   last; 
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart;

            j--; asize++;

            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_NVS;
            aos_memmap[i - j + 1].low_address =   memmap[i].PhysicalStart;
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;

            last = memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiMemoryMappedIO || memmap[i].Type == EfiMemoryMappedIOPortSpace)
        {
            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
            aos_memmap[i - j + 1].low_address =   last; 
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart;

            j--; asize++;

            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_IO;
            aos_memmap[i - j + 1].low_address =   memmap[i].PhysicalStart;
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;

            last = memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else if(memmap[i].Type == EfiLoaderCode || memmap[i].Type == EfiLoaderData)
        {
            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
            aos_memmap[i - j + 1].low_address =   last; 
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart;

            j--; asize++;

            aos_memmap[i - j + 1].type =          AOZORA_MEMORY_CODE;
            aos_memmap[i - j + 1].low_address =   memmap[i].PhysicalStart;
            aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;

            last = memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
        }
        else 
        {
            //aos_memmap[i - j + 1].type =          AOZORA_MEMORY_INVALID;
            //aos_memmap[i - j + 1].low_address =   memmap[i].PhysicalStart;
            //aos_memmap[i - j + 1].high_address =  memmap[i].PhysicalStart + memmap[i].NumberOfPages * 4096;
            asize--;
            j++;
        }    
    }

    asize++; asize++;

    if(aos_memmap[asize - 1].high_address != maxsize)
    {
        aos_memmap[asize].type =            AOZORA_MEMORY_FREE;
        aos_memmap[asize].low_address =     last; 
        aos_memmap[asize].high_address =    maxsize;
    }
    else
        asize--;

    aos_memmap[0].type =                AOZORA_MEMORY_SIZEZERO;
    aos_memmap[0].low_address =         asize;
    aos_memmap[0].high_address =        maxsize;
}

aozora_status fetch_memory_map(EFI_HANDLE mainhandle, uintn gopbase, uintn gopsize) 
{
    EFI_MEMORY_DESCRIPTOR*    memmap;
    uintn                     size = sizeof(memmap);
    uintn                     key;
    uintn                     maxmem;

    BTSV->GetMemoryMap(&size, memmap, &key, null, null);
    size = size + sizeof(EFI_MEMORY_DESCRIPTOR) * 2;
    BTSV->AllocatePool(EfiLoaderData, size, (void**) &memmap);

    BTSV->GetMemoryMap(&size, memmap, &key, null, null);
    BTSV->ExitBootServices(mainhandle, key);

    traslate_map(memmap, size);

    aozora_memory mapmem = {AOZORA_MEMORY_MAP, 0x8000, 0x8000 + 24 * 512};
    aozora_memory gopmem = {AOZORA_MEMORY_GOP, gopbase, gopbase + gopsize};
    addmap(mapmem); 
    addmap(gopmem);

    return 0;
}