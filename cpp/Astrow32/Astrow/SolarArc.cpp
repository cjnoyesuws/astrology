// SolarArc.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "SolarArc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolarArc dialog


CSolarArc::CSolarArc(CWnd* pParent /*=NULL*/)
	: CDialog(CSolarArc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSolarArc)
	m_Day = 0;
	m_month = 0;
	m_system = -1;
	m_target = FALSE;
	m_year = 0;
	//}}AFX_DATA_INIT
}


void CSolarArc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolarArc)
	DDX_Text(pDX, IDC_DAY, m_Day);
	DDX_Text(pDX, IDC_MONTH, m_month);
	DDX_CBIndex(pDX, IDC_SYSTEM, m_system);
	DDX_Check(pDX, IDC_TARGET, m_target);
	DDX_Text(pDX, IDC_YEAR, m_year);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolarArc, CDialog)
	//{{AFX_MSG_MAP(CSolarArc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolarArc message handlers

void CSolarArc::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CSolarArc::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSolarArc::SetData(DIREC_DATA &d)
{
	if ( d.direct_system >= 100 ) {
		m_target = TRUE;
		m_system = d.direct_system-100;
	}
	else {
		m_target=FALSE;
		m_system = d.direct_system;
	}
	m_Day = d.direction.day;
	m_month = d.direction.month;
	m_year = d.direction.year;
}

void CSolarArc::GetData(DIREC_DATA &d)
{
 if ( m_target ) 
	 d.direct_system = m_system + 100;
 else
	 d.direct_system = m_system;
 d.direction.day = m_Day;
 d.direction.month = m_month;
 d.direction.year = m_year;
}