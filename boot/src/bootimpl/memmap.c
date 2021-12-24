#include <bootlib/memmap.h>

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

            maxsize += currmem.NumberOfPages * 4096;

            if(lasttype != AOZORA_MEMORY_FREE)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_FREE;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
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

            maxsize += currmem.NumberOfPages * 4096;

            if(lasttype != AOZORA_MEMORY_PERSISTENT)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_PERSISTENT;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
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

            maxsize += currmem.NumberOfPages * 4096;

            if(lasttype != AOZORA_MEMORY_BOOT)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_BOOT;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
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
                lasttype = AOZORA_MEMORY_NVS;
            }
            else
            {
                j++; 
                aos_memmap[i - j + 1].high_address = currmem.PhysicalStart + currmem.NumberOfPages * 4096;
                asize--;
            }
            break; 


        case EfiMemoryMappedIO:
        case EfiMemoryMappedIOPortSpace:
            if(lasttype != AOZORA_MEMORY_IO)
            {
                aos_memmap[i - j + 1].type =          AOZORA_MEMORY_IO;
                aos_memmap[i - j + 1].low_address =   currmem.PhysicalStart;
                aos_memmap[i - j + 1].high_address =  currmem.PhysicalStart + currmem.NumberOfPages * 4096;
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

aozora_status fetch_memory_map(EFI_HANDLE mainhandle) 
{
    EFI_MEMORY_DESCRIPTOR*    memmap;
    uintn                     size = sizeof(memmap);
    uintn                     key;
    uintn                     maxmem;
    uintn                     descsize;
    uint32                    ver;

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop = locateGOP();


    uintn gopbase = gop->Mode->FrameBufferBase;
    uintn gopsize = gop->Mode->FrameBufferSize;

    { // setup and store graphics settings
        graphics_mode gm;

        set_resolution(gop, 640,  360 );
        set_resolution(gop, 1024, 768 );
        set_resolution(gop, 1280, 1024);
        set_resolution(gop, 1280, 720 );
        //set_resolution(gop, 1920, 1080); 

        gm.format =                 gop->Mode->Info->PixelFormat;
        gm.horizontal_resolution =  gop->Mode->Info->HorizontalResolution;
        gm.vertical_resolution =    gop->Mode->Info->VerticalResolution;
        gm.pitch =                  gop->Mode->Info->PixelsPerScanLine;

        *gl_mode = gm;
    }

    BTSV->GetMemoryMap(&size, memmap, &key, null, null);
    size = size + sizeof(EFI_MEMORY_DESCRIPTOR) * 2;
    BTSV->AllocatePool(EfiLoaderData, size, (void**) &memmap);

    BTSV->GetMemoryMap(&size, memmap, &key, &descsize, &ver);
    BTSV->ExitBootServices(mainhandle, key);


    //for(uintn i = 0; i < size / descsize; i++)
    //{
    //    EFI_MEMORY_DESCRIPTOR mem = *(EFI_MEMORY_DESCRIPTOR*)(((uintn)memmap) + i * descsize);
    //    print_string("memory: ");
    //    print_num(i, 10, 0, 0);
    //    print_string(" type: ");
    //    print_num(mem.Type, 10, 0, 0);
    //    print_string(" size: ");
    //    print_num(mem.NumberOfPages, 10, 0, 0);
    //    print_string("\n\r");
    //}

    traslate_map(memmap, size, descsize);




    //fetch_graphics_map(gop);

    if(aos_memmap[1].type != AOZORA_MEMORY_FREE)
        goto errornf;
    if(aos_memmap[1].high_address < 0x250000)
        goto errornf;

    aozora_memory etcmem = {AOZORA_MEMORY_KERNEL, 0, 0x4000};
    aozora_memory mapmem = {AOZORA_MEMORY_MAP, 0x4000, 0x34000};
    aozora_memory knlmem = {AOZORA_MEMORY_KERNEL, 0x34000, 0x240000};
    aozora_memory etcmap = {AOZORA_MEMORY_MAP, 0x240000, 0x250000};
    aozora_memory gopmem = {AOZORA_MEMORY_GOP, gopbase, gopbase + gopsize};
    addmap(etcmem);
    addmap(mapmem); 
    addmap(knlmem);
    addmap(etcmap);
    addmap(gopmem);
    
    print_map();

    return 0;

errornf:
    print_string("error allocating aozora-os memory, memory at location 0 - 0x250000 is not free\n\r");
    return 1;

}