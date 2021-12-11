#pragma once

#include "kernel/drivers/disk.h"
#include "lib/typedef.h"

typedef union ReadonlyRecord
{
    struct
    { 
        uint8   jump[3];
        uint8   identifier[5];
        uint16  version;
        uint16  bytes_per_lsector;
        uint16  lsector_start;
        uint16  table_copies;
        uint64  JTable1_checksum;
        uint64  partition_size;
        uint64  JTable2_checksum;
        uint64  time;
    } record;
    byte data[32];
    
} sJR1;  



typedef union WritableRecord
{
    struct
    {
        uint64 JTable2_checksum;
        uint64 directory_count;
        uint64 file_count;
        uint64 abfile_count;
        uint64 rsector_pointer;
        uint64 rsector_count;
        uint16 alloc_table_size;
        uint16 alloc_table_checksum;
        uint16 res;
        uint16 sig;
    } record;
    byte data[64];

} sJR2;

ReadonlyRecord load_readonly_record()
{
    s JR1 jr;

    return jr;
}