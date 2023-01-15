// CommentDoc.cpp : implementation of the CCommentDoc class
//

#include "stdafx.h"
#include "Comment.h"

#include "CommentDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommentDoc

IMPLEMENT_DYNCREATE(CCommentDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommentDoc, CDocument)
	//{{AFX_MSG_MAP(CCommentDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommentDoc construction/destruction

CCommentDoc::CCommentDoc()
{
	// TODO: add one-time construction code here

}

CCommentDoc::~CCommentDoc()
{
}

BOOL CCommentDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCommentDoc serialization

void CCommentDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	((CEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CCommentDoc diagnostics

#ifdef _DEBUG
void CCommentDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCommentDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommentDoc commands
