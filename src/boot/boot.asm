BITS 16 

global bootmain
extern stage2main

section .stack

stack_top:
    resb 0x7000
stack_bot:

section .boot

bootmain:

    cli

    mov esp, stack_bot
    mov ebp, esp 

    jmp $



printchar:
    mov ah, 0x0E
    int 0x10
    ret

times 510 - ($-$$) db 0

db 0x55
db 0xaa