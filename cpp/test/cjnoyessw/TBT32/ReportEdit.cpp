// ReportEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "ReportEdit.h"
#include "symbol.hpp"
#include "texttypeary.hpp"
#include "errors.fns"
#include "setup.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern void TrimTraillfcr(CString &s);
/////////////////////////////////////////////////////////////////////////////
// CReportEdit dialog


CReportEdit::CReportEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CReportEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportEdit)
	m_Index = 0;
	m_Text = _T("");
	m_TextId = -1;
	//}}AFX_DATA_INIT
   pFuncs = new RTFFuncs(this);
}


void CReportEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportEdit)
	DDX_Text(pDX, IDC_INDEX, m_Index);
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDX_CBIndex(pDX, IDC_TEXTID, m_TextId);
	DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TABCTRLCTRL1, m_tabctrl);
}


BEGIN_MESSAGE_MAP(CReportEdit, CDialog)
	//{{AFX_MSG_MAP(CReportEdit)
	ON_CBN_SELCHANGE(IDC_TEXTID, OnSelchangeTextid)
	ON_EN_CHANGE(IDC_INDEX, OnChangeIndex)
	ON_COMMAND(ID_PASTE, OnPaste)
	ON_UPDATE_COMMAND_UI(ID_PASTE, OnUpdatePaste)
	ON_COMMAND(ID_CUT, OnCut)
	ON_UPDATE_COMMAND_UI(ID_CUT, OnUpdateCut)
	ON_UPDATE_COMMAND_UI(ID_COPY, OnUpdateCopy)
	ON_COMMAND(ID_COPY, OnCopy)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(ID_CLEAR, OnUpdateClear)
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
// CReportEdit message handlers

void CReportEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CReportEdit::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if ( m_TextIdStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CDialog::OnOK();
}

void CReportEdit::OnSelchangeTextid() 
{
	// TODO: Add your control notification handler code here
	if ( m_TextIdStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	}
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_TEXTID);
	int sel = pbox->GetCurSel();
    if ( sel != CB_ERR )
		pbox->GetLBText(sel,m_TextIdStr);
	else
	    pbox->GetWindowText(m_TextIdStr);
	m_Index = 0;
	UpdateData(FALSE);
	pbox->SelectString(0,m_TextIdStr);
    Find();
    
}

void CReportEdit::OnChangeIndex() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    if ( m_TextIdStr.GetLength() > 0 ) {
		if ( pFuncs->Modified(IDC_TEXT) ) {
		   if ( MessageBox(_T("Do You Want to Save This Entry?"), _T("Record is Modified"), MB_ICONQUESTION|MB_YESNO ) == IDYES )
			   Save();
			}
	   UpdateData(TRUE);
	   Find();
	}
}

void CReportEdit::OnPaste() 
{
	// TODO: Add your command handler code here
	pFuncs->Paste(IDC_TEXT);
}

void CReportEdit::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnCut() 
{
	// TODO: Add your command handler code here
   pFuncs->Cut(IDC_TEXT);
}

void CReportEdit::OnUpdateCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnUpdateCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnCopy() 
{
	// TODO: Add your command handler code here
   pFuncs->Copy(IDC_TEXT);
}

void CReportEdit::OnClear() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_TEXT);
}

void CReportEdit::OnUpdateClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CReportEdit::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete pFuncs;
	return CDialog::DestroyWindow();
}

BOOL CReportEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CComboBox *pbox = (CComboBox *)GetDlgItem(IDC_TEXTID);
	char *pt = pATextTypes->toSymType(m_TextType,1);
	pRepSymbols->toCombo(pbox,1, pt);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportEdit::OnChangeText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified=TRUE;
}

void CReportEdit::OnUndo() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_TEXT);	
}

void CReportEdit::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnUpdateText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CReportEdit::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_TEXT);
}

void CReportEdit::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnHead() 
{
	// TODO: Add your command handler code here
	pFuncs->DoHeading(IDC_TEXT);
}

void CReportEdit::OnUpdateHead(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnItal() 
{
	// TODO: Add your command handler code here
	pFuncs->DoItalic(IDC_TEXT);
}

void CReportEdit::OnUpdateItal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnUnbold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnBold(IDC_TEXT);
}

void CReportEdit::OnUpdateUnbold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnUnheading() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnHeading(IDC_TEXT);
}

void CReportEdit::OnUpdateUnheading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CReportEdit::OnUnitalic() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnItalic(IDC_TEXT);
}

void CReportEdit::OnUpdateUnitalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CReportEdit::Find()
{
 TCHAR errbuf[500], sqlbuf[150], key1[25];
 CString Lang = GetCurLanguage();
try {
#ifdef _UNICODE
   _stscanf((const TCHAR *)m_TextIdStr,_T("%l[^-]"), key1 );
   _stprintf( sqlbuf, _T("select * from ReportText where TextType='%ls' and textkey='%ls' and iIndex=%d and Lang='%ls'"),
      (LPCTSTR)m_TextType, key1, m_Index, (LPCTSTR)Lang);
#else
   sscanf((const char *)m_TextIdStr,_T("%[^-]"), key1 );
   sprintf( sqlbuf, _T("select * from ReportText where TextType='%s' and textkey='%s' and iIndex=%d and Lang='%s'"),
      (LPCTSTR)m_TextType, key1, m_Index, (LPCTSTR)Lang);
#endif

  
   if ( theSet.IsOpen() )
	   theSet.Close();
   theSet.Open(dbOpenDynaset,sqlbuf);
   if ( theSet.IsBOF() )
	   pFuncs->NewRTF(IDC_TEXT);
   else
      pFuncs->SetRTF(IDC_TEXT,theSet.m_text);
   m_tabctrl.Set_TabString(pFuncs->GetTabString());
   Invalidate(FALSE); 
}
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,499);
   alert_box(_T("Error on Database"), errbuf );
   return ( 0 );
  }
 return ( 1 );

}

BOOL CReportEdit::Save()
{
 TCHAR errbuf[500], key1[25];
try {
   if ( theSet.IsOpen() )
	   theSet.Close();
   theSet.Open();
   if ( theSet.IsBOF() )
	   theSet.AddNew();
   else
	   theSet.Edit();
#ifdef _UNICODE
   _stscanf((const TCHAR *)m_TextIdStr,_T("%l[^-]"), key1 );
#else
   _stscanf((const TCHAR *)m_TextIdStr,_T("%[^-]"), key1 );
#endif

   theSet.m_textkey = key1;
   theSet.m_iIndex = m_Index;
   theSet.m_texttype = m_TextType;
   pFuncs->SetTabString(m_tabctrl.GetTabString());
   theSet.m_text = pFuncs->GetRTF(IDC_TEXT);
   TrimTraillfcr(theSet.m_text);
   CSymbol *pSym=pRepSymbols->Find(key1,0);
   if ( pSym == NULL ) {
	   alert_box(_T("Bad Symbol"), _T("Can't Find Symbol %s"), m_TextIdStr );
       return( 0 );
		}
   theSet.m_iTextKey=pSym->value();
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

void CReportEdit::OnSpell() 
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
		// Put the corrected text back into the edit control.
		pFuncs->SetRTF(IDC_TEXT,checked);
	}
}

void CReportEdit::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}
