// ChartEditDoc.cpp : implementation of the CChartEditDoc class
//

#include "stdafx.h"
#include "ChartEdit.h"

#include "ChartEditDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartEditDoc

IMPLEMENT_DYNCREATE(CChartEditDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CChartEditDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CChartEditDoc)
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartEditDoc construction/destruction

CChartEditDoc::CChartEditDoc()
{
	// TODO: add one-time construction code here

}

CChartEditDoc::~CChartEditDoc()
{
}

BOOL CChartEditDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CChartEditDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CChartEditCntrItem(preo, (CChartEditDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CChartEditDoc serialization

void CChartEditDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CChartEditDoc diagnostics

#ifdef _DEBUG
void CChartEditDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CChartEditDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChartEditDoc commands

BOOL CChartEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	
	return TRUE;
}

BOOL CChartEditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CRichEditDoc::OnSaveDocument(lpszPathName);
}

void CChartEditDoc::SetTitle(LPCTSTR lpszTitle) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditDoc::SetTitle(lpszTitle);
}

void CChartEditDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditDoc::SetPathName(lpszPathName, bAddToMRU);
}

void CChartEditDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRichEditDoc::OnCloseDocument();
}


void CChartEditDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


void CChartEditDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	
}

void CChartEditDoc::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
