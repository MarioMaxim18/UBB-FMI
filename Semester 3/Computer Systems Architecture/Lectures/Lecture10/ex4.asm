;Ex4. Read the content from a file (the file exists in the folder and has a content on multiple lines  - ;different phrases) and print this text on the screen and then print the content into another file.
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
    file_name1 db "filewithlongtext.txt", 0   ; filename to be read
    access_mode1 db "r", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor1 dd -1       ; variable to hold the file descriptor
    len equ 300               ; maximum number of characters to read
    text times (len+1) db 0     ; string to hold the text which is read from file
    
    format db 'We have read %d chars from file', 10 , ' The text is: %s', 0
    
    file_name2 db "savedinlongtext.txt", 0   ; filename to be read
    access_mode2 db "w", 0       ; file access mode:
                                ; r - opens a file for reading. The file must exist.
    file_descriptor2 dd -1       ; variable to hold the file descriptor
    

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

        ; display the number of chars we've read and the text
        ; printf(format, eax, text)
        ;format db 'We have read %d chars from file', 10 , ' The text is: %s', 0
        push dword text
        push dword EAX
        push dword format
        call [printf]
        add esp, 4*3
        
        ; print into second file, in savedinlongtext.txt
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
        push dword text
        push dword EAX
        push dword format
        push dword [file_descriptor2]
        call [fprintf]
        add esp, 4*4
        

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

