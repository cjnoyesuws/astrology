// FileEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "charcons.h"
#include "astro.h"
#include "useri.h"
#include "FileEditDlg.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileEditDlg dialog


CFileEditDlg::CFileEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileEditDlg)
	m_comment = _T("");
	m_filename = _T("");
	m_name = _T("");
	m_type = _T("");
	//}}AFX_DATA_INIT
}


void CFileEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileEditDlg)
	DDX_Text(pDX, ID_FECOMMENTS, m_comment);
	DDV_MaxChars(pDX, m_comment, 49);
	DDX_Text(pDX, ID_FEFILENAME, m_filename);
	DDX_Text(pDX, ID_FENAME, m_name);
	DDV_MaxChars(pDX, m_name, 49);
	DDX_Text(pDX, ID_FETYPE, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileEditDlg, CDialog)
	//{{AFX_MSG_MAP(CFileEditDlg)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileEditDlg message handlers

void CFileEditDlg::SetData( XPFILE_DB &f ) 
{
 m_name = f.name;
 m_comment = f.comment;
 m_filename = f.file_name;
 m_type = long_types[f.type];
}

void CFileEditDlg::GetData( XPFILE_DB &f )
{
 strcpy(f.name,m_name);
 strcpy(f.comment,m_comment);
}

void CFileEditDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
