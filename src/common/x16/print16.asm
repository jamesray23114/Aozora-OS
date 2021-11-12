BITS 16

global printdec, printcstr, printchar, clearscreen, printregs
%include "common/x16/print16.nasm"

section .boot2

regdata:
    .ax: dw 1
    .bx: dw 1
    .cx: dw 1
    .dx: dw 1
    .si: dw 1
    .di: dw 1
    .bp: dw 1
    .sp: dw 1
.:

logal: db "AL = ...    0b........          0x.."  , 0 
logah: db "AH = ...    0b........          0x.."  , 0 
logbl: db "BL = ...    0b........          0x.."  , 0 
logbh: db "BH = ...    0b........          0x.."  , 0 
logcl: db "CL = ...    0b........          0x.."  , 0 
logch: db "CH = ...    0b........          0x.."  , 0 
logdl: db "DL = ...    0b........          0x.."  , 0 
logdh: db "DH = ...    0b........          0x.."  , 0 
logsp: db "SP = .....  0b................  0x....", 0
logbp: db "BP = .....  0b................  0x....", 0

printregs:

    mov [regdata.ax], ax
    mov [regdata.bx], bx
    mov [regdata.cx], cx
    mov [regdata.dx], dx

    mov [regdata.di], di
    mov [regdata.bp], bp
    mov [regdata.sp], sp

    __movcur 0, 1
    __printcstr logal
    __movcur 0, 2
    __printcstr logah

    __movcur 0, 3
    __printcstr logbl
    __movcur 0, 4
    __printcstr logbh

    __movcur 0, 5
    __printcstr logcl
    __movcur 0, 6
    __printcstr logch

    __movcur 0, 7
    __printcstr logdl
    __movcur 0, 8
    __printcstr logdh

    __movcur 0, 10
    __printcstr logsp
    __movcur 0, 11
    __printcstr logbp


    __movcur 05, 1
    __print_b10_i8 [regdata.ax]
    __movcur 14, 1
    __print_b2_i8  [regdata.ax]
    __movcur 05, 2
    __print_b10_i8 [regdata.ax + 1]
    __movcur 14, 2
    __print_b2_i8  [regdata.ax + 1]

    __movcur 05, 3
    __print_b10_i8 [regdata.bx]
    __movcur 14, 3
    __print_b2_i8  [regdata.bx]
    __movcur 05, 4
    __print_b10_i8 [regdata.bx + 1]
    __movcur 14, 4
    __print_b2_i8  [regdata.bx + 1]

    __movcur 05, 5
    __print_b10_i8 [regdata.cx]
    __movcur 14, 5
    __print_b2_i8  [regdata.cx]
    __movcur 05, 6
    __print_b10_i8 [regdata.cx + 1]
    __movcur 14, 6
    __print_b2_i8  [regdata.cx + 1]

    __movcur 05, 7
    __print_b10_i8 [regdata.dx]
    __movcur 14, 7
    __print_b2_i8  [regdata.dx]
    __movcur 05, 8
    __print_b10_i8 [regdata.dx + 1]
    __movcur 14, 8
    __print_b2_i8  [regdata.dx + 1]

    __movcur 05, 10
    __print_b10_i16 [regdata.sp]
    __movcur 14, 10
    __print_b2_i16  [regdata.sp]

    __movcur 05, 11
    __print_b10_i16 [regdata.bp]
    __movcur 14, 11
    __print_b2_i16  [regdata.bp]

    __movcur 0, 12

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
        
        cmp cx, 90 * 25
        inc cx

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
        cmp ax, 10
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
        cmp ax, 2
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

printchar:
    mov ah, 0x0E
    int 0x10
    ret
.:
