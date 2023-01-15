// DRelocationset.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DRelocationset.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRelocationset

IMPLEMENT_DYNAMIC(CDRelocationset, CDaoRecordset)

CDRelocationset::CDRelocationset(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	//{{AFX_FIELD_INIT(CDRelocationset)
	m_birthdate = (DATE)0;
	m_country = _T("");
	m_houroff = 0;
	m_latitude = _T("");
	m_location = _T("");
	m_longitude = _T("");
	m_minoff = 0;
	m_name = _T("");
	m_personal = _T("");
	m_specialcode = 0;
	m_state = _T("");
	m_timezone = 0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDRelocationset::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDRelocationset::GetDefaultSQL()
{
	return _T("relocations");
}

void CDRelocationset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDRelocationset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_DateTime(pFX, _T("[birthdate]"), m_birthdate);
	DFX_Text(pFX, _T("[country]"), m_country);
	DFX_Short(pFX, _T("[houroff]"), m_houroff);
	DFX_Text(pFX, _T("[latitude]"), m_latitude);
	DFX_Text(pFX, _T("[location]"), m_location);
	DFX_Text(pFX, _T("[longitude]"), m_longitude);
	DFX_Short(pFX, _T("[minoff]"), m_minoff);
	DFX_Text(pFX, _T("[name]"), m_name);
	DFX_Text(pFX, _T("[personal]"), m_personal);
	DFX_Short(pFX, _T("[specialcode]"), m_specialcode);
	DFX_Text(pFX, _T("[state]"), m_state);
	DFX_Short(pFX, _T("[timezone]"), m_timezone);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDRelocationset diagnostics

#ifdef _DEBUG
void CDRelocationset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDRelocationset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
