BITS 16

global printnum, printjstr, printcstr, printchar, clearscreen

section .boot2

clearscreen:
    mov ah, 0x02
    xor dx, dx
    int 0x10

    mov cx, 0

    .loop:
        mov al, ' '
        call printchar
        
        cmp cx, 90 * 25
        inc cx

        jnz .loop

    mov ah, 0x02
    xor bx, bx
    xor dx, dx
    int 0x10

    ret

printcstr:
    .loop:
        lodsb
        or al, al
        jz .exit
        call printchar
        jmp .loop
    .exit:
        ret

printnum:
    mov bx, 1
    mov cx, 10

    .loop:    
        cmp ax, cx
        jl .print

        mov dx, 0

        div cx
        push dx
        inc bx
        jmp .loop

    .print:

        add ax, '0'

        call printchar

        dec bx
        or bx, bx
        jz .exit

        pop ax
        jmp .print

    .exit:
        ret

printchar:
    mov ah, 0x0E
    int 0x10
    ret