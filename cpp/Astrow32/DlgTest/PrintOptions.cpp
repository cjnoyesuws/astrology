// PrintOptions.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "PrintOptions.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintOptions dialog


CPrintOptions::CPrintOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintOptions)
	m_cmtbeforetext = FALSE;
	m_comment = FALSE;
	m_cover = FALSE;
	m_ctrhead = FALSE;
	m_headp1 = FALSE;
	//}}AFX_DATA_INIT
}


void CPrintOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintOptions)
	DDX_Check(pDX, ID_CMTB4T, m_cmtbeforetext);
	DDX_Check(pDX, ID_POCMT, m_comment);
	DDX_Check(pDX, ID_POCOVER, m_cover);
	DDX_Check(pDX, ID_POCTRHD, m_ctrhead);
	DDX_Check(pDX, ID_POHDP1, m_headp1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintOptions, CDialog)
	//{{AFX_MSG_MAP(CPrintOptions)
	ON_BN_CLICKED(ID_POSTYLES, OnPostyles)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintOptions message handlers

void CPrintOptions::OnPostyles() 
{
	// TODO: Add your control notification handler code here
	
}

void CPrintOptions::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
