section .boot2

global gdt, gdt_descriptor, data_seg, code_seg

gdt:
    dd 0
    dd 0            ; null header
.code_seg:
    dw 0xFFFF       ; max value
    dw 0x0000       ; base value
    db 0x00         ; base 2 value
    db 10011010b    ; flags 
    db 11001111b    ; flags 2
    db 0x00         ; base 3
.data_seg:
    dw 0xFFFF       ; max value
    dw 0x0000       ; base value
    db 0x00         ; base 2 value
    db 10010010b    ; flags 
    db 10001111b    ; flags 2 & max value
    db 0x00         ; base 3
.end:

gdt_descriptor:
    dw gdt.end - gdt - 1    ;size
    dd gdt                  ;offset

code_seg equ gdt.code_seg - gdt
data_seg equ gdt.data_seg - gdt