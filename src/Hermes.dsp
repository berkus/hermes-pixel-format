# Microsoft Developer Studio Project File - Name="Hermes" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Hermes - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Hermes.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Hermes.mak" CFG="Hermes - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Hermes - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Hermes - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Hermes - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Hermes - Win32 Release"
# Name "Hermes - Win32 Debug"
# Begin Group "Source Code"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=.\Blit.c
# End Source File
# Begin Source File

SOURCE=.\c_16.c
# End Source File
# Begin Source File

SOURCE=.\c_24.c
# End Source File
# Begin Source File

SOURCE=.\c_32.c
# End Source File
# Begin Source File

SOURCE=.\c_clr.c
# End Source File
# Begin Source File

SOURCE=.\c_cnv.c
# End Source File
# Begin Source File

SOURCE=.\c_cpy.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_a.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_ac.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_ao_blit.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_ca.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_cc.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_cc_blit.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_co_blit.c
# End Source File
# Begin Source File

SOURCE=.\c_genrc_noalpha_alpha.c
# End Source File
# Begin Source File

SOURCE=.\c_i8.c
# End Source File
# Begin Source File

SOURCE=.\c_muhmu.c
# End Source File
# Begin Source File

SOURCE=.\Clear.c
# End Source File
# Begin Source File

SOURCE=.\Convert.c
# End Source File
# Begin Source File

SOURCE=.\d_32.c
# End Source File
# Begin Source File

SOURCE=.\Dither.c
# End Source File
# Begin Source File

SOURCE=.\FactConv.c
# End Source File
# Begin Source File

SOURCE=.\Factory.c
# End Source File
# Begin Source File

SOURCE=.\Format.c
# End Source File
# Begin Source File

SOURCE=.\Hermes.c
# End Source File
# Begin Source File

SOURCE=.\List.c
# End Source File
# Begin Source File

SOURCE=.\Palette.c
# End Source File
# Begin Source File

SOURCE=.\Utility.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\Clear.h
# End Source File
# Begin Source File

SOURCE=.\Convert.h
# End Source File
# Begin Source File

SOURCE=.\Debug.h
# End Source File
# Begin Source File

SOURCE=.\Dither.h
# End Source File
# Begin Source File

SOURCE=.\Factory.h
# End Source File
# Begin Source File

SOURCE=.\H_Clear.h
# End Source File
# Begin Source File

SOURCE=.\H_Config.h
# End Source File
# Begin Source File

SOURCE=.\H_Conv.h
# End Source File
# Begin Source File

SOURCE=.\H_Format.h
# End Source File
# Begin Source File

SOURCE=.\H_Pal.h
# End Source File
# Begin Source File

SOURCE=.\HeadC.h
# End Source File
# Begin Source File

SOURCE=.\HeadMMX.h
# End Source File
# Begin Source File

SOURCE=.\HeadX86.h
# End Source File
# Begin Source File

SOURCE=.\HermConf.h
# End Source File
# Begin Source File

SOURCE=.\Hermes.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\Palette.h
# End Source File
# Begin Source File

SOURCE=.\Types.h
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# Begin Source File

SOURCE=.\verwin.h
# End Source File
# End Group
# Begin Group "Assembly Code"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\nasm\mmx_clr.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building MMX Clearers
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\mmx_clr.asm
InputName=mmx_clr

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building MMX Clearers
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\mmx_clr.asm
InputName=mmx_clr

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\mmx_main.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building MMX main l00p.
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\mmx_main.asm
InputName=mmx_main

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building MMX main l00p.
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\mmx_main.asm
InputName=mmx_main

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\mmxp2_32.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building MMX p2 32-->* converters
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\mmxp2_32.asm
InputName=mmxp2_32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building MMX p2 32-->* converters
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\mmxp2_32.asm
InputName=mmxp2_32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\mmxp_32.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building MMX 32-->* converters
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\mmxp_32.asm
InputName=mmxp_32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building MMX 32-->* converters
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\mmxp_32.asm
InputName=mmxp_32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86_clr.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler Clearers
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86_clr.asm
InputName=x86_clr

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler Clearers
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86_clr.asm
InputName=x86_clr

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86_main.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler main loop
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86_main.asm
InputName=x86_main

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler main loop
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86_main.asm
InputName=x86_main

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_16.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler 16-->* converters
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86p_16.asm
InputName=x86p_16

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler 16-->* converters
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86p_16.asm
InputName=x86p_16

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_32.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler 32-->* converters
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86p_32.asm
InputName=x86p_32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler 32-->* converters
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86p_32.asm
InputName=x86p_32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_cpy.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler straight copying routines
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86p_cpy.asm
InputName=x86p_cpy

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler straight copying routines
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86p_cpy.asm
InputName=x86p_cpy

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_i8.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler index8-->* converters
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86p_i8.asm
InputName=x86p_i8

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler index8-->* converters
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86p_i8.asm
InputName=x86p_i8

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_s32.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building x86 assembler 32-->* s   t   r  e  t  c  h converters
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86p_s32.asm
InputName=x86p_s32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building x86 assembler 32-->* s   t   r  e  t  c  h converters
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86p_s32.asm
InputName=x86p_s32

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86pScpy.asm

!IF  "$(CFG)" == "Hermes - Win32 Release"

# Begin Custom Build - Building .. an empty file :)
InputDir=.\nasm
OutDir=.\Release
InputPath=.\nasm\x86pScpy.asm
InputName=x86pScpy

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "Hermes - Win32 Debug"

# Begin Custom Build - Building .. an empty file :)
InputDir=.\nasm
OutDir=.\Debug
InputPath=.\nasm\x86pScpy.asm
InputName=x86pScpy

"$(Outdir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(OutDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Definition Files"

# PROP Default_Filter "def"
# Begin Source File

SOURCE=.\Hermes.def
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Hermes.rc
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409 /d "MSVC"
# End Source File
# End Group
# End Target
# End Project
