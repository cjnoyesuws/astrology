// NewLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "NewLanguage.h"
#include "DLanguages.h"
#include "errors.fns"
// CNewLanguage dialog

IMPLEMENT_DYNAMIC(CNewLanguage, CDialog)
CNewLanguage::CNewLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CNewLanguage::IDD, pParent)
	, m_Description(_T(""))
	, m_langcode(_T(""))
{
}

CNewLanguage::~CNewLanguage()
{
}

void CNewLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DESC, m_Description);
	DDX_Text(pDX, IDC_LANGCODE, m_langcode);
	DDV_MaxChars(pDX, m_langcode, 10);
}


BEGIN_MESSAGE_MAP(CNewLanguage, CDialog)
END_MESSAGE_MAP()


// CNewLanguage message handlers

void CNewLanguage::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    UpdateData();
	CDLanguages langset;
	try {
	  langset.Open();
	  langset.AddNew();
	  langset.m_langcode = m_langcode;
	  langset.m_Description = m_Description;
	  langset.Update();
	}
	catch ( CDaoException *e ) {
	   TCHAR errbuf[500];
	   e->GetErrorMessage(errbuf,499);
       alert_box(_T("Error on Database"), errbuf );
	}
	CDialog::OnOK();
}
