// ArchiveData.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "ArchiveData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchiveData dialog


CArchiveData::CArchiveData(CWnd* pParent /*=NULL*/)
	: CDialog(CArchiveData::IDD, pParent)
{
	Program = 1;
	//{{AFX_DATA_INIT(CArchiveData)
	m_cmd = _T("");
	m_name = _T("");
	m_del = FALSE;
	//}}AFX_DATA_INIT
}


void CArchiveData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchiveData)
	DDX_Text(pDX, ID_ARCMD, m_cmd);
	DDX_Text(pDX, ID_ARNAME, m_name);
	DDX_Check(pDX, ID_ARDELETE, m_del);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchiveData, CDialog)
	//{{AFX_MSG_MAP(CArchiveData)
	ON_BN_CLICKED(ID_ARZIP, OnZip)
	ON_BN_CLICKED(ID_ARLHA, OnLha)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchiveData message handlers

void CArchiveData::OnWzip() 
{
	// TODO: Add your control notification handler code here
	Program = 1;
}

void CArchiveData::OnZip() 
{
	// TODO: Add your control notification handler code here
	Program = 1;
}

void CArchiveData::OnLha() 
{
	// TODO: Add your control notification handler code here
	Program = 0;
}

BOOL CArchiveData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CButton *ptr =(CButton *) GetDlgItem(ID_ARZIP);
	ptr->SetCheck(1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CArchiveData::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(CArchiveData::IDD, HELP_CONTEXT);
}
