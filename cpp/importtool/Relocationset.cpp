// Relocationset.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include "Relocationset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelocationset

IMPLEMENT_DYNAMIC(CRelocationset, CRecordset)

CRelocationset::CRelocationset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRelocationset)
	m_personal = _T("");
	m_name = _T("");
	m_country = _T("");
	m_state = _T("");
	m_location = _T("");
	m_longitude = _T("");
	m_latitude = _T("");
	m_timezone = 0;
	m_specialcode = 0;
	m_houroff = 0;
	m_minoff = 0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRelocationset::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CRelocationset::GetDefaultSQL()
{
	return _T("[relocations]");
}

void CRelocationset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRelocationset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[personal]"), m_personal);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Date(pFX, _T("[birthdate]"), m_birthdate);
	RFX_Text(pFX, _T("[country]"), m_country);
	RFX_Text(pFX, _T("[state]"), m_state);
	RFX_Text(pFX, _T("[location]"), m_location);
	RFX_Text(pFX, _T("[longitude]"), m_longitude);
	RFX_Text(pFX, _T("[latitude]"), m_latitude);
	RFX_Int(pFX, _T("[timezone]"), m_timezone);
	RFX_Int(pFX, _T("[specialcode]"), m_specialcode);
	RFX_Int(pFX, _T("[houroff]"), m_houroff);
	RFX_Int(pFX, _T("[minoff]"), m_minoff);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRelocationset diagnostics

#ifdef _DEBUG
void CRelocationset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRelocationset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
