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
    c db 10
    ; c * 3
    a dw 10
    b dw 4
    ; a *b
    d dd 11
    e dd 5

; our code starts here
segment code use32 class=code
    start:
        ; ...  ; c * 3
        mov al, 3 ; al = 3
        mul byte [c] ; ax = 3*c
        mov bx, ax ; save the value from ax 
           ; a *b
        mov ax, [a]
        mul word[b]; dx:ax 
        
        mov eax,[e]
        mul dword[d] ; d*e = edx:eax 
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
