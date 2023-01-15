// AstrowDaoFileListDoc.cpp : implementation of the CAstrowDaoFileListDoc class
//

#include "stdafx.h"
#include "AstrowDaoFileList.h"

#include "AstrowDaoFileListSet.h"
#include "AstrowDaoFileListDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListDoc

IMPLEMENT_DYNCREATE(CAstrowDaoFileListDoc, CDocument)

BEGIN_MESSAGE_MAP(CAstrowDaoFileListDoc, CDocument)
	//{{AFX_MSG_MAP(CAstrowDaoFileListDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAstrowDaoFileListDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CAstrowDaoFileListDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAstrowDaoFileList to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {879C7204-D961-42C7-A14F-67B18622BA3B}
static const IID IID_IAstrowDaoFileList =
{ 0x879c7204, 0xd961, 0x42c7, { 0xa1, 0x4f, 0x67, 0xb1, 0x86, 0x22, 0xba, 0x3b } };

BEGIN_INTERFACE_MAP(CAstrowDaoFileListDoc, CDocument)
	INTERFACE_PART(CAstrowDaoFileListDoc, IID_IAstrowDaoFileList, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListDoc construction/destruction

CAstrowDaoFileListDoc::CAstrowDaoFileListDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CAstrowDaoFileListDoc::~CAstrowDaoFileListDoc()
{
	AfxOleUnlockApp();
}

BOOL CAstrowDaoFileListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListDoc serialization

void CAstrowDaoFileListDoc::Serialize(CArchive& ar)
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
// CAstrowDaoFileListDoc diagnostics

#ifdef _DEBUG
void CAstrowDaoFileListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAstrowDaoFileListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAstrowDaoFileListDoc commands
