#pragma once

#include <Aozora/memory.h>
#include <Aozora/typedef.h>

#include "lib/print.h"

void traslate_map(EFI_MEMORY_DESCRIPTOR* memmap, uintn size, uintn descsize) // translates broken uefi implimentation of uefi
{
    uintn asize = size / descsize;

    uintn last = 0, maxsize = 0;
    bool ismapped = false;
    aozora_memory_type lasttype = AOZORA_MEMORY_INVALID;

    for(int i = 0, j = 0; i <= size / descsize; i++)
    {
        EFI_MEMORY_DESCRIPTOR currmem = *(EFI_MEMORY_DESCRIPTOR*)((uintn) memmap + (i * descsize));

        switch (currmem.Type)
        {
        case EfiReservedMemoryType:
        case EfiRuntimeServicesCode:
        case EfiRuntimeServicesData:
        case EfiPalCode:
        case EfiMaxMemoryType:
        default:
            if(lasttype != AOZORA_MEMORY_RESERVED)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_RESERVED;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_RESERVED;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;


        case EfiConventionalMemory:
        case EfiACPIReclaimMemory:
        case EfiBootServicesCode:
        case EfiBootServicesData:
            if(lasttype != AOZORA_MEMORY_FREE)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_FREE;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;


        case EfiPersistentMemory:
            if(lasttype != AOZORA_MEMORY_PERSISTENT)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_PERSISTENT;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_PERSISTENT;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;


        case EfiUnusableMemory:
            if(lasttype != AOZORA_MEMORY_BAD)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_BAD;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_BAD;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;

        case EfiLoaderCode:
        case EfiLoaderData:
            if(lasttype != AOZORA_MEMORY_BOOT)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_BOOT;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_BOOT;
            }
            else
            {
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                j++;
            }
            break;            
   

        case EfiACPIMemoryNVS:
            if(lasttype != AOZORA_MEMORY_NVS)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_NVS;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_NVS;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            maxsize = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
            break; 


        case EfiMemoryMappedIO:
        case EfiMemoryMappedIOPortSpace:
            if(lasttype != AOZORA_MEMORY_IO)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_IO;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                //j--;
                lasttype = AOZORA_MEMORY_IO;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;        
        }   
    }    

    aos_memmap[0].type =                AOZORA_MEMORY_INVALID;
    aos_memmap[0].low_address =         asize;
    aos_memmap[0].high_address =        maxsize;
}

aozora_status fetch_memory_map(EFI_HANDLE mainhandle, uintn gopbase, uintn gopsize) 
{
    EFI_MEMORY_DESCRIPTOR*    memmap;
    uintn                     size = sizeof(memmap);
    uintn                     key;
    uintn                     maxmem;
    uintn                     descsize;
    uint32                    ver;

    BTSV->GetMemoryMap(&size, memmap, &key, null, null);
    size = size + sizeof(EFI_MEMORY_DESCRIPTOR) * 2;
    BTSV->AllocatePool(EfiLoaderData, size, (void**) &memmap);

    BTSV->GetMemoryMap(&size, memmap, &key, &descsize, &ver);
    BTSV->ExitBootServices(mainhandle, key);

    traslate_map(memmap, size, descsize);

    aozora_memory test   = {AOZORA_MEMORY_KERNEL, 0xb000, 0xf000};
    aozora_memory mapmem = {AOZORA_MEMORY_MAP, 0x8000, 0x8000 + 24 * 512};
    aozora_memory gopmem = {AOZORA_MEMORY_GOP, gopbase, gopbase + gopsize};
    addmap(test); 
    addmap(mapmem); 
    addmap(gopmem);

    print_mmap(memmap, size, descsize);

    return 0;
}