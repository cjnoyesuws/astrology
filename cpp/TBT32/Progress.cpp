// Progress.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "Progress.h"
#include <afxcmn.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog


CProgress::CProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgress)
	m_File = _T("");
	//}}AFX_DATA_INIT
	Create(CProgress::IDD, pParent);
}


void CProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgress)
	DDX_Control(pDX, IDC_PROGRESS1, m_Ctrl);
	DDX_Text(pDX, IDC_FILE, m_File);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgress, CDialog)
	//{{AFX_MSG_MAP(CProgress)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgress message handlers
void CProgress::SetFile(CString &s) 
{
  UpdateData(TRUE);
  m_File = s;
  UpdateData(FALSE);
  Invalidate(FALSE);
}

void CProgress::SetMax(int m)
{
 UpdateData(TRUE);
 m_Ctrl.SetRange(1,m);
 m_Ctrl.SetStep(1);
}

void CProgress::IncProgress() 
{
 UpdateData(TRUE);
 m_Ctrl.StepIt();
 Invalidate(FALSE);
}

void CProgress::Reset()
{
  UpdateData(TRUE);
  m_Ctrl.SetPos(1);
}
