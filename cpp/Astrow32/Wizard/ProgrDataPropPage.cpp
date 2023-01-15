// ProgrDataPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "ChartWizard.h"

#include "ProgrDataPropPage.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgrDataPropPage dialog

IMPLEMENT_DYNAMIC(CProgrDataPropPage, CPropertyPage)
CProgrDataPropPage::CProgrDataPropPage()
	: CPropertyPage(CProgrDataPropPage::IDD, 0)
{
	//{{AFX_DATA_INIT(CProgrDataPropPage)
	m_system = 1;
	m_target = TRUE;
	m_day = 1;
	m_month = 1;
	m_year = 1999;
	//}}AFX_DATA_INIT
}


void CProgrDataPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgrDataPropPage)
	DDX_CBIndex(pDX, ID_PDSYSTEM, m_system);
	DDX_Check(pDX, ID_PDTARGET, m_target);
	DDX_Text(pDX, ID_PDDAY, m_day);
	DDV_MinMaxInt(pDX, m_day, 0, 31);
	DDX_Text(pDX, ID_PDMO, m_month);
	DDV_MinMaxInt(pDX, m_month, 0, 12);
	DDX_Text(pDX, ID_PDYEAR, m_year);
	DDV_MinMaxInt(pDX, m_year, 0, 2100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgrDataPropPage, CDialog)
	//{{AFX_MSG_MAP(CProgrDataPropPage)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgrDataPropPage message handlers

void CProgrDataPropPage::SetData( PROGR_DATA &p)
{
 if ( p.progress_system > 100 )
	m_target = TRUE;
 else
	m_target = FALSE;
 m_day = p.offset.day;
 m_month = p.offset.month;
 m_year = p.offset.year;
 m_system = p.progress_system % 100;
}

void CProgrDataPropPage::GetData( PROGR_DATA &p)
{
 if ( m_target == TRUE )
	p.progress_system = m_system +100;
 else
	p.progress_system = m_system;
 p.offset.day = m_day;
 p.offset.month = m_month;
 p.offset.year = m_year;
}

LRESULT CProgrDataPropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    return CPropertyPage::OnWizardNext();
}

BOOL CProgrDataPropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().pdp));
    return CPropertyPage::OnWizardFinish();
}

LRESULT CProgrDataPropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

    return CPropertyPage::OnWizardBack();
}


BOOL CProgrDataPropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
    SetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().pdp));
    UpdateData(FALSE);
    ((CChartWizard *)GetParent())->HandleButtons();
    return CPropertyPage::OnSetActive();
}

BOOL CProgrDataPropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

     return CPropertyPage::OnKillActive();
}