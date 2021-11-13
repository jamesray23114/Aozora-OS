BITS 16

global printdec, printcstr, printchar, clearscreen, printregs
%include "common/x16/print16.nasm"

section .boot2

regdata:
    .ax: dw 0
    .bx: dw 0
    .cx: dw 0
    .dx: dw 0
    .bp: dw 0
    .sp: dw 0
.:

log: 
    .al: db "AL = ...    0b........          0x.."  , 0 
    .ah: db "AH = ...    0b........          0x.."  , 0 
         db "BL = ...    0b........          0x.."  , 0 
         db "BH = ...    0b........          0x.."  , 0 
         db "CL = ...    0b........          0x.."  , 0 
         db "CH = ...    0b........          0x.."  , 0 
         db "DL = ...    0b........          0x.."  , 0 
         db "DH = ...    0b........          0x.."  , 0 
         db "SP = .....  0b................  0x....", 0
         db "BP = .....  0b................  0x....", 0
    .size: db ($ - log) / (.ah - .al) + 2
.:


printregs:

    mov [regdata.ax], ax
    mov [regdata.bx], bx
    mov [regdata.cx], cx
    mov [regdata.dx], dx

    mov [regdata.bp], bp
    mov [regdata.sp], sp

    mov cx, 2
    mov si, log.al

    .loopstr:
        __movcur 0, cl
        __printcstr si

        inc cx

        cmp cl, [log.size]
        jl .loopstr


    __movcur 05, 2
    __print_b10_i8 [regdata.ax]
    __movcur 14, 2
    __print_b2_i8  [regdata.ax]
    __movcur 34, 2
    __print_b16_i8  [regdata.ax]

    __movcur 05, 3
    __print_b10_i8 [regdata.ax + 1]
    __movcur 14, 3
    __print_b2_i8  [regdata.ax + 1]
    __movcur 34, 3
    __print_b16_i8  [regdata.ax + 1]

    __movcur 05, 4
    __print_b10_i8 [regdata.bx]
    __movcur 14, 4
    __print_b2_i8  [regdata.bx]
    __movcur 34, 4
    __print_b16_i8  [regdata.bx]

    __movcur 05, 5
    __print_b10_i8 [regdata.bx + 1]
    __movcur 14, 5
    __print_b2_i8  [regdata.bx + 1]
    __movcur 34, 5
    __print_b16_i8  [regdata.bx + 1]

    __movcur 05, 6
    __print_b10_i8 [regdata.cx]
    __movcur 14, 6
    __print_b2_i8  [regdata.cx]
    __movcur 34, 6
    __print_b16_i8  [regdata.cx]

    __movcur 05, 7
    __print_b10_i8 [regdata.cx + 1]
    __movcur 14, 7
    __print_b2_i8  [regdata.cx + 1]
    __movcur 34, 7
    __print_b16_i8  [regdata.cx + 1]

    __movcur 05, 8
    __print_b10_i8 [regdata.dx]
    __movcur 14, 8
    __print_b2_i8  [regdata.dx]
    __movcur 34, 8
    __print_b16_i8  [regdata.dx]

    __movcur 05, 9
    __print_b10_i8 [regdata.dx + 1]
    __movcur 14, 9
    __print_b2_i8  [regdata.dx + 1]
    __movcur 34, 9
    __print_b16_i8  [regdata.dx + 1]

    __movcur 05, 10
    __print_b10_i16 [regdata.sp]
    __movcur 14, 10
    __print_b2_i16  [regdata.sp]
    __movcur 34, 10
    __print_b16_i16  [regdata.sp]

    __movcur 05, 11
    __print_b10_i16 [regdata.bp]
    __movcur 14, 11
    __print_b2_i16  [regdata.bp]
    __movcur 34, 11
    __print_b16_i16  [regdata.bp]

    __movcur 0, 13

    ret
.:

setcurpos:

    xor bh, bh
    mov ah, 2
    int 0x10

    ret
.:

clearscreen:
    __movcurorg

    mov cx, 0

    .loop:
        mov al, ' '
        call printchar
        
        inc cx
        cmp cx, 90 * 10
        
        jnz .loop

    __movcurorg     

    ret
.:

printcstr:
    .loop:
        lodsb
        or al, al
        jz .exit
        call printchar
        jmp .loop
    .exit:
        ret
.:

printdec:
    mov bx, 1
    mov cx, 10

    .loop:    
        cmp ax, cx
        jl .print

        xor dx, dx

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
.:

printbin:
    mov bx, 1
    mov cx, 2

    .loop:    
        cmp ax, cx
        jl .print

        xor dx, dx

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
.:

printhex:
    mov bx, 1
    mov cx, 16

    .loop:    
        cmp ax, cx
        jl .print

        xor dx, dx

        div cx

        push dx
        inc bx
        jmp .loop


    .print:

        cmp ax, 9
        jl .below10

        add ax, 7

    .below10:
        add ax, '0'

        call printchar

        dec bx
        or bx, bx
        jz .exit

        pop ax
        jmp .print

    .exit:
        ret
.:

printchar:
    mov ah, 0x0E
    int 0x10
    ret
.:
