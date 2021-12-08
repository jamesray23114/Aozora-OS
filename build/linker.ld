ENTRY(bootmain)


SECTIONS
{   
    .stack 0x1000 (NOLOAD) : 
    {
        *(.stack)
    }

    . = 0x07c00;
    .boot   :   
    { 
        *(.boot)   
    }  
    . = 0x07c00 + (SIZEOF(.boot) / 512 + 1) * 512;
    .text : 
    { 
        *(.text)   
    }  
    .data : 
    { 
        *(.data)   
    }  
    .rodata : 
    { 
        *(.rodata) 
    }
    .bss :  
    { 
        *(.bss) 
        *(COMMON) 
    } 
    .kernel :
    {
        *(.rodata)
        *(.data)
        *(.text)
        *(.bss)
        *(COMMON) 
    }
    
    _SEGMENTBOOT = ((SIZEOF(.boot) - 512) / 512) + 1;
    _SEGMENTTEXT = (ALIGN(512) / 512) - ((0x07c00 + SIZEOF(.boot)) / 512) - 1;
    _KERNELLOC   = 0x07c00 + (_SEGMENTBOOT + 1) * 512; 
}
