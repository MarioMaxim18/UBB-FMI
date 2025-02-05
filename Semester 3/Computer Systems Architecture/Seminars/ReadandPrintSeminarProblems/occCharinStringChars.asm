 
  
    ; Read a string s (s string of characters)
    ; read a character c
    ; compute the number of occurence of c in s
    ; print this number on screen

bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          extern exit  , printf, scanf   , gets          ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          import printf msvcrt.dll
                          import scanf msvcrt.dll
                           import gets msvcrt.dll
segment data use32 class=data
   
formatmsgread db 'Insert a string of chars: ',0    
s resb 20
format_sir db '%s', 0
mesaj db 'We have this string from the keyboard:', 0 
formatcaracter db '%c', 0
caracter dd 0
mesajcitirec db 'insert one character: ', 0
mesajresultat db ' Characterul %c has %d number of occurence', 0
newline db 10, 0

; our code starts here
segment code use32 class=code
    start:
        ; ...
       ; c = a
        ;s = ana are mere 
        ; a : 3 times in s

        ; print on the screen: Insert a string of chars:
push dword formatmsgread
call [printf]
add esp, 4*1
        ;read the string s        
push dword s
call [gets]
add esp, 4*1
                
;print on screen: We have this string from the keyboard:
        
push dword mesaj
call [printf]
add esp, 4*1
                
; printing the s
     
push dword s
push dword format_sir        
call [printf]
add esp, 4*2

; print newline
push dword newline
call [printf]
add esp, 4*1

; print the msg: insert one character
push dword mesajcitirec
call [printf]
add esp, 4*1



; read the character c
    push dword caracter
    push dword formatcaracter
    call [scanf]
    add esp, 4*2
    
    ; compute the number of occurence of c in s
    
    mov ecx, 20 ; max no de char from s
    mov esi, 0 ; to parse string s
    
    mov ebx, 0 ; to count the occ
    
    repeta:
        mov al, [s+esi] ; acces the elem from s
        cmp al, [caracter]
        JE aduna
        JNE mergimaideparte
            aduna:
                inc ebx
                inc esi
            jmp end_repeta
            mergimaideparte:
                inc esi
                
                end_repeta:
    loop repeta
    
    ;printing output
    ; print the screen Characterul %c has      %d number of occurence'
    ;                              caracter    ebx
    push ebx
    push dword [caracter]
    push dword mesajresultat
    call [printf]
    add esp, 4*3
    
    


        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
