// TransBase.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "TransBase.h"
#include "io.h"
#include "directoryselect.h"
#ifdef _UNICODE
// CTransBase dialog

IMPLEMENT_DYNAMIC(CTransBase, CDialog)
CTransBase::CTransBase(CWnd* pParent /*=NULL*/)
	: CDialog(CTransBase::IDD, pParent)
	, m_basedir(_T(""))
{
}

CTransBase::~CTransBase()
{
}

void CTransBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BASEDIR, m_basedir);
}


BEGIN_MESSAGE_MAP(CTransBase, CDialog)
	ON_BN_CLICKED(IDC_SELECT, OnBnClickedSelect)
END_MESSAGE_MAP()


// CTransBase message handlers

void CTransBase::OnBnClickedSelect()
{
	// TODO: Add your control notification handler code here
    CDirectorySelect dir(FALSE);
	dir.m_pOFN->lpstrTitle = _T("Select Translation Base Directory");
	if ( dir.DoModal() == IDOK ) {
		m_basedir = dir.GetDirectory();
		UpdateData(FALSE);
	}
}

BOOL CTransBase::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTransBase::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);
	if (_waccess(m_basedir,0)) {
	   AfxMessageBox(_T("Directory Does Not Exist, Please Make Sure It Exists"));
	   return;
	}
    CString str;
	str = m_basedir;
	if ( str.Right(1) != _T("\\") )
		str += _T("\\");
    str += _T("txts");
	_wmkdir((LPCTSTR)str);
	str = m_basedir;
	if ( str.Right(1) != _T("\\") )
		str += _T("\\");
    str += _T("spls");
	_wmkdir((LPCTSTR)str);
	str = m_basedir;
	if ( str.Right(1) != _T("\\") )
		str += _T("\\");
    str += _T("mrgs");
	_wmkdir((LPCTSTR)str);
    str = m_basedir;
	if ( str.Right(1) != _T("\\") )
		str += _T("\\");
    str += _T("srcs");
	_wmkdir((LPCTSTR)str);
	CString msg = _T("Export the Text Source or Copy the Original Text Source to ") + str;
	AfxMessageBox(msg);
	AfxGetApp()->WriteProfileString(_T("Translation"),_T("BaseDir"),m_basedir);
	CDialog::OnOK();
}

#endif