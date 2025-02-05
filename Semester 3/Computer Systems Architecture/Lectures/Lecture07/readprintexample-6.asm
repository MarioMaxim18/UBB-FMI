; read a string of characters (a sentence).
; extract all vowels from the string.
; print the resulted string on the screen

; eg. ana are mere => aaaeee


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
                                                   
extern exit, printf, gets

import exit msvcrt.dll
import printf msvcrt.dll
import gets msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
   s resb 20
   format_sir db '%s', 0
   mesaj db 'S-a citit acest sir:', 0 
   vocale db 'aeiouAEIOU'
   lvoc equ $-vocale
   rezv resb 20
   copie dd 0
   newline db 10, 0

; our code starts here
segment code use32 class=code
    start:
              
        push dword s
        call [gets]
        add esp, 4*1
                
        ;print pe ecran mesajul
        
        push dword mesaj
        call [printf]
        add esp, 4*1
                
        ; print pe ecran sirul citit
        
        
        push dword s
        push dword format_sir        
        call [printf]
        add esp, 4*2
        
        ; prelucare si identificare vocale
        mov esi, 0; s
        mov ecx, 20
        mov edi, 0 ; rezv
        repetaidentificare:
            mov al, byte[s+esi]
            mov [copie], ecx 
            mov ecx, lvoc
            mov ebp, 0
            repetavocale:
                mov bl, byte[vocale+ebp]
                cmp al, bl
                je adauga
                jne next
                adauga:
                    mov [rezv+edi], al
                    inc edi
                next:
                    inc ebp
            loop repetavocale
            
            mov ecx, [copie]
            inc esi
        loop repetaidentificare 
          
          
        ; trecere pe linie noua
        push dword newline        
        call [printf]
        add esp, 4*1

            ; afisare sir voale din sir initial
        push dword rezv
        push dword format_sir        
        call [printf]
        add esp, 4*2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program

