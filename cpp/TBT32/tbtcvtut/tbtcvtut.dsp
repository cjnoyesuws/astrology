# Microsoft Developer Studio Project File - Name="tbtcvtut" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=tbtcvtut - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tbtcvtut.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tbtcvtut.mak" CFG="tbtcvtut - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tbtcvtut - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "tbtcvtut - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tbtcvtut - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TBTCVTUT_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TBTCVTUT_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "tbtcvtut - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TBTCVTUT_EXPORTS" /Yu"stdafx.h" /FD /GZ  /c
# ADD CPP /nologo /G5 /Zp2 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "TBTCVTUT_EXPORTS" /Yu"stdafx.h" /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "tbtcvtut - Win32 Release"
# Name "tbtcvtut - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3DBLDTXT.CPP
# End Source File
# Begin Source File

SOURCE=.\AMITOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\ARRAY.CPP
# End Source File
# Begin Source File

SOURCE=.\ASCTOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\AST2AMI.CPP
# End Source File
# Begin Source File

SOURCE=.\AST2ASC.CPP
# End Source File
# Begin Source File

SOURCE=.\AST2RTF.CPP
# End Source File
# Begin Source File

SOURCE=.\AST2WP4.CPP
# End Source File
# Begin Source File

SOURCE=.\AST2WP5.CPP
# End Source File
# Begin Source File

SOURCE=.\ast2wp6.cpp
# End Source File
# Begin Source File

SOURCE=.\AST2WS.CPP
# End Source File
# Begin Source File

SOURCE=.\ASTTODOC.CPP
# End Source File
# Begin Source File

SOURCE=.\BUILDRPT.CPP
# End Source File
# Begin Source File

SOURCE=.\BUILDTXT.CPP
# End Source File
# Begin Source File

SOURCE=.\COMPRESS.CPP
# End Source File
# Begin Source File

SOURCE=.\EXECER.CPP
# End Source File
# Begin Source File

SOURCE=.\LIBMAIN.CPP

!IF  "$(CFG)" == "tbtcvtut - Win32 Release"

!ELSEIF  "$(CFG)" == "tbtcvtut - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LOGTEXT.CPP
# End Source File
# Begin Source File

SOURCE=.\MKBSR.CPP
# End Source File
# Begin Source File

SOURCE=.\MKRBSR.CPP
# End Source File
# Begin Source File

SOURCE=.\MKSTRB.CPP
# End Source File
# Begin Source File

SOURCE=.\MKVBSR.CPP
# End Source File
# Begin Source File

SOURCE=.\MSWTOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\RTFTOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\STRTABLE.CPP
# End Source File
# Begin Source File

SOURCE=.\STRX.CPP
# End Source File
# Begin Source File

SOURCE=.\tbtcvtut.cpp
# End Source File
# Begin Source File

SOURCE=.\TEXTWRAP.CPP
# End Source File
# Begin Source File

SOURCE=.\WORDS.CPP
# End Source File
# Begin Source File

SOURCE=.\WP4TOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\WP5TOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\wp6toast.cpp
# End Source File
# Begin Source File

SOURCE=.\WPINTL.CPP
# End Source File
# Begin Source File

SOURCE=.\WSTOAST.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ARRAY.HPP
# End Source File
# Begin Source File

SOURCE=.\BUILDER.HPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TBTUTIL.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
