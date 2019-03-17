# Watcom makefile for Hermes-1.2.5 assembly

.SILENT
.EXTENSIONS:
.EXTENSIONS: .obj .asm

ASM_FLAGS = -f win32

ASM_FILES = x86_main.obj x86_clr.obj x86p_32.obj x86p_s32.obj &
            x86p_16.obj x86p_i8.obj x86p_cpy.obj &
            mmx_main.obj mmx_clr.obj mmxp2_32.obj mmxp_32.obj

all: $(ASM_FILES)

.asm.obj:
        nasm $(ASM_FLAGS) $[@ -o $@

clean:  .SYMBOLIC
        del *.obj
