// RectifyData.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "RectifyData.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectifyData dialog


CRectifyData::CRectifyData(CWnd* pParent /*=NULL*/)
	: CDialog(CRectifyData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRectifyData)
	m_ampm = -1;
	m_check = FALSE;
	m_deg = 0;
	m_min = 0;
	m_angle = -1;
	m_sign = -1;
	m_method = -1;
	m_tmin = 0;
	m_thrs = 0;
	//}}AFX_DATA_INIT
}


void CRectifyData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRectifyData)
	DDX_CBIndex(pDX, ID_RDAMPM, m_ampm);
	DDX_Check(pDX, ID_RDCHECK, m_check);
	DDX_Text(pDX, ID_RDKDEG, m_deg);
	DDV_MinMaxInt(pDX, m_deg, 0, 29);
	DDX_Text(pDX, ID_RDKMIN, m_min);
	DDV_MinMaxInt(pDX, m_min, 0, 59);
	DDX_CBIndex(pDX, ID_RDKNOWNANGL, m_angle);
	DDX_CBIndex(pDX, ID_RDKSIGN, m_sign);
	DDX_CBIndex(pDX, ID_RDMETHOD, m_method);
	DDX_Text(pDX, ID_RDMIN, m_tmin);
	DDV_MinMaxInt(pDX, m_tmin, 0, 60);
	DDX_Text(pDX, ID_RDHRS, m_thrs);
	DDV_MinMaxInt(pDX, m_thrs, 0, 12);
	//}}AFX_DATA_MAP
	if (pDX->m_bSaveAndValidate==FALSE)
	   OnSelchangeMethod(); 
}


BEGIN_MESSAGE_MAP(CRectifyData, CDialog)
	//{{AFX_MSG_MAP(CRectifyData)
	ON_CBN_SELCHANGE(ID_RDMETHOD, OnSelchangeMethod)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectifyData message handlers



void CRectifyData::OnSelchangeMethod() 
{
	// TODO: Add your control notification handler code here
	CComboBox *pc = (CComboBox *)GetDlgItem(ID_RDMETHOD);	   
    if ( pc != NULL ) {
	   if ( pc->GetCurSel() != -1 ) {
 	   int i = 	pc->GetCurSel();
 	   if ( i == KNOWN_ANGL ) {
	   	  CWnd *st =GetDlgItem(ID_RDKDEG);
	   	  st->EnableWindow(TRUE);
	      st =GetDlgItem(ID_RDKSIGN);
	   	  st->EnableWindow(TRUE);
	      st =GetDlgItem(ID_RDKMIN);
	   	  st->EnableWindow(TRUE);
	      st =GetDlgItem(ID_RDKNOWNANGL);
	   	  st->EnableWindow(TRUE);
	      }
	   else {
	   	  CWnd *st2 =GetDlgItem(ID_RDKDEG);
	   	  st2->EnableWindow(FALSE);
	      st2 =GetDlgItem(ID_RDKSIGN);
	   	  st2->EnableWindow(FALSE);
	      st2 =GetDlgItem(ID_RDKMIN);
	   	  st2->EnableWindow(FALSE);
	      st2 =GetDlgItem(ID_RDKNOWNANGL);
	   	  st2->EnableWindow(FALSE);
	      }
	   }
	
	}
}


void CRectifyData::SetData(RECT_DATA &d, TIM &bth, int btham)
{
 m_check =d.birth_time_known;
 m_method =d.rect_system;
 if ( d.trial.hours ) {
    m_ampm = d.am_pm;
    m_thrs = d.trial.hours % 12;
    m_tmin = d.trial.minutes %60;
	}
 else
	{
	m_ampm = btham;
	m_thrs = bth.hours % 12;
    m_tmin = bth.minutes %60;
	}
 m_angle = d.angle;
 m_sign = d.sign%12;
 m_deg = d.degree.degrees%30;
 m_min = d.degree.minutes%60;
}

void CRectifyData::GetData(RECT_DATA &d)
{
 d.birth_time_known = m_check;
 d.rect_system = m_method;
 if ( m_ampm )
    d.trial.hours = m_thrs + 12;
 else 
 	d.trial.hours = m_thrs;
 d.am_pm = m_ampm;
 d.trial.minutes = m_tmin;
 d.angle = m_angle;
 d.sign = m_sign;
 d.degree.degrees = m_deg;
 d.degree.minutes = m_min % 60;
 d.total_minutes = ((((d.sign * 30) + d.degree.degrees)) * 60)+ d.degree.minutes;
if ( d.am_pm && d.trial.hours != 12)
   d.trial.hours += 12;
 else if ( d.trial.hours == 12 )
   d.trial.hours = 0;
 if ( d.rect_system == SOLARCHART || d.rect_system == FLATCHART ) {
   if ( d.trial.hours != 12 )
      d.trial.hours = 12;
   if ( d.trial.minutes != 0 )
      d.trial.minutes = 0;
   if ( !d.am_pm )
      d.am_pm = 1;
   }
}

void CRectifyData::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}

void CRectifyData::OnOK() 
{
 UpdateData(TRUE);
 CDialog::OnOK();
}