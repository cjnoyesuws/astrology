// ArrayEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "ArrayEdit.h"
#include ".\arrayedit.h"
#include "symbol.hpp"
#include "DReportText1.h"
#include "errors.fns"
#include "setup.h"
#pragma warning( disable : 4995)

// CArrayEdit dialog

IMPLEMENT_DYNAMIC(CArrayEdit, CDialog)
CArrayEdit::CArrayEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CArrayEdit::IDD, pParent)
	, m_Edit(_T(""))
{
 m_index = -1;
 m_orig = "";
 m_item = "";
 m_bModified = FALSE;
}

CArrayEdit::~CArrayEdit()
{
}

void CArrayEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CArrayEdit, CDialog)
	ON_BN_CLICKED(ID_DELETE, OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_BN_CLICKED(IDCAIDC_INSERT, OnBnClickedInsert)
END_MESSAGE_MAP()


// CArrayEdit message handlers

void CArrayEdit::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	if ( m_index != -1 ) {
	   CListBox *pBox = (CListBox *)GetDlgItem(IDC_LIST1);
	   pBox->DeleteString(m_index);
	   m_orig = "";
	   m_Edit = "";
	   m_index = -1;
	   UpdateData(FALSE);
	   m_bModified = TRUE;
	   }
}

void CArrayEdit::OnBnClickedAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if ( m_Edit.GetLength() > 1 ) {
	   CListBox *pBox = (CListBox *)GetDlgItem(IDC_LIST1);
	   pBox->AddString(m_Edit);
	   m_bModified = TRUE;
	   m_orig="";
	   m_Edit="";
	   UpdateData(FALSE);
	}

}

void CArrayEdit::OnCbnSelchangeCombo1()
{
	// TODO: Add your control notification handler code here
   CString m_combo;
   CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
   int sel = pBox->GetCurSel();
    if ( sel != CB_ERR )
		pBox->GetLBText(sel,m_combo);
	else
	    pBox->GetWindowText(m_combo);
	CListBox *pBox2 = (CListBox *)GetDlgItem(IDC_LIST1);
	UpdateData(TRUE);
	if ( m_Edit != m_orig && m_orig.GetLength()>1 && m_index != -1)
	   pBox2->DeleteString(m_index);
	if ( m_Edit != m_orig && m_Edit.GetLength()>1 && m_index != -1)
		pBox2->InsertString(m_index, m_Edit);
	else if ( m_Edit.GetLength() > 1 && m_index == -1 )
		pBox2->AddString(m_Edit);
	if ( m_bModified == TRUE )
		DoSave();
	FillList(m_combo);
   
}

void CArrayEdit::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
	CListBox *pBox = (CListBox *)GetDlgItem(IDC_LIST1);
	UpdateData(TRUE);
	if ( m_Edit != m_orig && m_orig.GetLength()>0 && m_index != -1 && m_Edit.GetLength()>0)
	   pBox->DeleteString(m_index);
	if ( m_Edit != m_orig && m_Edit.GetLength()>0 && m_index != -1)
		pBox->InsertString(m_index, m_Edit);
	else if ( m_Edit.GetLength() > 1 && m_index == -1 )
		pBox->AddString(m_Edit);
	int sel = pBox->GetCurSel();
	m_index = sel;
	pBox->GetText(sel,m_Edit);
	m_orig = m_Edit;
	m_bModified = TRUE;
	UpdateData(FALSE);

}

BOOL CArrayEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_COMBO1);
    pRepSymbols->toArrayCombo(pbox, m_symtypes);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CArrayEdit::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
    CListBox *pBox2 = (CListBox *)GetDlgItem(IDC_LIST1);
	UpdateData(TRUE);
	if ( m_Edit != m_orig && m_orig.GetLength()>1 && m_index != -1)
	   pBox2->DeleteString(m_index);
	if ( m_Edit != m_orig && m_Edit.GetLength()>1 && m_index != -1)
		pBox2->InsertString(m_index, m_Edit);
	else if ( m_Edit.GetLength() > 1 && m_index == -1 )
		pBox2->AddString(m_Edit);
	if ( m_bModified == TRUE )
		DoSave();
	CDialog::OnOK();
}

void CArrayEdit::DoSave()
{
 char sqlbuf[150], key1[25], item[35], ttp[35], alang[11];
 TCHAR errbuf[500];
 CListBox *pBox = (CListBox *)GetDlgItem(IDC_LIST1);
 int iKey, iInd;
 CString tt;
 try {
   CDReportText theSet;
   CString Lang = GetCurLanguage();
   memset(alang,0,11);
#ifdef _UNICODE
   memset(item,0,35);
   memset(ttp,0,35);
   wcstombs(item,m_item,m_item.GetLength());
   wcstombs(ttp,m_texttype,m_texttype.GetLength());
   wcstombs(alang, (LPCTSTR)Lang, Lang.GetLength());
#else
   strcpy(item,m_item);
   strcpy(ttp,m_texttype);
   strcpy(alang,Lang);
#endif
   sscanf(item,"%[^-]", key1 );

  
   sprintf( sqlbuf, "select * from ReportText where textkey='%s' and texttype='%s' and lang='%s' order by iIndex", \
	   key1, ttp, alang);
   theSet.Open(dbOpenDynaset,CString(sqlbuf));
   int cnt = pBox->GetCount();
   iInd = 0;
   if ( !theSet.IsBOF() ) {
	   tt = theSet.m_texttype;
	   iKey = theSet.m_iTextKey;
	   while ( !theSet.IsEOF() ) {
		  theSet.Edit();
		  if (pBox->GetTextLen(iInd)== LB_ERR ) {
			 theSet.CancelUpdate();
			 while ( !theSet.IsEOF() ) {
			    theSet.Delete();
				theSet.MoveNext();
			    iInd++;
			    }
			 break;
		     }
		  pBox->GetText(iInd,theSet.m_text);
	      theSet.Update();
		  theSet.MoveNext();
          iInd++;
	   }
	   for ( ; iInd < cnt; iInd++ ) {
	      theSet.AddNew();
		  if ( pBox->GetTextLen(iInd)> 0 )
		     pBox->GetText(iInd,theSet.m_text);
		  else
			  theSet.m_text = "";
		  if ( theSet.m_text.Trim().GetLength() == 0 && iInd == cnt-1 ) {
			  theSet.CancelUpdate();
			  break;
		     }
		  theSet.m_iIndex = iInd;
		  theSet.m_texttype = tt;
		  theSet.m_textkey = key1;
		  theSet.m_iTextKey= iKey;
		  theSet.Update();
	   }
   } 
   theSet.Close();
}
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
  }
 m_bModified = FALSE;
}

void CArrayEdit::FillList(CString &s )
{
 char sqlbuf[150], key1[25],sbuf[50], ttp[50], alang[11];
 TCHAR errbuf[500];
 CListBox *pBox = (CListBox *)GetDlgItem(IDC_LIST1);
 memset(sbuf,0,50);
 memset(ttp,0,50);
 try {
   CDReportText theSet;
   CString Lang = GetCurLanguage();
   memset(alang,0,11);
   #ifdef _UNICODE
   wcstombs(alang, (LPCTSTR)Lang,Lang.GetLength());
   wcstombs(sbuf,s,s.GetLength());
   wcstombs(ttp,m_texttype,m_texttype.GetLength());
#else
   strcpy(sbuf,s);
   strcpy(alang,(LPCTSTR)Lang);
   strcpy(ttp,m_texttype);
#endif
   sscanf(sbuf,"%[^-]", key1 );
   sprintf( sqlbuf, "select * from ReportText where textkey='%s' and texttype='%s' and Lang='%s' order by iIndex", key1, ttp, alang);
   theSet.Open(dbOpenDynaset,CString(sqlbuf));
   pBox->ResetContent();
   CString t;
   if ( !theSet.IsBOF() ) {
	   pBox->AddString(theSet.m_text);
	   while ( !theSet.IsEOF() ) {
	      theSet.MoveNext();
		  pBox->AddString(theSet.m_text);
	      t = theSet.m_text;   
	   }
	   if ( t.Trim().GetLength()==0)
		   pBox->DeleteString(pBox->GetCount()-1);
   } 
   theSet.Close();
}
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
  }
 m_item = s;
 m_bModified = FALSE;
 m_Edit = "";
 m_orig = "";
 m_index = -1;
 UpdateData(FALSE);
}

void CArrayEdit::OnBnClickedInsert()
{
	// TODO: Add your control notification handler code here
   CListBox *pBox = (CListBox *)GetDlgItem(IDC_LIST1);
   UpdateData(TRUE);
   if ( m_Edit.GetLength() > 0 && m_index != -1) {
	   pBox->InsertString(m_index,m_Edit);
	   m_orig = m_Edit;
       m_bModified = TRUE;
       }
}
