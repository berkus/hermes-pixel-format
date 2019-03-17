;
; MMX surface clear routines for HERMES
; Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
; This source code is licensed under the GNU LGPL
; 
; Please refer to the file COPYING.LIB contained in the distribution for
; licensing conditions
;

BITS 32
	

GLOBAL _ClearMMX_32
GLOBAL _ClearMMX_24
GLOBAL _ClearMMX_16
GLOBAL _ClearMMX_8

SECTION .text use32

;;
;; --------------------------------------------------------------------------
;; HermesClearInterface (ebp+..)
;;   0: char8 *dest
;;   4: int32 value
;;   8: unsigned int width (already checked to be >0!)
;;  12: unsigned int height (already checked to be >0!)
;;  16: int add


_ClearMMX_32:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov eax,[ebp+4]		; pixel value	
	movd mm0,[ebp+4]
	
	mov edx,[ebp+12]	; height
	movq mm1,mm0

	psllq mm0,32	
	mov edi,[ebp]		; destination

	por mm0,mm1
.L_y
	mov ecx,[ebp+8]
	
	mov ebx,ecx

	shr ecx,1
	jz .L_last

.L_x
	movq [edi],mm0
        add edi,BYTE 8

	dec ecx
	jnz .L_x
	
	
.L_last
	test ebx,1
	jz .L_endline
	
	mov [edi],eax
        add edi,BYTE 4

.L_endline

	add edi,[ebp+16]
	
	dec edx
	jnz .L_y

	emms 

	pop ebp
	ret

	
		
_ClearMMX_24:
	ret

	

_ClearMMX_16:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov eax,[ebp+4]		; pixel value	
	mov ebx,[ebp+4]
	
	mov edx,[ebp+12]	; height
	mov edi,[ebp]		; destination
	
	shl eax,16		; Duplicate pixel value
	and ebx,0ffffh

	or eax,ebx

	movd mm0,eax
	movd mm1,eax

	psllq mm0,32

	por mm0,mm1
.L_y
	mov ecx,[ebp+8]

	test edi,3		; Check if destination is aligned mod 4
	jz .L_aligned

	mov [edi],ax		; otherwise write one pixel
        add edi,BYTE 2
	
	dec ecx
	jz .L_endline

.L_aligned
	mov ebx,ecx
	shr ecx,2
	
	jz .L_last
		
.L_x
	movq [edi],mm0
        add edi,BYTE 8

	dec ecx
	jnz .L_x

.L_last
        and ebx,BYTE 3
	jz .L_endline

	mov [edi],ax		; Write trailing pixels
        add edi,BYTE 2
	dec ebx
	jz .L_endline

	mov [edi],ax
        add edi,BYTE 2
	dec ebx
	jz .L_endline

	mov [edi],ax
        add edi,BYTE 2
	dec ebx
	jnz .L_endline
	
.L_endline
	add edi,[ebp+16]
	
	dec edx
	jnz .L_y

	emms
	
	pop ebp
	ret
	

	
;; Clear8_x86 isn't optimised fully yet as it seems to be a tiny bit slower
;; than the C routine
_ClearMMX_8:			
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov eax,[ebp+4]		; pixel value		
	mov ebx,[ebp+4]
	
	mov edx,[ebp+12]	; height
	and ebx,0ffh		
	
	shl eax,8		; Put the byte pixel value in all four bytes
	mov edi,[ebp]		; destination

	mov al,bl
	mov bh,bl
	
	shl eax,16		
	
	mov ah,bh
	mov al,bl

	movd mm0,eax
	movd mm1,eax

	psllq mm0,32
	
	por mm0,mm1

.L_y
	mov ecx,[ebp+8]

	test edi,3		; Align mod 4
	jz .L_aligned

	mov ebx,edi

        and ebx,BYTE 3

	mov [edi],al		; Unrolled (copy & paste), align and jump
	inc edi			; if finished, faster than a loop...
	dec ecx
	jz .L_endline
	dec ebx	
	jz .L_aligned

	mov [edi],al		; Second pixel
	inc edi	
	dec ecx
	jz .L_endline
	dec ebx	
	jz .L_aligned

	mov [edi],al		; Third pixel
	inc edi	
	dec ecx
	jz .L_endline
	dec ebx	
	jz .L_aligned
	
.L_aligned	
	mov ebx,ecx		; Store ecx for later

	shr ecx,3		; We write 8 pixels at once
	jz .L_last

.L_x
	movq [edi],mm0
        add edi,BYTE 8

	dec ecx
	jnz .L_x
	
.L_last
	mov ecx,ebx		; Clean up trailing pixels

        and ecx,BYTE 7          ; Could be up to 7 left
	jz .L_endline

        test cl,100b            ; If there's less than four jump
	jz .L_lessthanfour

	mov [edi],eax		; Otherwise write a dword
        add edi,BYTE 4
	
        sub ecx,BYTE 4
	
.L_lessthanfour
	rep stosb		; Clean up the very rest

.L_endline
	add edi,[ebp+16]
	
	dec edx
	jnz .L_y

	emms
	
	pop ebp
	ret


