; general examples using printf


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
text  db "Now we have CSA lecture.", 0 
format  db "%d", 0  ; definining the format
formathex  db "%x", 0  ; definining the format
nr dd -17
newline db 10,0

n dd 7
formatmesaj  db "It's week %d of school", 0  ; definining the format

formatmesajcunr  db "It's semester %d, week %d of school.", 0  ; definining the format

formatmesajcunr1  db "It's semester 0, week %d of school.", 0 


    ;string asciiz ; ultima poz valoarea 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
push dword text  ; pushing the parameter on the stack
call [printf]       ; calling the printf function
add esp, 4 * 1     ; cleaning the parameters from the stack

; printare newline
push dword newline
call [printf]
add esp, 4*1



push dword [nr]  ; pushing the parameters on the stack from right to left
push dword format  
call [printf]       ; calling the printf function
add esp, 4 * 2     ; cleaning the parameters from the stack

; printare newline
push dword newline
call [printf]
add esp, 4*1


push dword [nr]  ; pushing the parameters on the stack from right to left
push dword formathex  
call [printf]       ; calling the printf function
add esp, 4 * 2     ; cleaning the parameters from the stack

; printare newline
push dword newline
call [printf]
add esp, 4*1

push dword [n]  ; pushing the value of n on the stack
 push dword formatmesaj 
 call [printf]       ; calling the printf function
add esp, 4 * 2     ; cleaning the parameters from the stack


; printare newline
push dword newline
call [printf]
add esp, 4*1

push dword 7  ; pushing parameters on the stack
push dword 1 
push dword formatmesajcunr  
 call [printf]       ; calling the printf function
 add esp, 4 * 3     ; cleaning the parameters from the stack
 
 ; printare newline
push dword newline
call [printf]
add esp, 4*1

push dword 7  ; pushing parameters on the stack
push dword formatmesajcunr1  
 call [printf]       ; calling the printf function
 add esp, 4 * 2    ; cleaning the parameters from the stack


    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
            ; add esp, 4*1 