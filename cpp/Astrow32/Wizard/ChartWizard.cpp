// ChartWizard.cpp : implementation file
//

#include "stdafx.h"
#include "Wizard.h"
#include "charttypeproppage.h"
#include "ChartWizard.h"
#include ".\chartwizard.h"
#include "direc.hpp"

// CChartWizard

IMPLEMENT_DYNAMIC(CChartWizard, CPropertySheet)
CChartWizard::CChartWizard(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
	, m_chart_type(0),m_old_file_type(0), m_file_type(0)
{
	EnableActiveAccessibility();
	m_pcompatinfo_pp = new CBirthInfoPropPage(IDD_COMPAT_BIRTH_INF_PROP_PAGE);
}

CChartWizard::CChartWizard(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
	, m_chart_type(0),m_old_file_type(0), m_file_type(0)
{
	EnableActiveAccessibility();
	m_pcompatinfo_pp = new CBirthInfoPropPage(IDD_COMPAT_BIRTH_INF_PROP_PAGE);
}

CChartWizard::~CChartWizard()
{
	delete m_pcompatinfo_pp;
}


BEGIN_MESSAGE_MAP(CChartWizard, CPropertySheet)
END_MESSAGE_MAP()


// CChartWizard message handlers

void CChartWizard::SetChartType(int nChartType)
{
 m_chart_type = nChartType;
}

void CChartWizard::DoAddPages(void)
{
	if ( m_file_type > 0 && m_file_type != m_old_file_type ) {
		int pgcnt = GetPageCount();
		for ( int ipg = 2; ipg < pgcnt; ipg++ )
			RemovePage(ipg);
	}
	switch ( m_file_type ) {
	   case NATAL_FILE :
       case NUMERIC_FILE :	
	   case FIXED_FILE:
	   case ARABIC_FILE:
	   case HELIO_FILE:
	   case PROBLEM_FILE:	
		   break;
	   case COMPATIBILITY_FILE :
		   AddPage((CPropertyPage *)m_pcompatinfo_pp);
		   break;
	   case TRANSITS_FILE :
		   AddPage((CPropertyPage *)&m_transinfo_pp);
		   AddPage((CPropertyPage *)&m_transdata_pp);
		   break;
#ifdef DELUXE
	   case PROGRESSED_FILE:
		   AddPage((CPropertyPage *)&m_progr_pp);
		   break;
	   case SOLAR_RETURN_FILE:
	   case LUNAR_RETURN_FILE:
		   AddPage((CPropertyPage *)&m_return_data_pp);
		   break;
	   case RETURN_W_RELOC:
		   AddPage((CPropertyPage *)&m_return_data_pp);
		   AddPage((CPropertyPage *)&m_reloc_pp);
		   break;
       case RETURN_W_TRANS:
		   AddPage((CPropertyPage *)&m_return_data_pp);
		   AddPage((CPropertyPage *)&m_transinfo_pp);
		   AddPage((CPropertyPage *)&m_transdata_pp);
		   break;
	   case RELOCATION_FILE:
		   AddPage((CPropertyPage *)&m_reloc_pp);
		   break;
	   case COMPOSITE_FILE:
		   AddPage((CPropertyPage *)m_pcompatinfo_pp);
		   AddPage((CPropertyPage *)&m_reloc_pp);
		   break;
#ifdef PRO	  
	   case COMPOTRAN_FILE:
		   AddPage((CPropertyPage *)m_pcompatinfo_pp);
		   AddPage((CPropertyPage *)&m_reloc_pp);
		   AddPage((CPropertyPage *)&m_transinfo_pp);
		   AddPage((CPropertyPage *)&m_transdata_pp);
		   break;
#endif
	   case SOLARARC_FILE:
		   AddPage((CPropertyPage *)&m_solar_pp);
		   break;
	   case HARMONIC_FILE:
		   AddPage((CPropertyPage *)&m_harmonic_pp);
		   break;
#endif
	   default :
		   break;
	}
	m_old_file_type = m_file_type;
}

void CChartWizard::InitializeSheet(void)
{
 AddPage((CPropertyPage *)&m_chart_typepp);
 AddPage((CPropertyPage *)&m_birthinfo_pp);
 SetWizardMode();
}

void CChartWizard::HandleButtons(void)
{
 DWORD buttons = PSWIZB_NEXT|PSWIZB_BACK;
 if ( !GetActiveIndex() )
    buttons &= PSWIZB_NEXT;
 if ( GetActiveIndex() == (GetPageCount()-1))
    buttons = PSWIZB_BACK|PSWIZB_FINISH;
 SetWizardButtons(buttons);
 if ( buttons & PSWIZB_FINISH )
    SetFinishText("Done");
}


enum ChartType CChartWizard::GetChartTypeEnum()
{
  static enum ChartType types[21] = {BirthSgnOnly,BirthSgnHse,SgnHseAsp,Complete,Numeric,
    Compatibility,Transits,Progress,Reloc,CReturn,CReturnReloc,CReturnTrans,Compos,SolarArc,Harmonic,
	ComposTrans,Fixed,Arabic,Helio,Problem}; 
  return(types[m_chart_type]);
}
