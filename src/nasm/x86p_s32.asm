
BITS 32

GLOBAL _ConvertX86p32_16RGB565_S

SECTION .text use32

EXTERN _x86return_S

;; _Convert*_S
;; Paramters:   
;;   ESI = source
;;   EDI = dest
;;   ECX = amount (NOT 0!!! (the _ConvertX86 routine checks for that though))
;;   EDX = x increment
;; Destroys:
;;   EAX, EBX, ECX, EDX


_ConvertX86p32_16RGB565_S:

	push ebp
	push edx		; increment now at [esp+4]!

	mov ebp,0

	push ecx
	shr ecx,1
	jnz .L_ok
	jmp .L_final

.L_ok:

ALIGN 8
.Lx:
	mov eax,ebp
	
	shr eax,14
	add ebp,[esp+4]

	mov edx,ebp
	and eax,0fffffffch	

	shr edx,14
	mov ebx,[esi+eax]	; ebx = pixel one
	
	and edx,0fffffffch	
	and ebx,0f8fcf8h

	shr bh,2
	mov eax,[esi+edx]	; eax = pixel two
	
	and eax,0f8fcf8h
	add ebp,[esp+4]
	
	shr ah,2		; eax & ebx= rrrrr000|00gggggg|bbbbb000

	mov edx,eax

	shr dx,3
	and eax,0f80000h

	shr eax,8
	
	or eax,edx

	shl eax,16
	mov edx,ebx

	shr dx,3
	and ebx,0f80000h

	shr ebx,8
	or ah,dh

	or ah,bh
	or al,dl

	mov [edi],eax
	add edi,4

	dec ecx
	jnz .Lx

.L_final:
	pop ecx
	and ecx,1
	jz .L_out

	shr ebp,14		; trailing pixel

	and ebp,0fffffffch
	
        mov eax,[esi+ebp]
        mov ebx,[esi+ebp]

        shr ebx,8
        and eax,0fcf8h

        shr ah,2
        and ebx,0f800h

        shr eax,3

        or eax,ebx

        mov [edi],ax
        add edi,2

.L_out:

	pop edx
	pop ebp
	jmp _x86return_S


