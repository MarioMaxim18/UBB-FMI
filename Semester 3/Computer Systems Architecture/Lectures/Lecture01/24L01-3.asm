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
      ; E = (7-a) - ( c+d)
    a dw 3
    c db 1
    d dd 2
    
    e dd 0

; our code starts here
segment code use32 class=code
    start:
        ; ... (7-a)
        ; 7 - word
        
        mov ax, 7
        sub ax,[a]; ax= 7-a
        
        ;c+d
        ; c byte + d doubleword
        movzx ebx, byte[c] ; move with 0 in the left from byte c to doubleword ebx
        ;movzx move with zero extended 
        
        add ebx, [d] ; ebx =c+d
        
        ;(7-a) - ( c+d)
        ;  ax   - ebx
        ; ax -> edx
        ; word -> doublword
        movzx edx, ax ; fill with 0 into the left
        
        sub edx, ebx; edx = e
        
        mov dword[e], edx
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
