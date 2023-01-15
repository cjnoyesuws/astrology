// TransData.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"

#include "TransDataPropPage.h"
#include <afxpriv.h>
#include "ChartWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransDataPropPage dialog

IMPLEMENT_DYNAMIC(CTransDataPropPage, CPropertyPage)
CTransDataPropPage::CTransDataPropPage()
	: CPropertyPage(CTransDataPropPage::IDD,0)
{
	//{{AFX_DATA_INIT(CTransDataPropPage)
	m_day = 1;
	m_end = PLUTO;
	m_mo = 0;
	m_num = 0;
	m_start = SUN;
	//}}AFX_DATA_INIT
}


void CTransDataPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransDataPropPage)
	DDX_Text(pDX, ID_TDDAY, m_day);
	DDV_MinMaxInt(pDX, m_day, 1, 31);
	DDX_CBIndex(pDX, ID_TDEND, m_end);
	DDX_Text(pDX, ID_TDMO, m_mo);
	DDV_MinMaxInt(pDX, m_mo, 0, 12);
	DDX_Text(pDX, ID_TDNUM, m_num);
	DDV_MinMaxInt(pDX, m_num, 1, 360);
	DDX_CBIndex(pDX, ID_TDSTART, m_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransDataPropPage, CDialog)
	//{{AFX_MSG_MAP(CTransDataPropPage)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransDataPropPage message handlers


void CTransDataPropPage::SetData(TRANS_DATA &t)
{
 m_num = t.num_transits;
 if ( t.end_planet > 0 )
    m_end = t.end_planet;
 if ( t.start_planet > 0 )
    m_start = t.start_planet;
 if ( t.interval_date.day > 0 )
    m_day = t.interval_date.day;
 m_mo = t.interval_date.month;
}

void CTransDataPropPage::GetData(TRANS_DATA &t)
{
 t.num_transits = m_num;
 t.end_planet = m_end;
 t.start_planet = m_start;
 t.interval_date.day = m_day;
 t.interval_date.month = m_mo;
}


LRESULT CTransDataPropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    return CPropertyPage::OnWizardNext();
}

BOOL CTransDataPropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().tdp));
    return CPropertyPage::OnWizardFinish();
}

LRESULT CTransDataPropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

    return CPropertyPage::OnWizardBack();
}

void CTransDataPropPage::OnOK()
{
     // TODO: Add your specialized code here and/or call the base class

     UpdateData(TRUE);
     CPropertyPage::OnOK();
}

BOOL CTransDataPropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
    SetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().tdp));
    UpdateData(FALSE);
    ((CChartWizard *)GetParent())->HandleButtons();
    return CPropertyPage::OnSetActive();
}

BOOL CTransDataPropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

     return CPropertyPage::OnKillActive();
}
