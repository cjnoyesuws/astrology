// SelectTextItem.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "SelectTextItem.h"
#include "texttypeary.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectTextItem dialog


CSelectTextItem::CSelectTextItem(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectTextItem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectTextItem)
	m_Item = -1;
	//}}AFX_DATA_INIT
}


void CSelectTextItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectTextItem)
	DDX_CBIndex(pDX, IDC_TEXTITEM, m_Item);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectTextItem, CDialog)
	//{{AFX_MSG_MAP(CSelectTextItem)
	ON_CBN_SELCHANGE(IDC_TEXTITEM, OnSelchangeTextitem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectTextItem message handlers

void CSelectTextItem::OnSelchangeTextitem() 
{
	  TCHAR buf[100];
     // TODO: Add your control notification handler code here
	  CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_TEXTITEM);
     pbox->GetWindowText(buf,100);
     m_strItem=buf;
}

void CSelectTextItem::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CSelectTextItem::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CSelectTextItem::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_TEXTITEM);
   pATextTypes->toTextTypeCombo(pbox,m_type, m_ary);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
