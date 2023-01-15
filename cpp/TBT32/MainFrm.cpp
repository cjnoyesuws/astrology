// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TBT32.h"
#include <afxcmn.h>
#include "MainFrm.h"
#include "setup.h"
#include "fileary.hpp"
#include "symbol.hpp"
#include "textbloc.hpp"
#include "strtransform.h"
#include "texttypeary.hpp"
#include "rtffuncs.h"
#include "dregtext1.h"
#include "dreporttext1.h"
#include "dhelptxt1.h"
#include "daspecttext1.h"
#include "progress.h"
#include "importhelp.h"
#include "importRegText.h"
#include "importAspText.h"
#include "importreporttext.h"
#include "reportedit.h"
#include "regtextedit.h"
#include "aspTextEdit.h"
#include "helpedit.h"
#include "fileSelector.h"
#include "selectTextItem.h"
#include "arrayedit.h"
#include "newlanguage.h"
#include "setlanguage.h"
#include "directoryselect.h"
#include "basedbexport.h"
#include "regdbexport.h"
#include "aspdbexport.h"
#include "hlpdbexport.h"
#include "reptdbexport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_ASPECTTEXT, OnAspecttext)
	ON_COMMAND(ID_IMPORT_IMPORTAHELPFILE, OnImportImportahelpfile)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTAHELPFILE, OnUpdateImportImportahelpfile)
	ON_COMMAND(ID_IMPORT_IMPORTASPECTTEXT, OnImportImportaspecttext)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTASPECTTEXT, OnUpdateImportImportaspecttext)
	ON_COMMAND(ID_IMPORT_IMPORTPLANETHOUSETEXT, OnImportImportplanethousetext)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTPLANETHOUSETEXT, OnUpdateImportImportplanethousetext)
	ON_COMMAND(ID_IMPORT_IMPORTREPORTTEXT, OnImportImportreporttext)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTREPORTTEXT, OnUpdateImportImportreporttext)
	ON_COMMAND(ID_REGULARTXT, OnRegulartxt)
	ON_UPDATE_COMMAND_UI(ID_REGULARTXT, OnUpdateRegulartxt)
	ON_COMMAND(ID_HELPTXT, OnHelptxt)
	ON_UPDATE_COMMAND_UI(ID_HELPTXT, OnUpdateHelptxt)
	ON_COMMAND(ID_EDITTEXTSOURCES_REPORTTEXTSOURCES, OnEdittextsourcesReporttextsources)
	ON_UPDATE_COMMAND_UI(ID_EDITTEXTSOURCES_REPORTTEXTSOURCES, OnUpdateEdittextsourcesReporttextsources)
	ON_COMMAND(ID_OPTIONS_SETUP, OnOptionsSetup)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SETUP, OnUpdateOptionsSetup)
	ON_COMMAND(ID_ARRAYTEXT, OnArraytext)
	ON_UPDATE_COMMAND_UI(ID_ARRAYTEXT, OnUpdateArraytext)
	ON_COMMAND(ID_ADDLANGUAGE, OnAddlanguage)
	ON_UPDATE_COMMAND_UI(ID_ADDLANGUAGE, OnUpdateAddlanguage)
	ON_COMMAND(ID_SET_CURR_LANGUAGE, OnSetLanguage)
	ON_UPDATE_COMMAND_UI(ID_SET_CURR_LANGUAGE, OnUpdateSetLanguage)
	//}}AFX_MSG_MAP
	
	ON_COMMAND(ID_EXPORT_EXPORTASPECTTEXT, OnExportExportaspecttext)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_EXPORTASPECTTEXT, OnUpdateExportExportaspecttext)
	ON_COMMAND(ID_EXPORT_EXPORTHELP, OnExportExporthelp)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_EXPORTHELP, OnUpdateExportExporthelp)
	ON_COMMAND(ID_EXPORT_EXPORTREGULARTEXT, OnExportExportregulartext)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_EXPORTREGULARTEXT, OnUpdateExportExportregulartext)
	ON_COMMAND(ID_EXPORT_EXPORTREPORTS, OnExportExportreports)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_EXPORTREPORTS, OnUpdateExportExportreports)
	ON_COMMAND(ID_IMPORT_IMPORTEXPORTEDASPECTFILE, OnImportImportexportedaspectfile)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTEXPORTEDASPECTFILE, OnUpdateImportImportexportedaspectfile)
	ON_COMMAND(ID_IMPORT_IMPORTEXPORTEDHELPFILE, OnImportImportexportedhelpfile)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTEXPORTEDHELPFILE, OnUpdateImportImportexportedhelpfile)
	ON_COMMAND(ID_IMPORT_IMPORTEXPORTEDPLANET, OnImportImportexportedplanet)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTEXPORTEDPLANET, OnUpdateImportImportexportedplanet)
	ON_COMMAND(ID_IMPORT_IMPORTEXPORTEDREPORTFILE, OnImportImportexportedreportfile)
	ON_UPDATE_COMMAND_UI(ID_IMPORT_IMPORTEXPORTEDREPORTFILE, OnUpdateImportImportexportedreportfile)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnAspecttext() 
{
	// TODO: Add your command handler code here
	char buf1[20];
	CSelectTextItem it(this);
	it.m_type=3;
	it.m_ary=0;
	if ( it.DoModal() != IDOK )
		return;
	CString str = it.m_strItem;
    strcpy( buf1, pATextTypes->toTextType( str ));
	CAspTextEdit asp(this);
	asp.m_TextType = buf1;
	asp.DoModal();
	
}

void CMainFrame::OnUpdateAspecttext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable();

}

void CMainFrame::OnImportImportahelpfile() 
{
	// TODO: Add your command handler code here
	CProgress prog(this);
	CDirectorySelect sel(TRUE);
	CString dir;
	if ( sel.DoModal() == IDOK )
		dir = sel.GetDirectory();
	else
		dir = GetSrcDir();
	ImportHelp *imp = new ImportHelp(&prog,dir,FALSE);
	imp->Process();
	delete imp;
}

void CMainFrame::OnUpdateImportImportahelpfile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->Enable();

}

void CMainFrame::OnImportImportaspecttext() 
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[25];
	CFileSelector sel(this);
	sel.m_type=3;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	for ( int i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    CString str = sel.m_FileAry[i];
		if ( str.GetLength()==0)
			continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
		strcpy(buf1, pFileList->toFileName( str) );
        strcpy(buf2, pFileList->toTextType(buf1) );
		ImportAspText *imp = new ImportAspText(buf1,buf2, &prog, sel.m_import_dir);
	    imp->Process();
	    delete imp;
		}
}

void CMainFrame::OnUpdateImportImportaspecttext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnImportImportplanethousetext() 
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[25];
	CFileSelector sel(this);
	sel.m_type=2;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	for ( int i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    CString str = sel.m_FileAry[i];
	    if ( str.GetLength()==0)
		   continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
	    strcpy(buf1, pFileList->toFileName(str) );
        strcpy(buf2, pFileList->toTextType(buf1) );
		ImportRegText *imp = new ImportRegText(buf1,buf2, &prog, sel.m_import_dir);
	    imp->Process();
	    delete imp;
		}
}

void CMainFrame::OnUpdateImportImportplanethousetext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnImportImportreporttext() 
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[50];
	CFileSelector sel(this);
	sel.m_type=1;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	ImportReportText *imp;
	CString str;
	int i = 0;
	for ( i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    str = sel.m_FileAry[i];
	    if (str.GetLength()==0)
		   continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
	    strcpy(buf1, pFileList->toFileName((CString &)str) );
        strcpy(buf2, pFileList->toTextType(buf1) );
		imp = new ImportReportText(buf1,buf2,&prog, sel.m_import_dir);
		imp->Process();
	    delete imp;
		}
}

void CMainFrame::OnUpdateImportImportreporttext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnRegulartxt() 
{
	// TODO: Add your command handler code here
	char buf1[20];
	CSelectTextItem it(this);
	it.m_type=2;
	it.m_ary=0;
	if ( it.DoModal() != IDOK )
		return;
	CString str = it.m_strItem;
    strcpy( buf1, pATextTypes->toTextType(str ));
	CRegTextEdit reg(this);
	reg.m_TextType = buf1;
	reg.DoModal();

}

void CMainFrame::OnUpdateRegulartxt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  pCmdUI->Enable();	
}


void CMainFrame::OnHelptxt() 
{
	// TODO: Add your command handler code here
	int ret;
	char buf1[20];
    CString str;
	do {
      CSelectTextItem *it = new CSelectTextItem(this);
	  it->m_type=0;
	  it->m_ary=0;
	  ret = it->DoModal();
	  str = it->m_strItem;
	  delete it;      
	  if ( ret == IDOK ) {
		 strcpy( buf1, pATextTypes->toTextType( str ));
		 CHelpEdit *hlp = new CHelpEdit(this);
		 hlp->m_TextType = buf1;
		 ret = hlp->DoModal();
		 delete hlp;
		}
	} while ( ret == IDOK );
}

void CMainFrame::OnUpdateHelptxt(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnEdittextsourcesReporttextsources() 
{
	// TODO: Add your command handler code here
	char buf1[20];
	CSelectTextItem it(this);
	it.m_type=1;
	it.m_ary= 0;
	if ( it.DoModal() != IDOK )
		return;
	CString str = it.m_strItem;
    strcpy( buf1, pATextTypes->toTextType(str ) );
	CReportEdit rep(this);
	rep.m_TextType = buf1;
	rep.DoModal();

}

void CMainFrame::OnUpdateEdittextsourcesReporttextsources(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnOptionsSetup() 
{
	// TODO: Add your command handler code here
	CSetup st;
   st.DoModal();
}

void CMainFrame::OnUpdateOptionsSetup(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnArraytext()
{
	// TODO: Add your command handler code here
	char buf1[50];
	CSelectTextItem it(this);
	it.m_type=1;
	it.m_ary = 1;
	if ( it.DoModal() != IDOK )
		return;
	CString str = it.m_strItem;
    strcpy( buf1, pATextTypes->toTextType( str ) );
    CArrayEdit ed(this);
	ed.SetTextType(buf1);
	strcpy( buf1, pATextTypes->toSymType( CString(buf1), 1 ) );
	ed.SetSymTypes(buf1);
    ed.DoModal();
}

void CMainFrame::OnUpdateArraytext(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnAddlanguage()
{
	// TODO: Add your command handler code here
	CNewLanguage lang(this);
	lang.DoModal();

}

void CMainFrame::OnUpdateAddlanguage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnSetLanguage()
{
	// TODO: Add your command handler code here
	CSetLanguage setlang(this);
	setlang.DoModal();
}

void CMainFrame::OnUpdateSetLanguage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnExportExportaspecttext()
{
	// TODO: Add your command handler code here
	CDirectorySelect sel(FALSE);
	CString Lang = "";
#ifdef _UNICODE
    Lang = GetCurLanguage();
#endif
	if ( sel.DoModal() == IDOK ) {
	  CProgress prog(this);
	  CAspDbExport exp(sel.GetDirectory(),&prog,pATextTypes->TypeCount(3),Lang);
	  exp.Process();
	}
}

void CMainFrame::OnUpdateExportExportaspecttext(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnExportExporthelp()
{
	// TODO: Add your command handler code here
	CDirectorySelect sel(FALSE);
	CString Lang = "";
#ifdef _UNICODE
    Lang = GetCurLanguage();
#endif	
	if ( sel.DoModal() == IDOK ) {
	  CProgress prog(this);
	  CHlpDbExport exp(sel.GetDirectory(),&prog,pATextTypes->TypeCount(0),Lang);
	  exp.Process();
	}
}

void CMainFrame::OnUpdateExportExporthelp(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnExportExportregulartext()
{
	// TODO: Add your command handler code here
	CDirectorySelect sel(FALSE);
	CString Lang = "";
#ifdef _UNICODE
    Lang = GetCurLanguage();
#endif
	if ( sel.DoModal() == IDOK ) {
	  CProgress prog(this);
	  CRegDbExport exp(sel.GetDirectory(),&prog,pATextTypes->TypeCount(2),Lang);
	  exp.Process();
	}
}

void CMainFrame::OnUpdateExportExportregulartext(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnExportExportreports()
{
	// TODO: Add your command handler code here
	CDirectorySelect sel(FALSE);
	CString Lang = "";
#ifdef _UNICODE
    Lang = GetCurLanguage();
#endif
	if ( sel.DoModal() == IDOK ) {
	  CProgress prog(this);
	  CReptDbExport exp(sel.GetDirectory(),&prog,pATextTypes->TypeCount(1),Lang);
	  exp.Process();
	}
}

void CMainFrame::OnUpdateExportExportreports(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CMainFrame::OnImportImportexportedaspectfile()
{
	// TODO: Add your command handler code here
    char buf1[25], buf2[25], buf3[25];;
	CFileSelector sel(this);
	sel.m_type=3;
	sel.m_bExport = TRUE;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	for ( int i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    CString str = sel.m_FileAry[i];
		if ( str.GetLength()==0)
			continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
		memset(buf3,0,25);
		strcpy(buf1, pFileList->toFileName( str) );
        strcpy(buf2, buf1 );
		sprintf(buf3,"3-%s", buf1);
		ImportAspText *imp = new ImportAspText(buf3,buf2, &prog, sel.m_import_dir);
	    imp->Process();
	    delete imp;
		}
}

void CMainFrame::OnUpdateImportImportexportedaspectfile(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
   pCmdUI->Enable();
}

void CMainFrame::OnImportImportexportedhelpfile()
{
	// TODO: Add your command handler code here
	CProgress prog(this);
	CDirectorySelect sel(TRUE);
	CString dir;
	if ( sel.DoModal() == IDOK )
		dir = sel.GetDirectory();
	else
		dir = GetSrcDir();
	ImportHelp *imp = new ImportHelp(&prog,dir,TRUE);
	imp->Process();
	delete imp;
}

void CMainFrame::OnUpdateImportImportexportedhelpfile(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
   pCmdUI->Enable();
}

void CMainFrame::OnImportImportexportedplanet()
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[25], buf3[25];
	CFileSelector sel(this);
	sel.m_bExport = TRUE;
	sel.m_type=2;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	for ( int i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    CString str = sel.m_FileAry[i];
	    if ( str.GetLength()==0)
		   continue;
		memset(buf1,0,25);
		memset(buf2,0,25);
		memset(buf3,0,25);
	    strcpy(buf1, pFileList->toFileName(str) );
        strcpy(buf2, buf1);
		sprintf(buf3,"2-%s", buf1);
		ImportRegText *imp = new ImportRegText(buf3,buf2, &prog, sel.m_import_dir);
	    imp->Process();
	    delete imp;
		}
}

void CMainFrame::OnUpdateImportImportexportedplanet(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
   pCmdUI->Enable();
}

void CMainFrame::OnImportImportexportedreportfile()
{
	// TODO: Add your command handler code here
	char buf1[25], buf2[50], buf3[50];
	CFileSelector sel(this);
	sel.m_bExport = TRUE;
	sel.m_type=1;
	if ( sel.DoModal() != IDOK )
		return;
	CProgress prog(this);
	ImportReportText *imp;
	CString str;
	int i = 0;
	for ( i = 0; i < sel.m_FileAry.GetSize(); i++ ) {
	    str = sel.m_FileAry[i];
	    if (str.GetLength()==0)
		   continue;
		memset(buf1,0,25);
		memset(buf2,0,50);
		memset(buf3,0,50);
	    strcpy(buf1, pFileList->toFileName((CString &)str) );
        strcpy(buf2, buf1);
		sprintf(buf3,"1-%s",buf1);
		imp = new ImportReportText(buf3,buf2,&prog, sel.m_import_dir);
		imp->Process();
	    delete imp;
		}
}

void CMainFrame::OnUpdateImportImportexportedreportfile(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
   pCmdUI->Enable();
}
