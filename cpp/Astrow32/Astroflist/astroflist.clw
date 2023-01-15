; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSplashWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "astroflist.h"
LastPage=0

ClassCount=9
Class1=CAstroflistApp
Class2=CAstroflistDoc
Class3=CAstroflistView
Class4=CMainFrame
Class7=CAboutDlg
Class8=CChildFrame

ResourceCount=12
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_AST_HELP
Resource8=IDD_DIRECTORIES
Resource9=IDD_FILE_NAME
Resource10=IDD_FILE_KILL
Resource11=IDD_FILE_EDIT
Resource12=IDR_ASTRFLTYPE
Class9=CSplashWnd

[CLS:CAstroflistApp]
Type=0
HeaderFile=astroflist.h
ImplementationFile=astroflist.cpp
Filter=N

[CLS:CAstroflistDoc]
Type=0
HeaderFile=astroflistDoc.h
ImplementationFile=astroflistDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CAstroflistView]
Type=0
HeaderFile=astroflistView.h
ImplementationFile=astroflistView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=astroflist.cpp
ImplementationFile=astroflist.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_OPTIONS_DIRECTORIES
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_ASTRFLTYPE]
Type=1
Class=CAstroflistView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_OPTIONS_DIRECTORIES
Command15=ID_WINDOW_NEW
Command16=ID_WINDOW_CASCADE
Command17=ID_WINDOW_TILE_HORZ
Command18=ID_WINDOW_ARRANGE
Command19=ID_APP_ABOUT
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIRECTORIES]
Type=1
ControlCount=13
Control1=101,static,1342308352
Control2=ID_DMAIN,edit,1350631552
Control3=102,static,1342308352
Control4=ID_DHELP,edit,1350631552
Control5=103,static,1342308352
Control6=ID_DDATABASE,edit,1350631552
Control7=104,static,1342308352
Control8=ID_DDATA,edit,1350631552
Control9=105,static,1342308352
Control10=ID_DUSER,edit,1350631552
Control11=IDOK,button,1342242817
Control12=ID_HELP,button,1342242816
Control13=IDCANCEL,button,1342242816

[DLG:IDD_FILE_NAME]
Type=1
ControlCount=12
Control1=101,static,1342308352
Control2=ID_FNNAME,edit,1350631552
Control3=103,static,1342308352
Control4=ID_FNCOMMENT,edit,1350631552
Control5=105,static,1342308352
Control6=ID_FNTYPE,static,1342308480
Control7=IDC_STATIC,static,1342308352
Control8=ID_FNFILENAME,edit,1350632576
Control9=IDOK,button,1342242817
Control10=IDHELP,button,1342242816
Control11=IDCANCEL,button,1342242816
Control12=ID_FNSELFILE,button,1342242816

[DLG:IDD_FILE_KILL]
Type=1
ControlCount=13
Control1=101,static,1342308352
Control2=ID_FKNAME,static,1342308352
Control3=103,static,1342308352
Control4=ID_FKCOMMENT,static,1342308352
Control5=105,static,1342308352
Control6=ID_FKTYPE,static,1342308352
Control7=107,static,1342308352
Control8=ID_FKFILENAME,static,1342308352
Control9=ID_FKCONTINUE,button,1342242851
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816
Control12=IDNO,button,1342242816
Control13=IDHELP,button,1342242816

[DLG:IDD_FILE_EDIT]
Type=1
ControlCount=11
Control1=101,static,1342308352
Control2=ID_FENAME,edit,1350631552
Control3=103,static,1342308352
Control4=ID_FECOMMENTS,edit,1350631552
Control5=105,static,1342308352
Control6=ID_FETYPE,static,1342308480
Control7=107,static,1342308352
Control8=ID_FEFILENAME,static,1342308480
Control9=IDOK,button,1342242817
Control10=IDHELP,button,1342242816
Control11=IDCANCEL,button,1342242816

[DLG:IDD_AST_HELP]
Type=1
ControlCount=7
Control1=IDCANCEL,button,1342242817
Control2=106,static,1342308352
Control3=ID_AHLIST,listbox,1352728585
Control4=ID_AHVIEW,button,1342242816
Control5=ID_AHPRINT,button,1342242816
Control6=ID_AHCONVERT,button,1342242816
Control7=IDHELP,button,1342242816

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd

