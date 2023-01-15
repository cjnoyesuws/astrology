// HelpEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TBT32.h"
#include "wspell.h"
#include "tabctrlctrl1.h"
#include "HelpEdit.h"
#include "errors.fns"
#include ".\helpedit.h"
#include "setup.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpEdit dialog


CHelpEdit::CHelpEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpEdit)
	m_Text = _T("");
	//}}AFX_DATA_INIT
   pFuncs = new RTFFuncs(this);
}


void CHelpEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpEdit)
	DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_TABCTRLCTRL1, m_tabctrl);
}


BEGIN_MESSAGE_MAP(CHelpEdit, CDialog)
	//{{AFX_MSG_MAP(CHelpEdit)
	ON_COMMAND(ID_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(ID_CLEAR, OnUpdateClear)
	ON_COMMAND(ID_COPY, OnCopy)
	ON_UPDATE_COMMAND_UI(ID_COPY, OnUpdateCopy)
	ON_COMMAND(ID_CUT, OnCut)
	ON_UPDATE_COMMAND_UI(ID_CUT, OnUpdateCut)
	ON_COMMAND(ID_PASTE, OnPaste)
	ON_UPDATE_COMMAND_UI(ID_PASTE, OnUpdatePaste)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_COMMAND(ID_UNDO, OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, OnUpdateUndo)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
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
	ON_BN_CLICKED(ID_PRIOR, OnBnClickedPrior)
	ON_BN_CLICKED(ID_NEXT, OnBnClickedNext)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpEdit message handlers

void CHelpEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	//if ( pFuncs->Modified(IDC_EDIT1) )
    //  DoSave();
	CDialog::OnCancel();
}

void CHelpEdit::OnOK() 
{
	// TODO: Add extra validation here
	if ( pFuncs->Modified(IDC_EDIT1) )
      DoSave();
	CDialog::OnOK();
}

BOOL CHelpEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	TCHAR buf[500];
	char sqlbuf[100];
	// TODO: Add extra initialization here
	CString Lang = GetCurLanguage();
#ifdef _UNICODE
   sprintf(sqlbuf,"select * from HelpText where texttype='%ls' and Lang='%ls' order by iChunk", (LPCTSTR)m_TextType, (LPCTSTR)Lang );
#else
   sprintf(sqlbuf,"select * from HelpText where texttype='%s' and Lang='%s' order by iChunk", (LPCTSTR)m_TextType, (LPCTSTR) Lang );
#endif
   try {
      theSet.Open(dbOpenDynaset,CString(sqlbuf));
      if (!theSet.IsBOF() ) 
         pFuncs->SetRTF(IDC_EDIT1,theSet.m_Text);
      else
         pFuncs->NewRTF(IDC_EDIT1);
      UpdateData(FALSE);
	  m_tabctrl.Set_TabString(pFuncs->GetTabString());
      }
   catch ( CDaoException *e ) {
      e->GetErrorMessage(buf,500);
      alert_box(_T("Error in Database"), buf );
      }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHelpEdit::OnClear() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_EDIT1);	
}

void CHelpEdit::OnUpdateClear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
   pCmdUI->Enable();	
}

void CHelpEdit::OnCopy() 
{
	// TODO: Add your command handler code here
   pFuncs->Copy(IDC_EDIT1);
}

void CHelpEdit::OnUpdateCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnCut() 
{
	// TODO: Add your command handler code here
   pFuncs->Cut(IDC_EDIT1);
}

void CHelpEdit::OnUpdateCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnPaste() 
{
	// TODO: Add your command handler code here
   pFuncs->Paste(IDC_EDIT1);
}

void CHelpEdit::OnUpdatePaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_bModified = TRUE;
}

void CHelpEdit::OnUndo() 
{
	// TODO: Add your command handler code here
   pFuncs->Undo(IDC_EDIT1);
}

void CHelpEdit::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnUpdateEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	
}

void CHelpEdit::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_EDIT1);

}

void CHelpEdit::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnHead() 
{
	// TODO: Add your command handler code here
	   pFuncs->DoHeading(IDC_EDIT1);
}

void CHelpEdit::OnUpdateHead(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnItal() 
{
	// TODO: Add your command handler code here
	   pFuncs->DoItalic(IDC_EDIT1);
}

void CHelpEdit::OnUpdateItal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CHelpEdit::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete pFuncs;
   theSet.Close();
	return CDialog::DestroyWindow();
}

void CHelpEdit::OnUnbold() 
{
	// TODO: Add your command handler code here
	   pFuncs->DoUnBold(IDC_EDIT1);
}

void CHelpEdit::OnUpdateUnbold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnUnheading() 
{
	// TODO: Add your command handler code here
   pFuncs->DoUnHeading(IDC_EDIT1);
}

void CHelpEdit::OnUpdateUnheading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CHelpEdit::OnUnitalic() 
{
	// TODO: Add your command handler code here
	   pFuncs->DoUnItalic(IDC_EDIT1);	
}

void CHelpEdit::OnUpdateUnitalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable();
}

void CHelpEdit::DoSave()
{
 TCHAR errbuf[500];
 try {
   if ( theSet.IsBOF() ) 
      theSet.AddNew();
   else
      theSet.Edit();
   theSet.m_texttype=m_TextType;
   pFuncs->SetTabString(m_tabctrl.Get_TabString());
   theSet.m_Text=pFuncs->GetRTF(IDC_EDIT1);
   theSet.Update();   
   } 
 catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,500);
   alert_box(_T("Error on Database"),errbuf);
   }
}

void CHelpEdit::OnSpell() 
{
	// TODO: Add your command handler code here
	CString str = pFuncs->GetRTF(IDC_EDIT1);

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
		pFuncs->SetRTF(IDC_EDIT1,m_ctrl.GetText());
	}
 Invalidate(FALSE);
}

void CHelpEdit::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();	
}

void CHelpEdit::OnBnClickedPrior()
{
	// TODO: Add your control notification handler code here
	TCHAR errbuf[500];
	if ( theSet.IsBOF() ) {
		MessageBox(_T("No Prior Chunks for this Text"),_T("Message"));
		return;
	}
	pFuncs->SetTabString(m_tabctrl.Get_TabString());
	CString str = pFuncs->GetRTF(IDC_EDIT1);
	try {
	    theSet.Edit();
		theSet.m_Text = str;
		theSet.Update();
		theSet.MovePrev();
		if ( theSet.IsBOF() ) {
			MessageBox(_T("This is First Chunk"),_T("Message"));
			theSet.MoveFirst();
		   }
		pFuncs->SetRTF(IDC_EDIT1,theSet.m_Text);
		m_tabctrl.Set_TabString(pFuncs->GetTabString());
		Invalidate(FALSE);
	}
    catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,500);
   alert_box(_T("Error on Database"),errbuf);
   }

}

void CHelpEdit::OnBnClickedNext()
{
	// TODO: Add your control notification handler code here
	TCHAR errbuf[500];
	if ( theSet.IsEOF() ) {
		MessageBox(_T("No Next Chunks for this Text"),_T("Message"));
		return;
	}
	pFuncs->SetTabString(m_tabctrl.Get_TabString());
	CString str = pFuncs->GetRTF(IDC_EDIT1);
	try {
	    theSet.Edit();
		theSet.m_Text = str;
		theSet.Update();
		theSet.MoveNext();
		if ( theSet.IsEOF() ) {
			theSet.MovePrev();
			MessageBox(_T("No Next Chunks for this Text"),_T("Message"));

		}
		pFuncs->SetRTF(IDC_EDIT1,theSet.m_Text);
		m_tabctrl.Set_TabString(pFuncs->GetTabString());
		Invalidate(FALSE);
	}
    catch ( CDaoException *e ) {
   e->GetErrorMessage(errbuf,500);
   alert_box(_T("Error on Database"),errbuf);
   }

}

void CHelpEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
    CRect r;
	m_tabctrl.GetWindowRect(&(RECT)r);
	if ( point.x >= r.left && point.x <= r.right &&
		   point.y >= r.top && point.y <= r.bottom )
	    m_tabctrl.DoTheClick(point.x-r.left);

	CDialog::OnLButtonDown(nFlags, point);
}
BEGIN_EVENTSINK_MAP(CHelpEdit, CDialog)
	ON_EVENT(CHelpEdit, IDC_TABCTRLCTRL1, 1, DoClickTabctrlctrl1, VTS_I4)
END_EVENTSINK_MAP()

void CHelpEdit::DoClickTabctrlctrl1(long xpos)
{
	// TODO: Add your message handler code here
}
