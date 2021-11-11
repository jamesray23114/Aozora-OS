BITS 16

global stage2main
extern _STAGE2BYTES, printcstr, printnum, clearscreen

section .boot2

stage2main:

    call clearscreen

    xor ah, ah
    mov al, 0x6a
    int 0x10

    mov si, welcomestring
    mov bl, 11
    call printcstr 
    ret


welcomestring: db "Welcome to Aozora-OS!", 0
