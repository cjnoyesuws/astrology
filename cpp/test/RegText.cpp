// RegText.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "RegText.h"
#include "setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegText

IMPLEMENT_DYNAMIC(CRegText, CRecordset)

CRegText::CRegText(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRegText)
	m_TextType = _T("");
	m_Key1 = _T("");
	m_key2 = _T("");
	m_Key1num = 0;
	m_Key2num = 0;
	m_Text = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRegText::GetDefaultConnect()
{
	return GetConnect();
}

CString CRegText::GetDefaultSQL()
{
	return _T("[RegularText]");
}

void CRegText::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRegText)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TextType]"), m_TextType);
	RFX_Text(pFX, _T("[Key1]"), m_Key1);
	RFX_Text(pFX, _T("[key2]"), m_key2);
	RFX_Int(pFX, _T("[Key1num]"), m_Key1num);
	RFX_Int(pFX, _T("[Key2num]"), m_Key2num);
	RFX_Text(pFX, _T("[Text]"), m_Text);
	if ( bExport == FALSE ) {
	   m_nParams=3;
       pFX->SetFieldType(CFieldExchange::inputParam);
	   RFX_Text(pFX, _T("[TextTypeParam]"), m_TextTypeParam);
	   if ( m_bIntQuery ) {
	      RFX_Int(pFX, _T("[Key1numParam]"), m_Key1numParam);
	      RFX_Int(pFX, _T("[Key2numParam]"), m_Key2numParam);
	      m_strFilter = "TextType=? and Key1num=? and Key2num=?";	
	   }
	   else {
	      RFX_Text(pFX, _T("[Key1Param]"), m_Key1Param);
	      RFX_Text(pFX, _T("[Key2Param]"), m_Key2Param);
	      m_strFilter = "TextType=? and Key1=? and Key2=?";	
	   }
	}
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRegText diagnostics

#ifdef _DEBUG
void CRegText::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRegText::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
