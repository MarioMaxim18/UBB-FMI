;   B9. A string of doublewords S is given. Compute string D containing only low bytes from low words from each doubleword from string S.
;   If S  = 51234678h, 1a2b3c4dh => D = 78h, 4dh

bits 32 ; assembling for the 32 bits architectureS

; declare the EntryPoint (a label defining the very first instruction of the program)
global start 
   
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    s dd 51234678h, 1a2b3c4dh
    ; 78 46 23 51 4d 3c 2b 1a
    len_s equ ($-s)/4   ; 1 dd = 4 bytes
    d times len_s db 0  

   
; our code starts here
segment code use32 class=code
    start:
        mov ECX, len_s
        mov ESI, 0
        mov EDI, 0
        
        repeta:
            mov al, byte[s+ESI]
            ;mov EAX, dword[s+ESI]
            mov [d+EDI], AL
            add ESI, 4
            inc EDI
        loop repeta
            
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
         
