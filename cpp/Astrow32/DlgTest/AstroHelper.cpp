// AstroHelper.cpp : implementation file
//

#include "stdafx.h"
#include "astrow.h"
#include "DHelpTxt.h"
#include "asthlper.hpp"
#include "paths.hpp"
#include "errors.fns"
#include "AstroHelper.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include "fptr.h"
#include "repstyle.hpp"
#include "attrib.h"
#include "tabs.hpp"
#include "sexcodes.hpp"
#include "virttext.hpp"
#include "prtrdrv.hpp"
#include "convopt.hpp"
#include "paths.hpp"
#include "coverdat.hpp"
#include "AstroviewDoc.h"
#include "AstroviewView.h"
#include "asfil2tx.hpp"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Needs more implementation when file viewing and printing are brought into
// mdi app

/////////////////////////////////////////////////////////////////////////////
// CAstroHelper dialog


CAstroHelper::CAstroHelper(CWnd* pParent /*=NULL*/)
	: CDialog(CAstroHelper::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAstroHelper)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  HelpList.read("ASTHLPER.DAT", HELP_F);
  if ( !HelpList.count() )
     return;
  sel = new int[HelpList.count()+1];
  if ( sel == NULL ) {
     do_mem_error( 0 );
     return;
     }
  memset( sel, 0, (HelpList.count()+1) * 2 );
 }


void CAstroHelper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAstroHelper)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAstroHelper, CDialog)
	//{{AFX_MSG_MAP(CAstroHelper)
	ON_BN_CLICKED(ID_AHCONVERT, OnAhconvert)
	ON_BN_CLICKED(ID_AHPRINT, OnAhprint)
	ON_BN_CLICKED(ID_AHVIEW, OnAhview)
	ON_LBN_DBLCLK(ID_AHLIST, OnDblclkAhlist)
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroHelper message handlers

void CAstroHelper::OnAhconvert() 
{
	// TODO: Add your control notification handler code here
 int cnt; 
 CStringArray *list;
 char outfile[100];
 astroFileToText *txt;
 ConvData *pcd;

 CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);
 cnt = pList->GetSelCount()-1;
 if ( !pList->GetSelCount() ) {
    alert_box("", "No Files Selected!");
    return;
    }
 strcpy( outfile, "TEXT.TXT" );
 list = makePrintList();
 txt = new astroFileToText(HELP_F);
 if ( !txt->getSetup(&pcd ) ) {
    delete txt;
    return;
    }
 txt->setFiles( list, 0 );
 txt->doConvert(0);
 delete txt;
 }

void CAstroHelper::OnAhprint() 
{
	// TODO: Add your control notification handler code here
 CStringArray *list;
 CWinApp *app;

 CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);
 
 if ( !pList->GetSelCount() ) {
    alert_box("", "No Files Selected!");
    return;
    }
 int cnt = pList->GetSelCount()-1;
 list = makePrintList();
 app = AfxGetApp();
 ((CAstrowApp *)app)->OpenDocBatchSendCmdWait(HelpTypeFile, (*list)[0], ID_FILE_PRINT, list, cnt );
 return;	
}

void CAstroHelper::OnAhview() 
{
	// TODO: Add your control notification handler code here
	int i;
 FILE_DB fd;
 char buf[250];

 CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);
 i = pList->GetCaretIndex();
 strcpy( buf, set_path( (char *)(LPCSTR) HelpList[i]->getFile(), HELP_F ) );
 HelpList[i]->doGetText();
 AfxGetApp()->OpenDocumentFile(buf);
 
}

void CAstroHelper::OnDblclkAhlist() 
{
	// TODO: Add your control notification handler code here
	CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);	
	if ( pList->GetCaretIndex() < pList->GetCount() )
	   OnAhview();
}

BOOL CAstroHelper::OnInitDialog() 
{
	CDialog::OnInitDialog();
  int i;
  char buf[10];
  AstHelperItem *item=(AstHelperItem *)buf;
 	
	// TODO: Add extra initialization here
  CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);	
  for ( i = 0; item != NULL; i++ ) {
      item = HelpList[i];
      if ( item != NULL )
	     pList->AddString(item->getTitle());
      }
 return TRUE;  // return TRUE unless you set the focus to a control
               // EXCEPTION: OCX Property Pages should return FALSE
}


CStringArray *CAstroHelper::makePrintList()
{
 int i, cnt, *sp;
 CString s;
 static CStringArray ar;


 CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);	
 if ( !pList->GetSelCount() ) {
    alert_box("", "No Files Selected!");
    return( &ar );
    }
 cnt =pList->GetSelCount();
 ar.SetSize(cnt+2,1);
 pList->GetSelItems(pList->GetSelCount(), sel);
 for ( i = 0, cnt = pList->GetSelCount(), sp = sel; i < cnt; i++, sp++ ) {
     HelpList[*sp]->doGetText();
	 s = HelpList[*sp]->getFile();
	 ar[i] = s;
	}
 ar[cnt] = CString("NULL");
 return( &ar  );
}


CStringArray *CAstroHelper::makeTitleList()
{
 int i, cnt, *sp;
 CString s;
 static CStringArray ar;


 CListBox *pList = (CListBox *)GetDlgItem(ID_AHLIST);	
 if ( !pList->GetSelCount() ) {
    alert_box("", "No Files Selected!");
    return( &ar );
    }
 cnt =pList->GetSelCount();
 ar.SetSize(cnt+2,1);
 pList->GetSelItems(pList->GetSelCount(), sel);
 for ( i = 0, cnt = pList->GetSelCount(), sp = sel; i < cnt; i++, sp++ ) {
     s = HelpList[*sp]->getFile();
	 ar[i] = s;
	}
	
 ar[cnt] = "NULL";
 return( &ar  );
}

void CAstroHelper::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CDialog::WinHelp(LOWORD((DWORD)IDD)+HID_BASE_RESOURCE, HELP_CONTEXT);
}
