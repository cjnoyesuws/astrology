// EditData.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "EditData.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditData dialog


CEditData::CEditData(CWnd* pParent /*=NULL*/)
	: CDialog(CEditData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditData)
	m_options = _T("");
	m_path = _T("");
	m_useext = FALSE;
	//}}AFX_DATA_INIT
}


void CEditData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditData)
	DDX_Text(pDX, ID_OPTIONS, m_options);
	DDX_Text(pDX, IDC_PATH, m_path);
	DDX_Check(pDX, IDC_USEEXT, m_useext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditData, CDialog)
	//{{AFX_MSG_MAP(CEditData)
	ON_BN_CLICKED(IDC_USEEXT, OnUseext)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditData message handlers

void CEditData::OnUseext() 
{
	// TODO: Add your control notification handler code here
	
}

void CEditData::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
