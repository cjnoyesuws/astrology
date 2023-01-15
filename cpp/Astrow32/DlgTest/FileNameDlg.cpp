// FileNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "charcons.h"
#include "astro.h"
#include "useri.h"
#include "FileNameDlg.h"
#include "direc.hpp"
#include "folders.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileNameDlg dialog


CFileNameDlg::CFileNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNameDlg::IDD, pParent)
	, m_folder(0), m_bFind(FALSE)
	, m_auto(TRUE)
{
	//{{AFX_DATA_INIT(CFileNameDlg)
	m_comment = _T("");
	m_filename = _T("");
	m_name = _T("");
	m_type = _T("");
	m_folder = theFolders.GetCurFolder()-DEFAULT_FLD;
	//}}AFX_DATA_INIT
}


void CFileNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileNameDlg)
	DDX_Text(pDX, ID_FNCOMMENT, m_comment);
	DDV_MaxChars(pDX, m_comment, 49);
	DDX_Text(pDX, ID_FNFILENAME, m_filename);
	DDV_MaxChars(pDX, m_filename, 254);
	DDX_Text(pDX, ID_FNNAME, m_name);
	DDV_MaxChars(pDX, m_name, 49);
	DDX_Text(pDX, ID_FNTYPE, m_type);
	//}}AFX_DATA_MAP
	DDX_CBIndex(pDX, IDC_FOLDER, m_folder);
	DDX_Check(pDX, IDC_AUTO, m_auto);
}


BEGIN_MESSAGE_MAP(CFileNameDlg, CDialog)
	//{{AFX_MSG_MAP(CFileNameDlg)
	ON_BN_CLICKED(ID_FNSELFILE, OnFnselfile)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileNameDlg message handlers

void CFileNameDlg::OnFnselfile() 
{
	
	// TODO: Add your control notification handler code here
	
	CString filter = "ASTRO Report Files (*.ASRPT)|*.ASRPT||";
	CFileDialog cfd(TRUE,".ASRPT", m_filename, 
		 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, this );
	cfd.m_ofn.lpstrInitialDir = (char *)(LPCTSTR)theDirectories.getUser();
		if ( cfd.DoModal() == IDOK )
	   m_filename = cfd.GetPathName();		
	UpdateData(FALSE);
}

void CFileNameDlg::SetData( XPFILE_DB &f ) 
{
 m_name = f.name;
 m_comment = f.comment;
 m_filename = f.file_name;
 m_type = long_types[f.type];
 m_folder = f.folder-DEFAULT_FLD;
}

void CFileNameDlg::GetData( XPFILE_DB &f )
{
 strcpy(f.name,m_name);
 strcpy(f.comment,m_comment);
 strcpy(f.file_name, m_filename );
 f.folder = m_folder+DEFAULT_FLD;
}


void CFileNameDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

BOOL CFileNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    if ( m_bFind)
	   GetDlgItem(IDC_FOLDER)->EnableWindow(FALSE);
	else {
		CComboBox* p = (CComboBox *)GetDlgItem(IDC_FOLDER);
		theFolders.toCombo(p);
	}
	// TODO:  Add extra initialization here
    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}