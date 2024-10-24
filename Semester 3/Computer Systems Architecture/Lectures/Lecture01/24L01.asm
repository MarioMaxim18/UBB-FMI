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
    a db 10 ; a define byte with value 10 ; 2 haxadecimal digits
    b dw 10 ; 4 hexadecimal digits  10=000ah
    c dd 11
    d dq 12
    
    x dd 12345678h
    ;    dx = 1234 ax = 5678
    
    z dq 1122334455667788h
    ; z -> edx:eax , edx= 11223344, eax = 55667788
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;mov dest, source
            ; dest <- source
        ; a -> 
        mov al, [a] ; al = 10
        mov bx, [b] ; bx= 10
        mov ecx, [c] ;ecx=11
        
        mov ax, word[x+0]
        
        mov dx, word[x+2]
        
        ; 4 bytes = doubleword = dword
        mov eax, dword[z+0]
        mov edx, dword[z+4]
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
