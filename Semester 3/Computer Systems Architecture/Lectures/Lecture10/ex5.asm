;Ex 5: Read a number from a file: ‘nr.txt’
;Add constant 10 at this number and then print the result in file nr.txt, on newline.

bits 32

global start

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose, fscanf, printf
import exit msvcrt.dll
import fopen msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import fscanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    file_name db "nr.txt", 0   ; filename to be created
    access_mode db "r+", 0       ; file access mode:
                                ; w - creates an empty file for writing
    file_descriptor dd -1       ; variable to hold the file descriptor
       
    format_read db '%d', 0
        
    a resd 1
    b resd 1
    newline db 10, 0
    rez resd 1
    
    file_name2 db "nrout.txt", 0   ; filename to be created
    access_mode2 db "w", 0       ; file access mode:
                                ; w - creates an empty file for writing
    file_descriptor2 dd -1   

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
        
        ;int fscanf (FILE * stream=file descriptor, const char * format, <address_variable_1>, <address_variable_2>, <...>)
        push dword a
        push dword format_read ;  definit in ds
        push dword [file_descriptor] ; identificatorul de fisier din care citim
        call [fscanf]
        add esp, 4*3
        
          push dword b
        push dword format_read ;  definit in ds
        push dword [file_descriptor] ; identificatorul de fisier din care citim
        call [fscanf]
        add esp, 4*3

        ; write the text to file using fprintf()
        ; fprintf(file_descriptor, text)
        mov eax, [a]
        mov ebx, [b]
        add eax, ebx
        mov [rez], eax
      
      ;print on new line the value from file add value 10
        
        ;first print new line
        push dword newline
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*2
        
    

          ;second, print the result
        push dword [rez]
        push dword format_read
       
        call [printf]
        add esp, 4*2
        
        
                  ; ;second, print the result
        push dword [rez]
        push dword format_read
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
         push dword access_mode2     
        push dword file_name2
        call [fopen]
        add esp, 4*2                ; clean-up the stack

        mov [file_descriptor2], eax 
        
            ; ;second, print the result
        push dword [rez]
        push dword format_read
        push dword [file_descriptor2]
        call [fprintf]
        add esp, 4*3
        
        ; call fclose() to close the file
        ; fclose(file_descriptor)
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
        
            ; fclose(file_descriptor)
        push dword [file_descriptor2]
        call [fclose]
        add esp, 4

      final:

        ; exit(0)
        push dword 0      
        call [exit]
