BITS 16

%include "common/x16/print16.nasm"

global stage2main
extern kmain
extern gdt, gdt_descriptor, code_seg, data_seg

section .boot2

stage2main:
    call clearscreen
    jmp enter32bitmode
    ;call enter64bitmode
    ;call kmain

    jmp $
.:


enter32bitmode:

    cli 

    in al, 0x92
    or al, 2
    out 0x92, al

    lgdt [gdt_descriptor]
    
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ;hlt

    jmp code_seg:startPmode

    ;ret
.:

enter64bitmode:

    ret
.:

[BITS 32]

startPmode:
    
    mov ax, data_seg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


    mov [0xb8000], byte 'h'

    hlt

times 2048 - ($ - $$) db 0