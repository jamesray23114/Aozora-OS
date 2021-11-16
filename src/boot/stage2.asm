BITS 16

global stage2main

extern kernel_main
extern gdt, gdt_descriptor, code_seg, data_seg, editGDT
extern setupPaging

section .boot

stage2main:
    jmp enterKernal
.:

enterKernal:

    cli 

    in al, 0x92
    or al, 2
    out 0x92, al

    lgdt [gdt_descriptor]
    
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp code_seg:start32bitmode
.:

BITS 32

detectCPUID:
    pushfd
    pop eax
    mov ecx, eax

    xor eax, 1 << 21

    push eax 
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    mov eax, ecx
    jz noCPUID_error

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29

    jz noLongMode_error

    ret
.:

noCPUID_error:
    call error
    mov [0xb800E],  byte 'n'
    mov [0xb8010],  byte 'o'
    mov [0xb8014],  byte 'c'
    mov [0xb8016],  byte 'p'
    mov [0xb8018],  byte 'u'
    mov [0xb801A],  byte 'i'
    mov [0xb801C],  byte 'd'
    hlt
.:

noLongMode_error:
    call error
    mov [0xb800E],  byte 'n'
    mov [0xb8010],  byte 'o'
    mov [0xb8014],  byte 'l'
    mov [0xb8016],  byte 'o'
    mov [0xb8018],  byte 'n'
    mov [0xb801A],  byte 'g'
    mov [0xb801C],  byte 'm'
    mov [0xb801E],  byte 'o'
    mov [0xb8020],  byte 'd'
    mov [0xb8022],  byte 'e'
    hlt
.:

error:
    mov [0xb8000],  byte 'E'
    mov [0xb8002],  byte 'R'
    mov [0xb8004],  byte 'R'
    mov [0xb8006],  byte 'O'
    mov [0xb8008],  byte 'R'
    mov [0xb800A],  byte ':'

    ret
.:

start32bitmode:
    
    mov ax, data_seg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call detectCPUID
    call setupPaging
    call editGDT

    call code_seg:enter64bitmode
.:

section .text

BITS 64

enter64bitmode:

    mov ax, data_seg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp kernel_main
.:
