; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPageSetp
LastTemplate=CListBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Astroview.h"
LastPage=0

ClassCount=9
Class1=CAstroviewApp
Class2=CAstroviewDoc
Class3=CAstroviewView
Class4=CMainFrame

ResourceCount=8
Resource1=IDD_PAGESETP
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Class6=CFindText
Resource3=IDD_CONVOPT
Class7=CPageSetp
Resource4=IDD_REPSTYLES
Resource5=IDD_ABOUTBOX
Resource6=IDD_FIND
Resource7=IDD_PSEUDO
Class8=CParaEdit
Class9=CODListBox
Resource8=IDD_PARA

[CLS:CAstroviewApp]
Type=0
HeaderFile=Astroview.h
ImplementationFile=Astroview.cpp
Filter=N

[CLS:CAstroviewDoc]
Type=0
HeaderFile=AstroviewDoc.h
ImplementationFile=AstroviewDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CAstroviewView]
Type=0
HeaderFile=AstroviewView.h
ImplementationFile=AstroviewView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CAstroviewView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=Astroview.cpp
ImplementationFile=Astroview.cpp
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
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_PAGE_SETUP
Command9=ID_APP_EXIT
Command10=ID_FILE_MRU_FILE1
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_DEL
Command16=ID_EDIT_SEARCH
Command17=ID_EDIT_SEARCHCONTINUE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_VIEW_LARGERFONTS
Command21=ID_VIEW_SMALLERFONTS
Command22=ID_HELP_FINDER
Command23=ID_APP_ABOUT
Command24=ID_OPTIONS_VIEWERSETUP
Command25=ID_OPTIONS_CONVERSIONSETUP
Command26=ID_OPTIONS_PRINTING
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_HELP
Command10=ID_CONTEXT_HELP
Command11=ID_EDIT_SEARCHCONTINUE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE_AS
Command3=ID_FILE_PRINT
Command4=ID_EDIT_SEARCH
Command5=ID_VIEW_SMALLERFONTS
Command6=ID_VIEW_LARGERFONTS
Command7=ID_HELP_FINDER
CommandCount=7

[DLG:IDD_FIND]
Type=1
Class=CFindText
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT1,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CFindText]
Type=0
HeaderFile=FindText.h
ImplementationFile=FindText.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFindText

[DLG:IDD_PAGESETP]
Type=1
Class=CPageSetp
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_TOP,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_LEFT,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BOTTOM,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_RIGHT,edit,1350631552
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816

[CLS:CPageSetp]
Type=0
HeaderFile=PageSetp.h
ImplementationFile=PageSetp.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPageSetp

[DLG:IDD_PSEUDO]
Type=1
Class=?
ControlCount=15
Control1=107,static,1342308352
Control2=ID_PSHEAD,edit,1350631552
Control3=108,static,1342308352
Control4=ID_PEHEAD,edit,1350631552
Control5=109,static,1342308352
Control6=ID_PSBOLD,edit,1350631552
Control7=110,static,1342308352
Control8=ID_PEBOLD,edit,1350631552
Control9=111,static,1342308352
Control10=ID_PSSCORE,edit,1350631552
Control11=112,static,1342308352
Control12=ID_PESCORE,edit,1350631552
Control13=1,button,1342242817
Control14=150,button,1342242816
Control15=2,button,1342242816

[DLG:IDD_REPSTYLES]
Type=1
Class=?
ControlCount=9
Control1=ID_RSREG,button,1342242816
Control2=ID_RSBOLD,button,1342242816
Control3=ID_RSHEAD,button,1342242816
Control4=ID_RSSCORE,button,1342242816
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=ID_HELP,button,1342242816
Control8=108,static,1342177284
Control9=109,static,1342177284

[DLG:IDD_CONVOPT]
Type=1
Class=?
ControlCount=14
Control1=101,static,1342308352
Control2=ID_COLEFT,edit,1350631552
Control3=103,static,1342308352
Control4=ID_COWIDTH,edit,1350631552
Control5=ID_COCMT,button,1342242819
Control6=ID_COCPG,button,1342242819
Control7=ID_COCB4,button,1342242819
Control8=107,static,1342308352
Control9=ID_COFORMAT,combobox,1344339971
Control10=ID_COSTYLES,button,1342242816
Control11=ID_COPSEUDO,button,1342242816
Control12=IDOK,button,1342242816
Control13=ID_HELP,button,1342242816
Control14=IDCANCEL,button,1342242816

[DLG:IDD_PARA]
Type=1
Class=CParaEdit
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_PTEXT,edit,1350635588

[CLS:CParaEdit]
Type=0
HeaderFile=ParaEdit.h
ImplementationFile=ParaEdit.cpp
BaseClass=CDialog
Filter=D
LastObject=CParaEdit
VirtualFilter=dWC

[CLS:CODListBox]
Type=0
HeaderFile=ODListBox.h
ImplementationFile=ODListBox.cpp
BaseClass=CListBox
Filter=W
LastObject=CODListBox

