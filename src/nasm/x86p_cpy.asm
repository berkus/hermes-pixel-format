

BITS 32


GLOBAL _CopyX86p_4byte
GLOBAL _CopyX86p_3byte
GLOBAL _CopyX86p_2byte
GLOBAL _CopyX86p_1byte

EXTERN _x86return

	
SECTION .text use32

;; _Copy*
;; Paramters:
;;   ESI = source 
;;   EDI = dest
;;   ECX = amount (NOT 0!!! (the _ConvertX86 routine checks for that though))
;; Destroys:
;;   EAX, EBX, EDX

_CopyX86p_4byte:

	rep movsd
	
	jmp _x86return
	

_CopyX86p_3byte:
	
	lea ecx, [ecx+ecx*2]
	jmp SHORT _CopyX86p_1byte


	
_CopyX86p_2byte:

	test edi,3			; Check if video memory is aligned
        jz .L_ALIGNED

        mov ax,[esi]
        add esi,BYTE 2
	
	mov [edi],ax
        add edi,BYTE 2
		
	dec ecx
	jz .L3
	
.L_ALIGNED
    
	mov ebx,ecx			; Save ecx for later

	shr ecx,1
	jz .L2

	rep movsd

.L2
        and ebx,BYTE 1
	jz .L3

	mov ax,[esi]
        add esi,BYTE 2
	
	mov [edi],ax
        add edi,BYTE 2
	
.L3
	jmp _x86return


	
_CopyX86p_1byte:

.L_alignloop
	test edi,3
	jz .L_aligned

	mov al,[esi]
	inc esi
	
	mov [edi],al
	inc edi

	dec ecx
	jz .L4
        jmp SHORT .L_alignloop
	
.L_aligned:	
	mov edx,ecx

	shr ecx,2
	jz .L2
	
	rep movsd

.L2:
	mov ecx,edx		; Get the remaining pixels to draw
	
        and ecx,BYTE 3
	jz .L4			; width was modulo 4
	
.L3:	
	mov al,[esi]
	inc esi
	
	mov [edi],al
	inc edi
		
	dec ecx
	jnz .L3
	
.L4:	
	jmp _x86return
