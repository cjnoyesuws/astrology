// TextConverterDoc.cpp : implementation of the CTextConverterDoc class
//

#include "stdafx.h"
#include "TextConverter.h"

#include "TextConverterDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextConverterDoc

IMPLEMENT_DYNCREATE(CTextConverterDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextConverterDoc, CDocument)
END_MESSAGE_MAP()


// CTextConverterDoc construction/destruction

CTextConverterDoc::CTextConverterDoc()
{
	// TODO: add one-time construction code here

}

CTextConverterDoc::~CTextConverterDoc()
{
}

BOOL CTextConverterDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTextConverterDoc serialization

void CTextConverterDoc::Serialize(CArchive& ar)
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


// CTextConverterDoc diagnostics

#ifdef _DEBUG
void CTextConverterDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextConverterDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTextConverterDoc commands
