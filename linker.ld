ENTRY(bootmain)

MEMORY
{
    bootloader  (W): org = 0x07c00, len = -1
    bootloader2 (W): org = 0x07e00, len = -1
    kernel      (W): org = 0x10000, len = -1
    stack       (W): org = 0,       len = -1 
}
SECTIONS
{
    .boot           :   { *(.boot)   } >bootloader
    .boot2          :   { *(.boot2)  } >bootloader2
    .kernel         :   { *(.kernel) } >kernel
    .stack (NOLOAD) : { *(.stack)  } >stack
}