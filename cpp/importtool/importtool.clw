; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFileListSet
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "importtool.h"

ClassCount=11
Class1=CImporttoolApp
Class2=CImporttoolDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_IMPORTTOOL_DIALOG
Class4=CProgress
Class5=CBirthSet
Class6=CLocationSet
Class7=CRelocationset
Class8=CtransitSet
Class9=CRectificationSet
Class10=CImportThread
Class11=CFileListSet
Resource4=IDD_PROGRESS
Resource5=IDD_DIALOG1

[CLS:CImporttoolApp]
Type=0
HeaderFile=importtool.h
ImplementationFile=importtool.cpp
Filter=N

[CLS:CImporttoolDlg]
Type=0
HeaderFile=importtoolDlg.h
ImplementationFile=importtoolDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CImporttoolDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=importtoolDlg.h
ImplementationFile=importtoolDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IMPORTTOOL_DIALOG]
Type=1
Class=CImporttoolDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DB,edit,1350631552
Control5=IDC_BIRTHS,button,1342246147
Control6=IDC_LOCS,button,1342246147

[DLG:IDD_PROGRESS]
Type=1
Class=CProgress
ControlCount=1
Control1=IDC_MESSAGE,static,1342308864

[CLS:CProgress]
Type=0
HeaderFile=Progress.h
ImplementationFile=Progress.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL
VirtualFilter=dWC

[CLS:CBirthSet]
Type=0
HeaderFile=BirthSet.h
ImplementationFile=BirthSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CBirthSet

[DB:CBirthSet]
DB=1
DBType=ODBC
ColumnCount=16
Column1=[name], 12, 100
Column2=[birthdate], 11, 16
Column3=[hours], 5, 2
Column4=[minutes], 5, 2
Column5=[AMPM], 12, 4
Column6=[country], 12, 100
Column7=[state], 12, 100
Column8=[location], 12, 100
Column9=[longitude], 12, 16
Column10=[latitude], 12, 16
Column11=[timezone], 5, 2
Column12=[specialcode], 5, 2
Column13=[houroff], 5, 2
Column14=[minoff], 5, 2
Column15=[rect], -7, 1
Column16=[sex], 5, 2

[CLS:CLocationSet]
Type=0
HeaderFile=LocationSet.h
ImplementationFile=LocationSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CLocationSet]
DB=1
DBType=ODBC
ColumnCount=9
Column1=[country], 12, 100
Column2=[state], 12, 100
Column3=[location], 12, 100
Column4=[longitude], 12, 16
Column5=[latitude], 12, 16
Column6=[timezone], 5, 2
Column7=[specialcode], 5, 2
Column8=[houroff], 5, 2
Column9=[minoff], 5, 2

[CLS:CRelocationset]
Type=0
HeaderFile=Relocationset.h
ImplementationFile=Relocationset.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CRelocationset]
DB=1
DBType=ODBC
ColumnCount=11
Column1=[name], 12, 100
Column2=[birthdate], 11, 16
Column3=[country], 12, 100
Column4=[state], 12, 100
Column5=[location], 12, 100
Column6=[longitude], 12, 16
Column7=[latitude], 12, 16
Column8=[timezone], 5, 2
Column9=[specialcode], 5, 2
Column10=[houroff], 5, 2
Column11=[minoff], 5, 2

[CLS:CtransitSet]
Type=0
HeaderFile=transitSet.h
ImplementationFile=transitSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:CtransitSet]
DB=1
DBType=ODBC
ColumnCount=15
Column1=[name], 12, 100
Column2=[birthdate], 11, 16
Column3=[hours], 5, 2
Column4=[minutes], 5, 2
Column5=[AMPM], 12, 4
Column6=[country], 12, 100
Column7=[state], 12, 100
Column8=[location], 12, 100
Column9=[longitude], 12, 16
Column10=[latitude], 12, 16
Column11=[timezone], 5, 2
Column12=[specialcode], 5, 2
Column13=[houroff], 5, 2
Column14=[minoff], 5, 2
Column15=[Event], 12, 100

[CLS:CRectificationSet]
Type=0
HeaderFile=RectificationSet.h
ImplementationFile=RectificationSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CRectificationSet

[DB:CRectificationSet]
DB=1
DBType=ODBC
ColumnCount=10
Column1=[name], 12, 100
Column2=[birthdate], 11, 16
Column3=[birth_time_known], -7, 1
Column4=[rect_system], 5, 2
Column5=[hours], 5, 2
Column6=[minutes], 5, 2
Column7=[am_pm], 12, 4
Column8=[angle], 5, 2
Column9=[sign], 5, 2
Column10=[totalminutes], 5, 2

[CLS:CImportThread]
Type=0
HeaderFile=ImportThread.h
ImplementationFile=ImportThread.cpp
BaseClass=CWinThread
Filter=N

[CLS:CFileListSet]
Type=0
HeaderFile=FileListSet.h
ImplementationFile=FileListSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CFileListSet

[DB:CFileListSet]
DB=1
DBType=ODBC
ColumnCount=9
Column1=[name], 12, 160
Column2=[comments], 12, 250
Column3=[filename], 12, 510
Column4=[filenum], 5, 2
Column5=[IsTextReport], -7, 1
Column6=[FileType], -6, 1
Column7=[counter], 4, 4
Column8=[has_cover], -7, 1
Column9=[has_comments], -7, 1

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

