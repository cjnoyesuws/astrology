# Microsoft Developer Studio Project File - Name="importtool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=importtool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "importtool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "importtool.mak" CFG="importtool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "importtool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "importtool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "importtool - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "importtool - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "importtool - Win32 Release"
# Name "importtool - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BirthSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Astrow32\ENGDLL\Charcons.cpp
# End Source File
# Begin Source File

SOURCE=..\Astrow32\UIUTL\Direc.cpp
# End Source File
# Begin Source File

SOURCE=..\Astrow32\UIUTL\Errors.cpp
# End Source File
# Begin Source File

SOURCE=.\FileListSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportBirths.cpp
# End Source File
# Begin Source File

SOURCE=.\ImporterData.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportFileList.cpp

!IF  "$(CFG)" == "importtool - Win32 Release"

!ELSEIF  "$(CFG)" == "importtool - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ImportLocations.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportThread.cpp

!IF  "$(CFG)" == "importtool - Win32 Release"

!ELSEIF  "$(CFG)" == "importtool - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\importtool.cpp
# End Source File
# Begin Source File

SOURCE=.\importtool.rc
# End Source File
# Begin Source File

SOURCE=.\importtoolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LocationSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Progress.cpp
# End Source File
# Begin Source File

SOURCE=.\RectificationSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Relocationset.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\transitSet.cpp
# End Source File
# Begin Source File

SOURCE=..\Astrow32\UIUTL\Uis2dsk.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Astrow32\INC\ASTRO.H
# End Source File
# Begin Source File

SOURCE=.\BirthSet.h
# End Source File
# Begin Source File

SOURCE=..\Astrow32\INC\Dataext.h
# End Source File
# Begin Source File

SOURCE=..\Astrow32\INC\Db.h
# End Source File
# Begin Source File

SOURCE=..\Astrow32\INC\Dbstruct.h
# End Source File
# Begin Source File

SOURCE=..\Astrow32\INC\Direc.hpp
# End Source File
# Begin Source File

SOURCE=.\FileListSet.h
# End Source File
# Begin Source File

SOURCE=.\ImportBirths.h
# End Source File
# Begin Source File

SOURCE=.\ImporterData.h
# End Source File
# Begin Source File

SOURCE=.\ImportFileList.h

!IF  "$(CFG)" == "importtool - Win32 Release"

!ELSEIF  "$(CFG)" == "importtool - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ImportLocations.h
# End Source File
# Begin Source File

SOURCE=.\ImportThread.h

!IF  "$(CFG)" == "importtool - Win32 Release"

!ELSEIF  "$(CFG)" == "importtool - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\importtool.h
# End Source File
# Begin Source File

SOURCE=.\importtoolDlg.h
# End Source File
# Begin Source File

SOURCE=.\LocationSet.h
# End Source File
# Begin Source File

SOURCE=.\Progress.h
# End Source File
# Begin Source File

SOURCE=.\RectificationSet.h
# End Source File
# Begin Source File

SOURCE=.\Relocationset.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\transitSet.h
# End Source File
# Begin Source File

SOURCE=..\Astrow32\INC\Useri.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Astro.ico
# End Source File
# Begin Source File

SOURCE=.\res\importtool.ico
# End Source File
# Begin Source File

SOURCE=.\res\importtool.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=..\Astrow32\INC\Errors.fns
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\Astrow32\INC\Uicvt.fns
# End Source File
# End Target
# End Project
