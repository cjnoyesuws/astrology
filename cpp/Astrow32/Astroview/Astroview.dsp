# Microsoft Developer Studio Project File - Name="Astroview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Astroview - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Astroview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Astroview.mak" CFG="Astroview - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Astroview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Astroview - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Astroview - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "USEDLL" /D "DELUXE" /D "PRO" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Astroview - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "USEDLL" /D "DELUXE" /D "PRO" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Astroview - Win32 Release"
# Name "Astroview - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=\Astrow32\Wpconv\Asfil2tx.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astami.cpp
# End Source File
# Begin Source File

SOURCE=.\Astroview.cpp
# End Source File
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
# Begin Source File

SOURCE=.\Astroview.rc
# End Source File
# Begin Source File

SOURCE=.\AstroviewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AstroviewView.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astrtf.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\astwp6.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astwperf.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Astwstar.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\astwww.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Charcons.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Colorfnt.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Cover\Compress.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Astroedit\ConvertData.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Convopt.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Decompf.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Direc.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Errors.cpp
# End Source File
# Begin Source File

SOURCE=.\FindText.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Fptr.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Inifile.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Cover\Loadcovr.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ODListBox.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Opmkprs.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\outprnw6.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Outprnwp.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Pageopt.cpp
# End Source File
# Begin Source File

SOURCE=.\PageSetp.cpp
# End Source File
# Begin Source File

SOURCE=.\ParaEdit.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Astroedit\PseudoStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=\Astrow32\Astroedit\ReportStyles.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Repstyle.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Rwfdata.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Setpath.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Sexcodes.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Strclip.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Tabout.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Tabs.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Txtsrch.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Uis2dsk.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Virtsave.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Virttext.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Words.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Wpconv\Wpintl.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Wrfdata.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Astroview.h
# End Source File
# Begin Source File

SOURCE=.\AstroviewDoc.h
# End Source File
# Begin Source File

SOURCE=.\AstroviewView.h
# End Source File
# Begin Source File

SOURCE=..\ASTROEDIT\ConvertData.h
# End Source File
# Begin Source File

SOURCE=.\FindText.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ODListBox.h
# End Source File
# Begin Source File

SOURCE=.\PageSetp.h
# End Source File
# Begin Source File

SOURCE=.\paraedit.h
# End Source File
# Begin Source File

SOURCE=..\Astroedit\pseudostyle.h
# End Source File
# Begin Source File

SOURCE=..\ASTROEDIT\ReportStyles.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Astroview.ico
# End Source File
# Begin Source File

SOURCE=.\res\Astroview.rc2
# End Source File
# Begin Source File

SOURCE=.\res\AstroviewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
