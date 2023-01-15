// WizardDoc.cpp : implementation of the CWizardDoc class
//

#include "stdafx.h"
#include "Wizard.h"

#include "WizardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizardDoc

IMPLEMENT_DYNCREATE(CWizardDoc, CDocument)

BEGIN_MESSAGE_MAP(CWizardDoc, CDocument)
END_MESSAGE_MAP()


// CWizardDoc construction/destruction

CWizardDoc::CWizardDoc()
{
	// TODO: add one-time construction code here

}

CWizardDoc::~CWizardDoc()
{
}

BOOL CWizardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CWizardDoc serialization

void CWizardDoc::Serialize(CArchive& ar)
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


// CWizardDoc diagnostics

#ifdef _DEBUG
void CWizardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWizardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CWizardDoc commands
