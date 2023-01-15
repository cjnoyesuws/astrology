// PageSetp.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "pageopt.hpp"
#include "PageSetp.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSetp dialog


CPageSetp::CPageSetp(CWnd* pParent /*=NULL*/)
	: CDialog(CPageSetp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageSetp)
	m_bottom = 0;
	m_left = 0;
	m_right = 0;
	m_top = 0;
	//}}AFX_DATA_INIT
}


void CPageSetp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSetp)
	DDX_Text(pDX, IDC_BOTTOM, m_bottom);
	DDV_MinMaxInt(pDX, m_bottom, 0, 200);
	DDX_Text(pDX, IDC_LEFT, m_left);
	DDV_MinMaxInt(pDX, m_left, 0, 200);
	DDX_Text(pDX, IDC_RIGHT, m_right);
	DDV_MinMaxInt(pDX, m_right, 0, 200);
	DDX_Text(pDX, IDC_TOP, m_top);
	DDV_MinMaxInt(pDX, m_top, 0, 200);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageSetp, CDialog)
	//{{AFX_MSG_MAP(CPageSetp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSetp message handlers


void CPageSetp::SetData( PageData &d )
{
 CRect r = d.getMargins();
 m_left = r.left;
 m_right = r.right;
 m_top = r.top;
 m_bottom = r.bottom;
}

void CPageSetp::GetData( PageData &d )
{
 CRect r;
 r.left =(int) m_left;
 r.right =(int) m_right;
 r.top =(int) m_top;
 r.bottom =(int) m_bottom;
 d.getMargins() = r;
}

