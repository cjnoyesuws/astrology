// FindText.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "FindText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindText dialog


CFindText::CFindText(CWnd* pParent /*=NULL*/)
	: CDialog(CFindText::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindText)
	m_text = _T("");
	m_matchcase = FALSE;
	m_wholeword = FALSE;
	//}}AFX_DATA_INIT
}


void CFindText::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindText)
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDX_Check(pDX, IDC_MATCHCASE, m_matchcase);
	DDX_Check(pDX, IDC_WHOLEWORD, m_wholeword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindText, CDialog)
	//{{AFX_MSG_MAP(CFindText)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindText message handlers


void CFindText::GetData(CString &t, BOOL &mcase, BOOL &wword)
{
t = m_text;
mcase = m_matchcase;
wword = m_wholeword;
}

void CFindText::SetData(CString &t, BOOL &mcase, BOOL &wword)
{
m_text = t;
m_matchcase = mcase;
m_wholeword = wword;
}
