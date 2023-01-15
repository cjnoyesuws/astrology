// LocationSet.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include "LocationSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocationSet

IMPLEMENT_DYNAMIC(CLocationSet, CRecordset)

CLocationSet::CLocationSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLocationSet)
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
	m_nDefaultType = dynaset;
}


CString CLocationSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CLocationSet::GetDefaultSQL()
{
	return _T("[locations]");
}

void CLocationSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLocationSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
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
// CLocationSet diagnostics

#ifdef _DEBUG
void CLocationSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLocationSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
