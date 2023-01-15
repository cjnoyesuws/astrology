// DHelpTxt1.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "DHelpTxt1.h"
#include "setup.h"
#include "setlanguage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDHelpTxt

IMPLEMENT_DYNAMIC(CDHelpTxt, CDaoRecordset)

CDHelpTxt::CDHelpTxt(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDHelpTxt)
	m_texttype = _T("");
	m_Text = _T("");
	m_Lang = _T("");
	m_iChunk = -1;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDHelpTxt::GetDefaultDBName()
{
	return GetDatabaseNamePath();
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
	DFX_Short(pFX,_T("[iChunk]"),m_iChunk );
	m_Lang = GetCurLanguage();
	DFX_Text(pFX, _T("[Lang]"), m_Lang);
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
