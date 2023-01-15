// FileKillDlg.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "charcons.h"
#include "astro.h"
#include "useri.h"
#include "FileKillDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileKillDlg dialog


CFileKillDlg::CFileKillDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileKillDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileKillDlg)
	m_comment = _T("");
	m_continue = FALSE;
	m_filename = _T("");
	m_name = _T("");
	m_type = _T("");
	//}}AFX_DATA_INIT
}


void CFileKillDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileKillDlg)
	DDX_Text(pDX, ID_FKCOMMENT, m_comment);
	DDX_Check(pDX, ID_FKCONTINUE, m_continue);
	DDX_Text(pDX, ID_FKFILENAME, m_filename);
	DDX_Text(pDX, ID_FKNAME, m_name);
	DDX_Text(pDX, ID_FKTYPE, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileKillDlg, CDialog)
	//{{AFX_MSG_MAP(CFileKillDlg)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileKillDlg message handlers

void CFileKillDlg::OnNo() 
{ 
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDialog::EndDialog(IDNO);
}

void CFileKillDlg::SetData( XPFILE_DB &f ) 
{
 m_name = f.name;
 m_comment = f.comment;
 m_filename = f.file_name;
 m_type = long_types[f.type];
}

void CFileKillDlg::GetData( int &c )
{
 c = m_continue;
}


void CFileKillDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
