#pragma once

#define _U unsigned

#define true 1
#define false 0

#define null 0
#define nullptr (void*) 0

typedef _U char         byte;

typedef    char         int8;
typedef    short        int16;
typedef    int          int32;
typedef    long long    int64;

typedef _U char         uint8;
typedef _U short        uint16;
typedef _U int          uint32;
typedef _U long long    uint64;

typedef    int64        intn;
typedef    uint64       uintn;

typedef    byte*        memory;

typedef    uint8        bool;
typedef    uint8        aozora_status;

#undef _U

static     memory       ram = 0;