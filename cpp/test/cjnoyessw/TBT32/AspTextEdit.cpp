// AspTextEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "AspTextEdit.h"
#include "symbol.hpp"
#include "texttypeary.hpp"
#include "errors.fns"
#include "setup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAspTextEdit dialog


CAspTextEdit::CAspTextEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CAspTextEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAspTextEdit)
	m_Text = _T("");
	m_Aspect = -1;
	m_Plan1 = -1;
	m_Plan2 = -1;
	//}}AFX_DATA_INIT
   pFuncs = new RTFFuncs(this);
}


void CAspTextEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAspTextEdit)
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDX_CBIndex(pDX, IDC_ASPECT, m_Aspect);
	DDX_CBIndex(pDX, IDC_PLAN1, m_Plan1);
	DDX_CBIndex(pDX, IDC_PLAN2, m_Plan2);
	DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAspTextEdit, CDialog)
	//{{AFX_MSG_MAP(CAspTextEdit)
	ON_CBN_SELCHANGE(IDC_ASPECT, OnSelchangeAspect)
	ON_CBN_SELCHANGE(IDC_PLAN1, OnSelchangePlan1)
	ON_CBN_SELCHANGE(IDC_PLAN2, OnSelchangePlan2)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(ID_CLEAR, OnUpdateClear)
	ON_UPDATE_COMMAND_UI(ID_COPY, OnUpdateCopy)
	ON_COMMAND(ID_COPY, OnCopy)
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
// CAspTextEdit message handlers

void CAspTextEdit::OnSelchangeAspect() 
{
	// TODO: Add your control notification handler code here
	if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() &&
		    m_AspectStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_ASPECT);
	int sel = pbox->GetCurSel();
    if ( sel != CB_ERR )
		pbox->GetLBText(sel,m_AspectStr);
	else
	    pbox->GetWindowText(m_AspectStr);
    if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() > 0 && 
		   m_AspectStr.GetLength() > 0 )
	   Find();
}

void CAspTextEdit::OnSelchangePlan1() 
{
	// TODO: Add your control notification handler code here
	if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() &&
		    m_AspectStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_PLAN1);
	int sel = pbox->GetCurSel();
    if ( sel != CB_ERR )
		pbox->GetLBText(sel,m_Plan1Str);
	else
	    pbox->GetWindowText(m_Plan1Str);
    if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() > 0 && 
		   m_AspectStr.GetLength() > 0 )
	   Find();
}

void CAspTextEdit::OnSelchangePlan2() 
{
	// TODO: Add your control notification handler code here
	if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() &&
		    m_AspectStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_PLAN2);
	int sel = pbox->GetCurSel();
    if ( sel != CB_ERR )
		pbox->GetLBText(sel,m_Plan2Str);
	else
	    pbox->GetWindowText(m_Plan2Str);
    if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() > 0 && 
		   m_AspectStr.GetLength() > 0 )
	   Find();
	
}


void CAspTextEdit::OnClear() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_TEXT);	
}

void CAspTextEdit::OnUpdateClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   pCmdUI->Enable();	
}

void CAspTextEdit::OnUpdateCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAspTextEdit::OnCopy() 
{
	// TODO: Add your command handler code here
   pFuncs->Copy(IDC_TEXT);	
}

void CAspTextEdit::OnCut() 
{
	// TODO: Add your command handler code here
   pFuncs->Cut(IDC_TEXT);	
}

void CAspTextEdit::OnUpdateCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();	
}

void CAspTextEdit::OnPaste() 
{
	// TODO: Add your command handler code here
   pFuncs->Paste(IDC_TEXT);	
}

void CAspTextEdit::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CAspTextEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char sm1[30], sm2[30], sm3[15], ch;
	CDialog::OnInitDialog();
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_PLAN1);
	char *pt = pATextTypes->toSymType(m_TextType,3);
	sscanf(pt, "%[^|]%c%[^|]%c%s", sm1, &ch, sm2, &ch, sm3  );
	pRegSymbols->toCombo(pbox,1, sm1);
	pbox = (CComboBox *)GetDlgItem(IDC_PLAN2);
    pRegSymbols->toCombo(pbox,2, sm2, 4);
    pbox = (CComboBox *)GetDlgItem(IDC_ASPECT);
    pRegSymbols->toCombo(pbox,3, sm3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAspTextEdit::OnOK() 
{
	// TODO: Add extra validation here
	if ( m_Plan1Str.GetLength() > 0 && m_Plan2Str.GetLength() &&
		    m_AspectStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CDialog::OnOK();
}

void CAspTextEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CAspTextEdit::OnChangeText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified=TRUE;
}

void CAspTextEdit::OnUndo() 
{
	// TODO: Add your command handler code here
	pFuncs->Undo(IDC_TEXT);
}

void CAspTextEdit::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAspTextEdit::OnUpdateText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CAspTextEdit::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_TEXT);
}

void CAspTextEdit::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAspTextEdit::OnHead() 
{
	// TODO: Add your command handler code here
	pFuncs->DoHeading(IDC_TEXT);
}

void CAspTextEdit::OnUpdateHead(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAspTextEdit::OnItal() 
{
	// TODO: Add your command handler code here
	pFuncs->DoItalic(IDC_TEXT);
}

void CAspTextEdit::OnUpdateItal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

//BOOL CAspTextEdit::DestroyWindow() 
//{
//	// TODO: Add your specialized code here and/or call the base class
//	delete pFuncs;
//	return CDialog::DestroyWindow();
//}

void CAspTextEdit::OnUnbold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnBold(IDC_TEXT);
}

void CAspTextEdit::OnUpdateUnbold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAspTextEdit::OnUnheading() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnHeading(IDC_TEXT);
}

void CAspTextEdit::OnUpdateUnheading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();	
}

void CAspTextEdit::OnUnitalic() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnItalic(IDC_TEXT);
}

void CAspTextEdit::OnUpdateUnitalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void getKey(char *buf, CString &ks)
{
 char str[200];

#ifdef _UNICODE
 wcstombs(str,ks,ks.GetLength());
 str[ks.GetLength()] = '\0';
#else
 strcpy(str,ks);
#endif
 sscanf(str,"%[^-]", buf );
}

BOOL CAspTextEdit::Find()
{
  TCHAR errbuf[500]; 
  char sqlbuf[150], key1[25], key2[25], key3[25], alang[11];
  try {
   getKey(key1,m_Plan1Str);
   getKey(key2,m_Plan2Str);
   getKey(key3,m_AspectStr);
   CString Lang = GetCurLanguage();
#ifdef _UNICODE
   sprintf( sqlbuf, "select * from AspectText where Planet1='%s' and Planet2='%s' and Aspect='%s' and TextType='%ls' and Lang='%ls'",
      key1, key2, key3, (LPCTSTR)m_TextType, (LPCTSTR)Lang );
#else
   sprintf( sqlbuf, "select * from AspectText where Planet1='%s' and Planet2='%s' and Aspect='%s' and TextType='%ls'",
      key1, key2, key3, (const char *)m_TextType, (LPCTSTR)Lang );
#endif
   if ( theSet.IsOpen() )
	   theSet.Close();
   theSet.Open(dbOpenDynaset, CString(sqlbuf));
   if ( theSet.IsBOF() )
	   pFuncs->NewRTF(IDC_TEXT);
   else
      pFuncs->SetRTF(IDC_TEXT,theSet.m_Text);
   Invalidate();
 }
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return ( 0 );
  }
 return ( 1 );

}

BOOL CAspTextEdit::Save()
{
 TCHAR errbuf[500]; 
 char key1[25], key2[25], key3[25];
 try {
   if ( !theSet.IsOpen() )
	   theSet.Open();
   if ( theSet.IsBOF() )
	   theSet.AddNew();
   else
	   theSet.Edit();
   getKey(key1,m_Plan1Str);
   getKey(key2,m_Plan2Str);
   getKey(key3,m_AspectStr);
   theSet.m_Planet1 = key1;
   theSet.m_Planet2 = key2;
   theSet.m_Aspect = key3;
   theSet.m_TextType = m_TextType;
   theSet.m_Text = pFuncs->GetRTF(IDC_TEXT);
   CSymbol *pSym=pRegSymbols->Find(key1,1,0);
   if ( pSym == NULL ) {
	   alert_box(_T("Bad Symbol"), _T("Can't Find Symbol %s"), (LPCTSTR)m_Plan1Str );
       return( 0 );
		}
   theSet.m_Planet1num=pSym->value();
   pSym=pRegSymbols->Find(key2,2,0);
   if ( pSym == NULL ) {
	   CSymbol *pSym=pRegSymbols->Find(key2,4,0);
	   if ( pSym == NULL ) {
		  alert_box(_T("Bad Symbol"), _T("Can't Find Symbol %s"), (LPCTSTR)m_Plan2Str );
		  return( 0 );
		  }
	}
   theSet.m_Planet2num=pSym->value();
   pSym=pRegSymbols->Find(key3,3,0);
   if ( pSym == NULL ) {
	   alert_box(_T("Bad Symbol"), _T("Can't Find Symbol %s"), (LPCTSTR)m_AspectStr );
       return( 0 );
		}
   theSet.m_Aspectnum=pSym->value();
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

void CAspTextEdit::OnSpell() 
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
		pFuncs->SetRTF(IDC_TEXT,m_ctrl.GetText());
	}
  Invalidate(FALSE);
}

void CAspTextEdit::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}
