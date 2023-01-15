// AstrowDoc.cpp : implementation of the CAstrowDoc class
//

#include "stdafx.h"
#include "Astrow.h"

#include "AstrowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrowDoc

IMPLEMENT_DYNCREATE(CAstrowDoc, CDocument)

BEGIN_MESSAGE_MAP(CAstrowDoc, CDocument)
	//{{AFX_MSG_MAP(CAstrowDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrowDoc construction/destruction

CAstrowDoc::CAstrowDoc()
{
	// TODO: add one-time construction code here

}

CAstrowDoc::~CAstrowDoc()
{
}

BOOL CAstrowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAstrowDoc serialization

void CAstrowDoc::Serialize(CArchive& ar)
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
// CAstrowDoc diagnostics

#ifdef _DEBUG
void CAstrowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstrowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrowDoc commands
