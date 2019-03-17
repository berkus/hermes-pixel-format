;
; x86 format converters for HERMES
; Some routines Copyright (c) 1998 Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
; This source code is licensed under the GNU LGPL
; 
; Please refer to the file COPYING.LIB contained in the distribution for
; licensing conditions		
;

BITS 32

GLOBAL _ConvertX86
GLOBAL _ConvertX86Stretch
GLOBAL _x86return
GLOBAL _x86return_S
	
GLOBAL _Hermes_X86_CPU


SECTION .data use32

cpu_flags dd 0

SECTION .text use32

s_pixels equ 0
s_width equ 4
s_height equ 8
s_add equ 12
d_pixels equ 16
d_width equ 20
d_height equ 24
d_add equ 28
conv_func equ 32
lookup equ 36
s_pitch equ 40
d_pitch equ 44
		
;; _ConvertX86:	 
;; [ESP+8] ConverterInfo*
;; --------------------------------------------------------------------------
;;
;; ConvertX86Stretch 'abuses' the following info structure fields:
;;	- d_pitch for the y increment
;;	- s_add for the x increment
;; because they're unused anyway and this is thread safe.. (it's a per
;; converter handle structure)
_ConvertX86Stretch:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov eax,[ebp+s_height]
	sal eax,16
	cdq
	idiv DWORD [ebp+d_height]
 	mov [ebp+d_pitch],eax

	mov eax,[ebp+s_width]
	sal eax,16
	cdq
	idiv DWORD [ebp+d_width]
	mov [ebp+s_add],eax

	mov [ebp+s_height],DWORD 0

	mov edi,[ebp+d_pixels]
	mov esi,[ebp+s_pixels]

	mov edx,[ebp+s_add]
	mov ecx,[ebp+d_width]
	jmp [ebp+conv_func]

ALIGN 8
_x86return_S:

	dec dword [ebp+d_height]
	jz endconvert_S

	mov eax,[ebp+s_height]
	add edi,[ebp+d_add]

	add eax,[ebp+d_pitch]

	mov ebx,eax

	shr eax,16
	
	mul dword [ebp+s_pitch]
	and ebx,0ffffh

	mov [ebp+s_height],ebx
	add esi,eax
	
	mov edx,[ebp+s_add]
        mov ecx,[ebp+d_width]
	
	jmp [ebp+conv_func]
		
endconvert_S:
		
	pop ebp
	ret



_ConvertX86:
	push ebp
	mov ebp,esp

	mov ebp,[ebp+8]

	mov esi,[ebp+s_pixels]
	mov ecx,[ebp+d_width]
	mov edi,[ebp+d_pixels]
	
	jmp [ebp+32]

ALIGN 8
_x86return:	
        dec dword [ebp+s_height]
        jz  endconvert

        mov ecx,[ebp+d_width]
        add esi,[ebp+s_add]
        add edi,[ebp+d_add]

        jmp [ebp+32]

	
endconvert:	
	pop ebp
	ret		



;; Hermes_X86_CPU returns the CPUID flags in eax
	
_Hermes_X86_CPU:
	pushfd
	pop eax
	
	mov ecx,eax
	
	xor eax,040000h
	push eax
	
	popfd
	pushfd

	pop eax
	xor eax,ecx
	jz .L1			; Processor is 386

	push ecx
	popfd

	mov eax,ecx
	xor eax,200000h

	push eax
	popfd
	pushfd

	pop eax
	xor eax,ecx
	je .L1
	
	pusha
	
	mov eax,1
	cpuid

	mov [cpu_flags],edx

	popa

	mov eax,[cpu_flags]

.L1:	
	ret
