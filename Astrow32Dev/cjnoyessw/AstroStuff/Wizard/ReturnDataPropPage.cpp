// ReturnData.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "ReturnDataPropPage.h"
#include <afxpriv.h>
#include "ChartWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReturnDataPropPage dialog

IMPLEMENT_DYNAMIC(CReturnDataPropPage, CPropertyPage)
CReturnDataPropPage::CReturnDataPropPage()
	: CPropertyPage(CReturnDataPropPage::IDD, 0)
{
	//{{AFX_DATA_INIT(CReturnDataPropPage)
	m_body = -1;
	m_eday = 0;
	m_emo = 0;
	m_eyear = 0;
	m_pday = 0;
	m_pmo = 0;
	m_prog = FALSE;
	m_progsys = -1;
	m_pyear = 0;
	m_sday = 0;
	m_smo = 0;
	m_syear = 0;
	m_target = FALSE;
	//}}AFX_DATA_INIT
}


void CReturnDataPropPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReturnDataPropPage)
	DDX_CBIndex(pDX, ID_RDBODY, m_body);
	DDX_Text(pDX, ID_RDEDAY, m_eday);
	DDV_MinMaxInt(pDX, m_eday, 1, 31);
	DDX_Text(pDX, ID_RDEMO, m_emo);
	DDV_MinMaxInt(pDX, m_emo, 1, 12);
	DDX_Text(pDX, ID_RDEYEAR, m_eyear);
	DDV_MinMaxInt(pDX, m_eyear, 0, 2100);
	DDX_Text(pDX, ID_RDPDAY, m_pday);
	DDV_MinMaxInt(pDX, m_pday, 0, 31);
	DDX_Text(pDX, ID_RDPMO, m_pmo);
	DDV_MinMaxInt(pDX, m_pmo, 0, 12);
	DDX_Check(pDX, ID_RDPROG, m_prog);
	DDX_CBIndex(pDX, ID_RDPROGSYS, m_progsys);
	DDX_Text(pDX, ID_RDPYEAR, m_pyear);
	DDV_MinMaxInt(pDX, m_pyear, 0, 2100);
	DDX_Text(pDX, ID_RDSDAY, m_sday);
	DDV_MinMaxInt(pDX, m_sday, 0, 31);
	DDX_Text(pDX, ID_RDSMO, m_smo);
	DDV_MinMaxInt(pDX, m_smo, 0, 12);
	DDX_Text(pDX, ID_RDSYEAR, m_syear);
	DDV_MinMaxInt(pDX, m_syear, 0, 2100);
	DDX_Check(pDX, ID_RDTARGET, m_target);
	//}}AFX_DATA_MAP
	if (!pDX->m_bSaveAndValidate)
	   onProg();
}


BEGIN_MESSAGE_MAP(CReturnDataPropPage, CDialog)
	//{{AFX_MSG_MAP(CReturnDataPropPage)
	ON_BN_CLICKED(ID_RDPROG, onProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReturnDataPropPage message handlers



void CReturnDataPropPage::SetData(RETURN_DATA &rd )
{
 m_body = rd.planet;
 m_prog = (rd.is_prog?TRUE:FALSE);
 m_sday = rd.start.day;
 m_smo = rd.start.month;
 m_syear = rd.start.year;
 m_eday = rd.end.day;
 m_emo = rd.end.month;
 m_eyear = rd.end.year;
 if ( rd.prog.progress_system > 100 )
	m_target = TRUE;
 else
	m_target = FALSE;
 m_pday = rd.prog.offset.day;
 m_pmo = rd.prog.offset.month;
 m_pyear = rd.prog.offset.year;
 m_progsys = rd.prog.progress_system % 100;
}

void CReturnDataPropPage::GetData(RETURN_DATA &rd )
{
 rd.planet = m_body;
 rd.is_prog = (m_prog?1:0);
 rd.end.day = m_eday;
 rd.end.month = m_emo;
 rd.end.year = m_eyear;
 rd.start.day = m_sday;
 rd.start.month = m_smo;
 rd.start.year = m_syear;
 if ( m_target == TRUE )
	rd.prog.progress_system = m_progsys +100;
 else
	rd.prog.progress_system = m_progsys;
 rd.prog.offset.day = m_pday;
 rd.prog.offset.month = m_pmo;
 rd.prog.offset.year = m_pyear;
}


void CReturnDataPropPage::onProg()
{
	// TODO: Add your control notification handler code here
	CWnd *p;
	CButton *b =(CButton *)GetDlgItem(ID_RDPROG);
	if (b->GetCheck()==1) {
	   p = GetDlgItem(ID_RDPDAY);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_RDPMO);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_RDPROGSYS);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_RDPYEAR);
	   p->EnableWindow(TRUE);
	   p = GetDlgItem(ID_RDTARGET);
	   p->EnableWindow(TRUE);
	   }
	else {
	   p = GetDlgItem(ID_RDPDAY);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_RDPMO);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_RDPROGSYS);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_RDPYEAR);
	   p->EnableWindow(FALSE);
	   p = GetDlgItem(ID_RDTARGET);
	   p->EnableWindow(FALSE);
	   }

}

LRESULT CReturnDataPropPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    return CPropertyPage::OnWizardNext();
}

BOOL CReturnDataPropPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData(TRUE);
    GetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().rtdp));
    return CPropertyPage::OnWizardFinish();
}

LRESULT CReturnDataPropPage::OnWizardBack()
{
	// TODO: Add your specialized code here and/or call the base class

    return CPropertyPage::OnWizardBack();
}

void CReturnDataPropPage::OnOK()
{
     // TODO: Add your specialized code here and/or call the base class

     UpdateData(TRUE);
     CPropertyPage::OnOK();
}

BOOL CReturnDataPropPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
    SetData(*(((CChartWizard *)GetParent())->GetChartDataPtrs().rtdp));
    UpdateData(FALSE);
    ((CChartWizard *)GetParent())->HandleButtons();
    return CPropertyPage::OnSetActive();
}

BOOL CReturnDataPropPage::OnKillActive()
{
	// TODO: Add your specialized code here and/or call the base class

     return CPropertyPage::OnKillActive();
}