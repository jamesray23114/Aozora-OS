#pragma once

#include <efi/efi.h>

#include <bootlib/gop.h>

#include <typedef.h>
#include <lib/memory.h>
#include <lib/pci/pci.h>
#include <lib/gl/gl.h>

void map_traslate(EFI_MEMORY_DESCRIPTOR* memmap, uintn size, uintn descsize) //TODO: account for broken uefi implementations
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
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_RESERVED;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_RESERVED;
            }
            else
            {
                j++; 
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;


        case EfiConventionalMemory:
        case EfiACPIReclaimMemory:
        case EfiBootServicesCode:
        case EfiBootServicesData:

            maxsize += currmem.NumberOfPages * 4096;

            if(lasttype != AOZORA_MEMORY_FREE)
            {
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_FREE;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_FREE;
            }
            else
            {
                j++; 
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;


        case EfiPersistentMemory:

            maxsize += currmem.NumberOfPages * 4096;

            if(lasttype != AOZORA_MEMORY_PERSISTENT)
            {
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_PERSISTENT;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_PERSISTENT;
            }
            else
            {
                j++; 
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;


        case EfiUnusableMemory:
            if(lasttype != AOZORA_MEMORY_BAD)
            {
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_BAD;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_BAD;
            }
            else
            {
                j++; 
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;

        case EfiLoaderCode:
        case EfiLoaderData:

            maxsize += currmem.NumberOfPages * 4096;

            if(lasttype != AOZORA_MEMORY_BOOT)
            {
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_BOOT;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_BOOT;
            }
            else
            {
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                j++;
            }
            break;            
   

        case EfiACPIMemoryNVS:
            if(lasttype != AOZORA_MEMORY_NVS)
            {
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_NVS;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_NVS;
            }
            else
            {
                j++; 
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break; 


        case EfiMemoryMappedIO:
        case EfiMemoryMappedIOPortSpace:
            if(lasttype != AOZORA_MEMORY_IO)
            {
                MEMMAP[i - j + 1].type =          AOZORA_MEMORY_IO;
                MEMMAP[i - j + 1].low_address =   currmem.PhysicalStart;
                MEMMAP[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                lasttype = AOZORA_MEMORY_IO;
            }
            else
            {
                j++; 
                MEMMAP[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break;        
        }   
    }    

    aozora_memory swap;
    last = 0;

    for(int i = 1; i < asize + 1; i++)
    {
        for(int j = i; j < asize + 1; j++)
        {
            if(MEMMAP[j].low_address < MEMMAP[i].high_address)
            {
                swap = MEMMAP[i];
                MEMMAP[i] = MEMMAP[j];
                MEMMAP[j] = swap;
            }
        }
    };

    for(int i = 1; i < asize + 1; i++)
    {
        if(MEMMAP[i].low_address < MEMMAP[i - 1].high_address && MEMMAP[i].type == AOZORA_MEMORY_FREE)
            MEMMAP[i].low_address = MEMMAP[i - 1].high_address;
    };


    MEMMAP[0].type =                AOZORA_MEMORY_INVALID;
    MEMMAP[0].low_address =         asize;
    MEMMAP[0].high_address =        maxsize;
}

aozora_status map_fetch(EFI_HANDLE mainhandle)  // TODO: split into smaller functions
{
    EFI_MEMORY_DESCRIPTOR*    memmap;
    uintn                     size = sizeof(memmap);
    uintn                     key;
    uintn                     maxmem;
    uintn                     descsize;
    uint32                    ver;

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = gop_locate();

    uintn gopbase = gop->Mode->FrameBufferBase;
    uintn gopsize = gop->Mode->FrameBufferSize;

    { // TODO: move to gop.c
        graphics_mode gm;

        gop_setResolution(gop, 640,  360 );
        gop_setResolution(gop, 1024, 768 );
        gop_setResolution(gop, 1280, 1024);
        gop_setResolution(gop, 1280, 720 );
        gop_setResolution(gop, 1920, 1080); 
        
        gm.format =                 gop->Mode->Info->PixelFormat;
        gm.horizontal_resolution =  gop->Mode->Info->HorizontalResolution;
        gm.vertical_resolution =    gop->Mode->Info->VerticalResolution;
        gm.pitch =                  gop->Mode->Info->PixelsPerScanLine;
        gm.resolution =             gm.horizontal_resolution * gm.vertical_resolution;
        gm.location =               (uint32*) gop->Mode->FrameBufferBase;

        *gl_mode = gm;
    }

    BTSV->GetMemoryMap(&size, memmap, &key, null, null);
    size = size + sizeof(EFI_MEMORY_DESCRIPTOR) * 2;
    BTSV->AllocatePool(EfiLoaderData, size, (void**) &memmap);

    BTSV->GetMemoryMap(&size, memmap, &key, &descsize, &ver);
    BTSV->ExitBootServices(mainhandle, key);

    map_traslate(memmap, size, descsize);

    if(MEMMAP[1].type != AOZORA_MEMORY_FREE)
        goto errornf;
    if(MEMMAP[1].high_address < 0x36000)
        goto errornf;

    aozora_memory mapmem = {AOZORA_MEMORY_MAP, 0x0000, 0x36000};
    aozora_memory gopmem = {AOZORA_MEMORY_GOP, gopbase, gopbase + gopsize};
    map_add(mapmem);
    map_add(gopmem);
    
    //map_print();

    pci_addDevices();

    return 0;

errornf:
    gl_puts("error allocating aozora-os memory, memory at location 0 - 0x36000 is not free\n\r");
    map_print();
    return 1;
}