// WizardView.cpp : implementation of the CWizardView class
//

#include "stdafx.h"
#include "Wizard.h"

#include "WizardDoc.h"
#include "WizardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizardView

IMPLEMENT_DYNCREATE(CWizardView, CView)

BEGIN_MESSAGE_MAP(CWizardView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CWizardView construction/destruction

CWizardView::CWizardView()
{
	// TODO: add construction code here

}

CWizardView::~CWizardView()
{
}

BOOL CWizardView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CWizardView drawing

void CWizardView::OnDraw(CDC* /*pDC*/)
{
	CWizardDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CWizardView printing

BOOL CWizardView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWizardView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWizardView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CWizardView diagnostics

#ifdef _DEBUG
void CWizardView::AssertValid() const
{
	CView::AssertValid();
}

void CWizardView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWizardDoc* CWizardView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWizardDoc)));
	return (CWizardDoc*)m_pDocument;
}
#endif //_DEBUG


// CWizardView message handlers
