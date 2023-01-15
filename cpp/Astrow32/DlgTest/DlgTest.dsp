# Microsoft Developer Studio Project File - Name="DlgTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DlgTest - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DlgTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DlgTest.mak" CFG="DlgTest - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DlgTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DlgTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DlgTest - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "DlgTest - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

# Name "DlgTest - Win32 Release"
# Name "DlgTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=\Astrow32\Dlg\Acombbox.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engdll\Anomaly.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchiveData.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Databas\Asbplus.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Aspects.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Asthlper.cpp
# End Source File
# Begin Source File

SOURCE=.\AstroHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\BirthInfo.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Charcons.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\CoverPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Customize.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Databas\Database.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Direc.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Astrograph\Directories.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTest.rc
# End Source File
# Begin Source File

SOURCE=.\DlgTestDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTestView.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Errors.cpp
# End Source File
# Begin Source File

SOURCE=.\FileEditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileKillDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FileNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Databas\Freesp.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engdll\Julian.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Loadorbs.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OrbEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgrData.cpp
# End Source File
# Begin Source File

SOURCE=.\QdtOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Realoc.cpp
# End Source File
# Begin Source File

SOURCE=.\RectifyData.cpp
# End Source File
# Begin Source File

SOURCE=.\RelocScr.cpp
# End Source File
# Begin Source File

SOURCE=.\ReturnData.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Setpath.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Setup.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engdll\Sidereal.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Strclip.cpp
# End Source File
# Begin Source File

SOURCE=.\TransData.cpp
# End Source File
# Begin Source File

SOURCE=.\TransInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\TransScr.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Uis2dsk.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ArchiveData.h
# End Source File
# Begin Source File

SOURCE=.\AstroHelper.h
# End Source File
# Begin Source File

SOURCE=.\BirthInfo.h
# End Source File
# Begin Source File

SOURCE=.\ChartOptions.h
# End Source File
# Begin Source File

SOURCE=.\CoverPage.h
# End Source File
# Begin Source File

SOURCE=.\Customize.h
# End Source File
# Begin Source File

SOURCE=..\Astrograph\Directories.h
# End Source File
# Begin Source File

SOURCE=.\DlgTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestDoc.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestView.h
# End Source File
# Begin Source File

SOURCE=.\FileEditDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileKillDlg.h
# End Source File
# Begin Source File

SOURCE=.\FileNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OrbEdit.h
# End Source File
# Begin Source File

SOURCE=.\PrintOptions.h
# End Source File
# Begin Source File

SOURCE=.\ProgrData.h
# End Source File
# Begin Source File

SOURCE=.\QdtOptions.h
# End Source File
# Begin Source File

SOURCE=.\RectifyData.h
# End Source File
# Begin Source File

SOURCE=.\RelocScr.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ReturnData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TransData.h
# End Source File
# Begin Source File

SOURCE=.\TransInfo.h
# End Source File
# Begin Source File

SOURCE=.\TransScr.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DlgTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\DlgTest.rc2
# End Source File
# Begin Source File

SOURCE=.\res\DlgTestDoc.ico
# End Source File
# End Group
# End Target
# End Project
