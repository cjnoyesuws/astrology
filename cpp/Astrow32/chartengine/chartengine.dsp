# Microsoft Developer Studio Project File - Name="chartengine" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=chartengine - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "chartengine.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "chartengine.mak" CFG="chartengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "chartengine - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "chartengine - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "chartengine - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "chartengine - Win32 Release"
# Name "chartengine - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Engine\Anprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Arabpt.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Aspects.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Asthelio.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Astmisc.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Astrprob.cpp
# End Source File
# Begin Source File

SOURCE=..\Batch\Batchimp.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Charcons.cpp
# End Source File
# Begin Source File

SOURCE=.\chartengine.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Chcomp.cpp

!IF  "$(CFG)" == "chartengine - Win32 Release"

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Engine\Chrthead.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Cmprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Compat.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Compile.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Compile2.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Compos.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Coprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Coprnsum.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Ctprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Direc.cpp

!IF  "$(CFG)" == "chartengine - Win32 Release"

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Engine\Docalc.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Dopoptxt.cpp

!IF  "$(CFG)" == "chartengine - Win32 Release"

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Engine\Dotext.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Errors.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Fixdstar.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Fptr.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Graphdat.cpp
# End Source File
# Begin Source File

SOURCE=..\Graph\Graphwrt.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Heprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Intrhous.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Loadorbs.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Memmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Midpoint.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Misccalc.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Mkastrpr.cpp

!IF  "$(CFG)" == "chartengine - Win32 Release"

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Engine\Mkdat.c

!IF  "$(CFG)" == "chartengine - Win32 Release"

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Engine\Mktmdt.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Nhprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Nmprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Nxprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Ochthed.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Opmkprs.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Oprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Oprnsumm.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Outchthd.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Outqry.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Outreprn.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Oututil.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Prnrect.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Prnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Prnsumm.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Progress.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Prprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Realoc.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Reprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Return.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Rwfdata.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Setdata.c

!IF  "$(CFG)" == "chartengine - Win32 Release"

!ELSEIF  "$(CFG)" == "chartengine - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Uiutl\Setpath.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Sexcodes.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\Engine\Table.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Tabs.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Transits.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Trprnres.cpp
# End Source File
# Begin Source File

SOURCE=..\Uiutl\Uis2dsk.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Engine\Import.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
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
