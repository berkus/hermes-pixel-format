# ---------------------------------------------------------------------------
!if !$d(BCB)
BCB = $(MAKEDIR)\..
!endif

# ---------------------------------------------------------------------------
# IDE SECTION
# ---------------------------------------------------------------------------
# The following section of the project makefile is managed by the BCB IDE.
# It is recommended to use the IDE to change any of the values in this
# section.
# ---------------------------------------------------------------------------

VERSION = BCB.05.03
# ---------------------------------------------------------------------------
PROJECT = Hermes.dll
OBJFILES = Intermediate\c_16.obj Intermediate\c_24.obj Intermediate\c_32.obj \
    Intermediate\c_32_ao_blit.obj Intermediate\c_clr.obj \
    Intermediate\c_cnv.obj Intermediate\c_cpy.obj Intermediate\c_genrc.obj \
    Intermediate\c_genrc_a.obj Intermediate\c_genrc_ac.obj \
    Intermediate\c_genrc_ao_blit.obj Intermediate\c_genrc_ca.obj \
    Intermediate\c_genrc_cc.obj Intermediate\c_genrc_cc_blit.obj \
    Intermediate\c_genrc_co_blit.obj Intermediate\c_i8.obj \
    Intermediate\c_muhmu.obj Intermediate\Clear.obj Intermediate\Convert.obj \
    Intermediate\d_32.obj Intermediate\Dither.obj Intermediate\FactConv.obj \
    Intermediate\Factory.obj Intermediate\Format.obj Intermediate\Hermes.obj \
    Intermediate\List.obj Intermediate\Palette.obj Intermediate\Blit.obj \
    Intermediate\Utility.obj Intermediate\x86pScpy.obj \
    Intermediate\mmx_main.obj Intermediate\mmxp_32.obj \
    Intermediate\mmxp2_32.obj Intermediate\x86_clr.obj \
    Intermediate\x86_main.obj Intermediate\x8616lut.obj \
    Intermediate\x86p_16.obj Intermediate\x86p_32.obj \
    Intermediate\x86p_cpy.obj Intermediate\x86p_i8.obj \
    Intermediate\x86p_s32.obj Intermediate\mmx_clr.obj
RESFILES = 
MAINSOURCE = Hermes.bpf
RESDEPEN = $(RESFILES)
LIBFILES = 
IDLFILES = 
IDLGENFILES = 
LIBRARIES = 
PACKAGES = VCL50.bpi VCLX50.bpi bcbsmp50.bpi VCLDB50.bpi VCLADO50.bpi ibsmp50.bpi \
    VCLBDE50.bpi VCLDBX50.bpi QRPT50.bpi TEEUI50.bpi TEEDB50.bpi TEE50.bpi \
    DSS50.bpi TEEQR50.bpi VCLIB50.bpi VCLMID50.bpi VCLIE50.bpi INETDB50.bpi \
    INET50.bpi NMFAST50.bpi WEBMID50.bpi bcbie50.bpi dclocx50.bpi \
    bcb97axserver50.bpi
SPARELIBS = 
DEFFILE = borland.def
# ---------------------------------------------------------------------------
PATHCPP = .;
PATHASM = .;nasm
PATHPAS = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
USERDEFINES = X86_ASSEMBLER
SYSDEFINES = NO_STRICT;_NO_VCL
INCLUDEPATH = $(BCB)\include;$(BCB)\include\vcl
LIBPATH = $(BCB)\lib\obj;$(BCB)\lib
WARNINGS= -w-par
# ---------------------------------------------------------------------------
CFLAG1 = -WD -O2 -H=$(BCB)\lib\vcl50.csm -Hc -Vx -Ve -X- -a8 -5 -b -k- -vi -Oc -tWD \
    -tWM -c
IDLCFLAGS = -I$(BCB)\include -I$(BCB)\include\vcl -src_suffix cpp -DX86_ASSEMBLER -boa
PFLAGS = -N2Intermediate -N0Intermediate -$Y- -$L- -$D- -v -JPHNE -M
RFLAGS = 
AFLAGS = /mx /w2 /zn
LFLAGS = -IIntermediate -D"" -aa -Tpd -x -Gn -Gi
# ---------------------------------------------------------------------------
ALLOBJ = c0d32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cw32mt.lib
# ---------------------------------------------------------------------------
!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0

[Version Info Keys]
CompanyName=
FileDescription=
FileVersion=1.0.0.0
InternalName=
LegalCopyright=
LegalTrademarks=
OriginalFilename=
ProductName=
ProductVersion=1.0.0.0
Comments=

[Debugging]
DebugSourceDirs=$(BCB)\source\vcl

!endif





# ---------------------------------------------------------------------------
# MAKE SECTION
# ---------------------------------------------------------------------------
# This section of the project file is not used by the BCB IDE.  It is for
# the benefit of building from the command-line using the MAKE utility.
# ---------------------------------------------------------------------------

.autodepend
# ---------------------------------------------------------------------------
!if "$(USERDEFINES)" != ""
AUSERDEFINES = -d$(USERDEFINES:;= -d)
!else
AUSERDEFINES =
!endif

!if !$d(BCC32)
BCC32 = bcc32
!endif

!if !$d(CPP32)
CPP32 = cpp32
!endif

!if !$d(DCC32)
DCC32 = dcc32
!endif

!if !$d(TASM32)
TASM32 = nasmw -fobj
!endif

!if !$d(LINKER)
LINKER = ilink32
!endif

!if !$d(BRCC32)
BRCC32 = brcc32
!endif


# ---------------------------------------------------------------------------
!if $d(PATHCPP)
.PATH.CPP = $(PATHCPP)
.PATH.C   = $(PATHCPP)
!endif

!if $d(PATHPAS)
.PATH.PAS = $(PATHPAS)
!endif

!if $d(PATHASM)
.PATH.ASM = $(PATHASM)
!endif

!if $d(PATHRC)
.PATH.RC  = $(PATHRC)
!endif
# ---------------------------------------------------------------------------
$(PROJECT): $(IDLGENFILES) $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) -L$(LIBPATH) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES)
!
# ---------------------------------------------------------------------------
.pas.hpp:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.pas.obj:
    $(BCB)\BIN\$(DCC32) $(PFLAGS) -U$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -O$(INCLUDEPATH) --BCB {$< }

.cpp.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.obj:
    $(BCB)\BIN\$(BCC32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n$(@D) {$< }

.c.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.cpp.i:
    $(BCB)\BIN\$(CPP32) $(CFLAG1) $(WARNINGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -n. {$< }

.asm.obj:
    $(BCB)\BIN\$(TASM32)  $< -o $@

.rc.res:
    $(BCB)\BIN\$(BRCC32) $(RFLAGS) -I$(INCLUDEPATH) -D$(USERDEFINES);$(SYSDEFINES) -fo$@ $<
# ---------------------------------------------------------------------------




