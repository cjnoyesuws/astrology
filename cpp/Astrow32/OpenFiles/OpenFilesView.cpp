// OpenFilesView.cpp : implementation of the COpenFilesView class
//

#include "stdafx.h"
#include "OpenFiles.h"

#include "OpenFilesDoc.h"
#include "OpenFilesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenFilesView

IMPLEMENT_DYNCREATE(COpenFilesView, CView)

BEGIN_MESSAGE_MAP(COpenFilesView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// COpenFilesView construction/destruction

COpenFilesView::COpenFilesView()
{
	// TODO: add construction code here

}

COpenFilesView::~COpenFilesView()
{
}

BOOL COpenFilesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenFilesView drawing

void COpenFilesView::OnDraw(CDC* /*pDC*/)
{
	COpenFilesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// COpenFilesView printing

BOOL COpenFilesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenFilesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenFilesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenFilesView diagnostics

#ifdef _DEBUG
void COpenFilesView::AssertValid() const
{
	CView::AssertValid();
}

void COpenFilesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenFilesDoc* COpenFilesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenFilesDoc)));
	return (COpenFilesDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenFilesView message handlers
