BITS 16

global stage2main
extern _STAGE2BYTES, printcstr, printnum, clearscreen

section .boot2

stage2main:

    call clearscreen

    mov si, welcomestring
    call printcstr 
    ret


welcomestring: db "Welcome to Aozora-OS!", 0
