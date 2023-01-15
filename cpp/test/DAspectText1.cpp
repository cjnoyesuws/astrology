// DAspectText1.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "DAspectText1.h"
#include "setup.h"
#include "setlanguage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDAspectText

IMPLEMENT_DYNAMIC(CDAspectText, CDaoRecordset)

CDAspectText::CDAspectText(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDAspectText)
	m_TextType = _T("");
	m_Planet1 = _T("");
	m_Planet2 = _T("");
	m_Planet1num = 0;
	m_Planet2num = 0;
	m_Aspect = _T("");
	m_Aspectnum = 0;
	m_Text = _T("");
	m_Lang = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDAspectText::GetDefaultDBName()
{
	return GetDatabaseNamePath();
}

CString CDAspectText::GetDefaultSQL()
{
	return _T("[AspectText]");
}

void CDAspectText::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDAspectText)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[TextType]"), m_TextType);
	DFX_Text(pFX, _T("[Planet1]"), m_Planet1);
	DFX_Text(pFX, _T("[Planet2]"), m_Planet2);
	DFX_Short(pFX, _T("[Planet1num]"), m_Planet1num);
	DFX_Short(pFX, _T("[Planet2num]"), m_Planet2num);
	DFX_Text(pFX, _T("[Aspect]"), m_Aspect);
	DFX_Short(pFX, _T("[Aspectnum]"), m_Aspectnum);
	DFX_Text(pFX, _T("[Text]"), m_Text);
	m_Lang = GetCurLanguage();
	DFX_Text(pFX, _T("[Lang]"), m_Lang);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDAspectText diagnostics

#ifdef _DEBUG
void CDAspectText::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDAspectText::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
