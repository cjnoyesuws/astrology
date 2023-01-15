// AstrowView.cpp : implementation of the CAstrowView class
//

#include "stdafx.h"
#include "Astrow.h"

#include "AstrowDoc.h"
#include "AstrowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrowView

IMPLEMENT_DYNCREATE(CAstrowView, CView)

BEGIN_MESSAGE_MAP(CAstrowView, CView)
	//{{AFX_MSG_MAP(CAstrowView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrowView construction/destruction

CAstrowView::CAstrowView()
{
	// TODO: add construction code here

}

CAstrowView::~CAstrowView()
{
}

BOOL CAstrowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowView drawing

void CAstrowView::OnDraw(CDC* pDC)
{
	CAstrowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowView printing

BOOL CAstrowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAstrowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAstrowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowView diagnostics

#ifdef _DEBUG
void CAstrowView::AssertValid() const
{
	CView::AssertValid();
}

void CAstrowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAstrowDoc* CAstrowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstrowDoc)));
	return (CAstrowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrowView message handlers




