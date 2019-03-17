# Microsoft Developer Studio Project File - Name="HermesStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=HermesStatic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HermesStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HermesStatic.mak" CFG="HermesStatic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HermesStatic - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "HermesStatic - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /Ob2 /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "MSVC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "MSVC"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Hermes.lib"

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "MSVC" /YX /FD /GZ /c
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "MSVC"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\Hermesd.lib"

!ENDIF 

# Begin Target

# Name "HermesStatic - Win32 Release"
# Name "HermesStatic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=.\c_32_ao_blit.c

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

!ENDIF 

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

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE=.\H_Blit.h
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

SOURCE=.\H_Types.h
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

# PROP Default_Filter "asm"
# Begin Source File

SOURCE=.\nasm\mmx_clr.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\mmx_clr.asm
InputName=mmx_clr

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\mmx_clr.asm
InputName=mmx_clr

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\mmx_main.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\mmx_main.asm
InputName=mmx_main

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\mmx_main.asm
InputName=mmx_main

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\mmxp2_32.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\mmxp2_32.asm
InputName=mmxp2_32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\mmxp2_32.asm
InputName=mmxp2_32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\mmxp_32.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\mmxp_32.asm
InputName=mmxp_32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\mmxp_32.asm
InputName=mmxp_32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86_clr.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86_clr.asm
InputName=x86_clr

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86_clr.asm
InputName=x86_clr

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86_main.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86_main.asm
InputName=x86_main

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86_main.asm
InputName=x86_main

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_16.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86p_16.asm
InputName=x86p_16

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86p_16.asm
InputName=x86p_16

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_32.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86p_32.asm
InputName=x86p_32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86p_32.asm
InputName=x86p_32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_cpy.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86p_cpy.asm
InputName=x86p_cpy

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86p_cpy.asm
InputName=x86p_cpy

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_i8.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86p_i8.asm
InputName=x86p_i8

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86p_i8.asm
InputName=x86p_i8

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86p_s32.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86p_s32.asm
InputName=x86p_s32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86p_s32.asm
InputName=x86p_s32

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\nasm\x86pScpy.asm

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Release
InputPath=.\nasm\x86pScpy.asm
InputName=x86pScpy

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

# End Custom Build

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

# Begin Custom Build
InputDir=.\nasm
IntDir=.\Debug
InputPath=.\nasm\x86pScpy.asm
InputName=x86pScpy

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasmw -o $(IntDir)\$(InputName).obj -f win32 $(InputDir)\$(InputName).asm

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

# PROP Default_Filter "rc"
# Begin Source File

SOURCE=.\Hermes.rc

!IF  "$(CFG)" == "HermesStatic - Win32 Release"

# ADD BASE RSC /l 0x414
# ADD RSC /l 0x409

!ELSEIF  "$(CFG)" == "HermesStatic - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
