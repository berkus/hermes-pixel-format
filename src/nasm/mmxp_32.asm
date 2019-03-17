;
; MMX format converters for HERMES
; Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
; This source code is licensed under the GNU LGPL
; 
; Please refer to the file COPYING.LIB contained in the distribution for
; licensing conditions		
;
; COPYRIGHT NOTICE
; 
; This file partly contains code that is (c) Intel Corporation, specifically
; the mode detection routine, and the converter to 15 bit (8 pixel
; conversion routine from the mmx programming tutorial pages).
; 
	
BITS 32

	
GLOBAL _ConvertMMXp32_16RGB555

EXTERN _mmxreturn
 
SECTION .data use32
	
;ALIGN 8

;mmx32_rgb555_rb dd 00f800f8h,00f800f8h    ; Constants for conversion routines
;mmx32_rgb555_add dd 20000008h,20000008h
;mmx32_rgb555_g dd 0000f800h,0000f800h

		
			
SECTION .text use32

mmx32_rgb555_rb dd 00f800f8h,00f800f8h    ; Constants for conversion routines 
mmx32_rgb555_add dd 20000008h,20000008h
mmx32_rgb555_g dd 0000f800h,0000f800h

;; Gone for now, it didn't draw correctly AND was slower than the x86 routine 
_ConvertMMXp32_16RGB565:
	
	jmp _mmxreturn

	

	
_ConvertMMXp32_16RGB555:

	movq mm7,qword [mmx32_rgb555_add]
	movq mm6,qword [mmx32_rgb555_g]
        
	mov edx,ecx		           ; Save ecx 

        and ecx,BYTE 0fffffff8h            ; clear lower three bits
	jnz .L_OK
        jmp .L2 

.L_OK:
	
	movq mm2,[esi+8]

	movq mm0,[esi]
	movq mm3,mm2

	pand mm3,qword [mmx32_rgb555_rb]
	movq mm1,mm0

	pand mm1,qword [mmx32_rgb555_rb]
	pmaddwd mm3,mm7

	pmaddwd mm1,mm7
	pand mm2,mm6

.L1:
	movq mm4,[esi+24]
	pand mm0,mm6

	movq mm5,[esi+16]
	por mm3,mm2

	psrld mm3,6
	por mm1,mm0

	movq mm0,mm4
	psrld mm1,6

	pand mm0,qword [mmx32_rgb555_rb]
	packssdw mm1,mm3

	movq mm3,mm5
	pmaddwd mm0,mm7

	pand mm3,qword [mmx32_rgb555_rb]
	pand mm4,mm6

	movq [edi],mm1			
	pmaddwd mm3,mm7

        add esi,BYTE 32
	por mm4,mm0

	pand mm5,mm6
	psrld mm4,6

	movq mm2,[esi+8]
	por mm5,mm3

	movq mm0,[esi]
	psrld mm5,6

	movq mm3,mm2
	movq mm1,mm0

	pand mm3,qword [mmx32_rgb555_rb]
	packssdw mm5,mm4

	pand mm1,qword [mmx32_rgb555_rb]
	pand mm2,mm6

	movq [edi+8],mm5
	pmaddwd mm3,mm7

	pmaddwd mm1,mm7
        add edi,BYTE 16
	
        sub ecx,BYTE 8
	jz .L2
        jmp .L1


.L2:	
	mov ecx,edx
	
        and ecx,BYTE 7
	jz .L4
	
.L3:	
	mov ebx,[esi]
        add esi,BYTE 4
	
        mov eax,ebx
        mov edx,ebx

        shr eax,3
        shr edx,6

        and eax,BYTE 0000000000011111b
        and edx,     0000001111100000b

        shr ebx,9

        or eax,edx

        and ebx,     0111110000000000b

        or eax,ebx

        mov [edi],ax
        add edi,BYTE 2

	dec ecx
	jnz .L3	

.L4:		
	jmp _mmxreturn
