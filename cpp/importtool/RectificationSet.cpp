// RectificationSet.cpp : implementation file
//

#include "stdafx.h"
#include "importtool.h"
#include <afxdisp.h>
#include "RectificationSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectificationSet

IMPLEMENT_DYNAMIC(CRectificationSet, CRecordset)

CRectificationSet::CRectificationSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRectificationSet)
	m_name = _T("");
	m_birth_time_known = FALSE;
	m_rect_system = 0;
	m_hours = 0;
	m_minutes = 0;
	m_am_pm = FALSE;
	m_angle = 0;
	m_sign = 0;
	m_totalminutes = 0;
	m_degree= _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRectificationSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CRectificationSet::GetDefaultSQL()
{
	return _T("[rectification]");
}

void CRectificationSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRectificationSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Date(pFX, _T("[birthdate]"), m_birthdate);
	RFX_Bool(pFX, _T("[birth_time_known]"), m_birth_time_known);
	RFX_Int(pFX, _T("[rect_system]"), m_rect_system);
	RFX_Int(pFX, _T("[hours]"), m_hours);
	RFX_Int(pFX, _T("[minutes]"), m_minutes);
	RFX_Bool(pFX, _T("[am_pm]"), m_am_pm);
	RFX_Int(pFX, _T("[angle]"), m_angle);
	RFX_Int(pFX, _T("[sign]"), m_sign);
	RFX_Int(pFX, _T("[totalminutes]"), m_totalminutes);
	RFX_Text(pFX, _T("[degree]"), m_degree);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRectificationSet diagnostics

#ifdef _DEBUG
void CRectificationSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRectificationSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
