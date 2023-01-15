// TextConverterView.cpp : implementation of the CTextConverterView class
//

#include "stdafx.h"
#include "TextConverter.h"

#include "TextConverterDoc.h"
#include "TextConverterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextConverterView

IMPLEMENT_DYNCREATE(CTextConverterView, CView)

BEGIN_MESSAGE_MAP(CTextConverterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTextConverterView construction/destruction

CTextConverterView::CTextConverterView()
{
	// TODO: add construction code here

}

CTextConverterView::~CTextConverterView()
{
}

BOOL CTextConverterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTextConverterView drawing

void CTextConverterView::OnDraw(CDC* /*pDC*/)
{
	CTextConverterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CTextConverterView printing

BOOL CTextConverterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTextConverterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTextConverterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTextConverterView diagnostics

#ifdef _DEBUG
void CTextConverterView::AssertValid() const
{
	CView::AssertValid();
}

void CTextConverterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextConverterDoc* CTextConverterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextConverterDoc)));
	return (CTextConverterDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextConverterView message handlers
