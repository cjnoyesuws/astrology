// astrpgraphDoc.cpp : implementation of the CAstrpgraphDoc class
//

#include "stdafx.h"
#include "astrpgraph.h"

#include "astrpgraphDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphDoc

IMPLEMENT_DYNCREATE(CAstrpgraphDoc, CDocument)

BEGIN_MESSAGE_MAP(CAstrpgraphDoc, CDocument)
	//{{AFX_MSG_MAP(CAstrpgraphDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphDoc construction/destruction

CAstrpgraphDoc::CAstrpgraphDoc()
{
	// TODO: add one-time construction code here

}

CAstrpgraphDoc::~CAstrpgraphDoc()
{
}

BOOL CAstrpgraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphDoc serialization

void CAstrpgraphDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphDoc diagnostics

#ifdef _DEBUG
void CAstrpgraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstrpgraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrpgraphDoc commands
