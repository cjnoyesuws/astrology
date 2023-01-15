# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Astroview - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Astroview - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Astroview - Win32 Release" && "$(CFG)" !=\
 "Astroview - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Astroview.mak" CFG="Astroview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Astroview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Astroview - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Astroview - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Astroview - Win32 Release"

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

ALL : "$(OUTDIR)\Astroview.exe" "$(OUTDIR)\Astroview.hlp"

CLEAN : 
	-@erase ".\Release\Astroview.exe"
	-@erase ".\Release\Pageopt.obj"
	-@erase ".\Release\Astroview.pch"
	-@erase ".\Release\Opmkprs.obj"
	-@erase ".\Release\ParaEdit.obj"
	-@erase ".\Release\outprnw6.obj"
	-@erase ".\Release\Wrfdata.obj"
	-@erase ".\Release\ODListBox.obj"
	-@erase ".\Release\Txtsrch.obj"
	-@erase ".\Release\Repstyle.obj"
	-@erase ".\Release\Words.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\PageSetp.obj"
	-@erase ".\Release\ReportStyles.obj"
	-@erase ".\Release\Outprnwp.obj"
	-@erase ".\Release\Charcons.obj"
	-@erase ".\Release\Fptr.obj"
	-@erase ".\Release\Virtsave.obj"
	-@erase ".\Release\Wpintl.obj"
	-@erase ".\Release\Setpath.obj"
	-@erase ".\Release\AstroviewView.obj"
	-@erase ".\Release\Sexcodes.obj"
	-@erase ".\Release\Astwstar.obj"
	-@erase ".\Release\Asfil2tx.obj"
	-@erase ".\Release\Rwfdata.obj"
	-@erase ".\Release\Convopt.obj"
	-@erase ".\Release\Astrtf.obj"
	-@erase ".\Release\Direc.obj"
	-@erase ".\Release\Astwperf.obj"
	-@erase ".\Release\Virttext.obj"
	-@erase ".\Release\AstroviewDoc.obj"
	-@erase ".\Release\Errors.obj"
	-@erase ".\Release\Uis2dsk.obj"
	-@erase ".\Release\ConvertData.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\astwww.obj"
	-@erase ".\Release\Astami.obj"
	-@erase ".\Release\Strclip.obj"
	-@erase ".\Release\PseudoStyle.obj"
	-@erase ".\Release\Tabs.obj"
	-@erase ".\Release\Tabout.obj"
	-@erase ".\Release\Loadcovr.obj"
	-@erase ".\Release\FindText.obj"
	-@erase ".\Release\Inifile.obj"
	-@erase ".\Release\astwp6.obj"
	-@erase ".\Release\Decompf.obj"
	-@erase ".\Release\Colorfnt.obj"
	-@erase ".\Release\Compress.obj"
	-@erase ".\Release\Astroview.obj"
	-@erase ".\Release\Astroview.res"
	-@erase ".\Release\Astroview.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D " USEDLL" /D " DELUXE" /D " PRO" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D " USEDLL" /D " DELUXE" /D " PRO"\
 /Fp"$(INTDIR)/Astroview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Astroview.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Astroview.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Astroview.pdb" /machine:I386 /out:"$(OUTDIR)/Astroview.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Pageopt.obj" \
	"$(INTDIR)/Opmkprs.obj" \
	"$(INTDIR)/ParaEdit.obj" \
	"$(INTDIR)/outprnw6.obj" \
	"$(INTDIR)/Wrfdata.obj" \
	"$(INTDIR)/ODListBox.obj" \
	"$(INTDIR)/Txtsrch.obj" \
	"$(INTDIR)/Repstyle.obj" \
	"$(INTDIR)/Words.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/PageSetp.obj" \
	"$(INTDIR)/ReportStyles.obj" \
	"$(INTDIR)/Outprnwp.obj" \
	"$(INTDIR)/Charcons.obj" \
	"$(INTDIR)/Fptr.obj" \
	"$(INTDIR)/Virtsave.obj" \
	"$(INTDIR)/Wpintl.obj" \
	"$(INTDIR)/Setpath.obj" \
	"$(INTDIR)/AstroviewView.obj" \
	"$(INTDIR)/Sexcodes.obj" \
	"$(INTDIR)/Astwstar.obj" \
	"$(INTDIR)/Asfil2tx.obj" \
	"$(INTDIR)/Rwfdata.obj" \
	"$(INTDIR)/Convopt.obj" \
	"$(INTDIR)/Astrtf.obj" \
	"$(INTDIR)/Direc.obj" \
	"$(INTDIR)/Astwperf.obj" \
	"$(INTDIR)/Virttext.obj" \
	"$(INTDIR)/AstroviewDoc.obj" \
	"$(INTDIR)/Errors.obj" \
	"$(INTDIR)/Uis2dsk.obj" \
	"$(INTDIR)/ConvertData.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/astwww.obj" \
	"$(INTDIR)/Astami.obj" \
	"$(INTDIR)/Strclip.obj" \
	"$(INTDIR)/PseudoStyle.obj" \
	"$(INTDIR)/Tabs.obj" \
	"$(INTDIR)/Tabout.obj" \
	"$(INTDIR)/Loadcovr.obj" \
	"$(INTDIR)/FindText.obj" \
	"$(INTDIR)/Inifile.obj" \
	"$(INTDIR)/astwp6.obj" \
	"$(INTDIR)/Decompf.obj" \
	"$(INTDIR)/Colorfnt.obj" \
	"$(INTDIR)/Compress.obj" \
	"$(INTDIR)/Astroview.obj" \
	"$(INTDIR)/Astroview.res"

"$(OUTDIR)\Astroview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Astroview - Win32 Debug"

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

ALL : "$(OUTDIR)\Astroview.exe" "$(OUTDIR)\Astroview.hlp"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Astroview.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Astroview.exe"
	-@erase ".\Debug\Sexcodes.obj"
	-@erase ".\Debug\Asfil2tx.obj"
	-@erase ".\Debug\Opmkprs.obj"
	-@erase ".\Debug\AstroviewView.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\Astwperf.obj"
	-@erase ".\Debug\Astami.obj"
	-@erase ".\Debug\Wrfdata.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\outprnw6.obj"
	-@erase ".\Debug\Strclip.obj"
	-@erase ".\Debug\Words.obj"
	-@erase ".\Debug\Wpintl.obj"
	-@erase ".\Debug\Astroview.obj"
	-@erase ".\Debug\FindText.obj"
	-@erase ".\Debug\Outprnwp.obj"
	-@erase ".\Debug\ReportStyles.obj"
	-@erase ".\Debug\ODListBox.obj"
	-@erase ".\Debug\Setpath.obj"
	-@erase ".\Debug\Pageopt.obj"
	-@erase ".\Debug\Colorfnt.obj"
	-@erase ".\Debug\Compress.obj"
	-@erase ".\Debug\astwww.obj"
	-@erase ".\Debug\Convopt.obj"
	-@erase ".\Debug\Direc.obj"
	-@erase ".\Debug\Astwstar.obj"
	-@erase ".\Debug\Txtsrch.obj"
	-@erase ".\Debug\ParaEdit.obj"
	-@erase ".\Debug\Uis2dsk.obj"
	-@erase ".\Debug\Tabout.obj"
	-@erase ".\Debug\Virttext.obj"
	-@erase ".\Debug\AstroviewDoc.obj"
	-@erase ".\Debug\ConvertData.obj"
	-@erase ".\Debug\astwp6.obj"
	-@erase ".\Debug\Repstyle.obj"
	-@erase ".\Debug\PageSetp.obj"
	-@erase ".\Debug\PseudoStyle.obj"
	-@erase ".\Debug\Charcons.obj"
	-@erase ".\Debug\Tabs.obj"
	-@erase ".\Debug\Loadcovr.obj"
	-@erase ".\Debug\Inifile.obj"
	-@erase ".\Debug\Astrtf.obj"
	-@erase ".\Debug\Fptr.obj"
	-@erase ".\Debug\Virtsave.obj"
	-@erase ".\Debug\Rwfdata.obj"
	-@erase ".\Debug\Errors.obj"
	-@erase ".\Debug\Decompf.obj"
	-@erase ".\Debug\Astroview.res"
	-@erase ".\Debug\Astroview.ilk"
	-@erase ".\Debug\Astroview.pdb"
	-@erase ".\Debug\Astroview.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D " USEDLL" /D " DELUXE" /D " PRO" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D " USEDLL" /D " DELUXE" /D " PRO"\
 /Fp"$(INTDIR)/Astroview.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Astroview.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Astroview.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Astroview.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Astroview.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Sexcodes.obj" \
	"$(INTDIR)/Asfil2tx.obj" \
	"$(INTDIR)/Opmkprs.obj" \
	"$(INTDIR)/AstroviewView.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Astwperf.obj" \
	"$(INTDIR)/Astami.obj" \
	"$(INTDIR)/Wrfdata.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/outprnw6.obj" \
	"$(INTDIR)/Strclip.obj" \
	"$(INTDIR)/Words.obj" \
	"$(INTDIR)/Wpintl.obj" \
	"$(INTDIR)/Astroview.obj" \
	"$(INTDIR)/FindText.obj" \
	"$(INTDIR)/Outprnwp.obj" \
	"$(INTDIR)/ReportStyles.obj" \
	"$(INTDIR)/ODListBox.obj" \
	"$(INTDIR)/Setpath.obj" \
	"$(INTDIR)/Pageopt.obj" \
	"$(INTDIR)/Colorfnt.obj" \
	"$(INTDIR)/Compress.obj" \
	"$(INTDIR)/astwww.obj" \
	"$(INTDIR)/Convopt.obj" \
	"$(INTDIR)/Direc.obj" \
	"$(INTDIR)/Astwstar.obj" \
	"$(INTDIR)/Txtsrch.obj" \
	"$(INTDIR)/ParaEdit.obj" \
	"$(INTDIR)/Uis2dsk.obj" \
	"$(INTDIR)/Tabout.obj" \
	"$(INTDIR)/Virttext.obj" \
	"$(INTDIR)/AstroviewDoc.obj" \
	"$(INTDIR)/ConvertData.obj" \
	"$(INTDIR)/astwp6.obj" \
	"$(INTDIR)/Repstyle.obj" \
	"$(INTDIR)/PageSetp.obj" \
	"$(INTDIR)/PseudoStyle.obj" \
	"$(INTDIR)/Charcons.obj" \
	"$(INTDIR)/Tabs.obj" \
	"$(INTDIR)/Loadcovr.obj" \
	"$(INTDIR)/Inifile.obj" \
	"$(INTDIR)/Astrtf.obj" \
	"$(INTDIR)/Fptr.obj" \
	"$(INTDIR)/Virtsave.obj" \
	"$(INTDIR)/Rwfdata.obj" \
	"$(INTDIR)/Errors.obj" \
	"$(INTDIR)/Decompf.obj" \
	"$(INTDIR)/Astroview.res"

"$(OUTDIR)\Astroview.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Astroview - Win32 Release"
# Name "Astroview - Win32 Debug"

!IF  "$(CFG)" == "Astroview - Win32 Release"

!ELSEIF  "$(CFG)" == "Astroview - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Astroview - Win32 Release"

!ELSEIF  "$(CFG)" == "Astroview - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Astroview.cpp
DEP_CPP_ASTRO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Utlduad.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Virttext.hpp"\
	".\AstroviewDoc.h"\
	".\AstroviewView.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\Astroview.obj" : $(SOURCE) $(DEP_CPP_ASTRO) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Astroview - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D " USEDLL" /D " DELUXE" /D " PRO"\
 /Fp"$(INTDIR)/Astroview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Astroview.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Astroview - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D " USEDLL" /D " DELUXE" /D " PRO"\
 /Fp"$(INTDIR)/Astroview.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Astroview.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AstroviewDoc.cpp
DEP_CPP_ASTROV=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astrow.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Virttext.hpp"\
	".\AstroviewDoc.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\AstroviewDoc.obj" : $(SOURCE) $(DEP_CPP_ASTROV) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AstroviewView.cpp
DEP_CPP_ASTROVI=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astrow.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Virttext.hpp"\
	".\AstroviewDoc.h"\
	".\AstroviewView.h"\
	".\FindText.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\ReportStyles.h"\
	{$(INCLUDE)}"\Pageopt.hpp"\
	".\PageSetp.h"\
	{$(INCLUDE)}"\Attrib.h"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\ConvertData.h"\
	{$(INCLUDE)}"\Coverdat.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Prtrdrv.hpp"\
	{$(INCLUDE)}"\Asfil2tx.hpp"\
	".\paraedit.h"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\AstroviewView.obj" : $(SOURCE) $(DEP_CPP_ASTROVI) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Astroview.rc
DEP_RSC_ASTROVIE=\
	".\res\Astroview.ico"\
	".\res\AstroviewDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\Astroview.rc2"\
	

"$(INTDIR)\Astroview.res" : $(SOURCE) $(DEP_RSC_ASTROVIE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\Astroview.hpj

!IF  "$(CFG)" == "Astroview - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=Astroview
InputPath=.\hlp\Astroview.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "Astroview - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=Astroview
InputPath=.\hlp\Astroview.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Dlg\Repstyle.cpp
DEP_CPP_REPST=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Repstyle.obj" : $(SOURCE) $(DEP_CPP_REPST) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Dlg\Colorfnt.cpp
DEP_CPP_COLOR=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Colorfnt.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Words.cpp
DEP_CPP_WORDS=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Words.obj" : $(SOURCE) $(DEP_CPP_WORDS) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Direc.cpp
DEP_CPP_DIREC=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\Direc.obj" : $(SOURCE) $(DEP_CPP_DIREC) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Inifile.cpp
DEP_CPP_INIFI=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Inifile.obj" : $(SOURCE) $(DEP_CPP_INIFI) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Setpath.cpp
DEP_CPP_SETPA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\Setpath.obj" : $(SOURCE) $(DEP_CPP_SETPA) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Strclip.cpp
DEP_CPP_STRCL=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Strclip.obj" : $(SOURCE) $(DEP_CPP_STRCL) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Virtsave.cpp
DEP_CPP_VIRTS=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Virttext.hpp"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Virtsave.obj" : $(SOURCE) $(DEP_CPP_VIRTS) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Virttext.cpp
DEP_CPP_VIRTT=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Virttext.hpp"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Virttext.obj" : $(SOURCE) $(DEP_CPP_VIRTT) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Charcons.cpp
DEP_CPP_CHARC=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Charcons.obj" : $(SOURCE) $(DEP_CPP_CHARC) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Uis2dsk.cpp
DEP_CPP_UIS2D=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Dbstruct.h"\
	{$(INCLUDE)}"\Fptr.h"\
	

"$(INTDIR)\Uis2dsk.obj" : $(SOURCE) $(DEP_CPP_UIS2D) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\FindText.cpp
DEP_CPP_FINDT=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astrow.h"\
	".\FindText.h"\
	

"$(INTDIR)\FindText.obj" : $(SOURCE) $(DEP_CPP_FINDT) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Txtsrch.cpp
DEP_CPP_TXTSR=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Tabs.hpp"\
	{$(INCLUDE)}"\Sexcodes.hpp"\
	{$(INCLUDE)}"\Virttext.hpp"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\Txtsrch.obj" : $(SOURCE) $(DEP_CPP_TXTSR) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Wrfdata.cpp
DEP_CPP_WRFDA=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Dataext.h"\
	{$(INCLUDE)}"\Output.fns"\
	

"$(INTDIR)\Wrfdata.obj" : $(SOURCE) $(DEP_CPP_WRFDA) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Cover\Compress.cpp
DEP_CPP_COMPR=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Compress.obj" : $(SOURCE) $(DEP_CPP_COMPR) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Astroedit\ReportStyles.cpp
DEP_CPP_REPOR=\
	".\..\Astroedit\stdafx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\ReportStyles.h"\
	

"$(INTDIR)\ReportStyles.obj" : $(SOURCE) $(DEP_CPP_REPOR) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Dlg\Pageopt.cpp
DEP_CPP_PAGEO=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Pageopt.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Pageopt.obj" : $(SOURCE) $(DEP_CPP_PAGEO) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageSetp.cpp
DEP_CPP_PAGES=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astrow.h"\
	{$(INCLUDE)}"\Pageopt.hpp"\
	".\PageSetp.h"\
	

"$(INTDIR)\PageSetp.obj" : $(SOURCE) $(DEP_CPP_PAGES) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


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
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Astroedit\ConvertData.cpp
DEP_CPP_CONVE=\
	".\..\Astroedit\stdafx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	{$(INCLUDE)}"\Attrib.h"\
	".\..\Astroedit\pseudostyle.h"\
	{$(INCLUDE)}"\Repstyle.hpp"\
	{$(INCLUDE)}"\ReportStyles.h"\
	{$(INCLUDE)}"\Convopt.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	{$(INCLUDE)}"\ConvertData.h"\
	

"$(INTDIR)\ConvertData.obj" : $(SOURCE) $(DEP_CPP_CONVE) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Astroedit\PseudoStyle.cpp
DEP_CPP_PSEUD=\
	".\..\Astroedit\stdafx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	{$(INCLUDE)}"\Attrib.h"\
	".\..\Astroedit\pseudostyle.h"\
	

"$(INTDIR)\PseudoStyle.obj" : $(SOURCE) $(DEP_CPP_PSEUD) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


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
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Loadcovr.obj" : $(SOURCE) $(DEP_CPP_LOADC) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Wpintl.cpp
DEP_CPP_WPINT=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Wpintl.obj" : $(SOURCE) $(DEP_CPP_WPINT) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
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
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Wpconv\Asfil2tx.cpp
DEP_CPP_ASFIL=\
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
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\filelst.hpp"\
	{$(INCLUDE)}"\Asfil2tx.hpp"\
	{$(INCLUDE)}"\Txtdrv.h"\
	

"$(INTDIR)\Asfil2tx.obj" : $(SOURCE) $(DEP_CPP_ASFIL) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ParaEdit.cpp
DEP_CPP_PARAE=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astrow.h"\
	".\paraedit.h"\
	

"$(INTDIR)\ParaEdit.obj" : $(SOURCE) $(DEP_CPP_PARAE) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ODListBox.cpp
DEP_CPP_ODLIS=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Astroview.h"\
	".\ODListBox.h"\
	

"$(INTDIR)\ODListBox.obj" : $(SOURCE) $(DEP_CPP_ODLIS) "$(INTDIR)"\
 "$(INTDIR)\Astroview.pch"


# End Source File
# End Target
# End Project
################################################################################
