// Astroview.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Astrow.h"
#include "MainFrm.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "utlduad.h"
#include "fptr.h"
#include "tabs.hpp"
#include "virttext.hpp"
#include "AstroviewDoc.h"
#include "AstroviewView.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Directories theDirectories;

PROGR_DATA progress_data;
TRANS_DATA transit_data;
RECT_DATA birth_rectd, comp_rectd, trans_rectd;
RETURN_DATA return_data;
BIRTH_DB birth_rec, comp_rec, trans_rec;
LOC_DB reloc_data;
short birth_ok, birth_rect_ok = 1, comp_ok, comp_rect_ok = 1,
    trans_ok, trans_data_ok, prog_ok;
AS_INF near birth_inf[18], near alt_inf[18];
AS_INF_EXT near birth_ext[18], near alt_ext[18];
short near house_cusps[13], near alt_cusps[13];
DATA_PACKET birth_dp = { NATAL_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
comp_dp = { COMPA_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
trans_dp = { TRANS_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, NULL },
progr_dp = { PROGR_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
return_dp = { RETUR_CH, &birth_rectd, NULL, &progress_data, &return_data, NULL, &reloc_data, NULL },
reloc_dp = { RELOC_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
compos_dp = { COMPO_CH|RELOC_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, &comp_rectd },
fixed_dp = { FIXED_CH, &birth_rectd, NULL, &progress_data, NULL, NULL, &reloc_data, NULL },
arabp_dp = { ARABP_CH, &birth_rectd, NULL, &progress_data,  NULL, NULL, &reloc_data, NULL },
comptr_dp = { COMPO_CH|TRANS_CH|RELOC_CH, &birth_rectd, &transit_data, &progress_data, NULL, NULL, &reloc_data, &comp_rectd };


/////////////////////////////////////////////////////////////////////////////
// CAstroviewApp

BEGIN_MESSAGE_MAP(CAstroviewApp, CWinApp)
	//{{AFX_MSG_MAP(CAstroviewApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroviewApp construction

CAstroviewApp::CAstroviewApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAstroviewApp object

CAstroviewApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAstroviewApp initialization

BOOL CAstroviewApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings(6);  // Load standard INI file options (including MRU)
	theDirectories.getFromIni();
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAstroviewDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAstroviewView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

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
void CAstroviewApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAstroviewApp commands
