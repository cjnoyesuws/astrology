// ReportTextEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "ReportTextEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportTextEdit dialog


CReportTextEdit::CReportTextEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CReportTextEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportTextEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReportTextEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportTextEdit)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportTextEdit, CDialog)
	//{{AFX_MSG_MAP(CReportTextEdit)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportTextEdit message handlers
