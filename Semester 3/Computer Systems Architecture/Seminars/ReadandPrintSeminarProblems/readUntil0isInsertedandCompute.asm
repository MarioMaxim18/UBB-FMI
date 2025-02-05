bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          extern exit  , printf, scanf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          import printf msvcrt.dll
                          import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
   ; 2. Read numbers (in base 10) until the value 0 is read from the keyboard. 
;Compute and display the number of the inserted values and the sum of these values.
;Eg: 1, 3, 4, 0 => 3 values and sum = 8 

 
 ; variable x in which we will keep the number that we are reading from the keyboard
 x dd 0
 ; reading format
 formatread db '%d', 0
 msgprint db ' We have read %d numbers and the sum of these numbers is %d', 0
 suma dd 0
 msgstart db 'Insert numbers. To stop insert 0: ', 0


; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        mov ebx, 0
        ;print msgstart on screen
        push dword msgstart
        call [printf]
        add esp, 4*1
        
        repeta:
            ;read a value for x
            push dword x
            push dword formatread
            call [scanf]
            add esp, 4*2
            
            ;adding the value to the sum and increment the numbers of the values that we have read
            
            mov eax, [x]
            add [suma], eax
            inc ebx
            
            ; check if the value 0 was inserted from the keyboard
            cmp eax, 0 
            JE finalsiafisare
            JNE repeta
            
            finalsiafisare:
                dec ebx   ; beacause  0 is also counted
                ; 'We have read %d numbers and the sum of these numbers is %d', 0
                push dword [suma]
                push ebx
                push dword msgprint
                call [printf]
                add esp, 4*3
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
