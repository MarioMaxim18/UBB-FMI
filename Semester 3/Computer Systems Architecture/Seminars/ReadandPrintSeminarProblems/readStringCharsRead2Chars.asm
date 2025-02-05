bits 32 ; assembling for the 32 bits architecture

global start        

extern exit             
extern scanf,printf,gets, getchar
import scanf msvcrt.dll
import printf msvcrt.dll
import gets msvcrt.dll
import exit msvcrt.dll
import getchar msvcrt.dll    
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s resb 100
    format_sir db '%s', 0
    formatcaracter db '%c', 0
    caracter1 resb 1
    caracter2 resb 1
    mesajcitiresir db 'Citeste un sir: ', 0 
    mesajafisaresir db 'Sirul citit este %s ' ,0
    mesajcaracter1 db 'Introduceti un caracter ',0
    mesajcarcater2 db 'Introduceti al doilea caracter',0
    newline db 10,0
    mesajresc db 'Cele 2 caractere citite sunt %c si %c ', 0
    

segment code use32 class=code
    start:
       ;mesaj pt primul caracter citit
        push mesajcaracter1
        call [printf]
        add esp,4*1
        
        ;citim caracterul efectiv
        push dword caracter1
        push dword formatcaracter
        call [scanf]
        add esp, 4*2
        
        ;dupa carcater avem si un enter salvat, il "stergem pe enter" folosind getchar
        call [getchar] ; to delete the "enter" character inserted automaticaly after the character1
        
        ;mesaj pt caracterul 2 de citit
        push mesajcarcater2
        call [printf]
        add esp,4*1
        
        ;citim caracterul 2
        push dword caracter2
        push dword formatcaracter
        call [scanf]
        add esp, 4*2
        
        ;dupa carcater avem si un enter salvat, il "stergem pe enter" folosind getchar
        call [getchar]
        
        ;mesaj pt citire sir
        push dword mesajcitiresir
        call [printf]
        add esp,4*1
        
       ;citire efectiva sir        
        push dword s
        call [gets]
        add esp, 4*1
        
        ;afisam ceea ce am citit:
        ;intai trecem pe linie noua
        push dword newline
        call [printf]
        add esp, 4*1
        
        ;afisam sirul citit
        push dword s
        push mesajafisaresir
        call [printf]
        add esp, 4*2
        
        ;afisam newline again
        push dword newline
        call [printf]
        add esp, 4*1
        
        
        ; si afisam cele 2 caractere citite
        push dword [caracter2]
        push dword [caracter1]
        push dword mesajresc
        call [printf]
        add esp, 4*3     
        
         ;testam intai :)
         ; acum incepem procesarea lui s conform cerintei.
      
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
