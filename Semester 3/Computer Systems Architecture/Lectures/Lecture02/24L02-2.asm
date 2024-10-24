bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ... E = (a*2) - (b*c)
     a db 10
     b db 2
     c dw 3
     
     ;aux variable
     aux dd 0

; our code starts here
segment code use32 class=code
    start:
        ; a *2 
        mov al, 2
        mul byte[a]; ax = 2*a
        
        ; save ax in bx
        mov bx, ax
        
        ; b*c
        movzx ax, byte[b]
        mul word[c] ; dx:ax = b*c
        
        ;E = (a*2) - (b*c)
        ;     bx       dx:ax
        
        ;1 bx -> dd
        ; 2 dx:ax -> eax
        
        mov word[aux+0], ax
        mov word[aux+2], dx
        mov eax, [aux]
        ; dx:ax -> aux -> eax 
        
        movzx ebx, bx ; bx-> ebx
        
        sub ebx, eax ; ebx = res exp
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
