// EZAstrowView.cpp : implementation of the CEZAstrowView class
//

#include "stdafx.h"
#include "EZAstrow.h"

#include "EZAstrowDoc.h"
#include "EZAstrowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEZAstrowView

IMPLEMENT_DYNCREATE(CEZAstrowView, CFormView)

BEGIN_MESSAGE_MAP(CEZAstrowView, CFormView)
END_MESSAGE_MAP()

// CEZAstrowView construction/destruction

CEZAstrowView::CEZAstrowView()
	: CFormView(CEZAstrowView::IDD)
{
	// TODO: add construction code here

}

CEZAstrowView::~CEZAstrowView()
{
}

void CEZAstrowView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CEZAstrowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CEZAstrowView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
}


// CEZAstrowView diagnostics

#ifdef _DEBUG
void CEZAstrowView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEZAstrowView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEZAstrowDoc* CEZAstrowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEZAstrowDoc)));
	return (CEZAstrowDoc*)m_pDocument;
}
#endif //_DEBUG


// CEZAstrowView message handlers
