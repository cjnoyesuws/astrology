# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=WPReport - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to WPReport - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "WPReport - Win32 Release" && "$(CFG)" !=\
 "WPReport - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "WPReport.mak" CFG="WPReport - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WPReport - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "WPReport - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "WPReport - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "WPReport - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\WPReport.dll"

CLEAN : 
	-@erase ".\Release\WPReport.dll"
	-@erase ".\Release\TextConv.obj"
	-@erase ".\Release\WPCVT.obj"
	-@erase ".\Release\fileopen.obj"
	-@erase ".\Release\WPReport.lib"
	-@erase ".\Release\WPReport.exp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/WPReport.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WPReport.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/WPReport.pdb" /machine:I386\
 /def:"\wpro\wpStuff\Wpcvt\WPReport.def" /out:"$(OUTDIR)/WPReport.dll"\
 /implib:"$(OUTDIR)/WPReport.lib" 
DEF_FILE= \
	"..\WPReport.def"
LINK32_OBJS= \
	".\Release\TextConv.obj" \
	".\Release\WPCVT.obj" \
	".\Release\fileopen.obj"

"$(OUTDIR)\WPReport.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "WPReport - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\WPReport.dll" "$(OUTDIR)\WPReport.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\WPReport.bsc"
	-@erase ".\Debug\fileopen.sbr"
	-@erase ".\Debug\WPCVT.sbr"
	-@erase ".\Debug\TextConv.sbr"
	-@erase ".\Debug\WPReport.dll"
	-@erase ".\Debug\fileopen.obj"
	-@erase ".\Debug\WPCVT.obj"
	-@erase ".\Debug\TextConv.obj"
	-@erase ".\Debug\WPReport.ilk"
	-@erase ".\Debug\WPReport.lib"
	-@erase ".\Debug\WPReport.exp"
	-@erase ".\Debug\WPReport.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/WPReport.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/WPReport.bsc" 
BSC32_SBRS= \
	".\Debug\fileopen.sbr" \
	".\Debug\WPCVT.sbr" \
	".\Debug\TextConv.sbr"

"$(OUTDIR)\WPReport.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/WPReport.pdb" /debug /machine:I386\
 /def:"\wpro\wpStuff\Wpcvt\WPReport.def" /out:"$(OUTDIR)/WPReport.dll"\
 /implib:"$(OUTDIR)/WPReport.lib" 
DEF_FILE= \
	"..\WPReport.def"
LINK32_OBJS= \
	".\Debug\fileopen.obj" \
	".\Debug\WPCVT.obj" \
	".\Debug\TextConv.obj"

"$(OUTDIR)\WPReport.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "WPReport - Win32 Release"
# Name "WPReport - Win32 Debug"

!IF  "$(CFG)" == "WPReport - Win32 Release"

!ELSEIF  "$(CFG)" == "WPReport - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\wpro\wpStuff\Wpcvt\TextConv.cpp
DEP_CPP_TEXTC=\
	{$(INCLUDE)}"\Scwin32.h"\
	{$(INCLUDE)}"\Sctypes.h"\
	{$(INCLUDE)}"\Wpwp7us.h"\
	".\..\WPCVT.h"\
	

!IF  "$(CFG)" == "WPReport - Win32 Release"


"$(INTDIR)\TextConv.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WPReport - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\TextConv.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TextConv.sbr" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\wpro\wpStuff\Wpcvt\WPCVT.cpp
DEP_CPP_WPCVT=\
	{$(INCLUDE)}"\Scwin32.h"\
	{$(INCLUDE)}"\Sctypes.h"\
	{$(INCLUDE)}"\Wpwp7us.h"\
	".\..\WPCVT.h"\
	

!IF  "$(CFG)" == "WPReport - Win32 Release"


"$(INTDIR)\WPCVT.obj" : $(SOURCE) $(DEP_CPP_WPCVT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WPReport - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\WPCVT.obj" : $(SOURCE) $(DEP_CPP_WPCVT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\WPCVT.sbr" : $(SOURCE) $(DEP_CPP_WPCVT) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\wpro\wpStuff\Wpcvt\fileopen.cpp
DEP_CPP_FILEO=\
	{$(INCLUDE)}"\Scwin32.h"\
	{$(INCLUDE)}"\Sctypes.h"\
	{$(INCLUDE)}"\Wpwp7us.h"\
	".\..\WPCVT.h"\
	

!IF  "$(CFG)" == "WPReport - Win32 Release"


"$(INTDIR)\fileopen.obj" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "WPReport - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\fileopen.obj" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\fileopen.sbr" : $(SOURCE) $(DEP_CPP_FILEO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\wpro\wpStuff\Wpcvt\WPReport.def

!IF  "$(CFG)" == "WPReport - Win32 Release"

!ELSEIF  "$(CFG)" == "WPReport - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
