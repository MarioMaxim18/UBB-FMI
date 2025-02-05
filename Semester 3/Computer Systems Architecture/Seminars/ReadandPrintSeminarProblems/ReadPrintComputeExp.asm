bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit  , printf, scanf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          import printf msvcrt.dll
                          import scanf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
;1. Read two numbers a, b in decimal. 
;Read two numbers in hexadecimal (c and d).
;Compute the following expression: 12 / a + (c*d + b*1010b) / 12h 
;and print the result on screen in hexadecimal and decimal.

  a dd 0
  b dd 0
  c dd 0
  d dd 0
  formatdecimal db '%d', 0
  formathexadecimal db '%x',0
  printresult db 'result = %x in hexadecimal and %d in decimal', 0  
  ;params from right to left on the stack, value rez for %d and then value rez for %x

  printmsgstarta db 'Insert a value for  a in decimal =', 0
    printmsgstartb db 'Insert a value for  b in decimal =', 0
      printmsgstartc db 'Insert a value for  c in hexadecimal =', 0
        printmsgstartd db 'Insert a value for  d in hexadecimal =', 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        
        ;print msg for insert from keyboard  a
        
        push dword printmsgstarta
        call [printf]
        add esp, 4*1
       
       ; read the value a
        
         push dword a
         push dword formatdecimal
         call [scanf]
         add esp, 4*2
         
          ;print msg for insert from keyboard  b
        
        push dword printmsgstartb
        call [printf]
        add esp, 4*1
        ; read the value b
        
         push dword b
         push dword formatdecimal
         call [scanf]
         add esp, 4*2
         
         
          ;print msg for insert from keyboard  c
        
        push dword printmsgstartc
        call [printf]
        add esp, 4*1
        
        ; read the value c
        
         push dword c
         push dword formathexadecimal
         call [scanf]
         add esp, 4*2
         
          ;print msg for insert from keyboard  d
        
        push dword printmsgstartd
        call [printf]
        add esp, 4*1
        ; read the value d
        
         push dword d
         push dword formathexadecimal
         call [scanf]
         add esp, 4*2
         
         ; compute the exp: 12 / a + (c*d + b*1010b) / 12h
         ; (c*d + b*1010b) 
         mov eax, [c]
         imul dword [d]   ; edx:eax = c*d
         
         ; copy edx:eax in ecx:ebx
         
         mov ebx, eax
         mov ecx, edx
            ;  b*1010b
            
         mov eax, 1010b
         imul dword [b] ; edx:eax = 1010b*b
         
         ;c*d + b*1010b
         ; ecx:ebx + 
         ; edx:eax
         
         add eax, ebx
         adc edx, ecx  ; edx:eax = c*d + b*1010b
         
         ;(c*d + b*1010b ) / 12h
         mov ebx, 12h
         ; edx:eax = c*d + b*1010b
         idiv ebx   ; edx:eax/ ebx   = eax - catul imp si in edx restul imp, deci eax = (c*d + b*1010b) / 12h
         
         ; salvare eax in ebx
         mov ebx, eax; ebx = (c*d + b*1010b) / 12h
         
          ;12 / a
          mov eax, 12
          CDQ  ; eax -> edx:eax
          idiv dword [a]  ; eax - quot 12 / a si in edx reminder
          
;     2 / a + (c*d + b*1010b) / 12h
        add eax, ebx ; eax  = 2 / a + (c*d + b*1010b) / 12h
        
        ; print the result
        
        ; printresult db 'result = %x in hexadecimal and %d in decimal', 0
        
        push eax  ; will replace %d
        push eax   ; will replace %x
        push dword printresult
        call [printf]
        add esp, 4*3
          
          
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
