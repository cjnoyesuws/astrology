// CoverPage.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "astro.h"
#include "useri.h"
#include "paths.hpp"
#include "coverdat.hpp"
#include "rtffuncs.h"
#include "CoverPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoverPage dialog

static char tabline[] ="^@|60|5|10|20|30|40|50|";

CCoverPage::CCoverPage(CWnd* pParent /*=NULL*/)
	: CDialog(CCoverPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCoverPage)
	m_Subject = _T("");
	m_astrologer = _T("");
	m_comment = _T("");
	m_font = -1;
	m_graphic = _T("");
	m_image = -1;
	m_title = _T("");
	//}}AFX_DATA_INIT
   pFuncs = new RTFFuncs(this);
}


void CCoverPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoverPage)
	DDX_Text(pDX, ID_CP_SUBJECT, m_Subject);
	DDX_Text(pDX, ID_CPASTROLOGER, m_astrologer);
	//DDX_Text(pDX, ID_CPCOMMENT, m_comment);
	DDX_CBIndex(pDX, ID_CPFONT, m_font);
	DDX_Text(pDX, ID_CPGRAPHIC, m_graphic);
	DDX_CBIndex(pDX, ID_CPIMAGE, m_image);
	DDX_Text(pDX, ID_CPTITLE, m_title);
	DDX_Control(pDX, IDC_WSPELLCTRL1, m_ctrl);
	DDX_Control(pDX, IDC_TABCTRLCTRL1, m_tabctrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCoverPage, CDialog)
	//{{AFX_MSG_MAP(CCoverPage)
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
	ON_BN_CLICKED(IDC_SELECT_FILE, OnBnClickedSelectFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoverPage message handlers

void CCoverPage::SetData(CoverPageData &d)
{
 m_Subject = d.getName();
 m_astrologer =	d.getAstName();
 m_comment = d.getComments();
 m_font = d.getFont();
 m_image = d.getImage();
 m_title = d.getTitle();
}

void CCoverPage::GetData(CoverPageData &d)
{
 d.getName() = m_Subject;
 d.getAstName() = m_astrologer;
 d.getComments() = m_comment;
 d.getFont() = m_font;
 d.getImage() = m_image;
 d.getTitle() = m_title;
}


void CCoverPage::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(CCoverPage::IDD, HELP_CONTEXT);
}


void CCoverPage::OnEditCopy() 
{
	// TODO: Add your command handler code here
	pFuncs->Copy(IDC_CPCOMMENT);
}

void CCoverPage::OnEditCut() 
{
	// TODO: Add your command handler code here
	pFuncs->Cut(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnEditDelete() 
{
	// TODO: Add your command handler code here
	pFuncs->Clear(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnEditPaste() 
{
	// TODO: Add your command handler code here
	pFuncs->Paste(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnEditUndo() 
{
	// TODO: Add your command handler code here
	pFuncs->Undo(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnItalic() 
{
	// TODO: Add your command handler code here
	pFuncs->DoItalic(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnNormal() 
{
	// TODO: Add your command handler code here
	pFuncs->DoUnHeading(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnHeading() 
{
	// TODO: Add your command handler code here
	pFuncs->DoHeading(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateHeading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CCoverPage::OnBold() 
{
	// TODO: Add your command handler code here
	pFuncs->DoBold(IDC_CPCOMMENT);
}

void CCoverPage::OnUpdateBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

BOOL CCoverPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	pFuncs->SetRTF(IDC_CPCOMMENT,m_comment);
	UpdateData(FALSE);
    CString tabs = pFuncs->GetTabString();
	if ( tabs.Trim().GetLength()==0 )
		tabs = tabline;
	m_tabctrl.Set_TabString(tabs);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCoverPage::OnDestroy() 
{
	CDialog::OnDestroy();
	delete pFuncs;
	// TODO: Add your message handler code here
	
}

void CCoverPage::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	pFuncs->SetTabString(m_tabctrl.Get_TabString());
	m_comment=pFuncs->GetRTF(IDC_CPCOMMENT);
	CDialog::OnOK();
}

void CCoverPage::OnSpell() 
{
	// TODO: Add your command handler code here
	CString str = pFuncs->GetRTF(IDC_CPCOMMENT);

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
		pFuncs->SetRTF(IDC_CPCOMMENT,m_ctrl.GetText());
	}
 Invalidate(FALSE);
}

void CCoverPage::OnUpdateSpell(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();	
}


void CCoverPage::OnBnClickedSelectFile()
{
	// TODO: Add your control notification handler code here
	char szFilter[] = "Bitmap Files (*.bmp)|*.bmp|JPeg Files (*.jpg)|*.jpg|GIF Files (*.GIF)|*.GIF||";
	CFileDialog fdg(TRUE,".BMP", 0, 0, szFilter, this, 0 );
	if ( fdg.DoModal() == IDOK ) {
		m_graphic = fdg.GetPathName();
		UpdateData(FALSE);
	}

}
