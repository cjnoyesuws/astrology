// astrpgraphView.cpp : implementation of the CAstrpgraphView class
//

#include "stdafx.h"
#include "astrpgraph.h"

#include "astrpgraphDoc.h"
#include "astrpgraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphView

IMPLEMENT_DYNCREATE(CAstrpgraphView, CView)

BEGIN_MESSAGE_MAP(CAstrpgraphView, CView)
	//{{AFX_MSG_MAP(CAstrpgraphView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphView construction/destruction

CAstrpgraphView::CAstrpgraphView()
{
	// TODO: add construction code here

}

CAstrpgraphView::~CAstrpgraphView()
{
}

BOOL CAstrpgraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphView drawing

void CAstrpgraphView::OnDraw(CDC* pDC)
{
	CAstrpgraphDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphView printing

BOOL CAstrpgraphView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAstrpgraphView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAstrpgraphView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphView diagnostics

#ifdef _DEBUG
void CAstrpgraphView::AssertValid() const
{
	CView::AssertValid();
}

void CAstrpgraphView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAstrpgraphDoc* CAstrpgraphView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAstrpgraphDoc)));
	return (CAstrpgraphDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphView message handlers
