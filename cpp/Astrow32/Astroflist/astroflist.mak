# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=astroflist - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to astroflist - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "astroflist - Win32 Release" && "$(CFG)" !=\
 "astroflist - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "astroflist.mak" CFG="astroflist - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "astroflist - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "astroflist - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "astroflist - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "astroflist - Win32 Release"

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

ALL : "$(OUTDIR)\astroflist.exe"

CLEAN : 
	-@erase ".\Release\astroflist.exe"
	-@erase ".\Release\astroflistDoc.obj"
	-@erase ".\Release\astroflist.pch"
	-@erase ".\Release\Fptr.obj"
	-@erase ".\Release\Quelist.obj"
	-@erase ".\Release\Quesel.obj"
	-@erase ".\Release\Setpath.obj"
	-@erase ".\Release\FileKillDlg.obj"
	-@erase ".\Release\Direc.obj"
	-@erase ".\Release\Charcons.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\Quefind.obj"
	-@erase ".\Release\Quinsdel.obj"
	-@erase ".\Release\Errors.obj"
	-@erase ".\Release\Doque.obj"
	-@erase ".\Release\Uis2dsk.obj"
	-@erase ".\Release\astroflist.obj"
	-@erase ".\Release\Queuio.obj"
	-@erase ".\Release\Queutil.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\Strclip.obj"
	-@erase ".\Release\astroflistView.obj"
	-@erase ".\Release\Inifile.obj"
	-@erase ".\Release\FileEditDlg.obj"
	-@erase ".\Release\Queitm.obj"
	-@erase ".\Release\Scanfile.obj"
	-@erase ".\Release\FileNameDlg.obj"
	-@erase ".\Release\Directories.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\Sortfils.obj"
	-@erase ".\Release\astroflist.res"
	-@erase ".\Release\Splash.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D " DELUXE" /D " PRO" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D " DELUXE" /D " PRO" /Fp"$(INTDIR)/astroflist.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/astroflist.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/astroflist.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/astroflist.pdb" /machine:I386 /out:"$(OUTDIR)/astroflist.exe" 
LINK32_OBJS= \
	"$(INTDIR)/astroflistDoc.obj" \
	"$(INTDIR)/Fptr.obj" \
	"$(INTDIR)/Quelist.obj" \
	"$(INTDIR)/Quesel.obj" \
	"$(INTDIR)/Setpath.obj" \
	"$(INTDIR)/FileKillDlg.obj" \
	"$(INTDIR)/Direc.obj" \
	"$(INTDIR)/Charcons.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/Quefind.obj" \
	"$(INTDIR)/Quinsdel.obj" \
	"$(INTDIR)/Errors.obj" \
	"$(INTDIR)/Doque.obj" \
	"$(INTDIR)/Uis2dsk.obj" \
	"$(INTDIR)/astroflist.obj" \
	"$(INTDIR)/Queuio.obj" \
	"$(INTDIR)/Queutil.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Strclip.obj" \
	"$(INTDIR)/astroflistView.obj" \
	"$(INTDIR)/Inifile.obj" \
	"$(INTDIR)/FileEditDlg.obj" \
	"$(INTDIR)/Queitm.obj" \
	"$(INTDIR)/Scanfile.obj" \
	"$(INTDIR)/FileNameDlg.obj" \
	"$(INTDIR)/Directories.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/Sortfils.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/astroflist.res"

"$(OUTDIR)\astroflist.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "astroflist - Win32 Debug"

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

ALL : "$(OUTDIR)\astroflist.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\astroflist.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\astroflist.exe"
	-@erase ".\Debug\astroflistView.obj"
	-@erase ".\Debug\Doque.obj"
	-@erase ".\Debug\Fptr.obj"
	-@erase ".\Debug\Quelist.obj"
	-@erase ".\Debug\Setpath.obj"
	-@erase ".\Debug\Queitm.obj"
	-@erase ".\Debug\Queuio.obj"
	-@erase ".\Debug\Quinsdel.obj"
	-@erase ".\Debug\Uis2dsk.obj"
	-@erase ".\Debug\astroflist.obj"
	-@erase ".\Debug\Sortfils.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\FileEditDlg.obj"
	-@erase ".\Debug\Quesel.obj"
	-@erase ".\Debug\FileNameDlg.obj"
	-@erase ".\Debug\Inifile.obj"
	-@erase ".\Debug\Charcons.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\Directories.obj"
	-@erase ".\Debug\Quefind.obj"
	-@erase ".\Debug\Errors.obj"
	-@erase ".\Debug\Scanfile.obj"
	-@erase ".\Debug\Queutil.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\Strclip.obj"
	-@erase ".\Debug\astroflistDoc.obj"
	-@erase ".\Debug\Direc.obj"
	-@erase ".\Debug\FileKillDlg.obj"
	-@erase ".\Debug\astroflist.res"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\astroflist.ilk"
	-@erase ".\Debug\astroflist.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D " DELUXE" /D " PRO" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D " DELUXE" /D " PRO" /Fp"$(INTDIR)/astroflist.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/astroflist.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/astroflist.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/astroflist.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/astroflist.exe" 
LINK32_OBJS= \
	"$(INTDIR)/astroflistView.obj" \
	"$(INTDIR)/Doque.obj" \
	"$(INTDIR)/Fptr.obj" \
	"$(INTDIR)/Quelist.obj" \
	"$(INTDIR)/Setpath.obj" \
	"$(INTDIR)/Queitm.obj" \
	"$(INTDIR)/Queuio.obj" \
	"$(INTDIR)/Quinsdel.obj" \
	"$(INTDIR)/Uis2dsk.obj" \
	"$(INTDIR)/astroflist.obj" \
	"$(INTDIR)/Sortfils.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/FileEditDlg.obj" \
	"$(INTDIR)/Quesel.obj" \
	"$(INTDIR)/FileNameDlg.obj" \
	"$(INTDIR)/Inifile.obj" \
	"$(INTDIR)/Charcons.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/Directories.obj" \
	"$(INTDIR)/Quefind.obj" \
	"$(INTDIR)/Errors.obj" \
	"$(INTDIR)/Scanfile.obj" \
	"$(INTDIR)/Queutil.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Strclip.obj" \
	"$(INTDIR)/astroflistDoc.obj" \
	"$(INTDIR)/Direc.obj" \
	"$(INTDIR)/FileKillDlg.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/astroflist.res"

"$(OUTDIR)\astroflist.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "astroflist - Win32 Release"
# Name "astroflist - Win32 Debug"

!IF  "$(CFG)" == "astroflist - Win32 Release"

!ELSEIF  "$(CFG)" == "astroflist - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "astroflist - Win32 Release"

!ELSEIF  "$(CFG)" == "astroflist - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\astroflist.cpp
DEP_CPP_ASTRO=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\astroflist.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\astroflistDoc.h"\
	".\astroflistView.h"\
	".\Splash.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\astroflist.obj" : $(SOURCE) $(DEP_CPP_ASTRO) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "astroflist - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D " DELUXE" /D " PRO" /Fp"$(INTDIR)/astroflist.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\astroflist.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "astroflist - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D " DELUXE" /D " PRO" /Fp"$(INTDIR)/astroflist.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\astroflist.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\astroflist.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp
DEP_CPP_CHILD=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\astroflist.h"\
	".\ChildFrm.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\astroflistDoc.cpp
DEP_CPP_ASTROF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\astroflistDoc.h"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\astroflistDoc.obj" : $(SOURCE) $(DEP_CPP_ASTROF) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\astroflistView.cpp
DEP_CPP_ASTROFL=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\astroflistDoc.h"\
	".\astroflistView.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Directories.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\astroflistView.obj" : $(SOURCE) $(DEP_CPP_ASTROFL) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\astroflist.rc
DEP_RSC_ASTROFLI=\
	".\res\astroflist.ico"\
	".\res\astroflistDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\Cglyph.bmp"\
	".\res\Ctext.bmp"\
	".\res\bitmap1.bmp"\
	".\res\astroflist.rc2"\
	

"$(INTDIR)\astroflist.res" : $(SOURCE) $(DEP_RSC_ASTROFLI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Charcons.cpp
DEP_CPP_CHARC=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Charcons.obj" : $(SOURCE) $(DEP_CPP_CHARC) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
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
 "$(INTDIR)\astroflist.pch"
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
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Inifile.cpp
DEP_CPP_INIFI=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Inifile.hpp"\
	

"$(INTDIR)\Inifile.obj" : $(SOURCE) $(DEP_CPP_INIFI) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
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
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Uiutl\Strclip.cpp
DEP_CPP_STRCL=\
	{$(INCLUDE)}"\StdAfx.h"\
	

"$(INTDIR)\Strclip.obj" : $(SOURCE) $(DEP_CPP_STRCL) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
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
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Quinsdel.cpp
DEP_CPP_QUINS=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	

"$(INTDIR)\Quinsdel.obj" : $(SOURCE) $(DEP_CPP_QUINS) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Quefind.cpp
DEP_CPP_QUEFI=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\astrow.h"\
	".\..\DlgTest\FileNameDlg.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Quefind.obj" : $(SOURCE) $(DEP_CPP_QUEFI) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Queitm.cpp
DEP_CPP_QUEIT=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	

"$(INTDIR)\Queitm.obj" : $(SOURCE) $(DEP_CPP_QUEIT) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Quelist.cpp
DEP_CPP_QUELI=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\Uicvt.fns"\
	{$(INCLUDE)}"\astroflistDoc.h"\
	

"$(INTDIR)\Quelist.obj" : $(SOURCE) $(DEP_CPP_QUELI) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Quesel.cpp
DEP_CPP_QUESE=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	

"$(INTDIR)\Quesel.obj" : $(SOURCE) $(DEP_CPP_QUESE) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Queuio.cpp
DEP_CPP_QUEUI=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\astrow.h"\
	".\..\DlgTest\FileKillDlg.h"\
	".\..\DlgTest\FileEditDlg.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Queuio.obj" : $(SOURCE) $(DEP_CPP_QUEUI) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Queutil.cpp

!IF  "$(CFG)" == "astroflist - Win32 Release"

DEP_CPP_QUEUT=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	

"$(INTDIR)\Queutil.obj" : $(SOURCE) $(DEP_CPP_QUEUT) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "astroflist - Win32 Debug"

DEP_CPP_QUEUT=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	
NODEP_CPP_QUEUT=\
	".\..\Que\}"\
	

"$(INTDIR)\Queutil.obj" : $(SOURCE) $(DEP_CPP_QUEUT) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Que\Doque.cpp
DEP_CPP_DOQUE=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\astrow.h"\
	".\..\DlgTest\FileNameDlg.h"\
	{$(INCLUDE)}"\Charcons.h"\
	

"$(INTDIR)\Doque.obj" : $(SOURCE) $(DEP_CPP_DOQUE) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\DlgTest\FileKillDlg.cpp
DEP_CPP_FILEK=\
	".\..\DlgTest\stdafx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	".\..\DlgTest\FileKillDlg.h"\
	

"$(INTDIR)\FileKillDlg.obj" : $(SOURCE) $(DEP_CPP_FILEK) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\DlgTest\FileEditDlg.cpp
DEP_CPP_FILEE=\
	".\..\DlgTest\stdafx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	".\..\DlgTest\FileEditDlg.h"\
	

"$(INTDIR)\FileEditDlg.obj" : $(SOURCE) $(DEP_CPP_FILEE) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\DlgTest\FileNameDlg.cpp
DEP_CPP_FILEN=\
	".\..\DlgTest\stdafx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	".\..\DlgTest\FileNameDlg.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\FileNameDlg.obj" : $(SOURCE) $(DEP_CPP_FILEN) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Astrograph\Directories.cpp
DEP_CPP_DIRECT=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Direc.hpp"\
	{$(INCLUDE)}"\Directories.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	

"$(INTDIR)\Directories.obj" : $(SOURCE) $(DEP_CPP_DIRECT) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
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
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Util\Sortfils.cpp
DEP_CPP_SORTF=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	

"$(INTDIR)\Sortfils.obj" : $(SOURCE) $(DEP_CPP_SORTF) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Astrow32\Util\Scanfile.cpp
DEP_CPP_SCANF=\
	{$(INCLUDE)}"\StdAfx.h"\
	{$(INCLUDE)}"\astrow.h"\
	{$(INCLUDE)}"\Astro.h"\
	{$(INCLUDE)}"\Useri.h"\
	{$(INCLUDE)}"\Fptr.h"\
	{$(INCLUDE)}"\Charcons.h"\
	{$(INCLUDE)}"\Errors.fns"\
	{$(INCLUDE)}"\Paths.hpp"\
	{$(INCLUDE)}"\Filelst.hpp"\
	{$(INCLUDE)}"\procmsg.h"\
	

"$(INTDIR)\Scanfile.obj" : $(SOURCE) $(DEP_CPP_SCANF) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\StdAfx.h"\
	".\Splash.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\astroflist.pch"


# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section astroflist : {DC1638D0-10F9-11D1-931D-0000C00DEE96}
# 	0:8:Splash.h:D:\Astrow32\Astroflist\Splash.h
# 	0:10:Splash.cpp:D:\Astrow32\Astroflist\Splash.cpp
# 	1:9:IDB_ASTRO:105
# 	2:10:ResHdrName:resource.h
# 	2:11:ProjHdrName:stdafx.h
# 	2:10:WrapperDef:_SPLASH_SCRN_
# 	2:12:SplClassName:CSplashWnd
# 	2:21:SplashScreenInsertKey:4.0
# 	2:10:HeaderName:Splash.h
# 	2:10:ImplemName:Splash.cpp
# 	2:7:BmpID16:IDB_ASTRO
# End Section
################################################################################
