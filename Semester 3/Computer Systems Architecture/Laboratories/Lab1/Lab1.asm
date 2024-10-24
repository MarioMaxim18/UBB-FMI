; a –word, b – byte, c - word, d – byte
; 4)(b-a)+3+d-c
; the result will be saved in R of doubleword date type

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 
   
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

    a dw 2
    b db 3
    c dw 4
    d db 1
    R dd 0
    x db 6
   
; our code starts here
segment code use32 class=code
    start:
        mov AX, [a];
        mov BL, [b];
        mov BH, 0;
        sub BX, AX;
        add BX, 3;
        mov AL, [d];
        mov AH, 0;
        add BX, AX;
        mov AX, [c];
        sub BX, AX;
        mov AX, BX;
;       movzx eax, ax;
        mov DX, 0; 
        push DX;
        push AX;
        pop EAX;
        mov [R], EAX;
  
; exit(0)
    push    dword 0      ; push the parameter for exit onto the stack
    call    [exit]       ; call exit to terminate the program