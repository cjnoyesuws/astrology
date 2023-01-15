; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChartEditView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChartEdit.h"
LastPage=0

ClassCount=5
Class1=CChartEditApp
Class2=CChartEditDoc
Class3=CChartEditView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_MAINFRAME
Resource2=IDR_CNTR_INPLACE
Class5=CAboutDlg
Resource4=IDD_ABOUTBOX
Resource5="EDIT"

[CLS:CChartEditApp]
Type=0
HeaderFile=ChartEdit.h
ImplementationFile=ChartEdit.cpp
Filter=N

[CLS:CChartEditDoc]
Type=0
HeaderFile=ChartEditDoc.h
ImplementationFile=ChartEditDoc.cpp
Filter=N
BaseClass=CRichEditDoc
VirtualFilter=DC
LastObject=CChartEditDoc

[CLS:CChartEditView]
Type=0
HeaderFile=ChartEditView.h
ImplementationFile=ChartEditView.cpp
Filter=C
BaseClass=CRichEditView
VirtualFilter=VWC
LastObject=ID_SYLES_NORMAL


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_SYLES_NORMAL




[CLS:CAboutDlg]
Type=0
HeaderFile=ChartEdit.cpp
ImplementationFile=ChartEdit.cpp
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
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_SELECT_ALL
Command15=ID_EDIT_FIND
Command16=ID_EDIT_REPEAT
Command17=ID_EDIT_REPLACE
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_STYLES_BOLD
Command21=ID_STYLES_ITALIC
Command22=ID_STYLES_HEADING
Command23=ID_STYLES_NORMAL
Command24=ID_HELP_FINDER
Command25=ID_APP_ABOUT
CommandCount=25

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CChartEditView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_SELECT_ALL
Command2=ID_STYLES_BOLD
Command3=ID_EDIT_COPY
Command4=ID_EDIT_FIND
Command5=ID_EDIT_REPLACE
Command6=ID_STYLES_HEADING
Command7=ID_STYLES_ITALIC
Command8=ID_FILE_NEW
Command9=ID_SYLES_NORMAL
Command10=ID_FILE_OPEN
Command11=ID_FILE_PRINT
Command12=ID_FILE_SAVE
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_CANCEL_EDIT_CNTR
Command17=ID_HELP
Command18=ID_CONTEXT_HELP
Command19=ID_EDIT_REPEAT
Command20=ID_NEXT_PANE
Command21=ID_PREV_PANE
Command22=ID_EDIT_COPY
Command23=ID_EDIT_PASTE
Command24=ID_OLE_EDIT_PROPERTIES
Command25=ID_EDIT_CUT
Command26=ID_EDIT_UNDO
CommandCount=26

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CChartEditView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CONTEXT_HELP
Command8=ID_HELP
Command9=ID_CANCEL_EDIT_CNTR
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:"EDIT"]
Type=1
Command1=ID_EDIT_CUT
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_COPY
Command5=ID_BOLD
Command6=ID_ITALIC
Command7=ID_HEADING
Command8=ID_NORMAL
CommandCount=8

