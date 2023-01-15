// ParaEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "rtffuncs.h"
#include "ParaEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParaEdit dialog


CParaEdit::CParaEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CParaEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParaEdit)
	m_text = _T("");
	//}}AFX_DATA_INIT
	pFuncs = new RTFFuncs(this);
}


void CParaEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParaEdit)
	//DDX_Text(pDX, IDC_PTEXT, m_text);
	DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
    DDX_Control(pDX, IDC_TABCTRLCTRL1, m_tabctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParaEdit, CDialog)
	//{{AFX_MSG_MAP(CParaEdit)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_ITALIC, OnItalic)
	ON_UPDATE_COMMAND_UI(ID_ITALIC, OnUpdateItalic)
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, OnUpdateNormal)
	ON_COMMAND(ID_HEADING, OnHeading)
	ON_UPDATE_COMMAND_UI(ID_HEADING, OnUpdateHeading)
	ON_COMMAND(ID_BOLD, OnBold)
	ON_UPDATE_COMMAND_UI(ID_BOLD, OnUpdateBold)
	ON_WM_DESTROY()
	ON_COMMAND(ID_SPELL, OnSpell)
	ON_UPDATE_COMMAND_UI(ID_SPELL, OnUpdateSpell)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParaEdit message handlers


void EditTextBlock::set( CString &t )
{
 buf = t; 
}


void EditTextBlock::preProcess()
{
 char *gpt, *npt, *nbuf;
 int len, i, t, l;

 nsr = 0;
 nTabs = 0;
 memset(tabbuf, 0, sizeof(tabbuf));
 len = buf.GetLength();
 nbuf = new char[len+30];
 for ( gpt = (char *)(LPCTSTR)buf, npt = nbuf, t = 0, i = 0; i < len; i++ ) {
     if ( *gpt == '\1' ) {
	l = *(gpt+1);
	l += 2;
	memcpy( tabbuf, gpt, l );
	tabbuf[l]='\0';
	gpt += l;
	i += l;
	}
     if ( *gpt == '\n' ) {
	*npt++ = '\r';
	*npt++ = *gpt++;
	}
     else if ( *gpt == '\x80' ) {
	stickRet[nsr++] = i+1;
	*npt++ = '\r';
	*npt++ = '\n';
	gpt++;
	}
     else if ( *gpt == '|' ) {
	*npt++ = *gpt++;
	tabs[t++] = *gpt++;
	}
     else
	*npt++ = *gpt++;
     }
 if ( t )
    nTabs = t++;
 *npt++ = '\0';
 *npt++ = '\0';
 for ( i = 0; i < nsr; i++ ) {
     if ( stickRet[i] > 2 )
        stickRet[i] = stickRet[i]-len;
     }   
 buf = nbuf;
 delete nbuf;
}

void EditTextBlock::postProcess()
{
 char *xp, *bp;
 int i, j, t;
 CString x;

 x.GetBuffer(buf.GetLength()+20+strlen(tabbuf));
 x = tabbuf;
 for ( t = 0, xp = (char *)(LPCTSTR)x+x.GetLength(), bp = (char *)(LPCTSTR)buf, i = 0, j = 0; i < buf.GetLength(); i++ ) {
     if (bp[i] == '\t') {
	xp[j++] = ' ';
	}
     else if ( bp[i] == '|' ) {
	xp[j++]=bp[i];
	if ( t < nTabs )
	   xp[j++]=tabs[t++];
	else
	   xp[j++]=(unsigned char)i;
	}
     else if ( bp[i] != '\r' ) {
	xp[j++]=bp[i];
	}
     }
 for ( i = 0; i < nsr; i++ ) {
    switch( stickRet[i] ) {
          case 1:
	       if ( xp[0] == '\n' )
   	          xp[0] = 0x80;
	       break;
          case 2:
	       if ( xp[1] == '\n' )
   	          xp[1] = 0x80;
	       break;
          case -1:
	       if ( xp[j-1] == '\n' )
   	          xp[j-1] = 0x80;
	       break;
          case -2:
	       if ( xp[j-2] == '\n' )
	          xp[j-2] = 0x80;
	       break;
          default :
	        break;
          }
       }   
 xp[j++] = '\0';
 buf = x;
}


void CParaEdit::GetData( CString &t)
{
 etb.set(m_text);
 etb.postProcess();
 t = etb.get();
}

void CParaEdit::SetData( CString &t )
{
 etb.set(t);
 etb.preProcess();
 m_text = etb.get();
 
}
void CParaEdit::OnEditCopy() 
{
	// TODO: Add your command handler code here
	pFuncs->Copy(IDC_PTEXT);
}

void CParaEdit::OnEditCut() 
{
	// TODO: Add your command handler code here
	pFuncs->Cut(IDC_PTEXT);
}

void CParaEdit::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnEditDelete() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_PTEXT);
}

void CParaEdit::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnEditPaste() 
{
	// TODO: Add your command handler code here
	pFuncs->Paste(IDC_PTEXT);
}

void CParaEdit::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnEditUndo() 
{
	// TODO: Add your command handler code here
	pFuncs->Undo(IDC_PTEXT);
}

void CParaEdit::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnItalic() 
{
	// TODO: Add your command handler code here
	pFuncs->DoItalic(IDC_PTEXT);
}

void CParaEdit::OnUpdateItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnNormal() 
{
	// TODO: Add your command handler code here
   pFuncs->DoUnHeading(IDC_PTEXT);	
}

void CParaEdit::OnUpdateNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnHeading() 
{
	// TODO: Add your command handler code here
	pFuncs->DoHeading(IDC_PTEXT);
}

void CParaEdit::OnUpdateHeading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CParaEdit::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_PTEXT);
}

void CParaEdit::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}


void CParaEdit::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete pFuncs;
}

void CParaEdit::OnSpell() 
{
	// TODO: Add your command handler code here
	CString str = pFuncs->GetRTF(IDC_PTEXT);

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
		pFuncs->SetRTF(IDC_PTEXT,m_ctrl.GetText());
	}
 Invalidate(FALSE);
}

void CParaEdit::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();	
}

BOOL CParaEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	pFuncs->SetRTF(IDC_PTEXT,m_text);
	m_tabctrl.Set_TabString(pFuncs->GetTabString());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParaEdit::OnOK() 
{
	// TODO: Add extra validation here
	CString tb =m_tabctrl.Get_TabString();
	pFuncs->SetTabString(tb);
	m_text = pFuncs->GetRTF(IDC_PTEXT);
	CDialog::OnOK();
}

