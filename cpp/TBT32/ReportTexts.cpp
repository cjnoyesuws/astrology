// ReportTexts.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "ReportTexts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportTexts

IMPLEMENT_DYNAMIC(CReportTexts, CRecordset)

CReportTexts::CReportTexts(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CReportTexts)
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CReportTexts::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CReportTexts::GetDefaultSQL()
{
	return _T("[ReportText]");
}

void CReportTexts::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CReportTexts)
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CReportTexts diagnostics

#ifdef _DEBUG
void CReportTexts::AssertValid() const
{
	CRecordset::AssertValid();
}

void CReportTexts::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
