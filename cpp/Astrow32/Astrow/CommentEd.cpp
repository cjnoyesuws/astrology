// CommentEd.cpp : implementation file
//

#include "stdafx.h"
#include "Astrow.h"
#include "paths.hpp"
#include "astro.h"
#include "useri.h"
#include "rtffuncs.h"
#include "CommentEd.h"
#include <io.h>
#include "errors.fns"
#include ".\commented.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int decompress( char *inbuf, char **outbuf, int in_size, int *out_size, int notabs );
extern int compress_string( char *in_str, char *out_str );
static char tabline[] ="^@|60|5|10|20|30|40|50|";



/////////////////////////////////////////////////////////////////////////////
// CCommentEd dialog


CCommentEd::CCommentEd(CWnd* pParent /*=NULL*/)
	: CDialog(CCommentEd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommentEd)
	m_edit = _T("");
	//}}AFX_DATA_INIT
  pFuncs = new RTFFuncs(this);
}


void CCommentEd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommentEd)
   DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
   DDX_Control(pDX, IDC_TABCTRLCTRL1, m_tabctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommentEd, CDialog)
	//{{AFX_MSG_MAP(CCommentEd)
	ON_BN_CLICKED(IDHELP, OnHelp)
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
	ON_EN_CHANGE(IDC_EDIT, OnEnChangeEdit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommentEd message handlers

void CCommentEd::OnOK() 
{
	// TODO: Add extra validation here
	save();
	CDialog::OnOK();
}

void CCommentEd::OnHelp() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CCommentEd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	load();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CCommentEd::load()
{
 int len, nlen;
 FILE *stream;
 char *bf, *p;

 if ( access( m_fname, 6 ) == -1 ) {
    m_edit = "";
    pFuncs->NewRTF(IDC_EDIT);
	m_tabctrl.Set_TabString(tabline);
    return;
    }
 if ( (stream = freadx_fptr( (char *)(LPCTSTR)m_fname, NULL, 0 )) == NULL ) {
    do_error((char *)(LPCTSTR)m_fname);
    pFuncs->NewRTF(IDC_EDIT);
	m_tabctrl.Set_TabString(tabline);
    return;
    }
 len = (int)filelength(fileno(stream));
 char *rb = new char[len+2];
 if (rb == NULL) {
    do_mem_error(0);
    fclose( stream );
    pFuncs->NewRTF(IDC_EDIT);
	m_tabctrl.Set_TabString(tabline);
    return;
    }
 if ( (len = fread(rb, 1, len, stream)) < len ) {
    do_error( (char *)(LPCTSTR)m_fname );
    fclose( stream );
    pFuncs->NewRTF(IDC_EDIT);
	m_tabctrl.Set_TabString(tabline);
    return;
    }
 rb[len] = '\0';
 nlen = len * 2;
 bf = m_edit.GetBufferSetLength(nlen);
 //bf = (char *)(LPCTSTR)m_edit;
 p = rb;
 decompress( p, (char **)&bf, len, &nlen, 1 );
 delete rb;
 fclose( stream );
 pFuncs->SetRTF(IDC_EDIT,m_edit);
 m_tabctrl.Set_TabString(pFuncs->GetTabString());
 //UpdateData(FALSE);
}


void CCommentEd::save()
{
 NFDB x;
 int len;
 FILE *stream;
 char *bf;

 x.x = *m_fdb;
 x.x.type = -2;
 if ( (stream = fwrite_fptr( (char *)(LPCTSTR)m_fname, &x, 6 )) == NULL ) {
    do_error((char *)(LPCTSTR)m_fname);
    return;
    }
 //UpdateData(TRUE);
 pFuncs->SetTabString(m_tabctrl.Get_TabString());
 m_edit = pFuncs->GetRTF(IDC_EDIT);
 len = 0;
 fwrite(&len, 2, 1, stream );
 fwrite(&len, 2, 1, stream );
 fwrite((const void *)(LPCSTR)m_edit,m_edit.GetLength(),1,stream);
 fclose( stream );
 m_fdb->has_comments = 1;
 return;
}

void CCommentEd::SetFileNameFdb(char *fileName, XPFILE_DB *ptr)
{
 m_fname = fileName;
 m_fdb = ptr;
}

void CCommentEd::OnEditCopy() 
{
	// TODO: Add your command handler code here
	pFuncs->Copy(IDC_EDIT);
}

void CCommentEd::OnEditCut() 
{
	// TODO: Add your command handler code here
	pFuncs->Cut(IDC_EDIT);
}

void CCommentEd::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnEditDelete() 
{
	// TODO: Add your command handler code here
   pFuncs->Clear(IDC_EDIT);
}

void CCommentEd::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnEditPaste() 
{
	// TODO: Add your command handler code here
	pFuncs->Paste(IDC_EDIT);
}

void CCommentEd::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnEditUndo() 
{
	// TODO: Add your command handler code here
	pFuncs->Undo(IDC_EDIT);
}

void CCommentEd::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnItalic() 
{
	// TODO: Add your command handler code here
	pFuncs->DoItalic(IDC_EDIT);
}

void CCommentEd::OnUpdateItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnNormal() 
{
	// TODO: Add your command handler code here
   pFuncs->DoUnHeading(IDC_EDIT);	
}

void CCommentEd::OnUpdateNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnHeading() 
{
	// TODO: Add your command handler code here
	pFuncs->DoHeading(IDC_EDIT);
}

void CCommentEd::OnUpdateHeading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCommentEd::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_EDIT);
}

void CCommentEd::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}


void CCommentEd::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	delete pFuncs;
}
void CCommentEd::OnSpell() 
{
	// TODO: Add your command handler code here
	CString str = pFuncs->GetRTF(IDC_EDIT);

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
		pFuncs->SetRTF(IDC_EDIT,m_ctrl.GetText());
	}
 Invalidate(FALSE);
}

void CCommentEd::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();	
}

void CCommentEd::OnEnChangeEdit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
