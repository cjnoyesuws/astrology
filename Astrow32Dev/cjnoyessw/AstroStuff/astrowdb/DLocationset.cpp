// DLocationset.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DLocationset.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDLocationset

IMPLEMENT_DYNAMIC(CDLocationset, CDaoRecordset)

CDLocationset::CDLocationset(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	//{{AFX_FIELD_INIT(CDLocationset)
	m_country = _T("");
	m_state = _T("");
	m_location = _T("");
	m_longitude = _T("");
	m_latitude = _T("");
	m_timezone = 0;
	m_specialcode = 0;
	m_houroff = 0;
	m_minoff = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDLocationset::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDLocationset::GetDefaultSQL()
{
	return _T("[locations]");
}

void CDLocationset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDLocationset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[country]"), m_country);
	DFX_Text(pFX, _T("[state]"), m_state);
	DFX_Text(pFX, _T("[location]"), m_location);
	DFX_Text(pFX, _T("[longitude]"), m_longitude);
	DFX_Text(pFX, _T("[latitude]"), m_latitude);
	DFX_Short(pFX, _T("[timezone]"), m_timezone);
	DFX_Short(pFX, _T("[specialcode]"), m_specialcode);
	DFX_Short(pFX, _T("[houroff]"), m_houroff);
	DFX_Short(pFX, _T("[minoff]"), m_minoff);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDLocationset diagnostics

#ifdef _DEBUG
void CDLocationset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDLocationset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
