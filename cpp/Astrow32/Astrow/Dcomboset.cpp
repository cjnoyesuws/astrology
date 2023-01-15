// DComboset.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DComboset.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDComboset

IMPLEMENT_DYNAMIC(CDComboset, CDaoRecordset)

CDComboset::CDComboset(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pDatabase))
{
	//{{AFX_FIELD_INIT(CDComboset)
	m_data = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDComboset::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDComboset::GetDefaultSQL()
{
	return _T("[locations]");
}

void CDComboset::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDComboset)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, m_field, m_data);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDComboset diagnostics

#ifdef _DEBUG
void CDComboset::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDComboset::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
