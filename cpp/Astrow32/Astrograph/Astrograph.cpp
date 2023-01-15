// Astrograph.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Astrograph.h"

#include "MainFrm.h"
#include "astro.h"
#include "useri.h"
#include "fptr.h"
#include "errors.fns"
#include "graphdat.hpp"
#include "paths.hpp"
#include "aspect.h"
#include "radius.h"
#include "asdrawbs.hpp"
#include "asgflags.h"
#include "dataext.h"
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
#include "vicdefs.h"
#include "AstrographDoc.h"
#include "AstrographView.h"
#include "direc.hpp"
#include "folders.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFolders theFolders;
short house_cusps[13];
short alt_cusps[13];
CSingleDocTemplate* pDocTemplate;
Directories theDirectories;
int report_table;
/////////////////////////////////////////////////////////////////////////////
// CAstrographApp

BEGIN_MESSAGE_MAP(CAstrographApp, CWinApp)
	//{{AFX_MSG_MAP(CAstrographApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CAstrographApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrographApp construction

CAstrographApp::CAstrographApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAstrographApp object

CAstrographApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAstrographApp initialization

BOOL CAstrographApp::InitInstance()
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

	//CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAstrographDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAstrographView));
	AddDocTemplate(pDocTemplate);
    pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME1,
		RUNTIME_CLASS(CAstrographDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAstrographView));
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
void CAstrographApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAstrographApp commands
void CAstrographApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	pDocTemplate->OpenDocumentFile(".ASGRA");
}
