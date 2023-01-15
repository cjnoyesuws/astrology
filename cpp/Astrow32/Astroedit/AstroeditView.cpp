// AstroeditView.cpp : implementation of the CAstroeditView class
//

#include "stdafx.h"
#include "afxrich.h"
#include "Astroedit.h"
#include "attrib.h"
#include "inifile.hpp"
#include "repstyle.hpp"
#include "reportstyles.h"
#include "pseudostyle.h"
#include "convopt.hpp"
#include "convertData.h"
#include "AstroeditDoc.h"
#include "AstroeditView.h"
#include "findtext.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstroeditView
									   
IMPLEMENT_DYNCREATE(CAstroeditView, CRichEditView)

BEGIN_MESSAGE_MAP(CAstroeditView, CRichEditView)
	//{{AFX_MSG_MAP(CAstroeditView)
	ON_COMMAND(ID_OPTIONS_TEXTFILECONVERSIONS, OnOptionsTextfileconversions)
	ON_UPDATE_COMMAND_UI(ID_EDIT_BOLDTEXT, OnUpdateEditBoldtext)
	ON_COMMAND(ID_EDIT_BOLDTEXT, OnEditBoldtext)
	ON_UPDATE_COMMAND_UI(ID_EDIT_HEADLINETEXT, OnUpdateEditHeadlinetext)
	ON_COMMAND(ID_EDIT_HEADLINETEXT, OnEditHeadlinetext)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ITALICUNDERSCORETEXT, OnUpdateEditItalicunderscoretext)
	ON_COMMAND(ID_EDIT_ITALICUNDERSCORETEXT, OnEditItalicunderscoretext)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REGULARTEXT, OnUpdateEditRegulartext)
	ON_COMMAND(ID_EDIT_REGULARTEXT, OnEditRegulartext)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_FINDCONT, OnEditFindcont)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstroeditView construction/destruction

CAstroeditView::CAstroeditView()
{
	// TODO: add construction code here
styles = NULL;
textToFind = "";
matchCase = FALSE;
wholeWord = FALSE;
}

CAstroeditView::~CAstroeditView()
{
if ( styles != NULL ) 
   delete styles;
}

BOOL CAstroeditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAstroeditView drawing

void CAstroeditView::OnDraw(CDC* pDC)
{
	CAstroeditDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAstroeditView printing

BOOL CAstroeditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->m_nCurPage = 2;
	return DoPreparePrinting(pInfo);
}

void CAstroeditView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAstroeditView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAstroeditView diagnostics

#ifdef _DEBUG
void CAstroeditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CAstroeditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CAstroeditDoc* CAstroeditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstroeditDoc)));
	return (CAstroeditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstroeditView message handlers

void CAstroeditView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
CHARFORMAT cf;
CDC *dc;

Invalidate(TRUE);
dc = GetDC();
styles = new ReportStyles(dc);	
SetupCharFormat(cf,styles->getRegColor(),styles->getRegFont());
GetRichEditCtrl()->SetDefaultCharFormat(cf);
ReleaseDC(dc);
}

void CAstroeditView::OnOptionsTextfileconversions() 
{
	// TODO: Add your command handler code here
CDC *dc = GetDC();	
ReportStyles rs(dc);
rs.getFromIni(ConvData_SEC);
ConvData cd;
cd.getFromIni();
CConvertData cdd(this);
cdd.SetData(cd,rs);
if ( cdd.DoModal() == IDOK ) {
   cdd.GetData(cd);
   if ( styles != NULL )
	  styles->Update(rs);
   rs.saveToIni(ConvData_SEC);
   cd.saveToIni();
   }
}

void CAstroeditView::OnUpdateEditBoldtext(CCmdUI* pCmdUI) 
{
	
	// TODO: Add your command update UI handler code here
	CRichEditView::OnUpdateNeedSel(pCmdUI);
	
}	   


void CAstroeditView::OnEditBoldtext() 
{
	// TODO: Add your command handler code here
	CHARFORMAT cf;
	PARAFORMAT pf;
	cf = GetCharFormatSelection();
	pf = GetParaFormatSelection();   
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_LEFT;
	SetupCharFormat(cf,styles->getBoldColor(),styles->getBoldFont());
	SetParaFormat(pf);
	SetCharFormat(cf);	
}

void CAstroeditView::OnUpdateEditHeadlinetext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CRichEditView::OnUpdateNeedSel(pCmdUI);
}

void CAstroeditView::OnEditHeadlinetext() 
{
	// TODO: Add your command handler code here
	CHARFORMAT cf;
	PARAFORMAT pf;
	cf = GetCharFormatSelection();
	pf = GetParaFormatSelection();   
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_CENTER;
	SetupCharFormat(cf,styles->getHeadColor(),styles->getHeadFont());
	SetParaFormat(pf);
	SetCharFormat(cf);
}

void CAstroeditView::OnUpdateEditItalicunderscoretext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CRichEditView::OnUpdateNeedSel(pCmdUI);
	
}

void CAstroeditView::OnEditItalicunderscoretext() 
{
	// TODO: Add your command handler code here
	CHARFORMAT cf;
	PARAFORMAT pf;
	cf = GetCharFormatSelection();
	pf = GetParaFormatSelection();   
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_LEFT;
	SetupCharFormat(cf,styles->getItalColor(),styles->getItalFont());
	SetParaFormat(pf);
	SetCharFormat(cf);
}

void CAstroeditView::OnUpdateEditRegulartext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CRichEditView::OnUpdateNeedSel(pCmdUI);
}

void CAstroeditView::OnEditRegulartext() 
{
	// TODO: Add your command handler code here
	CHARFORMAT cf;
	PARAFORMAT pf;
	cf = GetCharFormatSelection();
	pf = GetParaFormatSelection();   
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_LEFT;
	SetupCharFormat(cf,styles->getRegColor(),styles->getRegFont());
	SetParaFormat(pf);
	SetCharFormat(cf);
}


void CAstroeditView::SetupCharFormat(CHARFORMAT &cf, COLORREF &cr, LOGFONT *lf)
{
 float f;
	
 cf.dwMask=CFM_BOLD|CFM_COLOR|CFM_FACE|CFM_ITALIC|CFM_SIZE|CFM_UNDERLINE;
 cf.crTextColor = cr;
 strcpy( cf.szFaceName,lf->lfFaceName);
 CDC *dc = GetDC();
 f =(float)dc->GetDeviceCaps(LOGPIXELSY) / 72.0;
 cf.yHeight = (long)((float)lf->lfHeight/f) * 20;
 ReleaseDC(dc);
 cf.bCharSet = lf->lfCharSet;
 cf.bPitchAndFamily = lf->lfPitchAndFamily;
 cf.dwEffects = 0;
 if ( lf->lfWeight >= FW_BOLD )
	cf.dwEffects = CFE_BOLD;
 if ( lf->lfItalic )
	cf.dwEffects |= CFE_ITALIC;
 if ( lf->lfUnderline )
	cf.dwEffects |= CFE_UNDERLINE;
}


void CAstroeditView::OnEditFind() 
{
	// TODO: Add your command handler code here
	
	CFindText cfd;
	cfd.SetData(textToFind,matchCase,wholeWord);
	if ( cfd.DoModal() == IDOK ) {
	   cfd.GetData(textToFind,matchCase,wholeWord );
	   if ( !FindText(textToFind,matchCase,wholeWord) ) {
	   	  CString b;
	      b.Format(	"  Can\'t Find Text \"%s\"!  ", (LPCTSTR)textToFind);
		  MessageBox(b, "Find Text" );
		  }
	   }
}

void CAstroeditView::OnEditFindcont() 
{
	// TODO: Add your command handler code here
		CFindText cfd;
	if ( textToFind.GetLength() == 0 )
	   OnEditFind(); 
	if ( !FindText(textToFind,matchCase,wholeWord) ) {
	   CString b;
	   b.Format(	"  Can\'t Find Text \"%s\"!  ", (LPCTSTR)textToFind);
	   MessageBox(b, "Find Text" );	  
	   }
		
}
