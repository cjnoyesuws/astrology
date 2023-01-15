// DTransitset.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DTransitset.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDTransitset

IMPLEMENT_DYNAMIC(CDTransitset, CDaoRecordset)

CDTransitset::CDTransitset(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	//{{AFX_FIELD_INIT(CDTransitset)
	m_AMPM = FALSE;
	m_birthdate = (DATE)0;
	m_country = _T("");
	m_event = _T("");
	m_houroff = 0;
	m_hours = 0;
	m_latitude = _T("");
	m_location = _T("");
	m_longitude = _T("");
	m_minoff = 0;
	m_minutes = 0;
	m_name = _T("");
	m_specialcode = 0;
	m_state = _T("");
	m_timezone = 0;
	m_transdate = (DATE)0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDTransitset::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDTransitset::GetDefaultSQL()
{
	return _T("[transits]");
}

void CDTransitset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDTransitset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Bool(pFX, _T("[AMPM]"), m_AMPM);
	DFX_DateTime(pFX, _T("[birthdate]"), m_birthdate);
	DFX_Text(pFX, _T("[country]"), m_country);
	DFX_Text(pFX, _T("[event]"), m_event);
	DFX_Short(pFX, _T("[houroff]"), m_houroff);
	DFX_Short(pFX, _T("[hours]"), m_hours);
	DFX_Text(pFX, _T("[latitude]"), m_latitude);
	DFX_Text(pFX, _T("[location]"), m_location);
	DFX_Text(pFX, _T("[longitude]"), m_longitude);
	DFX_Short(pFX, _T("[minoff]"), m_minoff);
	DFX_Short(pFX, _T("[minutes]"), m_minutes);
	DFX_Text(pFX, _T("[name]"), m_name);
	DFX_Short(pFX, _T("[specialcode]"), m_specialcode);
	DFX_Text(pFX, _T("[state]"), m_state);
	DFX_Short(pFX, _T("[timezone]"), m_timezone);
	DFX_DateTime(pFX, _T("[transdate]"), m_transdate);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDTransitset diagnostics

#ifdef _DEBUG
void CDTransitset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDTransitset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
