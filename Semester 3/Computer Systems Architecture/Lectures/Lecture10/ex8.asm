bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll    
import fclose msvcrt.dll     
import fprintf msvcrt.dll    

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    nume db "fisierscriere.txt", 0
    text db "_Sir cu ?cifre, caractere speciale /si_, si 099, _LITERE-; si altele?=<>aSDasdfF!%$ CUVANT][\]litere}}{~aaa"
    ;       "XSirXcuXXcifreXXcaractereXspecialeXXsiXXXsiX099XXXLITEREXXXsiXalteleXXXXaSDasdfFXXXXCUVANTXXXXlitereXXXXaaa"
    text_len EQU $-text
    mod_acces db "w", 0
    descriptor dd 0
    format db "%c", 0
    

; our code starts here
segment code use32 class=code
    start:
     
        push dword mod_acces
        push dword nume
        call [fopen]
        add esp, 4*2
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca eax != 0)
        CMP eax, 0
        JE final
        mov [descriptor], eax
        
        mov ecx, text_len    ; ecx = lungimea textului (numarul de caractere din text)
        mov esi, text
        CLD
        repeta:
        
            LODSB            ; incarcam urmatorul caracter din text in al
            
            ;CMP al, ' '      ; daca e spatiu sarim peste
            ;JE next
            
            CMP al, '0'      ; daca al < '0' at nu e nici cifra, nici litera mare sau mica deci inlocuim
            JB inlocuieste
            CMP al, '9'      ; daca al >= '0' si al <= '9' at e cifra si sarim peste
            JBE next
            CMP al, 'A'      ; daca al > '9' si al < 'A' at nu e nici cifra, nici litera mare sau mica deci inlocuim
            JB inlocuieste
            CMP al, 'Z'      ; daca al >= 'A' si al <= 'Z' at e litera mare deci sarim peste
            JBE next
            CMP al, 'a'      ; daca al > 'Z' si al < 'a' at nu e nici cifra, nici litera mare sau mica deci inlocuim
            JB inlocuieste
            CMP al, 'z'      ; daca al >= 'a' si al <= 'z' at e litera mica deci sarim peste
            JBE next
                             ; daca e mai mare decat 'z' inlocuim oricum
            
            inlocuieste:
            
                mov al, 'X'
            
            next:
            
                mov bl, al
                mov eax, 0
                mov al, bl
                PUSHAD
                
                ; scriem in fisier caracterul
                push dword eax
                push dword format
                push dword [descriptor]
                call [fprintf]
                add esp, 4*3    ; eliberam stiva
                
                POPAD
        
        LOOP repeta
        
        
        ; inchidem fisierul
        push dword [descriptor]
        call [fclose]
        add esp, 4      ; eliberam stiva
        
        final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
