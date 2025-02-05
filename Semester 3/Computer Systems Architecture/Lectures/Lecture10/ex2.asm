;Ex2. Open an existing file with the name ‘toread.txt’. The file  toread.txt exists in current folder:
bits 32
global start; declare external functions needed by our program
extern exit, fopen, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db 'toread.txt', 0   ; filename to be created
    access_mode db "r", 0       ; file access mode:
                                ; r - creates an empty file for reading
    file_descriptor dd -1       ; variable to hold the file descriptor
    
    eroaredeschidere db ' unable to open the file', 0

; our code starts here
segment code use32 class=code
    start:
        ; call fopen() to create the file
        ; fopen() will return a file descriptor in the EAX or 0 in case of error
        ; eax = fopen(file_name, access_mode)
        push dword access_mode     
        push dword file_name
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor], eax  ; store the file descriptor returned by fopen
        
        ; check if fopen() has successfully created the file (EAX != 0)
        cmp eax, 0
        je eroareOpen
        
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
        jmp final 
        
        eroareOpen:
            ;print on the screen a message
            push dword eroaredeschidere
            call [printf]
            add esp, 4*1
        
      final:
        ; exit(0)
        push dword 0      
        call [exit]

