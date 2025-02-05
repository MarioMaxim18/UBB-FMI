; general examples
; read and print


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit , scanf   , printf           ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll   
import printf msvcrt.dll                       ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

nr dd  0             ; defining the variable n
format  db "%d", 0  ; definining the format
formathex db '%x',0

a dd  0              ; defining the variable n
b dd 0
c dd 0
newline db 10, 0


n dd  0       ; defining the variable n
m dd 0
format2  db "%d %d", 0 

format3  db "%d %d %d", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...


        ;read a number using scanf
        
push dword n       ; pushing the parameters on the stack from right to left
push dword format
call [scanf]       ; calling the scanf function for reading
add esp, 4 * 2     ; cleaning the parameters from the stack

 
 ; print the number using printf
 push dword [n]  ; pushing the parameters on the stack from right to left
 push dword format  
 call [printf]       ; calling the printf function
 add esp, 4 * 2 

 
 ; ; print newline (if we want a new line to be printed 
; push dword newline
; call [printf]
; add esp, 4*1

; ; print a number in hexadecimal format

 ; push dword [n]  ; pushing the parameters on the stack from right to left
 ; push dword formathex
 ; call [printf]       ; calling the printf function
 ; add esp, 4 * 2 

 ; read 2 numbers using scanf
push dword  m      ; pushing the parameters on the stack from right to left
push dword n
push dword format2
call [scanf]       ; calling the scanf function for reading
add esp, 4 * 3     


    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
