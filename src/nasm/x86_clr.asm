;
; x86 surface clear routines for HERMES
; Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
; This source code is licensed under the GNU LGPL
; 
; Please refer to the file COPYING.LIB contained in the distribution for
; licensing conditions
;
; (04/10/99)	Modified ClearX86_8		<Mikko.Tiihonen@hut.fi>

BITS 32
	

GLOBAL _ClearX86_32
GLOBAL _ClearX86_24
GLOBAL _ClearX86_16
GLOBAL _ClearX86_8

SECTION .text use32

;;   
;; --------------------------------------------------------------------------
;; HermesClearInterface (ebp+..)
;;   0: char8 *dest
;;   4: int32 value
;;   8: unsigned int width (already checked to be >0!)
;;  12: unsigned int height (already checked to be >0!)
;;  16: int add

ALIGN 8
_ClearX86_32:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]
	
	mov edi,[ebp]		; destination
	mov eax,[ebp+4]		; pixel value	
	
	mov edx,[ebp+12]	; height
ALIGN 4	
.L_y
	mov ecx,[ebp+8]
	rep stosd

	add edi,[ebp+16]
	
	dec edx
	jnz .L_y

	pop ebp
	ret

	
		
_ClearX86_24:
	ret

	

ALIGN 8
_ClearX86_16:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]
	
	mov edi,[ebp]		; destination
	mov eax,[ebp+4]		; pixel value	
	
	mov edx,[ebp+12]	; height
	mov ebx,eax

	shl eax,16		; Duplicate pixel value
	and ebx,0ffffh
	
	or eax,ebx
.L_y
	mov ecx,[ebp+8]

	test edi,3		; Check if destination is aligned mod 4
	jz .L_aligned

	mov [edi],ax		; otherwise write one pixel
        add edi,BYTE 2
	
	dec ecx
	jz .L_endline

.L_aligned
	shr ecx,1
	
rep stosd

	jnc .L_endline

	mov [edi],ax
        add edi,BYTE 2

.L_endline
	add edi,[ebp+16]
	
	dec edx
	jnz .L_y

	pop ebp
	ret
	

	
ALIGN 8
_ClearX86_8:			
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov eax,[ebp+4]		; pixel value		
	mov edx,[ebp+12]	; height
	
	mov ah,al
	mov edi,[ebp]		; destination

	mov ecx,eax

	shl eax,16		; Put the byte pixel value in all four bytes
	and ecx,0ffffh		; of eax

	mov ebx,[ebp+8]
	or eax,ecx
	
	cmp ebx,5		; removes need for extra checks later
	jbe .L_short_y
	
ALIGN 4
.L_y
	test edi,3
	jz .L_aligned

	mov ecx,edi
	neg ecx
        and ecx,BYTE 3

	sub ebx,ecx

	rep stosb

.L_aligned	
	mov ecx,ebx

	shr ecx,2
	and ebx,BYTE 3

	rep stosd

	mov ecx,ebx
	rep stosb

	add edi,[ebp+16]
	
	dec edx
	mov ebx,[ebp+8]
	jnz .L_y

	pop ebp
	ret

;; Short loop
ALIGN 4
.L_short_y
	mov ecx,ebx
	
	rep stosb
	add edi,[ebp+16]
	
	dec edx
	jnz .L_short_y
	
	pop ebp
	ret

;; ClearX86_8 version 2,  
;; I'm not sure wheather this is faster or not... 
;; too many jumps could confuse the CPU branch quessing


ALIGN 8
_ClearX86_8_2:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov eax,[ebp+4]		; pixel value		
	mov edx,[ebp+12]	; height
	
	mov ah,al
	mov edi,[ebp]		; destination

	mov ecx,eax

	shl eax,16		; Put the byte pixel value in all four bytes
	and ecx,0ffffh		; of eax

	mov ebx,[ebp+8]
	or eax,ecx
	
	cmp ebx,5		; removes need for extra checks in main loop
	jbe .L_short_y


ALIGN 4
.L_y
	test edi,3
	jz .L_aligned

	mov ecx,edi
	neg ecx
	and ecx,BYTE 3

	mov [edi],al
	sub ebx,ecx

	inc edi	

	dec ecx
	jz .L_aligned

	mov [edi],al
	inc edi	
	dec ecx
	jz .L_aligned

	mov [edi],al
	inc edi	
	
.L_aligned	
	mov ecx,ebx

	shr ecx,2
	and ebx,BYTE 3

	rep stosd

	jz .L_endline
		; ebx

	mov [edi],al
		; Write remaining (1,2 or 3) pixels
	inc edi	
	dec ebx
	jz .L_endline

	mov [edi],al
	inc edi	
	dec ebx
	jz .L_endline

	mov [edi],al
	inc edi	
	dec ebx
	jz .L_endline

	mov [edi],al		
	inc edi

.L_endline
	add edi,[ebp+16]
	
	dec edx
	mov ebx,[ebp+8]
	jnz .L_y

	pop ebp
	ret

;; Short loop
ALIGN 4
.L_short_y
	mov ecx,ebx
	
	rep stosb
	add edi,[ebp+16]
	
	dec edx
	jnz .L_short_y
	
	pop ebp
	ret
