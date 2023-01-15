// OpenFilesDoc.cpp : implementation of the COpenFilesDoc class
//

#include "stdafx.h"
#include "OpenFiles.h"

#include "OpenFilesDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenFilesDoc

IMPLEMENT_DYNCREATE(COpenFilesDoc, CDocument)

BEGIN_MESSAGE_MAP(COpenFilesDoc, CDocument)
END_MESSAGE_MAP()


// COpenFilesDoc construction/destruction

COpenFilesDoc::COpenFilesDoc()
{
	// TODO: add one-time construction code here

}

COpenFilesDoc::~COpenFilesDoc()
{
}

BOOL COpenFilesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// COpenFilesDoc serialization

void COpenFilesDoc::Serialize(CArchive& ar)
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


// COpenFilesDoc diagnostics

#ifdef _DEBUG
void COpenFilesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenFilesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COpenFilesDoc commands
