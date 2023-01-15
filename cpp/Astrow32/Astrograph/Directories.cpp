// Directories.cpp : implementation file
//

#include "stdafx.h"
#include "newmultdoctmpl.h"
#include "Astrow.h"
#include "direc.hpp"
#include "Directories.h"
#include <afxpriv.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirectories dialog


CDirectories::CDirectories(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectories::IDD, pParent)
	
{
	//{{AFX_DATA_INIT(CDirectories)
	m_data = _T("");
	m_database = _T("");
	m_help = _T("");
	m_main = _T("");
	m_user = _T("");
    m_dbName = _T("astrow.mdb");
    m_txtdbname = _T("astrow.mdb");
   m_DatabaseText = TRUE;
	//}}AFX_DATA_INIT
}


void CDirectories::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectories)
	DDX_Text(pDX, ID_DDATA, m_data);
	DDV_MaxChars(pDX, m_data, 250);
	DDX_Text(pDX, ID_DDATABASE, m_database);
	DDV_MaxChars(pDX, m_database, 250);
	DDX_Text(pDX, ID_DHELP, m_help);
	DDX_Text(pDX, ID_DMAIN, m_main);
	DDV_MaxChars(pDX, m_main, 255);
	DDX_Text(pDX, ID_DUSER, m_user);
	DDV_MaxChars(pDX, m_user, 250);
	DDX_Text(pDX, IDC_DBNAME, m_dbName);
	DDV_MaxChars(pDX, m_dbName, 35);
	DDX_Check(pDX, IDC_DBTEXT, m_DatabaseText);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_TXTDBNAME, m_txtdbname);
	DDV_MaxChars(pDX, m_txtdbname, 255);
}


BEGIN_MESSAGE_MAP(CDirectories, CDialog)
	//{{AFX_MSG_MAP(CDirectories)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_TXTDBNAME, OnEnChangeTxtdbname)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectories message handlers

void CDirectories::SetData( Directories &p )
{
m_data = p.getData();
m_database = p.getDB();
m_help = p.getHelp();
m_main = p.getMain();
m_user = p.getUser();
m_dbName = p.getDbName();
m_txtdbname = p.getTxtDbName();
}

void CDirectories::GetData( Directories &p )
{
p.getData() = m_data; 
p.getDB() = m_database; 
p.getHelp() = m_help; 
p.getMain() = m_main; 
p.getUser() = m_user;
p.getDbName() = m_dbName; 
p.getTxtDbName() = m_txtdbname;
}

void CDirectories::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

void CDirectories::OnEnChangeTxtdbname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CDirectories::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

    UpdateData(TRUE);
    CString db = m_database;
	if ( db.Right(1) != "\\" )
		db += "\\";
	db += m_dbName;
	if ( _access( (LPCTSTR)db, 0 ) ) {
	   AfxMessageBox("The Database Can't Be Found At This Location, Can't Save");
	   return;
	}
	CDialog::OnOK();
}
