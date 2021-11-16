BITS 16 

global bootmain
global DRIVE

extern stage2main, _SEGMENTBOOT, _SEGMENTTEXT, _KERNELLOC

section .stack

stack_top:
    resb 0x6000
stack_bot:

section .boot

bootmain:

    cli                     ;clear interrupts
    
    mov sp, stack_bot       ;setup stack
    mov bp, sp 

    mov [DRIVE], dl

    call clearscreen

    ; bios read disk

    mov dl, [DRIVE]         ; disk os was loaded from

    mov ah, 0x02            ; command for read disk            
    mov al, _SEGMENTBOOT    ; number of segments (512 bytes) to read
    mov dh, 0               ; head to read from -> reading from bottom so doesnt matter
    mov ch, 0               ; cylinder to read from   ^
    mov cl, 2               ; sector to read from (reads from that sector inclusivly)
    mov bx, diskload        ; where to store output in memory(right behind out boot loader)
    int 0x13

    cmp ah, 0
    jnz error               ; carry flag is set on error

    mov ah, 0x02            ; command for read disk            
    mov al, _SEGMENTTEXT    ; number of segments (512 bytes) to read
    mov dh, 0               ; head to read from -> reading from bottom so doesnt matter
    mov ch, 0               ; cylinder to read from   ^
    mov cl, _SEGMENTBOOT + 2    ; sector to read from (reads from that sector inclusivly)
    mov bx, _KERNELLOC          ; where to store output in memory(right behind out boot loader)
    int 0x13

    cmp ah, 0
    jnz error               ; carry flag is set on error

    jmp stage2main         

error:
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

    hlt
.:

clearscreen:
    call move_cursor_to_org

    mov cx, 0

    .loop:
    mov al, ' '
    mov ah, 0x0e
    int 0x10

    inc cx

    cmp ecx, 90 * 10
    jb .loop
    
    call move_cursor_to_org

    ret
.:

move_cursor_to_org:
    mov ah, 2
    xor bx, bx
    xor dx, dx
    int 0x10
    ret

DRIVE: db 0                 ; stores drive used to boot os

times 510 - ($-$$) db 0

db 0x55
db 0xaa

diskload: