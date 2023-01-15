// dbMergeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dbMerge.h"
#include "ado.h"
#include "importerdata.h"
#include "dbMergeDlg.h"
#include "merger.h"
#include "direct.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern BOOL bRunAuto;

char *pConnect = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Persist Security Info=False";

CString getDataDefDir()
{
 int off; 
 char buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_PERSONAL, 1)) {
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

CString GetDatabaseName()
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

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CdbMergeDlg dialog



CdbMergeDlg::CdbMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdbMergeDlg::IDD, pParent)
	, m_source(_T(""))
	, m_dest(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdbMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SOURCE, m_source);
	DDX_Text(pDX, IDC_DEST, m_dest);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_CURRITEM, m_curr_item);
}

BEGIN_MESSAGE_MAP(CdbMergeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DESTLOCATE, OnBnClickedDestlocate)
	ON_BN_CLICKED(IDC_SRCLOCATE, OnBnClickedSrclocate)
END_MESSAGE_MAP()


// CdbMergeDlg message handlers

BOOL CdbMergeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    UpdateData(FALSE);
	// Add "About..." menu item to system menu.
	m_dest =GetDatabasePath();
	
	if ( m_dest.GetLength() > 0 ) {
	   if ( m_dest.Right(1) == "\\" )
		    m_dest+= GetDatabaseName();
	   else {
	       m_dest+= "\\";
           m_dest+= GetDatabaseName();
	   }
	}
	m_source =GetDatabasePath();
	
	if ( m_dest.GetLength() > 0 ) {
	   if ( m_dest.Right(1) == "\\" )
		    m_dest+= "AstrowOldDb.mdb";
	   else {
	       m_dest+= "\\";
           m_dest+= "AstrowOldDB.mdb";
	   }
	}
	char buf[100];
    char buf2[100];
	char inifile[150];
	getcwd(inifile,150);
	if ( inifile[strlen(inifile)-1]=='\\')
		strcat(inifile, "merge.ini");
	else
		strcat(inifile,"\\merge.ini");
	m_table_count = GetPrivateProfileInt("Tables","Count",0,inifile);
	int nItemFrom=-1, nItemTo=-1;
	for ( int i = 1; i <= m_table_count; i++ ) {
	    sprintf( buf, "Table%d", i );
		GetPrivateProfileString("Tables",buf,"",buf2,100,inifile);
		m_tables.SetAtGrow(i,buf2);
        GetPrivateProfileString("Sorts",buf,"",buf2,100,inifile);
		m_sorts.SetAtGrow(i,buf2);
	    GetPrivateProfileString("PKeys",buf,"",buf2,100,inifile);
		m_pkeys.SetAtGrow(i,buf2);
		GetPrivateProfileString("Description",buf,"",buf2,100,inifile);
		m_descrip.SetAtGrow(i,buf2);
		int index = m_list.AddString(buf2);
		m_list.SetItemData(index,i);
		if ( nItemFrom == -1 )
			nItemFrom = index;
		nItemTo = index;
	}
	m_list.SelItemRange(TRUE,nItemFrom,nItemTo);
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

//	// TODO: Add extra initialization here
//	
    UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CdbMergeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CdbMergeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CdbMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CdbMergeDlg::OnBnClickedDestlocate()
{
	// TODO: Add your control notification handler code here
   // szFilters is a text string that includes two file name filters:
   // "*.my" for "MyType Files" and "*.*' for "All Files."
   char szFilters[]=
      "Access Databases (*.mdb)|*.mdb||";
   CString m_start;
   UpdateData(TRUE);

   if ( m_dest.GetLength() > 0 )
	   m_start = m_dest;
   else
	   m_start = "Astrow.mdb";
   // Create an Open dialog; the default file name extension is ".my".
   CFileDialog fileDlg (TRUE, m_start, "*.mdb",
      OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
   
   // Display the file dialog. When user clicks OK, fileDlg.DoModal() 
   // returns IDOK.
   if( fileDlg.DoModal ()==IDOK )
   {
      m_dest = fileDlg.GetPathName();
      UpdateData(FALSE);
   }

}

void CdbMergeDlg::OnBnClickedSrclocate()
{
	// TODO: Add your control notification handler code here
char szFilters[]=
      "Access Databases (*.mdb)|*.mdb||";
   CString m_start;
   UpdateData(TRUE);

   if ( m_source.GetLength() > 0 )
	   m_start = m_source;
   else
	   m_start = "AstrowOldDb.mdb";
   // Create an Open dialog; the default file name extension is ".my".
   CFileDialog fileDlg (TRUE, m_start, "*.mdb",
      OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
   
   // Display the file dialog. When user clicks OK, fileDlg.DoModal() 
   // returns IDOK.
   if( fileDlg.DoModal ()==IDOK )
   {
      m_source = fileDlg.GetPathName();
      UpdateData(FALSE);
   }
}

void CdbMergeDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	char connect[300];
	int items[30];
    m_data.m_source = m_source;
	m_data.m_dest = m_dest;
	m_data.m_pSourceDb = &m_sourceDb;
	m_data.m_pDestDb = &m_destDb;
	m_data.m_pProgress = &m_curr_item;
	int count = m_list.GetSelCount();
	m_list.GetSelItems(30,items);
	m_progress.SetRange(0,count);
	m_progress.SetStep(1);
    CMerger proc(&m_data);
	sprintf(connect,pConnect,(LPCSTR)m_source);
	m_sourceDb.Open(connect);
	sprintf(connect,pConnect,(LPCSTR)m_dest);
	m_destDb.Open(connect);
	for ( int i = 0; i < count; i++ ) {
        int item = m_list.GetItemData(items[i]);
		m_data.m_table = m_tables.GetAt(item);
		m_data.m_sort = m_sorts.GetAt(item);
		m_data.m_pkeys = m_pkeys.GetAt(item);
		m_progress.StepIt();
		proc.process();
	}
	m_sourceDb.Close();
	m_destDb.Close();
	CDialog::OnOK();
}
