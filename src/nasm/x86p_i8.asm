;
; x86 format converters for HERMES
; Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
; This source code is licensed under the GNU LGPL
; 
; Please refer to the file COPYING.LIB contained in the distribution for
; licensing conditions		
; 
; Some routines are (c) Glenn Fiedler (ptc@gaffer.org), used with permission
;

BITS 32

GLOBAL _ConvertX86pI8_32
GLOBAL _ConvertX86pI8_24
GLOBAL _ConvertX86pI8_16

EXTERN _ConvertX86
EXTERN _x86return

SECTION .text use32


;; Convert_*
;; Paramters:	
;;   ESI = source 
;;   EDI = dest
;;   ECX = amount (NOT 0!!! (the ConvertX86 routine checks for that though))
;; Destroys:
;;   EAX, EBX, EDX

_ConvertX86pI8_32:	

        xor ebx,ebx
	mov edx,[ebp+36]
.L1:
	mov bl,[esi]
	inc esi
	
	mov eax,[edx+ebx*4]

	mov [edi],eax
        add edi,BYTE 4

	dec ecx
	jnz .L1

	jmp _x86return
	

	
_ConvertX86pI8_24:
	mov ebx,[ebp+36]	

	xor edx,edx

	; check short
        cmp ecx,BYTE 32
	ja .L3

	
.L1    ; short loop
	mov dl,[esi]
	mov eax,[ebx+edx*4]
	mov [edi+0],al  ; blue
	mov [edi+1],ah  ; green
	shr eax,16
	mov [edi+2],al  ; red
	inc esi
        add edi,BYTE 3
	dec ecx
	jnz .L1
.L2
	jmp _x86return
    
.L3 ; head
	mov eax,edi
        and eax,BYTE 11b
	jz .L4
	mov dl,[esi]
	mov eax,[ebx+edx*4]
	mov [edi+0],al  ; blue
	mov [edi+1],ah  ; green
	shr eax,16
	mov [edi+2],al  ; red
	inc esi
        add edi,BYTE 3
	dec ecx
        jmp SHORT .L3

.L4	; save ebp
	push ebp
	mov ebp,ebx

	; save count
	push ecx

	; unroll 4 times
	shr ecx,2

.L5     push ecx                        ; save ecx
        mov dl,[esi]                    ; index to "A"           

        mov eax,[ebp+edx*4]             ; eax = [xx][A2][A1][A0]
        shl eax,8                       ; eax = [A2][A1][A0][xx]

        mov dl,[esi+1]                  ; index to "B"

        mov al,[ebp+edx*4+0]            ; eax = [A2][A1][A0][B0]
        ror eax,8                       ; eax = [B0][A2][A1][A0] (done)
        mov [edi],eax

        mov eax,[ebp+edx*4]             ; eax = [xx][B2][B1][B0]
        shl eax,8                       ; eax = [B2][B1][B0][xx]

        mov dl,[esi+3]                  ; index to "D"

        mov ecx,[ebp+edx*4]             ; ecx = [xx][D2][D1][D0]
        shl ecx,8                       ; ecx = [D2][D1][D0][xx]

        mov dl,[esi+2]                  ; index to "C"

        mov ah,[ebp+edx*4+1]            ; eax = [B2][B1][C1][xx]
        mov al,[ebp+edx*4+0]            ; eax = [B2][B1][C1][C0]
        ror eax,16                      ; eax = [C1][C0][B2][B1] (done)
        
        mov cl,[ebp+edx*4+2]            ; ecx = [D2][D1][D0][C2] (done)

        mov [edi+4],eax        
        mov [edi+8],ecx
    
        add esi,BYTE 4
        add edi,BYTE 3*4

        pop ecx                         ; restore ecx
        
        dec ecx
        jnz .L5

	; tail
	pop ecx
        and ecx,BYTE 11b
	jz .L7

.L6	
	mov dl,[esi]
	mov eax,[ebx+edx*4]
	mov [edi+0],al  ; blue
	mov [edi+1],ah  ; green
	shr eax,16
	mov [edi+2],al  ; red
	inc esi
        add edi,BYTE 3
	dec ecx
	jnz .L6

.L7	pop ebp
	jmp _x86return

	
ALIGN 8	
_ConvertX86pI8_16:
        xor ebx,ebx
	mov edx,[ebp+36]

	test edi,3
	jz .Laligned

        mov bl,[esi]

        mov eax,[edx+ebx*4]
        inc esi

        mov [edi],ax
        add edi,BYTE 2   

	dec ecx
	jz .out

.Laligned
	push ecx

	xor eax,eax
	xor ebx,ebx

	shr ecx,1
	jz .last_pixel
ALIGN 8
.Ly:
	mov bl,[esi+1]
	mov al,[esi]

	mov ebx,[edx+ebx*4]
	add esi,BYTE 2

	shl ebx,16
	mov eax,[edx+eax*4]

	or eax,ebx
	xor ebx,ebx

	mov [edi],eax
	add edi,BYTE 4

	xor eax,eax
	dec ecx
	jnz .Ly

.last_pixel:
	pop ecx

	test cl,1
	jz .out

	mov bl,[esi]

        mov eax,[edx+ebx*4]
	inc esi

        mov [edi],ax
	add edi,BYTE 2

.out:
	jmp _x86return






