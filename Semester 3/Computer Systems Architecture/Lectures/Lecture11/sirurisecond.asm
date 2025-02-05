
	
bits 32

segment code use32 class=code public
global concatenare ; export concatenare
concatenare:


mov esi, [esp+4] 
           ;ESI = the offset of the source string (s1)
mov edi, [esp+12] 
           ;EDI = the offset of the destination string(s3)
mov ecx, [esp+20] 
          ; ECX = len1

cld

repeta:
	lodsb
	stosb
loop repeta
	
	mov esi, [esp+8] ;s2
	mov ecx, [esp+16] ; len2
	
	repeta2:
        lodsb
        stosb
	loop repeta2
	
ret 4*5