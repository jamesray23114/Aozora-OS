BITS 16

%include "common/x16/print16.nasm"

global stage2main
extern _STAGE2BYTES, DRIVE
section .boot2

line: db 0

stage2main:

    call clearscreen

    __printcstr welcomestring
    __movcur 0, 1


    .loop:
        mov ah, 0

        int 0x13
        jnz .print

        ; mov al, byte [0x041E + 32]   
        jmp .loop   
    
    .print:
        __print_b16_i8 al
        jmp .loop

    hlt
.:

welcomestring: db "  Welcome to Aozora-OS!  ", 0
