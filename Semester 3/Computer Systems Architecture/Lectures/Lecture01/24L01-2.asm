bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; E = (7-a) - ( c+d)
    a db 3
    c db 1
    d db 2
    e db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;(7-a)
        mov al,7
        sub al, [a] ; al = 7-a
        
        ; ( c+d)
        mov bl, [c]
        add bl, [d]; bl = c+d
        
        ; (7-a) - ( c+d)
        sub al, bl; al = (7-a) - ( c+d)
        
        ; al-> e
        mov byte[e], al
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
