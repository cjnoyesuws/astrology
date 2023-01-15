// EZAstrowDoc.cpp : implementation of the CEZAstrowDoc class
//

#include "stdafx.h"
#include "EZAstrow.h"

#include "EZAstrowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEZAstrowDoc

IMPLEMENT_DYNCREATE(CEZAstrowDoc, CDocument)

BEGIN_MESSAGE_MAP(CEZAstrowDoc, CDocument)
END_MESSAGE_MAP()


// CEZAstrowDoc construction/destruction

CEZAstrowDoc::CEZAstrowDoc()
{
	// TODO: add one-time construction code here

}

CEZAstrowDoc::~CEZAstrowDoc()
{
}

BOOL CEZAstrowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEZAstrowDoc serialization

void CEZAstrowDoc::Serialize(CArchive& ar)
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


// CEZAstrowDoc diagnostics

#ifdef _DEBUG
void CEZAstrowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEZAstrowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEZAstrowDoc commands
