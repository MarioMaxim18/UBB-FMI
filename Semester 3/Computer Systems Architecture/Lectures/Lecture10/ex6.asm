;ex6. Problem: Read a string from a file ’input.txt’. 
;Extract in a string s all small letters and print this string on the screen
;Extract in a string c all capital letters and print this string c in file ’out.txt’


bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fread, fclose, printf, fprintf
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name1 db "input.txt", 0   ; filename to be read
    access_mode1 db "r", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor1 dd -1       ; variable to hold the file descriptor
    len equ 300               ; maximum number of characters to read
    text times (len+1) db 0     ; string to hold the text which is read from file
    
    format db 'We have read %d chars from file', 10 , ' The text is: %s', 0
    
    file_name2 db "output.txt", 0   ; filename to be read
    access_mode2 db "w", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor2 dd -1       ; variable to hold the file descriptor
    
    nr_caractere resd 1
    s resb 300
    c resb 300
    formatrez db '%s', 0

; our code starts here
segment code use32 class=code
    start:
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode1     
        push dword file_name1
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor1], eax  ; store the file descriptor returned by fopen

        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je final

        ; read the text from file using fread()
        ; after the fread() call, EAX will contain the number of chars we've read 
        ; eax = fread(text, 1, len, file_descriptor)
        push dword [file_descriptor1]
        push dword len
        push dword 1
        push dword text        
        call [fread]
        add esp, 4*4
        
        mov [nr_caractere], eax

        
        
        ; now text contains the string from our input file
        mov esi, 0; text
        mov edi, 0 ; s - small letters
        mov ebp, 0 ; c - capital letters

        ; we first create the string of capital letters
        mov ecx, [nr_caractere]
        repeta:
            mov al, [text+esi]
            cmp al, 'A'
            JAE verificaZM
            JB mergimaideparte
            
            verificaZM:
            cmp al, 'Z'
                JBE adaugainc
                JA mergimaideparte
                
                
                adaugainc:
                mov [c+ebp], al
                inc ebp
                inc esi
                
                jmp end_repeta
                mergimaideparte:
                inc esi
                
        end_repeta:
        loop repeta
        
        ;second, we create the string of small letters
        mov ecx, [nr_caractere]
        mov esi, 0
        mov edi, 0
        repeta2:
        mov al, [text+esi]
        cmp al, 'a'
        JAE verificaz
        JB mergimaideparte2
        
        verificaz:
        cmp al, 'z'
                JBE adaugains
                JA mergimaideparte2
                
                adaugains:
                mov [s+edi], al
                inc edi
                inc esi
                
                jmp end_repeta2
                mergimaideparte2:
                inc esi
                end_repeta2:
        loop repeta2
        
        
        ;print strin with small letters in the screen
        
        push dword s
        push dword formatrez
        call [printf]
        add esp, 4*2
        
        
        ; print into second file the string of capital letters
        ;before printing, we create the file: accesmode w
         ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode2     
        push dword file_name2
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor2], eax  ; store the file descriptor returned by fopen
        
        ;now printing:
        ; display the number of chars we've read and the text
        ; printf(format, eax, text)
        push dword c
        push dword formatrez
        push dword [file_descriptor2]
        call [fprintf]
        add esp, 4*3
        

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor1]
        call [fclose]
        add esp, 4

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor2]
        call [fclose]
        add esp, 4
      final:

        ; exit(0)
        push dword 0
        call [exit]
