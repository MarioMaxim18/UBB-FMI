; 4.  (a*2+b/2+e)/(c-d)+x/a; (signed) 12/3+6/3=4+2=6
; a-word; b,c,d-byte; e-doubleword; x-qword

bits 32 ; assembling for the 32 bits architectureS

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 
   
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    aux dd 0
    a dw 3
    b db 2
    c db 7
    e dd 5
    d db 4
    x dq 6
   
; our code starts here
segment code use32 class=code
    start:
        mov ax, [a]          ; AX = a
        movsx ebx, ax        
        add ebx, ebx         ; EBX = a * 2 

        ; Calculate b / 2
        mov al, [b]          
        cbw                  
        mov cl, 2
        idiv cl              ; AX = b / 2 (signed division)

        ; Combine a * 2 and b / 2
        add ebx, eax         ; EBX = a * 2 + b / 2

        ; Add e to the result
        add ebx, [e]         ; EBX = a * 2 + b / 2 + e

        ; Calculate c - d
        mov al, [c]          
        sub al, [d]          
        cbw                  
        movsx ecx, ax        

        ; Divide (a * 2 + b / 2 + e) by (c - d)
        cdq                  
        idiv ecx             ; EAX = (a * 2 + b / 2 + e) / (c - d)

        ; Store the intermediate result
        mov ebx, eax         ; EBX = (a * 2 + b / 2 + e) / (c - d)

        ; Calculate x / a
        mov eax, dword [x]   
        mov edx, dword [x + 4]
        mov ax, [a]          
        cwd                  
        push dx              
        push ax             
        pop ebx              
        cdq                  
        idiv ebx             ; EAX = x / a

        ; Add the two results
        add eax, ebx         ; EAX = (a * 2 + b / 2 + e) / (c - d) + x / a

        ; exit(0)
        push dword 0         ; push the parameter for exit onto the stack
        call [exit]          ; call exit to terminate the program

    