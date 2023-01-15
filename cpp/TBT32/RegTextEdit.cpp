// RegTextEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "RegTextEdit.h"
#include "symbol.hpp"
#include "texttypeary.hpp"
#include "errors.fns"
#include "setup.h"
#include ".\regtextedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegTextEdit dialog


CRegTextEdit::CRegTextEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CRegTextEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegTextEdit)
	m_Key1 = -1;
	m_Key2 = "";
	m_Text = "";
	//}}AFX_DATA_INIT
   pFuncs = new RTFFuncs(this);
}


void CRegTextEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegTextEdit)
	DDX_CBIndex(pDX, IDC_KEY1, m_Key1);
	DDX_CBString(pDX, IDC_KEY2, m_Key2);
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegTextEdit, CDialog)
	//{{AFX_MSG_MAP(CRegTextEdit)
	ON_CBN_SELCHANGE(IDC_KEY1, OnSelchangeKey1)
	ON_CBN_SELCHANGE(IDC_KEY2, OnSelchangeKey2)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(ID_CLEAR, OnUpdateClear)
	ON_COMMAND(ID_COPY, OnCopy)
	ON_UPDATE_COMMAND_UI(ID_COPY, OnUpdateCopy)
	ON_COMMAND(ID_CUT, OnCut)
	ON_UPDATE_COMMAND_UI(ID_CUT, OnUpdateCut)
	ON_COMMAND(ID_PASTE, OnPaste)
	ON_UPDATE_COMMAND_UI(ID_PASTE, OnUpdatePaste)
	ON_EN_CHANGE(IDC_TEXT, OnChangeText)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, OnUpdateUndo)
	ON_EN_UPDATE(IDC_TEXT, OnUpdateText)
	ON_COMMAND(ID_BOLD, OnBold)
	ON_UPDATE_COMMAND_UI(ID_BOLD, OnUpdateBold)
	ON_COMMAND(ID_HEAD, OnHead)
	ON_UPDATE_COMMAND_UI(ID_HEAD, OnUpdateHead)
	ON_COMMAND(ID_ITAL, OnItal)
	ON_UPDATE_COMMAND_UI(ID_ITAL, OnUpdateItal)
	ON_COMMAND(ID_UNBOLD, OnUnbold)
	ON_UPDATE_COMMAND_UI(ID_UNBOLD, OnUpdateUnbold)
	ON_COMMAND(ID_UNHEADING, OnUnheading)
	ON_UPDATE_COMMAND_UI(ID_UNHEADING, OnUpdateUnheading)
	ON_COMMAND(ID_UNITALIC, OnUnitalic)
	ON_UPDATE_COMMAND_UI(ID_UNITALIC, OnUpdateUnitalic)
	ON_COMMAND(ID_SPELL, OnSpell)
	ON_UPDATE_COMMAND_UI(ID_SPELL, OnUpdateSpell)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegTextEdit message handlers

void CRegTextEdit::OnOK() 
{
	// TODO: Add extra validation here
	if ( m_Key1Str.GetLength() > 0 && m_Key1Str.GetLength()) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CDialog::OnOK();
}

void CRegTextEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CRegTextEdit::OnSelchangeKey1() 
{
	// TODO: Add your control notification handler code here
	if ( m_Key1Str.GetLength() > 0 && m_Key1Str.GetLength()) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_KEY1);
	int sel = pbox->GetCurSel();
    if ( sel != CB_ERR )
		pbox->GetLBText(sel,m_Key1Str);
	else
	    pbox->GetWindowText(m_Key1Str);

    if ( m_Key1Str.GetLength() > 0 && m_Key2Str.GetLength() > 0 )
	   Find();
}

void CRegTextEdit::OnSelchangeKey2() 
{
	// TODO: Add your control notification handler code here
	if ( m_Key1Str.GetLength() > 0 && m_Key2Str.GetLength()) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_KEY2);
	int sel = pbox->GetCurSel();
    if ( sel != CB_ERR )
		pbox->GetLBText(sel,m_Key2Str);
	else
	    pbox->GetWindowText(m_Key2Str);
    if ( m_Key1Str.GetLength() > 0 && m_Key2Str.GetLength() > 0 )
	   Find();
}

void CRegTextEdit::OnClear() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_TEXT);
}

void CRegTextEdit::OnUpdateClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnCopy() 
{
	// TODO: Add your command handler code here
   pFuncs->Copy(IDC_TEXT);	
}

void CRegTextEdit::OnUpdateCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnCut() 
{
	// TODO: Add your command handler code here
   pFuncs->Cut(IDC_TEXT);	
	
}

void CRegTextEdit::OnUpdateCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnPaste() 
{
	// TODO: Add your command handler code here
   pFuncs->Paste(IDC_TEXT);	
	
}

void CRegTextEdit::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CRegTextEdit::OnInitDialog() 
{
	char sm1[30], sm2[30], ch;
	CDialog::OnInitDialog();
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_KEY1);
	char *pt = pATextTypes->toSymType(m_TextType,2);
	sscanf(pt, "%[^|]%c%s", sm1, &ch, sm2 );
	pRegSymbols->toCombo(pbox,1, sm1);
	pbox = (CComboBox *)GetDlgItem(IDC_KEY2);
    pRegSymbols->toCombo(pbox,2, sm2);
	// TODO: Add extra initialization here
//	delete pFuncs;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegTextEdit::OnChangeText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified=TRUE;
}

void CRegTextEdit::OnUndo() 
{
	// TODO: Add your command handler code here
   pFuncs->Undo(IDC_TEXT);	
	
}

void CRegTextEdit::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnUpdateText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CRegTextEdit::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_TEXT);
}

void CRegTextEdit::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnHead() 
{
	// TODO: Add your command handler code here
	pFuncs->DoHeading(IDC_TEXT);
}

void CRegTextEdit::OnUpdateHead(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnItal() 
{
	// TODO: Add your command handler code here
	pFuncs->DoItalic(IDC_TEXT);
}

void CRegTextEdit::OnUpdateItal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnUnbold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnBold(IDC_TEXT);
}

void CRegTextEdit::OnUpdateUnbold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnUnheading() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnHeading(IDC_TEXT);
}

void CRegTextEdit::OnUpdateUnheading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CRegTextEdit::OnUnitalic() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnItalic(IDC_TEXT);
}

void CRegTextEdit::OnUpdateUnitalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CRegTextEdit::Find()
{
TCHAR errbuf[500], sqlbuf[125], key1[25], key2[25];
try {
	CString Lang = GetCurLanguage();
#ifdef _UNICODE    
	_stscanf((LPCTSTR)m_Key1Str,_T("%l[^-]"), key1 );
	_stscanf((LPCTSTR)m_Key2Str,_T("%l[^-]"), key2 );
	_stprintf( sqlbuf, _T("select * from RegularText where Key1='%ls' and Key2='%ls' and TextType='%ls' and Lang='%ls'"),
      key1, key2, (LPCTSTR)m_TextType, (LPCTSTR)Lang );
#else
    sscanf((LPCTSTR)m_Key1Str,"%[^-]", key1 );
	sscanf((LPCTSTR)m_Key2Str,"%[^-]", key2 );
	sprintf( sqlbuf, "select * from RegularText where Key1='%s' and Key2='%s' and TextType='%s'",
      key1, key2, (LPCTSTR)m_TextType);
#endif
	if ( theSet.IsOpen() )
	   theSet.Close();
   theSet.Open(dbOpenDynaset,sqlbuf);
   if ( theSet.IsBOF() )
	   pFuncs->NewRTF(IDC_TEXT);
   else
      pFuncs->SetRTF(IDC_TEXT, theSet.m_Text );
   Invalidate();
 }
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return ( 0 );
  }
 return ( 1 );

}

BOOL CRegTextEdit::Save()
{
 TCHAR errbuf[500], key1[25], key2[25];
#ifdef _UNICODE
 _stscanf((LPCTSTR)m_Key1Str,_T("%l[^-]"), key1 );
 _stscanf((LPCTSTR)m_Key2Str,_T("%l[^-]"), key2 );
#else
 sscanf((const char *)m_Key1Str,"%[^-]", key1 );
 sscanf((const char *)m_Key2Str,"%[^-]", key2 );
#endif
 try {
   if ( !theSet.IsOpen() )
	   theSet.Open();
   if ( theSet.IsBOF() )
	   theSet.AddNew();
   else
	   theSet.Edit();
   theSet.m_Key1 = key1;
   theSet.m_key2 = key2;
   theSet.m_TextType = m_TextType;
   theSet.m_Text = pFuncs->GetRTF(IDC_TEXT);
   CSymbol *pSym=pRegSymbols->Find(key1,1,0);
   if ( pSym == NULL ) {
	   alert_box(_T("Bad Symbol"), _T("Can't Find Symbol %s"), (LPCTSTR)m_Key1Str );
       return( 0 );
		}
   theSet.m_Key1num=pSym->value();
   pSym=pRegSymbols->Find(key2,2,0);
   if ( pSym == NULL ) {
	   alert_box(_T("Bad Symbol"), _T("Can't Find Symbol %s"), (LPCTSTR)m_Key2Str );
       return( 0 );
		}
   theSet.m_Key2num=pSym->value();
   theSet.Update();
   theSet.Close();
 }
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return ( 0 );
  }
 return ( 1 );

}

void CRegTextEdit::OnSpell() 
{
	// TODO: Add your command handler code here
	CString str = pFuncs->GetRTF(IDC_TEXT);

	// Interactively check the spelling of the CString.
	// The CString's contents will be displayed so the user can see
	// errors in context. Any corrections made by the user will update
	// the CString.
	// Note that WSpell's ShowContext property has been set to True.
	m_ctrl.SetText(pFuncs->getBasicString());
	m_ctrl.SetShowDialog(TRUE);
	m_ctrl.SetShowContext(TRUE);
	if (m_ctrl.Start() >= 0) {
		CString checked = pFuncs->GetTabString();
		checked += m_ctrl.GetText();
		pFuncs->SetRTF(IDC_TEXT,checked);
	}
   Invalidate(FALSE);
}

void CRegTextEdit::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
    pCmdUI->Enable();	
}

BOOL CRegTextEdit::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
    delete pFuncs;
	return CDialog::DestroyWindow();
}
