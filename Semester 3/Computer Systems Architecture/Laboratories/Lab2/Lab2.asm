; 4. –a*a + 2*(b-1) – d (signed)
; a,b,c - byte, d - word 

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 
   
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    a db 3
    b db 2
    d dw 4
   
; our code starts here
segment code use32 class=code
    start:
        mov AL, [a]
        imul AL; AX=a*a
        mov CX, -1
        imul CX; DX:AX=-(a*a)
        mov BX, AX; BX=a*a 

        mov AL, [b]
        sub AL, 1; AL=b-1
        imul byte[2]; AX=2*(b-1)

        add BX, AX; BX=–a*a + 2*(b-1)

        SUB BX, [d]; BX=–a*a + 2*(b-1) - d

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

    