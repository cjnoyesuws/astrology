// importtool.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "importtool.h"
#include "progress.h"
#include "importerdata.h"
#include "importtoolDlg.h"
#include ".\importtool.h"
#include "direc.hpp"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProgress **pProg=0;
ImporterData *pImpData=0;
HANDLE **phThread=0;
CWinThread **pwThread=0;
CImporttoolDlg *pDialog;
Directories theDirectories;
BOOL bRunAuto;
/////////////////////////////////////////////////////////////////////////////
// CImporttoolApp

BEGIN_MESSAGE_MAP(CImporttoolApp, CWinApp)
	//{{AFX_MSG_MAP(CImporttoolApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImporttoolApp construction

CImporttoolApp::CImporttoolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CImporttoolApp object

CImporttoolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CImporttoolApp initialization

BOOL CImporttoolApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	if ( strstr(AfxGetApp()->m_lpCmdLine,"-auto") == NULL )
		bRunAuto = FALSE;
	else if (!_access("C:\\ASTROW\\NBIRTHBS.DAT",0)) {
		if ( AfxMessageBox("Do You Want to Automatically Merge All Your Old Data?",
			  MB_YESNO ) == IDYES )
		   bRunAuto=TRUE;
		else
		   bRunAuto=FALSE;
	}
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
    SetRegistryKey("Christopher J. Noyes Software");
	pDialog = new CImporttoolDlg(NULL);
	m_pMainWnd = pDialog;
    theDirectories.getFromIni();
	pDialog->Create(CImporttoolDlg::IDD, NULL);
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return TRUE;
}

int CImporttoolApp::_Yield(int n)
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

BOOL CImporttoolApp::InitApplication()
{
 return TRUE;
}

BOOL CImporttoolApp::OnIdle( LONG lCount)
{
 return( CWinApp::OnIdle(lCount) );
}
int CImporttoolApp::ExitInstance()
{
	theDirectories.CloseDb();
	// TODO: Add your specialized code here and/or call the base class
	return CWinApp::ExitInstance();
}
