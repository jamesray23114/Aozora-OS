section .kernal

printcstr:
    .loop:
        lodsb
        or al, al
        jz .exit
        call printchar
        jmp .loop
    .exit:
        ret

printjstr:
    lodsb
    mov cl, al
    .loop:
        dec cl
        or cl, cl
        jz .exit
        lodsb
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