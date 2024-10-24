bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; e= a/c + (b*d) - 13/ (a+2)
    ;a byte, b word, c-byte, d-doubleword
    ; signed
    a db 10
    b dw -3
    c db -2
    d dd -10
    aux dq 0
    aux2 dq 0
    

; our code starts here
segment code use32 class=code
    start:
        ; a/c
        ;byte/byte
        movsx ax, byte [a]
         ; sol2
         ; mov al, [a]
         ; cbw ; ax = a
        idiv byte[c]; al = a/c 
        
        ; save al in bl
        mov bl, al; bl =a/c
        ;(b*d)
        ;word*doubleword
        mov ax, [b]
        cwde ; ax -> eax 
            ;sol2:
            ; movsx eax, ax 
        imul dword[d] ; edx:eax = b*d
        
        ; edx:eax - > aux
        mov dword[aux+0], eax
        mov dword[aux+4], edx
        
        ; 13/ (a+2)
        mov cl, 2
        add cl, [a]; cl=a+2
        mov ax, 13
        idiv cl ; ax/cl = al = 13/(a+2)
        
        ; e= a/c + (b*d) - 13/ (a+2)
        ;     bl +   aux - al 
        ;     byte+   quad - byte
        
        ;al = 13/(a+2)
        ; al -> edx:eax 
        cbw ; al->ax
        cwde ; ax -> eax
        cdq ; eax -> edx: eax 
        
        ; edx: eax -> aux2
        mov dword[aux2+0], eax
        mov dword[aux2+4], edx
        
        ; bl -> edx:eax
        mov al, bl
        cbw
        cwde
        cdq
        ; edx:eax = bl = a/c
        
        ; ; e= a/c + (b*d) - 13/ (a+2)
        ;      edx:eax + aux - aux2
        add eax, dword[aux+0]
        adc edx, dword[aux+4]
        
        sub eax, dword[aux2+0]
        sbb edx, dword[aux2+4]
        ; edx:eax = e
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
