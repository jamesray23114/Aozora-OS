#pragma once

#include "efiapi.h"
#include "efiprot.h"

#define BTSV ST->BootServices    // TODO: remove these macros and global definitions for BS and ST
#define RTSV ST->RuntimeServices 
#define COUT ST->ConOut
#define CIN  ST->ConIn

extern EFI_SYSTEM_TABLE*   ST;
extern EFI_BOOT_SERVICES*  BS;