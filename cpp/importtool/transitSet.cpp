// transitSet.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include <afxdisp.h>
#include "transitSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CtransitSet

IMPLEMENT_DYNAMIC(CtransitSet, CRecordset)

CtransitSet::CtransitSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CtransitSet)
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
	m_Event = _T("");
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CtransitSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CtransitSet::GetDefaultSQL()
{
	return _T("[transits]");
}

void CtransitSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CtransitSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Date(pFX, _T("[birthdate]"), m_birthdate);
	RFX_Date(pFX, _T("[transdate]"), m_transdate);
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
	RFX_Text(pFX, _T("[event]"), m_Event);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CtransitSet diagnostics

#ifdef _DEBUG
void CtransitSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CtransitSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
