#include <efi.h>
#include <efilib.h>
 
#include "print.h"

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_INPUT_KEY Key;
 
    ST = SystemTable;

    EFI_MEMORY_DESCRIPTOR*  mem_map[80];
    UINTN*                  size = sizeof(mem_map) * sizeof(EFI_MEMORY_DESCRIPTOR);
    UINTN*                  key;
    UINTN*                  dsize;
    UINT32*                 dver;

    EFI_STATUS mm = ST->BootServices->GetMemoryMap(size, mem_map, key, dsize, dver);
    EFI_STATUS ex = ST->BootServices->ExitBootServices(ImageHandle, key);
    print_efi_status(mm);
    print_efi_status(ex);

    return Status;
}
