; 4.Given the bytes A and B, Compute the doubleword C as follows:
    ;· the bits 8-15 of C have the value 0
    ;· the bits 16-23 of C are the same as the bits of B
    ;· the bits 24-31 of C are the same as the bits of A
    ;· the bits 0-7 of C have the value 1

bits 32 ; assembling for the 32 bits architectureS

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 
   
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    a db 11100111b
    b db 10001001b
    c dd 0
   
; our code starts here
segment code use32 class=code
    start:
        or dword[c], 00000000000000000000000011111111b;
 
        mov eax, 0
        mov AL, [b]
        shl EAX, 24; EAX = b7 b6 b5 b4 b3 b2 b1 b0 0 0 0 ... 0
        shr EAX, 8
        or dword[c], EAX
        or word[c+0], 0000_0000_0000_0000b
        or word[c+2], 0000_1111_1111_1111b
        
        mov al, byte[a]
        mov byte[c+3], al
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
         