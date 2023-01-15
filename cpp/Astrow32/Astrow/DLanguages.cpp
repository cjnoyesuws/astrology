// DHelpTxt1.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "DLanguages.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDHelpTxt

IMPLEMENT_DYNAMIC(CDLanguages, CDaoRecordset)

CDLanguages::CDLanguages(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDHelpTxt)
	m_langcode = _T("");
	m_Description = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDLanguages::GetDefaultDBName()
{
	return GetDatabaseName();
}

CString CDLanguages::GetDefaultSQL()
{
	return _T("[Languages]");
}

void CDLanguages::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDHelpTxt)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[langcode]"), m_langcode);
	DFX_Text(pFX, _T("[Description]"), m_Description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDHelpTxt diagnostics

#ifdef _DEBUG
void CDLanguages::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDLanguages::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
