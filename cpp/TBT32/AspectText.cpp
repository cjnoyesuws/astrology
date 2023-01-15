// AspectText.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "AspectText.h"
#include "setup.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAspectText

IMPLEMENT_DYNAMIC(CAspectText, CRecordset)

CAspectText::CAspectText(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAspectText)
	m_TextType = _T("");
	m_Planet1 = _T("");
	m_Planet2 = _T("");
	m_Planet1num = 0;
	m_Planet2num = 0;
	m_Aspect = _T("");
	m_Aspectnum = 0;
	m_Text = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAspectText::GetDefaultConnect()
{
	return GetConnect();
}

CString CAspectText::GetDefaultSQL()
{
	return _T("[AspectText]");
}

void CAspectText::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAspectText)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TextType]"), m_TextType);
	RFX_Text(pFX, _T("[Planet1]"), m_Planet1);
	RFX_Text(pFX, _T("[Planet2]"), m_Planet2);
	RFX_Int(pFX, _T("[Planet1num]"), m_Planet1num);
	RFX_Int(pFX, _T("[Planet2num]"), m_Planet2num);
	RFX_Text(pFX, _T("[Aspect]"), m_Aspect);
	RFX_Int(pFX, _T("[Aspectnum]"), m_Aspectnum);
	RFX_Text(pFX, _T("[Text]"), m_Text);
   if ( m_nParams > 0 ) {
      pFX->SetFieldType(CFieldExchange::inputParam);
      RFX_Text(pFX, _T("[TextTypeParam]"), m_TextTypeParam);
      if ( m_bIntQuery ) {
         RFX_Int(pFX, _T("[Planet1numParam]"), m_Planet1numParam);
	      RFX_Int(pFX, _T("[Planet2numParam]"), m_Planet2numParam);
         RFX_Int(pFX, _T("[AspectnumParam]"), m_AspectnumParam);
         m_strFilter = "Planet1num=? and Planet2num=? and Aspectnum=?";
         }
      else {
         RFX_Text(pFX, _T("[Planet1Param]"), m_Planet1Param);
	      RFX_Text(pFX, _T("[Planet2Param]"), m_Planet2Param);
         RFX_Text(pFX, _T("[AspectParam]"), m_AspectParam);
         m_strFilter = "Planet1=? and Planet2=? and Aspect=?";
         }
      
      }
   
   
   //}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAspectText diagnostics

#ifdef _DEBUG
void CAspectText::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAspectText::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
