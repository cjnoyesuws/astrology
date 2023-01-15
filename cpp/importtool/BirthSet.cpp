// BirthSet.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include "BirthSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBirthSet

IMPLEMENT_DYNAMIC(CBirthSet, CRecordset)

CBirthSet::CBirthSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CBirthSet)
	m_name = _T("");
	m_hours = 0;
	m_minutes = 0;
	m_AMPM = FALSE;
	m_country = _T("");
	m_state = _T("");
	m_location = _T("");
	m_longitude = _T("");
	m_latitude = _T("");
	m_timezone = 0;
	m_specialcode = 0;
	m_houroff = 0;
	m_minoff = 0;
	m_rect = FALSE;
	m_sex = 0;
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CBirthSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CBirthSet::GetDefaultSQL()
{
	return _T("[births]");
}

void CBirthSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBirthSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Date(pFX, _T("[birthdate]"), m_birthdate);
	RFX_Int(pFX, _T("[hours]"), m_hours);
	RFX_Int(pFX, _T("[minutes]"), m_minutes);
	RFX_Bool(pFX, _T("[AMPM]"), m_AMPM);
	RFX_Text(pFX, _T("[country]"), m_country);
	RFX_Text(pFX, _T("[state]"), m_state);
	RFX_Text(pFX, _T("[location]"), m_location);
	RFX_Text(pFX, _T("[longitude]"), m_longitude);
	RFX_Text(pFX, _T("[latitude]"), m_latitude);
	RFX_Int(pFX, _T("[timezone]"), m_timezone);
	RFX_Int(pFX, _T("[specialcode]"), m_specialcode);
	RFX_Int(pFX, _T("[houroff]"), m_houroff);
	RFX_Int(pFX, _T("[minoff]"), m_minoff);
	RFX_Bool(pFX, _T("[rect]"), m_rect);
	RFX_Int(pFX, _T("[sex]"), m_sex);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CBirthSet diagnostics

#ifdef _DEBUG
void CBirthSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBirthSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
