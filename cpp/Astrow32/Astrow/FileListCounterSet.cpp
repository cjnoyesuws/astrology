// FileListCounterSet.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "FileListCounterSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileListCounterSet

IMPLEMENT_DYNAMIC(CFileListCounterSet, CRecordset)

CFileListCounterSet::CFileListCounterSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CFileListCounterSet)
	m_counter = 0;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_nParams=1;
	m_strFilter="IsTextReport=?";
}


CString CFileListCounterSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=astrow");
}

CString CFileListCounterSet::GetDefaultSQL()
{
	return _T("[FileList]");
}

void CFileListCounterSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFileListCounterSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[counter]"), m_counter);
	//}}AFX_FIELD_MAP
}

void CFileListCounterSet::DoBulkFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFileListCounterSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long_Bulk(pFX, _T("[counter]"), &m_pCounters, &m_pCounterLengths);
    pFX->SetFieldType(CFieldExchange::inputParam);
    RFX_Bool(pFX, _T("[IsTextReportParam]"), m_IsTextReportParam);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFileListCounterSet diagnostics

#ifdef _DEBUG
void CFileListCounterSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFileListCounterSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
