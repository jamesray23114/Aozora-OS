#pragma once

#include <efi/efi.h>

#include <lib/memory.h>
#include <typedef.h>

#include <bootlib/gop.h>
#include <bootlib/print.h>

void traslate_map(EFI_MEMORY_DESCRIPTOR* memmap, uintn size, uintn descsize);
aozora_status fetch_memory_map(EFI_HANDLE mainhandle);