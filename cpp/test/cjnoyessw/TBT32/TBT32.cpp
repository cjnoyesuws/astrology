// TBT32.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TBT32.h"

#include "MainFrm.h"
#include "fileary.hpp"
#include "symbol.hpp"
#include "strtransform.h"
#include "texttypeary.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSymbolAry *pRegSymbols;
CRSymbolAry *pRepSymbols;
CStrTransform *pTransformers;
CAsFileAry *pFileList;
CATextTypeAry *pATextTypes;

/////////////////////////////////////////////////////////////////////////////
// CTBT32App

BEGIN_MESSAGE_MAP(CTBT32App, CWinApp)
	//{{AFX_MSG_MAP(CTBT32App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTBT32App construction

CTBT32App::CTBT32App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTBT32App object

CTBT32App theApp;

/////////////////////////////////////////////////////////////////////////////
// CTBT32App initialization

BOOL CTBT32App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
   AfxInitRichEdit();
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Christopher J. Noyes Software"));

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
   pFrame->ShowWindow(SW_SHOW);
   pFrame->UpdateWindow();
   pFileList = new CAsFileAry();
   pFileList->Load();
   pTransformers = new CStrTransform();
   pTransformers->Load();
   //AfxMessageBox("After Trans");
   pRegSymbols=new CSymbolAry();
   pRegSymbols->Load();
   pRepSymbols=new CRSymbolAry();
   pRepSymbols->Load();
   pATextTypes = new CATextTypeAry;
   pATextTypes->Load();
   //AfxMessageBox("lists loaded");

	// The one and only window has been initialized, so show and update it.
   

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CTBT32App message handlers





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
void CTBT32App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CTBT32App message handlers


int CTBT32App::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
   delete pFileList;
   delete pTransformers;
   delete pRegSymbols;
   delete pRepSymbols;
   delete pATextTypes;
	return CWinApp::ExitInstance();
}
