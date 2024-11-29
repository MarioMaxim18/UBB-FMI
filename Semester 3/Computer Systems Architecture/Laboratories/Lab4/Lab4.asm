;   A4. A string of bytes A is given. Construct string B such that each element from B represent the product of two consecutive elements from string A.
;   If A = 2, 4, 5, 7 => B = 8, 20, 35

bits 32 ; assembling for the 32 bits architectureS

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 
   
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    s db 2, 4, 5, 7
    len_sir equ $-s
    b times len_sir-1 dw 0 
   
; our code starts here
segment code use32 class=code
    start:
        mov ECX, len_sir-1
        mov ESI, 0
        mov EDI, 0
        
        repeta:
            mov AL, [s+ESI]
            mov BL, [s+ESI+1]
            mul BL; AX =s1*s2
            mov [b+EDI], AX
            inc ESI               
            add EDI, 2                
        loop repeta
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
         
