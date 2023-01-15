; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCoverPage
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DlgTest.h"
LastPage=0

ClassCount=24
Class1=CDlgTestApp
Class2=CDlgTestDoc
Class3=CDlgTestView
Class4=CMainFrame

ResourceCount=23
Resource1=IDD_BIRTH_INF
Resource2=IDD_COVER_DAT
Resource8=IDD_RECT_DATA
Resource9=IDD_CUSTOM
Resource10=IDD_AST_HELP
Resource11=IDD_QDT_OPTIONS
Resource12=IDD_ABOUTBOX
Resource13=IDD_OPTIONS
Resource14=IDD_ARCHIVE_DAT
Resource15=IDD_TRANS_DATA
Resource16=IDD_RELOC_DAT
Class5=CAboutDlg
Resource3=IDD_FILE_KILL
Resource4=IDD_PRINT_OPT
Resource5=IDD_PROGRESS_DATA
Resource6=IDD_RETURN_DATA
Resource7=IDD_FILE_NAME
Class6=CArchiveData
Class7=CCoverPage
Class8=CCustomize
Class9=CFileEditDlg
Class10=CFileNameDlg
Class11=CFileKillDlg
Class12=CChartOptions
Class13=CProgrData
Class14=CRectifyData
Class15=CReturnData
Class16=CTransData
Class17=CPrintOptions
Class18=CQdtOptions
Class19=CAstroHelper
Class20=COrbEdit
Resource17=IDD_ORB_EDIT
Resource18=IDD_FILE_EDIT
Resource19=IDR_MAINFRAME
Resource20=IDD_DIRECTORIES
Class21=CRelocScr
Resource21=IDD_TRANS_INFO
Class22=CTransScr
Resource22="LOCAT"
Class23=CBirthInfo
Class24=CTransInfo
Resource23="BIRTH"

[CLS:CDlgTestApp]
Type=0
HeaderFile=DlgTest.h
ImplementationFile=DlgTest.cpp
Filter=N

[CLS:CDlgTestDoc]
Type=0
HeaderFile=DlgTestDoc.h
ImplementationFile=DlgTestDoc.cpp
Filter=N

[CLS:CDlgTestView]
Type=0
HeaderFile=DlgTestView.h
ImplementationFile=DlgTestView.cpp
Filter=C
LastObject=CDlgTestView
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T



[CLS:CAboutDlg]
Type=0
HeaderFile=DlgTest.cpp
ImplementationFile=DlgTest.cpp
Filter=D
LastObject=104

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
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_DIALOGS_ARCHIVEFILES
Command12=ID_DIALOGS_COVERPAGEDATA
Command13=ID_DIALOGS_CUSTOMIZE
Command14=ID_DIALOGS_FILEDATAEDIT
Command15=ID_DIALOGS_KILLAFILE
Command16=ID_DIALOGS_FILENAME
Command17=ID_DIALOGS_OPTIONS
Command18=ID_DIALOGS_ORBEDIT
Command19=ID_DIALOGS_PRINTOPTIONS
Command20=ID_DIALOGS_PROGRESSDATA
Command21=ID_DIALOGS_QDTOPTIONS
Command22=ID_DIALOGS_RECTIFICATION
Command23=ID_DIALOGS_RETURNDATA
Command24=ID_DIALOGS_TRANSITDATA
Command25=ID_DIALOGS_DIRECTORIES
Command26=ID_DATARELOCATION
Command27=ID_DATA_TRANSITINFO
Command28=ID_DATA_BIRTHINFO
Command29=ID_APP_ABOUT
CommandCount=29

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

[DLG:IDD_ARCHIVE_DAT]
Type=1
Class=CArchiveData
ControlCount=11
Control1=101,static,1342308352
Control2=ID_ARNAME,edit,1350631552
Control3=ID_ARGRP,button,1342177287
Control4=ID_ARLHA,button,1342177289
Control5=ID_ARZIP,button,1342177289
Control6=ID_ARDELETE,button,1342373891
Control7=103,static,1342308352
Control8=ID_ARCMD,edit,1350631552
Control9=IDOK,button,1342373889
Control10=IDHELP,button,1342242816
Control11=IDCANCEL,button,1342242816

[DLG:IDD_AST_HELP]
Type=1
Class=CAstroHelper
ControlCount=7
Control1=IDCANCEL,button,1342242817
Control2=106,static,1342308352
Control3=ID_AHLIST,listbox,1352728585
Control4=ID_AHVIEW,button,1342242816
Control5=ID_AHPRINT,button,1342242816
Control6=ID_AHCONVERT,button,1342242816
Control7=IDHELP,button,1342242816

[DLG:IDD_TRANS_DATA]
Type=1
Class=CTransData
ControlCount=15
Control1=101,static,1342308352
Control2=ID_TDNUM,edit,1350631424
Control3=103,static,1342308352
Control4=104,static,1342308352
Control5=ID_TDSTART,combobox,1344339971
Control6=106,static,1342308352
Control7=ID_TDEND,combobox,1344339971
Control8=108,static,1342308352
Control9=109,static,1342308352
Control10=ID_TDMO,edit,1350631424
Control11=111,static,1342308352
Control12=ID_TDDAY,edit,1350631424
Control13=IDOK,button,1342242817
Control14=IDHELP,button,1342242816
Control15=IDCANCEL,button,1342242816

[DLG:IDD_RETURN_DATA]
Type=1
Class=CReturnData
ControlCount=31
Control1=101,static,1342308352
Control2=ID_RDBODY,combobox,1342242819
Control3=103,static,1342308352
Control4=104,static,1342308352
Control5=ID_RDSMO,edit,1350631424
Control6=106,static,1342308352
Control7=ID_RDSDAY,edit,1350631424
Control8=108,static,1342308352
Control9=ID_RDSYEAR,edit,1350631424
Control10=110,static,1342308352
Control11=111,static,1342308352
Control12=ID_RDEMO,edit,1350631424
Control13=113,static,1342308352
Control14=ID_RDEDAY,edit,1350631424
Control15=115,static,1342308352
Control16=ID_RDEYEAR,edit,1350631424
Control17=117,static,1342177284
Control18=ID_RDPROG,button,1342242851
Control19=119,static,1342308352
Control20=ID_RDPROGSYS,combobox,1342242819
Control21=121,static,1342308352
Control22=122,static,1342308352
Control23=ID_RDPMO,edit,1350631424
Control24=124,static,1342308352
Control25=ID_RDPDAY,edit,1350631424
Control26=126,static,1342308352
Control27=ID_RDPYEAR,edit,1350631424
Control28=ID_RDTARGET,button,1342242819
Control29=IDOK,button,1342242817
Control30=IDHELP,button,1342242816
Control31=IDCANCEL,button,1342242816

[DLG:IDD_RECT_DATA]
Type=1
Class=CRectifyData
ControlCount=21
Control1=ID_RDCHECK,button,1342242851
Control2=102,static,1342308352
Control3=ID_RDMETHOD,combobox,1344339971
Control4=104,static,1342308352
Control5=105,static,1342308352
Control6=ID_RDHRS,edit,1350631552
Control7=107,static,1342308352
Control8=ID_RDMIN,edit,1350631552
Control9=109,static,1342308352
Control10=ID_RDAMPM,combobox,1342242819
Control11=111,static,1342308352
Control12=ID_RDKNOWNANGL,combobox,1478557699
Control13=113,static,1342308352
Control14=ID_RDKSIGN,combobox,1478557699
Control15=115,static,1342308352
Control16=ID_RDKDEG,edit,1484849280
Control17=117,static,1342308352
Control18=ID_RDKMIN,edit,1484849280
Control19=IDOK,button,1342242817
Control20=IDHELP,button,1342242816
Control21=IDCANCEL,button,1342242816

[DLG:IDD_QDT_OPTIONS]
Type=1
Class=CQdtOptions
ControlCount=19
Control1=ID_QDONCE,button,1342242819
Control2=ID_QDRESTRICTTIM,button,1342242819
Control3=103,static,1342308352
Control4=104,static,1342308352
Control5=ID_QDFHR,edit,1350631424
Control6=106,static,1342308352
Control7=ID_QDFMIN,edit,1350631424
Control8=108,static,1342308352
Control9=ID_QDFAMPM,combobox,1342242819
Control10=110,static,1342308352
Control11=111,static,1342308352
Control12=ID_QDLHR,edit,1350631424
Control13=113,static,1342308352
Control14=ID_QDLMIN,edit,1350631424
Control15=115,static,1342308352
Control16=ID_QDLAMPM,combobox,1342242819
Control17=IDOK,button,1342242817
Control18=IDHELP,button,1342242817
Control19=IDCANCEL,button,1342242816

[DLG:IDD_PROGRESS_DATA]
Type=1
Class=CProgrData
ControlCount=12
Control1=101,static,1342308352
Control2=ID_PDSYSTEM,combobox,1342242819
Control3=103,static,1342308352
Control4=ID_PDMO,edit,1350631424
Control5=105,static,1342308352
Control6=ID_PDDAY,edit,1350631424
Control7=107,static,1342308352
Control8=ID_PDYEAR,edit,1350631424
Control9=ID_PDTARGET,button,1342242819
Control10=IDOK,button,1342242817
Control11=IDHELP,button,1342242816
Control12=IDCANCEL,button,1342242816

[DLG:IDD_PRINT_OPT]
Type=1
Class=CPrintOptions
ControlCount=9
Control1=ID_POCOVER,button,1342242819
Control2=ID_POCMT,button,1342242819
Control3=ID_POHDP1,button,1342242819
Control4=ID_CMTB4T,button,1342242819
Control5=ID_POCTRHD,button,1342242819
Control6=IDOK,button,1342242817
Control7=IDHELP,button,1342242816
Control8=ID_POSTYLES,button,1342242816
Control9=IDCANCEL,button,1342242816

[DLG:IDD_ORB_EDIT]
Type=1
Class=COrbEdit
ControlCount=57
Control1=101,static,1342308352
Control2=ID_AOCONTEXT,combobox,1344339971
Control3=103,static,1342308352
Control4=104,static,1342308352
Control5=105,static,1342308352
Control6=106,static,1342308352
Control7=107,static,1342308352
Control8=108,static,1342308352
Control9=145,static,1342177284
Control10=109,static,1342308352
Control11=ID_AODCONJUNCT,edit,1350631552
Control12=ID_AOICONJUNCT,button,1342242819
Control13=112,static,1342308352
Control14=ID_AODSEXTILE,edit,1350631552
Control15=ID_AOISEXT,button,1342242819
Control16=115,static,1342308352
Control17=ID_AODTRINE,edit,1350631552
Control18=ID_AOITRINE,button,1342242819
Control19=118,static,1342308352
Control20=ID_AODOPPOSE,edit,1350631552
Control21=ID_AOIOPPOSE,button,1342242819
Control22=121,static,1342308352
Control23=ID_AODSQUARE,edit,1350631552
Control24=ID_AOISQUARE,button,1342242819
Control25=124,static,1342308352
Control26=ID_AODSSEXT,edit,1350631552
Control27=ID_AOISSEXT,button,1342242819
Control28=127,static,1342308352
Control29=ID_AODSSQARE,edit,1350631552
Control30=ID_AOISSQUARE,button,1342242819
Control31=130,static,1342308352
Control32=ID_AODSSESQUIQ,edit,1350631552
Control33=ID_AOISSESQUIQ,button,1342242819
Control34=133,static,1342308352
Control35=ID_AODQUIN,edit,1350631552
Control36=ID_AOIQUINCUNX,button,1342242819
Control37=136,static,1342308352
Control38=ID_AODBIQUI,edit,1350631552
Control39=ID_AOIBQUINT,button,1342242819
Control40=139,static,1342308352
Control41=ID_AODQUINTILE,edit,1350631552
Control42=ID_AOIQUINT,button,1342242819
Control43=142,static,1342308352
Control44=ID_AODTREDEC,edit,1350631552
Control45=ID_AOITREDEC,button,1342242819
Control46=199,static,1342308352
Control47=ID_AODDECILE,edit,1350631552
Control48=ID_AOIDECILE,button,1342242819
Control49=151,static,1342177284
Control50=152,static,1342308352
Control51=ID_AODNONPLAN,edit,1350631552
Control52=154,static,1342308352
Control53=ID_AODHSCUSP,edit,1350631552
Control54=ID_AOIHSCUSP,button,1342242851
Control55=IDOK,button,1342242817
Control56=IDHELP,button,1342242816
Control57=IDCANCEL,button,1342242816

[DLG:IDD_OPTIONS]
Type=1
Class=CChartOptions
ControlCount=21
Control1=ID_OPCTGRP,button,1342308359
Control2=ID_OPTROPICAL,button,1342177289
Control3=ID_OPSIDEREAL,button,1342177289
Control4=104,static,1342308352
Control5=ID_OPHOUSEPROC,combobox,1344339971
Control6=ID_OPHOUSES,button,1342373891
Control7=ID_OPASPECTS,button,1342242819
Control8=ID_OPEXTASP,button,1342242819
Control9=ID_OPMISC,button,1342242819
Control10=ID_OPEXTMISC,button,1342242819
Control11=ID_OPSUMMARY,button,1342242819
Control12=ID_OPVERTEAST,button,1342242819
Control13=ID_OPTEXT,button,1342242819
Control14=ID_OPMIDGRP,button,1342177287
Control15=IDOPMBASE,button,1342373891
Control16=ID_OPMHALF,button,1342242819
Control17=ID_OPMFULL,button,1342242819
Control18=ID_OPMMIDASP,button,1342242819
Control19=IDOK,button,1342242816
Control20=IDHELP,button,1342242816
Control21=IDCANCEL,button,1342242816

[DLG:IDD_FILE_NAME]
Type=1
Class=CFileNameDlg
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
Class=CFileKillDlg
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
Class=CFileEditDlg
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

[DLG:IDD_CUSTOM]
Type=1
Class=CCustomize
ControlCount=14
Control1=ID_CSCOGROUP,button,1342308359
Control2=ID_CS_RELOC,button,1342242819
Control3=ID_CSPROGR,button,1342242819
Control4=ID_CSPRGCUSP,button,1342242819
Control5=ID_CSOOGROUP,button,1342308359
Control6=ID_CSTEXT,button,1342373891
Control7=ID_CSGRAPH,button,1342242819
Control8=ID_CSDATAFILE,button,1342242819
Control9=109,static,1342308352
Control10=ID_CSDFTYPE,combobox,1342177283
Control11=ID_CSCUSTOM,button,1342242816
Control12=IDOK,button,1342242817
Control13=IDHELP,button,1342242816
Control14=IDCANCEL,button,1342242816

[DLG:IDD_COVER_DAT]
Type=1
Class=CCoverPage
ControlCount=17
Control1=111,static,1342308352
Control2=ID_CPFONT,combobox,1344339971
Control3=101,static,1342308352
Control4=ID_CPIMAGE,combobox,1344339971
Control5=103,static,1342308352
Control6=ID_CPGRAPHIC,edit,1350632576
Control7=105,static,1342308352
Control8=ID_CPTITLE,edit,1350631552
Control9=107,static,1342308352
Control10=ID_CP_SUBJECT,edit,1350631552
Control11=113,static,1342308352
Control12=ID_CPASTROLOGER,edit,1350631552
Control13=109,static,1342308352
Control14=ID_CPCOMMENT,edit,1352732740
Control15=IDOK,button,1342242817
Control16=IDHELP,button,1342242816
Control17=ID_CANCEL,button,1342242816

[CLS:CArchiveData]
Type=0
HeaderFile=ArchiveData.h
ImplementationFile=ArchiveData.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDHELP

[CLS:CCoverPage]
Type=0
HeaderFile=CoverPage.h
ImplementationFile=CoverPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:CCustomize]
Type=0
HeaderFile=Customize.h
ImplementationFile=Customize.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=109

[CLS:CFileEditDlg]
Type=0
HeaderFile=FileEditDlg.h
ImplementationFile=FileEditDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=101
VirtualFilter=dWC

[CLS:CFileNameDlg]
Type=0
HeaderFile=FileNameDlg.h
ImplementationFile=FileNameDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=101

[CLS:CFileKillDlg]
Type=0
HeaderFile=FileKillDlg.h
ImplementationFile=FileKillDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=101

[CLS:CChartOptions]
Type=0
HeaderFile=ChartOptions.h
ImplementationFile=ChartOptions.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDHELP

[CLS:CProgrData]
Type=0
HeaderFile=ProgrData.h
ImplementationFile=ProgrData.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=101

[CLS:CRectifyData]
Type=0
HeaderFile=RectifyData.h
ImplementationFile=RectifyData.cpp
BaseClass=CDialog
Filter=D
LastObject=102
VirtualFilter=dWC

[CLS:CReturnData]
Type=0
HeaderFile=ReturnData.h
ImplementationFile=ReturnData.cpp
BaseClass=CDialog
Filter=D
LastObject=IDHELP
VirtualFilter=dWC

[CLS:CTransData]
Type=0
HeaderFile=TransData.h
ImplementationFile=TransData.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDHELP

[CLS:CPrintOptions]
Type=0
HeaderFile=PrintOptions.h
ImplementationFile=PrintOptions.cpp
BaseClass=CDialog
Filter=D
LastObject=CPrintOptions
VirtualFilter=dWC

[CLS:CQdtOptions]
Type=0
HeaderFile=QdtOptions.h
ImplementationFile=QdtOptions.cpp
BaseClass=CDialog
Filter=D
LastObject=103
VirtualFilter=dWC

[CLS:CAstroHelper]
Type=0
HeaderFile=AstroHelper.h
ImplementationFile=AstroHelper.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDHELP

[CLS:COrbEdit]
Type=0
HeaderFile=OrbEdit.h
ImplementationFile=OrbEdit.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=101

[DLG:IDD_DIRECTORIES]
Type=1
Class=CTransScr
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
Control12=IDHELP,button,1342242816
Control13=IDCANCEL,button,1342242816

[MNU:"BIRTH"]
Type=1
Class=?
Command1=ID_GETBIRTH
Command2=ID_ADDBIRTH
Command3=ID_REPLACEBIRTH
Command4=ID_DELETEBIRTH
Command5=ID_MAKEPOPUP
Command6=ID_COPYBIRTH
Command7=ID_PASTEBIRTH
Command8=ID_CLEARBIRTH
Command9=ID_RETURN
CommandCount=9

[MNU:"LOCAT"]
Type=1
Class=?
Command1=ID_GETLOCAT
Command2=ID_ADDLOCAT
Command3=ID_REPLACELOCAT
Command4=ID_DELETELOCAT
Command5=ID_COPYLOCAT
Command6=ID_PASTELOCAT
Command7=ID_CLEARLOCAT
Command8=ID_RETURN
CommandCount=8

[DLG:IDD_RELOC_DAT]
Type=1
Class=CRelocScr
ControlCount=31
Control1=117,static,1342308352
Control2=ID_RLCOUNTRY,combobox,1344340226
Control3=120,static,1342308352
Control4=ID_RLSTATE,combobox,1344340226
Control5=122,static,1342308352
Control6=ID_RLLOCATION,combobox,1344340226
Control7=124,static,1342308352
Control8=ID_RLLODEG,edit,1350631424
Control9=126,static,1342308352
Control10=ID_RLLOMIN,edit,1350631424
Control11=129,static,1342308352
Control12=ID_RLEASTWEST,combobox,1342242819
Control13=130,static,1342308352
Control14=ID_RLLADEG,edit,1350631424
Control15=132,static,1342308352
Control16=ID_RLLAMIN,edit,1350631424
Control17=135,static,1342308352
Control18=ID_RLNORTHSOUTH,combobox,1342242819
Control19=136,static,1342308352
Control20=ID_RLTIMEZONE,combobox,1344339971
Control21=138,static,1342308352
Control22=ID_RLSPECCODE,combobox,1344339971
Control23=142,static,1342308352
Control24=ID_RLGMTHR,edit,1350565888
Control25=143,static,1342308352
Control26=ID_RLGMTMIN,edit,1350631424
Control27=144,static,1342308352
Control28=ID_RLMENU,button,1342242816
Control29=IDOK,button,1342242817
Control30=IDHELP,button,1342242816
Control31=IDCANCEL,button,1342242816

[CLS:CRelocScr]
Type=0
HeaderFile=RelocScr.h
ImplementationFile=RelocScr.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=117

[CLS:CTransScr]
Type=0
HeaderFile=TransScr.h
ImplementationFile=TransScr.cpp
BaseClass=CDialog
Filter=D
LastObject=101

[DLG:IDD_BIRTH_INF]
Type=1
Class=CBirthInfo
ControlCount=50
Control1=101,static,1342308352
Control2=ID_BINAME,combobox,1344340226
Control3=103,static,1342308352
Control4=ID_BISEX,combobox,1342242819
Control5=105,static,1342308352
Control6=ID_BIMO,edit,1350631424
Control7=107,static,1342308352
Control8=ID_BIDAY,edit,1350631424
Control9=109,static,1342308352
Control10=ID_BIYEAR,edit,1350631424
Control11=111,static,1342308352
Control12=ID_BIHR,edit,1350631424
Control13=113,static,1342308352
Control14=ID_BIMIN,edit,1350631424
Control15=115,static,1342308352
Control16=ID_BIAMPM,combobox,1342242819
Control17=117,static,1342308352
Control18=118,static,1342308352
Control19=ID_RLCOUNTRY,combobox,1344340226
Control20=120,static,1342308352
Control21=ID_RLSTATE,combobox,1344340226
Control22=122,static,1342308352
Control23=ID_RLLOCATION,combobox,1344340226
Control24=124,static,1342308352
Control25=ID_RLLODEG,edit,1350631424
Control26=126,static,1342308352
Control27=ID_RLLOMIN,edit,1350631424
Control28=129,static,1342308352
Control29=ID_RLEASTWEST,combobox,1342242819
Control30=130,static,1342308352
Control31=ID_RLLADEG,edit,1350631424
Control32=132,static,1342308352
Control33=ID_RLLAMIN,edit,1350631424
Control34=135,static,1342308352
Control35=ID_RLNORTHSOUTH,combobox,1342242819
Control36=136,static,1342308352
Control37=ID_RLTIMEZONE,combobox,1344339971
Control38=138,static,1342308352
Control39=ID_RLSPECCODE,combobox,1344339971
Control40=142,static,1342308352
Control41=ID_RLGMTHR,edit,1350631424
Control42=143,static,1342308352
Control43=ID_RLGMTMIN,edit,1350631424
Control44=144,static,1342308352
Control45=ID_BIMENU,button,1342242816
Control46=ID_BIRECT,button,1342242816
Control47=ID_RLMENU,button,1342242816
Control48=IDOK,button,1342242817
Control49=IDHELP,button,1342242816
Control50=IDCANCEL,button,1342242816

[DLG:IDD_TRANS_INFO]
Type=1
Class=CTransInfo
ControlCount=46
Control1=101,static,1342308352
Control2=ID_BINAME,combobox,1344340226
Control3=105,static,1342308352
Control4=ID_BIMO,edit,1350639616
Control5=107,static,1342308352
Control6=ID_BIDAY,edit,1350639616
Control7=109,static,1342308352
Control8=ID_BIYEAR,edit,1350639616
Control9=111,static,1342308352
Control10=ID_BIHR,edit,1350639616
Control11=113,static,1342308352
Control12=ID_BIMIN,edit,1350639616
Control13=115,static,1342308352
Control14=ID_BIAMPM,combobox,1342242819
Control15=117,static,1342308352
Control16=118,static,1342308352
Control17=ID_RLCOUNTRY,combobox,1344340226
Control18=120,static,1342308352
Control19=ID_RLSTATE,combobox,1344340226
Control20=122,static,1342308352
Control21=ID_RLLOCATION,combobox,1344340226
Control22=124,static,1342308352
Control23=ID_RLLODEG,edit,1350639616
Control24=126,static,1342308352
Control25=ID_RLLOMIN,edit,1350639616
Control26=129,static,1342308352
Control27=ID_RLEASTWEST,combobox,1342242819
Control28=130,static,1342308352
Control29=ID_RLLADEG,edit,1350639616
Control30=132,static,1342308352
Control31=ID_RLLAMIN,edit,1350639616
Control32=135,static,1342308352
Control33=ID_RLNORTHSOUTH,combobox,1342242819
Control34=136,static,1342308352
Control35=ID_RLTIMEZONE,combobox,1344339971
Control36=138,static,1342308352
Control37=ID_RLSPECCODE,combobox,1344339971
Control38=142,static,1342308352
Control39=ID_RLGMTHR,edit,1350631424
Control40=143,static,1342308352
Control41=ID_RLGMTMIN,edit,1350631424
Control42=144,static,1342308352
Control43=ID_RLMENU,button,1342242816
Control44=IDOK,button,1342242817
Control45=IDHELP,button,1342242816
Control46=IDCANCEL,button,1342242816

[CLS:CBirthInfo]
Type=0
HeaderFile=BirthInfo.h
ImplementationFile=BirthInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDHELP

[CLS:CTransInfo]
Type=0
HeaderFile=TransInfo.h
ImplementationFile=TransInfo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDHELP

