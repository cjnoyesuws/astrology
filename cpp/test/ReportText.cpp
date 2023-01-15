// ReportText.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "ReportText.h"
#include "setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportText

IMPLEMENT_DYNAMIC(CReportText, CRecordset)

CReportText::CReportText(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CReportText)
	m_texttype = _T("");
	m_textkey = _T("");
	m_iIndex = 0;
	m_iTextKey = 0;
	m_text = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CReportText::GetDefaultConnect()
{
	return GetConnect();
}

CString CReportText::GetDefaultSQL()
{
	return _T("[ReportText]");
}

void CReportText::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CReportText)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[texttype]"), m_texttype);
	RFX_Text(pFX, _T("[textkey]"), m_textkey);
	RFX_Int(pFX, _T("[iIndex]"), m_iIndex);
	RFX_Int(pFX, _T("[iTextKey]"), m_iTextKey);
	RFX_Text(pFX, _T("[text]"), m_text);
   if ( m_nParams > 0 ) {
      pFX->SetFieldType(CFieldExchange::inputParam);
      RFX_Text(pFX, _T("[texttypeparam]"), m_texttypeParam);
      m_strFilter="texttype=?";
      if ( m_nParams > 1 && m_bIntQuery ) {
         RFX_Int(pFX, _T("[iTextKeyParam]"), m_iTextKeyParam);
         m_strFilter += " and iTextKey=?";
         }
      else {
         RFX_Text(pFX, _T("[textkeyParam]"), m_textkeyParam);
         RFX_Int(pFX, _T("[iIndexParam]"), m_iIndexParam);
         }
      }   
   //}}AFX_FIELD_MAP
}


void CReportText::DoBulkFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CReportText)
	pFX->SetFieldType(CFieldExchange::outputColumn);
   RFX_Text_Bulk(pFX, _T("[text]"), &m_pStrTexts, &m_pTextLens, 1000 );
   RFX_Int_Bulk(pFX, _T("[iIndex]"), &m_piIndex, &m_piIndexLens );
   RFX_Int_Bulk(pFX, _T("[iTextKey]"), &m_piTextKey, &m_piTextKeyLens );
   pFX->SetFieldType(CFieldExchange::inputParam);
   RFX_Text(pFX, _T("[texttypeparam]"), m_texttypeParam);
}

/////////////////////////////////////////////////////////////////////////////
// CReportText diagnostics

#ifdef _DEBUG
void CReportText::AssertValid() const
{
	CRecordset::AssertValid();
}

void CReportText::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
