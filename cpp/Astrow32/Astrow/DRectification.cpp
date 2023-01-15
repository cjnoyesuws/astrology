// DRectification.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DRectification.h"
#include "direc.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRectification

IMPLEMENT_DYNAMIC(CDRectification, CDaoRecordset)

CDRectification::CDRectification(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pTextDatabase))
{
	//{{AFX_FIELD_INIT(CDRectification)
	m_name = _T("");
	m_birthdate = (DATE)0;
	m_birth_time_known = FALSE;
	m_rect_system = 0;
	m_hours = 0;
	m_minutes = 0;
	m_am_pm = FALSE;
	m_angle = 0;
	m_sign = 0;
	m_totalminutes = 0;
	m_degree = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDRectification::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDRectification::GetDefaultSQL()
{
	return _T("[rectification]");
}

void CDRectification::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDRectification)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[name]"), m_name);
	DFX_DateTime(pFX, _T("[birthdate]"), m_birthdate);
	DFX_Bool(pFX, _T("[birth_time_known]"), m_birth_time_known);
	DFX_Short(pFX, _T("[rect_system]"), m_rect_system);
	DFX_Short(pFX, _T("[hours]"), m_hours);
	DFX_Short(pFX, _T("[minutes]"), m_minutes);
	DFX_Bool(pFX, _T("[am_pm]"), m_am_pm);
	DFX_Short(pFX, _T("[angle]"), m_angle);
	DFX_Short(pFX, _T("[sign]"), m_sign);
	DFX_Short(pFX, _T("[totalminutes]"), m_totalminutes);
	DFX_Text(pFX, _T("[degree]"), m_degree);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDRectification diagnostics

#ifdef _DEBUG
void CDRectification::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDRectification::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
