// Astrow.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Astrow.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "charcons.h"
#include "tabs.hpp"
#include "virttext.hpp"
#include "paths.hpp"
#include "coverdat.hpp"
#include "AstroviewDoc.h"
#include "AstroviewView.h"
#include "afxcoll.h"
#include "filelst.hpp"
#include "astroflistDoc.h"
#include "astroflistView.h"
#include <afxhtml.h>
#include "astrogriddoc.h"
#include "astrogridview.h"
#include "fptr.h"
#include "graphdat.hpp"
#include "aspect.h"
#include "radius.h"
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "datagrfa.hpp"
#include "polar.hpp"
#include "arndcirc.hpp"
#include "grlist.hpp"
#include "plotplan.hpp"
#include "plothous.hpp"
#include "plotslin.hpp"
#include "tickcirc.hpp"
#include "graspgrd.hpp"
#include "graspcir.hpp"
#include "key.hpp"
#include "datakey.hpp"
#include "plotgrtp.hpp"
#include "graopt.hpp"
#include "inifile.hpp"
#include "grafont.hpp"
#include "AstrographDoc.h"
#include "vicdefs.h"
#include "AstrographView.h"
#include "direc.hpp"
#include "utlduad.h"
#include "setup.hpp"
#include "AstrowCmdLine.h"
#include "qdtopt.hpp"
#include "splashwnd.h"
#include "strtransform.h"
#include <io.h>
#include <sys\stat.h>
#include "folders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int write_birth_data(char *file);
void kill_textmgr();
int read_birth_data(char *file);

FILE *logstream;

//CString RelocationPersonal;
Directories theDirectories;
CFolders theFolders;
FileListArray AstFileList;
CStrTransform *pTransformers;
int m_dial;
int m_harmonic;
PROGR_DATA progress_data;
TRANS_DATA transit_data;
RECT_DATA birth_rectd, comp_rectd, trans_rectd;
RETURN_DATA return_data;
BIRTH_DB birth_rec, comp_rec, trans_rec;
LOC_DB reloc_data;
DIREC_DATA solar_data;
short birth_ok, birth_rect_ok = 1, comp_ok, comp_rect_ok = 1,
    trans_ok, trans_data_ok, prog_ok;
AS_INF near birth_inf[32], near alt_inf[32];
AS_INF_EXT near birth_ext[32], near alt_ext[32];
short near house_cusps[13], near alt_cusps[13];
DATA_PACKET birth_dp = { NATAL_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
comp_dp = { COMPA_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, &comp_rectd, &m_harmonic, &m_dial },
trans_dp = { TRANS_CH, &birth_rectd, &transit_data, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
progr_dp = { PROGR_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
return_dp = { RETUR_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
reloc_dp = { RELOC_CH, &birth_rectd, NULL, &progress_data,  &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
compos_dp = { COMPO_CH|RELOC_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, &comp_rectd, &m_harmonic, &m_dial },
fixed_dp = { FIXED_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
arabp_dp = { ARABP_CH, &birth_rectd, NULL, &progress_data,  &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
comptr_dp = { COMPO_CH|TRANS_CH|RELOC_CH, &birth_rectd, &transit_data, &progress_data, &return_data, &solar_data, &reloc_data, &comp_rectd, &m_harmonic, &m_dial },
solar_dp = { NATAL_CH|SOLAR_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial },
harmonic_dp = { NATAL_CH|HARMON_CH, &birth_rectd, NULL, &progress_data, &return_data, &solar_data, &reloc_data, NULL, &m_harmonic, &m_dial };




/////////////////////////////////////////////////////////////////////////////
// CAstrowApp

BEGIN_MESSAGE_MAP(CAstrowApp, CWinApp)
	//{{AFX_MSG_MAP(CAstrowApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	//ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrowApp construction

CAstrowApp::CAstrowApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//logstream = fopen("C:\\log.txt", "wt" );
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAstrowApp object

CAstrowApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAstrowApp initialization

void CAstrowApp::OpenFlists()
{
    ((CDocTemplate *)pFlist)->OpenDocumentFile(NULL);
    ((CDocTemplate *)pFlist)->OpenDocumentFile(NULL);
	((CDocTemplate *)pFlist)->OpenDocumentFile(NULL);
}


BOOL CAstrowApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	m_nCmdShow = SW_SHOWMAXIMIZED;
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	SetRegistryKey("Christopher J. Noyes Software");
	//fputs("3d controls\n", logstream);
    AfxEnableControlContainer();
	//fputs("control cont\n", logstream);
	AfxInitRichEdit();
	//fputs("richedit\n", logstream);
	AfxOleInit();
	//fputs("ole\n", logstream);
	LoadStdProfileSettings(6);  // Load standard INI file options (including MRU)
	//fputs("profile\n", logstream);
	theDirectories.getFromIni();
	//fputs("directories\n", logstream);
    setup_dat.readFromIni();
	//fputs("setup\n", logstream);
    theFolders.getFromIni();
	//fputs("folders\n", logstream);
	birth_rectd.birth_time_known = 1;
    comp_rectd.birth_time_known = 1;
    trans_rectd.birth_time_known = 1;
 	//fputs("history\n", logstream);
	read_birth_data( set_path( "ASTRODAT.HIS", USER_F ) );
    read_birth_data( set_path( "ASTRODAT.DEF", USER_F ) );
	AstFileList.GetCurFolder() = DEFAULT_FLD;
	//fputs("file list\n", logstream);
	AstFileList.setName("NASTFIL.LST");
    AstFileList.read();
    

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	//fputs("start doctemplates\n", logstream);
	CNewMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTROGTYPE,
		RUNTIME_CLASS(CAstrographDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstrographView));
	AddDocTemplate((CMultiDocTemplate*)pDocTemplate);
	pGraph = pDocTemplate;
	pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTROGTYPE1,
		RUNTIME_CLASS(CAstrographDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstrographView));
	AddDocTemplate((CMultiDocTemplate*)pDocTemplate);
	pNewGraph = pDocTemplate;
	pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTROVTYPE,
		RUNTIME_CLASS(CAstroviewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstroviewView));
	AddDocTemplate((CMultiDocTemplate*)pDocTemplate);
	pText = pDocTemplate;
	pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTROVTYPE1,
		RUNTIME_CLASS(CAstroviewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstroviewView));
	pNewText = pDocTemplate;
	AddDocTemplate((CMultiDocTemplate*)pDocTemplate);
	pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTROHTYPE,
		RUNTIME_CLASS(CAstroviewDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstroviewView));
	AddDocTemplate(pDocTemplate);
	pHelp = pDocTemplate;
		pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTRGRDTYPE,
		RUNTIME_CLASS(CAstrogridDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstrogridView));
	AddDocTemplate(pDocTemplate);
	pGrid = pDocTemplate;
	pDocTemplate = new CNewMultiDocTemplate(
		IDR_ASTRFLTYPE,
		RUNTIME_CLASS(CAstroflistDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAstroflistView));
	pFlist = pDocTemplate;
	AddDocTemplate((CMultiDocTemplate*)pDocTemplate);
	//fputs("start shell\n", logstream);
			// Enable DDE Execute open
	EnableShellOpen();
	//fputs("start types\n", logstream);
	RegisterShellFileTypes(FALSE);
    //fputs("transform\n", logstream);
	pTransformers = new CStrTransform(0);
	//fputs("frame\n", logstream);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	m_pMainWnd->DragAcceptFiles();
	// Parse command line for standard shell commands, DDE, file open
	CAstrowCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
    //fputs("parsecmd\n", logstream);
	if ( cmdInfo.m_bQdt == TRUE && checkQdt() == FALSE )
	   return FALSE;
	else if ( cmdInfo.m_bQdt == TRUE ) {
	   int ret = MessageBox( NULL, "Now Your Daily Chart Will be Compiled!", "ASTRO For Windows", MB_ICONQUESTION|MB_YESNOCANCEL );
	   if ( ret == IDNO || ret == IDCANCEL )
		  return FALSE;
	   read_birth_data( set_path( "QDTRADAT.HIS", USER_F ) );
       read_birth_data( set_path( "QDTRADAT.DEF", USER_F ) );
 	   }
	//fputs("qdt\n", logstream);
	// Dispatch commands specified on the command line
	if ( cmdInfo.m_nShellCommand != CCommandLineInfo::FileNew ) {
	   if (!ProcessShellCommand(cmdInfo))
	    	return FALSE;
	   }
	// The main window has been initialized, so show and update it.
	//fputs("show\n", logstream);
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	if ( cmdInfo.m_bQdt == TRUE )
	   pMainFrame->DoQdt();
	//fputs("splash\n", logstream);
	if ( cmdInfo.m_bShowSplash == TRUE ) {
	   CSplashWnd * psp = new CSplashWnd(pMainFrame);
	   psp->ShowWindow(SW_SHOW);
	   }
	OpenFlists();
	//fputs("end\n", logstream);
	//fclose(logstream);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAstrowApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowApp commands

void CAstrowApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	
}

void CAstrowApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}


void CAstrowCommandLineInfo::ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast )
{
if ( bFlag == TRUE ) { 
   if ( !strcmpi( lpszParam, "QDT" ) ) {
	  m_bQdt = TRUE;
#ifdef DEMO
m_bShowSplash = TRUE;
#else
m_bShowSplash = FALSE;
#endif      
	  
      }
   else
	  m_bQdt = FALSE;
   }
CCommandLineInfo::ParseParam( lpszParam, bFlag, bLast );
}


BOOL CAstrowApp::checkQdt() 
{
	// TODO: Add your command handler code here
 SYSTEMTIME tm;
 TIME_ZONE_INFORMATION tzi;
 QdtData qdt;
 int hr;
 
 qdt.getFromIni();
 GetSystemTime(&tm);
 GetTimeZoneInformation(&tzi);
 tm.wHour -= (tzi.Bias/60);

 if ( qdt.getRunOnce() && tm.wDay == qdt.getLastDay()
		      && tm.wMonth == qdt.getLastMonth() ) {
    		return( FALSE );
    	}
    else if ( qdt.getRestrictTime() ) {
   	  if ( qdt.getFirstHours() < qdt.getLastHours() ) {
    	   if ( ( tm.wHour < qdt.getFirstHours() || tm.wHour > qdt.getLastHours() ) ||
	    	(qdt.getFirstHours() == tm.wHour && tm.wMinute < qdt.getFirstMin() ) ||
	    	(qdt.getLastHours() == tm.wHour && tm.wMinute > qdt.getLastMin() )  ) {
	  	    return(FALSE);
	  	    }
      	}
    	else {
       	int l = qdt.getLastHours()+24;
       	if ( qdt.getLastHours() == tm.wHour )
	  	   tm.wHour += 24;
       	else if ( tm.wHour < qdt.getLastHours() )
	  	   tm.wHour += 24;
       	if ( (hr < qdt.getFirstHours() || tm.wHour > l ) ||
	     	(qdt.getFirstHours() == hr && tm.wMinute < qdt.getFirstMin() ) ||
	    	(l == hr && tm.wMinute > qdt.getLastMin() )  ) {
	  	   return(FALSE);
       	   }
       	}
      }
return( TRUE );
    
}

int CAstrowApp::_Yield(int n)
{
    _AFX_THREAD_STATE* pState = AfxGetThreadState();

	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;
	int i;

	// acquire and dispatch messages until a WM_QUIT message is received.
	for (i = 0; i < n+2; i++)	 
	{
		if (!::PeekMessage(&(pState->m_msgCur), NULL, NULL, NULL, PM_NOREMOVE))
		   return( 0 );
		if ( !AfxGetThread()->PumpMessage() )
		   return( 0 );
	}

 return( 1 );
}

int CAstrowApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	write_birth_data( set_path( "ASTRODAT.HIS", USER_F ) );
    AstFileList.write();
	//AstFileList.free();
	kill_textmgr();
   delete pTransformers;
   theDirectories.CloseDb();
   if ( theDirectories.m_pDatabase!=theDirectories.m_pTextDatabase)
	   delete theDirectories.m_pTextDatabase;
   delete theDirectories.m_pDatabase;
   return CWinApp::ExitInstance();
}

int CAstrowApp::OpenDocSendCmdWait(enum filetype type, LPCTSTR lpszDoc, UINT cmd )
{
CNewMultiDocTemplate *pTmp;
CDocument *pDoc;
CFrameWnd* pFrame;
switch( type ) 	{
	case GraphTypeFile :
    	 pTmp = pGraph;
	     break;
	case TextTypeFile :
	     pTmp = pText;
	     break;
    case NewGraphTypeFile :
    	 pTmp = pNewGraph;
	     break;
	case NewTextTypeFile :
	     pTmp = pNewText;
	     break;
	case HelpTypeFile :
	     pTmp = pHelp;
	     break;
    case GridTypeFile :
	     pTmp = pGrid;
	     break;
	default :
	     break;
	}
pDoc =pTmp->OpenDocumentFile(lpszDoc, TRUE, &pFrame);
if ( pDoc == NULL || pFrame == NULL )
   return( 0 );
if ( type == GraphTypeFile || type==NewGraphTypeFile )
   ((CAstrographDoc *)pDoc)->SetCanClose(0);
else if ( type == GridTypeFile )
   ((CAstrogridDoc *)pDoc)->SetCanClose(0);
else 
   ((CAstroviewDoc *)pDoc)->SetCanClose(0);
//_Yield(4);
if ( type == GraphTypeFile || type==NewGraphTypeFile ) {
   if ( cmd == ID_FILE_PRINT )
      ((CAstrographDoc *)pDoc)->DoPrint();
   else
      ((CAstrographDoc *)pDoc)->DoExport();
		}
else if ( type == GridTypeFile ) {
   if ( cmd == ID_FILE_PRINT )
      ((CAstrogridDoc *)pDoc)->DoPrint();
		}
   else 
   ((CAstroviewDoc *)pDoc)->DoPrint();
//_Yield(4);  
while ( !pDoc->CanCloseFrame(pFrame) );
	  //_Yield(2);
pFrame->Invalidate(TRUE);
_Yield(4);
pDoc->OnCloseDocument();
return( 1 );
}

int CAstrowApp::OpenDocBatchSendCmdWait(enum filetype type, LPCTSTR lpszDoc, UINT cmd, CStringArray *pAr, int cnt )
{
CNewMultiDocTemplate *pTmp;
CDocument *pDoc;
CFrameWnd* pFrame;
switch( type ) 	{
	case GraphTypeFile :
    	 pTmp = pGraph;
	     break;
	case TextTypeFile :
	     pTmp = pText;
	     break;
	case NewGraphTypeFile :
    	 pTmp = pNewGraph;
	     break;
	case NewTextTypeFile :
	     pTmp = pNewText;
	     break;
	case HelpTypeFile :
	     pTmp = pHelp;
	     break;
    case GridTypeFile :
	     pTmp = pGrid;
	     break;
	default :
	     break;
	}
pDoc =pTmp->OpenDocumentFile(lpszDoc,TRUE, &pFrame);
if ( pDoc == NULL || pFrame == NULL )
   return( 0 );
//_Yield(1);
switch( type ) 	{
	case GraphTypeFile :
	case NewGraphTypeFile :
    	((CAstrographDoc *)pDoc)->SetMultiFiles( pAr, cnt );
	     break;
	case TextTypeFile :
	case NewTextTypeFile :
	case HelpTypeFile :
	     ((CAstroviewDoc *)pDoc)->SetMultiFiles( pAr, cnt );
	     break;
    case GridTypeFile :
	     ((CAstrogridDoc *)pDoc)->SetMultiFiles( pAr, cnt );
	     break;
	default :
	     break;
	}
if ( type == GraphTypeFile || type==NewGraphTypeFile )
   ((CAstrographDoc *)pDoc)->SetCanClose(0);
else if ( type == GridTypeFile )
   ((CAstrogridDoc *)pDoc)->SetCanClose(0);
else
   ((CAstroviewDoc *)pDoc)->SetCanClose(0);
if ( type == GraphTypeFile || type==NewGraphTypeFile ) {
   if ( cmd == ID_FILE_PRINT )
      ((CAstrographDoc *)pDoc)->DoPrint();
   else
      ((CAstrographDoc *)pDoc)->DoExport();
		}
else if ( type == GridTypeFile ) {
   if ( cmd == ID_FILE_PRINT )
      ((CAstrogridDoc *)pDoc)->DoPrint();
		}   
   else 
   ((CAstroviewDoc *)pDoc)->DoPrint();
//_Yield(1);  
while ( !pDoc->CanCloseFrame(pFrame) );
pFrame->Invalidate(TRUE);
_Yield(4);
pDoc->OnCloseDocument();
return( 1 );
}
