// DHelpTxt.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DHelpTxt.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHelpTxt

IMPLEMENT_DYNAMIC(CDHelpTxt, CDaoRecordset)

CDHelpTxt::CDHelpTxt(CDaoDatabase* pdb)
: CDaoRecordset((pdb==NULL?pdb:theDirectories.m_pTextDatabase))
{
	//{{AFX_FIELD_INIT(CDHelpTxt)
	m_texttype = _T("");
	m_Text = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDHelpTxt::GetDefaultDBName()
{
	return GetTextDatabaseName();
}

CString CDHelpTxt::GetDefaultSQL()
{
	return _T("[HelpText]");
}

void CDHelpTxt::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDHelpTxt)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[texttype]"), m_texttype);
	DFX_Text(pFX, _T("[Text]"), m_Text);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDHelpTxt diagnostics

#ifdef _DEBUG
void CDHelpTxt::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDHelpTxt::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
