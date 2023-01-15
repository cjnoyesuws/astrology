// DReportText.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "DReportText.h"
#include "direc.hpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDReportText

IMPLEMENT_DYNAMIC(CDReportText, CDaoRecordset)

CDReportText::CDReportText(CDaoDatabase* pdb)
: CDaoRecordset((pdb!=NULL?pdb:theDirectories.m_pTextDatabase))
{
	//{{AFX_FIELD_INIT(CDReportText)
	m_texttype = _T("");
	m_textkey = _T("");
	m_iIndex = 0;
	m_iTextKey = 0;
	m_text = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDReportText::GetDefaultDBName()
{
	return GetTextDatabaseName();
}

CString CDReportText::GetDefaultSQL()
{
	return _T("[ReportText]");
}

void CDReportText::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDReportText)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[texttype]"), m_texttype);
	DFX_Text(pFX, _T("[textkey]"), m_textkey);
	DFX_Short(pFX, _T("[iIndex]"), m_iIndex);
	DFX_Short(pFX, _T("[iTextKey]"), m_iTextKey);
	DFX_Text(pFX, _T("[text]"), m_text);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDReportText diagnostics

#ifdef _DEBUG
void CDReportText::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDReportText::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
