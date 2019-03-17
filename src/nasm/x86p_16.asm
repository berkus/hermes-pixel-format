;
; x86 format converters for HERMES
; Copyright (c) 1998 Glenn Fielder (gaffer@gaffer.org)
; This source code is licensed under the GNU LGPL
; 
; Please refer to the file COPYING.LIB contained in the distribution for
; licensing conditions		
; 
; Routines adjusted for Hermes by Christian Nentwich (c.nentwich@cs.ucl.ac.uk)
; Used with permission.
; 

	
BITS 32

GLOBAL _ConvertX86p16_32RGB888
GLOBAL _ConvertX86p16_32BGR888
GLOBAL _ConvertX86p16_32RGBA888
GLOBAL _ConvertX86p16_32BGRA888
GLOBAL _ConvertX86p16_24RGB888
GLOBAL _ConvertX86p16_24BGR888
GLOBAL _ConvertX86p16_16BGR565
GLOBAL _ConvertX86p16_16RGB555
GLOBAL _ConvertX86p16_16BGR555
GLOBAL _ConvertX86p16_8RGB332

EXTERN _ConvertX86
EXTERN _x86return

GLOBAL _ConvertX86p16_32RGB888_LUT_X86
GLOBAL _ConvertX86p16_32BGR888_LUT_X86
GLOBAL _ConvertX86p16_32RGBA888_LUT_X86
GLOBAL _ConvertX86p16_32BGRA888_LUT_X86


	
SECTION .text use32



_ConvertX86p16_32RGB888:

    ; check short
    cmp ecx,BYTE 32
    ja .L3


    ; short loop
    xor ebx,ebx
.L1 mov bl,[esi]                                        ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8]     ; eax = ARGB8888 of lower byte pixel 1
    mov bl,[esi+1]                                      ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8+4]   ; edx = ARGB8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4
    dec ecx
    jnz .L1
.L2
    jmp _x86return
	

.L3 ; save ebp
    push ebp

    ; save count
    push ecx

    ; unroll twice
    mov ebp,ecx
    shr ebp,1
    
    ; point arrays to end
    lea esi,[esi+ebp*4]
    lea edi,[edi+ebp*8]

    ; negative counter 
    neg ebp

    ; clear
    xor ebx,ebx
    xor ecx,ecx

    ; prestep
    mov cl,[esi+ebp*4+0]
    mov bl,[esi+ebp*4+1]

.L4     mov edx,[_ConvertX86p16_32RGB888_LUT_X86+ecx*8]
        mov cl,[esi+ebp*4+2]

        mov eax,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8+4]
        mov bl,[esi+ebp*4+3]

        add eax,edx
        mov edx,[_ConvertX86p16_32RGB888_LUT_X86+ecx*8]

        mov [edi+ebp*8],eax
        mov eax,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8+4]

        add eax,edx
        mov cl,[esi+ebp*4+4]

        mov [edi+ebp*8+4],eax
        mov bl,[esi+ebp*4+5]

        inc ebp
        jnz .L4

    ; tail
    pop ecx
    and ecx,BYTE 1
    jz .L6
    xor ebx,ebx
    mov bl,[esi]                                        ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8]     ; eax = ARGB8888 of lower byte pixel 1
    mov bl,[esi+1]                                      ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8+4]   ; edx = ARGB8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4

.L6 pop ebp
    jmp _x86return






_ConvertX86p16_32BGR888:

    ; check short
    cmp ecx,BYTE 32
    ja .L3


    ; short loop
    xor ebx,ebx
.L1 mov bl,[esi]                                        ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8]     ; eax = ABGR8888 of lower byte pixel 1
    mov bl,[esi+1]                                      ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8+4]   ; edx = ABGR8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 ; save ebp
    push ebp

    ; save count
    push ecx

    ; unroll twice
    mov ebp,ecx
    shr ebp,1
    
    ; point arrays to end
    lea esi,[esi+ebp*4]
    lea edi,[edi+ebp*8]

    ; negative counter 
    neg ebp

    ; clear
    xor ebx,ebx
    xor ecx,ecx

    ; prestep
    mov cl,[esi+ebp*4+0]
    mov bl,[esi+ebp*4+1]

.L4     mov edx,[_ConvertX86p16_32BGR888_LUT_X86+ecx*8]
        mov cl,[esi+ebp*4+2]

        mov eax,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8+4]
        mov bl,[esi+ebp*4+3]

        add eax,edx
        mov edx,[_ConvertX86p16_32BGR888_LUT_X86+ecx*8]

        mov [edi+ebp*8],eax
        mov eax,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8+4]

        add eax,edx
        mov cl,[esi+ebp*4+4]

        mov [edi+ebp*8+4],eax
        mov bl,[esi+ebp*4+5]

        inc ebp
        jnz .L4

    ; tail
    pop ecx
    and ecx,BYTE 1
    jz .L6
    xor ebx,ebx
    mov bl,[esi]                                        ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8]     ; eax = ABGR8888 of lower byte pixel 1
    mov bl,[esi+1]                                      ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8+4]   ; edx = ABGR8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4

.L6 pop ebp
    jmp _x86return






_ConvertX86p16_32RGBA888:

    ; check short
    cmp ecx,BYTE 32
    ja .L3


    ; short loop
    xor ebx,ebx
.L1 mov bl,[esi]                                         ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32RGBA888_LUT_X86+ebx*8]     ; eax = RGBA8888 of lower byte pixel 1
    mov bl,[esi+1]                                       ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32RGBA888_LUT_X86+ebx*8+4]   ; edx = RGBA8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 ; save ebp
    push ebp

    ; save count
    push ecx

    ; unroll twice
    mov ebp,ecx
    shr ebp,1
    
    ; point arrays to end
    lea esi,[esi+ebp*4]
    lea edi,[edi+ebp*8]

    ; negative counter 
    neg ebp

    ; clear
    xor ebx,ebx
    xor ecx,ecx

    ; prestep
    mov cl,[esi+ebp*4+0]
    mov bl,[esi+ebp*4+1]

.L4     mov edx,[_ConvertX86p16_32RGBA888_LUT_X86+ecx*8]
        mov cl,[esi+ebp*4+2]

        mov eax,[_ConvertX86p16_32RGBA888_LUT_X86+ebx*8+4]
        mov bl,[esi+ebp*4+3]

        add eax,edx
        mov edx,[_ConvertX86p16_32RGBA888_LUT_X86+ecx*8]

        mov [edi+ebp*8],eax
        mov eax,[_ConvertX86p16_32RGBA888_LUT_X86+ebx*8+4]

        add eax,edx
        mov cl,[esi+ebp*4+4]

        mov [edi+ebp*8+4],eax
        mov bl,[esi+ebp*4+5]

        inc ebp
        jnz .L4

    ; tail
    pop ecx
    and ecx,BYTE 1
    jz .L6
    xor ebx,ebx
    mov bl,[esi]                                         ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32RGBA888_LUT_X86+ebx*8]     ; eax = RGBA8888 of lower byte pixel 1
    mov bl,[esi+1]                                       ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32RGBA888_LUT_X86+ebx*8+4]   ; edx = RGBA8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4

.L6 pop ebp
    jmp _x86return






_ConvertX86p16_32BGRA888:

    ; check short
    cmp ecx,BYTE 32
    ja .L3

    ; short loop
    xor ebx,ebx
.L1 mov bl,[esi]                                         ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32BGRA888_LUT_X86+ebx*8]     ; eax = BGRA8888 of lower byte pixel 1
    mov bl,[esi+1]                                       ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32BGRA888_LUT_X86+ebx*8+4]   ; edx = BGRA8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 ; save ebp
    push ebp

    ; save count
    push ecx

    ; unroll twice
    mov ebp,ecx
    shr ebp,1
    
    ; point arrays to end
    lea esi,[esi+ebp*4]
    lea edi,[edi+ebp*8]

    ; negative counter 
    neg ebp

    ; clear
    xor ebx,ebx
    xor ecx,ecx

    ; prestep
    mov cl,[esi+ebp*4+0]
    mov bl,[esi+ebp*4+1]

.L4     mov edx,[_ConvertX86p16_32BGRA888_LUT_X86+ecx*8]
        mov cl,[esi+ebp*4+2]

        mov eax,[_ConvertX86p16_32BGRA888_LUT_X86+ebx*8+4]
        mov bl,[esi+ebp*4+3]

        add eax,edx
        mov edx,[_ConvertX86p16_32BGRA888_LUT_X86+ecx*8]

        mov [edi+ebp*8],eax
        mov eax,[_ConvertX86p16_32BGRA888_LUT_X86+ebx*8+4]

        add eax,edx
        mov cl,[esi+ebp*4+4]

        mov [edi+ebp*8+4],eax
        mov bl,[esi+ebp*4+5]

        inc ebp
        jnz .L4

    ; tail
    pop ecx
    and ecx,BYTE 1
    jz .L6
    xor ebx,ebx
    mov bl,[esi]                                         ; ebx = lower byte pixel 1
    mov eax,[_ConvertX86p16_32BGRA888_LUT_X86+ebx*8]     ; eax = BGRA8888 of lower byte pixel 1
    mov bl,[esi+1]                                       ; ebx = upper byte pixel 1
    mov edx,[_ConvertX86p16_32BGRA888_LUT_X86+ebx*8+4]   ; edx = BGRA8888 of upper byte pixel 1
    add eax,edx
    mov [edi],eax
    add esi,BYTE 2
    add edi,BYTE 4

.L6 pop ebp
    jmp _x86return






_ConvertX86p16_24RGB888:

    ; check short
    cmp ecx,BYTE 32
    ja .L3


    ; short loop
    xor edx,edx
.L1 mov dl,[esi]
    mov eax,[_ConvertX86p16_32RGB888_LUT_X86+edx*8]       ; eax = ARGB8888 of lower byte
    mov dl,[esi+1]
    mov ebx,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]     ; ebx = ARGB8888 of upper byte
    add eax,ebx                                           ; eax = ARGB8888 pixel
    mov [edi],al
    mov [edi+1],ah
    shr eax,16
    mov [edi+2],al
    add esi,BYTE 2
    add edi,BYTE 3
    dec ecx
    jnz .L1
.L2 jmp _x86return


.L3 ; clear edx
    xor edx,edx

.L4 ; head
    mov eax,edi
    and eax,BYTE 11b
    jz .L5
    mov dl,[esi]
    mov eax,[_ConvertX86p16_32RGB888_LUT_X86+edx*8]       ; eax = ARGB8888 of lower byte
    mov dl,[esi+1]
    mov ebx,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]     ; ebx = ARGB8888 of upper byte
    add eax,ebx                                           ; eax = ARGB8888 pixel
    mov [edi],al
    mov [edi+1],ah
    shr eax,16
    mov [edi+2],al
    add esi,BYTE 2
    add edi,BYTE 3
    dec ecx
    jmp SHORT .L4

.L5 ; unroll 4 times
    push ebp
    mov ebp,ecx
    shr ebp,2

    ; clear ebx
    xor ebx,ebx

    ; save count
    push ecx

    ; prestep
    mov bl,[esi+0]                                      ; ebx = lower byte pixel 1
    mov dl,[esi+1]                                      ; edx = upper byte pixel 1

.L6     mov eax,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8]         ; eax = ARGB8888 of lower byte pixel 1
        mov bl,[esi+2]                                      ; ebx = lower byte pixel 2

        mov ecx,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]       ; ecx = ARGB8888 of upper byte pixel 1
        mov dl,[esi+3]                                      ; edx = upper byte pixel 2
        
        push ebp                                            ; save ebp
        add eax,ecx                                         ; eax = ARGB8888 of pixel 1

        mov ebp,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8]         ; ebp = ARGB8888 of lower byte pixel 2
        mov ecx,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]       ; ecx = ARGB8888 of upper byte pixel 2

        mov bl,[esi+4]                                      ; ebx = lower byte pixel 3
        add ecx,ebp                                         ; ecx = ARGB8888 of pixel 2

        shl ebp,24                                          ; ebp = [b][0][0][0] of pixel 2
        mov dl,[esi+5]                                      ; edx = upper byte pixel 3

        shr ecx,8                                           ; ecx = [0][0][r][g] pixel 2
        add eax,ebp                                         ; eax = [b2][r1][g1][b1] (done)

        mov [edi],eax                                       ; store dword 1
        mov eax,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]       ; eax = ARGB8888 of upper byte pixel 3

        mov ebp,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8]         ; ebp = ARGB8888 of lower byte pixel 3
        mov bl,[esi+6]                                      ; ebx = lower byte pixel 4

        add ebp,eax                                         ; ebp = ARGB8888 of pixel 3
        mov dl,[esi+7]                                      ; edx = upper byte pixel 4

        shl ebp,16                                          ; ebp = [g][b][0][0] pixel 3

        shr eax,16                                          ;  al = red component of pixel 3
        add ebp,ecx                                         ; ebp = [g3][b3][r2][g2] (done)

        mov [edi+4],ebp                                     ; store dword 2
        mov ecx,[_ConvertX86p16_32RGB888_LUT_X86+ebx*8]         ; ebx = ARGB8888 of lower byte pixel 4

        mov ebp,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]       ; ebp = ARGB8888 of upper byte pixel 4
        mov bl,[esi+4*2+0]                                  ; ebx = lower byte pixel 1

        add ecx,ebp                                         ; ecx = ARGB8888 of pixel 4
        mov dl,[esi+4*2+1]                                  ; edx = upper byte pixel 1

        shl ecx,8                                           ; ecx = [r][g][b][0]
        pop ebp                                             ; restore ebp

        mov cl,al                                           ; ecx = [r4][g4][b4][r3] (done)
        add esi,BYTE 4*2

        mov [edi+8],ecx                                     ; store dword 3
        add edi,BYTE 3*4

        dec ebp
        jz .L7

        jmp .L6

.L7 ; check tail
    pop ecx
    and ecx,BYTE 11b
    jz .L9

.L8 ; tail
    mov dl,[esi]
    mov eax,[_ConvertX86p16_32RGB888_LUT_X86+edx*8]       ; eax = ARGB8888 of lower byte
    mov dl,[esi+1]
    mov ebx,[_ConvertX86p16_32RGB888_LUT_X86+edx*8+4]     ; ebx = ARGB8888 of upper byte
    add eax,ebx                                       ; eax = ARGB8888 pixel
    mov [edi],al
    mov [edi+1],ah
    shr eax,16
    mov [edi+2],al
    add esi,BYTE 2
    add edi,BYTE 3
    dec ecx
    jnz .L8

.L9 pop ebp
    jmp _x86return





_ConvertX86p16_24BGR888:

    ; check short
    cmp ecx,BYTE 32
    ja .L3


    ; short loop
    xor edx,edx
.L1 mov dl,[esi]
    mov eax,[_ConvertX86p16_32BGR888_LUT_X86+edx*8]       ; eax = ABGR8888 of lower byte
    mov dl,[esi+1]
    mov ebx,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]     ; ebx = ABGR8888 of upper byte
    add eax,ebx                                       ; eax = ABGR8888 pixel
    mov [edi],al
    mov [edi+1],ah
    shr eax,16
    mov [edi+2],al
    add esi,BYTE 2
    add edi,BYTE 3
    dec ecx
    jnz .L1
.L2 
    jmp _x86return


.L3 ; clear edx
    xor edx,edx

.L4 ; head
    mov eax,edi
    and eax,BYTE 11b
    jz .L5
    mov dl,[esi]
    mov eax,[_ConvertX86p16_32BGR888_LUT_X86+edx*8]       ; eax = ABGR8888 of lower byte
    mov dl,[esi+1]
    mov ebx,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]     ; ebx = ABGR8888 of upper byte
    add eax,ebx                                       ; eax = ABGR8888 pixel
    mov [edi],al
    mov [edi+1],ah
    shr eax,16
    mov [edi+2],al
    add esi,BYTE 2
    add edi,BYTE 3
    dec ecx
    jmp SHORT .L4

.L5 ; unroll 4 times
    push ebp
    mov ebp,ecx
    shr ebp,2

    ; clear ebx
    xor ebx,ebx

    ; save count
    push ecx

    ; prestep
    mov bl,[esi+0]                                      ; ebx = lower byte pixel 1
    mov dl,[esi+1]                                      ; edx = upper byte pixel 1

.L6     mov eax,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8]         ; eax = ABGR8888 of lower byte pixel 1
        mov bl,[esi+2]                                      ; ebx = lower byte pixel 2

        mov ecx,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]       ; ecx = ABGR8888 of upper byte pixel 1
        mov dl,[esi+3]                                      ; edx = upper byte pixel 2
        
        push ebp                                            ; save ebp
        add eax,ecx                                         ; eax = ABGR8888 of pixel 1

        mov ecx,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8]         ; ecx = ABGR8888 of lower byte pixel 2
        mov ebp,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]       ; ebp = ABGR8888 of upper byte pixel 2

        mov bl,[esi+4]                                      ; ebx = lower byte pixel 3
        add ecx,ebp                                         ; ecx = ABGR8888 of pixel 2

        shl ebp,24                                          ; ebp = [r][0][0][0] of pixel 2
        mov dl,[esi+5]                                      ; edx = upper byte pixel 3

        shr ecx,8                                           ; ecx = [0][0][b][g] pixel 2
        add eax,ebp                                         ; eax = [r2][b1][g1][r1] (done)

        mov [edi],eax                                       ; store dword 1
        mov ebp,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]       ; ebp = ABGR8888 of upper byte pixel 3

        mov eax,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8]         ; eax = ABGR8888 of lower byte pixel 3
        mov bl,[esi+6]                                      ; ebx = lower byte pixel 4

        add ebp,eax                                         ; ebp = ABGR8888 of pixel 3
        mov dl,[esi+7]                                      ; edx = upper byte pixel 4

        shl ebp,16                                          ; ebp = [g][r][0][0] pixel 3

        shr eax,16                                          ;  al = blue component of pixel 3
        add ebp,ecx                                         ; ebp = [g3][r3][b2][g2] (done)

        mov [edi+4],ebp                                     ; store dword 2
        mov ecx,[_ConvertX86p16_32BGR888_LUT_X86+ebx*8]         ; ebx = ABGR8888 of lower byte pixel 4

        mov ebp,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]       ; ebp = ABGR8888 of upper byte pixel 4
        mov bl,[esi+4*2+0]                                  ; ebx = lower byte pixel 1

        add ecx,ebp                                         ; ecx = ABGR8888 of pixel 4
        mov dl,[esi+4*2+1]                                  ; edx = upper byte pixel 1

        shl ecx,8                                           ; ecx = [b][g][r][0]
        pop ebp                                             ; restore ebp

        mov cl,al                                           ; ecx = [b4][g4][r4][b3] (done)
        add esi,BYTE 4*2

        mov [edi+8],ecx                                     ; store dword 3
        add edi,BYTE 3*4

        dec ebp
        jz .L7

        jmp .L6                                           

.L7 ; check tail
    pop ecx
    and ecx,BYTE 11b
    jz .L9

.L8 ; tail
    mov dl,[esi]
    mov eax,[_ConvertX86p16_32BGR888_LUT_X86+edx*8]       ; eax = ABGR8888 of lower byte
    mov dl,[esi+1]
    mov ebx,[_ConvertX86p16_32BGR888_LUT_X86+edx*8+4]     ; ebx = ABGR8888 of upper byte
    add eax,ebx                                       ; eax = ABGR8888 pixel
    mov [edi],al
    mov [edi+1],ah
    shr eax,16
    mov [edi+2],al
    add esi,BYTE 2
    add edi,BYTE 3
    dec ecx
    jnz .L8

.L9 pop ebp
    jmp _x86return



	
_ConvertX86p16_16BGR565:

    ; check short
    cmp ecx,BYTE 16
    ja .L3


.L1 ; short loop
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    shr eax,11
    and eax,BYTE 11111b
    and ebx,11111100000b
    shl edx,11
    add eax,ebx
    add eax,edx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 ; head
    mov eax,edi
    and eax,BYTE 11b
    jz .L4
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    shr eax,11
    and eax,BYTE 11111b
    and ebx,11111100000b
    shl edx,11
    add eax,ebx
    add eax,edx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx

.L4 ; save count
    push ecx

    ; unroll twice
    shr ecx,1
    
    ; point arrays to end
    lea esi,[esi+ecx*4]
    lea edi,[edi+ecx*4]

    ; negative counter 
    neg ecx
    jmp SHORT .L6
                              
.L5     mov [edi+ecx*4-4],eax
.L6     mov eax,[esi+ecx*4]

        mov ebx,[esi+ecx*4]
        and eax,07E007E0h         

        mov edx,[esi+ecx*4]
        and ebx,0F800F800h

        shr ebx,11
        and edx,001F001Fh

        shl edx,11
        add eax,ebx

        add eax,edx                 
        inc ecx

        jnz .L5                 
         
    mov [edi+ecx*4-4],eax

    ; tail
    pop ecx
    and ecx,BYTE 1
    jz .L7
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    shr eax,11
    and eax,BYTE 11111b
    and ebx,11111100000b
    shl edx,11
    add eax,ebx
    add eax,edx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2

.L7
    jmp _x86return






_ConvertX86p16_16RGB555:

    ; check short
    cmp ecx,BYTE 32
    ja .L3


.L1 ; short loop
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    shr ebx,1
    and ebx,     0111111111100000b
    and eax,BYTE 0000000000011111b
    add eax,ebx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 ; head
    mov eax,edi
    and eax,BYTE 11b
    jz .L4
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    shr ebx,1
    and ebx,     0111111111100000b
    and eax,BYTE 0000000000011111b
    add eax,ebx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx

.L4 ; save ebp
    push ebp

    ; save count
    push ecx

    ; unroll four times
    shr ecx,2
    
    ; point arrays to end
    lea esi,[esi+ecx*8]
    lea edi,[edi+ecx*8]

    ; negative counter 
    xor ebp,ebp
    sub ebp,ecx

.L5     mov eax,[esi+ebp*8]        ; agi?
        mov ecx,[esi+ebp*8+4]
       
        mov ebx,eax
        mov edx,ecx

        and eax,0FFC0FFC0h
        and ecx,0FFC0FFC0h

        shr eax,1
        and ebx,001F001Fh

        shr ecx,1
        and edx,001F001Fh

        add eax,ebx
        add ecx,edx

        mov [edi+ebp*8],eax
        mov [edi+ebp*8+4],ecx

        inc ebp
        jnz .L5                 

    ; tail
    pop ecx
.L6 and ecx,BYTE 11b
    jz .L7
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    shr ebx,1
    and ebx,     0111111111100000b
    and eax,BYTE 0000000000011111b
    add eax,ebx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx
    jmp SHORT .L6

.L7 pop ebp
    jmp _x86return






_ConvertX86p16_16BGR555:

    ; check short
    cmp ecx,BYTE 16
    ja .L3

	
.L1 ; short loop
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    shr eax,11
    and eax,BYTE 11111b
    shr ebx,1
    and ebx,1111100000b
    shl edx,10
    and edx,0111110000000000b
    add eax,ebx
    add eax,edx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 ; head
    mov eax,edi
    and eax,BYTE 11b
    jz .L4
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    shr eax,11
    and eax,BYTE 11111b
    shr ebx,1
    and ebx,1111100000b
    shl edx,10
    and edx,0111110000000000b
    add eax,ebx
    add eax,edx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2
    dec ecx

.L4 ; save count
    push ecx

    ; unroll twice
    shr ecx,1
    
    ; point arrays to end
    lea esi,[esi+ecx*4]
    lea edi,[edi+ecx*4]

    ; negative counter 
    neg ecx
    jmp SHORT .L6
                              
.L5     mov [edi+ecx*4-4],eax
.L6     mov eax,[esi+ecx*4]

        shr eax,1
        mov ebx,[esi+ecx*4]
        
        and eax,03E003E0h         
        mov edx,[esi+ecx*4]

        and ebx,0F800F800h

        shr ebx,11
        and edx,001F001Fh

        shl edx,10
        add eax,ebx

        add eax,edx                 
        inc ecx

        jnz .L5                 
         
    mov [edi+ecx*4-4],eax

    ; tail
    pop ecx
    and ecx,BYTE 1
    jz .L7
    mov al,[esi]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    shr eax,11
    and eax,BYTE 11111b
    shr ebx,1
    and ebx,1111100000b
    shl edx,10
    and edx,0111110000000000b
    add eax,ebx
    add eax,edx
    mov [edi],al
    mov [edi+1],ah
    add esi,BYTE 2
    add edi,BYTE 2

.L7
    jmp _x86return






_ConvertX86p16_8RGB332:

    ; check short
    cmp ecx,BYTE 16
    ja .L3


.L1 ; short loop
    mov al,[esi+0]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    and eax,BYTE 11000b         ; blue
    shr eax,3
    and ebx,11100000000b        ; green
    shr ebx,6
    and edx,1110000000000000b   ; red
    shr edx,8
    add eax,ebx
    add eax,edx
    mov [edi],al
    add esi,BYTE 2
    inc edi
    dec ecx
    jnz .L1
.L2
    jmp _x86return

.L3 mov eax,edi
    and eax,BYTE 11b
    jz .L4
    mov al,[esi+0]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    and eax,BYTE 11000b         ; blue
    shr eax,3
    and ebx,11100000000b        ; green
    shr ebx,6
    and edx,1110000000000000b   ; red
    shr edx,8
    add eax,ebx
    add eax,edx
    mov [edi],al
    add esi,BYTE 2
    inc edi
    dec ecx
    jmp SHORT .L3

.L4 ; save ebp
    push ebp

    ; save count
    push ecx

    ; unroll 4 times
    shr ecx,2

    ; prestep
    mov dl,[esi+0]
    mov bl,[esi+1]
    mov dh,[esi+2]
        
.L5     shl edx,16
        mov bh,[esi+3]
        
        shl ebx,16
        mov dl,[esi+4]

        mov dh,[esi+6]
        mov bl,[esi+5]

        and edx,00011000000110000001100000011000b
        mov bh,[esi+7]

        ror edx,16+3
        mov eax,ebx                                     ; setup eax for reds

        and ebx,00000111000001110000011100000111b
        and eax,11100000111000001110000011100000b       ; reds

        ror ebx,16-2
        add esi,BYTE 8

        ror eax,16
        add edi,BYTE 4

        add eax,ebx
        mov bl,[esi+1]                                  ; greens

        add eax,edx
        mov dl,[esi+0]                                  ; blues

        mov [edi-4],eax
        mov dh,[esi+2]

        dec ecx
        jnz .L5                 
    
    ; check tail
    pop ecx
    and ecx,BYTE 11b
    jz .L7

.L6 ; tail
    mov al,[esi+0]
    mov ah,[esi+1]
    mov ebx,eax
    mov edx,eax
    and eax,BYTE 11000b         ; blue
    shr eax,3
    and ebx,11100000000b        ; green
    shr ebx,6
    and edx,1110000000000000b   ; red
    shr edx,8
    add eax,ebx
    add eax,edx
    mov [edi],al
    add esi,BYTE 2
    inc edi
    dec ecx
    jnz .L6

.L7 pop ebp
    jmp _x86return


SECTION .data use32

_ConvertX86p16_32RGB888_LUT_X86:
		DD 0x00000000
		DD 0x00000000
		DD 0x00000008
		DD 0x00002000
		DD 0x00000010
		DD 0x00004000
		DD 0x00000018
		DD 0x00006100
		DD 0x00000020
		DD 0x00008100
		DD 0x00000029
		DD 0x0000a100
		DD 0x00000031
		DD 0x0000c200
		DD 0x00000039
		DD 0x0000e200
		DD 0x00000041
		DD 0x00080000
		DD 0x0000004a
		DD 0x00082000
		DD 0x00000052
		DD 0x00084000
		DD 0x0000005a
		DD 0x00086100
		DD 0x00000062
		DD 0x00088100
		DD 0x0000006a
		DD 0x0008a100
		DD 0x00000073
		DD 0x0008c200
		DD 0x0000007b
		DD 0x0008e200
		DD 0x00000083
		DD 0x00100000
		DD 0x0000008b
		DD 0x00102000
		DD 0x00000094
		DD 0x00104000
		DD 0x0000009c
		DD 0x00106100
		DD 0x000000a4
		DD 0x00108100
		DD 0x000000ac
		DD 0x0010a100
		DD 0x000000b4
		DD 0x0010c200
		DD 0x000000bd
		DD 0x0010e200
		DD 0x000000c5
		DD 0x00180000
		DD 0x000000cd
		DD 0x00182000
		DD 0x000000d5
		DD 0x00184000
		DD 0x000000de
		DD 0x00186100
		DD 0x000000e6
		DD 0x00188100
		DD 0x000000ee
		DD 0x0018a100
		DD 0x000000f6
		DD 0x0018c200
		DD 0x000000ff
		DD 0x0018e200
		DD 0x00000400
		DD 0x00200000
		DD 0x00000408
		DD 0x00202000
		DD 0x00000410
		DD 0x00204000
		DD 0x00000418
		DD 0x00206100
		DD 0x00000420
		DD 0x00208100
		DD 0x00000429
		DD 0x0020a100
		DD 0x00000431
		DD 0x0020c200
		DD 0x00000439
		DD 0x0020e200
		DD 0x00000441
		DD 0x00290000
		DD 0x0000044a
		DD 0x00292000
		DD 0x00000452
		DD 0x00294000
		DD 0x0000045a
		DD 0x00296100
		DD 0x00000462
		DD 0x00298100
		DD 0x0000046a
		DD 0x0029a100
		DD 0x00000473
		DD 0x0029c200
		DD 0x0000047b
		DD 0x0029e200
		DD 0x00000483
		DD 0x00310000
		DD 0x0000048b
		DD 0x00312000
		DD 0x00000494
		DD 0x00314000
		DD 0x0000049c
		DD 0x00316100
		DD 0x000004a4
		DD 0x00318100
		DD 0x000004ac
		DD 0x0031a100
		DD 0x000004b4
		DD 0x0031c200
		DD 0x000004bd
		DD 0x0031e200
		DD 0x000004c5
		DD 0x00390000
		DD 0x000004cd
		DD 0x00392000
		DD 0x000004d5
		DD 0x00394000
		DD 0x000004de
		DD 0x00396100
		DD 0x000004e6
		DD 0x00398100
		DD 0x000004ee
		DD 0x0039a100
		DD 0x000004f6
		DD 0x0039c200
		DD 0x000004ff
		DD 0x0039e200
		DD 0x00000800
		DD 0x00410000
		DD 0x00000808
		DD 0x00412000
		DD 0x00000810
		DD 0x00414000
		DD 0x00000818
		DD 0x00416100
		DD 0x00000820
		DD 0x00418100
		DD 0x00000829
		DD 0x0041a100
		DD 0x00000831
		DD 0x0041c200
		DD 0x00000839
		DD 0x0041e200
		DD 0x00000841
		DD 0x004a0000
		DD 0x0000084a
		DD 0x004a2000
		DD 0x00000852
		DD 0x004a4000
		DD 0x0000085a
		DD 0x004a6100
		DD 0x00000862
		DD 0x004a8100
		DD 0x0000086a
		DD 0x004aa100
		DD 0x00000873
		DD 0x004ac200
		DD 0x0000087b
		DD 0x004ae200
		DD 0x00000883
		DD 0x00520000
		DD 0x0000088b
		DD 0x00522000
		DD 0x00000894
		DD 0x00524000
		DD 0x0000089c
		DD 0x00526100
		DD 0x000008a4
		DD 0x00528100
		DD 0x000008ac
		DD 0x0052a100
		DD 0x000008b4
		DD 0x0052c200
		DD 0x000008bd
		DD 0x0052e200
		DD 0x000008c5
		DD 0x005a0000
		DD 0x000008cd
		DD 0x005a2000
		DD 0x000008d5
		DD 0x005a4000
		DD 0x000008de
		DD 0x005a6100
		DD 0x000008e6
		DD 0x005a8100
		DD 0x000008ee
		DD 0x005aa100
		DD 0x000008f6
		DD 0x005ac200
		DD 0x000008ff
		DD 0x005ae200
		DD 0x00000c00
		DD 0x00620000
		DD 0x00000c08
		DD 0x00622000
		DD 0x00000c10
		DD 0x00624000
		DD 0x00000c18
		DD 0x00626100
		DD 0x00000c20
		DD 0x00628100
		DD 0x00000c29
		DD 0x0062a100
		DD 0x00000c31
		DD 0x0062c200
		DD 0x00000c39
		DD 0x0062e200
		DD 0x00000c41
		DD 0x006a0000
		DD 0x00000c4a
		DD 0x006a2000
		DD 0x00000c52
		DD 0x006a4000
		DD 0x00000c5a
		DD 0x006a6100
		DD 0x00000c62
		DD 0x006a8100
		DD 0x00000c6a
		DD 0x006aa100
		DD 0x00000c73
		DD 0x006ac200
		DD 0x00000c7b
		DD 0x006ae200
		DD 0x00000c83
		DD 0x00730000
		DD 0x00000c8b
		DD 0x00732000
		DD 0x00000c94
		DD 0x00734000
		DD 0x00000c9c
		DD 0x00736100
		DD 0x00000ca4
		DD 0x00738100
		DD 0x00000cac
		DD 0x0073a100
		DD 0x00000cb4
		DD 0x0073c200
		DD 0x00000cbd
		DD 0x0073e200
		DD 0x00000cc5
		DD 0x007b0000
		DD 0x00000ccd
		DD 0x007b2000
		DD 0x00000cd5
		DD 0x007b4000
		DD 0x00000cde
		DD 0x007b6100
		DD 0x00000ce6
		DD 0x007b8100
		DD 0x00000cee
		DD 0x007ba100
		DD 0x00000cf6
		DD 0x007bc200
		DD 0x00000cff
		DD 0x007be200
		DD 0x00001000
		DD 0x00830000
		DD 0x00001008
		DD 0x00832000
		DD 0x00001010
		DD 0x00834000
		DD 0x00001018
		DD 0x00836100
		DD 0x00001020
		DD 0x00838100
		DD 0x00001029
		DD 0x0083a100
		DD 0x00001031
		DD 0x0083c200
		DD 0x00001039
		DD 0x0083e200
		DD 0x00001041
		DD 0x008b0000
		DD 0x0000104a
		DD 0x008b2000
		DD 0x00001052
		DD 0x008b4000
		DD 0x0000105a
		DD 0x008b6100
		DD 0x00001062
		DD 0x008b8100
		DD 0x0000106a
		DD 0x008ba100
		DD 0x00001073
		DD 0x008bc200
		DD 0x0000107b
		DD 0x008be200
		DD 0x00001083
		DD 0x00940000
		DD 0x0000108b
		DD 0x00942000
		DD 0x00001094
		DD 0x00944000
		DD 0x0000109c
		DD 0x00946100
		DD 0x000010a4
		DD 0x00948100
		DD 0x000010ac
		DD 0x0094a100
		DD 0x000010b4
		DD 0x0094c200
		DD 0x000010bd
		DD 0x0094e200
		DD 0x000010c5
		DD 0x009c0000
		DD 0x000010cd
		DD 0x009c2000
		DD 0x000010d5
		DD 0x009c4000
		DD 0x000010de
		DD 0x009c6100
		DD 0x000010e6
		DD 0x009c8100
		DD 0x000010ee
		DD 0x009ca100
		DD 0x000010f6
		DD 0x009cc200
		DD 0x000010ff
		DD 0x009ce200
		DD 0x00001400
		DD 0x00a40000
		DD 0x00001408
		DD 0x00a42000
		DD 0x00001410
		DD 0x00a44000
		DD 0x00001418
		DD 0x00a46100
		DD 0x00001420
		DD 0x00a48100
		DD 0x00001429
		DD 0x00a4a100
		DD 0x00001431
		DD 0x00a4c200
		DD 0x00001439
		DD 0x00a4e200
		DD 0x00001441
		DD 0x00ac0000
		DD 0x0000144a
		DD 0x00ac2000
		DD 0x00001452
		DD 0x00ac4000
		DD 0x0000145a
		DD 0x00ac6100
		DD 0x00001462
		DD 0x00ac8100
		DD 0x0000146a
		DD 0x00aca100
		DD 0x00001473
		DD 0x00acc200
		DD 0x0000147b
		DD 0x00ace200
		DD 0x00001483
		DD 0x00b40000
		DD 0x0000148b
		DD 0x00b42000
		DD 0x00001494
		DD 0x00b44000
		DD 0x0000149c
		DD 0x00b46100
		DD 0x000014a4
		DD 0x00b48100
		DD 0x000014ac
		DD 0x00b4a100
		DD 0x000014b4
		DD 0x00b4c200
		DD 0x000014bd
		DD 0x00b4e200
		DD 0x000014c5
		DD 0x00bd0000
		DD 0x000014cd
		DD 0x00bd2000
		DD 0x000014d5
		DD 0x00bd4000
		DD 0x000014de
		DD 0x00bd6100
		DD 0x000014e6
		DD 0x00bd8100
		DD 0x000014ee
		DD 0x00bda100
		DD 0x000014f6
		DD 0x00bdc200
		DD 0x000014ff
		DD 0x00bde200
		DD 0x00001800
		DD 0x00c50000
		DD 0x00001808
		DD 0x00c52000
		DD 0x00001810
		DD 0x00c54000
		DD 0x00001818
		DD 0x00c56100
		DD 0x00001820
		DD 0x00c58100
		DD 0x00001829
		DD 0x00c5a100
		DD 0x00001831
		DD 0x00c5c200
		DD 0x00001839
		DD 0x00c5e200
		DD 0x00001841
		DD 0x00cd0000
		DD 0x0000184a
		DD 0x00cd2000
		DD 0x00001852
		DD 0x00cd4000
		DD 0x0000185a
		DD 0x00cd6100
		DD 0x00001862
		DD 0x00cd8100
		DD 0x0000186a
		DD 0x00cda100
		DD 0x00001873
		DD 0x00cdc200
		DD 0x0000187b
		DD 0x00cde200
		DD 0x00001883
		DD 0x00d50000
		DD 0x0000188b
		DD 0x00d52000
		DD 0x00001894
		DD 0x00d54000
		DD 0x0000189c
		DD 0x00d56100
		DD 0x000018a4
		DD 0x00d58100
		DD 0x000018ac
		DD 0x00d5a100
		DD 0x000018b4
		DD 0x00d5c200
		DD 0x000018bd
		DD 0x00d5e200
		DD 0x000018c5
		DD 0x00de0000
		DD 0x000018cd
		DD 0x00de2000
		DD 0x000018d5
		DD 0x00de4000
		DD 0x000018de
		DD 0x00de6100
		DD 0x000018e6
		DD 0x00de8100
		DD 0x000018ee
		DD 0x00dea100
		DD 0x000018f6
		DD 0x00dec200
		DD 0x000018ff
		DD 0x00dee200
		DD 0x00001c00
		DD 0x00e60000
		DD 0x00001c08
		DD 0x00e62000
		DD 0x00001c10
		DD 0x00e64000
		DD 0x00001c18
		DD 0x00e66100
		DD 0x00001c20
		DD 0x00e68100
		DD 0x00001c29
		DD 0x00e6a100
		DD 0x00001c31
		DD 0x00e6c200
		DD 0x00001c39
		DD 0x00e6e200
		DD 0x00001c41
		DD 0x00ee0000
		DD 0x00001c4a
		DD 0x00ee2000
		DD 0x00001c52
		DD 0x00ee4000
		DD 0x00001c5a
		DD 0x00ee6100
		DD 0x00001c62
		DD 0x00ee8100
		DD 0x00001c6a
		DD 0x00eea100
		DD 0x00001c73
		DD 0x00eec200
		DD 0x00001c7b
		DD 0x00eee200
		DD 0x00001c83
		DD 0x00f60000
		DD 0x00001c8b
		DD 0x00f62000
		DD 0x00001c94
		DD 0x00f64000
		DD 0x00001c9c
		DD 0x00f66100
		DD 0x00001ca4
		DD 0x00f68100
		DD 0x00001cac
		DD 0x00f6a100
		DD 0x00001cb4
		DD 0x00f6c200
		DD 0x00001cbd
		DD 0x00f6e200
		DD 0x00001cc5
		DD 0x00ff0000
		DD 0x00001ccd
		DD 0x00ff2000
		DD 0x00001cd5
		DD 0x00ff4000
		DD 0x00001cde
		DD 0x00ff6100
		DD 0x00001ce6
		DD 0x00ff8100
		DD 0x00001cee
		DD 0x00ffa100
		DD 0x00001cf6
		DD 0x00ffc200
		DD 0x00001cff
		DD 0x00ffe200

_ConvertX86p16_32BGR888_LUT_X86:
		DD 0x00000000
		DD 0x00000000
		DD 0x00080000
		DD 0x00002000
		DD 0x00100000
		DD 0x00004000
		DD 0x00180000
		DD 0x00006100
		DD 0x00200000
		DD 0x00008100
		DD 0x00290000
		DD 0x0000a100
		DD 0x00310000
		DD 0x0000c200
		DD 0x00390000
		DD 0x0000e200
		DD 0x00410000
		DD 0x00000008
		DD 0x004a0000
		DD 0x00002008
		DD 0x00520000
		DD 0x00004008
		DD 0x005a0000
		DD 0x00006108
		DD 0x00620000
		DD 0x00008108
		DD 0x006a0000
		DD 0x0000a108
		DD 0x00730000
		DD 0x0000c208
		DD 0x007b0000
		DD 0x0000e208
		DD 0x00830000
		DD 0x00000010
		DD 0x008b0000
		DD 0x00002010
		DD 0x00940000
		DD 0x00004010
		DD 0x009c0000
		DD 0x00006110
		DD 0x00a40000
		DD 0x00008110
		DD 0x00ac0000
		DD 0x0000a110
		DD 0x00b40000
		DD 0x0000c210
		DD 0x00bd0000
		DD 0x0000e210
		DD 0x00c50000
		DD 0x00000018
		DD 0x00cd0000
		DD 0x00002018
		DD 0x00d50000
		DD 0x00004018
		DD 0x00de0000
		DD 0x00006118
		DD 0x00e60000
		DD 0x00008118
		DD 0x00ee0000
		DD 0x0000a118
		DD 0x00f60000
		DD 0x0000c218
		DD 0x00ff0000
		DD 0x0000e218
		DD 0x00000400
		DD 0x00000020
		DD 0x00080400
		DD 0x00002020
		DD 0x00100400
		DD 0x00004020
		DD 0x00180400
		DD 0x00006120
		DD 0x00200400
		DD 0x00008120
		DD 0x00290400
		DD 0x0000a120
		DD 0x00310400
		DD 0x0000c220
		DD 0x00390400
		DD 0x0000e220
		DD 0x00410400
		DD 0x00000029
		DD 0x004a0400
		DD 0x00002029
		DD 0x00520400
		DD 0x00004029
		DD 0x005a0400
		DD 0x00006129
		DD 0x00620400
		DD 0x00008129
		DD 0x006a0400
		DD 0x0000a129
		DD 0x00730400
		DD 0x0000c229
		DD 0x007b0400
		DD 0x0000e229
		DD 0x00830400
		DD 0x00000031
		DD 0x008b0400
		DD 0x00002031
		DD 0x00940400
		DD 0x00004031
		DD 0x009c0400
		DD 0x00006131
		DD 0x00a40400
		DD 0x00008131
		DD 0x00ac0400
		DD 0x0000a131
		DD 0x00b40400
		DD 0x0000c231
		DD 0x00bd0400
		DD 0x0000e231
		DD 0x00c50400
		DD 0x00000039
		DD 0x00cd0400
		DD 0x00002039
		DD 0x00d50400
		DD 0x00004039
		DD 0x00de0400
		DD 0x00006139
		DD 0x00e60400
		DD 0x00008139
		DD 0x00ee0400
		DD 0x0000a139
		DD 0x00f60400
		DD 0x0000c239
		DD 0x00ff0400
		DD 0x0000e239
		DD 0x00000800
		DD 0x00000041
		DD 0x00080800
		DD 0x00002041
		DD 0x00100800
		DD 0x00004041
		DD 0x00180800
		DD 0x00006141
		DD 0x00200800
		DD 0x00008141
		DD 0x00290800
		DD 0x0000a141
		DD 0x00310800
		DD 0x0000c241
		DD 0x00390800
		DD 0x0000e241
		DD 0x00410800
		DD 0x0000004a
		DD 0x004a0800
		DD 0x0000204a
		DD 0x00520800
		DD 0x0000404a
		DD 0x005a0800
		DD 0x0000614a
		DD 0x00620800
		DD 0x0000814a
		DD 0x006a0800
		DD 0x0000a14a
		DD 0x00730800
		DD 0x0000c24a
		DD 0x007b0800
		DD 0x0000e24a
		DD 0x00830800
		DD 0x00000052
		DD 0x008b0800
		DD 0x00002052
		DD 0x00940800
		DD 0x00004052
		DD 0x009c0800
		DD 0x00006152
		DD 0x00a40800
		DD 0x00008152
		DD 0x00ac0800
		DD 0x0000a152
		DD 0x00b40800
		DD 0x0000c252
		DD 0x00bd0800
		DD 0x0000e252
		DD 0x00c50800
		DD 0x0000005a
		DD 0x00cd0800
		DD 0x0000205a
		DD 0x00d50800
		DD 0x0000405a
		DD 0x00de0800
		DD 0x0000615a
		DD 0x00e60800
		DD 0x0000815a
		DD 0x00ee0800
		DD 0x0000a15a
		DD 0x00f60800
		DD 0x0000c25a
		DD 0x00ff0800
		DD 0x0000e25a
		DD 0x00000c00
		DD 0x00000062
		DD 0x00080c00
		DD 0x00002062
		DD 0x00100c00
		DD 0x00004062
		DD 0x00180c00
		DD 0x00006162
		DD 0x00200c00
		DD 0x00008162
		DD 0x00290c00
		DD 0x0000a162
		DD 0x00310c00
		DD 0x0000c262
		DD 0x00390c00
		DD 0x0000e262
		DD 0x00410c00
		DD 0x0000006a
		DD 0x004a0c00
		DD 0x0000206a
		DD 0x00520c00
		DD 0x0000406a
		DD 0x005a0c00
		DD 0x0000616a
		DD 0x00620c00
		DD 0x0000816a
		DD 0x006a0c00
		DD 0x0000a16a
		DD 0x00730c00
		DD 0x0000c26a
		DD 0x007b0c00
		DD 0x0000e26a
		DD 0x00830c00
		DD 0x00000073
		DD 0x008b0c00
		DD 0x00002073
		DD 0x00940c00
		DD 0x00004073
		DD 0x009c0c00
		DD 0x00006173
		DD 0x00a40c00
		DD 0x00008173
		DD 0x00ac0c00
		DD 0x0000a173
		DD 0x00b40c00
		DD 0x0000c273
		DD 0x00bd0c00
		DD 0x0000e273
		DD 0x00c50c00
		DD 0x0000007b
		DD 0x00cd0c00
		DD 0x0000207b
		DD 0x00d50c00
		DD 0x0000407b
		DD 0x00de0c00
		DD 0x0000617b
		DD 0x00e60c00
		DD 0x0000817b
		DD 0x00ee0c00
		DD 0x0000a17b
		DD 0x00f60c00
		DD 0x0000c27b
		DD 0x00ff0c00
		DD 0x0000e27b
		DD 0x00001000
		DD 0x00000083
		DD 0x00081000
		DD 0x00002083
		DD 0x00101000
		DD 0x00004083
		DD 0x00181000
		DD 0x00006183
		DD 0x00201000
		DD 0x00008183
		DD 0x00291000
		DD 0x0000a183
		DD 0x00311000
		DD 0x0000c283
		DD 0x00391000
		DD 0x0000e283
		DD 0x00411000
		DD 0x0000008b
		DD 0x004a1000
		DD 0x0000208b
		DD 0x00521000
		DD 0x0000408b
		DD 0x005a1000
		DD 0x0000618b
		DD 0x00621000
		DD 0x0000818b
		DD 0x006a1000
		DD 0x0000a18b
		DD 0x00731000
		DD 0x0000c28b
		DD 0x007b1000
		DD 0x0000e28b
		DD 0x00831000
		DD 0x00000094
		DD 0x008b1000
		DD 0x00002094
		DD 0x00941000
		DD 0x00004094
		DD 0x009c1000
		DD 0x00006194
		DD 0x00a41000
		DD 0x00008194
		DD 0x00ac1000
		DD 0x0000a194
		DD 0x00b41000
		DD 0x0000c294
		DD 0x00bd1000
		DD 0x0000e294
		DD 0x00c51000
		DD 0x0000009c
		DD 0x00cd1000
		DD 0x0000209c
		DD 0x00d51000
		DD 0x0000409c
		DD 0x00de1000
		DD 0x0000619c
		DD 0x00e61000
		DD 0x0000819c
		DD 0x00ee1000
		DD 0x0000a19c
		DD 0x00f61000
		DD 0x0000c29c
		DD 0x00ff1000
		DD 0x0000e29c
		DD 0x00001400
		DD 0x000000a4
		DD 0x00081400
		DD 0x000020a4
		DD 0x00101400
		DD 0x000040a4
		DD 0x00181400
		DD 0x000061a4
		DD 0x00201400
		DD 0x000081a4
		DD 0x00291400
		DD 0x0000a1a4
		DD 0x00311400
		DD 0x0000c2a4
		DD 0x00391400
		DD 0x0000e2a4
		DD 0x00411400
		DD 0x000000ac
		DD 0x004a1400
		DD 0x000020ac
		DD 0x00521400
		DD 0x000040ac
		DD 0x005a1400
		DD 0x000061ac
		DD 0x00621400
		DD 0x000081ac
		DD 0x006a1400
		DD 0x0000a1ac
		DD 0x00731400
		DD 0x0000c2ac
		DD 0x007b1400
		DD 0x0000e2ac
		DD 0x00831400
		DD 0x000000b4
		DD 0x008b1400
		DD 0x000020b4
		DD 0x00941400
		DD 0x000040b4
		DD 0x009c1400
		DD 0x000061b4
		DD 0x00a41400
		DD 0x000081b4
		DD 0x00ac1400
		DD 0x0000a1b4
		DD 0x00b41400
		DD 0x0000c2b4
		DD 0x00bd1400
		DD 0x0000e2b4
		DD 0x00c51400
		DD 0x000000bd
		DD 0x00cd1400
		DD 0x000020bd
		DD 0x00d51400
		DD 0x000040bd
		DD 0x00de1400
		DD 0x000061bd
		DD 0x00e61400
		DD 0x000081bd
		DD 0x00ee1400
		DD 0x0000a1bd
		DD 0x00f61400
		DD 0x0000c2bd
		DD 0x00ff1400
		DD 0x0000e2bd
		DD 0x00001800
		DD 0x000000c5
		DD 0x00081800
		DD 0x000020c5
		DD 0x00101800
		DD 0x000040c5
		DD 0x00181800
		DD 0x000061c5
		DD 0x00201800
		DD 0x000081c5
		DD 0x00291800
		DD 0x0000a1c5
		DD 0x00311800
		DD 0x0000c2c5
		DD 0x00391800
		DD 0x0000e2c5
		DD 0x00411800
		DD 0x000000cd
		DD 0x004a1800
		DD 0x000020cd
		DD 0x00521800
		DD 0x000040cd
		DD 0x005a1800
		DD 0x000061cd
		DD 0x00621800
		DD 0x000081cd
		DD 0x006a1800
		DD 0x0000a1cd
		DD 0x00731800
		DD 0x0000c2cd
		DD 0x007b1800
		DD 0x0000e2cd
		DD 0x00831800
		DD 0x000000d5
		DD 0x008b1800
		DD 0x000020d5
		DD 0x00941800
		DD 0x000040d5
		DD 0x009c1800
		DD 0x000061d5
		DD 0x00a41800
		DD 0x000081d5
		DD 0x00ac1800
		DD 0x0000a1d5
		DD 0x00b41800
		DD 0x0000c2d5
		DD 0x00bd1800
		DD 0x0000e2d5
		DD 0x00c51800
		DD 0x000000de
		DD 0x00cd1800
		DD 0x000020de
		DD 0x00d51800
		DD 0x000040de
		DD 0x00de1800
		DD 0x000061de
		DD 0x00e61800
		DD 0x000081de
		DD 0x00ee1800
		DD 0x0000a1de
		DD 0x00f61800
		DD 0x0000c2de
		DD 0x00ff1800
		DD 0x0000e2de
		DD 0x00001c00
		DD 0x000000e6
		DD 0x00081c00
		DD 0x000020e6
		DD 0x00101c00
		DD 0x000040e6
		DD 0x00181c00
		DD 0x000061e6
		DD 0x00201c00
		DD 0x000081e6
		DD 0x00291c00
		DD 0x0000a1e6
		DD 0x00311c00
		DD 0x0000c2e6
		DD 0x00391c00
		DD 0x0000e2e6
		DD 0x00411c00
		DD 0x000000ee
		DD 0x004a1c00
		DD 0x000020ee
		DD 0x00521c00
		DD 0x000040ee
		DD 0x005a1c00
		DD 0x000061ee
		DD 0x00621c00
		DD 0x000081ee
		DD 0x006a1c00
		DD 0x0000a1ee
		DD 0x00731c00
		DD 0x0000c2ee
		DD 0x007b1c00
		DD 0x0000e2ee
		DD 0x00831c00
		DD 0x000000f6
		DD 0x008b1c00
		DD 0x000020f6
		DD 0x00941c00
		DD 0x000040f6
		DD 0x009c1c00
		DD 0x000061f6
		DD 0x00a41c00
		DD 0x000081f6
		DD 0x00ac1c00
		DD 0x0000a1f6
		DD 0x00b41c00
		DD 0x0000c2f6
		DD 0x00bd1c00
		DD 0x0000e2f6
		DD 0x00c51c00
		DD 0x000000ff
		DD 0x00cd1c00
		DD 0x000020ff
		DD 0x00d51c00
		DD 0x000040ff
		DD 0x00de1c00
		DD 0x000061ff
		DD 0x00e61c00
		DD 0x000081ff
		DD 0x00ee1c00
		DD 0x0000a1ff
		DD 0x00f61c00
		DD 0x0000c2ff
		DD 0x00ff1c00
		DD 0x0000e2ff

_ConvertX86p16_32RGBA888_LUT_X86:
		DD 0x000000ff
		DD 0x000000ff
		DD 0x000008ff
		DD 0x002000ff
		DD 0x000010ff
		DD 0x004000ff
		DD 0x000018ff
		DD 0x006100ff
		DD 0x000020ff
		DD 0x008100ff
		DD 0x000029ff
		DD 0x00a100ff
		DD 0x000031ff
		DD 0x00c200ff
		DD 0x000039ff
		DD 0x00e200ff
		DD 0x000041ff
		DD 0x080000ff
		DD 0x00004aff
		DD 0x082000ff
		DD 0x000052ff
		DD 0x084000ff
		DD 0x00005aff
		DD 0x086100ff
		DD 0x000062ff
		DD 0x088100ff
		DD 0x00006aff
		DD 0x08a100ff
		DD 0x000073ff
		DD 0x08c200ff
		DD 0x00007bff
		DD 0x08e200ff
		DD 0x000083ff
		DD 0x100000ff
		DD 0x00008bff
		DD 0x102000ff
		DD 0x000094ff
		DD 0x104000ff
		DD 0x00009cff
		DD 0x106100ff
		DD 0x0000a4ff
		DD 0x108100ff
		DD 0x0000acff
		DD 0x10a100ff
		DD 0x0000b4ff
		DD 0x10c200ff
		DD 0x0000bdff
		DD 0x10e200ff
		DD 0x0000c5ff
		DD 0x180000ff
		DD 0x0000cdff
		DD 0x182000ff
		DD 0x0000d5ff
		DD 0x184000ff
		DD 0x0000deff
		DD 0x186100ff
		DD 0x0000e6ff
		DD 0x188100ff
		DD 0x0000eeff
		DD 0x18a100ff
		DD 0x0000f6ff
		DD 0x18c200ff
		DD 0x0000ffff
		DD 0x18e200ff
		DD 0x000400ff
		DD 0x200000ff
		DD 0x000408ff
		DD 0x202000ff
		DD 0x000410ff
		DD 0x204000ff
		DD 0x000418ff
		DD 0x206100ff
		DD 0x000420ff
		DD 0x208100ff
		DD 0x000429ff
		DD 0x20a100ff
		DD 0x000431ff
		DD 0x20c200ff
		DD 0x000439ff
		DD 0x20e200ff
		DD 0x000441ff
		DD 0x290000ff
		DD 0x00044aff
		DD 0x292000ff
		DD 0x000452ff
		DD 0x294000ff
		DD 0x00045aff
		DD 0x296100ff
		DD 0x000462ff
		DD 0x298100ff
		DD 0x00046aff
		DD 0x29a100ff
		DD 0x000473ff
		DD 0x29c200ff
		DD 0x00047bff
		DD 0x29e200ff
		DD 0x000483ff
		DD 0x310000ff
		DD 0x00048bff
		DD 0x312000ff
		DD 0x000494ff
		DD 0x314000ff
		DD 0x00049cff
		DD 0x316100ff
		DD 0x0004a4ff
		DD 0x318100ff
		DD 0x0004acff
		DD 0x31a100ff
		DD 0x0004b4ff
		DD 0x31c200ff
		DD 0x0004bdff
		DD 0x31e200ff
		DD 0x0004c5ff
		DD 0x390000ff
		DD 0x0004cdff
		DD 0x392000ff
		DD 0x0004d5ff
		DD 0x394000ff
		DD 0x0004deff
		DD 0x396100ff
		DD 0x0004e6ff
		DD 0x398100ff
		DD 0x0004eeff
		DD 0x39a100ff
		DD 0x0004f6ff
		DD 0x39c200ff
		DD 0x0004ffff
		DD 0x39e200ff
		DD 0x000800ff
		DD 0x410000ff
		DD 0x000808ff
		DD 0x412000ff
		DD 0x000810ff
		DD 0x414000ff
		DD 0x000818ff
		DD 0x416100ff
		DD 0x000820ff
		DD 0x418100ff
		DD 0x000829ff
		DD 0x41a100ff
		DD 0x000831ff
		DD 0x41c200ff
		DD 0x000839ff
		DD 0x41e200ff
		DD 0x000841ff
		DD 0x4a0000ff
		DD 0x00084aff
		DD 0x4a2000ff
		DD 0x000852ff
		DD 0x4a4000ff
		DD 0x00085aff
		DD 0x4a6100ff
		DD 0x000862ff
		DD 0x4a8100ff
		DD 0x00086aff
		DD 0x4aa100ff
		DD 0x000873ff
		DD 0x4ac200ff
		DD 0x00087bff
		DD 0x4ae200ff
		DD 0x000883ff
		DD 0x520000ff
		DD 0x00088bff
		DD 0x522000ff
		DD 0x000894ff
		DD 0x524000ff
		DD 0x00089cff
		DD 0x526100ff
		DD 0x0008a4ff
		DD 0x528100ff
		DD 0x0008acff
		DD 0x52a100ff
		DD 0x0008b4ff
		DD 0x52c200ff
		DD 0x0008bdff
		DD 0x52e200ff
		DD 0x0008c5ff
		DD 0x5a0000ff
		DD 0x0008cdff
		DD 0x5a2000ff
		DD 0x0008d5ff
		DD 0x5a4000ff
		DD 0x0008deff
		DD 0x5a6100ff
		DD 0x0008e6ff
		DD 0x5a8100ff
		DD 0x0008eeff
		DD 0x5aa100ff
		DD 0x0008f6ff
		DD 0x5ac200ff
		DD 0x0008ffff
		DD 0x5ae200ff
		DD 0x000c00ff
		DD 0x620000ff
		DD 0x000c08ff
		DD 0x622000ff
		DD 0x000c10ff
		DD 0x624000ff
		DD 0x000c18ff
		DD 0x626100ff
		DD 0x000c20ff
		DD 0x628100ff
		DD 0x000c29ff
		DD 0x62a100ff
		DD 0x000c31ff
		DD 0x62c200ff
		DD 0x000c39ff
		DD 0x62e200ff
		DD 0x000c41ff
		DD 0x6a0000ff
		DD 0x000c4aff
		DD 0x6a2000ff
		DD 0x000c52ff
		DD 0x6a4000ff
		DD 0x000c5aff
		DD 0x6a6100ff
		DD 0x000c62ff
		DD 0x6a8100ff
		DD 0x000c6aff
		DD 0x6aa100ff
		DD 0x000c73ff
		DD 0x6ac200ff
		DD 0x000c7bff
		DD 0x6ae200ff
		DD 0x000c83ff
		DD 0x730000ff
		DD 0x000c8bff
		DD 0x732000ff
		DD 0x000c94ff
		DD 0x734000ff
		DD 0x000c9cff
		DD 0x736100ff
		DD 0x000ca4ff
		DD 0x738100ff
		DD 0x000cacff
		DD 0x73a100ff
		DD 0x000cb4ff
		DD 0x73c200ff
		DD 0x000cbdff
		DD 0x73e200ff
		DD 0x000cc5ff
		DD 0x7b0000ff
		DD 0x000ccdff
		DD 0x7b2000ff
		DD 0x000cd5ff
		DD 0x7b4000ff
		DD 0x000cdeff
		DD 0x7b6100ff
		DD 0x000ce6ff
		DD 0x7b8100ff
		DD 0x000ceeff
		DD 0x7ba100ff
		DD 0x000cf6ff
		DD 0x7bc200ff
		DD 0x000cffff
		DD 0x7be200ff
		DD 0x001000ff
		DD 0x830000ff
		DD 0x001008ff
		DD 0x832000ff
		DD 0x001010ff
		DD 0x834000ff
		DD 0x001018ff
		DD 0x836100ff
		DD 0x001020ff
		DD 0x838100ff
		DD 0x001029ff
		DD 0x83a100ff
		DD 0x001031ff
		DD 0x83c200ff
		DD 0x001039ff
		DD 0x83e200ff
		DD 0x001041ff
		DD 0x8b0000ff
		DD 0x00104aff
		DD 0x8b2000ff
		DD 0x001052ff
		DD 0x8b4000ff
		DD 0x00105aff
		DD 0x8b6100ff
		DD 0x001062ff
		DD 0x8b8100ff
		DD 0x00106aff
		DD 0x8ba100ff
		DD 0x001073ff
		DD 0x8bc200ff
		DD 0x00107bff
		DD 0x8be200ff
		DD 0x001083ff
		DD 0x940000ff
		DD 0x00108bff
		DD 0x942000ff
		DD 0x001094ff
		DD 0x944000ff
		DD 0x00109cff
		DD 0x946100ff
		DD 0x0010a4ff
		DD 0x948100ff
		DD 0x0010acff
		DD 0x94a100ff
		DD 0x0010b4ff
		DD 0x94c200ff
		DD 0x0010bdff
		DD 0x94e200ff
		DD 0x0010c5ff
		DD 0x9c0000ff
		DD 0x0010cdff
		DD 0x9c2000ff
		DD 0x0010d5ff
		DD 0x9c4000ff
		DD 0x0010deff
		DD 0x9c6100ff
		DD 0x0010e6ff
		DD 0x9c8100ff
		DD 0x0010eeff
		DD 0x9ca100ff
		DD 0x0010f6ff
		DD 0x9cc200ff
		DD 0x0010ffff
		DD 0x9ce200ff
		DD 0x001400ff
		DD 0xa40000ff
		DD 0x001408ff
		DD 0xa42000ff
		DD 0x001410ff
		DD 0xa44000ff
		DD 0x001418ff
		DD 0xa46100ff
		DD 0x001420ff
		DD 0xa48100ff
		DD 0x001429ff
		DD 0xa4a100ff
		DD 0x001431ff
		DD 0xa4c200ff
		DD 0x001439ff
		DD 0xa4e200ff
		DD 0x001441ff
		DD 0xac0000ff
		DD 0x00144aff
		DD 0xac2000ff
		DD 0x001452ff
		DD 0xac4000ff
		DD 0x00145aff
		DD 0xac6100ff
		DD 0x001462ff
		DD 0xac8100ff
		DD 0x00146aff
		DD 0xaca100ff
		DD 0x001473ff
		DD 0xacc200ff
		DD 0x00147bff
		DD 0xace200ff
		DD 0x001483ff
		DD 0xb40000ff
		DD 0x00148bff
		DD 0xb42000ff
		DD 0x001494ff
		DD 0xb44000ff
		DD 0x00149cff
		DD 0xb46100ff
		DD 0x0014a4ff
		DD 0xb48100ff
		DD 0x0014acff
		DD 0xb4a100ff
		DD 0x0014b4ff
		DD 0xb4c200ff
		DD 0x0014bdff
		DD 0xb4e200ff
		DD 0x0014c5ff
		DD 0xbd0000ff
		DD 0x0014cdff
		DD 0xbd2000ff
		DD 0x0014d5ff
		DD 0xbd4000ff
		DD 0x0014deff
		DD 0xbd6100ff
		DD 0x0014e6ff
		DD 0xbd8100ff
		DD 0x0014eeff
		DD 0xbda100ff
		DD 0x0014f6ff
		DD 0xbdc200ff
		DD 0x0014ffff
		DD 0xbde200ff
		DD 0x001800ff
		DD 0xc50000ff
		DD 0x001808ff
		DD 0xc52000ff
		DD 0x001810ff
		DD 0xc54000ff
		DD 0x001818ff
		DD 0xc56100ff
		DD 0x001820ff
		DD 0xc58100ff
		DD 0x001829ff
		DD 0xc5a100ff
		DD 0x001831ff
		DD 0xc5c200ff
		DD 0x001839ff
		DD 0xc5e200ff
		DD 0x001841ff
		DD 0xcd0000ff
		DD 0x00184aff
		DD 0xcd2000ff
		DD 0x001852ff
		DD 0xcd4000ff
		DD 0x00185aff
		DD 0xcd6100ff
		DD 0x001862ff
		DD 0xcd8100ff
		DD 0x00186aff
		DD 0xcda100ff
		DD 0x001873ff
		DD 0xcdc200ff
		DD 0x00187bff
		DD 0xcde200ff
		DD 0x001883ff
		DD 0xd50000ff
		DD 0x00188bff
		DD 0xd52000ff
		DD 0x001894ff
		DD 0xd54000ff
		DD 0x00189cff
		DD 0xd56100ff
		DD 0x0018a4ff
		DD 0xd58100ff
		DD 0x0018acff
		DD 0xd5a100ff
		DD 0x0018b4ff
		DD 0xd5c200ff
		DD 0x0018bdff
		DD 0xd5e200ff
		DD 0x0018c5ff
		DD 0xde0000ff
		DD 0x0018cdff
		DD 0xde2000ff
		DD 0x0018d5ff
		DD 0xde4000ff
		DD 0x0018deff
		DD 0xde6100ff
		DD 0x0018e6ff
		DD 0xde8100ff
		DD 0x0018eeff
		DD 0xdea100ff
		DD 0x0018f6ff
		DD 0xdec200ff
		DD 0x0018ffff
		DD 0xdee200ff
		DD 0x001c00ff
		DD 0xe60000ff
		DD 0x001c08ff
		DD 0xe62000ff
		DD 0x001c10ff
		DD 0xe64000ff
		DD 0x001c18ff
		DD 0xe66100ff
		DD 0x001c20ff
		DD 0xe68100ff
		DD 0x001c29ff
		DD 0xe6a100ff
		DD 0x001c31ff
		DD 0xe6c200ff
		DD 0x001c39ff
		DD 0xe6e200ff
		DD 0x001c41ff
		DD 0xee0000ff
		DD 0x001c4aff
		DD 0xee2000ff
		DD 0x001c52ff
		DD 0xee4000ff
		DD 0x001c5aff
		DD 0xee6100ff
		DD 0x001c62ff
		DD 0xee8100ff
		DD 0x001c6aff
		DD 0xeea100ff
		DD 0x001c73ff
		DD 0xeec200ff
		DD 0x001c7bff
		DD 0xeee200ff
		DD 0x001c83ff
		DD 0xf60000ff
		DD 0x001c8bff
		DD 0xf62000ff
		DD 0x001c94ff
		DD 0xf64000ff
		DD 0x001c9cff
		DD 0xf66100ff
		DD 0x001ca4ff
		DD 0xf68100ff
		DD 0x001cacff
		DD 0xf6a100ff
		DD 0x001cb4ff
		DD 0xf6c200ff
		DD 0x001cbdff
		DD 0xf6e200ff
		DD 0x001cc5ff
		DD 0xff0000ff
		DD 0x001ccdff
		DD 0xff2000ff
		DD 0x001cd5ff
		DD 0xff4000ff
		DD 0x001cdeff
		DD 0xff6100ff
		DD 0x001ce6ff
		DD 0xff8100ff
		DD 0x001ceeff
		DD 0xffa100ff
		DD 0x001cf6ff
		DD 0xffc200ff
		DD 0x001cffff
		DD 0xffe200ff

_ConvertX86p16_32BGRA888_LUT_X86:
		DD 0x000000ff
		DD 0x000000ff
		DD 0x080000ff
		DD 0x002000ff
		DD 0x100000ff
		DD 0x004000ff
		DD 0x180000ff
		DD 0x006100ff
		DD 0x200000ff
		DD 0x008100ff
		DD 0x290000ff
		DD 0x00a100ff
		DD 0x310000ff
		DD 0x00c200ff
		DD 0x390000ff
		DD 0x00e200ff
		DD 0x410000ff
		DD 0x000008ff
		DD 0x4a0000ff
		DD 0x002008ff
		DD 0x520000ff
		DD 0x004008ff
		DD 0x5a0000ff
		DD 0x006108ff
		DD 0x620000ff
		DD 0x008108ff
		DD 0x6a0000ff
		DD 0x00a108ff
		DD 0x730000ff
		DD 0x00c208ff
		DD 0x7b0000ff
		DD 0x00e208ff
		DD 0x830000ff
		DD 0x000010ff
		DD 0x8b0000ff
		DD 0x002010ff
		DD 0x940000ff
		DD 0x004010ff
		DD 0x9c0000ff
		DD 0x006110ff
		DD 0xa40000ff
		DD 0x008110ff
		DD 0xac0000ff
		DD 0x00a110ff
		DD 0xb40000ff
		DD 0x00c210ff
		DD 0xbd0000ff
		DD 0x00e210ff
		DD 0xc50000ff
		DD 0x000018ff
		DD 0xcd0000ff
		DD 0x002018ff
		DD 0xd50000ff
		DD 0x004018ff
		DD 0xde0000ff
		DD 0x006118ff
		DD 0xe60000ff
		DD 0x008118ff
		DD 0xee0000ff
		DD 0x00a118ff
		DD 0xf60000ff
		DD 0x00c218ff
		DD 0xff0000ff
		DD 0x00e218ff
		DD 0x000400ff
		DD 0x000020ff
		DD 0x080400ff
		DD 0x002020ff
		DD 0x100400ff
		DD 0x004020ff
		DD 0x180400ff
		DD 0x006120ff
		DD 0x200400ff
		DD 0x008120ff
		DD 0x290400ff
		DD 0x00a120ff
		DD 0x310400ff
		DD 0x00c220ff
		DD 0x390400ff
		DD 0x00e220ff
		DD 0x410400ff
		DD 0x000029ff
		DD 0x4a0400ff
		DD 0x002029ff
		DD 0x520400ff
		DD 0x004029ff
		DD 0x5a0400ff
		DD 0x006129ff
		DD 0x620400ff
		DD 0x008129ff
		DD 0x6a0400ff
		DD 0x00a129ff
		DD 0x730400ff
		DD 0x00c229ff
		DD 0x7b0400ff
		DD 0x00e229ff
		DD 0x830400ff
		DD 0x000031ff
		DD 0x8b0400ff
		DD 0x002031ff
		DD 0x940400ff
		DD 0x004031ff
		DD 0x9c0400ff
		DD 0x006131ff
		DD 0xa40400ff
		DD 0x008131ff
		DD 0xac0400ff
		DD 0x00a131ff
		DD 0xb40400ff
		DD 0x00c231ff
		DD 0xbd0400ff
		DD 0x00e231ff
		DD 0xc50400ff
		DD 0x000039ff
		DD 0xcd0400ff
		DD 0x002039ff
		DD 0xd50400ff
		DD 0x004039ff
		DD 0xde0400ff
		DD 0x006139ff
		DD 0xe60400ff
		DD 0x008139ff
		DD 0xee0400ff
		DD 0x00a139ff
		DD 0xf60400ff
		DD 0x00c239ff
		DD 0xff0400ff
		DD 0x00e239ff
		DD 0x000800ff
		DD 0x000041ff
		DD 0x080800ff
		DD 0x002041ff
		DD 0x100800ff
		DD 0x004041ff
		DD 0x180800ff
		DD 0x006141ff
		DD 0x200800ff
		DD 0x008141ff
		DD 0x290800ff
		DD 0x00a141ff
		DD 0x310800ff
		DD 0x00c241ff
		DD 0x390800ff
		DD 0x00e241ff
		DD 0x410800ff
		DD 0x00004aff
		DD 0x4a0800ff
		DD 0x00204aff
		DD 0x520800ff
		DD 0x00404aff
		DD 0x5a0800ff
		DD 0x00614aff
		DD 0x620800ff
		DD 0x00814aff
		DD 0x6a0800ff
		DD 0x00a14aff
		DD 0x730800ff
		DD 0x00c24aff
		DD 0x7b0800ff
		DD 0x00e24aff
		DD 0x830800ff
		DD 0x000052ff
		DD 0x8b0800ff
		DD 0x002052ff
		DD 0x940800ff
		DD 0x004052ff
		DD 0x9c0800ff
		DD 0x006152ff
		DD 0xa40800ff
		DD 0x008152ff
		DD 0xac0800ff
		DD 0x00a152ff
		DD 0xb40800ff
		DD 0x00c252ff
		DD 0xbd0800ff
		DD 0x00e252ff
		DD 0xc50800ff
		DD 0x00005aff
		DD 0xcd0800ff
		DD 0x00205aff
		DD 0xd50800ff
		DD 0x00405aff
		DD 0xde0800ff
		DD 0x00615aff
		DD 0xe60800ff
		DD 0x00815aff
		DD 0xee0800ff
		DD 0x00a15aff
		DD 0xf60800ff
		DD 0x00c25aff
		DD 0xff0800ff
		DD 0x00e25aff
		DD 0x000c00ff
		DD 0x000062ff
		DD 0x080c00ff
		DD 0x002062ff
		DD 0x100c00ff
		DD 0x004062ff
		DD 0x180c00ff
		DD 0x006162ff
		DD 0x200c00ff
		DD 0x008162ff
		DD 0x290c00ff
		DD 0x00a162ff
		DD 0x310c00ff
		DD 0x00c262ff
		DD 0x390c00ff
		DD 0x00e262ff
		DD 0x410c00ff
		DD 0x00006aff
		DD 0x4a0c00ff
		DD 0x00206aff
		DD 0x520c00ff
		DD 0x00406aff
		DD 0x5a0c00ff
		DD 0x00616aff
		DD 0x620c00ff
		DD 0x00816aff
		DD 0x6a0c00ff
		DD 0x00a16aff
		DD 0x730c00ff
		DD 0x00c26aff
		DD 0x7b0c00ff
		DD 0x00e26aff
		DD 0x830c00ff
		DD 0x000073ff
		DD 0x8b0c00ff
		DD 0x002073ff
		DD 0x940c00ff
		DD 0x004073ff
		DD 0x9c0c00ff
		DD 0x006173ff
		DD 0xa40c00ff
		DD 0x008173ff
		DD 0xac0c00ff
		DD 0x00a173ff
		DD 0xb40c00ff
		DD 0x00c273ff
		DD 0xbd0c00ff
		DD 0x00e273ff
		DD 0xc50c00ff
		DD 0x00007bff
		DD 0xcd0c00ff
		DD 0x00207bff
		DD 0xd50c00ff
		DD 0x00407bff
		DD 0xde0c00ff
		DD 0x00617bff
		DD 0xe60c00ff
		DD 0x00817bff
		DD 0xee0c00ff
		DD 0x00a17bff
		DD 0xf60c00ff
		DD 0x00c27bff
		DD 0xff0c00ff
		DD 0x00e27bff
		DD 0x001000ff
		DD 0x000083ff
		DD 0x081000ff
		DD 0x002083ff
		DD 0x101000ff
		DD 0x004083ff
		DD 0x181000ff
		DD 0x006183ff
		DD 0x201000ff
		DD 0x008183ff
		DD 0x291000ff
		DD 0x00a183ff
		DD 0x311000ff
		DD 0x00c283ff
		DD 0x391000ff
		DD 0x00e283ff
		DD 0x411000ff
		DD 0x00008bff
		DD 0x4a1000ff
		DD 0x00208bff
		DD 0x521000ff
		DD 0x00408bff
		DD 0x5a1000ff
		DD 0x00618bff
		DD 0x621000ff
		DD 0x00818bff
		DD 0x6a1000ff
		DD 0x00a18bff
		DD 0x731000ff
		DD 0x00c28bff
		DD 0x7b1000ff
		DD 0x00e28bff
		DD 0x831000ff
		DD 0x000094ff
		DD 0x8b1000ff
		DD 0x002094ff
		DD 0x941000ff
		DD 0x004094ff
		DD 0x9c1000ff
		DD 0x006194ff
		DD 0xa41000ff
		DD 0x008194ff
		DD 0xac1000ff
		DD 0x00a194ff
		DD 0xb41000ff
		DD 0x00c294ff
		DD 0xbd1000ff
		DD 0x00e294ff
		DD 0xc51000ff
		DD 0x00009cff
		DD 0xcd1000ff
		DD 0x00209cff
		DD 0xd51000ff
		DD 0x00409cff
		DD 0xde1000ff
		DD 0x00619cff
		DD 0xe61000ff
		DD 0x00819cff
		DD 0xee1000ff
		DD 0x00a19cff
		DD 0xf61000ff
		DD 0x00c29cff
		DD 0xff1000ff
		DD 0x00e29cff
		DD 0x001400ff
		DD 0x0000a4ff
		DD 0x081400ff
		DD 0x0020a4ff
		DD 0x101400ff
		DD 0x0040a4ff
		DD 0x181400ff
		DD 0x0061a4ff
		DD 0x201400ff
		DD 0x0081a4ff
		DD 0x291400ff
		DD 0x00a1a4ff
		DD 0x311400ff
		DD 0x00c2a4ff
		DD 0x391400ff
		DD 0x00e2a4ff
		DD 0x411400ff
		DD 0x0000acff
		DD 0x4a1400ff
		DD 0x0020acff
		DD 0x521400ff
		DD 0x0040acff
		DD 0x5a1400ff
		DD 0x0061acff
		DD 0x621400ff
		DD 0x0081acff
		DD 0x6a1400ff
		DD 0x00a1acff
		DD 0x731400ff
		DD 0x00c2acff
		DD 0x7b1400ff
		DD 0x00e2acff
		DD 0x831400ff
		DD 0x0000b4ff
		DD 0x8b1400ff
		DD 0x0020b4ff
		DD 0x941400ff
		DD 0x0040b4ff
		DD 0x9c1400ff
		DD 0x0061b4ff
		DD 0xa41400ff
		DD 0x0081b4ff
		DD 0xac1400ff
		DD 0x00a1b4ff
		DD 0xb41400ff
		DD 0x00c2b4ff
		DD 0xbd1400ff
		DD 0x00e2b4ff
		DD 0xc51400ff
		DD 0x0000bdff
		DD 0xcd1400ff
		DD 0x0020bdff
		DD 0xd51400ff
		DD 0x0040bdff
		DD 0xde1400ff
		DD 0x0061bdff
		DD 0xe61400ff
		DD 0x0081bdff
		DD 0xee1400ff
		DD 0x00a1bdff
		DD 0xf61400ff
		DD 0x00c2bdff
		DD 0xff1400ff
		DD 0x00e2bdff
		DD 0x001800ff
		DD 0x0000c5ff
		DD 0x081800ff
		DD 0x0020c5ff
		DD 0x101800ff
		DD 0x0040c5ff
		DD 0x181800ff
		DD 0x0061c5ff
		DD 0x201800ff
		DD 0x0081c5ff
		DD 0x291800ff
		DD 0x00a1c5ff
		DD 0x311800ff
		DD 0x00c2c5ff
		DD 0x391800ff
		DD 0x00e2c5ff
		DD 0x411800ff
		DD 0x0000cdff
		DD 0x4a1800ff
		DD 0x0020cdff
		DD 0x521800ff
		DD 0x0040cdff
		DD 0x5a1800ff
		DD 0x0061cdff
		DD 0x621800ff
		DD 0x0081cdff
		DD 0x6a1800ff
		DD 0x00a1cdff
		DD 0x731800ff
		DD 0x00c2cdff
		DD 0x7b1800ff
		DD 0x00e2cdff
		DD 0x831800ff
		DD 0x0000d5ff
		DD 0x8b1800ff
		DD 0x0020d5ff
		DD 0x941800ff
		DD 0x0040d5ff
		DD 0x9c1800ff
		DD 0x0061d5ff
		DD 0xa41800ff
		DD 0x0081d5ff
		DD 0xac1800ff
		DD 0x00a1d5ff
		DD 0xb41800ff
		DD 0x00c2d5ff
		DD 0xbd1800ff
		DD 0x00e2d5ff
		DD 0xc51800ff
		DD 0x0000deff
		DD 0xcd1800ff
		DD 0x0020deff
		DD 0xd51800ff
		DD 0x0040deff
		DD 0xde1800ff
		DD 0x0061deff
		DD 0xe61800ff
		DD 0x0081deff
		DD 0xee1800ff
		DD 0x00a1deff
		DD 0xf61800ff
		DD 0x00c2deff
		DD 0xff1800ff
		DD 0x00e2deff
		DD 0x001c00ff
		DD 0x0000e6ff
		DD 0x081c00ff
		DD 0x0020e6ff
		DD 0x101c00ff
		DD 0x0040e6ff
		DD 0x181c00ff
		DD 0x0061e6ff
		DD 0x201c00ff
		DD 0x0081e6ff
		DD 0x291c00ff
		DD 0x00a1e6ff
		DD 0x311c00ff
		DD 0x00c2e6ff
		DD 0x391c00ff
		DD 0x00e2e6ff
		DD 0x411c00ff
		DD 0x0000eeff
		DD 0x4a1c00ff
		DD 0x0020eeff
		DD 0x521c00ff
		DD 0x0040eeff
		DD 0x5a1c00ff
		DD 0x0061eeff
		DD 0x621c00ff
		DD 0x0081eeff
		DD 0x6a1c00ff
		DD 0x00a1eeff
		DD 0x731c00ff
		DD 0x00c2eeff
		DD 0x7b1c00ff
		DD 0x00e2eeff
		DD 0x831c00ff
		DD 0x0000f6ff
		DD 0x8b1c00ff
		DD 0x0020f6ff
		DD 0x941c00ff
		DD 0x0040f6ff
		DD 0x9c1c00ff
		DD 0x0061f6ff
		DD 0xa41c00ff
		DD 0x0081f6ff
		DD 0xac1c00ff
		DD 0x00a1f6ff
		DD 0xb41c00ff
		DD 0x00c2f6ff
		DD 0xbd1c00ff
		DD 0x00e2f6ff
		DD 0xc51c00ff
		DD 0x0000ffff
		DD 0xcd1c00ff
		DD 0x0020ffff
		DD 0xd51c00ff
		DD 0x0040ffff
		DD 0xde1c00ff
		DD 0x0061ffff
		DD 0xe61c00ff
		DD 0x0081ffff
		DD 0xee1c00ff
		DD 0x00a1ffff
		DD 0xf61c00ff
		DD 0x00c2ffff
		DD 0xff1c00ff
		DD 0x00e2ffff


