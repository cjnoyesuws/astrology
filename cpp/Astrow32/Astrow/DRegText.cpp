// DRegText.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DRegText.h"
#include "direc.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDRegText

IMPLEMENT_DYNAMIC(CDRegText, CDaoRecordset)

CDRegText::CDRegText(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pTextDatabase))
{
	//{{AFX_FIELD_INIT(CDRegText)
	m_TextType = _T("");
	m_Key1 = _T("");
	m_key2 = _T("");
	m_Key1num = 0;
	m_Key2num = 0;
	m_Text = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDRegText::GetDefaultDBName()
{
	return GetTextDatabaseName();
}

CString CDRegText::GetDefaultSQL()
{
	return _T("[RegularText]");
}

void CDRegText::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDRegText)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[TextType]"), m_TextType);
	DFX_Text(pFX, _T("[Key1]"), m_Key1);
	DFX_Text(pFX, _T("[key2]"), m_key2);
	DFX_Short(pFX, _T("[Key1num]"), m_Key1num);
	DFX_Short(pFX, _T("[Key2num]"), m_Key2num);
	DFX_Text(pFX, _T("[Text]"), m_Text);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDRegText diagnostics

#ifdef _DEBUG
void CDRegText::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDRegText::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
