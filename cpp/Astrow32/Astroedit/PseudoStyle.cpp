// PseudoStyle.cpp : implementation file
//

#include "stdafx.h"
#ifdef CHARTVIEW
#include "chartview.h"
#else
#include "Astrow.h"
#endif
#include "attrib.h"
#include "PseudoStyle.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPseudoStyle dialog


CPseudoStyle::CPseudoStyle(CWnd* pParent /*=NULL*/)
	: CDialog(CPseudoStyle::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPseudoStyle)
	m_ebold = _T("");
	m_ehead = _T("");
	m_escore = _T("");
	m_sbold = _T("");
	m_shead = _T("");
	m_sscore = _T("");
	//}}AFX_DATA_INIT
}


void CPseudoStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPseudoStyle)
	DDX_Text(pDX, ID_PEBOLD, m_ebold);
	DDX_Text(pDX, ID_PEHEAD, m_ehead);
	DDX_Text(pDX, ID_PESCORE, m_escore);
	DDX_Text(pDX, ID_PSBOLD, m_sbold);
	DDX_Text(pDX, ID_PSHEAD, m_shead);
	DDX_Text(pDX, ID_PSSCORE, m_sscore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPseudoStyle, CDialog)
	//{{AFX_MSG_MAP(CPseudoStyle)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPseudoStyle message handlers


void CPseudoStyle::SetData(FIL_ATTRIB &f)
{
 m_ebold = f.bold_off;
 m_ehead = f.head_off;
 m_escore = f.uscore_off;
 m_sbold = f.bold_on;
 m_shead = f.head_on;
 m_sscore = f.uscore_on;
}

void CPseudoStyle::GetData(FIL_ATTRIB &f)
{
f.bold_off = m_ebold;
f.head_off = m_ehead;
f.uscore_off = m_escore;
f.bold_on = m_sbold;
f.head_on = m_shead;
f.uscore_on = m_sscore;
}
