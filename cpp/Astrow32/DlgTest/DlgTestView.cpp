// DlgTestView.cpp : implementation of the CDlgTestView class
//

#include "stdafx.h"
#include "DlgTest.h"
#include "DlgTestDoc.h"
#include "DlgTestView.h"
#include "astro.h"
#include "useri.h"
#include "inifile.hpp"
#include "dataext.h"
#include "asthlper.hpp"
#include "astrohelper.h"
#include "archivedata.h"
#include "setup.hpp"
#include "flags.h"
#include "chartoptions.h"
#include "coverdat.hpp"
#include "coverpage.h"
#include "customize.h"
#include "direc.hpp"
#include "fileeditdlg.h"
#include "filekilldlg.h"
#include "filenamedlg.h"
#include "aspect.h"
#include "orbedit.h"
#include "printoptions.h"
#include "progrdata.h"
#include "qdtopt.hpp"
#include "qdtoptions.h"
#include "rectifydata.h"
#include "returndata.h"
#include "transdata.h"
#include "directories.h"
#include "charcons.h"
#include "database.hpp"
#include "relocscr.h"
#include "dbstruct.h"
#include "database.hpp"
#include "uicvt.fns"
#include "Birthinfo.h"
#include "TransInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView

IMPLEMENT_DYNCREATE(CDlgTestView, CView)

BEGIN_MESSAGE_MAP(CDlgTestView, CView)
	//{{AFX_MSG_MAP(CDlgTestView)
	ON_COMMAND(ID_DIALOGS_ARCHIVEFILES, OnDialogsArchivefiles)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_ARCHIVEFILES, OnUpdateDialogsArchivefiles)
	ON_COMMAND(ID_DIALOGS_COVERPAGEDATA, OnDialogsCoverpagedata)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_COVERPAGEDATA, OnUpdateDialogsCoverpagedata)
	ON_COMMAND(ID_DIALOGS_CUSTOMIZE, OnDialogsCustomize)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_CUSTOMIZE, OnUpdateDialogsCustomize)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_FILEDATAEDIT, OnUpdateDialogsFiledataedit)
	ON_COMMAND(ID_DIALOGS_FILEDATAEDIT, OnDialogsFiledataedit)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_FILENAME, OnUpdateDialogsFilename)
	ON_COMMAND(ID_DIALOGS_FILENAME, OnDialogsFilename)
	ON_COMMAND(ID_DIALOGS_KILLAFILE, OnDialogsKillafile)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_KILLAFILE, OnUpdateDialogsKillafile)
	ON_COMMAND(ID_DIALOGS_OPTIONS, OnDialogsOptions)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_OPTIONS, OnUpdateDialogsOptions)
	ON_COMMAND(ID_DIALOGS_ORBEDIT, OnDialogsOrbedit)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_ORBEDIT, OnUpdateDialogsOrbedit)
	ON_COMMAND(ID_DIALOGS_PRINTOPTIONS, OnDialogsPrintoptions)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_PRINTOPTIONS, OnUpdateDialogsPrintoptions)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_PROGRESSDATA, OnUpdateDialogsProgressdata)
	ON_COMMAND(ID_DIALOGS_PROGRESSDATA, OnDialogsProgressdata)
	ON_COMMAND(ID_DIALOGS_QDTOPTIONS, OnDialogsQdtoptions)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_QDTOPTIONS, OnUpdateDialogsQdtoptions)
	ON_COMMAND(ID_DIALOGS_RECTIFICATION, OnDialogsRectification)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_RECTIFICATION, OnUpdateDialogsRectification)
	ON_COMMAND(ID_DIALOGS_RETURNDATA, OnDialogsReturndata)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_RETURNDATA, OnUpdateDialogsReturndata)
	ON_COMMAND(ID_DIALOGS_TRANSITDATA, OnDialogsTransitdata)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_TRANSITDATA, OnUpdateDialogsTransitdata)
	ON_COMMAND(ID_DIALOGS_DIRECTORIES, OnDialogsDirectories)
	ON_UPDATE_COMMAND_UI(ID_DIALOGS_DIRECTORIES, OnUpdateDialogsDirectories)
	ON_COMMAND(ID_DATARELOCATION, OnDatarelocation)
	ON_UPDATE_COMMAND_UI(ID_DATARELOCATION, OnUpdateDatarelocation)
	ON_COMMAND(ID_DATA_BIRTHINFO, OnDataBirthinfo)
	ON_UPDATE_COMMAND_UI(ID_DATA_BIRTHINFO, OnUpdateDataBirthinfo)
	ON_COMMAND(ID_DATA_TRANSITINFO, OnDataTransitinfo)
	ON_UPDATE_COMMAND_UI(ID_DATA_TRANSITINFO, OnUpdateDataTransitinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


FILE_DB testfiledb = {"Christopher J. Noyes", "Natal", "Christopher J. Noyes; Natal.out",
   NATAL_FILE, 1, 0, 0, 0, 1 };

short house_cusps[13];
/////////////////////////////////////////////////////////////////////////////
// CDlgTestView construction/destruction

CDlgTestView::CDlgTestView()
{
	// TODO: add construction code here

}

CDlgTestView::~CDlgTestView()
{
}

BOOL CDlgTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView drawing

void CDlgTestView::OnDraw(CDC* pDC)
{
	CDlgTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView diagnostics

#ifdef _DEBUG
void CDlgTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDlgTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgTestDoc* CDlgTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgTestDoc)));
	return (CDlgTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgTestView message handlers

void CDlgTestView::OnDialogsArchivefiles() 
{
	// TODO: Add your command handler code here
	CArchiveData cad;
	cad.DoModal();
}

void CDlgTestView::OnUpdateDialogsArchivefiles(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
 pCmdUI->Enable(TRUE);
}

void CDlgTestView::OnDialogsCoverpagedata() 
{
	// TODO: Add your command handler code here
 CoverPageData cpd;
 CCoverPage cp;
 cp.SetData(cpd);
 cp.DoModal();
 cp.GetData(cpd);
}

void CDlgTestView::OnUpdateDialogsCoverpagedata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
pCmdUI->Enable(TRUE);
}

void CDlgTestView::OnDialogsCustomize() 
{
	// TODO: Add your command handler code here
 	
 CCustomize cust;	
 cust.SetData(setup_dat.getBirthOpt().getOpt());
 cust.DoModal();
 cust.GetData(setup_dat.getBirthOpt().getOpt());
}

void CDlgTestView::OnUpdateDialogsCustomize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
pCmdUI->Enable(TRUE);	
}



void CDlgTestView::OnUpdateDialogsFiledataedit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsFiledataedit() 
{
	// TODO: Add your command handler code here
	CFileEditDlg ced;
	ced.SetData(testfiledb);
	ced.DoModal();
	ced.GetData(testfiledb);
}

void CDlgTestView::OnUpdateDialogsFilename(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsFilename() 
{
	// TODO: Add your command handler code here
	CFileNameDlg cnd;
	cnd.SetData(testfiledb);
	cnd.DoModal();
	cnd.GetData(testfiledb);
}


void CDlgTestView::OnDialogsKillafile() 
{
	// TODO: Add your command handler code here
	int status;
	CFileKillDlg ckd;
	ckd.SetData(testfiledb);
	ckd.DoModal();
	ckd.GetData(status);
}

void CDlgTestView::OnUpdateDialogsKillafile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsOptions() 
{
	// TODO: Add your command handler code here
	CChartOptions cust;
    cust.SetData(setup_dat.getBirthOpt().getOpt());
    cust.DoModal();
    cust.GetData(setup_dat.getBirthOpt().getOpt());
}

void CDlgTestView::OnUpdateDialogsOptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsOrbedit() 
{
	// TODO: Add your command handler code here
	COrbEdit coe;
	coe.DoModal();
}

void CDlgTestView::OnUpdateDialogsOrbedit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsPrintoptions() 
{
	// TODO: Add your command handler code here
	CPrintOptions cpo;
	cpo.DoModal();
}

void CDlgTestView::OnUpdateDialogsPrintoptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnUpdateDialogsProgressdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsProgressdata() 
{
	// TODO: Add your command handler code here
PROGR_DATA pd;
memset(&pd, 0, sizeof(PROGR_DATA));
CProgrData cpd;
cpd.SetData(pd);
cpd.DoModal();
cpd.GetData(pd);
}

void CDlgTestView::OnDialogsQdtoptions() 
{
	// TODO: Add your command handler code here
	QdtData qd;
	CQdtOptions cqo;
	cqo.SetData(qd);
	cqo.DoModal();
	cqo.GetData(qd);
	
}

void CDlgTestView::OnUpdateDialogsQdtoptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsRectification() 
{
	// TODO: Add your command handler code here
RECT_DATA pd;
TIM b = {6,45,0};
memset(&pd, 0, sizeof(RECT_DATA));
CRectifyData cpd;
cpd.SetData(pd, b, 0);
cpd.DoModal();
cpd.GetData(pd);
	
}

void CDlgTestView::OnUpdateDialogsRectification(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsReturndata() 
{
	// TODO: Add your command handler code here
RETURN_DATA pd;
memset(&pd, 0, sizeof(RETURN_DATA));
CReturnData cpd;
cpd.SetData(pd);
cpd.DoModal();
cpd.GetData(pd);
	
}

void CDlgTestView::OnUpdateDialogsReturndata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDialogsTransitdata() 
{
	// TODO: Add your command handler code here
TRANS_DATA pd;
memset(&pd, 0, sizeof(TRANS_DATA));
CTransData cpd;
cpd.SetData(pd);
cpd.DoModal();
cpd.GetData(pd);
}

void CDlgTestView::OnUpdateDialogsTransitdata(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}



void CDlgTestView::OnDialogsDirectories() 
{
	// TODO: Add your command handler code here
	CDirectories cdd;
	cdd.SetData(theDirectories);
	if ( cdd.DoModal() == IDOK ) {
	   cdd.GetData(theDirectories);
	   theDirectories.saveToIni();
	   }
	
}

void CDlgTestView::OnUpdateDialogsDirectories(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}

void CDlgTestView::OnDatarelocation() 
{
	// TODO: Add your command handler code here
	LOC_DB thelocdb;
	memset(&thelocdb,0,sizeof(LOC_DB));
	CRelocScr crs;
	crs.SetData(thelocdb);
	crs.DoModal();
	crs.GetData(thelocdb);
}

void CDlgTestView::OnUpdateDatarelocation(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);	
}


// needed functions for birth and loction screens 

void LocDatabase::buildDataKey( void *buf )
{
 LOC_DB *lp, loc;

 memset( &loc, 0, sizeof( LOC_DB ) );
 lp = cvt_dsk_2_nlocdb( &loc, (struct D_LOC_DB *)buf );
 make_key( lp->country, lp->state, lp->location );
 strcpy( id.key, db_key );
}

void BirthDatabase::buildDataKey( void *buf )
{
 BIRTH_DB *bp, nb;

 memset( &nb, 0, sizeof( BIRTH_DB ) );
 bp = cvt_dsk_2_nbirthdb( &nb, (union DBR *)buf, NULL );
 strcpy( id.key, bp->name );
}

void CDlgTestView::OnDataBirthinfo() 
{
	// TODO: Add your command handler code here
	BIRTH_DB db;
	RECT_DATA rd;
	memset(&db,0,sizeof(BIRTH_DB));
	memset(&rd,0,sizeof(RECT_DATA));
	CBirthInfo cbi;
	cbi.SetData(db,rd);
	cbi.DoModal();
	cbi.GetData(db,rd);
}

void CDlgTestView::OnUpdateDataBirthinfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);		
}

void CDlgTestView::OnDataTransitinfo() 
{
	// TODO: Add your command handler code here
	BIRTH_DB db;
	memset(&db,0,sizeof(BIRTH_DB));
	CTransInfo cbi;
	cbi.SetData(db);
	cbi.DoModal();
	cbi.GetData(db);
}

void CDlgTestView::OnUpdateDataTransitinfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);		
}
