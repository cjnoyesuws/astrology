// ProcMsg.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "ProcMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProcMsg dialog


ProcMsg::ProcMsg(CWnd* pParent /*=NULL*/)
	: CDialog(ProcMsg::IDD, pParent)
{
	Create(ProcMsg::IDD, pParent);
	notify = NULL;
	SetCapture();
	//{{AFX_DATA_INIT(ProcMsg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ProcMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ProcMsg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ProcMsg, CDialog)
	//{{AFX_MSG_MAP(ProcMsg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ProcMsg message handlers

BOOL ProcMsg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ProcMsg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if ( notify != NULL )
	   *notify = 1;
	ReleaseCapture();
	CDialog::OnCancel();
	DestroyWindow();
	
}


ProcMsg::ProcMsg(char *t, int *brk,  CWnd* pParent)
{
 Create(ProcMsg::IDD, pParent);
 SetCapture();
 GetDlgItem(IDC_TEXT)->SetWindowText(t);
 notify = brk;
 *notify = 0;
}

void ProcMsg::setText( char *t )
{
 GetDlgItem(IDC_TEXT)->SetWindowText(t);
 ((CAstrowApp *)AfxGetApp())->_Yield();
 Sleep(250);
}

ProcMsg::~ProcMsg()
{
 EndDialog(IDCANCEL);
 ReleaseCapture();
 DestroyWindow();
}