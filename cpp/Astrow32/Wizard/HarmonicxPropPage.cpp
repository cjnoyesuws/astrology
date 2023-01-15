// Harmonic.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "harmonicxPropPage.h"
#include <afxpriv.h>
#include "ChartWizard.h"

// CHarmonicPropPage dialog

IMPLEMENT_DYNAMIC(CHarmonicPropPage,CPropertyPage)
CHarmonicPropPage::CHarmonicPropPage()
   : CPropertyPage(CHarmonicPropPage::IDD, 0)
	, m_harmonic(0)
{
}

CHarmonicPropPage::~CHarmonicPropPage()
{
}

void CHarmonicPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HARM, m_harmonic);
	DDV_MinMaxInt(pDX, m_harmonic, 1, 30);
}


BEGIN_MESSAGE_MAP(CHarmonicPropPage, CDialog)
END_MESSAGE_MAP()


// CHarmonicPropPage message handlers

int CHarmonicPropPage::GetValue(void)
{
	return m_harmonic;
}

void CHarmonicPropPage::SetValue(int m_Value)
{
 m_harmonic = m_Value;
}

LRESULT CHarmonicPropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    return CPropertyPage::OnWizardNext();
}

BOOL CHarmonicPropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    *(((CChartWizard *)GetParent())->GetChartDataPtrs().harmonic) = m_harmonic;
    return CPropertyPage::OnWizardFinish();
}

LRESULT CHarmonicPropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

    return CPropertyPage::OnWizardBack();
}


BOOL CHarmonicPropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(FALSE);
    m_harmonic = *(((CChartWizard *)GetParent())->GetChartDataPtrs().harmonic);
    ((CChartWizard *)GetParent())->HandleButtons();
    return CPropertyPage::OnSetActive();
}

BOOL CHarmonicPropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

     return CPropertyPage::OnKillActive();
}