// Setup.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "Setup.h"
#include <io.h>
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetup dialog


CSetup::CSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetup)
	m_Dir = _T("");
	m_dbdir = _T("");
	m_database = _T("");
	//}}AFX_DATA_INIT
}


void CSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetup)
	DDX_Text(pDX, IDC_DIR, m_Dir);
	DDX_Text(pDX, IDC_DBDIR, m_dbdir);
	DDX_Text(pDX, IDC_DSN, m_database);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetup, CDialog)
	//{{AFX_MSG_MAP(CSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetup message handlers

void CSetup::OnOK() 
{
	// TODO: Add extra validation here
   char	buf[100];
   UpdateData(TRUE);
   AfxGetApp()->WriteProfileString(_T("TBT"),_T("DatabaseName"),(LPCTSTR)m_database);
	AfxGetApp()->WriteProfileString(_T("TBT"),_T("TEXTDIR"),(LPCTSTR)m_Dir);
   AfxGetApp()->WriteProfileString(_T("TBT"),_T("DBDIR"),(LPCTSTR)m_dbdir);
   CDialog::OnOK();
}

void CSetup::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CSetup::OnInitDialog() 
{
   CDialog::OnInitDialog();
	char buf[100], dsn[25];
   m_database=GetDatabaseName();
   m_Dir=GetSrcDir();
   m_dbdir=GetDatabasePath();
	// TODO: Add extra initialization here
   UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString getDataDefDir()
{
 int off; 
 TCHAR buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_PERSONAL, 1)) {
	 CString ret = _T("C:\\ASTROW");
	 return ret;
 }
 _tcscat( buf, _T("\\Astro For Windows"));
 if ( _taccess(buf, 0 ) )
	 _tmkdir(buf);
 CString def = buf;
 return( def );
}

CString getProgDefDir()
{
 int off; 
 TCHAR buf[200];
 if (!SHGetSpecialFolderPath( NULL, buf, CSIDL_PROGRAM_FILES, 0)) {
	 CString ret = _T("C:\\ASTROW");
	 return ret;
 }
 _tcscat( buf, _T("\\Astro For Windows"));
 if ( _taccess(buf, 0 ) )
	 _tmkdir(buf);
 CString def = buf;
 return( def );
}

CString GetDatabaseNamePath()
{
 CString str = GetDatabasePath();
 if ( str.Right(1)!="\\" )
    str += "\\";
 str += GetDatabaseName();
 return( str );
}

CString GetDatabaseName()
{
 
 return(AfxGetApp()->GetProfileString(_T("TBT"),_T("DatabaseName"),_T("astrow.mdb")) );
 
}

CString GetSrcDir()
{
 TCHAR buf[255];
 DWORD len, type;

 HKEY hkeysub;
 DWORD succ = RegOpenKey(HKEY_CURRENT_USER,_T("Software\\Christopher J. Noyes Software\\ASTRO For Windows\\Directories"),&hkeysub);
 RegQueryValueEx( hkeysub,_T("User"),NULL, &type,(LPBYTE)buf,&len);
 RegCloseKey(hkeysub);
 if ( !_tcslen(buf) )
	 _tcscpy(buf,(LPCTSTR)getDataDefDir());
 if ( buf[_tcslen(buf)-1]==_T('\\') )
    _tcscat(buf,_T("text\\"));
 else
    _tcscat(buf,_T("\\text\\"));
 return( AfxGetApp()->GetProfileString(_T("TBT"),_T("TEXTDIR"),buf));
}

CString GetDatabasePath()
{
 TCHAR buf[255];

 DWORD len, type;
 HKEY hkeysub;
 DWORD succ = RegOpenKey(HKEY_CURRENT_USER,_T("Software\\Christopher J. Noyes Software\\ASTRO For Windows\\Directories"),&hkeysub);
 succ = RegQueryValueEx( hkeysub, _T("DB"), NULL, &type,(LPBYTE)buf,&len);
 RegCloseKey(hkeysub);
 if ( !_tcslen(buf) )
	 _tcscpy(buf,(LPCTSTR)getDataDefDir());
 if ( buf[_tcslen(buf)-1]=='\\' )
    _tcscat(buf,_T("\\"));
 return( AfxGetApp()->GetProfileString(_T("TBT"),_T("DBDIR"),buf));
}

CString quote(CString &s)
{
 s.Replace(_T("'"),_T("''"));
 CString st = _T("'") + s + _T("'");
 return( st );
}

CString &GetCurLanguage()
{
	static CString str;
	
	if ( str.GetLength()==0 )
	   str= AfxGetApp()->GetProfileString(_T("TBT"),_T("CurrLanguage"),_T("English"));
	return str;
}
