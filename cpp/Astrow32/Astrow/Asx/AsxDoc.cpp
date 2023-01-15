// AsxDoc.cpp : implementation of the CAsxDoc class
//

#include "stdafx.h"
#include "Asx.h"

#include "AsxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAsxDoc

IMPLEMENT_DYNCREATE(CAsxDoc, CDocument)

BEGIN_MESSAGE_MAP(CAsxDoc, CDocument)
END_MESSAGE_MAP()


// CAsxDoc construction/destruction

CAsxDoc::CAsxDoc()
{
	// TODO: add one-time construction code here

}

CAsxDoc::~CAsxDoc()
{
}

BOOL CAsxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CAsxDoc serialization

void CAsxDoc::Serialize(CArchive& ar)
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


// CAsxDoc diagnostics

#ifdef _DEBUG
void CAsxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAsxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAsxDoc commands
