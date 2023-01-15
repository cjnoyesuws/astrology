// DregText1.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "DregText1.h"
#include "setup.h"
#include "setlanguage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDregText

IMPLEMENT_DYNAMIC(CDregText, CDaoRecordset)

CDregText::CDregText(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDregText)
	m_TextType = _T("");
	m_Key1 = _T("");
	m_key2 = _T("");
	m_Key1num = 0;
	m_Key2num = 0;
	m_Text = _T("");
	m_Lang = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDregText::GetDefaultDBName()
{
	return GetDatabaseNamePath();
}

CString CDregText::GetDefaultSQL()
{
	return _T("[RegularText]");
}

void CDregText::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDregText)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[TextType]"), m_TextType);
	DFX_Text(pFX, _T("[Key1]"), m_Key1);
	DFX_Text(pFX, _T("[key2]"), m_key2);
	DFX_Short(pFX, _T("[Key1num]"), m_Key1num);
	DFX_Short(pFX, _T("[Key2num]"), m_Key2num);
	DFX_Text(pFX, _T("[Text]"), m_Text);
	m_Lang = GetCurLanguage();
	DFX_Text(pFX, _T("[Lang]"), m_Lang);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDregText diagnostics

#ifdef _DEBUG
void CDregText::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDregText::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
