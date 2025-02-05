bits 32
global start
extern exit, printf
extern concatenare 
import printf msvcrt.dll
import exit msvcrt.dll
segment data use32 class=data public
s1 db 'abcdef'
len1 equ $-s1
s2 db '1234'
len2 equ $-s2
s3 times len1+len2+1 db 0
segment code use32 class=code public
start:
; we place all the parameters on the stack
push dword len1
push dword len2
push dword s3
push dword s2
push dword s1

call concatenare

push dword s3
call [printf]
add esp, 4*1

push dword 0
call [exit]
