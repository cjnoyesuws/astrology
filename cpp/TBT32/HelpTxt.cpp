// HelpTxt.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "HelpTxt.h"
#include "setup.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpTxt

IMPLEMENT_DYNAMIC(CHelpTxt, CRecordset)

CHelpTxt::CHelpTxt(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CHelpTxt)
	m_texttype = _T("");
	m_Text = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CHelpTxt::GetDefaultConnect()
{
	return GetConnect();
}

CString CHelpTxt::GetDefaultSQL()
{
	return _T("[HelpText]");
}

void CHelpTxt::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CHelpTxt)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[texttype]"), m_texttype);
	RFX_Text(pFX, _T("[Text]"), m_Text);
   pFX->SetFieldType(CFieldExchange::inputParam);
   if ( m_nParams > 0 ) {
      RFX_Text(pFX, _T("[texttypeParam]"), m_TextTypeParam);
      m_strFilter="texttype=?";
      }
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CHelpTxt diagnostics

#ifdef _DEBUG
void CHelpTxt::AssertValid() const
{
	CRecordset::AssertValid();
}

void CHelpTxt::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
