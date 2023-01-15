; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CReportEdit
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TBT32.h"
LastPage=0

ClassCount=22
Class1=CTBT32App
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=13
Resource1=IDD_HELPTXT
Resource2=IDD_ABOUTBOX
Resource3=IDD_TEXTTYPE
Resource4=IDD_SEL_FILE
Resource5=IDD_DIALOG1
Class2=CChildView
Class5=CTextType
Class6=CAspTextEdit
Class7=CHelpEdit
Class8=CRegTextEdit
Class9=CHelpTxt
Class10=CRegText
Class11=CAspectText
Resource6=IDD_ASPTEXT
Resource7=IDD_REPORTTEXT
Class12=CReportEdit
Class13=CReportText
Resource8=IDR_MAINFRAME
Class14=CFileSelector
Resource9=IDD_REGTEXT
Class15=CSelectTextItem
Resource10=IDD_SETUP
Class16=CSetup
Resource11=IDD_SELTEXTITEM
Class17=CDAspectText
Class18=CDHelpTxt
Class19=CDregText
Class20=CDAspText
Class21=CDReportText
Resource12=IDR_EDIT
Class22=CProgress
Resource13=IDD_PROGRESS

[CLS:CTBT32App]
Type=0
HeaderFile=TBT32.h
ImplementationFile=TBT32.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CTBT32App

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=TBT32.cpp
ImplementationFile=TBT32.cpp
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
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_STATUS_BAR
Command7=ID_HELPTXT
Command8=ID_REGULARTXT
Command9=ID_ASPECTTEXT
Command10=ID_EDITTEXTSOURCES_REPORTTEXTSOURCES
Command11=ID_IMPORT_IMPORTPLANETHOUSETEXT
Command12=ID_IMPORT_IMPORTASPECTTEXT
Command13=ID_IMPORT_IMPORTAHELPFILE
Command14=ID_IMPORT_IMPORTREPORTTEXT
Command15=ID_OPTIONS_SETUP
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_COPY
Command3=ID_EDIT_PASTE
Command4=ID_PASTE
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_NEXT_PANE
Command8=ID_PREV_PANE
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_CUT
Command12=ID_CUT
Command13=ID_EDIT_UNDO
Command14=ID_UNDO
CommandCount=14

[DLG:IDD_HELPTXT]
Type=1
Class=CHelpEdit
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,RICHEDIT,1352732740
Control5=IDC_WSPELLCTRL1,{245338C3-BCA3-4A2C-A7B7-53345999A8E8},1342242816

[DLG:IDD_TEXTTYPE]
Type=1
Class=CTextType
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TEXTTYPE,combobox,1344339971

[DLG:IDD_REGTEXT]
Type=1
Class=CRegTextEdit
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_KEY1,combobox,1344340227
Control5=IDC_STATIC,static,1342308352
Control6=IDC_KEY2,combobox,1344340226
Control7=IDC_TEXT,RICHEDIT,1352732740
Control8=IDC_WSPELLCTRL1,{245338C3-BCA3-4A2C-A7B7-53345999A8E8},1342242816

[DLG:IDD_ASPTEXT]
Type=1
Class=CAspTextEdit
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PLAN1,combobox,1344340227
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PLAN2,combobox,1344340227
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ASPECT,combobox,1344340227
Control9=IDC_TEXT,RICHEDIT,1352732740
Control10=IDC_STATIC,static,1342308352
Control11=IDC_WSPELLCTRL1,{245338C3-BCA3-4A2C-A7B7-53345999A8E8},1342242816

[CLS:CTextType]
Type=0
HeaderFile=TextType.h
ImplementationFile=TextType.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTextType

[CLS:CAspTextEdit]
Type=0
HeaderFile=AspTextEdit.h
ImplementationFile=AspTextEdit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_WSPELLCTRL1

[CLS:CHelpEdit]
Type=0
HeaderFile=HelpEdit.h
ImplementationFile=HelpEdit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_WSPELLCTRL1

[CLS:CRegTextEdit]
Type=0
HeaderFile=RegTextEdit.h
ImplementationFile=RegTextEdit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_SPELL

[CLS:CHelpTxt]
Type=0
HeaderFile=HelpTxt.h
ImplementationFile=HelpTxt.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CHelpTxt]
DB=1
DBType=ODBC
ColumnCount=2
Column1=[texttype], 12, 100
Column2=[Text], -1, 2147483646

[CLS:CRegText]
Type=0
HeaderFile=RegText.h
ImplementationFile=RegText.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRegText

[DB:CRegText]
DB=1
DBType=ODBC
ColumnCount=6
Column1=[TextType], 12, 100
Column2=[Key1], 12, 100
Column3=[key2], 12, 100
Column4=[Key1num], 5, 2
Column5=[Key2num], 5, 2
Column6=[Text], -1, 2147483646

[CLS:CAspectText]
Type=0
HeaderFile=AspectText.h
ImplementationFile=AspectText.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CAspectText

[DB:CAspectText]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[TextType], 12, 100
Column2=[Planet1], 12, 100
Column3=[Planet2], 12, 100
Column4=[Planet1num], 5, 2
Column5=[Planet2num], 5, 2
Column6=[Aspect], 12, 100
Column7=[Aspectnum], 5, 2
Column8=[Text], -1, 2147483646

[MNU:IDR_EDIT]
Type=1
Class=?
Command1=ID_COPY
Command2=ID_PASTE
Command3=ID_CUT
Command4=ID_CLEAR
Command5=ID_UNDO
Command6=ID_BOLD
Command7=ID_ITAL
Command8=ID_HEAD
Command9=ID_UNHEADING
Command10=ID_SPELL
CommandCount=10

[DLG:IDD_REPORTTEXT]
Type=1
Class=CReportEdit
ControlCount=9
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TEXTID,combobox,1344340227
Control5=IDC_STATIC,static,1342308352
Control6=IDC_INDEX,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_TEXT,RICHEDIT,1352732740
Control9=IDC_WSPELLCTRL1,{245338C3-BCA3-4A2C-A7B7-53345999A8E8},1342242816

[CLS:CReportEdit]
Type=0
HeaderFile=ReportEdit.h
ImplementationFile=ReportEdit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_SPELL

[CLS:CReportText]
Type=0
HeaderFile=ReportText.h
ImplementationFile=ReportText.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CReportText]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[texttype], 12, 100
Column2=[textkey], 12, 100
Column3=[iIndex], 5, 2
Column4=[iTextKey], 5, 2
Column5=[text], -1, 2147483646

[DLG:IDD_SEL_FILE]
Type=1
Class=CFileSelector
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FILES,listbox,1352728843

[CLS:CFileSelector]
Type=0
HeaderFile=FileSelector.h
ImplementationFile=FileSelector.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_FILES

[DLG:IDD_SELTEXTITEM]
Type=1
Class=CSelectTextItem
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_TEXTITEM,combobox,1344340227

[CLS:CSelectTextItem]
Type=0
HeaderFile=SelectTextItem.h
ImplementationFile=SelectTextItem.cpp
BaseClass=CDialog
Filter=D
LastObject=CSelectTextItem
VirtualFilter=dWC

[DLG:IDD_SETUP]
Type=1
Class=CSetup
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DIR,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DSN,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_DBDIR,edit,1350631552

[CLS:CSetup]
Type=0
HeaderFile=Setup.h
ImplementationFile=Setup.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSetup

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CDAspectText]
Type=0
HeaderFile=DAspectText1.h
ImplementationFile=DAspectText1.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:CDAspectText]
DB=1
DBType=DAO
ColumnCount=8
Column1=[TextType], 12, 50
Column2=[Planet1], 12, 50
Column3=[Planet2], 12, 50
Column4=[Planet1num], 5, 2
Column5=[Planet2num], 5, 2
Column6=[Aspect], 12, 50
Column7=[Aspectnum], 5, 2
Column8=[Text], -1, 0

[CLS:CDHelpTxt]
Type=0
HeaderFile=DHelpTxt1.h
ImplementationFile=DHelpTxt1.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:CDHelpTxt]
DB=1
DBType=DAO
ColumnCount=2
Column1=[texttype], 12, 50
Column2=[Text], -1, 0

[CLS:CDregText]
Type=0
HeaderFile=DregText1.h
ImplementationFile=DregText1.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:CDregText]
DB=1
DBType=DAO
ColumnCount=6
Column1=[TextType], 12, 50
Column2=[Key1], 12, 50
Column3=[key2], 12, 50
Column4=[Key1num], 5, 2
Column5=[Key2num], 5, 2
Column6=[Text], -1, 0

[CLS:CDAspText]
Type=0
HeaderFile=DAspText.h
ImplementationFile=DAspText.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:CDAspText]
DB=1
DBType=DAO
ColumnCount=0

[CLS:CDReportText]
Type=0
HeaderFile=DReportText1.h
ImplementationFile=DReportText1.cpp
BaseClass=CDaoRecordset
Filter=N
VirtualFilter=x

[DB:CDReportText]
DB=1
DBType=DAO
ColumnCount=5
Column1=[texttype], 12, 50
Column2=[textkey], 12, 50
Column3=[iIndex], 5, 2
Column4=[iTextKey], 5, 2
Column5=[text], -1, 0

[DLG:IDD_PROGRESS]
Type=1
Class=CProgress
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROGRESS1,msctls_progress32,1342177281
Control3=IDC_FILE,static,1350701057

[CLS:CProgress]
Type=0
HeaderFile=Progress.h
ImplementationFile=Progress.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_PROGRESS1

