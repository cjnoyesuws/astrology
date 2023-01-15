// DAspText.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "DAspText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma warning( disable : 4995 )
/////////////////////////////////////////////////////////////////////////////
// CDAspText

IMPLEMENT_DYNAMIC(CDAspText, CDaoRecordset)

CDAspText::CDAspText(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDAspText)
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDAspText::GetDefaultDBName()
{
	return _T("D:\\Astrow32\\DB\\astrow972a.mdb");
}

CString CDAspText::GetDefaultSQL()
{
	return _T("");
}

void CDAspText::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDAspText)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDAspText diagnostics

#ifdef _DEBUG
void CDAspText::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDAspText::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
