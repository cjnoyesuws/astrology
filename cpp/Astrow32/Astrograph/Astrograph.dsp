# Microsoft Developer Studio Project File - Name="Astrograph" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Astrograph - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Astrograph.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Astrograph.mak" CFG="Astrograph - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Astrograph - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Astrograph - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Astrograph - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NEW" /D "DELUXE" /D "PRO" /D "USEDLL" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "Astrograph - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "NEW" /D "DELUXE" /D "USEDLL" /D "GRAVIEWER" /FR /Yu"stdafx.h" /FD /c
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

# Name "Astrograph - Win32 Release"
# Name "Astrograph - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=\Astrow32\Graph\Arndcirc.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Asdrawbs.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Astmisc.cpp
# End Source File
# Begin Source File

SOURCE=.\Astrograph.cpp
# End Source File
# Begin Source File

SOURCE=.\Astrograph.rc
# End Source File
# Begin Source File

SOURCE=.\AstrographDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\AstrographView.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Charcons.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Colorfnt.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Datagrfa.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Datakey.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Cover\Decomp.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Direc.cpp
# End Source File
# Begin Source File

SOURCE=.\Directories.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Dopoptxt.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Dotext.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Errors.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Fptr.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Graclr.cpp
# End Source File
# Begin Source File

SOURCE=.\GraColor.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Grafilop.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Grafnt.cpp
# End Source File
# Begin Source File

SOURCE=.\GraFont.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphFileOpts.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Dlg\Graphopt.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphOpts.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Graphwrt.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Graspcir.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Graspgrd.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Grlist.cpp
# End Source File
# Begin Source File

SOURCE=..\ENGDLL\House.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Inifile.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Isincos.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Key.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Loadgrph.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Mktmdt.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Ochthed.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Outchthd.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Outqry.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Outreprn.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Engine\Oututil.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Plotgrtp.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Plothous.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Plotplan.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Plotslin.cpp
# End Source File
# Begin Source File

SOURCE=.\PopupEd.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
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

SOURCE=\Astrow32\Engine\Table.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Tabout.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Tabs.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Graph\Tickcirc.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Uis2dsk.cpp
# End Source File
# Begin Source File

SOURCE=\Astrow32\Uiutl\Words.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\INC\Arndcirc.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Asdrawbs.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\ASGFLAGS.H
# End Source File
# Begin Source File

SOURCE=.\Astrograph.h
# End Source File
# Begin Source File

SOURCE=.\AstrographDoc.h
# End Source File
# Begin Source File

SOURCE=.\AstrographView.h
# End Source File
# Begin Source File

SOURCE=..\INC\Datagrfa.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Datakey.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\DATAPANE.HPP
# End Source File
# Begin Source File

SOURCE=..\INC\Direc.hpp
# End Source File
# Begin Source File

SOURCE=.\Directories.h
# End Source File
# Begin Source File

SOURCE=..\INC\Fptr.h
# End Source File
# Begin Source File

SOURCE=.\GraColor.h
# End Source File
# Begin Source File

SOURCE=..\INC\Gracolor.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Grafilop.hpp
# End Source File
# Begin Source File

SOURCE=.\GraFont.h
# End Source File
# Begin Source File

SOURCE=..\INC\Grafont.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Graopt.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Graphdat.hpp
# End Source File
# Begin Source File

SOURCE=.\GraphFileOpts.h
# End Source File
# Begin Source File

SOURCE=.\GraphOpts.h
# End Source File
# Begin Source File

SOURCE=..\INC\Graphwrt.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Graspcir.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Graspgrd.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\GRCONV.HPP
# End Source File
# Begin Source File

SOURCE=..\INC\Grlist.hpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\INC\ORBS.H
# End Source File
# Begin Source File

SOURCE=..\INC\Plotgrtp.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Plothous.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Plotplan.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Plotslin.hpp
# End Source File
# Begin Source File

SOURCE=..\INC\Polar.hpp
# End Source File
# Begin Source File

SOURCE=.\PopupEd.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\INC\SEXCODES.HPP
# End Source File
# Begin Source File

SOURCE=..\INC\Tickcirc.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Astrograph.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Cglyph.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Graph.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Wheel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wheel.ico
# End Source File
# End Group
# End Target
# End Project
# Section Astrograph : {DC1638CC-10F9-11D1-931D-0000C00DEE96}
# 	2:10:CMainFrame:Palette support added
# End Section
