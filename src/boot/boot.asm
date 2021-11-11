BITS 16 

global bootmain
extern stage2main
extern _STAGE2BYTES

section .stack

stack_top:
    resb 0x7000
stack_bot:

section .boot

bootmain:

    cli                     ;clear interrupts
    
    mov esp, stack_bot      ;setup stack
    mov ebp, esp 

    ; bios read disk

    mov ah, 0x02            ; command for read disk            
    mov al, _STAGE2BYTES    ; number of bytes to read
    mov dh, 0               ; head to read from -> reading from bottom so doesnt matter
    mov ch, 0               ; cylinder to read from   ^
    mov cl, 2               ; sector to read from (reads from that sector inclusivly)
    mov bx, diskload        ; where to store output in memory(right behind out boot loader)
    int 0x13

    jc .error               ; carry flag is set on error

    call stage2main         

    jmp $

.error:
    mov al, 'E'             ; prints E
    mov ah, 0x0e            ;
    int 0x10                ;

    mov al, 'R'
    mov ah, 0x0e
    int 0x10

    mov al, 'R'
    mov ah, 0x0e
    int 0x10

    mov al, 'O'
    mov ah, 0x0e
    int 0x10

    mov al, 'R'
    mov ah, 0x0e
    int 0x10

    jmp $

DRIVE: db 0                 ; stores drive used to boot os

times 510 - ($-$$) db 0

db 0x55
db 0xaa

diskload: