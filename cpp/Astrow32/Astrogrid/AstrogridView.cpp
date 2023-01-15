// AstrogridView.cpp : implementation of the CAstrogridView class
//

#include "stdafx.h"
#include "Astrogrid.h"
#include "astro.h"
#include "useri.h"
#include "dataext.h"
#include <afxhtml.h>
#include "AstrogridDoc.h"
#include "AstrogridView.h"
#include "attrib.h"
#include "repstyle.hpp"
#include "convopt.hpp"
#include "convertdata.h"
#include ".\astrogridview.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAstrogridView

IMPLEMENT_DYNCREATE(CAstrogridView, CHtmlView)

BEGIN_MESSAGE_MAP(CAstrogridView, CHtmlView)
	// Standard printing commands
	ON_COMMAND(ID_OPTIONS_TEXT, OnOptionsFileconversionoptions)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_TEXT, OnUpdateOptionsFileconversionoptions)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, OnUpdateFilePrintPreview)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CAstrogridView construction/destruction

CAstrogridView::CAstrogridView()
{
	// TODO: add construction code here

}

CAstrogridView::~CAstrogridView()
{
}

BOOL CAstrogridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

void CAstrogridView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	CAstrogridDoc *pDoc = GetDocument();
	Navigate2(pDoc->Url(),NULL,NULL);
}


// CAstrogridView printing



// CAstrogridView diagnostics

#ifdef _DEBUG
void CAstrogridView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CAstrogridView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CAstrogridDoc* CAstrogridView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstrogridDoc)));
	return (CAstrogridDoc*)m_pDocument;
}
#endif //_DEBUG


// CAstrogridView message handlers

void CAstrogridView::OnOptionsFileconversionoptions()
{
	// TODO: Add your command handler code here
	CConvertData ccd;
	ConvData cd;
	cd.getFromIni();
	ReportStyles rs(GetDC());
	ccd.SetData(cd,rs);
	if ( ccd.DoModal() == IDOK ) {
	   ccd.GetData(cd);
	   cd.saveToIni();
	   }
}

void CAstrogridView::OnUpdateOptionsFileconversionoptions(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAstrogridView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CHtmlView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CAstrogridView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
     if ( zDelta > 0 ) 
	   OnKeyDown(VK_UP,zDelta/120,0);
   else
	   OnKeyDown(VK_DOWN,abs(zDelta)/120,0);
	return CHtmlView::OnMouseWheel(nFlags, zDelta, pt);
}

void CAstrogridView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CHtmlView::OnEndPrinting(pDC, pInfo);
}

void CAstrogridView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView)
{
	// TODO: Add your specialized code here and/or call the base class

	CHtmlView::OnEndPrintPreview(pDC, pInfo, point, pView);
}

void CAstrogridView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CHtmlView::OnBeginPrinting(pDC, pInfo);
}

void CAstrogridView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class

	CHtmlView::OnPrepareDC(pDC, pInfo);
}

BOOL CAstrogridView::OnPreparePrinting(CPrintInfo* pInfo)
{

	// TODO:  call DoPreparePrinting to invoke the Print dialog box

	return CHtmlView::OnPreparePrinting(pInfo);
}

void CAstrogridView::OnFilePrint()
{
	// TODO: Add your command handler code here
	    ExecWB( OLECMDID_PRINT,
               OLECMDEXECOPT_PROMPTUSER,
               NULL,
               NULL);


}

void CAstrogridView::OnUpdateFilePrint(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

void CAstrogridView::OnFilePrintPreview()
{
	// TODO: Add your command handler code here
    ExecWB( OLECMDID_PRINTPREVIEW,
            OLECMDEXECOPT_PROMPTUSER,
            NULL,
            NULL);
}

void CAstrogridView::OnUpdateFilePrintPreview(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable();
}

int CAstrogridView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CHtmlView::OnCreate(lpCreateStruct);
	return 0;
}
