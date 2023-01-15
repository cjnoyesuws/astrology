// importtoolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
//#include "progress.h"
#include "importerdata.h"
#include "importtoolDlg.h"
#include "importbirths.h"
#include "importlocations.h"
#include "importFileList.h"
#include "direc.hpp"
#include <io.h>
#include <direct.h>
#include ".\importtooldlg.h"

extern BOOL bRunAuto;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//Directories theDirectories;


CString getDataDefDir()
{
 int off; 
 char buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_COMMON_DOCUMENTS, 1)) {
	 CString ret = "C:\\ASTROW";
	 return ret;
 }
 strcat( buf, "\\Astro For Windows");
 if ( _access(buf, 0 ) )
	 mkdir(buf);
 CString def = buf;
 return( def );
}

CString GetDatabasePath()
{
 char buf[255];

 memset(buf,0,255);
 DWORD len, type;
 HKEY hkeysub;
 DWORD succ = RegOpenKey(HKEY_CURRENT_USER,"Software\\Christopher J. Noyes Software\\ASTRO For Windows\\Directories",&hkeysub);
 succ = RegQueryValueEx( hkeysub, "DB", NULL, &type,(LPBYTE)buf,&len);
 RegCloseKey(hkeysub);
 if ( !strlen(buf) )
	 strcpy(buf,(LPCTSTR)getDataDefDir());
 if ( buf[strlen(buf)-1]=='\\' )
    strcat(buf,"\\");
 return( CString(buf));
}

CString GetDatabaseNameOnly()
{
 char buf[255];

 memset(buf,0,255);
 DWORD len, type;
 HKEY hkeysub;
 DWORD succ = RegOpenKey(HKEY_CURRENT_USER,"Software\\Christopher J. Noyes Software\\ASTRO For Windows\\Database",&hkeysub);
 succ = RegQueryValueEx( hkeysub, "DatabaseName", NULL, &type,(LPBYTE)buf,&len);
 RegCloseKey(hkeysub);
 if ( !strlen(buf) )
	 strcpy(buf,"astrow.mdb");
 if ( buf[strlen(buf)-1]=='\\' )
    strcat(buf,"\\");
 return( CString(buf));
}


/*CString GetDatabaseName()
{
 CString str = GetDatabasePath();
 if ( str.Right(1)=="\\" )
	 str += GetDatabaseNameOnly();
 else {
     str += "\\";
     str += GetDatabaseNameOnly();
 }
 return str;
}
*/
void doImports(ImporterData *pImpData );

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

/////////////////////////////////////////////////////////////////////////////
// CImporttoolDlg dialog

CImporttoolDlg::CImporttoolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImporttoolDlg::IDD, pParent)
	, m_olddir(_T("C:\\ASTROW\\"))
{
	//{{AFX_DATA_INIT(CImporttoolDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	char buf[250];
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_data.m_olddir = m_olddir;
	m_data.m_dbdir = GetDatabasePath();
}

void CImporttoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImporttoolDlg)
	//DDX_Text(pDX, IDC_DB, m_data.m_dbdir);
	//DDX_Text(pDX, IDC_TXTDR, m_data.m_txtdir);
	//DDX_Text(pDX, IDC_USER, m_data.m_userdir);
	//DDX_Check(pDX, IDC_TEXT, m_data.m_text);
	DDX_Check(pDX, IDC_LOCS, m_data.m_locs);
	DDX_Check(pDX, IDC_FILE_LIST, m_data.m_files);
	DDX_Check(pDX, IDC_BIRTHS, m_data.m_births);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_OLDDIR, m_data.m_olddir);
	DDV_MaxChars(pDX, m_data.m_olddir, 255);
	DDX_Control(pDX, IDC_TASKS2, m_tasks);
	DDX_Control(pDX, IDC_RECORDS2, m_records);
}

BEGIN_MESSAGE_MAP(CImporttoolDlg, CDialog)
	//{{AFX_MSG_MAP(CImporttoolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SELECT, OnBnClickedSelect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImporttoolDlg message handlers

BOOL CImporttoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImporttoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImporttoolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	if ( bRunAuto ) {
	   bRunAuto=FALSE;
	   OnOK();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImporttoolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImporttoolDlg::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);
    m_data.m_progress = this;
	doImports(&m_data);
	CDialog::OnOK();
}


void doImports(ImporterData *pImpData )
{
    // do something with 'pObject'
    char buf[200];
	int cnt = 0;
	if ( pImpData->m_births )
		cnt++;
	if ( pImpData->m_locs )
		cnt++;
	if ( pImpData->m_files )
		cnt++;
	pImpData->m_progress->m_tasks.SetRange(0,cnt*10);
    pImpData->m_progress->m_tasks.SetStep(10);
	if ( pImpData->m_births ) {
       CImportBirths *pImpBirth = new CImportBirths( pImpData->m_olddir, pImpData->buffer, pImpData);
       pImpBirth->process();
	   delete pImpBirth;
	   pImpData->m_progress->m_tasks.StepIt();
	   pImpData->m_progress->Invalidate(0);
	   ( (CImporttoolApp *) AfxGetApp() )->_Yield(10);
	   }
	if ( pImpData->m_locs ) {
	   CImportLocations *pImpLoc = new CImportLocations( pImpData->m_olddir, pImpData->buffer, pImpData );
	   pImpLoc->process();
	   delete pImpLoc;
	   pImpData->m_progress->m_tasks.StepIt();
	   pImpData->m_progress->Invalidate(0);
	   ( (CImporttoolApp *) AfxGetApp() )->_Yield(10);
	   }
    if ( pImpData->m_files ) {
	   CImportFileList *pImpFlist = new CImportFileList( pImpData->m_olddir, pImpData->buffer, pImpData);
	   pImpFlist->process();
	   delete pImpFlist;
	   pImpData->m_progress->m_tasks.StepIt();
	   pImpData->m_progress->Invalidate(0);
	   ( (CImporttoolApp *) AfxGetApp() )->_Yield(10);
	   WinExec("Copier *.gra", SW_HIDE);
	   WinExec("Copier *.out", SW_HIDE);
	   } 
	( (CImporttoolApp *) AfxGetApp() )->_Yield(30);
    
}

BOOL CImporttoolDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::DestroyWindow();
}

void CImporttoolDlg::OnBnClickedSelect()
{
	// TODO: Add your control notification handler code here
  CFileDialog fd(TRUE,".DAT" );
  if ( fd.DoModal() == IDOK ) {
	  CString str = fd.GetPathName();
	  int pos = str.ReverseFind('\\');
      str = str.Left(pos+1);
      m_data.m_olddir = str;
	  UpdateData(FALSE);
  }

}
