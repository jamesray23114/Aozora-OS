#pragma once

#include "efiapi.h"
#include "efiprot.h"

#define BTSV ST->BootServices    // cSpell:ignore BTSV
#define RTSV ST->RuntimeServices // cSpell:ignore RTSV
#define COUT ST->ConOut
#define CIN  ST->ConIn

extern EFI_SYSTEM_TABLE*   ST;
extern EFI_BOOT_SERVICES*  BS;