# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Astroedit - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Astroedit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Astroedit - Win32 Release" && "$(CFG)" !=\
 "Astroedit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Astroedit.mak" CFG="Astroedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Astroedit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Astroedit - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Astroedit - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Astroedit - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Astroedit.exe" "$(OUTDIR)\Astroedit.hlp"

CLEAN : 
	-@erase ".\Release\Astroedit.exe"
	-@erase ".\Release\Sexcodes.obj"
	-@erase ".\Release\Astroedit.pch"
	-@erase ".\Release\Asfil2tx.obj"
	-@erase ".\Release\Opmkprs.obj"
	-@erase ".\Release\Astwperf.obj"
	-@erase ".\Release\astwww.obj"
	-@erase ".\Release\outprnw6.obj"
	-@erase ".\Release\Direc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\Tabout.obj"
	-@erase ".\Release\ConvertData.obj"
	-@erase ".\Release\Tabs.obj"
	-@erase ".\Release\FindText.obj"
	-@erase ".\Release\astwp6.obj"
	-@erase ".\Release\PseudoStyle.obj"
	-@erase ".\Release\Outprnwp.obj"
	-@erase ".\Release\Setpath.obj"
	-@erase ".\Release\AstroeditView.obj"
	-@erase ".\Release\Inifile.obj"
	-@erase ".\Release\Colorfnt.obj"
	-@erase ".\Release\Rwfdata.obj"
	-@erase ".\Release\Decompf.obj"
	-@erase ".\Release\Convopt.obj"
	-@erase ".\Release\Astrtf.obj"
	-@erase ".\Release\Astwstar.obj"
	-@erase ".\Release\Errors.obj"
	-@erase ".\Release\AstroeditDoc.obj"
	-@erase ".\Release\Rtftoast.obj"
	-@erase ".\Release\ReportStyles.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\Strclip.obj"
	-@erase ".\Release\Astami.obj"
	-@erase ".\Release\Asfil2txsmp.obj"
	-@erase ".\Release\Repstyle.obj"
	-@erase ".\Release\Astroedit.obj"
	-@erase ".\Release\Charcons.obj"
	-@erase ".\Release\Words.obj"
	-@erase ".\Release\Wpintl.obj"
	-@erase ".\Release\Loadcovr.obj"
	-@erase ".\Release\Fptr.obj"
	-@erase ".\Release\Astroedit.res"
	-@erase ".\Release\Astroedit.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Astroedit.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Astroedit.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Astroedit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Astroedit.pdb" /machine:I386 /out:"$(OUTDIR)/Astroedit.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sexcodes.obj" \
	"$(INTDIR)/Asfil2tx.obj" \
	"$(INTDIR)/Opmkprs.obj" \
	"$(INTDIR)/Astwperf.obj" \
	"$(INTDIR)/astwww.obj" \
	"$(INTDIR)/outprnw6.obj" \
	"$(INTDIR)/Direc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Tabout.obj" \
	"$(INTDIR)/ConvertData.obj" \
	"$(INTDIR)/Tabs.obj" \
	"$(INTDIR)/FindText.obj" \
	"$(INTDIR)/astwp6.obj" \
	"$(INTDIR)/PseudoStyle.obj" \
	"$(INTDIR)/Outprnwp.obj" \
	"$(INTDIR)/Setpath.obj" \
	"$(INTDIR)/AstroeditView.obj" \
	"$(INTDIR)/Inifile.obj" \
	"$(INTDIR)/Colorfnt.obj" \
	"$(INTDIR)/Rwfdata.obj" \
	"$(INTDIR)/Decompf.obj" \
	"$(INTDIR)/Convopt.obj" \
	"$(INTDIR)/Astrtf.obj" \
	"$(INTDIR)/Astwstar.obj" \
	"$(INTDIR)/Errors.obj" \
	"$(INTDIR)/AstroeditDoc.obj" \
	"$(INTDIR)/Rtftoast.obj" \
	"$(INTDIR)/ReportStyles.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Strclip.obj" \
	"$(INTDIR)/Astami.obj" \
	"$(INTDIR)/Asfil2txsmp.obj" \
	"$(INTDIR)/Repstyle.obj" \
	"$(INTDIR)/Astroedit.obj" \
	"$(INTDIR)/Charcons.obj" \
	"$(INTDIR)/Words.obj" \
	"$(INTDIR)/Wpintl.obj" \
	"$(INTDIR)/Loadcovr.obj" \
	"$(INTDIR)/Fptr.obj" \
	"$(INTDIR)/Astroedit.res"

"$(OUTDIR)\Astroedit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Astroedit - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Astroedit.exe" "$(OUTDIR)\Astroedit.hlp"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Astroedit.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Astroedit.exe"
	-@erase ".\Debug\ReportStyles.obj"
	-@erase ".\Debug\Sexcodes.obj"
	-@erase ".\Debug\Astwstar.obj"
	-@erase ".\Debug\Asfil2tx.obj"
	-@erase ".\Debug\Direc.obj"
	-@erase ".\Debug\Setpath.obj"
	-@erase ".\Debug\Rtftoast.obj"
	-@erase ".\Debug\Opmkprs.obj"
	-@erase ".\Debug\Astwperf.obj"
	-@erase ".\Debug\ConvertData.obj"
	-@erase ".\Debug\Asfil2txsmp.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\Repstyle.obj"
	-@erase ".\Debug\PseudoStyle.obj"
	-@erase ".\Debug\Loadcovr.obj"
	-@erase ".\Debug\AstroeditView.obj"
	-@erase ".\Debug\Wpintl.obj"
	-@erase ".\Debug\FindText.obj"
	-@erase ".\Debug\Fptr.obj"
	-@erase ".\Debug\Astrtf.obj"
	-@erase ".\Debug\Errors.obj"
	-@erase ".\Debug\Inifile.obj"
	-@erase ".\Debug\Rwfdata.obj"
	-@erase ".\Debug\Decompf.obj"
	-@erase ".\Debug\Convopt.obj"
	-@erase ".\Debug\outprnw6.obj"
	-@erase ".\Debug\astwww.obj"
	-@erase ".\Debug\Astami.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\Tabout.obj"
	-@erase ".\Debug\Words.obj"
	-@erase ".\Debug\Strclip.obj"
	-@erase ".\Debug\Tabs.obj"
	-@erase ".\Debug\Astroedit.obj"
	-@erase ".\Debug\Outprnwp.obj"
	-@erase ".\Debug\Charcons.obj"
	-@erase ".\Debug\astwp6.obj"
	-@erase ".\Debug\Colorfnt.obj"
	-@erase ".\Debug\AstroeditDoc.obj"
	-@erase ".\Debug\Astroedit.res"
	-@erase ".\Debug\Astroedit.ilk"
	-@erase ".\Debug\Astroedit.pdb"
	-@erase ".\Debug\Astroedit.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Astroedit.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Astroedit.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Astroedit.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Astroedit.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Astroedit.exe" 
LINK32_OBJS= \
	"$(INTDIR)/ReportStyles.obj" \
	"$(INTDIR)/Sexcodes.obj" \
	"$(INTDIR)/Astwstar.obj" \
	"$(INTDIR)/Asfil2tx.obj" \
	"$(INTDIR)/Direc.obj" \
	"$(INTDIR)/Setpath.obj" \
	"$(INTDIR)/Rtftoast.obj" \
	"$(INTDIR)/Opmkprs.obj" \
	"$(INTDIR)/Astwperf.obj" \
	"$(INTDIR)/ConvertData.obj" \
	"$(INTDIR)/Asfil2txsmp.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Repstyle.obj" \
	"$(INTDIR)/PseudoStyle.obj" \
	"$(INTDIR)/Loadcovr.obj" \
	"$(INTDIR)/AstroeditView.obj" \
	"$(INTDIR)/Wpintl.obj" \
	"$(INTDIR)/FindText.obj" \
	"$(INTDIR)/Fptr.obj" \
	"$(INTDIR)/Astrtf.obj" \
	"$(INTDIR)/Errors.obj" \
	"$(INTDIR)/Inifile.obj" \
	"$(INTDIR)/Rwfdata.obj" \
	"$(INTDIR)/Decompf.obj" \
	"$(INTDIR)/Convopt.obj" \
	"$(INTDIR)/outprnw6.obj" \
	"$(INTDIR)/astwww.obj" \
	"$(INTDIR)/Astami.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Tabout.obj" \
	"$(INTDIR)/Words.obj" \
	"$(INTDIR)/Strclip.obj" \
	"$(INTDIR)/Tabs.obj" \
	"$(INTDIR)/Astroedit.obj" \
	"$(INTDIR)/Outprnwp.obj" \
	"$(INTDIR)/Charcons.obj" \
	"$(INTDIR)/astwp6.obj" \
	"$(INTDIR)/Colorfnt.obj" \
	"$(INTDIR)/AstroeditDoc.obj" \
	"$(INTDIR)/Astroedit.res"

"$(OUTDIR)\Astroedit.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Astroedit - Win32 Release"
# Name "Astroedit - Win32 Debug"

!IF  "$(CFG)" == "Astroedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Astroedit - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Astroedit - Win32 Release"

!ELSEIF  "$(CFG)" == "Astroedit - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Astroedit.cpp
DEP_CPP_ASTRO=\
	".\StdAfx.h"\
	".\Astroedit.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	".\AstroeditDoc.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	".\AstroeditView.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Utlduad.h"\
	".\..\inc\paths.hpp"\
	

"$(INTDIR)\Astroedit.obj" : $(SOURCE) $(DEP_CPP_ASTRO) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Astroedit - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Astroedit.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Astroedit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Astroedit - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Astroedit.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Astroedit.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\Astroedit.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AstroeditDoc.cpp
DEP_CPP_ASTROE=\
	".\StdAfx.h"\
	".\Astroedit.h"\
	".\AstroeditDoc.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Coverdat.hpp"\
	{$(INCLUDE)}"\Asfil2tx.hpp"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\AstroeditDoc.obj" : $(SOURCE) $(DEP_CPP_ASTROE) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AstroeditView.cpp
DEP_CPP_ASTROED=\
	".\StdAfx.h"\
	".\Astroedit.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	".\reportstyles.h"\
	".\pseudostyle.h"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\ConvertData.h"\
	".\AstroeditDoc.h"\
	".\AstroeditView.h"\
	".\findtext.h"\
	

"$(INTDIR)\AstroeditView.obj" : $(SOURCE) $(DEP_CPP_ASTROED) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Astroedit.rc
DEP_RSC_ASTROEDI=\
	".\res\Astroedit.ico"\
	".\res\AstroeditDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\Astroedit.rc2"\
	

"$(INTDIR)\Astroedit.res" : $(SOURCE) $(DEP_RSC_ASTROEDI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\Astroedit.hpj

!IF  "$(CFG)" == "Astroedit - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Astroedit
InputPath=.\hlp\Astroedit.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "Astroedit - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Astroedit
InputPath=.\hlp\Astroedit.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConvertData.cpp
DEP_CPP_CONVE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	{$(INCLUDE)}"\Attrib.h"\
	".\pseudostyle.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	".\reportstyles.h"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	{$(INCLUDE)}"\ConvertData.h"\
	

"$(INTDIR)\ConvertData.obj" : $(SOURCE) $(DEP_CPP_CONVE) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FindText.cpp
DEP_CPP_FINDT=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	".\findtext.h"\
	

"$(INTDIR)\FindText.obj" : $(SOURCE) $(DEP_CPP_FINDT) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PseudoStyle.cpp
DEP_CPP_PSEUD=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	{$(INCLUDE)}"\Attrib.h"\
	".\pseudostyle.h"\
	

"$(INTDIR)\PseudoStyle.obj" : $(SOURCE) $(DEP_CPP_PSEUD) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ReportStyles.cpp
DEP_CPP_REPOR=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	".\reportstyles.h"\
	

"$(INTDIR)\ReportStyles.obj" : $(SOURCE) $(DEP_CPP_REPOR) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Rtftoast.cpp
DEP_CPP_RTFTO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Rtf.h"\
	{$(INCLUDE)}"\Errors.fns"\
	

"$(INTDIR)\Rtftoast.obj" : $(SOURCE) $(DEP_CPP_RTFTO) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Cover\Loadcovr.cpp
DEP_CPP_LOADC=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Coverdat.hpp"\
	".\..\inc\paths.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Loadcovr.obj" : $(SOURCE) $(DEP_CPP_LOADC) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Dlg\Repstyle.cpp
DEP_CPP_REPST=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Repstyle.obj" : $(SOURCE) $(DEP_CPP_REPST) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Dlg\Convopt.cpp
DEP_CPP_CONVO=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Convopt.obj" : $(SOURCE) $(DEP_CPP_CONVO) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Dlg\Colorfnt.cpp
DEP_CPP_COLOR=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Colorfnt.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Wpintl.cpp
DEP_CPP_WPINT=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Wpintl.obj" : $(SOURCE) $(DEP_CPP_WPINT) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Asfil2txsmp.cpp
DEP_CPP_ASFIL=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	".\..\inc\paths.hpp"\
	{$(INCLUDE)}"\Coverdat.hpp"\
	{$(INCLUDE)}"\Asfil2tx.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Asfil2txsmp.obj" : $(SOURCE) $(DEP_CPP_ASFIL) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astami.cpp
DEP_CPP_ASTAM=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Astami.obj" : $(SOURCE) $(DEP_CPP_ASTAM) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astrtf.cpp
DEP_CPP_ASTRT=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Astrtf.obj" : $(SOURCE) $(DEP_CPP_ASTRT) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\astwp6.cpp
DEP_CPP_ASTWP=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\astwp6.obj" : $(SOURCE) $(DEP_CPP_ASTWP) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astwperf.cpp
DEP_CPP_ASTWPE=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Astwperf.obj" : $(SOURCE) $(DEP_CPP_ASTWPE) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astwstar.cpp
DEP_CPP_ASTWS=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Astwstar.obj" : $(SOURCE) $(DEP_CPP_ASTWS) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\astwww.cpp
DEP_CPP_ASTWW=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\astwww.obj" : $(SOURCE) $(DEP_CPP_ASTWW) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Decompf.cpp
DEP_CPP_DECOM=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Decompf.obj" : $(SOURCE) $(DEP_CPP_DECOM) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Opmkprs.cpp
DEP_CPP_OPMKP=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Opmkprs.obj" : $(SOURCE) $(DEP_CPP_OPMKP) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\outprnw6.cpp
DEP_CPP_OUTPR=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\outprnw6.obj" : $(SOURCE) $(DEP_CPP_OUTPR) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Outprnwp.cpp
DEP_CPP_OUTPRN=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Outprnwp.obj" : $(SOURCE) $(DEP_CPP_OUTPRN) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Tabout.cpp
DEP_CPP_TABOU=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Tabout.obj" : $(SOURCE) $(DEP_CPP_TABOU) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Asfil2tx.cpp
DEP_CPP_ASFIL2=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astrow.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\Coverdat.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\ConvertData.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	".\..\inc\paths.hpp"\
	{$(INCLUDE)}"\filelst.hpp"\
	{$(INCLUDE)}"\Asfil2tx.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Asfil2tx.obj" : $(SOURCE) $(DEP_CPP_ASFIL2) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Rwfdata.cpp
DEP_CPP_RWFDA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Output.fns"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Errors.fns"\
	

"$(INTDIR)\Rwfdata.obj" : $(SOURCE) $(DEP_CPP_RWFDA) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Direc.cpp
DEP_CPP_DIREC=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	".\..\inc\paths.hpp"\
	

"$(INTDIR)\Direc.obj" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Errors.cpp
DEP_CPP_ERROR=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Errors.obj" : $(SOURCE) $(DEP_CPP_ERROR) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Fptr.cpp
DEP_CPP_FPTR_=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Fptr.obj" : $(SOURCE) $(DEP_CPP_FPTR_) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Inifile.cpp
DEP_CPP_INIFI=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Inifile.obj" : $(SOURCE) $(DEP_CPP_INIFI) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Charcons.cpp
DEP_CPP_CHARC=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Charcons.obj" : $(SOURCE) $(DEP_CPP_CHARC) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Setpath.cpp
DEP_CPP_SETPA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	".\..\inc\paths.hpp"\
	

"$(INTDIR)\Setpath.obj" : $(SOURCE) $(DEP_CPP_SETPA) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Sexcodes.cpp
DEP_CPP_SEXCO=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	

"$(INTDIR)\Sexcodes.obj" : $(SOURCE) $(DEP_CPP_SEXCO) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Strclip.cpp
DEP_CPP_STRCL=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Strclip.obj" : $(SOURCE) $(DEP_CPP_STRCL) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Tabs.cpp
DEP_CPP_TABS_=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Tabs.hpp"\
	

"$(INTDIR)\Tabs.obj" : $(SOURCE) $(DEP_CPP_TABS_) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Words.cpp
DEP_CPP_WORDS=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Words.obj" : $(SOURCE) $(DEP_CPP_WORDS) "$(INTDIR)"\
 "$(INTDIR)\Astroedit.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
