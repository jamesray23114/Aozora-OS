BITS 16

%include "common/x16/print16.nasm"

global stage2main
extern _STAGE2BYTES, DRIVE
section .boot2

line: db 0

stage2main:

    call clearscreen

    __printcstr welcomestring

    mov ax, 16
    mov dx, 77

    push ax
    push ax
    push ax
    push ax
    push ax
    push ax
    push ax

    __printregs

    hlt
.:

welcomestring: db "____Welcome to Aozora-OS!____", 0
