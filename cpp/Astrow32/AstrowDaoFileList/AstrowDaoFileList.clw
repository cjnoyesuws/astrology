; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAstrowDaoFileListView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AstrowDaoFileList.h"
ODLFile=AstrowDaoFileList.odl
LastPage=0

ClassCount=6
Class1=CAstrowDaoFileListApp
Class2=CAstrowDaoFileListDoc
Class3=CAstrowDaoFileListView
Class4=CMainFrame
Class6=CAboutDlg

ResourceCount=7
Resource1=IDD_ASTROWDAOFILELIST_FORM
Resource2=IDD_ABOUTBOX
Class5=CAstrowDaoFileListSet
Resource7=IDR_MAINFRAME

[CLS:CAstrowDaoFileListApp]
Type=0
HeaderFile=AstrowDaoFileList.h
ImplementationFile=AstrowDaoFileList.cpp
Filter=N

[CLS:CAstrowDaoFileListDoc]
Type=0
HeaderFile=AstrowDaoFileListDoc.h
ImplementationFile=AstrowDaoFileListDoc.cpp
Filter=N

[CLS:CAstrowDaoFileListView]
Type=0
HeaderFile=AstrowDaoFileListView.h
ImplementationFile=AstrowDaoFileListView.cpp
Filter=D
LastObject=IDC_TYPE
BaseClass=CDaoRecordView
VirtualFilter=XRVWC


[CLS:CAstrowDaoFileListSet]
Type=0
HeaderFile=AstrowDaoFileListSet.h
ImplementationFile=AstrowDaoFileListSet.cpp
Filter=N

[DB:CAstrowDaoFileListSet]
DB=1
DBType=DAO
ColumnCount=9
Column1=[name], 12, 80
Column2=[comments], 12, 125
Column3=[filename], 12, 255
Column4=[filenum], 5, 2
Column5=[IsTextReport], -7, 1
Column6=[FileType], -6, 1
Column7=[counter], 4, 4
Column8=[has_cover], -7, 1
Column9=[has_comments], -7, 1


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=AstrowDaoFileList.cpp
ImplementationFile=AstrowDaoFileList.cpp
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
Command14=ID_RECORD_FIRST
Command15=ID_RECORD_PREV
Command16=ID_RECORD_NEXT
Command17=ID_RECORD_LAST
Command18=ID_VIEW_TOOLBAR
Command19=ID_VIEW_STATUS_BAR
Command20=ID_HELP_FINDER
Command21=ID_APP_ABOUT
CommandCount=21

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT
Command4=ID_FILE_SAVE
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_HELP
Command9=ID_CONTEXT_HELP
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[DLG:IDD_ASTROWDAOFILELIST_FORM]
Type=1
Class=CAstrowDaoFileListView
ControlCount=11
Control1=IDC_STATIC,static,1342177287
Control2=IDC_STATIC,static,1342308354
Control3=IDC_NAME,edit,1350633600
Control4=IDC_STATIC,static,1342308354
Control5=IDC_COMMENT,edit,1350633600
Control6=IDC_COVER,static,1342312449
Control7=IDC_CMTPG,static,1342312449
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_FILENAME,edit,1350633600
Control11=IDC_TYPE,edit,1350633600

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
Command8=ID_RECORD_FIRST
Command9=ID_RECORD_PREV
Command10=ID_RECORD_NEXT
Command11=ID_RECORD_LAST
Command12=ID_APP_ABOUT
Command13=ID_CONTEXT_HELP
CommandCount=13

