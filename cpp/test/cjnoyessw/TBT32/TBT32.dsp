# Microsoft Developer Studio Project File - Name="TBT32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TBT32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TBT32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TBT32.mak" CFG="TBT32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TBT32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TBT32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TBT32 - Win32 Release"

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

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "TBT32" /Yu"stdafx.h" /FD /GZ /c
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

# Name "TBT32 - Win32 Release"
# Name "TBT32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AspectText.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\AspTextEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\AST2RTF.CPP
# End Source File
# Begin Source File

SOURCE=.\CHARCONS.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\DAspectText1.cpp
# End Source File
# Begin Source File

SOURCE=.\DAspText.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DHelpTxt1.cpp
# End Source File
# Begin Source File

SOURCE=.\DOSCMD.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DregText1.cpp
# End Source File
# Begin Source File

SOURCE=.\DReportText1.cpp
# End Source File
# Begin Source File

SOURCE=.\ENDETAB.CPP
# End Source File
# Begin Source File

SOURCE=.\ERRORS.CPP
# End Source File
# Begin Source File

SOURCE=.\FILEARY.CPP
# End Source File
# Begin Source File

SOURCE=.\FileSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\HelpTxt.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ImportAspText.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportRegText.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportReportText.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MAKE.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MAKEMAIN.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MKCHECK.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MKDEL.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MKIFPROC.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MKINPUT.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MKMACRO.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MKREADER.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Progress.cpp
# End Source File
# Begin Source File

SOURCE=.\RegText.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RegTextEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportText.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReportTextEdit.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReportTexts.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RTFFuncs.cpp
# End Source File
# Begin Source File

SOURCE=.\RTFTOAST.CPP
# End Source File
# Begin Source File

SOURCE=.\RULES.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelectTextItem.cpp
# End Source File
# Begin Source File

SOURCE=.\Setup.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Strbuff.cpp
# End Source File
# Begin Source File

SOURCE=.\StrTransform.cpp
# End Source File
# Begin Source File

SOURCE=.\SYMBOL.CPP
# End Source File
# Begin Source File

SOURCE=.\TBT32.cpp
# End Source File
# Begin Source File

SOURCE=.\TBT32.rc
# End Source File
# Begin Source File

SOURCE=.\TEXTBARY.CPP
# End Source File
# Begin Source File

SOURCE=.\TEXTBLOC.CPP
# End Source File
# Begin Source File

SOURCE=.\TextType.cpp

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\texttypeary.cpp
# End Source File
# Begin Source File

SOURCE=.\TEXTXREF.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TFILELST.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TSETPATH.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\WINCMD.CPP

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\wspell.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AspectText.h
# End Source File
# Begin Source File

SOURCE=.\AspTextEdit.h
# End Source File
# Begin Source File

SOURCE=.\CHARCONS.H

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\DAspectText1.h
# End Source File
# Begin Source File

SOURCE=.\DAspText.h
# End Source File
# Begin Source File

SOURCE=.\DHelpTxt1.h
# End Source File
# Begin Source File

SOURCE=.\DregText1.h
# End Source File
# Begin Source File

SOURCE=.\DReportText1.h
# End Source File
# Begin Source File

SOURCE=.\FILEARY.HPP
# End Source File
# Begin Source File

SOURCE=.\FileSelector.h
# End Source File
# Begin Source File

SOURCE=.\HelpEdit.h
# End Source File
# Begin Source File

SOURCE=.\HelpTxt.h

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ImportAspText.h
# End Source File
# Begin Source File

SOURCE=.\ImportHelp.h
# End Source File
# Begin Source File

SOURCE=.\ImportRegText.h
# End Source File
# Begin Source File

SOURCE=.\ImportReportText.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MAKE.H

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Progress.h
# End Source File
# Begin Source File

SOURCE=.\RegText.h
# End Source File
# Begin Source File

SOURCE=.\RegTextEdit.h
# End Source File
# Begin Source File

SOURCE=.\ReportEdit.h
# End Source File
# Begin Source File

SOURCE=.\ReportText.h
# End Source File
# Begin Source File

SOURCE=.\ReportTextEdit.h

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReportTexts.h

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RTFFuncs.h
# End Source File
# Begin Source File

SOURCE=.\SelectTextItem.h
# End Source File
# Begin Source File

SOURCE=.\Setup.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Strbuff.h
# End Source File
# Begin Source File

SOURCE=.\StrTransform.h
# End Source File
# Begin Source File

SOURCE=.\SYMBOL.H

!IF  "$(CFG)" == "TBT32 - Win32 Release"

!ELSEIF  "$(CFG)" == "TBT32 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SYMBOL.HPP
# End Source File
# Begin Source File

SOURCE=.\TBT32.h
# End Source File
# Begin Source File

SOURCE=.\TEXTBLOC.H
# End Source File
# Begin Source File

SOURCE=.\TextType.h
# End Source File
# Begin Source File

SOURCE=.\texttypeary.hpp
# End Source File
# Begin Source File

SOURCE=.\wspell.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\TBT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\TBT32.ico
# End Source File
# Begin Source File

SOURCE=.\res\TBT32.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section TBT32 : {245338C1-BCA3-4A2C-A7B7-53345999A8E8}
# 	2:5:Class:CWSpell
# 	2:10:HeaderFile:wspell.h
# 	2:8:ImplFile:wspell.cpp
# End Section
# Section TBT32 : {245338C3-BCA3-4A2C-A7B7-53345999A8E8}
# 	2:21:DefaultSinkHeaderFile:wspell.h
# 	2:16:DefaultSinkClass:CWSpell
# End Section
