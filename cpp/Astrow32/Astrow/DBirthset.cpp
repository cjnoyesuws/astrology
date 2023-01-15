// DBirthset.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DBirthset.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma warning ( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDBirthset

IMPLEMENT_DYNAMIC(CDBirthset, CDaoRecordset)

CDBirthset::CDBirthset(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	//{{AFX_FIELD_INIT(CDBirthset)
	m_name = _T("");
	m_birthdate = (DATE)0;
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
	m_nDefaultType = dbOpenDynaset;
}


CString CDBirthset::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDBirthset::GetDefaultSQL()
{
	return _T("[births]");
}

void CDBirthset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDBirthset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[name]"), m_name);
	DFX_DateTime(pFX, _T("[birthdate]"), m_birthdate);
	DFX_Short(pFX, _T("[hours]"), m_hours);
	DFX_Short(pFX, _T("[minutes]"), m_minutes);
	DFX_Bool(pFX, _T("[AMPM]"), m_AMPM);
	DFX_Text(pFX, _T("[country]"), m_country);
	DFX_Text(pFX, _T("[state]"), m_state);
	DFX_Text(pFX, _T("[location]"), m_location);
	DFX_Text(pFX, _T("[longitude]"), m_longitude);
	DFX_Text(pFX, _T("[latitude]"), m_latitude);
	DFX_Short(pFX, _T("[timezone]"), m_timezone);
	DFX_Short(pFX, _T("[specialcode]"), m_specialcode);
	DFX_Short(pFX, _T("[houroff]"), m_houroff);
	DFX_Short(pFX, _T("[minoff]"), m_minoff);
	DFX_Bool(pFX, _T("[rect]"), m_rect);
	DFX_Short(pFX, _T("[sex]"), m_sex);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDBirthset diagnostics

#ifdef _DEBUG
void CDBirthset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDBirthset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
