// ChartEditView.cpp : implementation of the CChartEditView class
//

#include "stdafx.h"
#include "ChartEdit.h"

#include "ChartEditDoc.h"
#include "CntrItem.h"
#include "ChartEditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartEditView

IMPLEMENT_DYNCREATE(CChartEditView, CRichEditView)

BEGIN_MESSAGE_MAP(CChartEditView, CRichEditView)
	//{{AFX_MSG_MAP(CChartEditView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_REPEAT, OnEditRepeat)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPEAT, OnUpdateEditRepeat)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE, OnUpdateEditReplace)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_STYLES_BOLD, OnStylesBold)
	ON_UPDATE_COMMAND_UI(ID_STYLES_BOLD, OnUpdateStylesBold)
	ON_COMMAND(ID_STYLES_HEADING, OnStylesHeading)
	ON_UPDATE_COMMAND_UI(ID_STYLES_HEADING, OnUpdateStylesHeading)
	ON_COMMAND(ID_STYLES_ITALIC, OnStylesItalic)
	ON_UPDATE_COMMAND_UI(ID_STYLES_ITALIC, OnUpdateStylesItalic)
	ON_COMMAND(ID_STYLES_NORMAL, OnStylesNormal)
	ON_UPDATE_COMMAND_UI(ID_STYLES_NORMAL, OnUpdateStylesNormal)
	ON_COMMAND(ID_SYLES_NORMAL, OnSylesNormal)
	ON_UPDATE_COMMAND_UI(ID_SYLES_NORMAL, OnUpdateSylesNormal)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartEditView construction/destruction

CChartEditView::CChartEditView()
{
	// TODO: add construction code here

}

CChartEditView::~CChartEditView()
{
}

BOOL CChartEditView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CChartEditView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CChartEditView printing

BOOL CChartEditView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CChartEditView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CChartEditView diagnostics

#ifdef _DEBUG
void CChartEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CChartEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CChartEditDoc* CChartEditView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChartEditDoc)));
	return (CChartEditDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChartEditView message handlers

void CChartEditView::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditFind() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditFind(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditRepeat() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditRepeat(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditReplace() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditReplace(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditSelectAll() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditSelectAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnEditUndo() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnStylesBold() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateStylesBold(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnStylesHeading() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateStylesHeading(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnStylesItalic() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateStylesItalic(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnStylesNormal() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateStylesNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CChartEditView::OnSylesNormal() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditView::OnUpdateSylesNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
