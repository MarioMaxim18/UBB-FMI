bits 32
global start        

import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import exit msvcrt.dll
extern fopen, fprintf, fclose, exit

segment data use32 class=data
    file_name db 'file.txt', 0
    text db 'ab12cd#@%3ef4g5h_6+7!i8$j9^g10^h11*i12`~13=', 0 ; 1+2+3+4+5+6+7+8+9+1+0+1+1+1+2+1+3 = 55
    text_len equ $-text
    write_mode db 'w', 0
    write_text db 'Sum of all ditis from text is = %d.', 0
    file_descriptor resd 1
    sum resd 0
    
segment code use32 class=code
    start:
        cld ; DF = 0, parcurgem de la stanga la dreapta
        mov ecx, text_len
        mov esi, text
      
    
        whole_text:
            lodsb ; al <- cate un caracter
            cmp al, '0'
            jl next
            cmp al, '9'
            jg next
            sub al, '0' ; char to int
            add [sum], al
            next:
        loop whole_text
        
        ; fopen("file.txt", "w")
        push dword write_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je final
        
        mov [file_descriptor], eax
        
        ; fprintf(file, "Sum of all ditis from text is = %d.", sum)
        push dword [sum]
        push dword write_text
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        ; fclose(file)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4*1
        
        final:
        
        ; exit(0)
        push dword 0
        call [exit]
