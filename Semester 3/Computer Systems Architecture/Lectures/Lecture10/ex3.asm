;Ex 3. Print a text defined in data segment into a file called ‘addextratext.txt’. The file exists and has a content. 
bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "addextratext.txt", 0       ; filename to be read
    access_mode db "a", 0           ; file access mode:
                                    ; a - appends to a file. Append data at
                                    ; the end of the file.
    file_descriptor dd -1           ; variable to hold the file descriptor
    text db "hello, this text is added extra into a file.", 0   ; text to append to file

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
        je final

        ; append the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        push dword text
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*1 ; clean only the file descriptor
        call [printf]
        add esp, 4*1

        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0
        call [exit]
