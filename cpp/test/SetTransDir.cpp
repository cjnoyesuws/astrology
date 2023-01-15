// SetTransDir.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "SetTransDir.h"
#include "directoryselect.h"


// CSetTransDir dialog

IMPLEMENT_DYNAMIC(CSetTransDir, CDialog)
CSetTransDir::CSetTransDir(CWnd* pParent /*=NULL*/)
	: CDialog(CSetTransDir::IDD, pParent)
	, m_transdir(_T(""))
{
}

CSetTransDir::~CSetTransDir()
{
}

void CSetTransDir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TRANSDIR, m_transdir);
}


BEGIN_MESSAGE_MAP(CSetTransDir, CDialog)
	ON_BN_CLICKED(IDC_SELECT, OnBnClickedSelect)
END_MESSAGE_MAP()


// CSetTransDir message handlers

void CSetTransDir::OnBnClickedSelect()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CDirectorySelect dir(FALSE);
	dir.m_pOFN->lpstrTitle = _T("Select Translated Files Directory");
	dir.m_pOFN->lpstrInitialDir = (LPCTSTR)m_transdir;
	if ( dir.DoModal() == IDOK ) {
		m_basedir = dir.GetDirectory();
		UpdateData(FALSE);
	}
}

void CSetTransDir::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
	if ( _waccess((LPCTSTR)m_transdir,0) ) {
		AfxMessageBox(_T("Translation Directory Does Not Exist, Please Make Sure It Exists"));
	    return;
	}
	if ( m_transdir.Right(1) == _T("\\") )
		m_transdir = m_transdir.Left(m_transdir.GetLength()-1);
	int index = m_transdir.ReverseFind('\\');
	if ( index != -1 )
		m_transdir = m_transdir.Right((m_transdir.GetLength()-index)-1);
	AfxGetApp()->WriteProfileString(_T("Translation"),_T("TransDir"),m_transdir);
	CDialog::OnOK();
}

BOOL CSetTransDir::OnInitDialog()
{
	CDialog::OnInitDialog();
    
	CString str = AfxGetApp()->GetProfileString(_T("Translation"),_T("BaseDir"));
	m_transdir = str;
	UpdateData(FALSE);
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
