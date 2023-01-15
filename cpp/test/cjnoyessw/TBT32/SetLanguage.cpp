// SetLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "SetLanguage.h"
#include "dlanguages.h"
#include "errors.fns"
// CSetLanguage dialog

IMPLEMENT_DYNAMIC(CSetLanguage, CDialog)
CSetLanguage::CSetLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CSetLanguage::IDD, pParent)
{
}

CSetLanguage::~CSetLanguage()
{
}

void CSetLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LANGUAGE, m_language);
}


BEGIN_MESSAGE_MAP(CSetLanguage, CDialog)
	ON_CBN_SELCHANGE(IDC_LANGUAGE, OnCbnSelchangeLanguage)
END_MESSAGE_MAP()


// CSetLanguage message handlers

BOOL CSetLanguage::OnInitDialog()
{
	CDialog::OnInitDialog();
    UpdateData(FALSE);
	m_language.AddString(_T("Default"));
	try { 
	  CDLanguages langset;
      langset.Open();
	  if (!langset.IsEOF()) {
		while ( !langset.IsEOF() ) {
			CString str = langset.m_langcode + _T("-") + langset.m_Description;
		    m_language.AddString(str);
			langset.MoveNext();
		    }
	     }
	    langset.Close();
	  }
	  catch ( CDaoException *e ) {
	    TCHAR errbuf[500];
		e->GetErrorMessage(errbuf,499);
        alert_box(_T("Error on Database"), errbuf );
	  }
      
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetLanguage::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnOK();
}

void CSetLanguage::OnCbnSelchangeLanguage()
{
	// TODO: Add your control notification handler code here
    int sel = m_language.GetCurSel();
	CString str;
	m_language.GetLBText(sel,str);
    if ( str == _T("Default") )
		m_langcode = _T("English");
	else {
		int pos = str.Find(_T('-'));
		if ( pos > 0 )
			m_langcode = str.Left(pos);
		else
			m_langcode = str;
	}
	AfxGetApp()->WriteProfileString(_T("TBT"),_T("CurrLanguage"),m_langcode);
}

