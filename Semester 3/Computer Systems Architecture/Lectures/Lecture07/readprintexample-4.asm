; read a string of numbers
; print the string on the screen


bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll

extern  scanf   , printf           ; tell nasm that exit exists even if we won't be defining it
   ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll   
import printf msvcrt.dll  
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format db '%d',0
    n dd 0
    msjstart db ' insert no of elements',0
    msjstart2 db ' insert the elements',0
    aux dd 0
    s resd 15
    msgfinal db 'The elemensts are',0
     formatafis db '%d, ',0

; our code starts here
segment code use32 class=code
    start:
        push dword msjstart
        call [printf]
        add esp, 4*1
        
        push dword n
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword msjstart2
        call [printf]
        add esp, 4*1
        
        mov esi, 0
        mov ecx, [n]
        repetacit:
        
            pushad ; push all general reg on stack
            
            push dword aux
            push dword format
            call [scanf]
            add esp, 4*2
            
            popad
            
            
            MOV EBX, [aux]
            mov dword  [s+esi], ebx
            add esi, 4
            
         
        loop repetacit
           
        push dword msgfinal
        call [printf]
        add esp, 4*1
        
        mov ecx, [n]
        mov esi, 0
        repetaafisare:
            pushad
            
            mov eax, dword[s+esi]
            
            push eax
            push dword formatafis
            call [printf]
            add esp, 4*2
            
            popad
            
            add esi, 4
            
           
        loop repetaafisare
            
            
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
