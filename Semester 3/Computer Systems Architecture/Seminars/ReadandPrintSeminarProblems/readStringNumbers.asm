; read a string of numbers
; extract from the read string only odd numbers.
; print the odd numbers string resulted on the screen

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
    format db '%d',0 ; decimal
    ;fomahex db '%x',0; hexadecimal
    n dd 0
    msjstart db ' insert no of elements: ',0
    msjstart2 db ' insert the elements: ',0
    aux dd 0
    s resd 15
    msgfinal db 10, 'The elemensts are: ',0
     formatafis db '%d ',0
    msgpare db 'The odd elements are: ',0
    sirp resd 15
    contor dd 0
    newline db 10, 0

; our code starts here
segment code use32 class=code
    start:
        push dword msjstart
        call [printf]
        add esp, 4*1
        
        push dword n ; the adress of n, where the n value from the keyboard will be saved
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword msjstart2
        call [printf]
        add esp, 4*1
        
        mov esi, 0
        mov ecx, [n]
        repetacit:
        
            pushad
            
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
            ; salvare registrii generali pe stiva
            
            mov eax, dword[s+esi]
            
            push eax
            push dword formatafis
            call [printf]
            add esp, 4*2
            
            popad
             ; scoatere registrii generali de pe stiva
            
            add esi, 4
            
           
        loop repetaafisare
        
        ; extract odd elems
        mov esi, 0
        mov edi, 0
        mov ecx, [n]
        repetaprelucrare:
            mov eax, dword[s+esi]
            cdq
            mov ebx, 2
            idiv ebx
            cmp edx,0
            JNE adaugainSirp
            JE next
                adaugainSirp:
                    mov eax, dword[s+esi]
                    mov dword[sirp+edi], eax
                    inc dword[contor] ; to count the number of element from the sirp
                    add edi, 4
                next:
                    add esi, 4
        loop repetaprelucrare
         

;print newline
push dword newline
call [printf]
add esp, 4*1

push dword msgpare
call [printf]
add esp, 4*1
         
        mov ecx, [contor]; nr de elem din sirul de printat
        mov esi, 0
        repetaafisareP:
            pushad
            ; salveaza toate dd-reg pe stiva
            
            mov eax, dword[sirp+esi]
            
            push eax
            push dword formatafis
            call [printf]
            ; printf (formatprint, valorile de printat)
            ; param se salveaza de la dr la stanga
            add esp, 4*2
            ; pop dword fomratafis
            ; pop dword eax
            ; esp - extended stack pointer
             popad
             ; ; scoate toate dd-reg pe stiva
             ; functiile externe modifica ecx, eax, edx 
            
            add esi, 4
            
           
        loop repetaafisareP
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
