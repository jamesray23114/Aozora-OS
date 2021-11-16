ENTRY(bootmain)


SECTIONS
{   
    .bss 0x1000 :  
    { 
        *(.bss) 
        *(COMMON) 
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
    .data : ALIGN(16)
    { 
        *(.data)   
    }  
    .rodata : ALIGN(16)  
    { 
        *(.rodata) 
    }    
    _SEGMENTBOOT = ((SIZEOF(.boot) - 512) / 512) + 1;
    _SEGMENTTEXT = (SIZEOF(.text) / 512) + 1;
    _KERNELLOC   = 0x07c00 + (_SEGMENTBOOT + 1) * 512; 
}
