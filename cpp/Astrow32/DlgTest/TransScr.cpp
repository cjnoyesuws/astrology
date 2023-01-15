// TransScr.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "TransScr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransScr dialog


CTransScr::CTransScr(CWnd* pParent /*=NULL*/)
	: CDialog(CTransScr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransScr)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransScr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransScr)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransScr, CDialog)
	//{{AFX_MSG_MAP(CTransScr)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransScr message handlers
