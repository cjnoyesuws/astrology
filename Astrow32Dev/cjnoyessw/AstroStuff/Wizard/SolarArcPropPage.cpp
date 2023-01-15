// SolarArcPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "SolarArcPropPage.h"
#include "ChartWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSolarArcPropPage dialog

IMPLEMENT_DYNAMIC(CSolarArcPropPage, CPropertyPage)
CSolarArcPropPage::CSolarArcPropPage()
	: CPropertyPage(CSolarArcPropPage::IDD, 0)
{
	//{{AFX_DATA_INIT(CSolarArcPropPage)
	m_Day = 0;
	m_month = 0;
	m_system = -1;
	m_target = FALSE;
	m_year = 0;
	//}}AFX_DATA_INIT
}


void CSolarArcPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSolarArcPropPage)
	DDX_Text(pDX, IDC_DAY, m_Day);
	DDX_Text(pDX, IDC_MONTH, m_month);
	DDX_CBIndex(pDX, IDC_SYSTEM, m_system);
	DDX_Check(pDX, IDC_TARGET, m_target);
	DDX_Text(pDX, IDC_YEAR, m_year);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSolarArcPropPage, CDialog)
	//{{AFX_MSG_MAP(CSolarArcPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSolarArcPropPage message handlers

void CSolarArcPropPage::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

void CSolarArcPropPage::SetData(DIREC_DATA &d)
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

void CSolarArcPropPage::GetData(DIREC_DATA &d)
{
 if ( m_target )
	 d.direct_system = m_system + 100;
 else
	 d.direct_system = m_system;
 d.direction.day = m_Day;
 d.direction.month = m_month;
 d.direction.year = m_year;
}

LRESULT CSolarArcPropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    return CPropertyPage::OnWizardNext();
}

BOOL CSolarArcPropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().ddp));
    return CPropertyPage::OnWizardFinish();
}

LRESULT CSolarArcPropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

    return CPropertyPage::OnWizardBack();
}


BOOL CSolarArcPropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	SetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().ddp));
    UpdateData(FALSE);
    ((CChartWizard *)GetParent())->HandleButtons();
    return CPropertyPage::OnSetActive();
}

BOOL CSolarArcPropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

     return CPropertyPage::OnKillActive();
}