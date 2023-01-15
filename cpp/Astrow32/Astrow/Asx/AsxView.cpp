// AsxView.cpp : implementation of the CAsxView class
//

#include "stdafx.h"
#include "Asx.h"

#include "AsxDoc.h"
#include "AsxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAsxView

IMPLEMENT_DYNCREATE(CAsxView, CView)

BEGIN_MESSAGE_MAP(CAsxView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CAsxView construction/destruction

CAsxView::CAsxView()
{
	// TODO: add construction code here

}

CAsxView::~CAsxView()
{
}

BOOL CAsxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAsxView drawing

void CAsxView::OnDraw(CDC* /*pDC*/)
{
	CAsxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAsxView printing

BOOL CAsxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAsxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAsxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CAsxView diagnostics

#ifdef _DEBUG
void CAsxView::AssertValid() const
{
	CView::AssertValid();
}

void CAsxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAsxDoc* CAsxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAsxDoc)));
	return (CAsxDoc*)m_pDocument;
}
#endif //_DEBUG


// CAsxView message handlers
