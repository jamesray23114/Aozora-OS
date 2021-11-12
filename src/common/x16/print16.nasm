BITS 16

extern printcstr
extern printdec
extern printbin
extern printregs
extern clearscreen
extern setcurpos

%macro __print_b10_i8 1 
    xor ax, ax
    mov byte al, %1
    call printdec
%endmacro

%macro __print_b10_i16 1
    mov word ax, %1
    call printdec
%endmacro

%macro __print_b2_i8 1 
    xor ax, ax
    mov byte al, %1
    call printbin
%endmacro

%macro __print_b2_i16 1
    mov word ax, %1
    call printbin
%endmacro

%macro __printcstr 1
    mov si, %1
    call printcstr
%endmacro

%macro __movcur 2
    mov dl, %1
    mov dh, %2
    call setcurpos
%endmacro

%macro __movcurorg 0
    xor dx, dx
    call setcurpos
%endmacro